import { createHash } from 'node:crypto'
import { setTimeout as pause } from 'node:timers/promises'
import { readTar, packTar } from './archive.ts'
import { Backup } from './backup.ts'
import { applyEdit, parseEdit, type EditInput, type MapEdit } from './edits.ts'
import { Maintenance } from './maintenance.ts'
import { inspectMap, loadMap } from './map.ts'
import { readRegion } from './persistence.ts'
import { inspectRooms } from './rooms.ts'

const active = new Set<string>()

type Snapshot = Map<string, { data: Buffer, type: 'file' | 'directory' }>

function member(files: Snapshot, name: string): Buffer {
  const entry = files.get(name)
  if (!entry || entry.type !== 'file') throw new Error(`Missing backup file: ${name}`)
  return entry.data
}

export function readSnapshot(archive: Buffer): Snapshot {
  const files = readTar(archive)
  if (!files.has('capture.complete') || member(files, 'snapshot/root').toString() !== '/mnt/data/rockrobo\n') {
    throw new Error('Invalid stopped backup.')
  }
  const seen = new Set<string>()
  for (const line of member(files, 'snapshot.md5').toString().trim().split('\n')) {
    const match = /^([a-f0-9]{32})  ([a-zA-Z0-9._-]+)$/.exec(line)
    if (!match || seen.has(match[2]!)) throw new Error('Invalid backup manifest.')
    seen.add(match[2]!)
    const digest = createHash('md5').update(member(files, `snapshot/${match[2]}`)).digest('hex')
    if (digest !== match[1]) throw new Error('Stopped backup checksum mismatch.')
  }
  for (const name of ['root', 'namespace', 'present', 'absent', 'interrupted', 'files.tar']) {
    if (!seen.has(name)) throw new Error('Incomplete backup manifest.')
  }
  return readTar(member(files, 'snapshot/files.tar'))
}

export function makePatch(edit: MapEdit, snapshot: Snapshot): Record<string, Buffer> {
  const catalog = readRegion(member(snapshot, 'SharedMultiMapInfo'), 8)
  if (!catalog || catalog.length !== 0x9c || !catalog[0]) throw new Error('Unsupported map catalog.')
  const flag = catalog.readInt32LE(0x94)
  const entries = [0, 1, 2, 3].map(index => catalog.subarray(1 + index * 0x24, 1 + (index + 1) * 0x24))
  const selected = entries.filter(entry => entry[0] === flag)
  if (flag < 2 || flag > 5 || selected.length !== 1 || selected[0]![1]! < 6 || selected[0]![1]! > 9) {
    throw new Error('Cannot identify the active primary map.')
  }
  const primary = `user_map${flag - 2}`
  const persistence = `PersistData_${flag}.data`
  const runtime = applyEdit(edit, member(snapshot, 'last_map'), member(snapshot, 'PersistData_1.data'))
  const main = applyEdit(edit, member(snapshot, primary), member(snapshot, persistence))
  return { last_map: runtime.raster, 'PersistData_1.data': runtime.persistence,
    [primary]: main.raster, [persistence]: main.persistence }
}

async function waitFor<T>(read: () => Promise<T | null>, milliseconds: number): Promise<T> {
  const deadline = Date.now() + milliseconds
  while (Date.now() < deadline) {
    const result = await read()
    if (result !== null) return result
    await pause(500)
  }
  throw new Error('The robot did not finish the operation in time.')
}

export async function saveMap(hostname: string, input: EditInput) {
  const edit = parseEdit(input)
  // Validate the export before starting maintenance, including room-grid bounds.
  applyEdit(edit)
  const session = process.env.MAP_EDITOR_SESSION
  if (!session) {
    throw new Error('Prepare a maintenance session for this robot before saving.')
  }
  if (active.has(hostname)) throw new Error('A save is already running for this robot.')
  const robot = new Maintenance(hostname, session)
  active.add(hostname)
  let armed = false
  let backup: Backup | undefined
  try {
    backup = await Backup.create()
    const boot = await robot.prepare()
    await backup.save('original-exclusions.tar', await robot.originals())
    await backup.save('request.json', Buffer.from(JSON.stringify({ hostname, session, boot,
      source: createHash('sha256').update(edit.raster).digest('hex') }) + '\n'))
    armed = true
    await robot.arm()
    await waitFor(async () => await robot.ready() ? true : null, 10_000)
    await robot.start()
    const hash = await waitFor(() => robot.backupHash(), 60_000)
    const archive = await robot.backup()
    if (createHash('md5').update(archive).digest('hex') !== hash) throw new Error('Backup transfer checksum mismatch.')
    const snapshot = readSnapshot(archive)
    await backup.save('untouched-stopped-backup.tar', archive)
    const patch = makePatch(edit, snapshot)
    await backup.save('candidate.tar', packTar(patch))
    await robot.install(patch)
    const nextBoot = await waitFor(async () => {
      try {
        const current = await robot.boot()
        return /^[a-f0-9-]{36}$/.test(current) && current !== boot ? current : null
      } catch { return null }
    }, 240_000)
    await robot.outcome()
    const expectedRaster = patch.last_map!.toString('base64')
    const expectedRooms = inspectRooms(patch['PersistData_1.data']!, inspectMap(patch.last_map!))
    const loaded = await waitFor(async () => {
      try {
        const current = await loadMap(hostname)
        return current.native.raster === expectedRaster && current.rooms === expectedRooms ? current : null
      } catch { return null }
    }, 60_000).catch(() => { throw new Error('The robot restarted, but the edited map could not be verified.') })
    const receipt = { hostname, boot: nextBoot, backup: backup.path, session, completed: new Date().toISOString() }
    await backup.save('receipt.json', Buffer.from(JSON.stringify(receipt, null, 2) + '\n'))
    return { map: loaded, backup: backup.path }
  } catch (error) {
    if (armed) await robot.recover().catch(() => {})
    console.error('Map save failed', { hostname, session, backup: backup?.path, error })
    throw error
  } finally {
    active.delete(hostname)
  }
}
