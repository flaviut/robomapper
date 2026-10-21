# S7 reverse-engineering reference

Findings for Roborock S7 firmware **`4.3.5_1612`**, with device observations from October 21, 2026. Start with the topic you need; session records are not operating instructions.

## What has been demonstrated

Stopping the map hosts, requesting MCU heartbeat hold-off, copying an untouched matching set, restoring supervision and rebooting normally succeeded on October 21, 2026. The [stopped-backup guide](guides/stopped-backup.md) records that sequence and the private backup's identity. The heartbeat reply was a transport acknowledgment, not readback of the MCU setting.

A later [unchanged restore](history/2026-10-21/unchanged-restore.md) reinstalled a fresh stopped set and rebooted normally. All 11 loaded map layers and all entities matched the pre-test map; native map/persistence files and catalog also matched on disk. **Edited-map import remains untested.** Fresh readiness and ownership checks are required for every session; historical PIDs and status readings expire.

## Map formats and state

An S7 saved map spans several files:

```text
RRSLAM raster           occupancy/confidence
PersistData_<flag>      labels, names, restrictions, poses, opaque state
SharedMultiMapInfo      primary/backup associations and current flag
slam_info.cfg           per-map navigation/recovery state
robot.db + sidecars     application projections and history
pose/config companions  other startup and recovery inputs
```

- [Native storage](reference/maps/storage.md) defines map flags, filenames and the RRSLAM v2 raster.
- [Persistence](reference/maps/persistence.md) covers the protobuf envelope, asynchronous saves, cancellation and buffer-aware loads.
- [Region layouts](reference/maps/regions.md) records decoded offsets, coordinate relationships and unresolved fields.
- [Matching set](reference/maps/matching-set.md) owns the finite file namespace, captured membership, SQLite companions and exclusions.
- [Cold-start selection](reference/maps/startup.md) follows runtime/primary selection, backup recovery and cache lifetime.
- [Edit constraints](reference/maps/editing.md) bounds occupancy-only changes; [room operations](reference/maps/room-operations.md) follows split, merge, naming, ID promotion and full regeneration.

To prepare bytes locally, use the [raster-edit guide](guides/raster-edit.md). For whole-set installation, use the [restore guide](guides/matching-set-restore.md) and [matching-set scripts](reference/tools/matching-set.md). Unchanged reinstallation is not evidence of safe navigation after an edit.

## Services and watchdogs

Two independent mechanisms matter: WatchDoge feeds the Linux watchdog, while chassis in `rr_loader` normally supplies MCU heartbeats. Stopping the loader also stops chassis, not just map writers.

- [Supervision](reference/services/supervision.md) explains exclusion parsing, restart/adoption behavior, command producers and exit checks.
- [Exclusion IPC](reference/services/exclusion-ipc.md) specifies the native FIFO API and packet ABI. **Empty or short content can select a destructive reset event.**
- [Plugin lifecycle](reference/services/plugins.md) follows cooperative loader cleanup and its limits as a save barrier.
- [Heartbeat control](reference/services/heartbeat.md) follows the chassis producer, native UART API and packaged MCU comparisons.
- [A14.G1 implementation](reference/services/a14-heartbeat.md) connects the observed build label to dispatch, sentinel handling and acknowledgment semantics.

## Local tools and evidence

The [map-maint reference](reference/tools/map-maint.md) defines the native helper's commands and ownership checks. Its [build guide](guides/build-map-maint.md) uses the saved runtime rather than introducing a newer libc. Building does not deploy or run it.

For static work, use [Ghidra tooling](reference/tools/retool.md), the [bounded function-recovery guide](guides/function-recovery.md), and the [static-recovery results and replay instructions](research/static-recovery.md). The [GMapping comparison](research/gmapping-comparison.md) explains why OpenSLAM structures are not this firmware's file schema.

Evidence stays beside its tools under [`analysis/re/`](../analysis/re/): [binary manifest](../analysis/re/manifest.json), [function index](../analysis/re/evidence/index.json), annotations, instruction exports, generated C and reviews. Generated C is decompiler output, not recovered source. Historical handoffs retain their original paths and checkpoint limits; use these docs for current navigation.

Private captures, saved rootfs files, build outputs and Ghidra projects are not checkout dependencies for reading the reference. Some local build/replay tasks require those inputs, as their guides state. Map archives and credentials remain private.

## Investigation history

The [history index](history/README.md) orders the feasibility assessment, readiness observations and refused first attempt. It includes the successful backup and unchanged restore without treating earlier conclusions or one-shot launch commands as current guidance.
