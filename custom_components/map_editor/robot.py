"""Bounded SSH transport and the robot's existing save protocol."""

import asyncio
from contextlib import asynccontextmanager
import hashlib
import os
from pathlib import Path
import re

import asyncssh

from .codec import MAX_ARCHIVE, MAX_MAP

_ROOT = "/mnt/data/rockrobo"


class SetupError(ValueError):
    """ValueError-compatible setup failure with a config-flow translation key."""

    def __init__(self, code: str, message: str | None = None):
        super().__init__(message if message is not None else code)
        self.code = code


class AuthorizationError(SetupError):
    """SSH authentication rejection or a missing local private key."""

    def __init__(self, message: str | None = None):
        super().__init__("authorization_required", message)


def setup_key(path: str) -> str:
    target = Path(path)
    target.parent.mkdir(parents=True, exist_ok=True, mode=0o700)
    if not target.exists():
        key = asyncssh.generate_private_key("ssh-ed25519")
        with open(target, "xb", opener=lambda name, flags: os.open(name, flags, 0o600)) as file:
            file.write(key.export_private_key())
    return asyncssh.read_private_key(target).export_public_key().decode().strip()


async def host_key(host: str, port: int) -> str:
    try:
        async with asyncio.timeout(15):
            key = await asyncssh.get_server_host_key(host, port=port, config=None)
        if key is None:
            raise ValueError("Robot did not provide an SSH host key.")
        return key.get_fingerprint()
    except (OSError, asyncssh.Error, ValueError) as err:
        raise SetupError("cannot_connect") from err


class _Host(asyncssh.SSHClient):
    def __init__(self, fingerprint: str):
        self._fingerprint = fingerprint

    def validate_host_public_key(self, host, addr, port, key):
        return key.get_fingerprint() == self._fingerprint


class Robot:
    def __init__(self, host: str, port: int, key_path: str, fingerprint: str):
        self._host = host
        self._port = port
        self._key_path = key_path
        self._fingerprint = fingerprint

    @asynccontextmanager
    async def _connect(self):
        try:
            key = await asyncio.to_thread(asyncssh.read_private_key, self._key_path)
        except FileNotFoundError as err:
            raise AuthorizationError("The local SSH private key is missing. Set up robot authorization again.") from err
        except (OSError, ValueError) as err:
            raise SetupError(
                "key_failed", "Could not read the local SSH private key. Check its contents and permissions.",
            ) from err
        async with asyncssh.connect(
            self._host, port=self._port, username="root", client_keys=[key],
            client_factory=lambda: _Host(self._fingerprint), known_hosts=(),
            config=None, agent_path=None, password_auth=False,
            kbdint_auth=False, connect_timeout=10, login_timeout=10,
            encoding=None,
        ) as connection:
            yield connection

    async def _run(self, command: str, data: bytes = b"", limit: int = MAX_MAP) -> bytes:
        async with asyncio.timeout(30), self._connect() as connection:
            async with connection.create_process(command) as process:
                stderr = asyncio.create_task(self._read(process.stderr, 8192))
                try:
                    if data:
                        process.stdin.write(data)
                        process.stdin.write_eof()
                    output = await self._read(process.stdout, limit)
                    error = await stderr
                    await process.wait_closed()
                    if process.exit_status != 0:
                        raise ValueError(f"Robot command failed (exit {process.exit_status}): {error.decode(errors='replace')}")
                    return output
                finally:
                    stderr.cancel()
                    await asyncio.gather(stderr, return_exceptions=True)

    @staticmethod
    async def _read(stream, limit: int) -> bytes:
        result = bytearray()
        while chunk := await stream.read(min(65536, limit - len(result) + 1)):
            result.extend(chunk)
            if len(result) > limit:
                raise ValueError("Robot output exceeds the size limit.")
        return bytes(result)

    async def check(self):
        try:
            result = await self._run("id -u; cat /etc/os-release", limit=8192)
        except SetupError:
            raise
        except asyncssh.PermissionDenied as err:
            raise AuthorizationError() from err
        except asyncssh.HostKeyNotVerifiable as err:
            raise SetupError("host_key_changed") from err
        except (OSError, asyncssh.Error, ValueError) as err:
            raise SetupError("cannot_connect") from err
        if not result.startswith(b"0\n"):
            raise SetupError(
                "root_required", "The SSH session does not have root access. Check the robot's SSH configuration.",
            )
        if b"ROBOROCK_VERSION=4.3.5_1612\n" not in result:
            raise SetupError(
                "unsupported_firmware", "The robot's firmware is not supported. See the integration documentation.",
            )

    async def read_map(self) -> tuple[bytes, bytes]:
        return tuple(await asyncio.gather(*(
            self._run(f"head -c {MAX_MAP + 1} {_ROOT}/{name}")
            for name in ("last_map", "PersistData_1.data")
        )))

    async def boot(self) -> str:
        return (await self._run("cat /proc/sys/kernel/random/boot_id", limit=128)).decode().strip()

    async def upload(self, work: str, payload: bytes) -> str:
        return (await self._run(
            f"set -eu; umask 077; mkdir -m 700 {work}; "
            f"tar -xpf - -C {work}; chmod 700 {work}/map-maint; "
            "cat /proc/sys/kernel/random/boot_id", payload, 128,
        )).decode().strip()

    async def install(self, work: str, change, report):
        async with asyncio.timeout(120), self._connect() as connection:
            async with connection.create_process(f"/bin/sh {work}/save.sh {work}") as process:
                stderr = asyncio.create_task(self._progress(process.stderr, report))
                try:
                    header = bytearray()
                    while not header.endswith(b"\n"):
                        byte = await process.stdout.read(1)
                        if not byte or len(header) >= 128:
                            raise ValueError("Invalid backup header.")
                        header.extend(byte)
                    match = re.fullmatch(rb"BACKUP (\d+) ([a-f0-9]{32})\n", header)
                    if not match or not 1024 <= int(match[1]) <= MAX_ARCHIVE:
                        raise ValueError("Invalid backup size or header.")
                    archive = await process.stdout.readexactly(int(match[1]))
                    if hashlib.md5(archive).hexdigest().encode() != match[2]:
                        raise ValueError("Backup transfer checksum mismatch.")
                    patch = await change(archive)
                    process.stdin.write(b"PATCH\n" + patch)
                    process.stdin.write_eof()
                    trailer = await self._read(process.stdout, 128)
                    await stderr
                    await process.wait_closed()
                    # A reboot may close SSH without an exit status; acknowledgement is mandatory.
                    if trailer.strip() != b"INSTALLED" or process.exit_status not in (0, None):
                        raise ValueError(f"Installation not acknowledged (exit {process.exit_status}).")
                finally:
                    stderr.cancel()
                    await asyncio.gather(stderr, return_exceptions=True)

    @staticmethod
    async def _progress(stream, report):
        pending = b""
        while chunk := await stream.read(4096):
            pending += chunk
            while b"\n" in pending:
                line, pending = pending.split(b"\n", 1)
                report(line[-8192:].decode(errors="replace"))
            pending = pending[-8192:]
        if pending:
            report(pending.decode(errors="replace"))
