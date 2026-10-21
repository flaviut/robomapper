import assert from 'node:assert/strict'
import { spawnSync } from 'node:child_process'
import { test } from 'node:test'
import { fileURLToPath } from 'node:url'
import { chromium, type Browser } from 'playwright'
import { createServer } from 'vite'
import { Cell, type Fill } from '../src/lib/editor.ts'
import { mapImage } from '../src/lib/view.ts'

const root = fileURLToPath(new URL('..', import.meta.url))

test('rectangle and whole-room fills preview, undo, and persist both layers', async () => {
  const server = await createServer({ root, server: { host: '127.0.0.1', port: 0, open: false } })
  let browser: Browser | undefined
  try {
    await server.listen()
    const path = spawnSync('sh', ['-c', 'command -v chromium || command -v chromium-browser'], { encoding: 'utf8' })
    browser = await chromium.launch({
      executablePath: process.env.CHROMIUM_PATH ?? (path.status === 0 ? path.stdout.trim() : undefined),
      headless: true,
    })
    const page = await browser.newPage({ viewport: { width: 1200, height: 900 } })
    const errors: string[] = []
    page.on('pageerror', error => errors.push(error.message))
    const cells = new Uint8Array(64)
    cells[12] = Cell.Wall
    cells[13] = Cell.Unknown
    const rooms = Uint8Array.from({ length: 64 }, (_, index) => index % 8 < 4 ? 1 : 2)
    rooms[0] = 0
    rooms[63] = 1
    const map = { width: 8, height: 8, left: 0, top: 0, scale: 1, checksum: 'fixture', cells, rooms }
    const fixture = { ...map, cells: Buffer.from(cells).toString('base64'), rooms: Buffer.from(rooms).toString('base64') }
    await page.route('**/api/map', route => route.fulfill({
      contentType: 'application/json', body: JSON.stringify(fixture),
    }))
    const url = server.resolvedUrls!.local[0]!
    await page.goto(url)
    await page.getByLabel('Robot hostname').fill('local-map')
    await page.getByRole('button', { name: 'Load map', exact: true }).click()
    const canvas = page.locator('canvas')
    await canvas.waitFor({ state: 'visible' })
    for (const name of ['Select', 'Delete', 'Erase', 'Line']) {
      assert.equal(await page.getByRole('button', { name, exact: true }).count(), 0)
    }
    await page.getByRole('button', { name: 'Rectangle', exact: true }).click()
    await page.getByRole('button', { name: 'Fit', exact: true }).click()
    await page.evaluate(() => new Promise(requestAnimationFrame))
    const move = async (x: number, y: number) => {
      const bounds = (await canvas.boundingBox())!
      await page.mouse.move(bounds.x + (x + 0.5) * bounds.width / 8, bounds.y + (y + 0.5) * bounds.height / 8)
    }
    const check = async (nextCells = cells, nextRooms = rooms) => {
      await page.evaluate(() => new Promise(requestAnimationFrame))
      const raster = await canvas.evaluate(node => Array.from(
        (node as HTMLCanvasElement).getContext('2d')!.getImageData(0, 0, 8, 8).data,
      ))
      assert.deepEqual(raster, [...mapImage({ ...map, cells: nextCells, rooms: nextRooms })])
    }
    const rectangle = (left: number, top: number, right: number, bottom: number, fill: Fill) => {
      const nextCells = cells.slice()
      const nextRooms = rooms.slice()
      for (let y = top; y <= bottom; y++) {
        for (let x = left; x <= right; x++) {
          const index = y * 8 + x
          if (typeof fill === 'number') nextCells[index] = fill
          else if (cells[index]! < Cell.Unknown) nextRooms[index] = fill.room
        }
      }
      return { cells: nextCells, rooms: nextRooms }
    }
    const undo = async () => {
      await page.getByRole('button', { name: 'Undo', exact: true }).click()
      await check()
      assert.equal(await page.getByRole('button', { name: 'Undo', exact: true }).isEnabled(), false)
    }

    await move(1, 1)
    await page.mouse.down()
    await move(6, 6)
    await check(rectangle(1, 1, 6, 6, Cell.Wall).cells)
    await move(1, 3)
    await check(rectangle(1, 1, 1, 3, Cell.Wall).cells)
    await page.mouse.up()
    const wall = rectangle(1, 1, 1, 3, Cell.Wall).cells
    await check(wall)
    await undo()
    await page.getByRole('button', { name: 'Redo', exact: true }).click()
    await check(wall)
    await undo()

    await move(2, 2)
    await page.mouse.down()
    await move(6, 6)
    await page.keyboard.press('Escape')
    await page.mouse.up()
    await check()
    assert.equal(await page.getByRole('button', { name: 'Redo', exact: true }).isEnabled(), true)

    for (const [name, value] of [['Floor', Cell.Floor], ['Unknown', Cell.Unknown]] as const) {
      await page.getByLabel('Fill type').selectOption(name)
      await move(6, 3)
      await page.mouse.down()
      await move(3, 1)
      await page.mouse.up()
      await check(rectangle(3, 1, 6, 3, value).cells)
      await undo()
    }

    await page.getByLabel('Fill type').selectOption('Room')
    await page.getByLabel('Target room').selectOption('2')
    await move(0, 0)
    await page.mouse.down()
    await move(7, 7)
    await page.mouse.up()
    await check(cells, rectangle(0, 0, 7, 7, { room: 2 }).rooms)
    await undo()

    await page.getByRole('button', { name: 'Room fill', exact: true }).click()
    await page.getByLabel('Fill type').selectOption('Unknown')
    await move(1, 1)
    await page.mouse.down()
    const roomCells = Uint8Array.from(cells, (value, index) => rooms[index] === 1 ? Cell.Unknown : value)
    await move(6, 6)
    await check(roomCells)
    await page.keyboard.press('Escape')
    await page.mouse.up()
    await check()
    await move(1, 1)
    await page.mouse.down()
    await page.mouse.up()
    await check(roomCells)
    await undo()

    await page.getByLabel('Fill type').selectOption('Room')
    await page.getByLabel('Target room').selectOption('2')
    await move(1, 1)
    await page.mouse.down()
    await page.mouse.up()
    const roomLabels = Uint8Array.from(rooms, (id, index) => id === 1 && cells[index]! < Cell.Unknown ? 2 : id)
    await check(cells, roomLabels)
    await page.waitForFunction(async expected => {
      const db = await new Promise<IDBDatabase>((resolve, reject) => {
        const request = indexedDB.open('map-editor', 1)
        request.onsuccess = () => resolve(request.result)
        request.onerror = () => reject(request.error)
      })
      try {
        const draft = await new Promise<{ rooms?: Uint8Array } | undefined>(resolve => {
          const request = db.transaction('session').objectStore('session').get('draft')
          request.onsuccess = () => resolve(request.result)
        })
        return JSON.stringify(Array.from(draft?.rooms ?? [])) === JSON.stringify(expected)
      } finally { db.close() }
    }, [...roomLabels])
    await page.reload()
    await canvas.waitFor({ state: 'visible' })
    await check(cells, roomLabels)
    assert.equal(await page.getByText('Room 1', { exact: true }).count(), 0)
    assert.equal(await page.getByText('Room 2', { exact: true }).count(), 1)
    assert.deepEqual(errors, [])

    const empty = await browser.newPage()
    await empty.route('**/api/map', route => route.fulfill({
      contentType: 'application/json', body: JSON.stringify({ ...fixture, rooms: Buffer.alloc(64).toString('base64') }),
    }))
    await empty.goto(url)
    await empty.getByLabel('Robot hostname').fill('no-rooms')
    await empty.getByRole('button', { name: 'Load map', exact: true }).click()
    assert.equal(await empty.getByRole('button', { name: 'Room fill', exact: true }).isDisabled(), true)
    await empty.getByRole('button', { name: 'Rectangle', exact: true }).click()
    const option = empty.getByRole('option', { name: 'Room', exact: true })
    assert.equal(await option.evaluate(node => (node as HTMLOptionElement).disabled), true)
  } finally {
    await browser?.close()
    await server.close()
  }
})
