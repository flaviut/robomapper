"""Setup failure categories survive transport, service, and config flow."""

import asyncio
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import AsyncMock, patch

import asyncssh

from homeassistant.core import HomeAssistant

from custom_components.map_editor import robot, service
from custom_components.map_editor.config_flow import ConfigFlow

_DATA = {"host": "robot.local", "port": 22, "key_path": "/config/key", "fingerprint": "SHA256:pinned"}


class RobotSetupErrorTests(unittest.IsolatedAsyncioTestCase):
    async def test_check_reports_unsupported_firmware(self):
        connection = robot.Robot(**_DATA)
        with patch.object(connection, "_run", new=AsyncMock(return_value=b"0\nROBOROCK_VERSION=other\n")):
            with self.assertRaises(service.SetupError) as raised:
                await connection.check()
        self.assertEqual(raised.exception.code, "unsupported_firmware")
        self.assertNotIn("4.3.5_1612", str(raised.exception))
        self.assertNotIsInstance(raised.exception, service.AuthorizationError)

    async def test_check_reports_missing_root_access_without_reauthorization(self):
        connection = robot.Robot(**_DATA)
        with patch.object(connection, "_run", new=AsyncMock(return_value=b"1000\nROBOROCK_VERSION=4.3.5_1612\n")):
            with self.assertRaises(service.SetupError) as raised:
                await connection.check()
        self.assertEqual(raised.exception.code, "root_required")
        self.assertNotIsInstance(raised.exception, service.AuthorizationError)

    async def test_check_accepts_supported_root_access(self):
        connection = robot.Robot(**_DATA)
        with patch.object(connection, "_run", new=AsyncMock(return_value=b"0\nROBOROCK_VERSION=4.3.5_1612\n")):
            await connection.check()


class ServiceSetupErrorTests(unittest.IsolatedAsyncioTestCase):
    def test_service_error_constructors_do_not_require_messages(self):
        connection_error = service.SetupError("cannot_connect")
        authorization_error = service.AuthorizationError()
        self.assertIsInstance(connection_error, ValueError)
        self.assertEqual(connection_error.code, "cannot_connect")
        self.assertIsInstance(authorization_error, service.SetupError)
        self.assertEqual(authorization_error.code, "authorization_required")

    async def test_connect_and_enroll_preserve_ssh_failure_categories(self):
        for operation in (service.connect_robot, service.enroll_robot):
            for failure, code in (
                (asyncssh.PermissionDenied("key rejected"), "authorization_required"),
                (asyncssh.HostKeyNotVerifiable("changed key"), "host_key_changed"),
                (ConnectionRefusedError("offline"), "cannot_connect"),
                (TimeoutError("timed out"), "cannot_connect"),
                (asyncssh.ConnectionLost("disconnected"), "cannot_connect"),
                (ValueError("invalid robot response"), "cannot_connect"),
                (FileNotFoundError("not a local key read"), "cannot_connect"),
            ):
                with self.subTest(operation=operation.__name__, code=code, failure=type(failure).__name__):
                    with patch.object(robot.Robot, "_run", new=AsyncMock(side_effect=failure)), patch.object(
                        service, "host_key", new=AsyncMock(),
                    ) as discover:
                        with self.assertRaises(ValueError) as raised:
                            await operation(_DATA)
                    self.assertIsInstance(raised.exception, service.SetupError)
                    self.assertEqual(raised.exception.code, code)
                    self.assertEqual(isinstance(raised.exception, service.AuthorizationError), code == "authorization_required")
                    self.assertIs(raised.exception.__cause__, failure)
                    discover.assert_not_awaited()
                    self.assertEqual(_DATA["fingerprint"], "SHA256:pinned")

    async def test_connect_and_enroll_preserve_setup_error_instances(self):
        failures = [service.SetupError(code) for code in (
            "cannot_connect", "host_key_changed", "unsupported_firmware", "root_required", "key_failed",
        )]
        failures.append(service.AuthorizationError())
        for operation in (service.connect_robot, service.enroll_robot):
            for failure in failures:
                with self.subTest(operation=operation.__name__, code=failure.code):
                    with patch.object(robot.Robot, "check", new=AsyncMock(side_effect=failure)):
                        with self.assertRaises(ValueError) as raised:
                            await operation(_DATA)
                    self.assertIs(raised.exception, failure)

    async def test_enroll_classifies_real_host_key_and_authentication_rejections(self):
        server_key = asyncssh.generate_private_key("ssh-ed25519")
        server = await asyncssh.create_server(
            asyncssh.SSHServer, "127.0.0.1", 0, server_host_keys=[server_key],
        )
        try:
            with tempfile.TemporaryDirectory() as directory:
                key_path = str(Path(directory) / "key")
                robot.setup_key(key_path)
                for fingerprint, code, cause_type in (
                    ("SHA256:wrong", "host_key_changed", asyncssh.HostKeyNotVerifiable),
                    (server_key.get_fingerprint(), "authorization_required", asyncssh.PermissionDenied),
                ):
                    with self.subTest(code=code):
                        data = {"host": "127.0.0.1", "port": server.get_port(),
                                "key_path": key_path, "fingerprint": fingerprint}
                        with patch.object(service, "host_key", new=AsyncMock()) as discover:
                            with self.assertRaises(service.SetupError) as raised:
                                await service.enroll_robot(data)
                        self.assertIsInstance(raised.exception, ValueError)
                        self.assertEqual(raised.exception.code, code)
                        self.assertEqual(isinstance(raised.exception, service.AuthorizationError), code == "authorization_required")
                        self.assertIsInstance(raised.exception.__cause__, cause_type)
                        self.assertEqual(data["fingerprint"], fingerprint)
                        discover.assert_not_awaited()
        finally:
            server.close()
            await server.wait_closed()

    async def test_missing_local_private_key_requires_authorization_without_connecting(self):
        with tempfile.TemporaryDirectory() as directory:
            data = {**_DATA, "key_path": str(Path(directory) / "missing-key")}
            with patch.object(asyncssh, "connect") as connect:
                with self.assertRaises(service.AuthorizationError) as raised:
                    await service.connect_robot(data)
            self.assertEqual(raised.exception.code, "authorization_required")
            self.assertIsInstance(raised.exception.__cause__, FileNotFoundError)
            connect.assert_not_called()

    async def test_unreadable_or_invalid_local_private_key_does_not_require_authorization(self):
        for failure in (PermissionError("unreadable key"), asyncssh.KeyImportError("invalid key")):
            with self.subTest(failure=type(failure).__name__):
                with patch.object(asyncssh, "read_private_key", side_effect=failure), patch.object(
                    asyncssh, "connect",
                ) as connect:
                    with self.assertRaises(service.SetupError) as raised:
                        await service.connect_robot(_DATA)
                self.assertEqual(raised.exception.code, "key_failed")
                self.assertNotIsInstance(raised.exception, service.AuthorizationError)
                self.assertIs(raised.exception.__cause__, failure)
                connect.assert_not_called()

    async def test_enroll_reports_host_key_discovery_failure(self):
        data = {name: value for name, value in _DATA.items() if name != "fingerprint"}
        for failure in (OSError("offline"), TimeoutError("timed out"), asyncssh.ConnectionLost("disconnected"), ValueError("no host key")):
            with self.subTest(failure=type(failure).__name__):
                with patch.object(asyncssh, "get_server_host_key", new=AsyncMock(side_effect=failure)), patch.object(
                    robot.Robot, "check", new=AsyncMock(),
                ) as check:
                    with self.assertRaises(service.SetupError) as raised:
                        await service.enroll_robot(data)
                self.assertEqual(raised.exception.code, "cannot_connect")
                self.assertNotIsInstance(raised.exception, service.AuthorizationError)
                check.assert_not_awaited()
                self.assertNotIn("fingerprint", data)

    async def test_enroll_captures_first_key_without_mutating_input(self):
        data = {name: value for name, value in _DATA.items() if name != "fingerprint"}
        with patch.object(service, "host_key", new=AsyncMock(return_value="SHA256:new")) as discover, patch.object(
            robot.Robot, "check", new=AsyncMock(),
        ):
            enrolled = await service.enroll_robot(data)
        discover.assert_awaited_once_with(data["host"], data["port"])
        self.assertEqual(enrolled, {**data, "fingerprint": "SHA256:new"})
        self.assertNotIn("fingerprint", data)

    async def test_enroll_does_not_swallow_cancellation(self):
        with patch.object(robot.Robot, "check", new=AsyncMock(side_effect=asyncio.CancelledError)):
            with self.assertRaises(asyncio.CancelledError):
                await service.enroll_robot(_DATA)


class ConfigFlowSetupErrorTests(unittest.IsolatedAsyncioTestCase):
    async def asyncSetUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.hass = HomeAssistant(self.tmp.name)
        self.flow = ConfigFlow()
        self.flow.hass = self.hass
        self.flow.context = {"source": "user"}
        self.flow._data = dict(_DATA)
        self.flow._mode = "user"
        self.flow._command = "authorize robot"

    async def asyncTearDown(self):
        await self.hass.async_stop()
        self.tmp.cleanup()

    async def test_authorize_shows_actionable_failure_category(self):
        for failure, code in (
            (asyncssh.PermissionDenied("key rejected"), "authorization_required"),
            (asyncssh.HostKeyNotVerifiable("changed key"), "host_key_changed"),
            (TimeoutError("timed out"), "cannot_connect"),
        ):
            with self.subTest(code=code):
                with patch.object(robot.Robot, "_run", new=AsyncMock(side_effect=failure)):
                    result = await self.flow.async_step_authorize({})
                self.assertEqual(result["step_id"], "authorize")
                self.assertEqual(result["errors"], {"base": code})

    async def test_authorize_shows_unsupported_firmware(self):
        with patch.object(robot.Robot, "_run", new=AsyncMock(return_value=b"0\nROBOROCK_VERSION=other\n")):
            result = await self.flow.async_step_authorize({})
        self.assertEqual(result["errors"], {"base": "unsupported_firmware"})

    async def test_reconfigure_non_authorization_errors_return_to_connection_form_without_command(self):
        self.flow._mode = "reconfigure"
        for code in ("cannot_connect", "host_key_changed", "unsupported_firmware", "root_required", "key_failed"):
            with self.subTest(code=code):
                with patch(
                    "custom_components.map_editor.config_flow.enroll_robot",
                    new=AsyncMock(side_effect=service.SetupError(code)),
                ):
                    result = await self.flow.async_step_authorize({})
                self.assertEqual(result["step_id"], "reconfigure")
                self.assertEqual(result["errors"], {"base": code})
                self.assertFalse(result.get("description_placeholders"))
                self.assertEqual(set(result["data_schema"].schema), {"host", "port"})
                self.assertEqual(result["data_schema"]({}), {"host": _DATA["host"], "port": _DATA["port"]})
                self.assertEqual(self.flow._data, _DATA)

    async def test_reconfigure_authorization_error_keeps_authorization_command(self):
        self.flow._mode = "reconfigure"
        with patch(
            "custom_components.map_editor.config_flow.enroll_robot",
            new=AsyncMock(side_effect=service.AuthorizationError()),
        ):
            result = await self.flow.async_step_authorize({})
        self.assertEqual(result["step_id"], "authorize")
        self.assertEqual(result["errors"], {"base": "authorization_required"})
        self.assertEqual(result["description_placeholders"], {"command": "authorize robot"})

    async def test_new_user_non_authorization_errors_keep_classified_authorization_form(self):
        for code in ("cannot_connect", "host_key_changed", "unsupported_firmware", "root_required", "key_failed"):
            with self.subTest(code=code):
                with patch(
                    "custom_components.map_editor.config_flow.enroll_robot",
                    new=AsyncMock(side_effect=service.SetupError(code)),
                ):
                    result = await self.flow.async_step_authorize({})
                self.assertEqual(result["step_id"], "authorize")
                self.assertEqual(result["errors"], {"base": code})
                self.assertEqual(result["description_placeholders"], {"command": "authorize robot"})

    def test_error_translations_match_and_do_not_prescribe_reauthorization_for_every_failure(self):
        directory = Path(__file__).resolve().parents[1] / "custom_components" / "map_editor"
        strings = json.loads((directory / "strings.json").read_text())
        english = json.loads((directory / "translations" / "en.json").read_text())
        self.assertEqual(strings, english)
        errors = strings["config"]["error"]
        for name in ("cannot_connect", "unsupported_firmware", "host_key_changed", "root_required", "key_failed"):
            with self.subTest(code=name):
                self.assertNotIn("authorization command", errors[name])
                self.assertNotIn("4.3.5_1612", errors[name])
        self.assertIn("authorization command", errors["authorization_required"])


if __name__ == "__main__":
    unittest.main()
