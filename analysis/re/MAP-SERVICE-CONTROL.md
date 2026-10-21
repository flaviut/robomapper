# Stop map hosts without stopping WatchDoge

**Prefer a cold restart: keep application exclusions active in the running WatchDoge, restore the original exclusion file on disk without reloading it, then reboot after the map work.** This avoids the missing-key restart branch and clears tmpfs-backed map buffers. Keep WatchDoge itself running: neither a WatchDoge signal nor its init-script `stop` case is an application-maintenance interface.

This is a static candidate for saved firmware `4.3.5_1612`, not an observed device procedure. Hardware liveness while a host is absent is a separate prerequisite. The saved normal process list marks `rr_loader` and `RoboController` key=1 and `AppProxy` key=0. Embedded loader configuration hosts both navigation and SLAM, **and chassis**, so killing the loader is not a map-only operation. See [the offline workflow](OFFLINE-MAP-WORKFLOW.md) for matching-set backup and replacement boundaries.

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
