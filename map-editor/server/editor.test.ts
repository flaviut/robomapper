import assert from 'node:assert/strict'
import { test } from 'node:test'
import { Cell, CellEditor, cellRect } from '../src/lib/editor.ts'

test('erase only selected cells and preserve the source raster', () => {
  const original = Uint8Array.from([0, 32, 64, 96, 128, 160, 192, 255, 7])
  const editor = new CellEditor(3, 3, original)
  const selection = cellRect({ x: 2, y: 1 }, { x: 1, y: 0 }, 3, 3)
  editor.fill(selection, Cell.Unknown)
  assert.equal(editor.commit(), true)
  assert.deepEqual([...editor.cells], [0, 128, 128, 96, 128, 128, 192, 255, 7])
  assert.deepEqual([...original], [0, 32, 64, 96, 128, 160, 192, 255, 7])
  editor.undo()
  assert.deepEqual(editor.cells, original)
  editor.redo()
  assert.equal(editor.cells[1], Cell.Unknown)
})

test('continuous wall strokes form one reversible edit', () => {
  const original = new Uint8Array(25).fill(Cell.Unknown)
  const editor = new CellEditor(5, 5, original)
  editor.line({ x: 0, y: 0 }, { x: 4, y: 4 }, Cell.Wall)
  editor.line({ x: 4, y: 4 }, { x: 0, y: 4 }, Cell.Wall)
  editor.line({ x: 0, y: 4 }, { x: 4, y: 4 }, Cell.Wall)
  editor.commit()
  for (let i = 0; i < 5; i++) {
    assert.equal(editor.cells[i * 5 + i], Cell.Wall)
    assert.equal(editor.cells[20 + i], Cell.Wall)
  }
  assert.equal(editor.cells[1], Cell.Unknown)
  assert.equal(editor.undo(), true)
  assert.deepEqual(editor.cells, original)
  assert.equal(editor.canUndo, false)
  assert.equal(editor.redo(), true)
  assert.equal(editor.cells[24], Cell.Wall)
})

test('clip strokes without painting along an outside edge', () => {
  const editor = new CellEditor(5, 5, new Uint8Array(25).fill(Cell.Unknown))
  editor.line({ x: -3, y: -2 }, { x: 7, y: -2 }, Cell.Wall)
  assert.equal(editor.commit(), false)
  editor.line({ x: -3, y: 2 }, { x: 7, y: 2 }, Cell.Wall)
  assert.equal(editor.commit(), true)
  assert.deepEqual([...editor.cells.subarray(10, 15)], [255, 255, 255, 255, 255])
  assert.equal(editor.cells[0], Cell.Unknown)
  assert.deepEqual(cellRect({ x: 3, y: 3 }, { x: -10, y: 20 }, 5, 5), {
    left: 0, top: 3, right: 3, bottom: 4,
  })
})

test('cancel and no-op edits preserve redo history', () => {
  const editor = new CellEditor(2, 1, Uint8Array.of(32, 64))
  editor.line({ x: 0, y: 0 }, { x: 1, y: 0 }, Cell.Wall)
  editor.commit()
  editor.undo()
  editor.line({ x: 0, y: 0 }, { x: 1, y: 0 }, Cell.Unknown)
  editor.cancel()
  assert.deepEqual([...editor.cells], [32, 64])
  assert.equal(editor.commit(), false)
  assert.equal(editor.canRedo, true)
  editor.redo()
  editor.undo()
  editor.line({ x: 1, y: 0 }, { x: 1, y: 0 }, Cell.Unknown)
  editor.commit()
  assert.equal(editor.canRedo, false)
})

test('cancel preserves the original value when a stroke revisits cells', () => {
  const editor = new CellEditor(1, 1, Uint8Array.of(42))
  editor.line({ x: 0, y: 0 }, { x: 0, y: 0 }, Cell.Wall)
  editor.line({ x: 0, y: 0 }, { x: 0, y: 0 }, Cell.Unknown)
  editor.cancel()
  assert.equal(editor.cells[0], 42)
})
