import assert from 'node:assert/strict'
import { test } from 'node:test'
import { fitView, zoomView, mapImage, roomLabels, roomColor } from '../src/lib/view.ts'

const map = {
  width: 3, height: 2, left: 0, top: 0, scale: 20, checksum: '',
  cells: Uint8Array.from([0, 128, 255, 0, 0, 0]),
  rooms: Uint8Array.from([16, 16, 16, 17, 0, 17]),
}

test('fit centers the map inside the viewport', () => {
  const view = fitView(600, 300, { width: 200, height: 200 })
  assert.equal(view.scale, 1.35)
  assert.equal(view.x, 165)
  assert.equal(view.y, 15)
})

test('zoom preserves the map point beneath the cursor', () => {
  const view = { x: 20, y: -10, scale: 2 }
  const next = zoomView(view, 2, 100, 50)
  assert.equal((100 - view.x) / view.scale, (100 - next.x) / next.scale)
  assert.equal((50 - view.y) / view.scale, (50 - next.y) / next.scale)
  assert.equal(zoomView(view, 10000, 0, 0).scale, 64)
  assert.equal(zoomView(view, 0.00001, 0, 0).scale, 0.01)
})

test('rooms have stable colors without hiding walls or unknown cells', () => {
  const image = mapImage(map)
  assert.deepEqual([...image.subarray(0, 4)], [...roomColor(16).map(channel => Math.round(192 * 0.8 + channel * 0.2)), 255])
  assert.deepEqual([...image.subarray(4, 8)], [108, 108, 108, 255])
  assert.deepEqual([...image.subarray(8, 12)], [24, 24, 24, 255])
  assert.deepEqual([...image.subarray(16, 20)], [192, 192, 192, 255])
  assert.notDeepEqual(roomColor(16), roomColor(17))
})

test('room tint preserves scan contrast within a room', () => {
  const cells = Uint8Array.of(0, 32, 64, 96, 127)
  const image = mapImage({ ...map, width: cells.length, height: 1, cells, rooms: new Uint8Array(cells.length).fill(16) })
  for (let i = 1; i < cells.length; i++) {
    for (let channel = 0; channel < 3; channel++) {
      const contrast = image[(i - 1) * 4 + channel]! - image[i * 4 + channel]!
      assert.ok(contrast >= (cells[i]! - cells[i - 1]!) * 0.5)
    }
  }
})

test('labels stay on traversable cells belonging to their room', () => {
  const labels = roomLabels(map)
  assert.deepEqual(labels.map(label => label.id).sort(), [16, 17])
  for (const label of labels) {
    const index = Math.floor(label.y) * map.width + Math.floor(label.x)
    assert.equal(map.rooms[index], label.id)
    assert.ok(map.cells[index]! < 128)
  }
})
