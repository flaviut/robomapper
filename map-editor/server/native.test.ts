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
import { packTar, readTar } from './archive.ts'
import { runSave } from './ssh.ts'
import { inspectMap } from './map.ts'
import { inspectRooms } from './rooms.ts'
import { readRegion } from './persistence.ts'

const run = promisify(execFile)
const script = fileURLToPath(new URL('../../tools/map-maint/save.sh', import.meta.url))

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

test('an interrupted installation restores affected files and preserves backups', async () => {
  const dir = await mkdtemp(join(tmpdir(), 'map-rollback-'))
  const root = join(dir, 'root')
  const work = join(dir, 'work')
  const path = process.env.PATH
  const original = Object.fromEntries(['last_map', 'user_map0', 'user_map4', 'PersistData_1.data', 'PersistData_2.data', 'PersistData_6.data', 'SharedMultiMapInfo', 'exclude_process.conf']
    .map(name => [name, Buffer.from(`original ${name}`)]))
  try {
    await mkdir(join(dir, 'bin'))
    await mkdir(root)
    await mkdir(work)
    await writeFile(join(dir, 'bin/sync'), '#!/bin/sh\nexit 0\n', { mode: 0o700 })
    const isolated = join(dir, 'save.sh')
    // Isolate hardware operations; exercise the real transfer, installation and rollback.
    await writeFile(isolated, (await readFile(script, 'utf8'))
      .replace(/^ROOT=.*$/m, `ROOT='${root}'`)
      .replace(/^PATH=.*$/m, `PATH='${dir}/bin:${path}'`)
      .replace(/stop_writers\(\) \{[\s\S]*?\n\}/, 'stop_writers() { touched=1; }')
      .replace('/sbin/reboot', ':'))
    for (const [name, data] of Object.entries(original)) await writeFile(join(root, name), data, { mode: 0o640 })
    const patch = Object.fromEntries(['last_map', 'user_map0', 'PersistData_1.data', 'PersistData_2.data'].map(name => [name, Buffer.from(`edited ${name}`)]))
    const hashes = Object.entries(patch).map(([name, data]) => `${createHash('md5').update(data).digest('hex')}  ${name}\n`).join('')
    const mv = (await run('sh', ['-c', 'command -v mv'])).stdout.trim()
    await writeFile(join(dir, 'bin/mv'), `#!/bin/sh\nn=$(cat '${dir}/count' 2>/dev/null || echo 0)\nn=$((n + 1))\necho "$n" > '${dir}/count'\n[ "$n" -ne 2 ] || exit 1\nexec '${mv}' "$@"\n`, { mode: 0o700 })
    await writeFile(join(dir, 'bin/ssh'), `#!/bin/sh\nexec sh '${isolated}' '${work}'\n`, { mode: 0o700 })
    process.env.PATH = `${dir}/bin:${path}`
    await assert.rejects(runSave('robot.local', 'save', async archive => {
      const snapshot = readTar(archive)
      for (const name of Object.keys(patch)) assert.deepEqual(snapshot.get(name)!.data, original[name])
      return packTar({ ...patch, 'patch.md5': Buffer.from(hashes) })
    }, () => {}), /code=1/)
    for (const [name, data] of Object.entries(original)) assert.deepEqual(await readFile(join(root, name)), data)
  } finally {
    process.env.PATH = path
    await rm(dir, { recursive: true, force: true })
  }
})
