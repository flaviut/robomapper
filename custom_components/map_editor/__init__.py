"""S7 map editor: authenticated UI and a small SSH-backed service."""

import asyncio
from pathlib import Path

from homeassistant.components import frontend, panel_custom
from homeassistant.components.http import StaticPathConfig
from homeassistant.config_entries import ConfigEntry, ConfigEntryState
from homeassistant.core import HomeAssistant
from homeassistant.exceptions import ConfigEntryNotReady

from .api import register_api
from .service import Editor, connect_robot

DOMAIN = "map_editor"
_ASSETS = "/map_editor_static"


async def async_setup(hass: HomeAssistant, config: dict) -> bool:
    await hass.http.async_register_static_paths([
        StaticPathConfig(_ASSETS, str(Path(__file__).parent / "frontend"), False),
    ])
    register_api(hass)
    return True


async def async_setup_entry(hass: HomeAssistant, entry: ConfigEntry) -> bool:
    try:
        robot = await connect_robot(entry.data)
    except ValueError as err:
        raise ConfigEntryNotReady("Could not verify root SSH access and supported firmware") from err
    entry.runtime_data = Editor(
        robot, Path(hass.config.path(DOMAIN, "backups")),
        hass.async_add_executor_job, hass.async_create_background_task,
        hass.data.setdefault(DOMAIN, asyncio.Lock()),
    )
    if not frontend.async_panel_exists(hass, DOMAIN):
        await panel_custom.async_register_panel(
            hass, frontend_url_path=DOMAIN, webcomponent_name="s7-map-editor",
            sidebar_title="robomapper", sidebar_icon="mdi:floor-plan",
            module_url=f"{_ASSETS}/panel.js?v=0.1.0", embed_iframe=False,
            require_admin=True,
        )
    return True


async def async_unload_entry(hass: HomeAssistant, entry: ConfigEntry) -> bool:
    if entry.runtime_data.busy():
        return False
    others = [item for item in hass.config_entries.async_entries(DOMAIN)
              if item.entry_id != entry.entry_id and item.state is ConfigEntryState.LOADED]
    if not others:
        frontend.async_remove_panel(hass, DOMAIN)
    return True
