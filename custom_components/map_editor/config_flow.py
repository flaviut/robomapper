"""Configure root SSH access without depending on a vacuum integration."""

import logging

import probatio as vol

from homeassistant import config_entries
from homeassistant.helpers import selector

from .service import connect_robot

DOMAIN = "map_editor"
_LOGGER = logging.getLogger(__name__)


def _schema(defaults):
    return vol.Schema({
        vol.Required("host", default=defaults.get("host", "")): str,
        vol.Required("port", default=defaults.get("port", 22)): vol.All(int, vol.Range(min=1, max=65535)),
        vol.Required("key_path", default=defaults.get("key_path", "/config/map_editor/id_ed25519")): str,
        vol.Required("fingerprint", default=defaults.get("fingerprint", "")): str,
        vol.Optional("vacuum_entity", description={"suggested_value": defaults.get("vacuum_entity")}):
            selector.EntitySelector(selector.EntitySelectorConfig(domain="vacuum")),
    })


class ConfigFlow(config_entries.ConfigFlow, domain=DOMAIN):
    VERSION = 1

    async def async_step_user(self, user_input=None):
        return await self._configure("user", user_input, {})

    async def async_step_reconfigure(self, user_input=None):
        entry = self._get_reconfigure_entry()
        if entry.state is config_entries.ConfigEntryState.LOADED and entry.runtime_data.busy():
            return self.async_abort(reason="save_running")
        return await self._configure("reconfigure", user_input, dict(entry.data))

    async def _configure(self, step, user_input, defaults):
        errors = {}
        if user_input is not None:
            user_input = {**user_input, "host": user_input["host"].strip(),
                          "fingerprint": user_input["fingerprint"].strip()}
            try:
                if not user_input["fingerprint"].startswith("SHA256:"):
                    raise ValueError("Enter the trusted SHA256 SSH host-key fingerprint.")
                await connect_robot(user_input)
            except ValueError:
                errors["base"] = "cannot_connect"
                _LOGGER.debug("Robot setup failed", exc_info=True)
            else:
                await self.async_set_unique_id(f"{user_input['host'].lower()}:{user_input['port']}")
                if step == "reconfigure":
                    self._abort_if_unique_id_mismatch()
                    return self.async_update_reload_and_abort(self._get_reconfigure_entry(), data=user_input)
                self._abort_if_unique_id_configured()
                return self.async_create_entry(title=user_input["host"], data=user_input)
        return self.async_show_form(step_id=step, data_schema=_schema(user_input or defaults), errors=errors)
