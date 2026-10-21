"""Set up robot access using an integration-managed SSH key."""

import logging

import probatio as vol

from homeassistant import config_entries

from .service import AuthorizationError, SetupError, enroll_robot, setup_access

DOMAIN = "map_editor"
_LOGGER = logging.getLogger(__name__)


def _schema(defaults):
    return vol.Schema({
        vol.Required("host", default=defaults.get("host", "")): str,
        vol.Required("port", default=defaults.get("port", 22)): vol.All(int, vol.Range(min=1, max=65535)),
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
        if user_input is None:
            return self.async_show_form(step_id=step, data_schema=_schema(defaults))

        host = user_input["host"].strip()
        port = user_input["port"]
        await self.async_set_unique_id(f"{host.lower()}:{port}")
        if step == "reconfigure":
            self._abort_if_unique_id_mismatch()
        else:
            self._abort_if_unique_id_configured()

        self._mode = step
        self._data = {"host": host, "port": port,
                      "key_path": defaults.get("key_path", self.hass.config.path("map_editor", "id_ed25519"))}
        if defaults.get("fingerprint"):
            self._data["fingerprint"] = defaults["fingerprint"]

        if step == "reconfigure":
            try:
                data = await enroll_robot(self._data)
            except AuthorizationError:
                pass
            except SetupError as err:
                _LOGGER.debug("Robot reconfiguration failed", exc_info=True)
                return self.async_show_form(step_id=step, data_schema=_schema(user_input),
                                            errors={"base": err.code})
            else:
                return self.async_update_reload_and_abort(self._get_reconfigure_entry(), data=data)

        try:
            self._command = await setup_access(self._data["key_path"], host, port)
        except (OSError, ValueError):
            _LOGGER.debug("SSH key setup failed", exc_info=True)
            return self.async_show_form(step_id=step, data_schema=_schema(user_input),
                                        errors={"base": "key_failed"})

        return await self.async_step_authorize()

    async def async_step_authorize(self, user_input=None):
        errors = {}
        if user_input is not None:
            try:
                data = await enroll_robot(self._data)
            except ValueError as err:
                errors["base"] = err.code if isinstance(err, SetupError) else "cannot_connect"
                _LOGGER.debug("Robot setup failed", exc_info=True)
                if (self._mode == "reconfigure" and isinstance(err, SetupError)
                        and not isinstance(err, AuthorizationError)):
                    return self.async_show_form(step_id="reconfigure", data_schema=_schema(self._data), errors=errors)
            else:
                if self._mode == "reconfigure":
                    return self.async_update_reload_and_abort(self._get_reconfigure_entry(), data=data)
                return self.async_create_entry(title=data["host"], data=data)

        return self.async_show_form(step_id="authorize", data_schema=vol.Schema({}),
                                    description_placeholders={"command": self._command}, errors=errors)
