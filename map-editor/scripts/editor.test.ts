import assert from 'node:assert/strict'
import { spawnSync } from 'node:child_process'
import { test } from 'node:test'
import { fileURLToPath } from 'node:url'
import { chromium, type Browser } from 'playwright'
import { createServer } from 'vite'

const root = fileURLToPath(new URL('..', import.meta.url))

test('line drags replace previews and commit only the final segment', async () => {
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
    const cells = Buffer.alloc(64)
    cells[12] = 255
    await page.route('**/api/map', route => route.fulfill({
      contentType: 'application/json',
      body: JSON.stringify({
        width: 8, height: 8, left: 0, top: 0, scale: 1, checksum: 'fixture',
        cells: cells.toString('base64'), rooms: Buffer.alloc(64).toString('base64'),
      }),
    }))
    await page.goto(server.resolvedUrls!.local[0]!)
    await page.getByLabel('Robot hostname').fill('local-map')
    await page.getByRole('button', { name: 'Load map', exact: true }).click()
    const canvas = page.locator('canvas')
    await canvas.waitFor({ state: 'visible' })
    await page.getByRole('button', { name: 'Fit', exact: true }).click()
    await page.getByRole('button', { name: 'Line', exact: true }).click()
    const bounds = (await canvas.boundingBox())!
    const move = (x: number, y: number) => page.mouse.move(
      bounds.x + (x + 0.5) * bounds.width / 8,
      bounds.y + (y + 0.5) * bounds.height / 8,
    )
    const raster = () => canvas.evaluate(node => {
      const image = (node as HTMLCanvasElement).getContext('2d')!.getImageData(0, 0, 8, 8)
      return Array.from({ length: 64 }, (_, index) => image.data[index * 4])
    })
    const original = Array.from(cells, value => value === 255 ? 108 : 192)
    const expected = (...indices: number[]) => original.map((value, index) => indices.includes(index) ? 108 : value)
    const check = async (image: number[]) => {
      await page.evaluate(() => new Promise(requestAnimationFrame))
      assert.deepEqual(await raster(), image)
    }

    await move(1, 1)
    await page.mouse.down()
    await move(6, 1)
    await check(expected(9, 10, 11, 12, 13, 14))
    await move(6, 6)
    await check(expected(9, 18, 27, 36, 45, 54))
    await move(1, 6)
    await page.mouse.up()
    const line = expected(9, 17, 25, 33, 41, 49)
    await check(line)

    await page.getByRole('button', { name: 'Undo', exact: true }).click()
    await check(original)
    assert.equal(await page.getByRole('button', { name: 'Undo', exact: true }).isEnabled(), false)
    await page.getByRole('button', { name: 'Redo', exact: true }).click()
    await check(line)
    await page.getByRole('button', { name: 'Undo', exact: true }).click()

    await move(1, 1)
    await page.mouse.down()
    await move(6, 1)
    await page.keyboard.press('Escape')
    await page.mouse.up()
    await check(original)
    assert.equal(await page.getByRole('button', { name: 'Redo', exact: true }).isEnabled(), true)

    await move(2, 2)
    await page.mouse.down()
    await page.mouse.up()
    await check(expected(18))
    await page.getByRole('button', { name: 'Undo', exact: true }).click()
    await check(original)
    assert.deepEqual(errors, [])
  } finally {
    await browser?.close()
    await server.close()
  }
})
