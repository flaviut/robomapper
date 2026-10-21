export interface HomeAssistant {
  callWS<T>(message: Record<string, unknown>): Promise<T>
}

export interface RobotEntry {
  id: string
  name: string
  vacuum_entity?: string
}

let hass: HomeAssistant | undefined
let panel: HTMLElement | undefined

export function setHass(value: HomeAssistant, element: HTMLElement) {
  hass = value
  panel = element
}

export function inHass(): boolean { return hass !== undefined }

export function request<T>(action: string, entry_id?: string, data?: unknown): Promise<T> {
  if (!hass) throw new Error('Home Assistant is not connected.')
  return hass.callWS<T>({ type: 'map_editor', action, ...(entry_id ? { entry_id } : {}), ...(data ? { data } : {}) })
}

export function openVacuum(entityId: string) {
  panel?.dispatchEvent(new CustomEvent('hass-more-info', {
    detail: { entityId }, bubbles: true, composed: true,
  }))
}
