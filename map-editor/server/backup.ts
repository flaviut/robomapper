import { mkdir, mkdtemp, open } from 'node:fs/promises'
import { homedir } from 'node:os'
import { join } from 'node:path'

export class Backup {
  private directory: string

  private constructor(directory: string) { this.directory = directory }

  static async create(): Promise<Backup> {
    const parent = join(process.env.XDG_STATE_HOME ?? join(homedir(), '.local/state'), 'map-editor/backups')
    await mkdir(parent, { recursive: true, mode: 0o700 })
    return new Backup(await mkdtemp(join(parent, 'upload-')))
  }

  get path(): string { return this.directory }

  async save(name: string, data: Buffer) {
    if (!/^[a-zA-Z0-9._-]+$/.test(name)) throw new Error('Invalid backup filename.')
    const file = await open(join(this.directory, name), 'wx', 0o600)
    try {
      await file.writeFile(data)
      await file.sync()
    } finally { await file.close() }
    // A durable file is not enough; persist its directory entry before authorizing installation.
    const directory = await open(this.directory, 'r')
    try { await directory.sync() } finally { await directory.close() }
  }
}
