import { createHash } from 'node:crypto'
import { readFile } from 'node:fs/promises'
import { fileURLToPath } from 'node:url'
import { maxArchiveBytes, packTar } from './archive.ts'
import { checkHost, runRemote } from './ssh.ts'

const toolsRoot = new URL('../../tools/map-maint/', import.meta.url)
const root = '/mnt/data/rockrobo'

export class Maintenance {
  private host: string
  private session: string

  constructor(host: string, session: string) {
    checkHost(host)
    if (!/^\/mnt\/data\/map-[a-zA-Z0-9][a-zA-Z0-9._-]{0,70}$/.test(session)) {
      throw new Error('Configure a fresh /mnt/data/map-* maintenance session.')
    }
    this.host = host
    this.session = session
  }

  async prepare(): Promise<string> {
    const files = Object.fromEntries(await Promise.all(['matching-set.sh', 'operations.sh', 'recover.sh'].map(async name =>
      [name, await readFile(fileURLToPath(new URL(name, toolsRoot)))] as const)))
    const hashes = Object.entries(files).map(([name, data]) => `${createHash('md5').update(data).digest('hex')}  ${name}\n`).join('')
    const output = await runRemote(this.host, `set -eu
umask 077
B=${this.session}
[ "$(id -u)" = 0 ]
grep -q '^ROBOROCK_VERSION=4.3.5_1612$' /etc/os-release
[ -d "$B" ] && [ ! -L "$B" ]
[ ! -e "$B/recovery.ready" ] && [ ! -e "$B/operations.identity" ] && [ ! -e "$B/matching" ]
[ "$(cat "$B/boot-id")" = "$(cat /proc/sys/kernel/random/boot_id)" ]
[ -f "$B/stop.sh" ] && [ ! -L "$B/stop.sh" ]
(cd "$B"; md5sum -c original.md5; md5sum -c inputs.md5) >/dev/null
cmp ${root}/exclude_process.conf "$B/exclude.original"
mkdir -m 700 "$B/editor-tools"
tar -xpf - -C "$B/editor-tools"
(cd "$B/editor-tools"; md5sum -c tools.md5) >/dev/null
printf 'Upload requested.\\n' > "$B/editor-upload"
cat "$B/boot-id"`, packTar({ ...files, 'tools.md5': Buffer.from(hashes) }))
    const boot = output.toString().trim()
    if (!/^[a-f0-9-]{36}$/.test(boot)) throw new Error('Invalid maintenance boot identity.')
    return boot
  }

  async originals(): Promise<Buffer> {
    return this.read('original-exclusions.tar')
  }

  async arm() {
    await runRemote(this.host, `set -eu
B=${this.session}
(trap '' HUP; exec setsid /bin/sh "$B/editor-tools/recover.sh" "$B" approved-once) </dev/null >"$B/recovery.log" 2>&1 &`)
  }

  async ready(): Promise<boolean> {
    const result = await runRemote(this.host, `set -eu
B=${this.session}
[ -f "$B/recovery.ready" ] || { printf waiting; exit 0; }
read -r pid tick deadline < "$B/recovery.ready"
case "$pid:$tick:$deadline" in *[!0-9:]*|:*|*:) exit 1;; esac
[ "$(awk '{print $5 ":" $6 ":" $22}' "/proc/$pid/stat")" = "$pid:$pid:$tick" ]
read -r uptime rest < /proc/uptime
[ "$((deadline - \${uptime%%.*}))" -ge 100 ]
printf ready`)
    return result.toString() === 'ready'
  }

  async start() {
    await runRemote(this.host, `set -eu
B=${this.session}
(trap '' HUP; exec setsid /bin/sh "$B/editor-tools/operations.sh" "$B" approved-once) </dev/null >"$B/operations.log" 2>&1 &`)
  }

  async backupHash(): Promise<string | null> {
    const result = await runRemote(this.host, `set -eu
B=${this.session}
if [ -e "$B/recover.now" ] || [ -e "$B/recovery.finished" ]; then
    tail -c 2048 "$B/operations.log" >&2
    exit 1
fi
[ -f "$B/backup.ready" ] || { printf waiting; exit 0; }
md5sum "$B/untouched-stopped-backup.tar"`)
    const text = result.toString().trim()
    if (text === 'waiting') return null
    if (!/^[a-f0-9]{32}  /.test(text)) throw new Error('Invalid backup checksum.')
    return text.slice(0, 32)
  }

  async backup(): Promise<Buffer> {
    return this.read('untouched-stopped-backup.tar')
  }

  async install(files: Record<string, Buffer>) {
    const names = Object.keys(files)
    const hashes = names.map(name => `${createHash('md5').update(files[name]!).digest('hex')}  ${name}\n`).join('')
    const payload = packTar({ ...files, 'patch.files': Buffer.from(names.join('\n') + '\n'), 'patch.md5': Buffer.from(hashes) })
    await runRemote(this.host, `set -eu
umask 077
B=${this.session}
W=$B/matching
[ -f "$B/backup.ready" ] && [ ! -e "$B/recovery.finished" ]
mkdir -m 700 "$W/patch"
tar -xpf - -C "$W/patch"
mv "$W/patch/patch.files" "$W/patch.files"
mv "$W/patch/patch.md5" "$W/patch.md5"
(cd "$W/patch"; md5sum -c ../patch.md5) >/dev/null
sync
printf 'Patch verified.\\n' > "$W/patch.ready"
printf 'Off-device backup verified.\\n' > "$W/offdevice.verified"
sync`, payload)
  }

  async boot(): Promise<string> {
    const result = await runRemote(this.host, 'cat /proc/sys/kernel/random/boot_id')
    return result.toString().trim()
  }

  async outcome(): Promise<Buffer> {
    return runRemote(this.host, `set -eu
B=${this.session}
[ -f "$B/recovery.finished" ]
[ -f "$B/matching/install.complete" ] && [ ! -e "$B/matching/rollback.started" ] || {
    tail -c 2048 "$B/operations.log" >&2
    exit 1
}
cat "$B/recovery.finished"`)
  }

  async recover() {
    await runRemote(this.host, `set -eu
[ -d ${this.session} ]
printf 'Recovery requested.\\n' > ${this.session}/recover.now`)
  }

  private read(name: string): Promise<Buffer> {
    return runRemote(this.host, `head -c ${maxArchiveBytes + 1} ${this.session}/${name}`, Buffer.alloc(0),
      { bytes: maxArchiveBytes, timeout: 30_000 })
  }
}
