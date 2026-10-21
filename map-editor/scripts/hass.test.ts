import assert from 'node:assert/strict'
import { spawnSync } from 'node:child_process'
import { readFile } from 'node:fs/promises'
import { createServer } from 'node:http'
import { test } from 'node:test'
import { chromium, type Browser } from 'playwright'

const assets = new URL('../../custom_components/map_editor/frontend/', import.meta.url)

// Serve the release bundle, not Vite's development backend.
test('HA panel loads, links a vacuum and resumes a save after reload', async () => {
  let stage = 'idle'
  let linked = true
  const calls: { action: string, entry_id?: string, data?: { confirmation?: string } }[] = []
  const cells = Buffer.alloc(64, 32).toString('base64')
  const rooms = Buffer.alloc(64, 1).toString('base64')
  const map = { width: 8, height: 8, left: 0, top: 0, scale: 20, checksum: 'fixture', cells, rooms,
    native: { raster: 'raster', persistence: 'persistence' } }
  const server = createServer(async (req, res) => {
    if (req.url === '/rpc') {
      const chunks = []
      for await (const chunk of req) chunks.push(chunk)
      const input = JSON.parse(Buffer.concat(chunks).toString()) as typeof calls[number]
      calls.push(input)
      let result: unknown
      if (input.action === 'entries') result = [{ id: 'robot-entry', name: 'robot.local', ...(linked ? { vacuum_entity: 'vacuum.robot' } : {}) }]
      else if (input.action === 'load') result = map
      else {
        if (input.action === 'save') stage = 'saving'
        result = { state: stage, stage: stage === 'saving' ? 'Store stopped backup' : 'Saved and verified' }
      }
      res.writeHead(200, { 'Content-Type': 'application/json' }).end(JSON.stringify(result))
      return
    }
    const name = req.url?.split('?')[0]?.split('/').pop()
    if (name === 'panel.js' || name === 'panel.css') {
      res.writeHead(200, { 'Content-Type': name.endsWith('.js') ? 'text/javascript' : 'text/css' })
      res.end(await readFile(new URL(name, assets)))
      return
    }
    res.writeHead(200, { 'Content-Type': 'text/html' }).end(`<!doctype html><html><body style="margin:0">
      <script type="module">
        import '/map_editor_static/panel.js';
        const panel = document.createElement('s7-map-editor');
        panel.hass = { callWS: async message => (await fetch('/rpc', {
          method: 'POST', body: JSON.stringify(message),
        })).json() };
        panel.addEventListener('hass-more-info', event => { document.body.dataset.entity = event.detail.entityId; });
        document.body.append(panel);
      </script></body></html>`)
  })
  let browser: Browser | undefined
  try {
    await new Promise<void>(resolve => server.listen(0, '127.0.0.1', resolve))
    const address = server.address() as { port: number }
    const executable = spawnSync('sh', ['-c', 'command -v chromium || command -v chromium-browser'], { encoding: 'utf8' })
    browser = await chromium.launch({
      executablePath: process.env.CHROMIUM_PATH ?? (executable.status === 0 ? executable.stdout.trim() : undefined),
      headless: true,
    })
    const page = await browser.newPage({ viewport: { width: 1200, height: 900 } })
    const errors: string[] = []
    page.on('pageerror', error => errors.push(error.message))
    await page.goto(`http://127.0.0.1:${address.port}/`)
    await page.getByLabel('Robot', { exact: true }).waitFor()
    assert.equal(await page.getByLabel('Robot hostname').count(), 0)
    await page.getByRole('button', { name: 'Load map', exact: true }).click()
    await page.locator('canvas').waitFor({ state: 'visible' })
    const background = await page.locator('header').evaluate(node => getComputedStyle(node).backgroundColor)
    assert.notEqual(background, 'rgba(0, 0, 0, 0)')
    await page.screenshot({ path: new URL('../artifacts/hass-panel.png', import.meta.url).pathname })
    await page.getByRole('button', { name: 'Open vacuum', exact: true }).click()
    assert.equal(await page.locator('body').getAttribute('data-entity'), 'vacuum.robot')
    assert.ok(await page.locator('canvas').evaluate(node => node.getBoundingClientRect().width > 0))
    await page.getByRole('button', { name: 'Save', exact: true }).click()
    await page.getByRole('button', { name: 'Save and restart', exact: true }).click()
    await page.getByRole('status').filter({ hasText: 'Store stopped backup' }).waitFor()
    assert.equal(calls.filter(call => call.action === 'save').length, 1)
    assert.equal(calls.find(call => call.action === 'save')?.data?.confirmation, 'install-and-reboot')
    await page.reload()
    await page.getByRole('status').filter({ hasText: 'Store stopped backup' }).waitFor()
    assert.equal(await page.getByRole('button', { name: 'Saving…', exact: true }).isDisabled(), true)
    stage = 'done'
    await page.getByRole('status').filter({ hasText: 'Saved. Robot restarted.' }).waitFor()
    assert.equal(calls.filter(call => call.action === 'save').length, 1)
    assert.ok(calls.every(call => call.action === 'entries' || call.entry_id === 'robot-entry'))
    assert.deepEqual(errors, [])
    await page.close()

    linked = false
    const unlinked = await browser.newPage()
    await unlinked.goto(`http://127.0.0.1:${address.port}/`)
    await unlinked.getByLabel('Robot', { exact: true }).waitFor()
    assert.equal(await unlinked.getByRole('button', { name: 'Open vacuum', exact: true }).count(), 0)
    await unlinked.getByRole('button', { name: 'Load map', exact: true }).click()
    await unlinked.locator('canvas').waitFor({ state: 'visible' })
  } finally {
    await browser?.close()
    await new Promise<void>((resolve, reject) => server.close(error => error ? reject(error) : resolve()))
  }
})
