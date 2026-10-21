"""Map loading and one browser-independent save at a time."""

import asyncio
from datetime import datetime, timezone
from enum import StrEnum
import hashlib
import json
import logging
import os
from pathlib import Path
import shlex
from uuid import uuid4

from .codec import apply_edit, load_map, make_patch, pack_tar, parse_edit, read_tar
from .robot import AuthorizationError, Robot, SetupError, host_key, setup_key

_LOGGER = logging.getLogger(__name__)


async def setup_access(path: str, host: str, port: int) -> str:
    public_key = await asyncio.to_thread(setup_key, path)
    script = await asyncio.to_thread(
        (Path(__file__).parent / "tools" / "authorize.sh").read_text,
    )
    destination = shlex.quote(f"root@{host}")
    command = shlex.quote(script)
    return f"printf '%s\\n' {shlex.quote(public_key)} | ssh -p {port} {destination} {command}"


async def enroll_robot(data: dict) -> dict:
    data = dict(data)
    if not data.get("fingerprint"):
        data["fingerprint"] = await host_key(data["host"], data["port"])
    await connect_robot(data)
    return data


async def connect_robot(data: dict) -> Robot:
    robot = Robot(data["host"], data["port"], data["key_path"], data["fingerprint"])
    await robot.check()
    return robot


class State(StrEnum):
    IDLE = "idle"
    SAVING = "saving"
    DONE = "done"
    ERROR = "error"


def _store(directory: Path, name: str, data: bytes):
    directory.mkdir(parents=True, exist_ok=True, mode=0o700)
    with (directory / name).open("xb") as file:
        os.chmod(file.fileno(), 0o600)
        file.write(data)
        file.flush()
        os.fsync(file.fileno())
    # Persist the filename before telling the robot it may replace files.
    fd = os.open(directory, os.O_RDONLY)
    try:
        os.fsync(fd)
    finally:
        os.close(fd)


def _payload() -> bytes:
    tools = Path(__file__).parent / "tools"
    return pack_tar({name: (tools / name).read_bytes() for name in ("save.sh", "map-maint")})


def _patch(edit, archive: bytes) -> bytes:
    files = make_patch(edit, read_tar(archive))
    hashes = "".join(f"{hashlib.md5(data).hexdigest()}  {name}\n" for name, data in files.items())
    return pack_tar({**files, "patch.md5": hashes.encode()})


class Editor:
    def __init__(self, robot: Robot, backups: Path, execute, spawn, save_lock: asyncio.Lock):
        self._robot = robot
        self._backups = backups
        self._execute = execute
        self._spawn = spawn
        self._save_lock = save_lock
        self._task = None
        self._status = {"state": State.IDLE, "stage": ""}

    def status(self) -> dict:
        return self._status.copy()

    def busy(self) -> bool:
        return self._task is not None and not self._task.done()

    async def load(self) -> dict:
        if self.busy():
            raise ValueError("A save is running. Wait for verification.")
        raster, persistence = await self._robot.read_map()
        return await self._execute(load_map, raster, persistence)

    async def save(self, data: dict) -> dict:
        if self._save_lock.locked():
            raise ValueError("A save is already running.")
        if data.get("confirmation") != "install-and-reboot":
            raise ValueError("Confirm saving and restart before continuing.")
        await self._save_lock.acquire()
        self._status = {"state": State.SAVING, "stage": "Validate edits", "id": uuid4().hex}
        coroutine = self._save(data)
        try:
            self._task = self._spawn(coroutine, "map_editor save")
        except Exception:
            coroutine.close()
            self._save_lock.release()
            raise
        self._task.add_done_callback(self._finished)
        return self.status()

    def _finished(self, task):
        if task.cancelled():
            self._status.update(state=State.ERROR, error="Save interrupted. Check the robot before retrying.")
        self._save_lock.release()

    def _stage(self, message: str):
        self._status["stage"] = message
        _LOGGER.info("Map save %s: %s", self._status["id"], message)

    async def _save(self, data: dict):
        directory = self._backups / self._status["id"]
        work = f"/mnt/data/map-editor-{self._status['id']}"
        try:
            edit = await self._execute(parse_edit, data)
            expected = await self._execute(apply_edit, edit)
            await self._execute(_store, directory, "request.json", json.dumps({
                "work": work, "source": hashlib.sha256(edit.raster).hexdigest(),
            }).encode())
            self._status["backup"] = str(directory)
            self._stage("Upload robot tools")
            boot = await self._robot.upload(work, await self._execute(_payload))

            async def change(archive):
                self._stage("Store stopped backup")
                await self._execute(_store, directory, "untouched-stopped-backup.tar", archive)
                self._stage("Build edited map files")
                patch = await self._execute(_patch, edit, archive)
                await self._execute(_store, directory, "candidate.tar", patch)
                self._stage("Install and restart")
                return patch

            self._stage("Stop writers and back up")
            await self._robot.install(work, change, self._stage)
            self._stage("Wait for restart and verify map")
            await self._verify(boot, expected)
            await self._execute(_store, directory, "receipt.json", json.dumps({
                "completed": datetime.now(timezone.utc).isoformat(), "work": work,
            }).encode())
            self._status.update(state=State.DONE, stage="Saved and verified after restart")
        except Exception as err:
            _LOGGER.exception("Map save failed at %s; backup: %s; robot: %s", self._status["stage"], directory, work)
            self._status.update(state=State.ERROR, error=f"{err} Check the robot before retrying. No automatic retry was made.")

    async def _verify(self, boot: str, expected: tuple[bytes, bytes]):
        deadline = asyncio.get_running_loop().time() + 240
        while asyncio.get_running_loop().time() < deadline:
            try:
                if await self._robot.boot() != boot:
                    raster, persistence = await self._robot.read_map()
                    actual = await self._execute(load_map, raster, persistence)
                    wanted = await self._execute(load_map, *expected)
                    if actual["native"]["raster"] == wanted["native"]["raster"] and actual["rooms"] == wanted["rooms"]:
                        return
            except (OSError, ValueError, asyncio.TimeoutError):
                pass
            except Exception as err:
                # SSH disconnects during reboot are expected; installation is never retried.
                _LOGGER.debug("Robot not ready after reboot: %s", err)
            await asyncio.sleep(2)
        raise ValueError("Could not verify the edited map after reboot.")
