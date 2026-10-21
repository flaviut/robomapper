import type { IncomingMessage, ServerResponse } from 'node:http'
import type { Plugin } from 'vite'
import { loadMap } from './map.ts'

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
    let body = ''
    for await (const chunk of req) {
      body += chunk.toString()
      if (Buffer.byteLength(body) > 1024) {
        res.writeHead(413).end(JSON.stringify({ error: 'Request too large.' }))
        return
      }
    }

    const input: unknown = JSON.parse(body)
    if (!input || typeof input !== 'object' || !('hostname' in input)
      || typeof input.hostname !== 'string') {
      res.writeHead(400).end(JSON.stringify({ error: 'A hostname is required.' }))
      return
    }

    const map = await loadMap(input.hostname)
    res.end(JSON.stringify(map))
  } catch (error) {
    const message = error instanceof Error ? error.message : 'Map loading failed.'
    res.writeHead(400).end(JSON.stringify({ error: message }))
  }
}

export function mapApi(): Plugin {
  const middleware = (req: IncomingMessage, res: ServerResponse, next: () => void) => {
    if (req.url !== '/api/map') {
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
