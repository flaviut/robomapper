import type { IncomingMessage, ServerResponse } from 'node:http'
import type { Plugin } from 'vite'
import { loadMap } from './map.ts'
import { saveMap } from './deploy.ts'
import { maxMapBytes } from './ssh.ts'

async function handleMap(req: IncomingMessage, res: ServerResponse) {
  res.setHeader('Cache-Control', 'no-store')
  res.setHeader('Content-Type', 'application/json')

  // Only the local UI may trigger SSH; reject cross-origin and non-JSON requests.
  const host = req.headers.host
  const origin = req.headers.origin
  if (!host || !/^(localhost|127\.0\.0\.1):\d+$/.test(host)
    || origin !== `http://${host}`) {
    res.writeHead(403).end(JSON.stringify({ error: 'Local same-origin requests only.' }))
    return
  }

  if (req.method !== 'POST' || req.headers['content-type'] !== 'application/json') {
    res.writeHead(405, { Allow: 'POST' }).end(JSON.stringify({ error: 'Use a JSON POST request.' }))
    return
  }

  try {
    const limit = req.url === '/api/map' ? 1024 : maxMapBytes * 6
    const chunks: Buffer[] = []
    let size = 0
    for await (const chunk of req) {
      size += chunk.length
      if (size > limit) {
        res.writeHead(413).end(JSON.stringify({ error: 'Request too large.' }))
        return
      }
      chunks.push(Buffer.from(chunk))
    }

    const input: unknown = JSON.parse(Buffer.concat(chunks).toString('utf8'))
    if (!input || typeof input !== 'object' || !('hostname' in input)
      || typeof input.hostname !== 'string') {
      res.writeHead(400).end(JSON.stringify({ error: 'A hostname is required.' }))
      return
    }

    if (req.url === '/api/map/save') {
      if (!('confirmation' in input) || input.confirmation !== 'install-and-reboot') {
        res.writeHead(400).end(JSON.stringify({ error: 'Confirm saving and restart before continuing.' }))
        return
      }
      res.end(JSON.stringify(await saveMap(input.hostname, input)))
      return
    }
    res.end(JSON.stringify(await loadMap(input.hostname)))
  } catch (error) {
    const message = error instanceof Error ? error.message : 'Map loading failed.'
    res.writeHead(400).end(JSON.stringify({ error: message }))
  }
}

export function mapApi(): Plugin {
  const middleware = (req: IncomingMessage, res: ServerResponse, next: () => void) => {
    if (!['/api/map', '/api/map/save'].includes(req.url ?? '')) {
      next()
      return
    }

    void handleMap(req, res)
  }

  return {
    name: 'map-api',
    configureServer(server) { server.middlewares.use(middleware) },
    configurePreviewServer(server) { server.middlewares.use(middleware) },
  }
}
