"""Integration lifecycle and API checks against Home Assistant itself."""

from pathlib import Path
import tempfile
from types import MappingProxyType, SimpleNamespace
import unittest
from unittest.mock import AsyncMock, MagicMock, patch

from homeassistant import loader
from homeassistant.components import frontend
from homeassistant.config_entries import ConfigEntries, ConfigEntry, ConfigEntryState
from homeassistant.core import HomeAssistant
from homeassistant.exceptions import Unauthorized

from custom_components import map_editor
from custom_components.map_editor.api import _request
from custom_components.map_editor.config_flow import ConfigFlow
from custom_components.map_editor.service import AuthorizationError, SetupError

_DATA = {"host": "robot.local", "port": 22, "key_path": "/config/key", "fingerprint": "SHA256:test"}


class IntegrationTests(unittest.IsolatedAsyncioTestCase):
    async def asyncSetUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.hass = HomeAssistant(self.tmp.name)
        self.hass.config_entries = ConfigEntries(self.hass, {})
        self.hass.http = SimpleNamespace(async_register_static_paths=AsyncMock())
        self.entry = self._entry("robot.local")
        self.connection = SimpleNamespace(user=SimpleNamespace(is_admin=True),
                                          send_result=MagicMock(), send_error=MagicMock())

    async def asyncTearDown(self):
        await self.hass.async_stop()
        self.tmp.cleanup()

    def _entry(self, host):
        entry = ConfigEntry(
            domain="map_editor", data={**_DATA, "host": host}, options={},
            title=host, source="user", unique_id=f"{host}:22", version=1,
            minor_version=1, discovery_keys=MappingProxyType({}), subentries_data=[],
            state=ConfigEntryState.LOADED,
        )
        self.hass.config_entries._entries[entry.entry_id] = entry
        return entry

    async def _setup(self, entry):
        with patch("custom_components.map_editor.connect_robot", new=AsyncMock()):
            self.assertTrue(await map_editor.async_setup_entry(self.hass, entry))

    async def _call(self, action, **kwargs):
        _request(self.hass, self.connection, {"id": 1, "type": "map_editor", "action": action, **kwargs})
        await self.hass.async_block_till_done(wait_background_tasks=True)

    async def test_manifest_loads_in_ha(self):
        (Path(self.tmp.name) / "custom_components").symlink_to(
            Path(__file__).resolve().parents[1] / "custom_components", target_is_directory=True,
        )
        loader.async_setup(self.hass)
        with self.assertLogs("homeassistant.loader", level="WARNING"):
            integration = await loader.async_get_integration(self.hass, "map_editor")
        self.assertEqual(integration.domain, "map_editor")
        self.assertEqual(integration.version, "0.1.0")

    async def test_setup_registers_bundled_assets_and_api(self):
        self.assertTrue(await map_editor.async_setup(self.hass, {}))
        config = self.hass.http.async_register_static_paths.call_args.args[0][0]
        self.assertEqual(config.url_path, "/map_editor_static")
        self.assertTrue((Path(config.path) / "panel.js").is_file())
        self.assertTrue((Path(config.path) / "panel.css").is_file())
        self.assertIn("map_editor", self.hass.data["websocket_api"])

    async def test_panel_and_unload(self):
        await self._setup(self.entry)
        self.assertTrue(frontend.async_panel_exists(self.hass, "map_editor"))
        panel = self.hass.data[frontend.DATA_PANELS]["map_editor"]
        self.assertTrue(panel.require_admin)
        self.assertTrue(await map_editor.async_unload_entry(self.hass, self.entry))
        self.assertFalse(frontend.async_panel_exists(self.hass, "map_editor"))
        await self._setup(self.entry)
        self.assertTrue(frontend.async_panel_exists(self.hass, "map_editor"))

    async def test_other_robot_keeps_panel(self):
        await self._setup(self.entry)
        other = self._entry("second.local")
        await self._setup(other)
        self.assertTrue(await map_editor.async_unload_entry(self.hass, self.entry))
        self.assertTrue(frontend.async_panel_exists(self.hass, "map_editor"))

    async def test_busy_unload_refused(self):
        self.entry.runtime_data = SimpleNamespace(busy=lambda: True)
        self.assertFalse(await map_editor.async_unload_entry(self.hass, self.entry))

    async def test_api_requires_admin(self):
        self.connection.user.is_admin = False
        with self.assertRaises(Unauthorized):
            _request(self.hass, self.connection, {"id": 1, "type": "map_editor", "action": "entries"})

    async def test_api_lists_robots(self):
        await self._call("entries")
        self.connection.send_result.assert_called_once_with(1, [
            {"id": self.entry.entry_id, "name": "robot.local"},
        ])

    async def test_api_rejects_unknown_entry(self):
        await self._call("load", entry_id="unknown")
        self.connection.send_error.assert_called_once()
        self.connection.send_result.assert_not_called()

    async def test_load_routes_through_service(self):
        self.entry.runtime_data = SimpleNamespace(load=AsyncMock(return_value={"map": "fixture"}))
        await self._call("load", entry_id=self.entry.entry_id)
        self.entry.runtime_data.load.assert_awaited_once()
        self.connection.send_result.assert_called_once_with(1, {"map": "fixture"})

    async def test_flow_uses_no_vacuum_dependency(self):
        flow = ConfigFlow()
        flow.hass = self.hass
        flow.context = {"source": "user"}
        flow.flow_id = "test"
        flow.handler = "map_editor"
        result = await flow.async_step_user()
        self.assertEqual(set(result["data_schema"].schema), {"host", "port"})
        result = await flow.async_step_user({"host": "new.local", "port": 22})
        self.assertEqual(result["step_id"], "authorize")
        command = result["description_placeholders"]["command"]
        self.assertIn("ssh-ed25519 ", command)
        self.assertIn("root@new.local", command)
        self.assertIn("authorized_keys", command)
        key_path = Path(self.tmp.name) / "map_editor" / "id_ed25519"
        self.assertEqual(key_path.stat().st_mode & 0o777, 0o600)
        self.assertEqual(key_path.parent.stat().st_mode & 0o777, 0o700)
        data = {**_DATA, "host": "new.local", "key_path": str(key_path)}
        with patch("custom_components.map_editor.config_flow.enroll_robot", new=AsyncMock(return_value=data)):
            result = await flow.async_step_authorize({})
        self.assertEqual(result["type"], "create_entry")
        self.assertEqual(result["data"], data)

    def _reconfigure_flow(self):
        self.entry.runtime_data = SimpleNamespace(busy=lambda: False)
        flow = ConfigFlow()
        flow.hass = self.hass
        flow.context = {"source": "reconfigure", "entry_id": self.entry.entry_id}
        flow.flow_id = "test"
        flow.handler = "map_editor"
        return flow

    async def test_reconfigure_reuses_working_access_without_key_setup(self):
        flow = self._reconfigure_flow()
        with (
            patch("custom_components.map_editor.config_flow.enroll_robot",
                  new=AsyncMock(return_value=dict(_DATA))) as enroll,
            patch("custom_components.map_editor.config_flow.setup_access",
                  new=AsyncMock(return_value="ssh-ed25519 test")) as setup,
            patch("custom_components.map_editor.robot.asyncssh.generate_private_key") as generate,
            patch("custom_components.map_editor.robot.asyncssh.read_private_key") as read,
            patch.object(self.hass.config_entries, "async_schedule_reload") as reload,
        ):
            result = await flow.async_step_reconfigure({"host": "robot.local", "port": 22})
        self.assertEqual(result["type"], "abort")
        self.assertEqual(result["reason"], "reconfigure_successful")
        enroll.assert_awaited_once_with(_DATA)
        setup.assert_not_awaited()
        generate.assert_not_called()
        read.assert_not_called()
        reload.assert_called_once_with(self.entry.entry_id)
        self.assertEqual(dict(self.entry.data), _DATA)

    async def test_reconfigure_requests_authorization_only_after_access_is_denied(self):
        flow = self._reconfigure_flow()
        calls = []

        async def enroll(data):
            calls.append("enroll")
            if len(calls) == 1:
                raise AuthorizationError()
            return dict(data)

        async def setup(path, host, port):
            calls.append("setup")
            return "authorization command"

        with (
            patch("custom_components.map_editor.config_flow.enroll_robot",
                  new=AsyncMock(side_effect=enroll)) as enroll_mock,
            patch("custom_components.map_editor.config_flow.setup_access",
                  new=AsyncMock(side_effect=setup)) as setup_mock,
            patch.object(self.hass.config_entries, "async_schedule_reload") as reload,
        ):
            result = await flow.async_step_reconfigure({"host": "robot.local", "port": 22})
            self.assertEqual(result["step_id"], "authorize")
            self.assertEqual(calls, ["enroll", "setup"])
            self.assertEqual(result["description_placeholders"]["command"], "authorization command")
            self.assertEqual(flow._data, _DATA)
            setup_mock.assert_awaited_once_with(_DATA["key_path"], _DATA["host"], _DATA["port"])
            result = await flow.async_step_authorize({})
        self.assertEqual(result["reason"], "reconfigure_successful")
        self.assertEqual(enroll_mock.await_count, 2)
        for call in enroll_mock.await_args_list:
            self.assertEqual(call.args, (_DATA,))
        reload.assert_called_once_with(self.entry.entry_id)
        self.assertEqual(dict(self.entry.data), _DATA)

    async def test_reconfigure_unrelated_setup_failure_does_not_request_authorization(self):
        for code in ("cannot_connect", "key_failed"):
            with self.subTest(code=code):
                flow = self._reconfigure_flow()
                with (
                    patch("custom_components.map_editor.config_flow.enroll_robot",
                          new=AsyncMock(side_effect=SetupError(code))) as enroll,
                    patch("custom_components.map_editor.config_flow.setup_access",
                          new=AsyncMock()) as setup,
                    patch.object(self.hass.config_entries, "async_schedule_reload") as reload,
                ):
                    result = await flow.async_step_reconfigure({"host": "robot.local", "port": 22})
                self.assertEqual(result["step_id"], "reconfigure")
                self.assertEqual(result["errors"], {"base": code})
                self.assertIsNone(result["description_placeholders"])
                enroll.assert_awaited_once_with(_DATA)
                setup.assert_not_awaited()
                reload.assert_not_called()
                self.assertEqual(dict(self.entry.data), _DATA)

    async def test_reconfigure_authorization_key_failure_stays_on_reconfigure(self):
        flow = self._reconfigure_flow()
        with (
            patch("custom_components.map_editor.config_flow.enroll_robot",
                  new=AsyncMock(side_effect=AuthorizationError())),
            patch("custom_components.map_editor.config_flow.setup_access",
                  new=AsyncMock(side_effect=OSError("key is not writable"))),
        ):
            result = await flow.async_step_reconfigure({"host": "robot.local", "port": 22})
        self.assertEqual(result["step_id"], "reconfigure")
        self.assertEqual(result["errors"], {"base": "key_failed"})
        self.assertIsNone(result["description_placeholders"])

    async def test_flow_rejects_unverified_connection(self):
        flow = ConfigFlow()
        flow.hass = self.hass
        flow.context = {"source": "user"}
        await flow.async_step_user({"host": "new.local", "port": 22})
        with patch("custom_components.map_editor.config_flow.enroll_robot", new=AsyncMock(side_effect=ValueError("wrong firmware"))):
            result = await flow.async_step_authorize({})
        self.assertEqual(result["errors"], {"base": "cannot_connect"})


if __name__ == "__main__":
    unittest.main()
