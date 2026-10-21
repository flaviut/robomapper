# Map maintenance: what works, and where to stop

**A stopped map backup has not yet worked on this robot.** The first service-stop attempt delivered the exclusion request, but the native helper still found a loader task and refused to open UART. Independent recovery restored the original exclusion bytes and normal reboot brought the services back. That is a demonstrated recovery, not a demonstrated maintenance window. No map files have been edited or restored.

A second, diagnostic attempt is now privately staged but **has not been armed or run**. Its current admission conditions are not met: at **October 21, 2026, 11:46:52 UTC**, the permitted read-only queries reported OTA `idle`, status `8`, battery **83%**, error `0`, and cleaning, returning, locating and dock-error fields all `0`. The deployed source maps status 8 to docked, not idle. The required idle state and battery of at least 90% must both be established before any service stop. No docking, motion or charging command was sent to change that result.

The earlier post-boot status `3` was idle. The deployed source also maps `1` and `2` to idle; a gate that accepts only `2` would incorrectly reject that earlier observation. A fresh status is still required immediately before any approved launch.

## The unresolved loader check

The first attempt's shell saw no loader executable, but the helper's broader check still found a loader identity. The old log did not record which task caused that refusal. An already-exited task awaiting collection, an exited main thread with other threads still alive, and a genuinely surviving loader are different situations. The missing same-boot observation prevents choosing between them. [Why the attempt stopped](WHY-MAINTENANCE-STOPPED.md) explains the difference without treating a possible zombie as an established diagnosis.

The improved helper reports the offending process PID, thread TID, state and whether the executable basename or task name matched. **Its refusal rules are unchanged.** This preparation uses the existing diagnostic build from `worktrees/map-loader-diagnosis/tools/map-maint/build/map-maint`, not the old helper. Its source matches this worktree byte-for-byte (source SHA256 `b3386e9e8dcf8b3ba250bd7c6192f2f472bd52cf3643bc0fe1a991941aa93b2e`); the existing object/build times and embedded diagnostic strings agree with that source revision. The ARM binary was neither executed locally nor rebuilt.

If the helper refuses again, the prepared script first records the reported process/thread, parent, start ticks, state, executable-link result, every available sibling's state/name/executable, and UART descriptor links. It never records process arguments, environment or unrelated descriptor targets. Observation has an eight-second budget and records when that budget prevents a complete scan. The independent recovery deadline remains authoritative. There is no UART retry, zombie exemption, guard bypass or backup after refusal.

## What is prepared for this boot

Fresh inspection at **11:43:32 UTC** identified Valetudo 371, WatchDoge 372, ADB 373, the SSH listener 374, logging 445, loader 449, controller 508, AppProxy 510, network manager 512 and miio bridge 514. Their executable paths and restricted role-specific arguments matched normal operation. Start ticks are pinned in the operations script; the scripts also refuse a different boot ID. These are new observations, not PIDs copied from the first attempt. Only loader 449 held the observed `/dev/ttyS2` and `/dev/uart_mcu` links, at descriptors 60 and 61. The helper will independently inspect all tasks before any UART operation.

All three live process-list hashes and both vendor-library hashes still match the earlier [session record](MAINTENANCE-SESSION.md). Rereading the lists confirmed that the appended tokens select only the intended loader, controller variants, AppProxy, miio bridge and updater. The full proposed content preserves all 19 original bytes and appends `\nrr_l\nRoboC\nAppP\nmiio\nSysU\n`: 46 content bytes, safely selecting event 8 rather than the destructive short-content event 9. No content has been sent in this preparation.

The new private local directory is `/tmp/map-maint-session-20261021T1145Z`. The matching robot script directory has the same path; the independent original-state directory is `/mnt/data/map-maint-session-20261021T1145Z`, outside `rockrobo`. All three directories are mode `0700`. Scripts and helper are `0700`; original-state files and proposed content are `0600`. Nothing reuses old session markers. Local originals were copied privately over strict-trust SSH after the target's absent SFTP server prevented the initial SCP transfer; no SSH, network or authentication setting was changed.

The **current** exclusion file was preserved before staging the proposed content. It is present and nonempty, 19 bytes, owner/group `0:0`, mode `0644`, with tar-recorded modification time **October 21, 2026, 07:43:18 UTC**. Its raw-copy MD5 is `e848cdeffe2b0a60a5d3f3e38fd1a2eb`; the new metadata-preserving tar MD5 is `bc5cdd2e73610049925c68cf78f70410`. The saved presence marker distinguishes this from an absent or empty original. Both copies exist locally and on `/mnt/data`. The older session's archive is not the restoration source for this attempt.

The following identities match locally and on the robot. The parent must read these exact local scripts and explicitly authorize one attempt before any recovery timer or service operation starts.

| File under the new local/robot script directory | MD5 |
| --- | --- |
| `operations.sh` | `bd234ce7b61a15eabf7604356cef7b1c` |
| `recover.sh` | `5d9b876a786f28280ec84331f39e3788` |
| `capture-refusal.sh` | `265507a606198a2570df44058a5ed7d2` |
| `map-maint` | `d9a7496e370bb6a5f841b525e85513aa` |
| `exclusions.content` | `d7133013ea99f643db8ff0be97e9c9f0` |

Their local SHA256 values are:

```text
operations.sh       e77b2ca70fcb81c7173acc9220a5223a24b38d1a580446b72dd4ecb8faa94a10
recover.sh          ed6fb807dc51e78523b5bbbd893f37e6554b8eefc1a255137eb036646db71fcb
capture-refusal.sh  4e001173ce351abfca43e74625fcf0be50bba59e9129a693d1a41e42f47ed97d
map-maint           5458fe2b5721a31e03bb51da444e20ac6b9f9d24b4053fbcfad76e9fccb34b05
```

At **11:46:51 UTC**, the robot still had no recovery-ready marker, operations identity, service-touch marker or snapshot directory. The original active exclusion bytes still matched. There was no active configuration write, service signal, UART access or reboot.

## The proposed one-shot sequence — not yet demonstrated

Use the prior [session's independent recovery arrangement](MAINTENANCE-SESSION.md#prepared-procedure-approved-for-one-attempt), but never reuse its old scripts or authorization. The newly staged scripts retain the following order:

1. Establish fresh read-only idle/no-error/no-activity status, OTA idle and battery at least 90%. Recheck this boot, executable/argument identities, start ticks, original exclusions and all pinned hashes. A changed deployment requires fresh preparation, not a guessed replacement PID.
2. Only after explicit parent approval, start recovery first with `nohup` and `setsid`, closed stdin and private persistent logs. Confirm its identity and 120-second uptime deadline before launching operations in its own session.
3. Operations sends TERM only to the identified Valetudo process and waits for exit. It then sends the complete event-8 content once, waits for the known application executables to disappear, and checks that WatchDoge, logging, SSH and networking remain alive. Delivery does not acknowledge host cleanup or a completed save.
4. Invoke the improved `mcu-disable` once. A refusal triggers the bounded same-boot capture and then immediate recovery. Only native API return **0** permits an untouched backup of the [finite matching set](MAP-FILE-CONTRACT.md), including present database sidecars and separately retained interrupted work. No map restore, SQL write, map decoding or replacement is included.
5. On success, failure or deadline, independent recovery ends only the verified operations process group. It records the timestamp and active exclusion metadata **before** restoring the original exclusions on disk only. It compares restored bytes, records the post-restoration metadata, syncs and requests a normal reboot. It sends no live exclusion-clear message while key hosts are missing.
6. After bounded SSH reconnection, observe a new boot, normal service executable/argument identities, original exclusion bytes/owner/mode, ordinary loader UART ownership, and fresh read-only idle/update status. Copy persistent logs and diagnostic metadata privately off-device. Call an archive a stopped backup only if its completion marker and all required files survived; an interrupted or missing snapshot is not a backup.

The new recovery script also records a tar header after restoration so its timestamp can be compared with a post-boot observation. A changed timestamp alone does not identify a writer. Optional diagnostic-recording failure does not prevent the established restore/reboot path; a failed original-byte restoration still stops rather than knowingly rebooting with wrong exclusions.

## Recovery limits

The first attempt demonstrated a normal reboot returning services, not a rescue channel independent of Linux. ADB has not been exercised; no pre-boot recovery route or recovery partition has been demonstrated. The 120-second timer bounds the intended wait before recovery, **not** flash flushing, shutdown or return of services. No force reboot or permanent boot hook is installed.

The original bytes and logs under `/mnt/data` survive an ordinary reboot once flushed; the helper, scripts and running timer under `/tmp` do not. Power loss before disk-only restoration can leave maintenance exclusions active on the next boot. No new automatic mechanism repairs that condition. WatchDoge must remain running throughout the service-off interval, and no WatchDoge signal is part of this procedure.

The [A14 heartbeat findings](A14-HEARTBEAT.md) explain the intended hold-off and its limits. Even an API return of 0 would acknowledge a transport exchange, not read the sentinel back. Until an admitted attempt actually passes that gate and produces a complete archive, the practical maintenance instruction is to retain normal operation and these originals, not edit map files behind a refused guard.
