import assert from 'node:assert/strict'
import { test } from 'node:test'
import { Cell, CellEditor, cellRect } from '../src/lib/editor.ts'

for (const value of [Cell.Floor, Cell.Wall, Cell.Unknown]) {
  test(`rectangle fill ${value} preserves other cells, rooms, and originals`, () => {
    const cells = Uint8Array.from([0, 32, 64, 96, 128, 160, 192, 255, 7])
    const rooms = Uint8Array.from([1, 1, 2, 1, 1, 2, 3, 3, 2])
    const editor = new CellEditor(3, 3, cells, rooms)
    editor.fill(cellRect({ x: 2, y: 1 }, { x: 1, y: 0 }, 3, 3), value)
    assert.equal(editor.commit(), true)
    assert.deepEqual([...editor.cells], [0, value, value, 96, value, value, 192, 255, 7])
    assert.deepEqual(editor.rooms, rooms)
    assert.deepEqual([...cells], [0, 32, 64, 96, 128, 160, 192, 255, 7])
    editor.undo()
    assert.deepEqual(editor.cells, cells)
    assert.equal(editor.canUndo, false)
    editor.redo()
    assert.equal(editor.cells[1], value)
  })
}

test('rectangle room assignment changes only floor labels', () => {
  const cells = Uint8Array.of(0, 32, 127, 128, 255, 200)
  const rooms = Uint8Array.of(0, 1, 1, 1, 2, 0)
  const editor = new CellEditor(3, 2, cells, rooms)
  editor.fill({ left: -5, top: -5, right: 10, bottom: 10 }, { room: 2 })
  assert.equal(editor.commit(), true)
  assert.deepEqual(editor.cells, cells)
  assert.deepEqual([...editor.rooms], [2, 2, 2, 1, 2, 0])
  assert.deepEqual([...rooms], [0, 1, 1, 1, 2, 0])
  editor.undo()
  assert.deepEqual(editor.rooms, rooms)
  editor.redo()
  assert.deepEqual([...editor.rooms], [2, 2, 2, 1, 2, 0])
})

test('rectangle room assignment accepts IDs absent from the source map', () => {
  const editor = new CellEditor(2, 1, Uint8Array.of(32, 64))
  const rect = { left: 0, top: 0, right: 1, bottom: 0 }
  for (const room of [1, 17, 63]) {
    editor.fill(rect, { room })
    assert.equal(editor.commit(), true)
    assert.deepEqual([...editor.rooms], [room, room])
    editor.undo()
    assert.deepEqual([...editor.rooms], [0, 0])
  }
})

test('invalid, empty, and cancelled fills preserve redo', () => {
  const editor = new CellEditor(2, 1, Uint8Array.of(32, 64), Uint8Array.of(1, 2))
  const rect = { left: 0, top: 0, right: 1, bottom: 0 }
  editor.fill(rect, Cell.Wall)
  editor.commit()
  editor.undo()
  for (const room of [0, -1, 64, 1.5, NaN]) {
    editor.fill(rect, { room })
    assert.equal(editor.commit(), false)
  }
  editor.fill({ left: 3, top: 0, right: 4, bottom: 0 }, Cell.Unknown)
  assert.equal(editor.commit(), false)
  editor.fill(rect, { room: 2 })
  editor.cancel()
  assert.deepEqual([...editor.cells], [32, 64])
  assert.deepEqual([...editor.rooms], [1, 2])
  assert.equal(editor.canRedo, true)
})

test('one history entry restores both occupancy and room changes at the same index', () => {
  const editor = new CellEditor(1, 1, Uint8Array.of(32), Uint8Array.of(1))
  const rect = { left: 0, top: 0, right: 0, bottom: 0 }
  editor.fill(rect, Cell.Floor)
  editor.fill(rect, { room: 2 })
  editor.commit()
  editor.undo()
  assert.deepEqual([...editor.cells], [32])
  assert.deepEqual([...editor.rooms], [1])
  assert.equal(editor.canUndo, false)
  editor.redo()
  assert.deepEqual([...editor.cells], [0])
  assert.deepEqual([...editor.rooms], [2])
})
