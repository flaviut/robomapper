import assert from 'node:assert/strict'
import { createHash } from 'node:crypto'
import { execFile } from 'node:child_process'
import { mkdir, mkdtemp, readFile, rm, writeFile } from 'node:fs/promises'
import { tmpdir } from 'node:os'
import { join } from 'node:path'
import { fileURLToPath } from 'node:url'
import { promisify } from 'node:util'
import { test } from 'node:test'
import { deflateSync } from 'node:zlib'
import { applyEdit, parseEdit } from './edits.ts'
import { packTar } from './archive.ts'
import { inspectMap } from './map.ts'
import { inspectRooms } from './rooms.ts'
import { readRegion } from './persistence.ts'

const run = promisify(execFile)
const script = fileURLToPath(new URL('../../tools/map-maint/matching-set.sh', import.meta.url))

function integer(value: number): Buffer {
  const bytes: number[] = []
  do { bytes.push(value % 128 | (value >= 128 ? 128 : 0)); value = Math.floor(value / 128) } while (value)
  return Buffer.from(bytes)
}

function field(id: number, value: number | Buffer): Buffer {
  return typeof value === 'number' ? Buffer.concat([integer(id * 8), integer(value)])
    : Buffer.concat([integer(id * 8 + 2), integer(value.length), value])
}

function fixture() {
  const header = Buffer.alloc(30)
  header.write('RRSLAM')
  header.writeUInt16LE(2, 6)
  header.writeUInt16LE(20, 8)
  header.writeUInt32LE(20, 10)
  header.writeInt32LE(-2, 14)
  header.writeInt32LE(-2, 18)
  header.writeUInt32LE(4, 22)
  header.writeUInt32LE(4, 26)
  const cells = Buffer.alloc(16, 32)
  const raster = Buffer.concat([header, cells, createHash('md5').update(cells).digest()])
  const region = Buffer.alloc(0x13f120, 77)
  region.writeInt32LE(4, 0x31da8)
  region.writeInt32LE(4, 0x31dac)
  region.fill(0x41, 0x31db0, 0x31dc0)
  const persistence = field(20, Buffer.concat([
    field(10, 5), field(20, 1), field(30, 1), field(40, region.length), field(50, deflateSync(region)),
  ]))
  return { raster, persistence, region }
}

test('edits preserve native headers, flags and every unrelated persistence byte', () => {
  const { raster, persistence, region } = fixture()
  const cells = Buffer.alloc(16, 32)
  const rooms = Buffer.from(inspectRooms(persistence, inspectMap(raster)), 'base64')
  cells[0] = 255
  rooms[1] = 17
  const result = applyEdit(parseEdit({ native: { raster: raster.toString('base64'), persistence: persistence.toString('base64') },
    cells: cells.toString('base64'), rooms: rooms.toString('base64') }))
  assert.deepEqual(result.raster.subarray(0, 30), raster.subarray(0, 30))
  assert.equal(inspectMap(result.raster).cells, cells.toString('base64'))
  const expected = Buffer.from(region)
  expected[0x31db1] = 0x40 | 17
  assert.deepEqual(readRegion(result.persistence, 5), expected)
})

test('an interrupted installation restores the whole captured set', async () => {
  const dir = await mkdtemp(join(tmpdir(), 'map-rollback-'))
  const root = join(dir, 'root')
  const work = join(dir, 'work')
  const original = Object.fromEntries(['last_map', 'user_map0', 'user_map4', 'PersistData_1.data', 'PersistData_2.data', 'PersistData_6.data']
    .map(name => [name, Buffer.from(`original ${name}`)]))
  try {
    await mkdir(join(dir, 'bin'))
    await writeFile(join(dir, 'bin/sync'), '#!/bin/sh\nexit 0\n', { mode: 0o700 })
    const env = { ...process.env, PATH: `${dir}/bin:${process.env.PATH}` }
    const isolated = join(dir, 'matching-set.sh')
    // Test file recovery without scanning unrelated host processes.
    await writeFile(isolated, (await readFile(script, 'utf8')).replace(/stopped\(\) \{[\s\S]*?\n\}/, 'stopped() { :; }'))
    await mkdir(root)
    for (const [name, data] of Object.entries(original)) await writeFile(join(root, name), data, { mode: 0o640 })
    await run('sh', [isolated, 'capture', root, work], { env })
    const patch = Object.fromEntries(['last_map', 'user_map0', 'PersistData_1.data', 'PersistData_2.data'].map(name => [name, Buffer.from(`edited ${name}`)]))
    await mkdir(join(work, 'patch'))
    await writeFile(join(dir, 'patch.tar'), packTar(patch))
    await run('tar', ['-xf', join(dir, 'patch.tar'), '-C', join(work, 'patch')])
    await writeFile(join(work, 'patch.files'), Object.keys(patch).join('\n') + '\n')
    await writeFile(join(work, 'patch.md5'), Object.entries(patch).map(([name, data]) => `${createHash('md5').update(data).digest('hex')}  ${name}\n`).join(''))
    await writeFile(join(work, 'patch.ready'), '')
    await writeFile(join(work, 'offdevice.verified'), '')
    const mv = (await run('sh', ['-c', 'command -v mv'])).stdout.trim()
    await writeFile(join(dir, 'bin/mv'), `#!/bin/sh\nn=$(cat '${dir}/count' 2>/dev/null || echo 0)\nn=$((n + 1))\necho "$n" > '${dir}/count'\n[ "$n" -ne 8 ] || exit 1\nexec '${mv}' "$@"\n`, { mode: 0o700 })
    await assert.rejects(run('sh', [isolated, 'apply', root, work], { env }))
    await run('sh', [isolated, 'rollback', root, work], { env })
    for (const [name, data] of Object.entries(original)) assert.deepEqual(await readFile(join(root, name)), data)
  } finally { await rm(dir, { recursive: true, force: true }) }
})
