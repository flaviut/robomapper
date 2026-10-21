import assert from 'node:assert/strict'
import { createHash } from 'node:crypto'
import { mkdtemp, writeFile, rm } from 'node:fs/promises'
import { tmpdir } from 'node:os'
import { join } from 'node:path'
import { test } from 'node:test'
import { createServer } from 'vite'
import { inspectMap } from './map.ts'
import { mapApi } from './api.ts'
import { readMap } from './ssh.ts'

function fixture() {
  const header = Buffer.alloc(30)
  header.write('RRSLAM')
  header.writeUInt16LE(2, 6)
  header.writeUInt16LE(20, 8)
  header.writeUInt32LE(20, 10)
  header.writeInt32LE(-40, 14)
  header.writeInt32LE(80, 18)
  header.writeUInt32LE(2, 22)
  header.writeUInt32LE(2, 26)
  const cells = Buffer.from([0, 127, 254, 255])
  return Buffer.concat([header, cells, createHash('md5').update(cells).digest()])
}

test('decode a verified fixed-frame raster', () => {
  const map = inspectMap(fixture())
  assert.equal(map.width, 2)
  assert.equal(map.height, 2)
  assert.equal(map.left, -40)
  assert.equal(map.top, 80)
  assert.equal(map.cells, 'AH/+/w==')
})

test('reject corrupt, unsupported, and truncated maps', () => {
  const corrupt = fixture()
  corrupt[30] = 1
  assert.throws(() => inspectMap(corrupt), /checksum/)
  assert.throws(() => inspectMap(fixture().subarray(0, 29)), /size/)
  assert.throws(() => inspectMap(fixture().subarray(0, -1)), /dimensions/)
  const unsupported = fixture()
  unsupported.writeUInt16LE(3, 6)
  assert.throws(() => inspectMap(unsupported), /header/)
  const dimensions = fixture()
  dimensions.writeUInt32LE(0, 22)
  assert.throws(() => inspectMap(dimensions), /dimensions/)
})

test('reject SSH argument and shell injection', () => {
  for (const host of ['-oProxyCommand=id', 'root@robot', 'robot;id', 'robot\nid', 'http://robot', '']) {
    assert.throws(() => readMap(host), /hostname/)
  }
})

test('local API loads through SSH and rejects foreign origins', async () => {
  const dir = await mkdtemp(join(tmpdir(), 'map-editor-'))
  const path = process.env.PATH
  const server = await createServer({
    configFile: false, plugins: [mapApi()],
    server: { host: '127.0.0.1', port: 0 },
  })

  try {
    // Replace only the transport; exercise the HTTP, service, and codec layers.
    await writeFile(join(dir, 'ssh'), `#!${process.execPath}
const args = process.argv.slice(2);
if (args.at(-2) !== 'root@robot.local' || !args.includes('StrictHostKeyChecking=yes')
  || args.at(-1) !== 'head -c 16777217 /mnt/data/rockrobo/last_map') process.exit(1);
process.stdout.write(Buffer.from('${fixture().toString('base64')}', 'base64'));
`, { mode: 0o700 })
    process.env.PATH = `${dir}:${path}`
    await server.listen()
    const address = server.httpServer!.address()
    assert.ok(address && typeof address !== 'string')
    const origin = `http://127.0.0.1:${address.port}`
    const request = (source: string) => fetch(`${origin}/api/map`, {
      method: 'POST', headers: { Origin: source, 'Content-Type': 'application/json' },
      body: JSON.stringify({ hostname: 'robot.local' }),
    })

    assert.equal((await request('http://foreign.example')).status, 403)
    const response = await request(origin)
    assert.equal(response.status, 200)
    assert.equal(response.headers.get('cache-control'), 'no-store')
    assert.deepEqual(await response.json(), inspectMap(fixture()))
  } finally {
    process.env.PATH = path
    await server.close()
    await rm(dir, { recursive: true, force: true })
  }
})
