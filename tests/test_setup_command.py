"""Authorization commands belong to the service, not the config flow."""

import shlex
import tempfile
import unittest
from unittest.mock import AsyncMock, patch

from homeassistant.config_entries import ConfigEntries
from homeassistant.core import HomeAssistant

from custom_components.map_editor.config_flow import ConfigFlow
from custom_components.map_editor.service import setup_access


class SetupCommandTests(unittest.IsolatedAsyncioTestCase):
    async def test_authorization_command(self):
        public_key = "ssh-ed25519 AAAA map-editor"
        with patch("custom_components.map_editor.service.setup_key", return_value=public_key) as setup_key:
            command = await setup_access("/config/key", "robot.local", 22)

        setup_key.assert_called_once_with("/config/key")
        self.assertEqual(shlex.split(command), [
            "printf", "%s\\n", public_key, "|", "ssh", "-p", "22", "root@robot.local",
            "umask 077; mkdir -p ~/.ssh; cat >> ~/.ssh/authorized_keys",
        ])

    async def test_quotes_shell_arguments(self):
        public_key = "ssh-ed25519 AAAA owner's $(key); comment"
        host = "robot's $(hostname); local"
        with patch("custom_components.map_editor.service.setup_key", return_value=public_key):
            command = await setup_access("/config/key", host, 2222)

        self.assertEqual(shlex.split(command), [
            "printf", "%s\\n", public_key, "|", "ssh", "-p", "2222", f"root@{host}",
            "umask 077; mkdir -p ~/.ssh; cat >> ~/.ssh/authorized_keys",
        ])

    async def test_flow_displays_command(self):
        with tempfile.TemporaryDirectory() as directory:
            hass = HomeAssistant(directory)
            hass.config_entries = ConfigEntries(hass, {})
            flow = ConfigFlow()
            flow.hass = hass
            flow.context = {"source": "user"}
            command = "Ready-to-display authorization command"
            try:
                with patch("custom_components.map_editor.config_flow.setup_access",
                           new=AsyncMock(return_value=command)) as setup:
                    result = await flow.async_step_user({"host": " robot.local ", "port": 2222})

                setup.assert_awaited_once_with(hass.config.path("map_editor", "id_ed25519"),
                                               "robot.local", 2222)
                self.assertEqual(result["step_id"], "authorize")
                self.assertEqual(result["description_placeholders"], {"command": command})
            finally:
                await hass.async_stop()


if __name__ == "__main__":
    unittest.main()
