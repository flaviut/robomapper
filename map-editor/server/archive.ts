const block = 512
export const maxArchiveBytes = 128 * 1024 * 1024

interface TarEntry {
  data: Buffer
  type: 'file' | 'directory'
}

function nameOk(name: string) {
  return name.length > 0 && /^[a-zA-Z0-9._/-]+$/.test(name)
    && !name.split('/').some(part => !part || part === '.' || part === '..')
}

function octal(header: Buffer, start: number, size: number): number {
  const text = header.subarray(start, start + size).toString('ascii').replace(/\0.*$/, '').trim()
  if (!/^[0-7]+$/.test(text)) throw new Error('Invalid tar number.')
  return parseInt(text, 8)
}

function text(header: Buffer, start: number, size: number): string {
  return header.subarray(start, start + size).toString('utf8').replace(/\0.*$/, '')
}

function sum(header: Buffer): number {
  return header.reduce((total, byte, index) => total + (index >= 148 && index < 156 ? 32 : byte), 0)
}

export function readTar(data: Buffer): Map<string, TarEntry> {
  if (data.length > maxArchiveBytes || data.length % block) throw new Error('Invalid tar size.')
  const entries = new Map<string, TarEntry>()
  let offset = 0
  while (offset + block <= data.length) {
    const header = data.subarray(offset, offset + block)
    if (header.every(byte => byte === 0)) {
      if (data.length - offset < 2 * block || !data.subarray(offset).every(byte => byte === 0)) {
        throw new Error('Invalid tar trailer.')
      }
      return entries
    }
    if (octal(header, 148, 8) !== sum(header)) throw new Error('Tar checksum mismatch.')
    const prefix = text(header, 345, 155)
    const name = `${prefix ? `${prefix}/` : ''}${text(header, 0, 100)}`.replace(/\/$/, '')
    const type = header[156] === 53 ? 'directory' : header[156] === 48 || header[156] === 0 ? 'file' : null
    const size = octal(header, 124, 12)
    if (!nameOk(name) || entries.has(name) || !type || (type === 'directory' && size)) {
      throw new Error('Unsafe tar member.')
    }
    offset += block
    if (size > data.length - offset) throw new Error('Truncated tar member.')
    entries.set(name, { type, data: data.subarray(offset, offset + size) })
    offset += Math.ceil(size / block) * block
  }
  throw new Error('Missing tar trailer.')
}

export function packTar(files: Record<string, Buffer>): Buffer {
  const chunks: Buffer[] = []
  for (const [name, data] of Object.entries(files)) {
    if (!nameOk(name) || Buffer.byteLength(name) > 100) throw new Error('Invalid archive filename.')
    const header = Buffer.alloc(block)
    header.write(name)
    header.write('0000600\0', 100)
    header.write('0000000\0', 108)
    header.write('0000000\0', 116)
    header.write(`${data.length.toString(8).padStart(11, '0')}\0`, 124)
    header.write('00000000000\0', 136)
    header[156] = 48
    header.write('ustar\0', 257)
    header.write('00', 263)
    header.write(`${sum(header).toString(8).padStart(6, '0')}\0 `, 148)
    chunks.push(header, data, Buffer.alloc((block - data.length % block) % block))
  }
  chunks.push(Buffer.alloc(2 * block))
  const result = Buffer.concat(chunks)
  if (result.length > maxArchiveBytes) throw new Error('Archive too large.')
  return result
}
