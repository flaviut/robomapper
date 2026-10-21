import { readStatus } from './miio.ts'
import { readHttp, runRemote } from './ssh.ts'

type Config = { webserver: { port: number, basicAuth: { enabled: boolean, username: string, password: string } } }

export async function checkReady(host: string) {
  const raw = await runRemote(host, 'head -c 1048576 /mnt/data/valetudo_config.json')
  let config: Config
  try { config = JSON.parse(raw.toString('utf8')) as Config }
  catch { throw new Error('Could not read robot configuration.') }
  const { port, basicAuth } = config.webserver
  const auth = basicAuth.enabled
    ? `Basic ${Buffer.from(`${basicAuth.username}:${basicAuth.password}`).toString('base64')}` : ''
  const timers = await readHttp(host, port, '/api/v2/timers/', auth) as Record<string, { enabled: boolean }>
  if (Object.values(timers).some(timer => timer.enabled)) throw new Error('Turn off scheduled cleaning before saving.')
  const updater = await readHttp(host, port, '/api/v2/updater/state', auth) as { busy: boolean, __class: string }
  if (updater.busy !== false || updater.__class !== 'ValetudoUpdaterIdleState') throw new Error('Wait for the robot update to finish.')
  const scheduled = await runRemote(host, `set -eu
awk '$1 == "Y" && $3 == 1 {print "scheduled"}' /mnt/data/rockrobo/apptimer.cfg
[ ! -s /mnt/data/rockrobo/servertimer.cfg ] || printf scheduled`)
  if (scheduled.length) throw new Error('Turn off scheduled cleaning before saving.')
  const { ota, status } = await readStatus(host)
  if (ota !== 'idle') throw new Error('Wait for the robot update to finish.')
  if (!status || ![1, 2, 3, 8].includes(status.state) || !Number.isInteger(status.battery) || status.battery < 80 ||
    ['error_code', 'in_cleaning', 'in_returning', 'is_locating', 'dock_error_status'].some(key => status[key] !== 0)) {
    throw new Error('The robot must be idle, error-free, and have at least 80% battery.')
  }
  const keys = ['state', 'battery', 'error_code', 'in_cleaning', 'in_returning', 'is_locating', 'dock_error_status']
  return { checked: new Date().toISOString(), ota, status: Object.fromEntries(keys.map(key => [key, status[key]])) }
}
