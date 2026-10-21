import type { RobotMap } from './maps.ts'
import type { View } from './view.ts'

export interface MapSession {
  id: string
  source: string
  map: RobotMap
  view?: View
  draft?: Uint8Array
}

function openStore(): Promise<IDBDatabase> {
  return new Promise((resolve, reject) => {
    const request = indexedDB.open('map-editor', 1)
    request.onupgradeneeded = () => request.result.createObjectStore('session')
    request.onsuccess = () => resolve(request.result)
    request.onerror = () => reject(request.error)
  })
}

function complete(transaction: IDBTransaction): Promise<void> {
  return new Promise((resolve, reject) => {
    transaction.oncomplete = () => resolve()
    transaction.onerror = () => reject(transaction.error)
    transaction.onabort = () => reject(transaction.error)
  })
}

export async function loadSession(): Promise<MapSession | null> {
  const db = await openStore()
  try {
    const transaction = db.transaction('session', 'readonly')
    const store = transaction.objectStore('session')
    const session = store.get('map')
    const viewport = store.get('view')
    const draft = store.get('draft')
    await complete(transaction)
    const saved = session.result as MapSession | undefined
    if (!saved) return null

    const position = viewport.result as { id: string, view: View } | undefined
    const view = position?.id === saved.id ? position.view : undefined
    const edited = draft.result as { id: string, cells: Uint8Array } | undefined
    const cells = edited?.id === saved.id && edited.cells.length === saved.map.cells.length
      ? edited.cells : undefined
    return { ...saved, view, ...(cells ? { draft: cells } : {}) }
  } finally {
    db.close()
  }
}

export async function saveSession(session: MapSession): Promise<void> {
  const db = await openStore()
  try {
    const transaction = db.transaction('session', 'readwrite')
    const store = transaction.objectStore('session')
    store.put(session, 'map')
    store.delete('view')
    store.delete('draft')
    await complete(transaction)
  } finally {
    db.close()
  }
}

export async function saveDraft(id: string, cells: Uint8Array): Promise<void> {
  const snapshot = cells.slice()
  const db = await openStore()
  try {
    const transaction = db.transaction('session', 'readwrite')
    transaction.objectStore('session').put({ id, cells: snapshot }, 'draft')
    await complete(transaction)
  } finally {
    db.close()
  }
}

export async function saveView(id: string, view: View): Promise<void> {
  const db = await openStore()
  try {
    const transaction = db.transaction('session', 'readwrite')
    // Store the small viewport separately; dragging must not rewrite the raster.
    const position = { x: view.x, y: view.y, scale: view.scale }
    transaction.objectStore('session').put({ id, view: position }, 'view')
    await complete(transaction)
  } finally {
    db.close()
  }
}
