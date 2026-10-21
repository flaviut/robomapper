# Map maintenance: an untouched stopped backup and normal return

**The October 21, 2026 third one-shot attempt acquired an untouched stopped matching set and recovered through normal reboot.** The native MCU operation returned 0 after the full task/descriptor ownership gates. Only then did operations archive the finite map namespace, with presence/absence and metadata, and sync before marking completion. Original supervision exclusions were restored on disk before reboot; normal services, loader UART ownership and quiet docked status returned. No map file was edited, replaced or restored.

The private off-device backup is `/home/user/.local/state/pi/map-backups/map-maint-session-20261021T1158Z/untouched-stopped-backup.tar`: **1,116,160 bytes**, MD5 **`7bd6af71635532868ff47f2cabbd3a05`**, SHA256 **`37fb5d2a3dab0dd85ddd537e3571e957ce517f00c908c68a25dcfdd308129790`**. The robot retains the same archive under `/mnt/data/map-maint-session-20261021T1158Z`. Robot and local MD5 agree. This archive contains `snapshot/files.tar`, the actual namespace, present/absent lists, metadata, saved file hashes and the completion marker. It was not extracted, replayed or used to restore anything. The separate session-record archives are not map backups.

The route below demonstrates service stop, a native transport acknowledgment, untouched acquisition and normal restart—not edited-map import or restoration, and not semantic readback of the MCU sentinel. The earlier two attempts ended in safe refusal; their evidence remains below. The [first session](MAINTENANCE-SESSION.md#approval-and-actual-outcome) lacked task-state evidence. [Why that attempt stopped](WHY-MAINTENANCE-STOPPED.md) explains why executable disappearance alone was insufficient; the second supplied the same-boot zombie/sibling observation needed for this narrow correction.

## Correction and exact completed attempt

The renewed direction authorizes a minimal correction after the second attempt reproduced and identified the refusal. `loader_absent()` still refuses an executable basename of `rr_loader` (including deleted executables). For a matching task `comm`, it now accepts only a positively observed **Z** state when that task's executable lookup failed specifically with `ENOENT` or `ESRCH`. The lookup decision is saved before reading `comm`; unrelated inspection errors, unreadable/unknown states and live states still refuse. The existing stat-state parser is factored into `task_state()` and reused by the unchanged refusal diagnostic. This changes only the task-name guard: device-number descriptor checks still run for that task, and every sibling task is still enumerated. An exited leader is not a process-wide exemption.

The ordinary ARMhf build used `tools/map-maint/build.sh`, the exact saved runtime at `/home/user/tmp/illegalplainape/analysis/rootfs`, existing `/tmp/map-helper-libc-dev` EGLIBC 2.19 headers/start objects, GCC 16.2.0 and binutils 2.46 from the existing Nix store, and Linux 7.2 declarations. The development package SHA256 remained `82328ca2989c3bfd75b40bb0adc282559b1a86711b5619a00b5639f2a339858a`. The new binary is **21,500 bytes**, MD5 `b31d38a722e6b0c9fe1163f75976ce18`, SHA256 `fb75e397eb09c51aa1a0402918fe55c357363be5843e6e7f896e6b7d7d8987f0`; source SHA256 is `637ca1de45ee0082dad6eeeaf429be97ead58365bb07125c1ecbcb8fc7341b0f`. The build did not execute the binary. No tests, suites, validators, emulators or replay were run.

The third attempt was staged dormant at local and robot `/tmp/map-maint-session-20261021T1158Z`, with persistent private records under `/mnt/data/map-maint-session-20261021T1158Z`. The parent read all three exact scripts and source commit `85c00b5`, then explicitly approved **one** attempt with the identities below. Both directories are `0700`; scripts/helper are `0700`, other files `0600`. The newly captured original exclusion bytes, presence and metadata are independent of the old attempt. A private local `original-state.tar` preserves them off-device; it is not a map backup. Staging did not touch the active file. Its original metadata tar MD5 is `e9452c0adf7eb4b26048525a7b960262` and its bytes retain MD5 `e848cdeffe2b0a60a5d3f3e38fd1a2eb`.

At **11:57:56 UTC**, the established read-only queries reported OTA idle, docked state **8**, battery **87%**, and error, cleaning, returning, locating and dock-error fields **0**. Fresh process identities, start ticks, executable/argument identities, executable/library hashes and boot ID were recorded privately. Loader **448**, start **1395**, owns UART links 60/61. Restricted environment observations for loader/controller/AppProxy still place the matching set under `/mnt/data/rockrobo`; `/run/shm` is tmpfs. These observations were refreshed immediately before the approved arming; the boot, process ticks, script/helper hashes, original bytes and original metadata still matched. Admission is OTA idle, source idle **1/2/3 or docked 8**, battery **at least 80%**, and those zero error/activity fields—not a new 90% charging requirement.

The three inspected scripts received explicit GO before launch. They use independent `nohup`/`setsid` recovery with a 120-second uptime deadline established before operations, pinned Valetudo TERM, one full 46-byte event-8 delivery, actual known-host executable disappearance, protected services and one native MCU invocation. Recovery uses TERM only for its verified private operations group, never a force signal or a vendor-service group. On refusal/failure the eight-second same-boot metadata capture precedes immediate recovery without retry. Only native return 0 admits the finite untouched matching-set archive, including presence/absence, DB companions and separate interrupted products, with bounded space and completion only after sync. Recovery records pre/post-restoration metadata, restores originals **on disk only**, then requests ordinary `/sbin/reboot`. No live exclusion-clear request, map writes/replacement, RPC regeneration, MQTT/schedule changes, boot hooks or force reboot are included.

Local and robot staged MD5 values match:

| File | MD5 | SHA256 (local) |
| --- | --- | --- |
| `operations.sh` | `8b8c00514e2cf809d9e98bd87698d31e` | `7af92b37b68dc0986386ecf597fbbb0d684c6953587fd16e7cd8dd8a842584d6` |
| `recover.sh` | `cd4dfc0e6e2aff14be01ddec394952bc` | `4a89fb42c45436f84432f1b8eb79fe5b7651ab6e36432a57ccead0be24a32423` |
| `capture-refusal.sh` | `72dadc3ca7410dd3afca128a1375cded` | `a27ca0d8e3fdc730684e079528335e7a587cbe4865d3153d5476cb5a1e2dc83b` |
| `map-maint` | `b31d38a722e6b0c9fe1163f75976ce18` | `fb75e397eb09c51aa1a0402918fe55c357363be5843e6e7f896e6b7d7d8987f0` |
| `exclusions.content` | `d7133013ea99f643db8ff0be97e9c9f0` | `85005f37d195c8401a5c377ce7ad9329ccc6ea5b1ea543718e9cbae466824ea4` |

The private original-state archive MD5 is `6c4e052fa0cb2b48aacf2953ba6b0a63`, SHA256 `bf70bc10685da347774b663e6b8ce4a504210b06b5babb7dcb2a416478f99dc3`. Restore/edit steps remain unproven and were outside this backup attempt.

### Actual acquisition and recovery

At **12:01:34 UTC**, fresh `get_ota_state`/`get_status` again reported OTA idle, docked **8**, battery **88%**, and zero error/cleaning/returning/locating/dock-error fields. Recovery was then armed as PID **3804**, start tick **66588**, in its own session/group, with uptime deadline **785** (120 seconds after arming). Operations launched once as PID **3820**, start tick **66690**. The service-stop marker is **12:01:36 UTC**. All admission and original-state comparisons passed before TERM to the exact Valetudo instance.

Event-8 delivery succeeded once; known map-host executables disappeared and protected services remained. The single `mcu-disable` invocation returned **0**, stdout reported the framed acknowledgment, and stderr was empty. No retry occurred. The code's full task enumeration and device-number descriptor checks remained in force; there is no process-wide skip for an exited leader.

Only that return admitted acquisition. `snapshot/files.tar` is **1,105,920 bytes**, MD5 **`9d5e20f02b05dc087643a570d4cfd93f`**. The finite namespace and present/absent lists accompany it unchanged. No matching interrupted `.cache`/`.tmp*` products were present, so no `interrupted-work.tar` was created. The scripts reached their final absence/protected-service checks, synced and wrote `backup.complete`. Recovery observed completion before its deadline; no claim is made that the abrupt host stop repaired any earlier interrupted save.

At **12:01:41 UTC**, recovery recorded the active **46-byte** maintenance exclusions. By **12:01:42 UTC**, it had restored the original **19 bytes**, owner/group **0:0**, mode **0644**, and original mtime **11:50:44 UTC**. The restored metadata tar MD5 exactly equals the original metadata tar MD5 `e9452c0adf7eb4b26048525a7b960262`. After sync it requested normal `/sbin/reboot`, without force flags, a live exclusion-clear request or any vendor-service signal beyond the approved Valetudo TERM/exclusion handling. The verified private operations group received TERM.

Bounded SSH observation found a new boot at **12:02:52 UTC**, uptime **62.98 seconds**, well within five minutes. At **12:03:08 UTC**, normal executable/argument identities were observed for Valetudo **371**, WatchDoge **372**, ADB **373**, SSH listener **374**, logging **445**, loader **449**, controller **508**, AppProxy **510**, network manager **512** and miio **514**. Only loader **449** held the observed UART links, descriptors **61/62**. The original exclusion bytes matched, with **0:0 / 0644**; temporary staging was gone. Fresh telemetry at **12:03:13 UTC** reported OTA idle, docked **8**, battery **88%**, and zero error/activity/dock-error fields.

The post-boot exclusion metadata archive has MD5 `809ed8d6c8f1882d6603e7228d434a0c`; the active listing shows mtime **12:02 UTC**, newer than the demonstrated restored mtime. The writer remains unidentified. No write was made to disguise that difference. An attempted optional `stat` observation found that command unavailable; the already captured metadata archives and listings were retained instead.

Only after those return checks were the private backup and recovery records copied off-device. The outer archive preserves the stopped `snapshot/` directory; its hash is acquisition integrity, not a validator or replay result. Persistent private local storage also holds `returned-session-records.tar` (**81,920 bytes**, SHA256 `7edc2fbda6c21f137c2da804c85b9c9462653827c505988a9714387d79c5b10b`) and the independent original-state archive. No backup contents or user secrets were printed or committed. No automatic second attempt, tests, suites, validators, emulators, review agents or nested agents were used.

## What the second attempt established

At **11:50:01 UTC**, fresh permitted `get_ota_state` and `get_status` queries reported OTA `idle`, status **8**, battery **84%**, error `0`, and cleaning, returning, locating and dock-error fields all `0`. The deployed source maps 8 to docked. It maps 1, 2 and 3 to idle: the earlier post-boot status 3 was idle, not an error.

The initial preparation required idle status and battery at least 90%, and refused to arm when it first observed docked status at 82–83%. After reading all three exact scripts, the parent explicitly authorized **one** attempt with idle 1/2/3 **or docked 8**, battery **at least 80%**, OTA idle and all those error/activity fields zero. This was an explicit admission change, not an interpretation that docked means idle. No motion, docking or charging command was sent. Fresh boot, process start ticks, executable/argument identities, original bytes and staged hashes were checked before launch.

Independent recovery was alive at **11:50:14 UTC**, PID **16279**, start tick **1482903**, in its own process group/session, with uptime deadline **14949**: 120 seconds after arming. Operations then started once, PID **16295**, start tick **1483005**. Its pinned Valetudo TERM and application-exclusion steps passed before the single MCU operation. The sender recorded successful delivery, which is a FIFO write rather than a graceful-save acknowledgment.

At **11:50:16 UTC**, the improved helper reported:

```text
Loader still exists; MCU disable refused. PID=449 TID=449 state=Z reason=comm matches rr_loader
```

The capture finished at **11:50:20 UTC**, before requesting recovery and within its eight-second budget. It recorded the original boot ID, process and thread **449**, parent **1**, start tick **1392**, state **Z**, name `rr_loader`, and an unsuccessful executable-link lookup. The entire sibling enumeration contained only task 449, also Z. The subsequent scan across all visible tasks completed without finding a link to either UART device. No arguments, environment or unrelated descriptor targets were recorded. These are contemporaneous observations, not an inference from reused post-boot PID numbers. Descriptor-link observation is not a replacement for the helper's stronger device-number ownership check.

Thus the second attempt identified the blocker: **the then-current helper's name check rejected an exited loader record even when this observation found no executing sibling or UART link**. There was one MCU invocation, return 1, no native heartbeat API call, no UART initialization, no retry and no backup. Neither `backup.complete` nor `snapshot/` exists in that second session.

## Second attempt's recovery and return

At **11:50:21 UTC**, before restoring originals, recovery recorded the 46-byte maintenance exclusions. After restoration at the same timestamp, it recorded the original 19 bytes, owner/group `0:0`, mode `0644`, and modification time **07:43:18 UTC**. The restored-file tar header exactly matches the new original metadata archive. Recovery compared bytes, synced and requested `/sbin/reboot` without a force flag. It did not send a live exclusion-clear request while key hosts were missing.

Bounded SSH reconnection observed a new boot by **11:51:37 UTC**; the robot reported **11:51:36 UTC**, uptime **67.98 seconds** and a different boot ID. At **11:51:50 UTC**, normal executable paths and role-specific arguments were observed for Valetudo 371, WatchDoge 372, ADB 373, SSH listener 374, logging 444, loader 448, controller 507, AppProxy 509, network manager 511 and miio bridge 944. Only loader 448 held the observed UART links, descriptors 60 and 61. The `/tmp` staging directory was gone, as expected after reboot.

Fresh telemetry at **11:51:56 UTC** reported OTA idle, docked status 8, battery **85%**, and error/activity/dock-error fields zero. Original exclusion bytes still matched, with owner/group `0:0` and mode `0644`. A post-boot metadata archive taken at **11:52:16 UTC** records modification time **11:50:44 UTC**, newer than the pre-reboot restored time. The two observations locate the change between restoration and that post-boot capture; **they do not identify its writer**. No write was made to disguise the difference.

Only after normal return were the private session logs, original-state files and diagnostics copied off-device. The local archive is **`/tmp/map-maint-session-20261021T1145Z/returned-session.tar`**, MD5 **`6467d80fea9e3d5a4fab6368eeeee578`**. It is a complete session-record copy, **not a map backup**. The robot retains those records under `/mnt/data/map-maint-session-20261021T1145Z`. No automatic second attempt was made.

## The parts of the procedure that are grounded

These steps explain the observed stop, copy and recovery route. They are **not** a ready-to-run generic script: all completed attempts' boot identities and authorizations are spent, and temporary robot scripts disappeared on reboot. A later run needs new private directories, independent originals, fresh status/identities and explicit approval of its exact scripts.

1. **Identify the current deployment and admit a quiet robot.** Use strict-trust SSH and only the established read-only OTA/status queries. Identify the current service executable paths, restricted role-specific arguments and start ticks rather than recycling old PIDs. Observe UART descriptor links without opening devices. Obtain explicit approval for the actual status/battery admission conditions before arming anything.
2. **Preserve the current supervision settings independently.** Record original presence, raw bytes, owner/group, mode and timestamp in a new private directory outside `rockrobo`, and retain a private off-device copy. The successful third attempt preserved a present-nonempty, 19-byte regular file with mode `0644`; absence and an empty file must not be substituted for it. The raw MD5 was `e848cdeffe2b0a60a5d3f3e38fd1a2eb`; its newly captured metadata tar MD5 was `e9452c0adf7eb4b26048525a7b960262`.
3. **Arm independent recovery first, then stop the identified producers.** The observed method uses `nohup` plus `setsid`, closed stdin and persistent private logs. Recovery establishes its own identity and 120-second uptime deadline before operations starts separately. Operations TERM-stops only the pinned Valetudo process, sends the full approved event-8 content once, waits for the known host executables to disappear, and keeps WatchDoge, logging, SSH and networking running.
4. **Respect the native ownership gate.** Invoke the corrected helper once. On refusal, capture the actual matched process/thread and all siblings within eight seconds, then immediately request recovery without retry. Its positive-Z/missing-executable exception is task-local: live siblings and UART descriptors still refuse. Only native return 0 permits copying the finite matching-set namespace, presence/absence, actual metadata, DB sidecars and separate interrupted products into bounded private space. Sync before the completion marker. The third attempt reached and completed this copy.
5. **Restore exclusions on disk only and reboot normally.** Independent recovery ends only the verified operations process group, records the pre-restoration timestamp, restores the saved exclusion bytes/metadata, compares bytes, syncs and requests normal reboot. Do not warm-reenable missing key hosts through IPC or rerun the reserve launcher. After bounded reconnection, establish a new boot, normal services, ordinary UART ownership, original exclusion bytes/owner/mode and fresh quiet/update status before copying private records off-device.

The complete proposed exclusion content preserved all 19 original bytes and appended `\nrr_l\nRoboC\nAppP\nmiio\nSysU\n`: **46 bytes**, plus the native terminating NUL. Rereading all three process lists confirmed the appended tokens select only the intended loader, controller variants, AppProxy, miio bridge and updater. The original rriot exclusions remain intact. This is event 8, not the destructive event selected by content of two bytes or less. Successful delivery can abruptly kill supervised hosts; it is not proof that a save finished.

The [finite matching-set contract](MAP-FILE-CONTRACT.md) remains the intended untouched-backup boundary, including same-epoch database sidecars, recorded absence and separate interrupted work. The third attempt completed that acquisition path. Map restoration, SQL writes, replacement, recovery RPCs and map regeneration are not part of this demonstrated procedure. The second attempt's refusal was resolved only by the narrow, evidence-grounded correction above; a partial or live copy must not be substituted for the demonstrated stopped backup.

## Second attempt's private scripts and helper (historical)

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

The improved helper was the existing build in `worktrees/map-loader-diagnosis/tools/map-maint/build/map-maint`, not the first attempt's binary. Its source matched the pre-correction worktree byte-for-byte, SHA256 `b3386e9e8dcf8b3ba250bd7c6192f2f472bd52cf3643bc0fe1a991941aa93b2e`; existing source/object/build times and embedded diagnostics agreed. It was not rebuilt, emulated or executed locally. No tests, suites, validators, replay, review agents or nested agents were run. All SSH connections retained `StrictHostKeyChecking=yes`; the old server's key-exchange warning did not prompt an SSH, trust or network change.

## Limits that still matter

Three normal recoveries do not establish an independent rescue channel. ADB has not been exercised, and no pre-boot rescue route or recovery partition has been demonstrated. The 120-second timer bounds the intended wait before recovery, **not** flash flushing, shutdown or return of services. There is no force-reboot fallback or permanent boot hook. Optional metadata capture must not block recovery; failed original-byte restoration must not be hidden by rebooting knowingly wrong exclusions.

The flushed original-state directory and logs survive ordinary reboot; the helper, scripts and running timer under `/tmp` do not. Power loss before restoration can leave maintenance exclusions active at the next boot, with no newly installed mechanism to repair that. WatchDoge must remain running during the stopped interval; no WatchDoge signal belongs to this route.

The [A14 heartbeat analysis](A14-HEARTBEAT.md) supports the intended hold-off, but even native return 0 would acknowledge transport rather than read the sentinel back. The third attempt reached the exchange and received native return 0; that is still not semantic readback. The demonstrated guard defect received only the narrow correction above, not a blanket zombie bypass. The backup is acquired and the robot has returned to normal operation. Edited-map import, restoration, interruption-safe rescue and any further attempt require separate decisions; none is implied by this successful untouched acquisition.
