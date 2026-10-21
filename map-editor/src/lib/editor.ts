export const Cell = { Unknown: 128, Wall: 255 } as const
export type CellValue = typeof Cell[keyof typeof Cell]

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
  private width: number
  private height: number
  private past: Change[][] = []
  private future: Change[][] = []
  private stroke = new Map<number, Change>()

  constructor(width: number, height: number, cells: Uint8Array) {
    if (!Number.isInteger(width) || !Number.isInteger(height) || width <= 0 || height <= 0
      || cells.length !== width * height) throw new Error('Invalid map dimensions.')
    this.width = width
    this.height = height
    this.data = cells.slice()
  }

  get cells(): Uint8Array { return this.data }
  get canUndo(): boolean { return this.past.length > 0 }
  get canRedo(): boolean { return this.future.length > 0 }

  fill(rect: CellRect, value: CellValue) {
    for (let y = Math.max(0, rect.top); y <= Math.min(this.height - 1, rect.bottom); y++) {
      for (let x = Math.max(0, rect.left); x <= Math.min(this.width - 1, rect.right); x++) {
        this.setCell(x, y, value)
      }
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

  private setCell(x: number, y: number, value: CellValue) {
    const index = y * this.width + x
    const before = this.data[index]!
    if (before === value) return
    const change = this.stroke.get(index) ?? { index, before, after: value }
    change.after = value
    this.stroke.set(index, change)
    this.data[index] = value
  }

  private restore(changes: Change[], side: 'before' | 'after') {
    for (const change of changes) this.data[change.index] = change[side]
  }
}
