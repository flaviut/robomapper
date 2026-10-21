import { createHash } from 'node:crypto'
import { inspectMap } from './map.ts'
import { inspectRooms, writeRooms } from './rooms.ts'
import { maxMapBytes } from './ssh.ts'

export interface EditInput {
  native: { raster: string, persistence: string }
  cells: string
  rooms: string
}

export interface MapEdit {
  raster: Buffer
  persistence: Buffer
  cells: Buffer
  rooms: Buffer
  beforeRooms: Buffer
}

function decode(value: unknown): Buffer {
  if (typeof value !== 'string' || value.length > Math.ceil(maxMapBytes / 3) * 4) throw new Error('Invalid map data.')
  const data = Buffer.from(value, 'base64')
  if (data.length > maxMapBytes || data.toString('base64') !== value) throw new Error('Invalid map encoding.')
  return data
}

export function parseEdit(input: EditInput): MapEdit {
  const raster = decode(input.native.raster)
  const persistence = decode(input.native.persistence)
  const map = inspectMap(raster)
  const cells = decode(input.cells)
  const rooms = decode(input.rooms)
  if (cells.length !== map.width * map.height || rooms.length !== cells.length || rooms.some(id => id > 63)) {
    throw new Error('Invalid edited map dimensions or room IDs.')
  }
  return { raster, persistence, cells, rooms, beforeRooms: Buffer.from(inspectRooms(persistence, map), 'base64') }
}

export function applyEdit(edit: MapEdit, raster = edit.raster, persistence = edit.persistence) {
  if (!raster.equals(edit.raster)) throw new Error('The robot map changed. Reload it before saving.')
  const map = inspectMap(raster)
  const beforeRooms = Buffer.from(inspectRooms(persistence, map), 'base64')
  if (!edit.rooms.equals(edit.beforeRooms) && !beforeRooms.equals(edit.beforeRooms)) {
    throw new Error('The robot rooms changed. Reload the map before saving.')
  }
  const digest = createHash('md5').update(edit.cells).digest()
  return {
    raster: Buffer.concat([raster.subarray(0, 30), edit.cells, digest]),
    persistence: edit.rooms.equals(edit.beforeRooms) ? persistence : writeRooms(persistence, map, edit.rooms),
  }
}

