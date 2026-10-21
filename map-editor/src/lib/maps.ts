import { inHass, request } from './hass.ts'

export interface SaveStatus {
  state: 'idle' | 'saving' | 'done' | 'error'
  stage: string
  id?: string
  error?: string
  backup?: string
}

export function saveStatus(entryId: string): Promise<SaveStatus> {
  return request<SaveStatus>('status', entryId)
}

export interface RobotMap {
  width: number
  height: number
  left: number
  top: number
  scale: number
  checksum: string
  cells: Uint8Array
  rooms: Uint8Array
  native: { raster: string, persistence: string }
}

type MapData = Omit<RobotMap, 'cells' | 'rooms'> & { cells: string, rooms: string, error?: string }

export async function loadMap(hostname: string): Promise<RobotMap> {
  if (inHass()) return decodeMap(await request<MapData>('load', hostname))
  const response = await fetch('/api/map', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ hostname }),
  })
  const result = await response.json() as MapData
  if (!response.ok) throw new Error(result.error ?? 'Map loading failed.')
  return decodeMap(result)
}

export async function saveMap(hostname: string, map: RobotMap, cells: Uint8Array, rooms: Uint8Array,
  progress: (status: SaveStatus) => void = () => {}): Promise<RobotMap> {
  if (inHass()) {
    let status = await request<SaveStatus>('save', hostname, {
      native: map.native, cells: encodeCells(cells), rooms: encodeCells(rooms),
      confirmation: 'install-and-reboot',
    })
    while (status.state === 'saving') {
      progress(status)
      await new Promise(resolve => setTimeout(resolve, 2000))
      status = await saveStatus(hostname)
    }
    progress(status)
    if (status.state !== 'done') throw new Error(status.error ?? 'Save was interrupted. Check the robot before retrying.')
    return loadMap(hostname)
  }
  const response = await fetch('/api/map/save', {
    method: 'POST', headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ native: map.native, cells: encodeCells(cells), rooms: encodeCells(rooms),
      hostname, confirmation: 'install-and-reboot' }),
  })
  const result = await response.json() as { map: MapData, error?: string }
  if (!response.ok) throw new Error(result.error ?? 'Could not save the map.')
  return decodeMap(result.map)
}

function encodeCells(cells: Uint8Array): string {
  let text = ''
  for (let offset = 0; offset < cells.length; offset += 32768) {
    text += String.fromCharCode(...cells.subarray(offset, offset + 32768))
  }
  return btoa(text)
}

function decodeMap(result: MapData): RobotMap {
  return { ...result, cells: decodeCells(result.cells), rooms: decodeCells(result.rooms) }
}

function decodeCells(value: string): Uint8Array {
  return Uint8Array.from(atob(value), cell => cell.charCodeAt(0))
}
