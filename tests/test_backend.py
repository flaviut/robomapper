"""Exercise saves and host-key verification without robot hardware."""

import asyncio
import hashlib
from pathlib import Path
import struct
import tempfile
import unittest

import asyncssh

from custom_components.map_editor import codec
from custom_components.map_editor.robot import Robot
from custom_components.map_editor.service import Editor
from test_codec import fixture, region


def snapshot():
    data, _ = fixture()
    catalog = bytearray(0x9C)
    catalog[0:3] = bytes([1, 2, 6])
    struct.pack_into("<i", catalog, 0x94, 2)
    return data, codec.pack_tar({
        "SharedMultiMapInfo": region(8, catalog),
        "last_map": codec.decode(data["native"]["raster"]),
        "PersistData_1.data": codec.decode(data["native"]["persistence"]),
    })


class _Robot:
    def __init__(self, directory):
        self.directory = directory
        self.data, self.archive = snapshot()
        self.installs = 0
        self.gate = asyncio.Event()

    async def upload(self, work, payload):
        assert set(codec.read_tar(payload)) == {"save.sh", "map-maint"}
        return "old-boot"

    async def install(self, work, change, report):
        self.installs += 1
        await self.gate.wait()
        self.patch = codec.read_tar(await change(self.archive))
        backups = list(self.directory.glob("*/untouched-stopped-backup.tar"))
        assert len(backups) == 1 and backups[0].read_bytes() == self.archive
        assert backups[0].stat().st_mode & 0o777 == 0o600
        report("Installed")

    async def boot(self):
        return "new-boot"

    async def read_map(self):
        return self.patch["last_map"], self.patch["PersistData_1.data"]


class ServiceTests(unittest.IsolatedAsyncioTestCase):
    async def asyncSetUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.directory = Path(self.tmp.name)
        self.robot = _Robot(self.directory)
        self.tasks = []

        def spawn(coro, name):
            task = asyncio.create_task(coro, name=name)
            self.tasks.append(task)
            return task

        self.editor = Editor(self.robot, self.directory, asyncio.to_thread, spawn)

    async def asyncTearDown(self):
        for task in self.tasks:
            task.cancel()
        await asyncio.gather(*self.tasks, return_exceptions=True)
        self.tmp.cleanup()

    async def test_save_survives_request_and_backs_up(self):
        data = {**self.robot.data, "confirmation": "install-and-reboot"}
        status = self.editor.save(data)
        self.assertEqual(status["state"], "saving")
        with self.assertRaisesRegex(ValueError, "already running"):
            self.editor.save(data)
        with self.assertRaisesRegex(ValueError, "save is running"):
            await self.editor.load()
        self.robot.gate.set()
        await self.tasks[0]
        self.assertEqual(self.editor.status()["state"], "done")
        self.assertEqual(self.robot.installs, 1)
        self.assertEqual(len(list(self.directory.glob("*/receipt.json"))), 1)
        self.assertEqual((await self.editor.load())["checksum"], codec.inspect_map(self.robot.patch["last_map"])["checksum"])

    async def test_explicit_confirmation(self):
        with self.assertRaisesRegex(ValueError, "Confirm"):
            self.editor.save(self.robot.data)
        self.assertFalse(self.tasks)

    async def test_failure_never_retries(self):
        self.robot.archive = b"invalid backup"
        self.robot.gate.set()
        with self.assertLogs("custom_components.map_editor.service", level="ERROR"):
            self.editor.save({**self.robot.data, "confirmation": "install-and-reboot"})
            await self.tasks[0]
        self.assertEqual(self.robot.installs, 1)
        self.assertEqual(self.editor.status()["state"], "error")
        self.assertIn("No automatic retry", self.editor.status()["error"])
        self.assertFalse(list(self.directory.glob("*/receipt.json")))

    async def test_cancellation_reports_uncertainty(self):
        self.editor.save({**self.robot.data, "confirmation": "install-and-reboot"})
        while not self.robot.installs:
            await asyncio.sleep(0.01)
        self.tasks[0].cancel()
        await asyncio.gather(*self.tasks, return_exceptions=True)
        self.assertEqual(self.editor.status()["state"], "error")
        self.assertIn("interrupted", self.editor.status()["error"])


class _Server(asyncssh.SSHServer):
    def begin_auth(self, username):
        return False


class TransportTests(unittest.IsolatedAsyncioTestCase):
    async def asyncSetUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.host_key = asyncssh.generate_private_key("ssh-ed25519")
        self.key_path = Path(self.tmp.name) / "key"
        self.key_path.write_bytes(asyncssh.generate_private_key("ssh-ed25519").export_private_key())
        _, self.archive = snapshot()
        self.received = b""
        self.trailer = b"INSTALLED\n"
        self.digest = hashlib.md5(self.archive).hexdigest()
        self.server = await asyncssh.create_server(
            _Server, "127.0.0.1", 0, server_host_keys=[self.host_key],
            process_factory=self._process, encoding=None,
        )
        self.robot = Robot("127.0.0.1", self.server.get_port(), str(self.key_path), self.host_key.get_fingerprint())

    async def asyncTearDown(self):
        self.server.close()
        await self.server.wait_closed()
        self.tmp.cleanup()

    async def _process(self, process):
        if process.command.startswith("/bin/sh "):
            process.stdout.write(f"BACKUP {len(self.archive)} {self.digest}\n".encode() + self.archive)
            process.stderr.write(b"Stopped writers\n")
            self.received = await process.stdin.read()
            process.stdout.write(self.trailer)
        else:
            process.stdout.write(b"0\nROBOROCK_VERSION=4.3.5_1612\n")
        process.exit(0)

    async def test_pinned_host_and_transfer(self):
        await self.robot.check()
        stages = []

        async def change(archive):
            self.assertEqual(archive, self.archive)
            return b"candidate"

        await self.robot.install("/mnt/data/test", change, stages.append)
        self.assertEqual(self.received, b"PATCH\ncandidate")
        self.assertEqual(stages, ["Stopped writers"])

    async def test_changed_host_key_rejected(self):
        robot = Robot("127.0.0.1", self.server.get_port(), str(self.key_path), "SHA256:wrong")
        with self.assertRaises(asyncssh.HostKeyNotVerifiable):
            await robot.check()

    async def test_corrupt_backup_never_authorizes(self):
        self.digest = "0" * 32

        async def change(archive):
            self.fail("Corrupt backup reached patch builder")

        with self.assertRaisesRegex(ValueError, "checksum"):
            await self.robot.install("/mnt/data/test", change, lambda line: None)
        self.assertEqual(self.received, b"")

    async def test_missing_ack_is_not_success(self):
        self.trailer = b""

        async def change(archive):
            return b"candidate"

        with self.assertRaisesRegex(ValueError, "not acknowledged"):
            await self.robot.install("/mnt/data/test", change, lambda line: None)


if __name__ == "__main__":
    unittest.main()
