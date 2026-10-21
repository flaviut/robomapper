import type { RobotMap } from './maps.ts'

type Raster = Pick<RobotMap, 'width' | 'height' | 'cells' | 'rooms'>

export interface View {
  x: number
  y: number
  scale: number
}

interface FitMap {
  width: number
  height: number
  cells?: Uint8Array
}

function mapBounds(map: FitMap) {
  const full = { x: 0, y: 0, width: map.width, height: map.height }
  if (!map.cells) return full
  let left = map.width
  let top = map.height
  let right = -1
  let bottom = -1
  for (let i = 0; i < map.cells.length; i++) {
    if (map.cells[i] === 128) continue
    const x = i % map.width
    const y = Math.floor(i / map.width)
    left = Math.min(left, x)
    top = Math.min(top, y)
    right = Math.max(right, x)
    bottom = Math.max(bottom, y)
  }
  if (right < 0) return full
  return { x: left, y: top, width: right - left + 1, height: bottom - top + 1 }
}

export function fitView(width: number, height: number, map: FitMap): View {
  const bounds = mapBounds(map)
  const scale = Math.max(0.01, Math.min(64, Math.min(width / bounds.width, height / bounds.height) * 0.9))
  return {
    x: (width - bounds.width * scale) / 2 - bounds.x * scale,
    y: (height - bounds.height * scale) / 2 - bounds.y * scale,
    scale,
  }
}

export function zoomView(view: View, factor: number, x: number, y: number): View {
  const scale = Math.max(0.01, Math.min(64, view.scale * factor))
  const ratio = scale / view.scale
  return { x: x - (x - view.x) * ratio, y: y - (y - view.y) * ratio, scale }
}

export function roomColor(id: number): [number, number, number] {
  const hue = (id * 0.61803398875) % 1
  return [0, 2 / 3, 1 / 3].map(offset => {
    const value = Math.abs(((hue + offset) % 1) * 6 - 3) - 1
    return Math.round(90 + Math.max(0, Math.min(1, value)) * 140)
  }) as [number, number, number]
}

export function mapImage(map: Raster): Uint8ClampedArray<ArrayBuffer> {
  const image = new Uint8ClampedArray(map.cells.length * 4)
  const colors = Array.from({ length: 64 }, (_, id) => roomColor(id))
  for (let i = 0; i < map.cells.length; i++) {
    const cell = map.cells[i]!
    if (cell === 128) continue
    const shade = Math.round(192 - cell * (84 / 255))
    const room = map.rooms[i]!
    const tint = room && cell < 128 ? colors[room] : undefined

    // Mid-gray walls contrast with both room fills and the dark background.
    for (let channel = 0; channel < 3; channel++) {
      image[i * 4 + channel] = tint ? Math.round(shade * 0.8 + tint[channel]! * 0.2) : shade
    }
    image[i * 4 + 3] = 255
  }
  return image
}

export function roomLabels(map: Raster) {
  const sums = new Map<number, { x: number, y: number, count: number }>()
  for (let i = 0; i < map.rooms.length; i++) {
    const id = map.rooms[i]!
    if (!id || map.cells[i]! >= 128) continue
    const sum = sums.get(id) ?? { x: 0, y: 0, count: 0 }
    sum.x += i % map.width + 0.5
    sum.y += Math.floor(i / map.width) + 0.5
    sum.count++
    sums.set(id, sum)
  }

  // Keep labels inside their rooms, including concave and disconnected shapes.
  const labels = new Map<number, { id: number, x: number, y: number, distance: number }>()
  for (let i = 0; i < map.rooms.length; i++) {
    const id = map.rooms[i]!
    const sum = sums.get(id)
    if (!sum || map.cells[i]! >= 128) continue
    const x = i % map.width + 0.5
    const y = Math.floor(i / map.width) + 0.5
    const distance = (x - sum.x / sum.count) ** 2 + (y - sum.y / sum.count) ** 2
    if (distance >= (labels.get(id)?.distance ?? Infinity)) continue
    labels.set(id, { id, x, y, distance })
  }
  return [...labels.values()]
}
