import { createHash, randomUUID } from 'node:crypto'
import { readFile } from 'node:fs/promises'
import { setTimeout as pause } from 'node:timers/promises'
import { readTar, packTar } from './archive.ts'
import { Backup } from './backup.ts'
import { applyEdit, parseEdit, type EditInput, type MapEdit } from './edits.ts'
import { inspectMap, loadMap } from './map.ts'
import { readRegion } from './persistence.ts'
import { inspectRooms } from './rooms.ts'
import { checkHost, readBoot, runSave, uploadSave } from './ssh.ts'

let saving = false
type Snapshot = Map<string, { data: Buffer, type: 'file' | 'directory' }>

function member(files: Snapshot, name: string): Buffer {
  const entry = files.get(name)
  if (!entry || entry.type !== 'file') throw new Error(`Missing backup file: ${name}`)
  return entry.data
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
  const result = applyEdit(edit)
  return { last_map: result.raster, 'PersistData_1.data': result.persistence,
    [primary]: result.raster, [persistence]: result.persistence }
}

export async function saveMap(hostname: string, input: EditInput) {
  checkHost(hostname)
  if (saving) throw new Error('A save is already running.')
  saving = true
  const started = Date.now()
  const work = `/mnt/data/map-editor-${randomUUID()}`
  const log = (line: string) => console.log(`${new Date().toISOString()} [map-save ${hostname}] ${line}`)
  let stage = 'Validate edits'
  const step = (name: string) => { stage = name; log(name) }
  let backup: Backup | undefined

  try {
    step('Validate edits')
    const edit = parseEdit(input)
    const expected = applyEdit(edit)
    const raster = expected.raster.toString('base64')
    const rooms = inspectRooms(expected.persistence, inspectMap(expected.raster))
    backup = await Backup.create()
    log(`Robot files: ${work}; local backup: ${backup.path}`)

    step('Upload save script and native helper')
    const tools = new URL('../../custom_components/map_editor/tools/', import.meta.url)
    const payload = packTar({ 'save.sh': await readFile(new URL('save.sh', tools)),
      'map-maint': await readFile(new URL('map-maint', tools)) })
    const boot = await uploadSave(hostname, work, payload, log)
    await backup.save('request.json', Buffer.from(JSON.stringify({ hostname, work, boot,
      source: createHash('sha256').update(edit.raster).digest('hex') }) + '\n'))

    step('Run save script')
    await runSave(hostname, work, async archive => {
      step(`Store verified stopped backup (${archive.length} bytes)`)
      await backup!.save('untouched-stopped-backup.tar', archive)
      step('Build edited map files')
      const patch = makePatch(edit, readTar(archive))
      const hashes = Object.entries(patch).map(([name, data]) => `${createHash('md5').update(data).digest('hex')}  ${name}\n`).join('')
      const candidate = packTar({ ...patch, 'patch.md5': Buffer.from(hashes) })
      await backup!.save('candidate.tar', candidate)
      step(`Send patch: ${Object.keys(patch).join(', ')}`)
      return candidate
    }, log)

    step('Wait for reboot and verify loaded map')
    const deadline = Date.now() + 240_000
    let lastError: unknown
    let nextBoot = boot
    let loaded: Awaited<ReturnType<typeof loadMap>> | undefined
    while (Date.now() < deadline) {
      try {
        nextBoot = await readBoot(hostname)
        if (nextBoot !== boot) {
          const map = await loadMap(hostname)
          if (map.native.raster === raster && map.rooms === rooms) { loaded = map; break }
          lastError = new Error('The restarted robot loaded a different map.')
        }
      } catch (error) { lastError = error }
      await pause(2000)
    }
    if (!loaded) throw new Error('Could not verify the edited map after reboot.', { cause: lastError })

    step('Store receipt')
    await backup.save('receipt.json', Buffer.from(JSON.stringify({ hostname, work, boot: nextBoot,
      completed: new Date().toISOString() }) + '\n'))
    log(`Saved and verified after reboot (${Date.now() - started}ms); backup: ${backup.path}`)
    return { map: loaded, backup: backup.path }
  } catch (error) {
    console.log(`${new Date().toISOString()} [map-save ${hostname}] FAILED: ${stage}; robot=${work}; backup=${backup?.path}`, error)
    throw error
  } finally {
    saving = false
  }
}
