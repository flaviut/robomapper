import { deflateSync, inflateSync } from 'node:zlib'

interface Field {
  id: number
  value: number | Buffer
  raw: Buffer
}

interface Region {
  fields: Field[]
  parts: Buffer[]
  data: Buffer
  compressed: number
}

function varint(data: Buffer, cursor: { pos: number }): number {
  let value = 0
  for (let shift = 0; shift < 49; shift += 7) {
    if (cursor.pos >= data.length) throw new Error('Incomplete persistence data.')
    const byte = data[cursor.pos++]!
    value += (byte & 127) * 2 ** shift
    if (byte < 128 && Number.isSafeInteger(value)) return value
  }
  throw new Error('Invalid persistence data.')
}

function encodeInt(value: number): Buffer {
  const bytes: number[] = []
  do {
    bytes.push(value % 128 | (value >= 128 ? 128 : 0))
    value = Math.floor(value / 128)
  } while (value)
  return Buffer.from(bytes)
}

function encodeField(id: number, value: Buffer): Buffer {
  return Buffer.concat([encodeInt(id * 8 + 2), encodeInt(value.length), value])
}

function fields(data: Buffer): Field[] {
  const cursor = { pos: 0 }
  const result: Field[] = []
  while (cursor.pos < data.length) {
    const start = cursor.pos
    const tag = varint(data, cursor)
    const id = Math.floor(tag / 8)
    const wire = tag % 8
    if (!id) throw new Error('Invalid persistence data.')
    if (wire === 0) {
      const value = varint(data, cursor)
      result.push({ id, value, raw: data.subarray(start, cursor.pos) })
      continue
    }

    const size = wire === 2 ? varint(data, cursor) : wire === 1 ? 8 : wire === 5 ? 4 : -1
    if (size < 0 || size > data.length - cursor.pos) throw new Error('Invalid persistence data.')
    const value = data.subarray(cursor.pos, cursor.pos + size)
    cursor.pos += size
    result.push({ id: wire === 2 ? id : -id, value, raw: data.subarray(start, cursor.pos) })
  }
  return result
}

function scalar(values: Field[], id: number): number {
  const value = values.findLast(field => field.id === id)?.value ?? 0
  if (typeof value !== 'number') throw new Error('Invalid persistence data.')
  return value
}

function findRegion(data: Buffer, id: number) {
  const envelope = fields(data)
  const matches = envelope.filter(field => field.id === 20 && Buffer.isBuffer(field.value)
    && scalar(fields(field.value), 10) === id)
  if (matches.length > 1) throw new Error('Duplicate persistence region.')
  return { envelope, field: matches[0] }
}

function decode(field: Field): Region {
  if (!Buffer.isBuffer(field.value)) throw new Error('Invalid persistence region.')
  const values = fields(field.value)
  const size = scalar(values, 40)
  if (size <= 0 || size > 16 * 1024 * 1024) throw new Error('Unsupported persistence region size.')
  const compressed = scalar(values, 20)
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
    if (!Buffer.isBuffer(part.value) || total >= size) throw new Error('Invalid persistence parts.')
    const decoded = compressed ? inflateSync(part.value, { maxOutputLength: size - total }) : part.value
    total += decoded.length
    parts.push(decoded)
  }
  if (total !== size || !parts.length || (sizes.length && (sizes.length !== parts.length
    || parts.some((part, i) => part.length !== sizes[i])))) throw new Error('Incomplete persistence region.')
  return { fields: values, parts, data: Buffer.concat(parts), compressed }
}

export function readRegion(data: Buffer, id: number): Buffer | null {
  const { field } = findRegion(data, id)
  return field ? decode(field).data : null
}

export function editRegion(data: Buffer, id: number, edit: (region: Buffer) => void): Buffer {
  const { envelope, field } = findRegion(data, id)
  if (!field) throw new Error('Missing persistence region.')
  const region = decode(field)
  const next = Buffer.from(region.data)
  edit(next)
  if (next.equals(region.data)) return data

  // Preserve unknown fields, flags, part boundaries, and unchanged compressed parts.
  let index = 0
  let offset = 0
  const values = region.fields.map(part => {
    if (part.id !== 50) return part.raw
    const before = region.parts[index++]!
    const after = next.subarray(offset, offset + before.length)
    offset += before.length
    if (after.equals(before)) return part.raw
    return encodeField(50, region.compressed ? deflateSync(after) : after)
  })
  return Buffer.concat(envelope.map(item => item === field ? encodeField(20, Buffer.concat(values)) : item.raw))
}
