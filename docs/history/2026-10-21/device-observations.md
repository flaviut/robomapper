# Device observations for offline map maintenance

> Historical record, retained as written. Later findings supersede some conclusions. Do not reuse its PIDs, staging paths or launch commands. See the [history index](../README.md) and [demonstrated backup procedure](../../guides/stopped-backup.md).

The running S7 matches the planned Linux process, library and map-file layout, but its saved MCU version is **STM32 A14.G1, M4.0.1**, not the preferred A3.G1/M4.0.2 package name. The full heartbeat-loss consumer was previously inspected for A3.G1; the A14.G1 comparison covered the heartbeat value conversion, not that complete consumer. The next useful step is to establish the A14.G1 behavior locally and prepare the native caller before considering a service stop.

These observations were collected through read-only SSH to `root@valetudo-illegalplainape.local` on **October 21, 2026, 04:20–04:26 UTC**. Every connection used `BatchMode=yes`, `ConnectTimeout=10` and `StrictHostKeyChecking=yes`. No service, supervision file, map file, mount or boot setting was changed. No UART, watchdog or flash device was opened, and no robot command or firmware helper was executed. Ordinary SSH logging and filesystem access-time effects were not suppressed.

## MCU evidence and its limits

`/run/shm/mcu_version` is a 57-byte regular file owned by `0:0`, mode `0644`, dated October 20 at 07:43, close to this boot. Its version label identifies **STM32, A14.G1, M4.0.1, release 20221102-132632**. This is saved runtime version evidence, rather than merely an image available in the firmware directory. It points to the packaged A14.G1 candidate discussed in [heartbeat control](../../reference/services/heartbeat.md), but it does not establish the exact bytes currently flashed.

No numeric MCU ID/JTAG or numeric gyro ID was recovered. `G1` is part of the saved version label; it is not a fresh gyro identification result. `/run/uart_test` was empty. Bounded watchdog and loader log excerpts, followed by targeted identification-pattern searches in those files, contained no MCU identification or upgrade result. The loader's open `MCU_normal.log` descriptor referred to a deleted, zero-length regular file. A bounded copy of one retained `MCU_normal…rr2.xz` archive did not decode as standard xz locally; no vendor decoder or target helper was run. Investigation stopped there rather than looking through unrelated device or credential files.

The loader, PID **448**, was the only process whose descriptor links pointed to `/dev/ttyS2` and `/dev/uart_mcu` (descriptors 61 and 62). Its mappings also included `/dev/uart_mcu`. This establishes the current owner without opening either device. It does not establish safe takeover, an acknowledged heartbeat hold-off, or behavior after the owner exits.

## Running software and launch paths

Linux reports `3.4.39`, `armv7l`. `/etc/rr-info` contains `A.01.0057-V1612`, and `/opt/rockrobo/buildnumber` contains `2022110200REL`. The existing Valetudo startup log identifies **Roborock S7**, firmware build **1612**, and **Valetudo 2026.05.0**.

| Role | PID | Executable and argv |
| --- | ---: | --- |
| Valetudo | 371 | `/mnt/data/valetudo`, no arguments |
| WatchDoge | 372 | `/opt/rockrobo/watchdog/WatchDoge`; `WatchDoge /opt/rockrobo/watchdog` |
| SSH listener | 374 | `/usr/sbin/dropbear`; `/usr/sbin/dropbear -F` |
| Logging | 444 | `/opt/rockrobo/rrlog/rrlogd`; `rrlogd /opt/rockrobo/rrlog/rrlog.conf` |
| Loader | 448 | `/opt/rockrobo/cleaner/bin/rr_loader`; `rr_loader -d` |
| Controller | 507 | `/opt/rockrobo/cleaner/bin/RoboController`; `RoboController` |
| Application host | 509 | `/opt/rockrobo/cleaner/bin/AppProxy`; `AppProxy` |
| Network manager | 511 | `/opt/rockrobo/wlan/wlanmgr`; `wlanmgr` |
| Command bridge | 513 | `/opt/rockrobo/miio/miio_client`; `miio_client -d /mnt/data/miio/ -l 1` |

`RoboController` and `AppProxy` use the process names `robo_main` and `app_main`. Identify them by executable and argv, not only `/proc/PID/comm`. The loader maps chassis, navigation and SLAM together, alongside persistence, IPC and `libuart_api.so.4.0.2`. WatchDoge, both controller hosts and the network manager also map the UART library; mapping a library does not mean they own the UART.

The observed environment for these processes, the SSH listener and logging agrees on `RR_ROOT=/opt/rockrobo`, `RR_UDATA=/mnt/data` and `NAV_DYNAMIC_CONFIG_PATH=/mnt/data/rockrobo`. Only those three environment variables were selected for inspection. The loader has no `-c` override in its argv.

The following live MD5 values equal those of the corresponding saved rootfs files. The robot has no `sha256sum` command, so the comparison used its existing `md5sum` instead.

| File under `/opt/rockrobo/cleaner` | Matching MD5 |
| --- | --- |
| `lib/librr_plugin_chassis.so` | `ce207a12b4786d290eefef80ee98f94d` |
| `lib/libuart_api.so.4.0.2` | `5c9d6a7b81bc2d9467b6d0f791ae6ace` |
| `bin/rr_loader` | `072927fd9c7082e5962a251b7f821117` |
| `lib/libroboipc.so` | `ebc857c5b2bd067cf36b6269d5368ac3` |

`/etc/inittab` independently respawns Dropbear and WatchDoge. The SSH listener has parent PID 1, separate from the map hosts and Valetudo. `adbd` is also running and has an inittab respawn entry, but no alternate recovery connection was exercised; the serial getty entry is commented out. SSH independence is observed, not proof of a pre-consumer rescue environment after a failed boot.

`/etc/rc.local` launches `/mnt/reserve/_root.sh`, which starts Valetudo once in the background. No Valetudo restart loop appears in that script. The normal `ProcessList.conf` contains the observed map-host commands, plus `SysUpdate` and `rriot_rr`; WatchDoge remains the application restart source described in [service control](../../reference/services/supervision.md). Neither rriot bridge nor `SysUpdate` was present in the process inventory. The `SysUpdate` executable is still installed, so absence during this observation is not a persistent update gate. A live rriot AppProxy respawner was not observed; its previously identified restart capability still matters if that bridge is enabled later.

## Storage and current map files

`/mnt/data` is `/dev/nandl`, ext4, mounted read/write with ordered data. `/run` and `/run/shm` are tmpfs; `/run/shm` has a 102,400 KiB limit. `/dev/shm` points to `/run/shm`. The inspected `rcS` creates that layout, consistent with the cold-boot assumptions in the [file contract](../../reference/maps/matching-set.md). No inspected boot-hook excerpt showed a shared-buffer import; this was not an exhaustive audit of custom boot code.

All 17 final regular files below are owned by numeric `0:0`, mode `0644`, under `/mnt/data/rockrobo`. None is a symlink. `map/` is an empty directory owned by `0:0`, mode `0755`.

| Final file | Bytes |
| --- | ---: |
| `last_map` | 175,936 |
| `user_map0` | 175,936 |
| `user_map4` | 175,936 |
| `PersistData_1.data` | 71,441 |
| `PersistData_2.data` | 71,482 |
| `PersistData_6.data` | 71,285 |
| `SharedMultiMapInfo` | 39 |
| `slam_info.cfg` | 196 |
| `robot.db` | 338,944 |
| `appproxy.map` | 40 |
| `StartPos.data` | 41 |
| `ChargerPos.data` | 41 |
| `ChargerType.data` | 24 |
| `Rotater.cfg` | 72 |
| `RoboController.cfg` | 1,240 |
| `robot.setting` | 186 |
| `lab.cfg` | 1 |

The other slots and vmaps in the file contract's finite namespace were absent. So were `robot.db-journal`, `robot.db-wal` and `robot.db-shm`, and managed-name `.cache`/`.tmp*` work products. A shallow, map-name-specific directory listing found no additional candidate final map files. No live database was opened or queried, and no grid, persistence payload or shared map buffer was read.

Runtime and primary persistence now have different sizes. Do not carry forward the historical capture's byte-equality assumption when preparing an edit; obtain a new stopped matching set first. These observations record live metadata, not a transactional backup.

At the initial observation, `/mnt/data` had **56,410 KiB available**. RAM totaled 250,880 KiB, with 17,992 KiB free, 30,140 KiB in buffers and 54,096 KiB cached; there was no swap. Space and memory must be reconsidered for the actual staging plan, rather than treating these values as reservations.

## Exclusions and readiness

The current `exclude_process.conf` is a regular file, owned by `0:0`, mode `0644`, containing **19 bytes**: one comma-separated line with `rriot_tuya` and `rriot_rr`, without a trailing newline. An exact private local copy is retained at `/tmp/map-device-facts.qGJxVd/exclude.original`; its local mode is `0600`. This is not a backup stored on the robot and will not survive local temporary-file cleanup.

Preserving those bytes and appending the three map-host names on separate lines produces 54 bytes. Adding all the service document's bridge/updater candidates produces 85 bytes, beyond the native IPC payload limit. Do not drop the original exclusions to make a payload fit; choose the actual command gate and entry method deliberately.

**Docked, stationary and idle status could not be confirmed from the inspected files and logs.** No updater process was observed, but that alone does not confirm an update-free interval. Commands and schedules were not gated, because this phase authorized observation only. The normal processes were still present with the same PIDs at the final observation.

The configuration therefore supports continuing the existing plan, with an important MCU-specific correction. First establish the full A14.G1 heartbeat consumer behavior and prepare the matching native helper locally. Numeric JTAG/gyro identification remains unavailable from this bounded inspection; if it is still required, the parent must choose how to obtain it rather than silently substituting the package name or issuing a vendor query. Before any service stop, separately establish current docked/idle/update status, the command gate and the recovery plan. This inspection does not authorize stopping services or opening UART.
