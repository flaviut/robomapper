"""Integration lifecycle and API checks against Home Assistant itself."""

from pathlib import Path
import tempfile
from types import MappingProxyType, SimpleNamespace
import unittest
from unittest.mock import AsyncMock, MagicMock, patch

from homeassistant.components import frontend
from homeassistant.config_entries import ConfigEntries, ConfigEntry, ConfigEntryState
from homeassistant.core import HomeAssistant
from homeassistant.exceptions import Unauthorized

from custom_components import map_editor
from custom_components.map_editor.api import _request
from custom_components.map_editor.config_flow import ConfigFlow

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

    async def test_api_lists_optional_link(self):
        await self._call("entries")
        self.connection.send_result.assert_called_once_with(1, [
            {"id": self.entry.entry_id, "name": "robot.local", "vacuum_entity": None},
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
        with patch("custom_components.map_editor.config_flow.connect_robot", new=AsyncMock()):
            result = await flow.async_step_user({**_DATA, "host": "new.local"})
        self.assertEqual(result["type"], "create_entry")
        self.assertNotIn("vacuum_entity", result["data"])

    async def test_flow_rejects_unverified_connection(self):
        flow = ConfigFlow()
        flow.hass = self.hass
        with patch("custom_components.map_editor.config_flow.connect_robot", new=AsyncMock(side_effect=ValueError("wrong firmware"))):
            result = await flow.async_step_user(_DATA)
        self.assertEqual(result["errors"], {"base": "cannot_connect"})


if __name__ == "__main__":
    unittest.main()
