# Map maintenance: the concrete path

For S7 firmware `4.3.5_1612`, stopping the application services, requesting MCU heartbeat hold-off, copying the matching map files and rebooting normally has worked. The [backup procedure](../guides/stopped-backup.md) gives the observed sequence and private archive location. The robot returned docked with no reported error. No map file was edited or restored.

The two earlier refusals exposed an exited loader record that still retained its process name. The helper now permits that name only for a positively identified zombie with a missing executable, while retaining every sibling-task and UART descriptor check. The third attempt completed the stopped backup. Its native return 0 confirms the framed exchange, not readback of the MCU setting; [the A14 explanation](../reference/services/a14-heartbeat.md) follows the matching firmware's heartbeat handler.

The sections below describe the broader replacement plan. Only the stop, untouched backup and normal return have been demonstrated; replacement and edited-map import remain separate work.

## 1. Have the helper ready before stopping anything

The helper has two small, distinct responsibilities, specified against existing device libraries:

- [Application supervision](../reference/services/supervision.md): send WatchDoge event-8 exclusion content through the documented private native FIFO channel, without registering a second AppProxy receiver. Preserve the original exclusion file and enforce the 63-byte content bound. Do not send empty/short content: that selects destructive event 9. If the required content cannot fit, the documented maintenance-boot alternative avoids this limit but still needs the MCU gate on that boot.
- [MCU supervision](../reference/services/heartbeat.md): after the old loader/UART owner exits, call `rua_keep_mcu_heartbeat(-1)` and require return 0. This existing export handles temporary UART ownership, framing, retries and acknowledgment. Do not inject raw serial bytes or stop WatchDoge. The helper is staged privately for each session, not installed as a system command.

The helper is in `tools/map-maint/`; [its instructions](../reference/tools/map-maint.md) explain how it was built against the robot's saved runtime libraries. It refuses malformed exclusion content and checks that the loader and UART owners are gone before requesting the hold-off. We have also traced the A14.G1 MCU's actual dispatch and consumer: −1 skips its missing-heartbeat handling. The reply confirms receipt of the framed request, not a readback of the stored value. The successful backup observed a service-off interval, but the reply itself is not semantic readback of the heartbeat setting.

## 2. Obtain the offline window

1. Start stationary and idle or docked, with sufficient battery and no reported activity, errors or update. Gate schedules and external commands; preserve the administrative connection.
2. Save the **current** supervision exclusions independently of the map backup. Prevent restart of the actual map hosts (`rr_loader`, `RoboController`, `AppProxy` in the saved normal configuration) and relevant bridges/updaters. Leave WatchDoge and its Linux watchdog feeder running.
3. Enter exclusions using the native helper or the conditional maintenance-boot route. Confirm the actual hosts and known descendants have exited. Exclusion delivery and its reply do not acknowledge exit or a completed save.
4. Obtain the acknowledged −1 MCU gate with the loader absent. Abort file replacement on UART lock/init/send failure. Do not send it before stopping chassis: the next normal heartbeat overwrites it. Do not assume a prior request persists through a reboot.
5. Retain maintenance exclusions on disk throughout file installation. This prevents automatic application startup after an interrupted installation; hardware liveness on that next boot still requires its own gate.

The finite vendor hold-off value 120 is not used to budget this window. Its exact wall-clock duration was not established. Host exit removes detached writer threads and private caches; a later real reboot removes old tmpfs shared buffers.

## 3. Back up or restore the matching set

Use the literal namespace and staging/quarantine procedure in the [matching-set reference](../reference/maps/matching-set.md) and [restore plan](../guides/matching-set-restore.md). The captured set has 17 regular files and an empty `map/` directory, including:

- Runtime `last_map` / `PersistData_1.data`.
- Primary `user_map0` / `PersistData_2.data`.
- Associated backup `user_map4` / `PersistData_6.data`.
- Catalog, full persistence, `slam_info.cfg`, app database, map-related pose/config companions and any present vmaps/SQLite sidecars.

Record absence as well as bytes. Restore all and only the chosen snapshot's members; quarantine newer slots, old DB companions and interrupted work products rather than extracting over an existing epoch. Preserve ownership/modes. Do not roll back identity, networking, supervision or Valetudo settings from a broad configuration archive.

For unchanged matching-set restore, no region decoding, SQL modification or segmentation regeneration is required. Current SQLite journal policy need not be changed: retain the main file and whichever same-epoch sidecars are present in the stopped snapshot. Prefer a newly acquired idle stopped snapshot over assuming the historical live-acquired archive was transactional.

## 4. Keep the first edit bounded

The [edit constraints](../reference/maps/editing.md) specify the exact encoding: preserve the 30-byte RRSLAM prefix/frame, alter only selected raw raster cells, and replace the trailing 16-byte `MD5(cells)`. Preserve persistence and spatial companions unchanged.

Cold startup can consume runtime flag 1 and catalog primary 2, so an active-map patch must account for both, not just `user_map0`. Historical captured copies were identical; that does not establish equality in the new stopped backup. Identify the actual selected maps and frames before preparing any patch, retain genuine backup flag 6 untouched, and do not apply offsets or bytes from one persistence file to another by assumption.

Keep the first patch small and topology-preserving. Do not change origin, dimensions, doors/connectivity, dock/pose or restrictions. Use the ordinary vendor split/merge/rename operations for room-label adjustments after startup; refresh current IDs/names between operations. These operations do not rebuild room ownership from arbitrary new raster geometry.

A real `manual_segment_map` route to full native segmentation has been traced, including controller dispatch. It is **not yet a justified offline-import repair step**: the stored-map selection, occupancy consumption and durable save sequence are not all closed. Do not issue it automatically after restoring files. Arbitrary geometry/frame editing remains outside this procedure; retain the raster or use vendor remapping instead.

## 5. Finish with a cold start

Finish the entire replacement and storage flush while all consumers remain stopped. Restore the original supervision file **on disk only**, without live reload, then perform a controlled reboot. That avoids warm-restart adoption races and stale `/BufferedMapInfo` state under the saved tmpfs layout.

Normal startup may load primary 2 during reboot recovery and runtime 1 during last-map handling. This is why both belong to the matching set. Do not issue an additional restore/recover/save RPC: the vendor backup-recovery series can copy older backup 6 over destinations 1 and 2. Let normal startup consume the installed set, keeping new commands gated until the intended map, rooms/restrictions and stationary pose are observed.

Per-file replacement is not multi-file atomic. Keep the complete quarantine for rollback and uninterrupted power through installation. Do not resume consumers after a partial installation; restore one whole epoch while still excluded.

## Before any map writes

Keep the acquired stopped backup unchanged and off-device. A replacement plan must identify the selected map and every affected companion, preserve a complete rollback set, and account for interruption between individual file writes. The demonstrated software recovery does not repair a partially installed set after power loss.

The [vendor status investigation](../history/2026-10-21/vendor-readiness.md) found no enabled cleaning timers. The completed backup started and ended docked at 88%, with the updater idle and no reported error or activity. Those readings expire: obtain fresh status and current process identities before another session.

An unchanged matching-set restore or a small fixed-frame patch is the intended first write operation, not something already demonstrated. Do not assume the current runtime and primary persistence are identical. Connectivity, dimension or coordinate changes still lack a complete transformation and import sequence.
