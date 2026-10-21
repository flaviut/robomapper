import { mkdir, readFile } from 'node:fs/promises'
import { dirname, resolve } from 'node:path'
import { spawnSync } from 'node:child_process'
import { fileURLToPath } from 'node:url'
import { parseArgs } from 'node:util'
import { chromium, type Browser } from 'playwright'
import { createServer } from 'vite'
import { inspectMap } from '../server/map.ts'
import { inspectRooms } from '../server/rooms.ts'

const root = fileURLToPath(new URL('..', import.meta.url))

function browserPath(): string | undefined {
  if (process.env.CHROMIUM_PATH) return process.env.CHROMIUM_PATH
  const result = spawnSync('sh', ['-c', 'command -v chromium || command -v chromium-browser'], { encoding: 'utf8' })
  return result.status === 0 ? result.stdout.trim() : undefined
}

async function main() {
  const { values } = parseArgs({ options: {
    map: { type: 'string' }, rooms: { type: 'string' }, hostname: { type: 'string' },
    output: { type: 'string' }, tool: { type: 'string' }, help: { type: 'boolean' },
  } })
  if (values.help) {
    console.log(`Usage:
  pnpm screenshot --map FILE [--rooms FILE] [--tool Line] [--output FILE]
  pnpm screenshot --hostname HOST [--tool Select] [--output FILE]

Captures a 1440 × 1000 desktop view. Starts and stops its own local server.
Local files never connect to a robot. --hostname explicitly loads over SSH.
Tools: Pan, Select, Erase, Line. Output: artifacts/map-editor.png.
Uses Chromium on PATH, or Playwright's installed browser.
Set CHROMIUM_PATH to choose another executable.`)
    return
  }
  if (Boolean(values.map) === Boolean(values.hostname)) throw new Error('Choose --map FILE or --hostname HOST.')
  if (values.rooms && !values.map) throw new Error('--rooms requires --map.')
  const tool = values.tool ?? 'Pan'
  if (!['Pan', 'Select', 'Erase', 'Line'].includes(tool)) throw new Error('Unknown tool. Choose Pan, Select, Erase, or Line.')

  let fixture: string | undefined
  if (values.map) {
    const map = inspectMap(await readFile(resolve(values.map)))
    const rooms = values.rooms
      ? inspectRooms(await readFile(resolve(values.rooms)), map)
      : Buffer.alloc(map.width * map.height).toString('base64')
    fixture = JSON.stringify({ ...map, rooms })
  }

  const server = await createServer({ root, server: { host: '127.0.0.1', port: 0, open: false } })
  let browser: Browser | undefined
  try {
    await server.listen()
    const url = server.resolvedUrls?.local[0]
    if (!url) throw new Error('Local server did not start.')
    browser = await chromium.launch({ executablePath: browserPath(), headless: true })
    const page = await browser.newPage({ viewport: { width: 1440, height: 1000 }, deviceScaleFactor: 1 })
    const errors: string[] = []
    page.on('pageerror', error => errors.push(error.message))
    if (fixture) {
      await page.route('**/api/map', route => route.fulfill({ contentType: 'application/json', body: fixture }))
    }
    await page.goto(url)
    await page.getByLabel('Robot hostname').fill(values.hostname ?? 'local-map')
    const loading = page.waitForResponse(response => response.url().endsWith('/api/map') && response.request().method() === 'POST')
    await page.getByRole('button', { name: 'Load map', exact: true }).click()
    const response = await loading
    if (!response.ok()) {
      const result = await response.json() as { error?: string }
      throw new Error(result.error ?? 'Map loading failed.')
    }
    await page.locator('canvas').waitFor({ state: 'visible' })
    await page.getByRole('button', { name: 'Fit', exact: true }).click()
    await page.getByRole('button', { name: tool, exact: true }).click()
    await page.mouse.move(0, 0)
    await page.evaluate(() => document.fonts.ready)
    if (errors.length) throw new Error(errors.join('\n'))
    const output = values.output ? resolve(values.output) : resolve(root, 'artifacts/map-editor.png')
    await mkdir(dirname(output), { recursive: true })
    await page.screenshot({ path: output, animations: 'disabled' })
    console.log(output)
  } finally {
    await browser?.close()
    await server.close()
  }
}

main().catch(error => {
  console.error(error instanceof Error ? error.message : error)
  process.exitCode = 1
})
