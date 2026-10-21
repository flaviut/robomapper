"""Administrator-only WebSocket boundary."""

import logging

import probatio as vol

from homeassistant.components import websocket_api
from homeassistant.config_entries import ConfigEntryState

_DOMAIN = "map_editor"
_LOGGER = logging.getLogger(__name__)


def register_api(hass):
    websocket_api.async_register_command(hass, _request)


@websocket_api.websocket_command({
    vol.Required("type"): _DOMAIN,
    vol.Required("action"): vol.In(("entries", "load", "save", "status")),
    vol.Optional("entry_id"): str,
    vol.Optional("data"): dict,
})
@websocket_api.require_admin
@websocket_api.async_response
async def _request(hass, connection, msg):
    if msg["action"] == "entries":
        connection.send_result(msg["id"], [
            {"id": entry.entry_id, "name": entry.title,
             "vacuum_entity": entry.data.get("vacuum_entity")}
            for entry in hass.config_entries.async_entries(_DOMAIN)
            if entry.state is ConfigEntryState.LOADED
        ])
        return

    entry = hass.config_entries.async_get_entry(msg.get("entry_id", ""))
    if entry is None or entry.domain != _DOMAIN or entry.state is not ConfigEntryState.LOADED:
        connection.send_error(msg["id"], "not_loaded", "Robot is not configured or connected.")
        return
    editor = entry.runtime_data
    try:
        if msg["action"] == "load":
            result = await editor.load()
        elif msg["action"] == "save":
            result = editor.save(msg.get("data", {}))
        else:
            result = editor.status()
    except Exception:
        _LOGGER.exception("Map editor %s failed for %s", msg["action"], entry.title)
        connection.send_error(msg["id"], "robot_error", "Robot operation failed. Check SSH access and the Home Assistant log.")
        return
    connection.send_result(msg["id"], result)
