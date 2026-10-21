# One short service-maintenance session

**Preparation is complete; execution is not authorized.** The helper and two scripts are staged privately, but none has been executed. Recovery is not armed. Valetudo, WatchDoge and all observed vendor hosts remain running. The active exclusion file still has its original 19 bytes, ownership, mode and modification time. The parent must read the exact scripts below and explicitly approve both the service stop and normal controlled reboot before either script is launched.

The only proposed map operation is an untouched stopped backup of the finite namespace in [the file contract](MAP-FILE-CONTRACT.md). No map replacement, restore, SQL change, firmware work, motor/cleaning/docking command, authentication change or network change belongs to this session. [The native helper](MAINTENANCE-HELPER.md) and [A14 heartbeat findings](A14-HEARTBEAT.md) explain why actual loader exit and an acknowledged `-1` request must precede that backup. A sequence acknowledgment is not semantic sentinel readback, and a successful local build is not observed device behavior.

Preparation began on **October 21, 2026, at 04:55 UTC**, from repository commit `58823a4`. All SSH connections used `BatchMode=yes`, `ConnectTimeout=10` and `StrictHostKeyChecking=yes`. No service signal, exclusion request, UART initialization, reboot, live configuration change or map copy was performed. Only the authorized private staging files were written on the robot. No tests, suites, validators, replay, review agents or nested agents were run. The initial inspection found no `stat` command; metadata was instead retained in a byte-preserving tar header and a private numeric-owner listing. Nothing was installed to supply missing tools.

## Latest readiness and process observations

The reusable private script `/tmp/map-vendor-status-native/read_vendor_telemetry.js` performed one authenticated `get_ota_state` followed by one authenticated `get_status`, using the previously obtained Valetudo **2026.05.0**, commit **`4a56bfe876c1f9b298fc5a1b3c8b213ad749ffa1`**, transport source. Credentials stayed in memory and no full reply was printed. At **05:02:03.321 UTC**, OTA state was `idle`. At **05:02:03.369 UTC**, status was `state=2`, `battery=96`, `error_code=0`, `in_cleaning=0`, `in_returning=0`, `in_fresh_state=1`, `is_locating=0`, and `dock_error_status=0`.

The matching source interprets that as idle and discharging, not docked or charging. Physical stillness is not independently measured. [The vendor schedule observation](VENDOR-STATUS.md) found no enabled cleaning schedule; [the Valetudo observation](CURRENT-ROBOT-STATUS.md) found zero timers and MQTT enabled. Those earlier schedule results were not replaced by an invented live schedule read. External automation has not been disabled or held in persistent configuration. Fresh idle/update telemetry is required immediately before any approved arming; actual Valetudo exit and vendor producer exits establish the proposed short command gate, not the present status snapshot.

The following executable/argv identities were read at **04:55:42 UTC**. The same service PIDs and executable paths were still present at **05:01:41 UTC**. The operations script pins these identities and refuses a changed deployment rather than guessing which process to signal.

| Role | PID | Executable | Argv |
| --- | ---: | --- | --- |
| Valetudo | 371 | `/mnt/data/valetudo` | `/mnt/data/valetudo` |
| WatchDoge | 372 | `/opt/rockrobo/watchdog/WatchDoge` | `WatchDoge /opt/rockrobo/watchdog` |
| ADB daemon | 373 | `/usr/bin/adbd` | `/usr/bin/adbd` |
| SSH listener | 374 | `/usr/sbin/dropbear` | `/usr/sbin/dropbear -F` |
| Logging | 444 | `/opt/rockrobo/rrlog/rrlogd` | `rrlogd /opt/rockrobo/rrlog/rrlog.conf` |
| Loader and UART owner | 448 | `/opt/rockrobo/cleaner/bin/rr_loader` | `rr_loader -d` |
| Controller | 507 | `/opt/rockrobo/cleaner/bin/RoboController` | `RoboController` |
| App host | 509 | `/opt/rockrobo/cleaner/bin/AppProxy` | `AppProxy` |
| Network manager | 511 | `/opt/rockrobo/wlan/wlanmgr` | `wlanmgr` |
| Vendor command bridge | 513 | `/opt/rockrobo/miio/miio_client` | `miio_client -d /mnt/data/miio/ -l 1` |

The controller and AppProxy comm names are `robo_main` and `app_main`; checks therefore use `/proc/PID/exe` and argv, not `pidof RoboController` or `pidof AppProxy`. Loader descriptors 61 and 62 were the observed links to `/dev/ttyS2` and `/dev/uart_mcu`. This observation does not replace the helper's complete task/descriptor scan immediately before its later UART call. The selected live environment still gives `RR_ROOT=/opt/rockrobo`, `RR_UDATA=/mnt/data` and `NAV_DYNAMIC_CONFIG_PATH=/mnt/data/rockrobo`.

Dropbear and ADB are independently respawned by init, as is WatchDoge. ADB has not been exercised as a recovery connection. There is no demonstrated second connection or pre-boot rescue route. The existing reserve launcher itself warns that this model has no recovery partition; do not treat working SSH as a promise of repair after a failed boot.

### Valetudo stop and return to normal operation

The exact deployed `backend/index.js` handles TERM by awaiting `Valetudo.shutdown()` and exiting. `backend/lib/Valetudo.js:236–264` stops network helpers, scheduler, MQTT controller, webserver, robot sockets and NTP, with a five-second forced-exit fallback. The prepared script checks PID 371's executable and argv, sends **TERM only to that PID**, and allows eight seconds for actual exit. It does not force-kill Valetudo or claim TERM drains already accepted vendor commands. MQTT and timers are not edited.

The chosen restart is normal controlled reboot, not a warm manual launch. Init runs `/etc/rc.local`, which backgrounds `/mnt/reserve/_root.sh`; that script supplies the existing human-readable ID and launches exactly `VALETUDO_CONFIG_PATH=/mnt/data/valetudo_config.json /mnt/data/valetudo >> /dev/null 2>&1 &`. There is no external Valetudo respawn loop in the inspected configuration. Do not manually rerun `_root.sh`: it also deletes logs and contains a conditional Wi-Fi rewrite. The rewrite condition was false during preparation; both staged scripts check that it remains false before admitting a future window. No launcher, network setting or boot configuration was changed.

### Storage and memory

The root filesystem is read-only squashfs. `/mnt/data` is `/dev/nandl`, ext4, read/write, ordered data. `/tmp` is tmpfs with a 61,440 KiB limit. `/run` and `/run/shm` are tmpfs, and `/dev/shm` points to `/run/shm`; the latter has a 102,400 KiB limit. `/mnt/default` is read-only ext4, `/mnt/reserve` is read/write ext4, and the three audio resource mounts are read-only squashfs. No remount or USB/gadget change was made.

At **05:02:03 UTC**, `/mnt/data` had **56,160 KiB available**, and `/tmp` had **61,384 KiB available**. RAM totaled **250,880 KiB**, with **16,068 KiB free**, **31,108 KiB buffered**, **55,132 KiB cached**, and no swap. The future backup goes to `/mnt/data`, not scarce tmpfs. The operations script requires at least 20 MiB free before stopping, rejects an acquisition larger than 8 MiB of allocated space for either archive, and requires extra headroom before each archive. These are refusal limits, not reserved space or a guarantee against concurrent logs or failing flash. The observed `map/` directory was only 1 KiB and had no additional contents.

## Exact private staging paths and byte identities

The new local private directory is **`/tmp/map-maint-session-20261021T0455Z`**. Its mode is `0700`; data files are `0600` and scripts are `0700`. No credential file was created.

The new robot helper/script directory is **`/tmp/map-maint-session-20261021T0455Z`**, owned by `0:0`, mode `0700`. The separate original-state directory is **`/mnt/data/map-maint-session-20261021T0455Z`**, also `0:0`, mode `0700`, outside `/mnt/data/rockrobo`. Both directory names were checked absent before creation; an existing directory would have caused an abort. No unrelated staging directory was reused.

| File | Local path | Robot path | Matching local/robot MD5 |
| --- | --- | --- | --- |
| Native helper | `/home/user/tmp/illegalplainape/worktrees/map-native-helper/tools/map-maint/build/map-maint` | `/tmp/map-maint-session-20261021T0455Z/map-maint` | `96ca12ccedba100b8905cd69137b4702` |
| Operations script | `/tmp/map-maint-session-20261021T0455Z/operations.sh` | `/tmp/map-maint-session-20261021T0455Z/operations.sh` | `a5d3eb55f29482750440424495b0605f` |
| Independent recovery script | `/tmp/map-maint-session-20261021T0455Z/recover.sh` | `/tmp/map-maint-session-20261021T0455Z/recover.sh` | `d752880be37ad9d8a9f10f7637689e93` |
| Proposed exclusion content | `/tmp/map-maint-session-20261021T0455Z/exclusions.content` | `/tmp/map-maint-session-20261021T0455Z/exclusions.content` | `d7133013ea99f643db8ff0be97e9c9f0` |
| Original raw exclusions | `/tmp/map-maint-session-20261021T0455Z/exclude.original` | `/mnt/data/map-maint-session-20261021T0455Z/exclude.original` | `e848cdeffe2b0a60a5d3f3e38fd1a2eb` |
| Original exclusions with metadata | `/tmp/map-maint-session-20261021T0455Z/original-exclusions.tar` | `/mnt/data/map-maint-session-20261021T0455Z/original-exclusions.tar` | `97f5587ea39fb3b2b34875dc354fc01a` |
| Original presence marker | `/tmp/map-maint-session-20261021T0455Z/original-presence` | `/mnt/data/map-maint-session-20261021T0455Z/original-presence` | `494c720291d4b901c3501ee160402d56` |
| Original metadata listing | `/tmp/map-maint-session-20261021T0455Z/original-metadata.txt` | `/mnt/data/map-maint-session-20261021T0455Z/original-metadata.txt` | `58c27433bc4010aaa07af403e6c13ae3` |

The helper is **17,312 bytes**, staged with mode `0700`, and was not executed even for help. Its source-build SHA256 is **`4ace18a953eff862a6c3815179a6e35ec3e1bf5e4d5e86cd19f39eb2944d51a0`**. The robot lacks SHA256 tooling; its MD5 matched the local source-build binary instead. The script files are `0700`; the exclusion proposal and all original-state files are `0600`. A `0600` staging marker says `STAGED_NOT_ARMED`. No recovery-ready marker, service-touch marker, recovery process or stopped-map snapshot was created.

The original exclusion file is a regular, non-symlink file, owner/group `0:0`, mode `0644`, **19 bytes**, modification time **October 20, 2026, 07:43:19 UTC**. It contains `rriot_tuya,rriot_rr` without a trailing newline. The marker records `present-nonempty`. The tar header preserves its original owner, group, mode and modification time independently of the private raw copy's restrictive mode. Absent, present-empty and present-nonempty are different states: recovery removes the active file only for recorded absence, reinstalls an actual zero-length file for recorded emptiness, and reinstalls the saved bytes for recorded nonempty presence. This session is deliberately pinned to the actual nonempty original and its hashes; a changed original requires new preparation, not substituting an empty stand-in.

### Proposed exclusions select only the intended records

The complete proposal preserves all 19 original bytes and appends exactly `\nrr_l\nRoboC\nAppP\nmiio\nSysU\n`: **46 content bytes**, or 47 including the native terminating NUL. It does not truncate content or select event 9. Nothing has been sent.

All three current process lists were reread. `rr_l` matches only `rr_loader`; `RoboC` matches only `RoboController`, `RoboControllerR` or `RoboControllerM` in their respective lists; `AppP` matches only `AppProxy`; and `miio` and `SysU` match only `miio_client` and `SysUpdate` in the normal list. No new token matches WatchDoge, `rrlogd`, `wlanmgr`, Dropbear or ADB. The original rriot tokens remain intact, including the bridge that can restart AppProxy. No rriot bridge or SysUpdate process appeared in the inventory.

The operations script pins the exact list MD5 values: normal **`9ba3a03761bc37c3453b9cc016f10436`**, FR **`c1d1858f4ccb82da5c5ff0f35d6c689d`**, and MT **`63f9beda621e6f746dce9fc9a0dd1b7b`**. Live IPC and UART library MD5 values also still match the saved target runtime: **`ebc857c5b2bd067cf36b6269d5368ac3`** and **`5c9d6a7b81bc2d9467b6d0f791ae6ace`**. The helper uses an explicit existing library search path with `/usr/lib/arm-linux-gnueabihf` spelled correctly; no library was replaced.

## What the scripts would do after explicit approval

The operations script is specific to this robot, this boot, these PIDs and these original exclusions. Both scripts require UID 0 and the explicit argument `approved-once`. They are not a generic command runner. Read their private local files before approval; the matching robot paths and MD5 values above identify the exact staged versions.

1. Recovery is separately spawned first, in its own session with stdin closed and stdout/stderr redirected privately. It verifies the original-state files, records its PID/start time and an uptime-based deadline, and watches for success, failure or a **120-second deadline**. Operations refuses a missing or stale recovery identity and requires at least 100 seconds left.
2. Operations verifies the helper, libraries, all three process lists, original active bytes, storage headroom, protected services and exact application PIDs/argv. It then marks that a stop may begin, sends TERM to Valetudo, and waits for exit. No persistent MQTT or timer setting is changed.
3. It sends the complete exclusion content through the specific helper once. The helper may abruptly kill tracked hosts; delivery is not a graceful-save or exit acknowledgment. Operations waits up to eight seconds for every known host/bridge/updater executable to disappear, including the renamed controller/AppProxy comm cases, and checks that WatchDoge, logging, SSH and networking remain present. It does not use vendor WatchDoge signals.
4. Only then does it call `map-maint mcu-disable` once. The helper rejects an old loader or UART owner and requires the native call to return 0. Its library initialization configures UART driver state, so this call requires the parent's go even though the inspected path has no flash or motor command. A failure or refusal leads directly to recovery; no backup is started and no helper retry is invented.
5. After acknowledgment, operations creates a private `snapshot/` under the data backup directory. It records the file contract's exact finite namespace, presence, absence and metadata, then archives all present final files together, including the main database and same-epoch sidecars. Present managed-name `.cache`/`.tmp*` work is retained in a separate archive, never promoted or removed. Unexpected symlinks/special files or excessive size cause refusal. No identity/Wi-Fi archive, SQL handle, map decoder, replacement or restore is involved. A complete snapshot is marked only after all required copies and `sync` succeed. The acquisition script stays alive waiting for recovery on both success and handled failure.
6. Recovery responds on the next one-second poll, or at its deadline even if SSH disappears. It kills only the verified, separately created operations process group, not any vendor service group. It restores the original exclusions **on disk only**, using the metadata-preserving tar into a new private subdirectory and a same-filesystem rename. It compares original bytes, syncs, and calls **`/sbin/reboot` without a force flag**. It does not reload exclusions by IPC while key processes are missing. If operations never reached the service-touch marker, recovery exits without restoring or rebooting.

The independent recovery script does not need the helper, an SSH trap, a parent shell, or a fresh connection. If its recorded operations leader has disappeared or been replaced, it avoids an ungrounded group signal and still proceeds to disk-only restoration and normal reboot. Any orphaned acquisition can only be writing the private backup, not an active map set; normal reboot ends that work. An interrupted archive without the completion marker must not be represented as a complete stopped backup.

### Exact future launch method — not run

After the parent has explicitly approved **arming, service stop, UART hold-off and normal reboot**, obtain fresh idle/update status, reread the exact script files, and use a root shell over the strict SSH options above. These are prepared launch commands, not preparation actions already taken:

```sh
umask 077
S=/tmp/map-maint-session-20261021T0455Z
B=/mnt/data/map-maint-session-20261021T0455Z
[ "$(id -u)" = 0 ] || exit 1
[ ! -e "$B/recovery.ready" ] || exit 1
/usr/bin/nohup /usr/bin/setsid /bin/sh "$S/recover.sh" approved-once \
    </dev/null >"$B/recovery.log" 2>&1 &
n=0
while [ ! -s "$B/recovery.ready" ]; do
    n=$((n + 1))
    [ "$n" -le 5 ] || exit 1
    sleep 1
done
/usr/bin/nohup /usr/bin/setsid /bin/sh "$S/operations.sh" approved-once \
    </dev/null >"$B/operations.log" 2>&1 &
```

`nohup`, `setsid`, `/bin/sh` and their paths were observed on the target; no launch experiment was made. Separate sessions, ignored SSH hangup, closed stdin and redirected output let both jobs continue without the SSH connection. The operations script itself checks that its process-group and session IDs equal its PID, as does recovery. No timer has been armed now. This is a one-shot job for the current boot, not a boot hook, installed service or reboot loop. Once launched, recovery is intentionally not canceled by simply dropping SSH.

## Time budget, fallback and remaining limits

The **planned service-off work budget is at most 120 seconds from recovery arming**, which precedes any stop. On ordinary scheduling, deadline polling and operations-group termination add about two seconds before disk restoration, flushing and the normal reboot request. Success or a handled failure asks for recovery earlier. The parent must separately approve that reboot before this job is armed; there is no force-reboot fallback and no attempt to warm-start missing key hosts.

There is **no measured bound on target `sync`, flash latency, normal shutdown or boot time**. Therefore approximately 122 seconds plus restoration/flush time is the planned maximum before requesting reboot, not a proven maximum until all services return. A hard total service-off bound cannot honestly be promised from preparation. The helper has not been exercised on this robot; neither an acknowledged hold-off nor a successful recovery interval has been observed. Disk corruption, recovery-process failure, an uninterruptible kernel task or a failed boot can defeat this software fallback. A restoration/metadata/byte-comparison failure stops recovery rather than rebooting with knowingly wrong exclusions. These are limits for the parent's explicit decision, not reasons to add a persistent boot mechanism or take extra device risks.

During the proposed stopped interval, WatchDoge and its Linux watchdog feeding remain alive. The ordinary reboot deliberately ends that interval and follows normal init shutdown/startup. No synthetic heartbeat re-enable is sent; normal chassis startup replaces the request. No sentinel is assumed to survive an MCU reset. The A14 source supports the sentinel branch, while the UART reply remains a transport sequence acknowledgment only.

The original-state backup under `/mnt/data` and the independent private local copy outlive the SSH connection; the data copy survives an ordinary reboot once written to storage. The helper, scripts and running timer under `/tmp` do **not** survive reboot or power loss. No job will automatically restore exclusions after power loss. If power disappears before original exclusions are restored, durable maintenance exclusions may leave application hosts disabled on the next boot; if original exclusions have already been restored, normal startup may resume them. There is no newly installed boot gate or demonstrated rescue connection to repair that automatically. Unflushed staging writes are not promised durable against abrupt power loss.

No active map file will be replaced in this session, so normal startup cannot encounter a partially installed replacement set. Abruptly stopping a host can still interrupt a pre-existing save; a complete stopped copy preserves the actual bytes and any interrupted work, not a claim that those bytes describe a logically perfect historical save. Only a fully completed private archive should later be copied off-device, without printing its contents. Normal return should be observed before accepting success; do not issue a map recovery RPC, cleaning, docking or firmware command to make it look successful.

## Approval checkpoint

The repo document is the preparation record; the private scripts, original-state archive and matching MD5 identities are the exact proposed execution inputs. The external preparation report is an additional handoff, not a replacement for this file. The next action is for the parent to read both scripts and authorize or reject the bounded attempt, including its controlled reboot and the stated unmeasured return-to-service time. Until that explicit decision, leave services, active exclusions, UART and recovery unmodified.
