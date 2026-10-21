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
