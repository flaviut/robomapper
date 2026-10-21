import { inflateSync } from 'node:zlib'

const regionBytes = 0x13f120
const segment = 0x31da0

type Field = { id: number, value: number | Buffer }

function varint(data: Buffer, cursor: { pos: number }): number {
  let value = 0
  for (let shift = 0; shift < 49; shift += 7) {
    if (cursor.pos >= data.length) throw new Error('Incomplete room data.')
    const byte = data[cursor.pos++]!
    value += (byte & 127) * 2 ** shift
    if (byte < 128 && Number.isSafeInteger(value)) return value
  }

  throw new Error('Invalid room data.')
}

function fields(data: Buffer): Field[] {
  const cursor = { pos: 0 }
  const result: Field[] = []
  while (cursor.pos < data.length) {
    const tag = varint(data, cursor)
    const id = Math.floor(tag / 8)
    const wire = tag % 8
    if (!id) throw new Error('Invalid room data.')
    if (wire === 0) {
      result.push({ id, value: varint(data, cursor) })
      continue
    }

    const size = wire === 2 ? varint(data, cursor) : wire === 1 ? 8 : wire === 5 ? 4 : -1
    if (size < 0 || size > data.length - cursor.pos) throw new Error('Invalid room data.')
    if (wire === 2) result.push({ id, value: data.subarray(cursor.pos, cursor.pos + size) })
    cursor.pos += size
  }

  return result
}

function scalar(values: Field[], id: number): number {
  const value = values.findLast(field => field.id === id)?.value ?? 0
  if (typeof value !== 'number') throw new Error('Invalid room data.')
  return value
}

function decodeRegion(data: Buffer): Buffer | null {
  let region: Buffer | null = null
  for (const field of fields(data)) {
    if (field.id !== 20 || !Buffer.isBuffer(field.value)) continue
    const values = fields(field.value)
    if (scalar(values, 10) !== 5) continue
    if (region || scalar(values, 40) !== regionBytes) throw new Error('Unsupported room data.')

    const sizes: number[] = []
    const parts: Buffer[] = []
    let total = 0
    for (const part of values) {
      if (part.id === 60) {
        if (typeof part.value === 'number') sizes.push(part.value)
        else {
          const cursor = { pos: 0 }
          while (cursor.pos < part.value.length) sizes.push(varint(part.value, cursor))
        }
      }
      if (part.id !== 50) continue
      if (!Buffer.isBuffer(part.value) || total >= regionBytes) throw new Error('Invalid room data.')

      // Firmware compresses each part separately, even when the encrypt flag is set.
      const decoded = scalar(values, 20)
        ? inflateSync(part.value, { maxOutputLength: regionBytes - total }) : part.value
      total += decoded.length
      if (total > regionBytes) throw new Error('Invalid room data.')
      parts.push(decoded)
    }

    if (total !== regionBytes || !parts.length
      || (sizes.length && (sizes.length !== parts.length
        || parts.some((part, i) => part.length !== sizes[i])))) {
      throw new Error('Incomplete room data.')
    }
    region = Buffer.concat(parts)
  }

  return region
}

export function inspectRooms(data: Buffer, map: { width: number, height: number, left: number, top: number }) {
  const region = decodeRegion(data)
  const rooms = Buffer.alloc(map.width * map.height)
  if (!region || !region[segment] || !region[segment + 4]) return rooms.toString('base64')

  const width = region.readInt32LE(segment + 8)
  const height = region.readInt32LE(segment + 12)
  if (width <= 0 || height <= 0 || width * height > 1024 * 1024) {
    throw new Error('Invalid room dimensions.')
  }

  // Segmentation is centered; the occupancy raster is a cropped window of that grid.
  const left = map.left + Math.ceil(width / 2)
  const top = map.top + Math.ceil(height / 2)
  for (let y = 0; y < map.height; y++) {
    const sy = top + y
    if (sy < 0 || sy >= height) continue
    for (let x = 0; x < map.width; x++) {
      const sx = left + x
      if (sx < 0 || sx >= width) continue
      rooms[y * map.width + x] = region[segment + 16 + sy * width + sx]! & 0x3f
    }
  }

  return rooms.toString('base64')
}
