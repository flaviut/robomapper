# Stop map hosts without stopping WatchDoge

**Prefer a cold restart: keep application exclusions active in the running WatchDoge, restore the original exclusion file on disk without reloading it, then reboot after the map work.** This avoids the missing-key restart branch and clears tmpfs-backed map buffers. Keep WatchDoge itself running: neither a WatchDoge signal nor its init-script `stop` case is an application-maintenance interface.

The [maintenance procedure](../../guides/stopped-backup.md) demonstrates this exclusion-based stop, untouched backup and normal reboot on firmware `4.3.5_1612`. The alternatives discussed below, including warm adoption and booting into exclusions, remain code-derived rather than demonstrated. Hardware liveness while a host is absent is a separate prerequisite. The saved normal process list marks `rr_loader` and `RoboController` key=1 and `AppProxy` key=0. Embedded loader configuration hosts both navigation and SLAM, **and chassis**, so killing the loader is not a map-only operation. See the [matching-set reference](../maps/matching-set.md) and [restore plan](../../guides/matching-set-restore.md) for file boundaries.

## Exclusions and restart behavior established in code

[WatchDoge's parser](../../../analysis/re/evidence/WatchDoge/selected.json), `WdogReloadExclusions` at VA `0x18400`, initially enables every process record and then disables names containing any parsed token. Positive tracked PIDs of matching records receive SIGKILL, and the record PID becomes −1; there is no exit wait, flush acknowledgment or normal-stop MCU-heartbeat adjustment. Disabled records are skipped by [`WdogScanProcesses`](../../../analysis/re/decompiled/WatchDoge/0x00017f68.c), VA `0x17f68`.

Preserve the original file byte-for-byte for rollback; do not replace unrelated exclusions with a newly invented three-name list. The parser processes at most three tokens per line. A final token without a comma is accepted only if its length exceeds three. It does not trim whitespace; empty comma-prefix tokens match every name. Append each new target on its own newline, with no blank comma fields. A file with more than three comma-separated entries on one line can silently omit later entries.

The exclusion IPC message is `0x07030342`. [`WdogWriteExclusions`](../../../analysis/re/evidence/WatchDoge/selected.json), VA `0x1dffc`, truncates `/mnt/data/rockrobo/exclude_process.conf`, writes the payload using `%s`, and closes it. Its caller at `0x1e7a8` selects event 8 only when **C-string `strlen(payload)>2`**. Event 9, selected for length at most two, deletes device/Wi-Fi/configuration data. **Never send empty/short content to clear exclusions.** Packet size is not the selector. Event 8 reloads exclusions and sends reply-like `0x03070343`; that is not proof of process exit or disk durability.

A nonmatching token longer than three characters provides an event-8-compatible empty effective exclusion set, but it must actually match no configured process name. If the original file has other exclusions, send those original exclusions instead; do not discard them. If the original file was absent or empty, prefer the cold-restart route, restoring that original absence/empty file only on disk without IPC.

### Warm adoption is possible, but less attractive

[`WdogFindPid`](../../../analysis/re/decompiled/WatchDoge/0x00017400.c), VA `0x17400`, runs `pidof NAME` through `popen`, parses a positive PID, returns −1 for missing/error and −2 when output contains a space (multiple PIDs). [`WdogAdoptPid`](../../../analysis/re/decompiled/WatchDoge/0x000174b8.c), VA `0x174b8`, stores a single positive result in the record. For −2 it executes `killall -9 NAME` and returns failure.

The scan calls adoption at `0x18240` **before** inspecting the key flag at `0x1824a–0x1824e`. Therefore, starting exactly one surviving instance of each excluded host, using the original launch command/environment, before removing its exclusion can avoid the missing-key path. Re-enabling a still-missing key host instead returns status 2, leading to supervisor teardown/escalation, not AppProxy-style direct restart. Disabled records are not scanned, so a manually started instance can remain present until re-enable. This is a code-supported possibility, not a device-demonstrated startup or map-cache initialization contract. Multiple instances can kill all copies; an initialization failure before adoption can still escalate.

For first map replacement, do not take that extra dependency. Leave the live exclusions alone, restore the original persistent exclusion file without triggering event 8, flush storage, and cold boot. Startup reloads the file and starts enabled records. Leaving maintenance exclusions on disk instead would preserve them across reboot and leave applications stopped.

## Keep the Linux watchdog feeder running

WatchDoge opens `/dev/watchdog`, requests timeout 16, applies the vendor `HWDOG_OPTION`, and starts a feed thread that sleeps eight seconds between feeds. Suspending WatchDoge stops that thread too. Closing the device writes the magic-close byte `V`, but the driver's acceptance of that request and vendor option is not established. Do not stop WatchDoge to obtain a maintenance window. The [watchdog findings](../../../analysis/re/evidence/components/watchdoge.json) trace initialization at `0x1ad68`, timeout/options near `0x1ade0`, feeding at `0x1af4a` and closing at `0x1ac20`.

The chassis heartbeat is separate: [the heartbeat reference](heartbeat.md) follows the producer in `rr_loader`, and the [A14 analysis](a14-heartbeat.md) follows the matching MCU's sentinel handling. Keeping the Linux feeder alive does not replace chassis heartbeat control.

## Vendor orderly stop is a whole-system path

There is an orderly shutdown notification, but it is **not a keep-WatchDoge-running maintenance mode**. `WdogIpcReceiveLoop:0x1e7a8` handles ID `0x0701002f`, copies its shutdown information and queues events 5/6/7 according to the low byte. `WdogMain:0x142e4` takes those events through `0x14856`: it tears down supervision, calls `WdogHwStopFeeder`, acknowledges with `0x01070030`, then follows poweroff/reboot handling. Do not send this message to open a maintenance window. `WdogStopProcesses:0x19ae0` is the internal reverse-order host stop: SIGHUP via `0x191c4`, mode-dependent heartbeat adjustment, bounded disappearance polling and SIGKILL fallback. Exclusion event 8 does not use it.

Similarly, saved `/etc/init/S04wdgenv` has empty `stop` and `restart` arms. `/etc/inittab` respawns WatchDoge. Its signal handler closes the hardware feeder before signal-specific behavior, so do not send WatchDoge SIGHUP/TERM/USR1/USR2 or suspend it. No separate externally callable orderly application-stop/restart service was found that preserves this feeder. A loader SIGHUP is an understood **host** quit request, not an undocumented supervisor signal, but sending it while the key host is still supervised creates a missing-key race. Sending event 8 first already SIGKILLs it. Do not describe that order as graceful shutdown.

## Entry, exit and deployment checks

The demonstrated entry uses the [native helper](../tools/map-maint.md) and [private IPC channel](exclusion-ipc.md). Exclusions prevent supervised respawn, not independent bridge respawn or new remote commands. Identify actual executables, argv, children and command producers, and keep SSH/networking available. WatchDoge is not a command gate for unsupervised Valetudo.

### Command producers

Start stationary, idle and not updating. Disable existing schedules/remote automations for the interval and hold new cleaning, room-edit, restore and firmware-update commands. Confirm the actual normal process list, loader argv/modules and data root match the saved configuration; alternate factory/MT lists require their actual controller names and arguments instead. Keep an administrative shell/recovery route available without opening app/cloud control again.

Valetudo's saved launch is an unsupervised background command in `/mnt/reserve/_root.sh`, itself launched by `rc.local`; no loop is present in the saved reserve script. At the inspected source revision, `backend/index.js` handles SIGTERM/SIGINT with shutdown, and `Valetudo.shutdown` shuts down the scheduler. For a matching deployment, `kill -TERM "$valetudo_pid"` is grounded, **after identifying that PID by executable/argv**. Wait for it to exit. Account for its automatic launch again on each reboot: retain an external command gate and stop the new instance before map work; do not assume it stays stopped across boot. A different deployed version/supervisor needs its own observed launch/stop behavior.

Bound the remaining producers, rather than trying to prove every possible concurrent program absent: stop/exclude the actual `rriot_rr`/other active rriot bridge, `miio_client` and idle updater `SysUpdate`, as well as the three map hosts. This keeps vendor/cloud input and controller timers out of the interval. `rriot_rr` additionally contains `restart_appproxy_process` and `restart AppProxy` strings: treat it as a possible independent AppProxy respawner, not merely an input socket. This string evidence does not establish its exact restart conditions. Do not retain that bridge and rely solely on WatchDoge's AppProxy exclusion. Leave `rrlogd`, WatchDoge and the management network available. No blanket firewall recipe is needed or inferred; preserve the shell path while gating the actual producers.

### Live entry and untested maintenance-boot alternative

Save the **current** exclusion file's bytes, owner/mode and original presence/absence in a separate, private maintenance directory. Do this before native IPC, which truncates the file. Keep that saved file out of the map restore set so restoring an older map cannot silently restore old supervision settings. If the original file is an unexpected symlink/nonregular object, resolve its ownership/path first rather than applying the regular-file examples below.

For a live entry, use the [native helper](../tools/map-maint.md) matching the contract above, with the original exclusions plus required targets. Require event 8, never event 9. This abruptly kills positive tracked map-host PIDs and prevents their supervised respawn. The 63-byte cap can make this inconvenient when also retaining command-producer exclusions. Do not work around it by dropping original exclusions or racing the IPC file write with a second write.

**Simpler sender-free entry: prepare maintenance exclusions on disk, then reboot into them.** This costs an extra boot but uses existing shell/file operations and WatchDoge startup, with no live IPC sender and no IPC payload cap. It is conditional on the same MCU/heartbeat prerequisite, not a bypass for it. With a regular file or original absence established, the following is a candidate shell sequence, **not executed during this investigation**. Every command must succeed before proceeding; do not reuse an existing maintenance directory or overwrite the saved original:

```sh
umask 077
E=/mnt/data/rockrobo/exclude_process.conf
B=/mnt/data/.map-maintenance
mkdir -m 700 "$B"
# If E exists, save its regular-file contents and metadata:
cp -p "$E" "$B/exclude.original"
```

If the original file is absent, omit that `cp` and record absence instead:

```sh
: > "$B/exclude.was-absent"
```

Construct a separate maintenance file, retaining the original bytes and adding one target per line. The names below are from the saved **normal** process list; include any other active bridge/host identified before stopping, not guessed names:

```sh
{
    if [ -f "$B/exclude.original" ]; then cat "$B/exclude.original"; fi
    printf '\nrr_loader\nRoboController\nAppProxy\nrriot_rr\nmiio_client\nSysUpdate\n'
} > "$B/exclude.maintenance"
cp "$B/exclude.maintenance" "$E.next"
chmod 600 "$E.next"
mv "$E.next" "$E"
sync
/sbin/reboot
```

The first inserted newline separates any unterminated original final line; each appended token is longer than three. A blank line is harmless; an empty **comma field** is not. Existing original tokens remain subject to their original parser quirks. Startup at `0x14644` reloads exclusions, refreshes PIDs at `0x1467e`, stops old tracked instances at `0x146a8`, then starts enabled records at `0x146d0` via `WdogStartEnabled:0x171e0`. Excluded records stay excluded in the subsequent scan. WatchDoge startup has its own stop/heartbeat behavior; do not assume this boot yields an independently sustained MCU feeder if the heartbeat prerequisite is unmet.

### Exit and ownership checks

After event 8 or the maintenance boot, confirm WatchDoge is still running and the **actual** writer hosts, their known descendants/extra map consumers and command bridges are gone. `pidof rr_loader`, `pidof RoboController`, `pidof AppProxy`, and the bridge/updater names provide a first name-based observation, not proof of identity or descendant exit. Follow the PIDs/executable paths and children recorded before stopping; inspect their `/proc/PID/task`/`status` while present and establish their exit. The host's threads stop with it; a detached writer thread does not outlive process exit. A zombie has no executing writer threads, but its unreaped parent/remaining children must not be confused with successful whole-tree shutdown.

Once the old loader/UART owner is gone, run the [acknowledged MCU gate](heartbeat.md#supported-userspace-call-without-stopping-watchdoge) before copying or replacing files. Do not send it while chassis still runs: its next raw-zero heartbeat overwrites the sentinel. An init/TTY-lock/send failure means no maintenance entry. After a maintenance reboot, obtain this gate on that boot rather than assuming an earlier request remains effective.

Do not proceed while a process remains in uninterruptible sleep, a surviving child still maps the map libraries/opens the target files, or a writer returns. A reply, a successful FIFO write, tracked PID=−1 and a fixed sleep are insufficient. Do not introduce a universal-concurrency proof: the practical boundary is the observed stopped writer-host set plus gated producers, with no open or mapped target files in any identified surviving consumer. Keep WatchDoge running and avoid reloading exclusions during the window.

For normal return, restore the independently saved original exclusion file **on disk only**, preserving presence, bytes and metadata; do not live-reload missing key hosts. Then sync and use controlled normal reboot as in the [backup guide](../../guides/stopped-backup.md). For proposed writes, keep maintenance exclusions until installation or whole-set rollback is complete; see the [restore plan](../../guides/matching-set-restore.md). These exclusions are not an independent hardware-safe rescue environment.

## What remains device-dependent

The software findings close parser selection, native FIFO framing/coexistence, exclusion reload, adoption order, multi-instance failure and sender-free boot entry. No application-maintenance stop interface preserving the feeder was found; the proposed choices are exclusions or a maintenance boot, not a fabricated vendor service command. The irreducible inputs are the actual process/configuration/command-gate inventory, [hardware liveness](heartbeat.md) with this loader absent, and [cold-start selection](../maps/startup.md) of the intended matching set. These are concrete deployment conditions, not a request to decode every possible writer or map region.

## Scope and provenance

All addresses are virtual addresses, even instruction addresses with Thumb state recorded separately in existing evidence. WatchDoge SHA256 is `3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6`. Saved files under `/home/user/tmp/illegalplainape/analysis/rootfs` and the [writer-host findings](../../../analysis/re/evidence/restore/writer-host/README.md) establish defaults, not the actual running argv, selected process list or device state. These findings came from local static analysis. The later [backup procedure](../../guides/stopped-backup.md) records the device execution.
