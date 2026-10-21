import assert from 'node:assert/strict'
import { test } from 'node:test'
import { loadSession, saveSession, saveView, saveDraft } from '../src/lib/session.ts'

function memoryStore() {
  const records = new Map()
  const db = {
    close() {},
    transaction() {
      const transaction = {
        objectStore: () => ({
          get: key => ({ result: structuredClone(records.get(key)) }),
          put: (value, key) => records.set(key, structuredClone(value)),
          delete: key => records.delete(key),
        }),
      }
      queueMicrotask(() => transaction.oncomplete())
      return transaction
    },
  }
  return {
    open() {
      const request = { result: db }
      queueMicrotask(() => request.onsuccess())
      return request
    },
  }
}

test('restore the cached map and only its own viewport', async () => {
  const original = globalThis.indexedDB
  globalThis.indexedDB = memoryStore()
  try {
    assert.equal(await loadSession(), null)
    const session = {
      id: 'first', source: 'robot.local',
      map: { width: 2, height: 1, cells: Uint8Array.of(0, 255), rooms: Uint8Array.of(16, 0) },
    }
    await saveSession(session)

    // Reactive proxies cannot be cloned by IndexedDB; persist plain coordinates.
    const view = new Proxy({ x: 40, y: -10, scale: 3 }, {})
    await saveView(session.id, view)
    assert.deepEqual(await loadSession(), { ...session, view: { x: 40, y: -10, scale: 3 } })

    const cells = Uint8Array.of(128, 255)
    const saving = saveDraft(session.id, cells)
    cells[0] = 255
    await saving
    const edited = await loadSession()
    assert.deepEqual(edited.draft, Uint8Array.of(128, 255))
    assert.deepEqual(edited.map.cells, session.map.cells)
    assert.deepEqual(edited.view, { x: 40, y: -10, scale: 3 })

    const next = { ...session, id: 'second', source: 'other.local' }
    await saveSession(next)
    assert.deepEqual(await loadSession(), { ...next, view: undefined })
    await saveView(session.id, view)
    await saveDraft(session.id, Uint8Array.of(255, 255))
    assert.deepEqual(await loadSession(), { ...next, view: undefined })
  } finally {
    if (original === undefined) delete globalThis.indexedDB
    else globalThis.indexedDB = original
  }
})
