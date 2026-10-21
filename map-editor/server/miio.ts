import { createCipheriv, createDecipheriv, createHash, randomInt } from 'node:crypto'
import { createSocket } from 'node:dgram'
import { isIPv6 } from 'node:net'
import { runRemote } from './ssh.ts'

type Query = 'get_ota_state' | 'get_status'
type Status = { state: number, battery: number, [key: string]: number }
const md5 = (...parts: Buffer[]) => parts.reduce((hash, part) => hash.update(part), createHash('md5')).digest()

export async function readStatus(host: string): Promise<{ ota: unknown, status: Status }> {
  const peer = await runRemote(host, 'printf "%s" "$SSH_CONNECTION"')
  const address = peer.toString('ascii').split(' ')[2]!
  const token = await runRemote(host, 'head -c 17 /mnt/data/miio/device.token', Buffer.alloc(0), { bytes: 4096, timeout: 15_000 })
  if (token.length !== 16) throw new Error('Could not read robot credentials.')
  const key = md5(token)
  const iv = md5(key, token)
  const socket = createSocket(isIPv6(address) ? 'udp6' : 'udp4')

  function exchange(packet: Buffer): Promise<Buffer> {
    return new Promise((resolve, reject) => {
      const timer = setTimeout(() => fail(), 6000)
      const clean = () => { clearTimeout(timer); socket.off('error', fail); socket.off('message', done) }
      const fail = () => { clean(); reject(new Error('Could not read fresh robot status.')) }
      const done = (reply: Buffer) => { clean(); resolve(reply) }
      socket.once('error', fail)
      socket.once('message', done)
      socket.send(packet, (error) => { if (error) fail() })
    })
  }

  try {
    await new Promise<void>((resolve, reject) => {
      socket.once('error', reject)
      socket.connect(54321, address, () => { socket.off('error', reject); resolve() })
    })
    const hello = Buffer.alloc(32, 0xff)
    hello.writeUInt16BE(0x2131, 0)
    hello.writeUInt16BE(32, 2)
    const handshake = await exchange(hello)
    if (handshake.length !== 32 || handshake.readUInt16BE(0) !== 0x2131 || !handshake.readUInt32BE(12)) {
      throw new Error('Invalid robot handshake.')
    }
    const start = Date.now()

    async function query(method: Query): Promise<unknown> {
      const id = randomInt(1, 0x7fffffff)
      const cipher = createCipheriv('aes-128-cbc', key, iv)
      const data = Buffer.from(JSON.stringify({ id, method, params: method === 'get_ota_state' ? [] : {} }))
      const body = Buffer.concat([cipher.update(data), cipher.final()])
      const header = Buffer.alloc(32)
      header.writeUInt16BE(0x2131, 0)
      header.writeUInt16BE(32 + body.length, 2)
      header.writeUInt32BE(handshake.readUInt32BE(8), 8)
      header.writeUInt32BE(handshake.readUInt32BE(12) + Math.floor((Date.now() - start) / 1000), 12)
      md5(header.subarray(0, 16), token, body).copy(header, 16)
      const reply = await exchange(Buffer.concat([header, body]))
      if (reply.length <= 32 || reply.readUInt16BE(0) !== 0x2131 || reply.readUInt16BE(2) !== reply.length ||
        !md5(reply.subarray(0, 16), token, reply.subarray(32)).equals(reply.subarray(16, 32))) {
        throw new Error('Invalid robot status response.')
      }
      const decipher = createDecipheriv('aes-128-cbc', key, iv)
      const decoded = Buffer.concat([decipher.update(reply.subarray(32)), decipher.final()])
      const message = JSON.parse(decoded.toString('utf8').replace(/\0$/, '')) as { id: number, result?: unknown[] }
      if (message.id !== id || !Array.isArray(message.result) || message.result.length !== 1) {
        throw new Error('Could not read robot readiness.')
      }
      return message.result[0]
    }

    // Only these read-only methods are exposed; handshake replies cannot replace the SSH-read key.
    const ota = await query('get_ota_state')
    const status = await query('get_status') as Status
    return { ota, status }
  } finally {
    token.fill(0)
    key.fill(0)
    iv.fill(0)
    socket.close()
  }
}
