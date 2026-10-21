import assert from 'node:assert/strict'
import { createHash } from 'node:crypto'
import { deflateSync } from 'node:zlib'
import { mkdtemp, writeFile, rm } from 'node:fs/promises'
import { tmpdir } from 'node:os'
import { join } from 'node:path'
import { test } from 'node:test'
import { createServer } from 'vite'
import { inspectMap } from './map.ts'
import { mapApi } from './api.ts'
import { readMap } from './ssh.ts'
import { inspectRooms } from './rooms.ts'

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

function vint(value: number): Buffer {
  const bytes: number[] = []
  do {
    bytes.push((value % 128) | (value >= 128 ? 128 : 0))
    value = Math.floor(value / 128)
  } while (value)
  return Buffer.from(bytes)
}

function field(id: number, value: number | Buffer): Buffer {
  return typeof value === 'number'
    ? Buffer.concat([vint(id * 8), vint(value)])
    : Buffer.concat([vint(id * 8 + 2), vint(value.length), value])
}

function roomRegion(): Buffer {
  const region = Buffer.alloc(0x13f120)
  const start = 0x31da0
  region[start] = region[start + 4] = 1
  region.writeInt32LE(1024, start + 8)
  region.writeInt32LE(1024, start + 12)
  const offset = start + 16 + (512 + 80) * 1024 + 512 - 40
  region.set([16 | 0x40, 17], offset)
  region.set([18, 0], offset + 1024)
  return region
}

function persistence(parts = [roomRegion()]): Buffer {
  return field(20, Buffer.concat([
    field(10, 5), field(20, 1), field(30, 1), field(40, 0x13f120),
    ...parts.map(part => field(50, deflateSync(part))),
    field(60, Buffer.concat(parts.map(part => vint(part.length)))),
  ]))
}

test('align room cells with the raster and mask non-ID bits', () => {
  const map = inspectMap(fixture())
  assert.deepEqual(Buffer.from(inspectRooms(persistence(), map), 'base64'), Buffer.from([16, 17, 18, 0]))
  const region = roomRegion()
  assert.equal(inspectRooms(persistence([region.subarray(0, 600000), region.subarray(600000)]), map), 'EBESAA==')
  assert.equal(inspectRooms(Buffer.alloc(0), map), 'AAAAAA==')
  assert.equal(inspectRooms(persistence(), { ...map, left: -514 }), 'AAAAAA==')
})

test('reject incomplete and oversized room data', () => {
  const map = inspectMap(fixture())
  assert.throws(() => inspectRooms(persistence().subarray(0, -1), map), /room data/)
  assert.throws(() => inspectRooms(persistence([Buffer.alloc(0x13f121)]), map))
  const region = roomRegion()
  region.writeInt32LE(2048, 0x31da8)
  assert.throws(() => inspectRooms(persistence([region]), map), /dimensions/)
  region.writeInt32LE(0, 0x31da8)
  assert.throws(() => inspectRooms(persistence([region]), map), /dimensions/)
})

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
if (args.at(-2) !== 'root@robot.local' || !args.includes('StrictHostKeyChecking=yes')) process.exit(1);
const files = {
  'head -c 16777217 /mnt/data/rockrobo/last_map': '${fixture().toString('base64')}',
  'head -c 16777217 /mnt/data/rockrobo/PersistData_1.data': '${persistence().toString('base64')}',
};
if (!files[args.at(-1)]) process.exit(1);
process.stdout.write(Buffer.from(files[args.at(-1)], 'base64'));
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
    assert.deepEqual(await response.json(), { ...inspectMap(fixture()), rooms: 'EBESAA==',
      native: { raster: fixture().toString('base64'), persistence: persistence().toString('base64') } })
    const save = (source: string, input: unknown) => fetch(`${origin}/api/map/save`, {
      method: 'POST', headers: { Origin: source, 'Content-Type': 'application/json' }, body: JSON.stringify(input),
    })
    assert.equal((await save('http://foreign.example', {})).status, 403)
    assert.equal((await save(origin, { hostname: 'robot.local' })).status, 400)
    assert.equal((await save(origin, { hostname: 'robot.local', confirmation: 'install-and-reboot' })).status, 400)
  } finally {
    process.env.PATH = path
    await server.close()
    await rm(dir, { recursive: true, force: true })
  }
})
