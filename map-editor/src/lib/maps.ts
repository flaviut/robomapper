export interface RobotMap {
  width: number
  height: number
  left: number
  top: number
  scale: number
  checksum: string
  cells: Uint8Array
}

export async function loadMap(hostname: string): Promise<RobotMap> {
  const response = await fetch('/api/map', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ hostname }),
  })
  const result = await response.json()
  if (!response.ok) throw new Error(result.error ?? 'Map loading failed.')

  return { ...result, cells: Uint8Array.from(atob(result.cells), cell => cell.charCodeAt(0)) }
}
