import assert from 'node:assert/strict'
import { spawnSync } from 'node:child_process'
import { test } from 'node:test'
import { fileURLToPath } from 'node:url'
import { chromium, type Browser } from 'playwright'
import { createServer } from 'vite'
import { Cell, type Fill } from '../src/lib/editor.ts'
import { mapImage } from '../src/lib/view.ts'

const root = fileURLToPath(new URL('..', import.meta.url))

test('rectangle palette fills preview, undo, and persist both layers', async () => {
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
    for (const name of ['Select', 'Delete', 'Erase', 'Line', 'Room fill']) {
      assert.equal(await page.getByRole('button', { name, exact: true }).count(), 0)
    }
    const palette = page.getByRole('complementary', { name: 'Rectangle fills' })
    assert.equal(await palette.count(), 0)
    await page.getByRole('button', { name: 'Rectangle', exact: true }).click()
    await palette.waitFor({ state: 'visible' })
    await page.getByRole('button', { name: 'Fit', exact: true }).click()
    await page.evaluate(() => new Promise(requestAnimationFrame))
    const sidebar = (await palette.boundingBox())!
    const viewport = (await page.getByRole('application').boundingBox())!
    assert.equal(sidebar.x, 0)
    assert.ok(sidebar.x + sidebar.width <= viewport.x)
    let previous = -1
    for (const name of ['Floor', 'Wall', 'Unknown', 'Room ID']) {
      const bounds = (await palette.getByRole('radio', { name, exact: true }).boundingBox())!
      assert.ok(bounds.y > previous)
      previous = bounds.y
    }
    assert.equal(await palette.getByRole('spinbutton', { name: 'Room number' }).isDisabled(), true)
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
      await palette.getByRole('radio', { name, exact: true }).check()
      await move(6, 3)
      await page.mouse.down()
      await move(3, 1)
      await page.mouse.up()
      await check(rectangle(3, 1, 6, 3, value).cells)
      await undo()
    }

    await palette.getByRole('radio', { name: 'Room ID', exact: true }).check()
    const input = palette.getByRole('spinbutton', { name: 'Room number' })
    for (const invalid of ['', '0', '64', '1.5']) {
      await input.fill(invalid)
      await move(2, 2)
      await page.mouse.down()
      await move(4, 4)
      await page.mouse.up()
      await check()
      assert.equal(await page.getByRole('button', { name: 'Undo', exact: true }).isEnabled(), false)
    }
    await input.fill('17')
    await move(0, 0)
    await page.mouse.down()
    await move(7, 7)
    const roomLabels = rectangle(0, 0, 7, 7, { room: 17 }).rooms
    await check(cells, roomLabels)
    await page.keyboard.press('Escape')
    await page.mouse.up()
    await check()
    await move(7, 7)
    await page.mouse.down()
    await move(0, 0)
    await page.mouse.up()
    await check(cells, roomLabels)
    await undo()
    await page.getByRole('button', { name: 'Redo', exact: true }).click()
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
    assert.equal(await page.getByText('Room 17', { exact: true }).count(), 1)
    assert.equal(await palette.count(), 0)
    assert.deepEqual(errors, [])

    const empty = await browser.newPage()
    await empty.route('**/api/map', route => route.fulfill({
      contentType: 'application/json', body: JSON.stringify({ ...fixture, rooms: Buffer.alloc(64).toString('base64') }),
    }))
    await empty.goto(url)
    await empty.getByLabel('Robot hostname').fill('no-rooms')
    await empty.getByRole('button', { name: 'Load map', exact: true }).click()
    await empty.locator('canvas').waitFor({ state: 'visible' })
    await empty.getByRole('button', { name: 'Rectangle', exact: true }).click()
    await empty.getByRole('radio', { name: 'Room ID', exact: true }).check()
    await empty.getByRole('spinbutton', { name: 'Room number' }).fill('63')
    const before = (await empty.locator('canvas').boundingBox())!
    await empty.getByRole('spinbutton', { name: 'Room number' }).press('ArrowLeft')
    assert.deepEqual(await empty.locator('canvas').boundingBox(), before)
    await empty.mouse.move(before.x + 2.5 * before.width / 8, before.y + 2.5 * before.height / 8)
    await empty.mouse.down()
    await empty.mouse.move(before.x + 3.5 * before.width / 8, before.y + 3.5 * before.height / 8)
    await empty.mouse.up()
    assert.equal(await empty.getByText('Room 63', { exact: true }).count(), 1)
    await empty.getByRole('button', { name: 'Pan', exact: true }).click()
    assert.equal(await empty.getByRole('complementary', { name: 'Rectangle fills' }).count(), 0)
  } finally {
    await browser?.close()
    await server.close()
  }
})
