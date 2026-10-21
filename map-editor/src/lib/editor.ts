export const Cell = { Floor: 0, Unknown: 128, Wall: 255 } as const
export type CellValue = typeof Cell[keyof typeof Cell]
export type Fill = CellValue | { room: number }
type Layer = 'cells' | 'rooms'

export interface Point {
  x: number
  y: number
}

export interface CellRect {
  left: number
  top: number
  right: number
  bottom: number
}

interface Change {
  layer: Layer
  index: number
  before: number
  after: number
}

export function cellRect(a: Point, b: Point, width: number, height: number): CellRect {
  return {
    left: Math.max(0, Math.min(width - 1, Math.min(a.x, b.x))),
    top: Math.max(0, Math.min(height - 1, Math.min(a.y, b.y))),
    right: Math.max(0, Math.min(width - 1, Math.max(a.x, b.x))),
    bottom: Math.max(0, Math.min(height - 1, Math.max(a.y, b.y))),
  }
}

function clipLine(from: Point, to: Point, width: number, height: number): [Point, Point] | null {
  if (![from.x, from.y, to.x, to.y].every(Number.isFinite)) return null
  const dx = to.x - from.x
  const dy = to.y - from.y
  let start = 0
  let end = 1
  for (const [p, q] of [[-dx, from.x], [dx, width - 1 - from.x], [-dy, from.y], [dy, height - 1 - from.y]]) {
    if (p === 0) {
      if (q! < 0) return null
      continue
    }
    const ratio = q! / p!
    if (p! < 0) start = Math.max(start, ratio)
    else end = Math.min(end, ratio)
    if (start > end) return null
  }

  return [
    { x: Math.round(from.x + start * dx), y: Math.round(from.y + start * dy) },
    { x: Math.round(from.x + end * dx), y: Math.round(from.y + end * dy) },
  ]
}

export class CellEditor {
  private data: Uint8Array
  private roomData: Uint8Array
  private width: number
  private height: number
  private past: Change[][] = []
  private future: Change[][] = []
  private stroke = new Map<number, Change>()

  constructor(width: number, height: number, cells: Uint8Array, rooms: Uint8Array = new Uint8Array(cells.length)) {
    if (!Number.isInteger(width) || !Number.isInteger(height) || width <= 0 || height <= 0
      || cells.length !== width * height || rooms.length !== cells.length) throw new Error('Invalid map dimensions.')
    this.width = width
    this.height = height
    this.data = cells.slice()
    this.roomData = rooms.slice()
  }

  get cells(): Uint8Array { return this.data }
  get rooms(): Uint8Array { return this.roomData }
  get canUndo(): boolean { return this.past.length > 0 }
  get canRedo(): boolean { return this.future.length > 0 }

  roomAt(point: Point): number {
    if (point.x < 0 || point.y < 0 || point.x >= this.width || point.y >= this.height) return 0
    return this.roomData[point.y * this.width + point.x] ?? 0
  }

  fill(rect: CellRect, value: Fill) {
    for (let y = Math.max(0, rect.top); y <= Math.min(this.height - 1, rect.bottom); y++) {
      for (let x = Math.max(0, rect.left); x <= Math.min(this.width - 1, rect.right); x++) {
        this.paint(y * this.width + x, value)
      }
    }
  }

  fillRoom(room: number, value: Fill) {
    if (!Number.isInteger(room) || room < 1 || room > 63) return
    // Membership, not connectivity, includes disconnected parts of the same room.
    for (let index = 0; index < this.roomData.length; index++) {
      if (this.roomData[index] === room) this.paint(index, value)
    }
  }

  line(from: Point, to: Point, value: CellValue) {
    const clipped = clipLine(from, to, this.width, this.height)
    if (!clipped) return
    let { x, y } = clipped[0]
    const { x: endX, y: endY } = clipped[1]
    const dx = Math.abs(endX - x)
    const dy = -Math.abs(endY - y)
    const sx = x < endX ? 1 : -1
    const sy = y < endY ? 1 : -1
    let error = dx + dy

    // Interpolate pointer samples so fast strokes leave no gaps.
    while (true) {
      this.setCell(x, y, value)
      if (x === endX && y === endY) return
      const step = 2 * error
      if (step >= dy) { error += dy; x += sx }
      if (step <= dx) { error += dx; y += sy }
    }
  }

  commit(): boolean {
    const changes = [...this.stroke.values()].filter(change => change.before !== change.after)
    this.stroke.clear()
    if (!changes.length) return false

    this.past.push(changes)
    if (this.past.length > 50) this.past.shift()
    this.future = []
    return true
  }

  cancel() {
    this.restore([...this.stroke.values()], 'before')
    this.stroke.clear()
  }

  undo(): boolean {
    const changes = this.past.pop()
    if (!changes) return false
    this.restore(changes, 'before')
    this.future.push(changes)
    return true
  }

  redo(): boolean {
    const changes = this.future.pop()
    if (!changes) return false
    this.restore(changes, 'after')
    this.past.push(changes)
    return true
  }

  private paint(index: number, value: Fill) {
    if (typeof value === 'number') {
      this.setValue(index, value, 'cells')
      return
    }

    // Room assignment changes segmentation only, never walls or unknown cells.
    if (this.data[index]! >= Cell.Unknown || !Number.isInteger(value.room) || value.room < 1 || value.room > 63) return
    this.setValue(index, value.room, 'rooms')
  }

  private setCell(x: number, y: number, value: CellValue) {
    this.setValue(y * this.width + x, value, 'cells')
  }

  private setValue(index: number, value: number, layer: Layer) {
    const data = layer === 'cells' ? this.data : this.roomData
    const before = data[index]!
    if (before === value) return
    const key = index + (layer === 'rooms' ? this.data.length : 0)
    const change = this.stroke.get(key) ?? { layer, index, before, after: value }
    change.after = value
    this.stroke.set(key, change)
    data[index] = value
  }

  private restore(changes: Change[], side: 'before' | 'after') {
    for (const change of changes) {
      const data = change.layer === 'cells' ? this.data : this.roomData
      data[change.index] = change[side]
    }
  }
}
