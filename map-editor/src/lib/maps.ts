export interface RobotMap {
  width: number
  height: number
  left: number
  top: number
  scale: number
  checksum: string
  cells: Uint8Array
  rooms: Uint8Array
}

export async function loadMap(hostname: string): Promise<RobotMap> {
  const response = await fetch('/api/map', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ hostname }),
  })
  const result = await response.json() as Omit<RobotMap, 'cells' | 'rooms'> & {
    cells: string
    rooms: string
    error?: string
  }
  if (!response.ok) throw new Error(result.error ?? 'Map loading failed.')

  return { ...result, cells: decodeCells(result.cells), rooms: decodeCells(result.rooms) }
}

function decodeCells(value: string): Uint8Array {
  return Uint8Array.from(atob(value), cell => cell.charCodeAt(0))
}
