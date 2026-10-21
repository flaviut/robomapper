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

test('fit excludes unknown padding without changing cell coordinates', () => {
  const cells = new Uint8Array(30).fill(128)
  cells[1 * 6 + 2] = 255
  cells[3 * 6 + 3] = 0
  const view = fitView(200, 120, { width: 6, height: 5, cells })
  assert.equal(view.scale, 36)
  assert.equal(view.x, -8)
  assert.equal(view.y, -30)
  cells.fill(128)
  assert.deepEqual(fitView(200, 120, { width: 6, height: 5, cells }), fitView(200, 120, { width: 6, height: 5 }))
})

test('unknown padding is transparent without hiding measured cells', () => {
  const image = mapImage(map)
  assert.equal(image[7], 0)
  assert.equal(image[3], 255)
  assert.equal(image[11], 255)
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
  assert.deepEqual([...image.subarray(4, 8)], [0, 0, 0, 0])
  assert.deepEqual([...image.subarray(8, 12)], [108, 108, 108, 255])
  assert.deepEqual([...image.subarray(16, 20)], [192, 192, 192, 255])
  assert.notDeepEqual(roomColor(16), roomColor(17))
})

test('room tint preserves scan contrast within a room', () => {
  const cells = Uint8Array.of(0, 32, 64, 96, 127)
  const image = mapImage({ ...map, width: cells.length, height: 1, cells, rooms: new Uint8Array(cells.length).fill(16) })
  for (let i = 1; i < cells.length; i++) {
    for (let channel = 0; channel < 3; channel++) {
      const contrast = image[(i - 1) * 4 + channel]! - image[i * 4 + channel]!
      assert.ok(contrast >= (cells[i]! - cells[i - 1]!) * 0.25)
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
