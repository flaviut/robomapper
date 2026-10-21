# Map maintenance: the concrete path

For S7 firmware `4.3.5_1612`, the intended approach is to stop the application services, pause MCU heartbeat supervision, copy the matching map files, and restart normally. That avoids editing a live map or rebuilding opaque persistence regions.

We attempted the service stop once. The helper still detected a loader task and refused before opening UART, so no backup or map changes occurred. Recovery restored the original exclusions and rebooted; SSH and the expected services returned. [The session record](MAINTENANCE-SESSION.md) explains what ran, and [the refusal explanation](WHY-MAINTENANCE-STOPPED.md) describes what we still need to identify. Leave the robot running rather than repeating the attempt without that information.

We have identified the control mechanisms and file formats, built the native helper, and inspected the running robot. Its Linux libraries match the saved firmware. The reported MCU version matches the A14.G1 image once its timestamp formatting is accounted for; [the A14 explanation](A14-HEARTBEAT.md) follows the actual heartbeat handler. The helper was uploaded and used during that attempt: its exclusion request succeeded, but its UART operation refused before calling the vendor API. Fresh telemetry showed the robot idle and the updater inactive before and after the normal reboot. The stopped backup procedure has not yet completed.

## 1. Have the helper ready before stopping anything

The helper has two small, distinct responsibilities, specified against existing device libraries:

- [Application supervision](MAP-SERVICE-CONTROL.md): send WatchDoge event-8 exclusion content through the documented private native FIFO channel, without registering a second AppProxy receiver. Preserve the original exclusion file and enforce the 63-byte content bound. Do not send empty/short content: that selects destructive event 9. If the required content cannot fit, the documented maintenance-boot alternative avoids this limit but still needs the MCU gate on that boot.
- [MCU supervision](MAP-HEARTBEAT-CONTROL.md): after the old loader/UART owner exits, call `rua_keep_mcu_heartbeat(-1)` and require return 0. This existing export handles temporary UART ownership, framing, retries and acknowledgment. Do not inject raw serial bytes, stop WatchDoge, or claim an installed helper command exists.

The helper is in `tools/map-maint/`; [its instructions](MAINTENANCE-HELPER.md) explain how it was built against the robot's saved runtime libraries. It refuses malformed exclusion content and checks that the loader and UART owners are gone before requesting the hold-off. We have also traced the A14.G1 MCU's actual dispatch and consumer: −1 skips its missing-heartbeat handling. The reply confirms receipt of the framed request, not a readback of the stored value. Do not treat the local build or that reply as an observed service-off interval.

## 2. Obtain the offline window

1. Start stationary and idle. Gate schedules, Valetudo/cloud/app commands and updating; preserve the administrative connection.
2. Save the **current** supervision exclusions independently of the map backup. Prevent restart of the actual map hosts (`rr_loader`, `RoboController`, `AppProxy` in the saved normal configuration) and relevant bridges/updaters. Leave WatchDoge and its Linux watchdog feeder running.
3. Enter exclusions using the native helper or the conditional maintenance-boot route. Confirm the actual hosts and known descendants have exited. Exclusion delivery and its reply do not acknowledge exit or a completed save.
4. Obtain the acknowledged −1 MCU gate with the loader absent. Abort file replacement on UART lock/init/send failure. Do not send it before stopping chassis: the next normal heartbeat overwrites it. Do not assume a prior request persists through a reboot.
5. Retain maintenance exclusions on disk throughout file installation. This prevents automatic application startup after an interrupted installation; hardware liveness on that next boot still requires its own gate.

The finite vendor hold-off value 120 is not used to budget this window. Its exact wall-clock duration was not established. Host exit removes detached writer threads and private caches; a later real reboot removes old tmpfs shared buffers.

## 3. Back up or restore the matching set

Use the literal namespace and staging/quarantine procedure in [MAP-FILE-CONTRACT.md](MAP-FILE-CONTRACT.md). The captured set has 17 regular files and an empty `map/` directory, including:

- Runtime `last_map` / `PersistData_1.data`.
- Primary `user_map0` / `PersistData_2.data`.
- Associated backup `user_map4` / `PersistData_6.data`.
- Catalog, full persistence, `slam_info.cfg`, app database, map-related pose/config companions and any present vmaps/SQLite sidecars.

Record absence as well as bytes. Restore all and only the chosen snapshot's members; quarantine newer slots, old DB companions and interrupted work products rather than extracting over an existing epoch. Preserve ownership/modes. Do not roll back identity, networking, supervision or Valetudo settings from a broad configuration archive.

For unchanged matching-set restore, no region decoding, SQL modification or segmentation regeneration is required. Current SQLite journal policy need not be changed: retain the main file and whichever same-epoch sidecars are present in the stopped snapshot. Prefer a newly acquired idle stopped snapshot over assuming the historical live-acquired archive was transactional.

## 4. Keep the first edit bounded

[MAP-EDIT-CONTRACT.md](MAP-EDIT-CONTRACT.md) specifies the exact encoding: preserve the 30-byte RRSLAM prefix/frame, alter only selected raw raster cells, and replace the trailing 16-byte `MD5(cells)`. Preserve persistence and spatial companions unchanged.

Cold startup can consume runtime flag 1 and catalog primary 2. The captured copies are identical, so an active-map patch must account for both, not just `user_map0`; the appropriate candidate is the same intended patch in those matching runtime/primary rasters, while retaining genuine backup flag 6 untouched. This is a derived preparation rule for the captured identity, not permission to overwrite unrelated slots. Different frames/maps require their own explicit selection, not byte-offset reuse.

Keep the first patch small and topology-preserving. Do not change origin, dimensions, doors/connectivity, dock/pose or restrictions. Use the ordinary vendor split/merge/rename operations for room-label adjustments after startup; refresh current IDs/names between operations. These operations do not rebuild room ownership from arbitrary new raster geometry.

A real `manual_segment_map` route to full native segmentation has been traced, including controller dispatch. It is **not yet a justified offline-import repair step**: the stored-map selection, occupancy consumption and durable save sequence are not all closed. Do not issue it automatically after restoring files. Arbitrary geometry/frame editing remains outside this procedure; retain the raster or use vendor remapping instead.

## 5. Finish with a cold start

Finish the entire replacement and storage flush while all consumers remain stopped. Restore the original supervision file **on disk only**, without live reload, then perform a controlled reboot. That avoids warm-restart adoption races and stale `/BufferedMapInfo` state under the saved tmpfs layout.

Normal startup may load primary 2 during reboot recovery and runtime 1 during last-map handling. This is why both belong to the matching set. Do not issue an additional restore/recover/save RPC: the vendor backup-recovery series can copy older backup 6 over destinations 1 and 2. Let normal startup consume the installed set, keeping new commands gated until the intended map, rooms/restrictions and stationary pose are observed.

Per-file replacement is not multi-file atomic. Keep the complete quarantine for rollback and uninterrupted power through installation. Do not resume consumers after a partial installation; restore one whole epoch while still excluded.

## What we still need before using it

First identify which task caused the refusal and why the shell's executable check missed it. The updated helper can record the PID, thread ID, state and matching rule without relaxing its refusal. It has been built locally but not deployed. The old logs lack those details, so neither a zombie nor a surviving thread can be named as the cause.

The [vendor status investigation](VENDOR-STATUS.md) found no enabled cleaning timers and observed the updater idle. After recovery, the robot again reported idle at 96% with no error or cleaning activity. Those readings expire and do not justify another stop by themselves. A further attempt needs a fresh reading and a plan to capture the missing task information while retaining independent recovery.

Take a new stopped backup before editing; the live persistence files no longer have the historical sizes, so do not reuse the old assumption that the runtime and primary copies are identical. An unchanged matching-set restore or a small fixed-frame patch remains the intended first operation. If the edit changes connectivity, dimensions or coordinates, this procedure does not supply the necessary transformation or import sequence.

No tests, validators, replay suites or review agents were used for this work. One approved service-stop attempt ran and recovered normally; no UART request, stopped backup or map replacement occurred. The component documents contain the source details, and the session record contains the observed outcome.
