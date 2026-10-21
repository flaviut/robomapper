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
  return runSsh(hostname, [`root@${hostname}`, command], input, limits)
}

export async function readHttp(hostname: string, port: number, path: string, authorization: string): Promise<unknown> {
  const request = Buffer.from(`GET ${path} HTTP/1.1\r\nHost: localhost\r\n${authorization ? `Authorization: ${authorization}\r\n` : ''}Connection: close\r\n\r\n`)
  const response = await runSsh(hostname, ['-W', `127.0.0.1:${port}`, `root@${hostname}`], request,
    { bytes: 1024 * 1024, timeout: 15_000 })
  const end = response.indexOf('\r\n\r\n')
  const headers = response.subarray(0, end).toString('ascii')
  if (end < 0 || !/^HTTP\/1\.[01] 200 /.test(headers)) throw new Error('Could not read the robot state.')
  let body = response.subarray(end + 4)
  if (/transfer-encoding: chunked/i.test(headers)) {
    const chunks: Buffer[] = []
    while (body.length) {
      const line = body.indexOf('\r\n')
      const size = parseInt(body.subarray(0, line).toString('ascii'), 16)
      if (line < 0 || !Number.isFinite(size) || size < 0 || size > body.length - line - 4) throw new Error('Invalid robot response.')
      if (!size) break
      chunks.push(body.subarray(line + 2, line + 2 + size))
      body = body.subarray(line + 4 + size)
    }
    body = Buffer.concat(chunks)
  }
  return JSON.parse(body.toString('utf8'))
}

function runSsh(hostname: string, args: string[], input: Buffer, limits: { bytes: number, timeout: number }): Promise<Buffer> {
  checkHost(hostname)
  // Credentials travel on stdin, never in SSH arguments or logs.
  return new Promise((resolve, reject) => {
    const child = execFile('ssh', [
      '-T', '-o', 'BatchMode=yes', '-o', 'StrictHostKeyChecking=yes',
      '-o', 'ConnectTimeout=10', '-o', 'ConnectionAttempts=1',
      '-o', 'ClearAllForwardings=yes', '-o', 'PermitLocalCommand=no',
      ...args,
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
