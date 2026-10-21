# Stop map hosts without stopping WatchDoge

**Prefer a cold restart: keep application exclusions active in the running WatchDoge, restore the original exclusion file on disk without reloading it, then reboot after the map work.** This avoids the missing-key restart branch and clears tmpfs-backed map buffers. Keep WatchDoge itself running: neither a WatchDoge signal nor its init-script `stop` case is an application-maintenance interface.

The [maintenance procedure](MAINTENANCE-PROCEDURE.md) demonstrates this exclusion-based stop, untouched backup and normal reboot on firmware `4.3.5_1612`. The alternatives discussed below, including warm adoption and booting into exclusions, remain code-derived rather than demonstrated. Hardware liveness while a host is absent is a separate prerequisite. The saved normal process list marks `rr_loader` and `RoboController` key=1 and `AppProxy` key=0. Embedded loader configuration hosts both navigation and SLAM, **and chassis**, so killing the loader is not a map-only operation. See [the offline workflow](OFFLINE-MAP-WORKFLOW.md) for matching-set backup and replacement boundaries.

## Exclusions and restart behavior established in code

[WatchDoge's parser](decompiled/WatchDoge/0x00018400.c), `WdogReloadExclusions` at VA `0x18400`, initially enables every process record and then disables names containing any parsed token. Positive tracked PIDs of matching records receive SIGKILL, and the record PID becomes −1; there is no exit wait, flush acknowledgment or normal-stop MCU-heartbeat adjustment. Disabled records are skipped by [`WdogScanProcesses`](decompiled/WatchDoge/0x00017f68.c), VA `0x17f68`.

Preserve the original file byte-for-byte for rollback; do not replace unrelated exclusions with a newly invented three-name list. The parser processes at most three tokens per line. A final token without a comma is accepted only if its length exceeds three. It does not trim whitespace; empty comma-prefix tokens match every name. Append each new target on its own newline, with no blank comma fields. A file with more than three comma-separated entries on one line can silently omit later entries.

The exclusion IPC message is `0x07030342`. [`WdogWriteExclusions`](decompiled/WatchDoge/0x0001dffc.c), VA `0x1dffc`, truncates `/mnt/data/rockrobo/exclude_process.conf`, writes the payload using `%s`, and closes it. Its caller at `0x1e7a8` selects event 8 only when **C-string `strlen(payload)>2`**. Event 9, selected for length at most two, deletes device/Wi-Fi/configuration data. **Never send empty/short content to clear exclusions.** Packet size is not the selector. Event 8 reloads exclusions and sends reply-like `0x03070343`; that is not proof of process exit or disk durability.

A nonmatching token longer than three characters provides an event-8-compatible empty effective exclusion set, but it must actually match no configured process name. If the original file has other exclusions, send those original exclusions instead; do not discard them. If the original file was absent or empty, prefer the cold-restart route, restoring that original absence/empty file only on disk without IPC.

### Warm adoption is possible, but less attractive

[`WdogFindPid`](decompiled/WatchDoge/0x00017400.c), VA `0x17400`, runs `pidof NAME` through `popen`, parses a positive PID, returns −1 for missing/error and −2 when output contains a space (multiple PIDs). [`WdogAdoptPid`](decompiled/WatchDoge/0x000174b8.c), VA `0x174b8`, stores a single positive result in the record. For −2 it executes `killall -9 NAME` and returns failure.

The scan calls adoption at `0x18240` **before** inspecting the key flag at `0x1824a–0x1824e`. Therefore, starting exactly one surviving instance of each excluded host, using the original launch command/environment, before removing its exclusion can avoid the missing-key path. Re-enabling a still-missing key host instead returns status 2, leading to supervisor teardown/escalation, not AppProxy-style direct restart. Disabled records are not scanned, so a manually started instance can remain present until re-enable. This is a code-supported possibility, not a device-demonstrated startup or map-cache initialization contract. Multiple instances can kill all copies; an initialization failure before adoption can still escalate.

For first map replacement, do not take that extra dependency. Leave the live exclusions alone, restore the original persistent exclusion file without triggering event 8, flush storage, and cold boot. Startup reloads the file and starts enabled records. Leaving maintenance exclusions on disk instead would preserve them across reboot and leave applications stopped.

## Scope and provenance

All addresses are virtual addresses, even instruction addresses with Thumb state recorded separately in existing evidence. WatchDoge SHA256 is `3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6`. Saved files under `/home/user/tmp/illegalplainape/analysis/rootfs` and the [writer-host findings](evidence/restore/writer-host/README.md) establish defaults, not the actual running argv, selected process list or device state. No robot access, firmware execution, configuration modification, tests, validators or new evidence infrastructure were used.

## Keep the Linux watchdog feeder running

WatchDoge opens `/dev/watchdog`, requests timeout 16, applies the vendor `HWDOG_OPTION`, and starts a feed thread that sleeps eight seconds between feeds. Suspending WatchDoge stops that thread too. Closing the device writes the magic-close byte `V`, but the driver's acceptance of that request and vendor option is not established. Do not stop WatchDoge to obtain a maintenance window. The [watchdog findings](evidence/components/watchdoge.json) trace initialization at `0x1ad68`, timeout/options near `0x1ade0`, feeding at `0x1af4a` and closing at `0x1ac20`.

The chassis heartbeat is separate: [the heartbeat reference](MAP-HEARTBEAT-CONTROL.md) follows the producer in `rr_loader`, and the [A14 analysis](A14-HEARTBEAT.md) follows the matching MCU's sentinel handling. Keeping the Linux feeder alive does not replace chassis heartbeat control.

## Concrete plugin exit: cooperative loops, not a public map-only stop

Focused Thumb disassembly closes the generic-callback edge left by the writer-host report. SLAM `rr_load_plugin:0x6c14` returns the callback table at VA `0x5440c` (file offset `0x4440c`); navigation `rr_load_plugin:0x5f830` returns VA `0x3044f8` (file offset `0x2f44f8`). Both tables have **null slot +0x10**, so neither provides a pre-join stop callback. Their thread and post-join callbacks are:

| Plugin | Thread slot +8 | Post-join slot +0x14 | Directly established behavior |
| --- | --- | --- | --- |
| SLAM | Thumb `0x534d` | Thumb `0x5299` | Loop at `0x537c–0x538e` dispatches messages until `rr_check_quit` is true. Post-join callback sends `0x090907d0`, calls `0x6c48`, then `ReleaseSharedRegion(1)` at `0x530a–0x530c`. |
| Navigation | Thumb `0x63e69` | Thumb `0x61175` | Thread wrapper calls singleton `0x6110c`, then `0x63d10`. Loop at `0x63dc4–0x63dd8` dispatches until `rr_check_quit`; after exit it calls `0x162938` with argument 1. Post-join wrapper tail-calls singleton vtable slot +0x10. |

These establish cooperative host cleanup, not a map-save barrier or a callable maintenance RPC. [`RRPlugin::final:0x19058`](evidence/restore/writer-host/proof/c/0x00019058.c) sets the per-plugin quit flag, wakes waiters, joins the thread, then calls the post-join slot. [`RRLoader::final:0x187fc`](evidence/restore/writer-host/proof/c/0x000187fc.c) joins the timer first, then finalizes **all** plugins, not just map plugins. Loader SIGHUP sets the loader quit flag at +0x9c; it does not select navigation/SLAM independently. No external plugin-unload or map-only shutdown interface is established by these callbacks. Calling a callback address from another process is not an alternative.

The SLAM shutdown notification and shared-region release happen after thread exit, but detached persistence workers elsewhere in the host are not covered by that join. For offline file work, actual host exit remains the useful boundary. Retaining chassis would instead require an independently grounded chassis-only host/configuration; this document does not authorize modifying the embedded plugin set.

Provenance: original tracked `librrslamdrv.so` SHA256 `b48f5f56eb1b2d22abbf727725ea558762337f8f0103229d8da6c1ab6275608a`; `librrnavdrv.so` SHA256 `603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475`. Export entries were read using a private `/tmp` copy made by source-root `retool.py copy`; callback instructions were read directly with pinned LLVM objdump in Thumb mode. The baseline did not identify these callback addresses as separate function entries; failed bounded exports were not treated as evidence. No baseline changes or new function definitions were made.

The timer join is now connected to the loader quit flag: timer init `0x16848` starts Thumb `0x16ce5`; its loop calls `updatetime`, sleeps 2,500 microseconds, then calls `RRLoader::checkQuit:0x18834` at `0x16d02`. That reads +0x9c. Thus SIGHUP can let the timer join advance to plugin cleanup once its current work returns; it is not an unconditional deadlock. `rr_check_quit:0x19164` follows the plugin control's +4 pointer and reads the plugin +0x184 quit byte set by finalization. The exported method named `RRLoader::stop:0x1845c` merely returns 1; its name is not a shutdown API.

## Sending exclusions: existing native API, not miio JSON

The available Valetudo checkout (`/home/user/dev/co/Valetudo`, commit `5d905ec2239dd14bbc11ee3785837562306a508e`) sends Roborock commands through `MiioValetudoRobot.js` and `miio/MiioSocket.js`, using encrypted UDP miio. `RoborockBasicControlCapability.stop()` sends `app_stop`: that stops cleaning, not the application processes. It is not a WatchDoge IPC sender. The saved native `miio_send_line` advertises `Usage: %s msg` and sends a string to a local server; it does not link `libroboipc` or provide the exclusion interface. No generic preinstalled exclusion command was found in the saved rootfs. Do not substitute either tool for the native IPC API.

The native library **does** provide enough framing and lifecycle to specify a small one-shot sender without guessing socket packets. `libroboipc.so` SHA256 is `a7a693c8edd37aa9367f680d2f742ef81f4b8007c97a7720fc02f35ded57a832`. Its `Packet_t` wire representation on this ARM little-endian firmware is 76 bytes:

| Offset | Size | Exclusion request value |
| --- | --- | --- |
| 0 | 4 | Message ID `0x07030342` (destination WatchDog=7, source AppProxy=3) |
| 4 | 4 | Sequence, assigned by native `GetNextSequenceNumber` |
| 8 | 4 | Message size: payload byte count including terminating NUL |
| 12 | 64 | NUL-terminated exclusion file content, remaining bytes zero |

`SendPacket:0x63ec` gets a sequence, forces nonblocking option bit 0, and calls `pDoSendPacket:0x637c`, which writes **all 0x4c bytes**, not just MessageSize. Channel selection is `g_Channels[((id>>16)&255)*17+(id>>24)]`. WatchDoge's `RecvPacket` stack buffer is also 0x4c bytes; it treats the data at +12 as a C string, ignoring MessageSize for file write and event selection. **Keep content at most 63 bytes, with no embedded NUL, and length greater than two.** `SendPacketEx` adds completion/echo machinery; it is not a way to send an arbitrary-sized exclusion file to this receiver.

### Minimal one-shot helper contract

This is an API specification, **not a shipped executable or a command to run**. No helper was built or executed. A target-ABI helper could use the following existing exported functions instead of writing directly to guessed paths:

1. Run with a unique basename/argv[0], such as `map-maint-ipc`, which matches none of `GetProcIndex:0x5530`'s known prefixes. Link/load the matching `libroboipc.so` normally. Its `.init_array` entry at VA `0x1bec8` invokes `DllInit:0x3324`; **do not invoke DllInit again**. It creates the sequence mutex and receive thread. For the unknown name, `DoInitialize` resolves process index 0; the pinned process matrix row and column 0 contain only −1, so no application channels are opened.
2. Call `pChannelOpen(AppProxy=3, WatchDog=7)`, exported as `_Z12pChannelOpen16ProcessAbbrIndexS_`. The pinned matrix has both `[3][7]=1` and `[7][3]=1`. `pChannelOpen:0x5e14` opens existing `/tmp/ApWd` write-only/nonblocking and `/tmp/WdAp` read-only/nonblocking. The saved vendor `opt/rockrobo/scripts/pipes.sh` creates both FIFOs. It does not create or unlink them in this library call. Null is failure; a nonnull handle can still have failed descriptor opens, so send must be checked.
3. **Keep that handle private; do not register it in `g_Channels` and do not call `DoInitialize("AppProxy")`.** The latter would open all AppProxy channels and let this helper's receiver compete with the real AppProxy for its messages. A private handle's reverse read descriptor is never read; merely opening it does not consume another process's reply. The helper's receive thread sees no registered channels from row 0.
4. Prepare the zeroed 76-byte packet above. Call `_Z21GetNextSequenceNumberP8Packet_t` (`0x5a94`) with its address, then `_Z13pChannelWritePvS_ji` (`0x5adc`) as `pChannelWrite(handle, &packet, 76, 0x800)`. Ignore SIGPIPE in the helper so loss of the reader is an error rather than an uncontrolled termination. Require return **76**, not merely nonnegative. This uses the same native channel-write primitive as SendPacket without installing a new consumer for live application traffic. Do not retry blindly after an ambiguous result.
5. Call `_Z13pChannelClosePv` (`0x6110`) on that handle, then exit normally. Close releases local descriptors and allocation, not the FIFO pathname. The library's `.fini_array` entry at VA `0x1bed0` invokes `DllUninit:0x2f64`, cancels/joins its own receive thread and tears down its local state. Do not call DllUninit twice.

This closes channel coexistence at the static API level: no second AppProxy process name, no registration/read of its channels, and no FIFO deletion. The 76-byte FIFO write is one native packet, but a successful write still means only delivery to the pipe. It neither waits for event 8 nor establishes host exit. Local sequence numbers can overlap another sender's numbers; this path requests no echo/completion and does not consume replies. Actual library/ABI/FIFO availability is a deployment observation, not a claim that an unbuilt helper exists on the robot.

For the captured original exclusions `rriot_tuya,rriot_rr`, adding `\nrr_loader\nRoboController\nAppProxy\n` remains below the cap (a pre-existing trailing newline also fits). Add any further command-producer exclusions only if the complete content still fits. **Do not truncate the original file or shorten tokens blindly to make it fit.** When the original plus required targets exceeds 63 bytes, the disk-before-reboot variant below avoids the IPC payload limit entirely.

Provenance: native `SendPacket`/`pDoSendPacket` are already [exported in the flow evidence](evidence/restore/flow/c/libroboipc.so/0x000063ec.c). Constructor, index lookup, channel open/write/close, sequence and destructor were exported by a focused import of the tracked library into the same private baseline copy under `/tmp`; source-root tooling and shared evidence were not changed. Native data matrix is VA `0x1c5bc` (file `0xc5bc`); abbreviation table VA `0x1c48c` (file `0xc48c`) maps indices 3/7 to `Ap`/`Wd`. No internet source searches were used.

## Vendor orderly stop is a whole-system path

There is an orderly shutdown notification, but it is **not a keep-WatchDoge-running maintenance mode**. `WdogIpcReceiveLoop:0x1e7a8` handles ID `0x0701002f`, copies its shutdown information and queues events 5/6/7 according to the low byte. `WdogMain:0x142e4` takes those events through `0x14856`: it tears down supervision, calls `WdogHwStopFeeder`, acknowledges with `0x01070030`, then follows poweroff/reboot handling. Do not send this message to open a maintenance window. `WdogStopProcesses:0x19ae0` is the internal reverse-order host stop: SIGHUP via `0x191c4`, mode-dependent heartbeat adjustment, bounded disappearance polling and SIGKILL fallback. Exclusion event 8 does not use it.

Similarly, saved `/etc/init/S04wdgenv` has empty `stop` and `restart` arms. `/etc/inittab` respawns WatchDoge. Its signal handler closes the hardware feeder before signal-specific behavior, so do not send WatchDoge SIGHUP/TERM/USR1/USR2 or suspend it. No separate externally callable orderly application-stop/restart service was found that preserves this feeder. A loader SIGHUP is an understood **host** quit request, not an undocumented supervisor signal, but sending it while the key host is still supervised creates a missing-key race. Sending event 8 first already SIGKILLs it. Do not describe that order as graceful shutdown.

## Candidate operational sequence

**Hardware prerequisite:** [MAP-HEARTBEAT-CONTROL.md](MAP-HEARTBEAT-CONTROL.md) identifies the candidate gate: after `rr_loader` and its UART ownership are gone, invoke the existing native `rua_keep_mcu_heartbeat(-1)` API and require return 0. The inspected MCU consumer skips missing-heartbeat escalation for that sentinel; installed-image applicability remains a device input. The [native helper](MAINTENANCE-HELPER.md) supplies that invocation and was used in the completed stopped backup. Exclusions alone, including the sender-free maintenance boot below, do not establish heartbeat liveness. Do not enter file maintenance until that invocation succeeds; do not assume the sentinel survives reboot or that the finite value 120 grants 120 seconds. The Linux `/dev/watchdog` feeder remains WatchDoge throughout the maintenance interval. A deliberate reboot ends that interval and runs normal shutdown/startup; it is not a promise that watchdog liveness survives arbitrary boot configurations.

### 1. Gate commands and identify this deployment

Start stationary, idle and not updating. Disable existing schedules/remote automations for the interval and hold new cleaning, room-edit, restore and firmware-update commands. Confirm the actual normal process list, loader argv/modules and data root match the saved configuration; alternate factory/MT lists require their actual controller names and arguments instead. Keep an administrative shell/recovery route available without opening app/cloud control again.

Valetudo's saved launch is an unsupervised background command in `/mnt/reserve/_root.sh`, itself launched by `rc.local`; no loop is present in the saved reserve script. At the inspected source revision, `backend/index.js` handles SIGTERM/SIGINT with shutdown, and `Valetudo.shutdown` shuts down the scheduler. For a matching deployment, `kill -TERM "$valetudo_pid"` is grounded, **after identifying that PID by executable/argv**. Wait for it to exit. Account for its automatic launch again on each reboot: retain an external command gate and stop the new instance before map work; do not assume it stays stopped across boot. A different deployed version/supervisor needs its own observed launch/stop behavior.

Bound the remaining producers, rather than trying to prove every possible concurrent program absent: stop/exclude the actual `rriot_rr`/other active rriot bridge, `miio_client` and idle updater `SysUpdate`, as well as the three map hosts. This keeps vendor/cloud input and controller timers out of the interval. `rriot_rr` additionally contains `restart_appproxy_process` and `restart AppProxy` strings: treat it as a possible independent AppProxy respawner, not merely an input socket. This string evidence does not establish its exact restart conditions. Do not retain that bridge and rely solely on WatchDoge's AppProxy exclusion. Leave `rrlogd`, WatchDoge and the management network available. No blanket firewall recipe is needed or inferred; preserve the shell path while gating the actual producers.

### 2. Preserve exclusions; choose a live or boot entry

Save the **current** exclusion file's bytes, owner/mode and original presence/absence in a separate, private maintenance directory. Do this before native IPC, which truncates the file. Keep that saved file out of the map restore set so restoring an older map cannot silently restore old supervision settings. If the original file is an unexpected symlink/nonregular object, resolve its ownership/path first rather than applying the regular-file examples below.

For a live entry, use the [native helper](MAINTENANCE-HELPER.md) matching the contract above, with the original exclusions plus required targets. Require event 8, never event 9. This abruptly kills positive tracked map-host PIDs and prevents their supervised respawn. The 63-byte cap can make this inconvenient when also retaining command-producer exclusions. Do not work around it by dropping original exclusions or racing the IPC file write with a second write.

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

Construct a separate maintenance file, retaining the original bytes and adding one target per line. The names below are from the saved **normal** process list; include any other active bridge/host established in step 1, not guessed names:

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

### 3. Confirm the actual stopped interval before copying

After event 8 or the maintenance boot, confirm WatchDoge is still running and the **actual** writer hosts, their known descendants/extra map consumers and command bridges are gone. `pidof rr_loader`, `pidof RoboController`, `pidof AppProxy`, and the bridge/updater names provide a first name-based observation, not proof of identity or descendant exit. Follow the PIDs/executable paths and children recorded before stopping; inspect their `/proc/PID/task`/`status` while present and establish their exit. The host's threads stop with it; a detached writer thread does not outlive process exit. A zombie has no executing writer threads, but its unreaped parent/remaining children must not be confused with successful whole-tree shutdown.

Once the old loader/UART owner is gone, run the acknowledged MCU gate above before copying or replacing files. Do not send it while chassis still runs: its next raw-zero heartbeat overwrites the sentinel. An init/TTY-lock/send failure means no maintenance entry. After a maintenance reboot, obtain this gate on that boot rather than assuming an earlier request remains effective.

Do not proceed while a process remains in uninterruptible sleep, a surviving child still maps the map libraries/opens the target files, or a writer returns. A reply, a successful FIFO write, tracked PID=−1 and a fixed sleep are insufficient. Do not introduce a universal-concurrency proof: the practical boundary is the observed stopped writer-host set plus gated producers, with no open or mapped target files in any identified surviving consumer. Keep WatchDoge running and avoid reloading exclusions during the window.

### 4. Back up, replace, and prepare next boot

Only now take the matching-set snapshot and perform the matching-set [backup/restore](MAP-FILE-CONTRACT.md) or bounded [edit](MAP-EDIT-CONTRACT.md). Stopping writers does not complete an interrupted save. Retain original file identities/companions, untouched rollback bytes and the independent supervision backup. Finish every intended replacement and flush storage **before** preparing normal boot. If a copy fails or a writer returns, restore the untouched matching set while still excluded, or remain in the maintenance state; do not enable consumers against a partly replaced set.

Restore the current deployment's original exclusion file **on disk only**, without IPC/reload. For an originally present file:

```sh
cp -p "$B/exclude.original" "$E.next"
mv "$E.next" "$E"
sync
/sbin/reboot
```

For original absence, remove only the maintenance exclusion file instead of sending empty IPC:

```sh
rm "$E"
sync
/sbin/reboot
```

An originally empty file follows the present-file branch. This is safe from event 9 because no IPC selector runs. The live supervisor retains its maintenance exclusion vector until reboot; startup reads the restored original file (or enables all records if absent). Keep the administrative/automation gate in place on the next boot until the intended map is loaded; account for the reserve-script Valetudo relaunch again. Reboot clears the saved `/run/shm`-backed runtime buffers, unlike warm adoption, but does not itself guarantee which map/recovery slot is chosen. File-set and recovery selection are outside this service-control document.

**Recovery discipline:** until the file transaction is complete, leave maintenance exclusions on disk. A power loss then retains the application gate on the next boot, subject to the same boot/hardware prerequisite. Restore original exclusions only after rollback/replacement is complete; there is deliberately no "automatic normal-start anyway" path. Do not restore old device/Wi-Fi/supervision files from a map archive. Once normal operation is established, retain the original supervision backup with the maintenance record rather than deleting the only recovery copy mid-window.

## What remains device-dependent

The software findings close parser selection, native FIFO framing/coexistence, exclusion reload, adoption order, multi-instance failure and sender-free boot entry. No application-maintenance stop interface preserving the feeder was found; the proposed choices are exclusions or a maintenance boot, not a fabricated vendor service command. The irreducible inputs are the actual process/configuration/command-gate inventory, hardware liveness with this loader absent (heartbeat document), and successful cold-start selection of the intended matching map set (file/recovery lane). These are concrete deployment conditions, not a request to decode every possible writer or map region.
