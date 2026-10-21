import { createHash } from 'node:crypto'
import { readMap, maxMapBytes } from './ssh.ts'

export function inspectMap(data: Buffer) {
  if (data.length < 46 || data.length > maxMapBytes) {
    throw new Error('Invalid map size.')
  }

  if (!data.subarray(0, 6).equals(Buffer.from('RRSLAM'))
    || data.readUInt16LE(6) !== 2 || data.readUInt16LE(8) !== 20
    || data.readUInt32LE(10) !== 20) {
    throw new Error('Unsupported map header. Expected RRSLAM v2.')
  }

  const width = data.readUInt32LE(22)
  const height = data.readUInt32LE(26)
  if (!width || !height || data.length !== 46 + width * height) {
    throw new Error('Invalid map dimensions.')
  }

  const cells = data.subarray(30, -16)
  const digest = createHash('md5').update(cells).digest()
  if (!digest.equals(data.subarray(-16))) {
    throw new Error('Map checksum mismatch. The map may have changed during reading; retry while idle.')
  }

  return {
    width, height, left: data.readInt32LE(14), top: data.readInt32LE(18),
    scale: data.readUInt32LE(10), checksum: digest.toString('hex'),
    cells: cells.toString('base64'),
  }
}

export async function loadMap(hostname: string) {
  return inspectMap(await readMap(hostname))
}
