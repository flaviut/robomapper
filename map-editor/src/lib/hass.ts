export interface HomeAssistant {
  callWS<T>(message: Record<string, unknown>): Promise<T>
}

export interface RobotEntry {
  id: string
  name: string
}

let hass: HomeAssistant | undefined

export function setHass(value: HomeAssistant) {
  hass = value
}

export function inHass(): boolean { return hass !== undefined }

export function request<T>(action: string, entry_id?: string, data?: unknown): Promise<T> {
  if (!hass) throw new Error('Home Assistant is not connected.')
  return hass.callWS<T>({ type: 'map_editor', action, ...(entry_id ? { entry_id } : {}), ...(data ? { data } : {}) })
}
