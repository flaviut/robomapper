import { execFile, spawn } from 'node:child_process'
import { createHash } from 'node:crypto'
import { createInterface } from 'node:readline'
import { maxArchiveBytes } from './archive.ts'

export const maxMapBytes = 16 * 1024 * 1024
export const mapPath = '/mnt/data/rockrobo/last_map'
type Limits = { bytes: number, timeout: number, report?: (line: string) => void }

export function readMap(hostname: string): Promise<Buffer> {
  return readFile(hostname, mapPath)
}

export function readRooms(hostname: string): Promise<Buffer> {
  return readFile(hostname, '/mnt/data/rockrobo/PersistData_1.data')
}

function readFile(hostname: string, path: string): Promise<Buffer> {
  return runRemote(hostname, `head -c ${maxMapBytes + 1} ${path}`)
}

export function checkHost(hostname: string) {
  if (!/^[a-zA-Z0-9][a-zA-Z0-9.-]{0,252}$/.test(hostname)) {
    throw new Error('Enter a hostname or IPv4 address, without a user, port, or URL.')
  }
}

function sshArgs(hostname: string, command: string): string[] {
  checkHost(hostname)
  return ['-T', '-o', 'BatchMode=yes', '-o', 'StrictHostKeyChecking=yes',
    '-o', 'ConnectTimeout=10', '-o', 'ConnectionAttempts=1',
    '-o', 'ClearAllForwardings=yes', '-o', 'PermitLocalCommand=no', `root@${hostname}`, command]
}

export function runRemote(hostname: string, command: string, input: Buffer = Buffer.alloc(0),
  limits: Limits = { bytes: maxMapBytes, timeout: 20_000 }): Promise<Buffer> {
  const args = sshArgs(hostname, command)
  const started = Date.now()
  return new Promise((resolve, reject) => {
    const child = execFile('ssh', args,
      { encoding: 'buffer', timeout: limits.timeout, maxBuffer: limits.bytes }, (error, stdout, stderr) => {
        if (error) {
          // Never include execFile's original error: it contains command arguments.
          reject(new Error(`SSH failed: code=${error.code ?? 'none'} signal=${error.signal ?? 'none'} elapsed=${Date.now() - started}ms limit=${limits.timeout}ms. ${stderr.toString('utf8').trim().slice(-8192)}`))
          return
        }
        resolve(stdout)
      })
    if (limits.report && child.stderr) createInterface({ input: child.stderr }).on('line', limits.report)
    child.stdin?.on('error', () => {})
    child.stdin?.end(input)
  })
}

export async function uploadSave(hostname: string, work: string, payload: Buffer, report: (line: string) => void): Promise<string> {
  return (await runRemote(hostname, `set -eu
umask 077
mkdir -m 700 ${work}
tar -xpf - -C ${work}
chmod 700 ${work}/map-maint
cat /proc/sys/kernel/random/boot_id`, payload, { bytes: maxMapBytes, timeout: 20_000, report })).toString().trim()
}

export async function readBoot(hostname: string): Promise<string> {
  return (await runRemote(hostname, 'cat /proc/sys/kernel/random/boot_id')).toString().trim()
}

export async function runSave(hostname: string, work: string,
  change: (archive: Buffer) => Promise<Buffer>, report: (line: string) => void): Promise<void> {
  const started = Date.now()
  const child = spawn('ssh', sshArgs(hostname, `/bin/sh ${work}/save.sh ${work}`), { timeout: 120_000, stdio: ['pipe', 'pipe', 'pipe'] })
  const closed = new Promise<{ code: number | null, signal: string | null, error?: Error }>(resolve => {
    child.once('error', error => resolve({ code: null, signal: null, error }))
    child.once('close', (code, signal) => resolve({ code, signal }))
  })
  let stderr = ''
  child.stderr.on('data', chunk => { stderr = (stderr + chunk.toString('utf8')).slice(-8192) })
  createInterface({ input: child.stderr }).on('line', report)
  child.stdin.on('error', () => {})
  let buffer = Buffer.alloc(0)
  let size: number | undefined
  let digest = ''
  let received = false

  try {
    // Only the framed backup travels on stdout; robot progress uses stderr.
    for await (const chunk of child.stdout) {
      buffer = Buffer.concat([buffer, chunk])
      if (size === undefined) {
        const end = buffer.indexOf('\n')
        if (end < 0) {
          if (buffer.length > 128) throw new Error('Invalid backup header.')
          continue
        }
        const header = /^BACKUP\s+(\d+)\s+([a-f0-9]{32})$/.exec(buffer.subarray(0, end).toString('ascii'))
        if (!header) throw new Error('Invalid backup header.')
        size = Number(header[1])
        digest = header[2]!
        if (size < 1024 || size > maxArchiveBytes) throw new Error('Invalid backup size.')
        buffer = buffer.subarray(end + 1)
      }
      if (!received) {
        if (buffer.length < size) continue
        const archive = buffer.subarray(0, size)
        if (createHash('md5').update(archive).digest('hex') !== digest) throw new Error('Backup transfer checksum mismatch.')
        const patch = await change(archive)
        buffer = buffer.subarray(size)
        received = true
        child.stdin.end(Buffer.concat([Buffer.from('PATCH\n'), patch]))
      }
      if (buffer.length > 128) throw new Error('Unexpected save output.')
    }
    const status = await closed
    if (status.error) throw new Error(`Could not start SSH: ${status.error.message}`)
    if (!received || buffer.toString('ascii').trim() !== 'INSTALLED' || status.signal || (status.code !== 0 && status.code !== 255)) {
      throw new Error(`Save script failed: code=${status.code} signal=${status.signal ?? 'none'} elapsed=${Date.now() - started}ms limit=120000ms. ${stderr.trim()}`)
    }
    report(`SSH closed: code=${status.code}; installation acknowledged`)
  } finally {
    child.stdin.destroy()
    child.kill()
  }
}
