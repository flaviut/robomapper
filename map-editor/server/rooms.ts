import { editRegion, readRegion } from './persistence.ts'

const regionBytes = 0x13f120
const segment = 0x31da0

type Frame = { width: number, height: number, left: number, top: number }

function grid(region: Buffer, map: Frame) {
  if (region.length !== regionBytes) throw new Error('Unsupported room data.')
  if (!region[segment] || !region[segment + 4]) return null
  const width = region.readInt32LE(segment + 8)
  const height = region.readInt32LE(segment + 12)
  if (width <= 0 || height <= 0 || width * height > 1024 * 1024) throw new Error('Invalid room dimensions.')
  return { width, height, left: map.left + Math.ceil(width / 2), top: map.top + Math.ceil(height / 2) }
}

function roomRegion(data: Buffer) {
  try { return readRegion(data, 5) } catch (error) {
    throw new Error(`Invalid room data: ${error instanceof Error ? error.message : 'Decode failed.'}`)
  }
}

export function inspectRooms(data: Buffer, map: Frame) {
  const region = roomRegion(data)
  const rooms = Buffer.alloc(map.width * map.height)
  if (!region) return rooms.toString('base64')
  const source = grid(region, map)
  if (!source) return rooms.toString('base64')

  // Segmentation is centered; occupancy is a cropped window of that grid.
  for (let y = 0; y < map.height; y++) {
    const sy = source.top + y
    if (sy < 0 || sy >= source.height) continue
    for (let x = 0; x < map.width; x++) {
      const sx = source.left + x
      if (sx < 0 || sx >= source.width) continue
      rooms[y * map.width + x] = region[segment + 16 + sy * source.width + sx]! & 0x3f
    }
  }
  return rooms.toString('base64')
}

export function writeRooms(data: Buffer, map: Frame, rooms: Buffer): Buffer {
  if (rooms.length !== map.width * map.height || rooms.some(id => id > 63)) throw new Error('Invalid room IDs.')
  const before = Buffer.from(inspectRooms(data, map), 'base64')
  if (rooms.equals(before)) return data
  return editRegion(data, 5, region => {
    const target = grid(region, map)
    if (!target) throw new Error('The map has no editable room grid.')
    for (let y = 0; y < map.height; y++) {
      for (let x = 0; x < map.width; x++) {
        const index = y * map.width + x
        if (rooms[index] === before[index]) continue
        const sx = target.left + x
        const sy = target.top + y
        if (sx < 0 || sy < 0 || sx >= target.width || sy >= target.height) {
          throw new Error('Room edit is outside the segmentation grid.')
        }
        const offset = segment + 16 + sy * target.width + sx
        region[offset] = (region[offset]! & 0xc0) | rooms[index]!
      }
    }
  })
}
