# Map maintenance: the stop works, but the backup gate still refuses

**The application-stop request and normal reboot recovery worked; a stopped map backup did not.** On October 21, 2026, the second one-shot attempt stopped Valetudo, delivered the application exclusions and passed the executable-absence checks. The improved helper then refused a remaining loader task. Same-boot evidence showed one zombie task—an exited task awaiting collection—with no surviving sibling and no observed UART descriptor links. The unchanged guard still rejects that task name, so the helper never initialized UART or requested MCU heartbeat hold-off. No map archive was started, and no map files were edited or restored.

Recovery restored the original exclusions on disk and requested normal reboot. The robot returned with its normal services, ordinary loader UART ownership, docked status, no reported activity or error, and OTA idle. **Do not bypass the refusal or treat the diagnostic archive as a map backup.** A complete maintenance procedure still needs an explicitly approved way to handle this demonstrated remaining task without admitting a live loader or UART owner.

The [first session](MAINTENANCE-SESSION.md#approval-and-actual-outcome) also recovered normally but lacked the task evidence. [Why that attempt stopped](WHY-MAINTENANCE-STOPPED.md) explains why executable disappearance alone could not answer whether threads remained alive. This second attempt supplies that missing observation; it does not change the helper's rules.

## What the second attempt established

At **11:50:01 UTC**, fresh permitted `get_ota_state` and `get_status` queries reported OTA `idle`, status **8**, battery **84%**, error `0`, and cleaning, returning, locating and dock-error fields all `0`. The deployed source maps 8 to docked. It maps 1, 2 and 3 to idle: the earlier post-boot status 3 was idle, not an error.

The initial preparation required idle status and battery at least 90%, and refused to arm when it first observed docked status at 82–83%. After reading all three exact scripts, the parent explicitly authorized **one** attempt with idle 1/2/3 **or docked 8**, battery **at least 80%**, OTA idle and all those error/activity fields zero. This was an explicit admission change, not an interpretation that docked means idle. No motion, docking or charging command was sent. Fresh boot, process start ticks, executable/argument identities, original bytes and staged hashes were checked before launch.

Independent recovery was alive at **11:50:14 UTC**, PID **16279**, start tick **1482903**, in its own process group/session, with uptime deadline **14949**: 120 seconds after arming. Operations then started once, PID **16295**, start tick **1483005**. Its pinned Valetudo TERM and application-exclusion steps passed before the single MCU operation. The sender recorded successful delivery, which is a FIFO write rather than a graceful-save acknowledgment.

At **11:50:16 UTC**, the improved helper reported:

```text
Loader still exists; MCU disable refused. PID=449 TID=449 state=Z reason=comm matches rr_loader
```

The capture finished at **11:50:20 UTC**, before requesting recovery and within its eight-second budget. It recorded the original boot ID, process and thread **449**, parent **1**, start tick **1392**, state **Z**, name `rr_loader`, and an unsuccessful executable-link lookup. The entire sibling enumeration contained only task 449, also Z. The subsequent scan across all visible tasks completed without finding a link to either UART device. No arguments, environment or unrelated descriptor targets were recorded. These are contemporaneous observations, not an inference from reused post-boot PID numbers. Descriptor-link observation is not a replacement for the helper's stronger device-number ownership check.

Thus the specific blocker is now known: **the helper's name check rejects an exited loader record even when this observation finds no executing sibling or UART link**. Its refusal remains intact. There was one MCU invocation, return 1, no native heartbeat API call, no UART initialization, no retry and no backup. Neither `backup.complete` nor `snapshot/` exists.

## Recovery and return to normal operation

At **11:50:21 UTC**, before restoring originals, recovery recorded the 46-byte maintenance exclusions. After restoration at the same timestamp, it recorded the original 19 bytes, owner/group `0:0`, mode `0644`, and modification time **07:43:18 UTC**. The restored-file tar header exactly matches the new original metadata archive. Recovery compared bytes, synced and requested `/sbin/reboot` without a force flag. It did not send a live exclusion-clear request while key hosts were missing.

Bounded SSH reconnection observed a new boot by **11:51:37 UTC**; the robot reported **11:51:36 UTC**, uptime **67.98 seconds** and a different boot ID. At **11:51:50 UTC**, normal executable paths and role-specific arguments were observed for Valetudo 371, WatchDoge 372, ADB 373, SSH listener 374, logging 444, loader 448, controller 507, AppProxy 509, network manager 511 and miio bridge 944. Only loader 448 held the observed UART links, descriptors 60 and 61. The `/tmp` staging directory was gone, as expected after reboot.

Fresh telemetry at **11:51:56 UTC** reported OTA idle, docked status 8, battery **85%**, and error/activity/dock-error fields zero. Original exclusion bytes still matched, with owner/group `0:0` and mode `0644`. A post-boot metadata archive taken at **11:52:16 UTC** records modification time **11:50:44 UTC**, newer than the pre-reboot restored time. The two observations locate the change between restoration and that post-boot capture; **they do not identify its writer**. No write was made to disguise the difference.

Only after normal return were the private session logs, original-state files and diagnostics copied off-device. The local archive is **`/tmp/map-maint-session-20261021T1145Z/returned-session.tar`**, MD5 **`6467d80fea9e3d5a4fab6368eeeee578`**. It is a complete session-record copy, **not a map backup**. The robot retains those records under `/mnt/data/map-maint-session-20261021T1145Z`. No automatic second attempt was made.

## The parts of the procedure that are grounded

These steps explain the observed stop-and-recover route. They are **not** a ready-to-run generic script: this attempt's boot identities and authorization are spent, and its temporary robot scripts disappeared on reboot.

1. **Identify the current deployment and admit a quiet robot.** Use strict-trust SSH and only the established read-only OTA/status queries. Identify the current service executable paths, restricted role-specific arguments and start ticks rather than recycling old PIDs. Observe UART descriptor links without opening devices. Obtain explicit approval for the actual status/battery admission conditions before arming anything.
2. **Preserve the current supervision settings independently.** Record original presence, raw bytes, owner/group, mode and timestamp in a new private directory outside `rockrobo`, and retain a private off-device copy. This attempt preserved a present-nonempty, 19-byte regular file with mode `0644`; absence and an empty file must not be substituted for it. The raw MD5 was `e848cdeffe2b0a60a5d3f3e38fd1a2eb`; the newly captured metadata tar MD5 was `bc5cdd2e73610049925c68cf78f70410`.
3. **Arm independent recovery first, then stop the identified producers.** The observed method uses `nohup` plus `setsid`, closed stdin and persistent private logs. Recovery establishes its own identity and 120-second uptime deadline before operations starts separately. Operations TERM-stops only the pinned Valetudo process, sends the full approved event-8 content once, waits for the known host executables to disappear, and keeps WatchDoge, logging, SSH and networking running.
4. **Respect the native ownership gate.** Invoke the improved helper once. On refusal, capture the actual matched process/thread and all siblings before immediately requesting recovery. Do not ignore a name match merely because one task is Z; a different attempt could have live sibling threads or a remaining owner. This attempt stopped here. No untouched map copy is allowed unless the native operation actually returns 0.
5. **Restore exclusions on disk only and reboot normally.** Independent recovery ends only the verified operations process group, records the pre-restoration timestamp, restores the saved exclusion bytes/metadata, compares bytes, syncs and requests normal reboot. Do not warm-reenable missing key hosts through IPC or rerun the reserve launcher. After bounded reconnection, establish a new boot, normal services, ordinary UART ownership, original exclusion bytes/owner/mode and fresh quiet/update status before copying private records off-device.

The complete proposed exclusion content preserved all 19 original bytes and appended `\nrr_l\nRoboC\nAppP\nmiio\nSysU\n`: **46 bytes**, plus the native terminating NUL. Rereading all three process lists confirmed the appended tokens select only the intended loader, controller variants, AppProxy, miio bridge and updater. The original rriot exclusions remain intact. This is event 8, not the destructive event selected by content of two bytes or less. Successful delivery can abruptly kill supervised hosts; it is not proof that a save finished.

The [finite matching-set contract](MAP-FILE-CONTRACT.md) remains the intended untouched-backup boundary, including same-epoch database sidecars, recorded absence and separate interrupted work. That acquisition path was **not reached** here. Map restoration, SQL writes, replacement, recovery RPCs and map regeneration are not part of this demonstrated procedure. A later proposal must resolve the actual refusal first, rather than quietly weakening the helper or calling a partial copy a backup.

## Exact private scripts and helper

The local directory `/tmp/map-maint-session-20261021T1145Z` retains the approved files and returned records. The robot used the same temporary path and the separate data directory above. All session directories were `0700`; scripts/helper were `0700`, other saved files `0600`. Local and robot MD5 identities matched before arming:

| File | MD5 |
| --- | --- |
| `operations.sh` | `bd234ce7b61a15eabf7604356cef7b1c` |
| `recover.sh` | `5d9b876a786f28280ec84331f39e3788` |
| `capture-refusal.sh` | `265507a606198a2570df44058a5ed7d2` |
| `map-maint` | `d9a7496e370bb6a5f841b525e85513aa` |
| `exclusions.content` | `d7133013ea99f643db8ff0be97e9c9f0` |

Local SHA256 identities are:

```text
operations.sh       e77b2ca70fcb81c7173acc9220a5223a24b38d1a580446b72dd4ecb8faa94a10
recover.sh          ed6fb807dc51e78523b5bbbd893f37e6554b8eefc1a255137eb036646db71fcb
capture-refusal.sh  4e001173ce351abfca43e74625fcf0be50bba59e9129a693d1a41e42f47ed97d
map-maint           5458fe2b5721a31e03bb51da444e20ac6b9f9d24b4053fbcfad76e9fccb34b05
```

The improved helper was the existing build in `worktrees/map-loader-diagnosis/tools/map-maint/build/map-maint`, not the first attempt's binary. Its source matched this worktree byte-for-byte, SHA256 `b3386e9e8dcf8b3ba250bd7c6192f2f472bd52cf3643bc0fe1a991941aa93b2e`; existing source/object/build times and embedded diagnostics agreed. It was not rebuilt, emulated or executed locally. No tests, suites, validators, replay, review agents or nested agents were run. All SSH connections retained `StrictHostKeyChecking=yes`; the old server's key-exchange warning did not prompt an SSH, trust or network change.

## Limits that still matter

Two normal recoveries do not establish an independent rescue channel. ADB has not been exercised, and no pre-boot rescue route or recovery partition has been demonstrated. The 120-second timer bounds the intended wait before recovery, **not** flash flushing, shutdown or return of services. There is no force-reboot fallback or permanent boot hook. Optional metadata capture must not block recovery; failed original-byte restoration must not be hidden by rebooting knowingly wrong exclusions.

The flushed original-state directory and logs survive ordinary reboot; the helper, scripts and running timer under `/tmp` do not. Power loss before restoration can leave maintenance exclusions active at the next boot, with no newly installed mechanism to repair that. WatchDoge must remain running during the stopped interval; no WatchDoge signal belongs to this route.

The [A14 heartbeat analysis](A14-HEARTBEAT.md) supports the intended hold-off, but even native return 0 would acknowledge transport rather than read the sentinel back. This attempt never reached that exchange. The remaining task is now a narrowly identified guard-policy decision, not an unexplained live loader: retain the current refusal until that decision is separately approved and implemented. The robot should remain in normal operation meanwhile.
