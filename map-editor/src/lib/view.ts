import type { RobotMap } from './maps.ts'

export interface View {
  x: number
  y: number
  scale: number
}

export function fitView(width: number, height: number, map: { width: number, height: number }): View {
  const scale = Math.max(0.01, Math.min(width / map.width, height / map.height) * 0.9)
  return { x: (width - map.width * scale) / 2, y: (height - map.height * scale) / 2, scale }
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

export function mapImage(map: RobotMap): Uint8ClampedArray<ArrayBuffer> {
  const image = new Uint8ClampedArray(map.cells.length * 4)
  const colors = Array.from({ length: 64 }, (_, id) => roomColor(id))
  for (let i = 0; i < map.cells.length; i++) {
    const cell = map.cells[i]!
    const shade = Math.round(192 - cell * (168 / 255))
    const room = map.rooms[i]!
    const tint = room && cell < 128 ? colors[room] : undefined

    // Muted floors and charcoal obstacles avoid black/white glare while retaining scan detail.
    for (let channel = 0; channel < 3; channel++) {
      image[i * 4 + channel] = tint ? Math.round(shade * 0.8 + tint[channel]! * 0.2) : shade
    }
    image[i * 4 + 3] = 255
  }
  return image
}

export function roomLabels(map: RobotMap) {
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
