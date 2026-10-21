import { execFile } from 'node:child_process'

export const maxMapBytes = 16 * 1024 * 1024
export const mapPath = '/mnt/data/rockrobo/last_map'

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

export function runRemote(hostname: string, command: string, input: Buffer = Buffer.alloc(0),
  limits = { bytes: maxMapBytes, timeout: 20_000 }): Promise<Buffer> {
  checkHost(hostname)
  // Only driver-built commands reach this boundary; browser input is never shell syntax.
  return new Promise((resolve, reject) => {
    const child = execFile('ssh', [
      '-T', '-o', 'BatchMode=yes', '-o', 'StrictHostKeyChecking=yes',
      '-o', 'ConnectTimeout=10', '-o', 'ConnectionAttempts=1',
      '-o', 'ClearAllForwardings=yes', '-o', 'PermitLocalCommand=no',
      `root@${hostname}`, command,
    ], { encoding: 'buffer', timeout: limits.timeout, maxBuffer: limits.bytes }, (error, stdout, stderr) => {
      if (error) {
        const detail = stderr.toString('utf8').trim().slice(-2048)
        reject(new Error(`SSH failed. ${detail || 'Check root SSH key access and known_hosts.'}`))
        return
      }

      resolve(stdout)
    })
    child.stdin?.on('error', () => {})
    child.stdin?.end(input)
  })
}
