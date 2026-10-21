import { execFile } from 'node:child_process'

export const maxMapBytes = 16 * 1024 * 1024
export const mapPath = '/mnt/data/rockrobo/last_map'

export function readMap(hostname: string): Promise<Buffer> {
  if (!/^[a-zA-Z0-9][a-zA-Z0-9.-]{0,252}$/.test(hostname)) {
    throw new Error('Enter a hostname or IPv4 address, without a user, port, or URL.')
  }

  // Fixed command and bounded output keep browser input out of the remote shell.
  return new Promise((resolve, reject) => {
    execFile('ssh', [
      '-T', '-o', 'BatchMode=yes', '-o', 'StrictHostKeyChecking=yes',
      '-o', 'ConnectTimeout=10', '-o', 'ConnectionAttempts=1',
      '-o', 'ClearAllForwardings=yes', '-o', 'PermitLocalCommand=no',
      `root@${hostname}`, `head -c ${maxMapBytes + 1} ${mapPath}`,
    ], { encoding: 'buffer', timeout: 20_000, maxBuffer: maxMapBytes }, (error, stdout) => {
      if (error) {
        reject(new Error('SSH read failed. Check the hostname, root SSH key access, and known_hosts.'))
        return
      }

      resolve(stdout)
    })
  })
}
