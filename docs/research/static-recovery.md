# Storage and supervision recovery — firmware 4.3.5_1612

Use the [function evidence index](../../analysis/re/evidence/index.json) to review 154 selected functions across seven binary identities. It links each even virtual entry address to its binary SHA256, generated C, instruction bytes, annotation owner and component evidence. [Independent review](../../analysis/re/evidence/review.md) found no blockers in this bounded static-analysis delivery; it is **not** a validated procedure for restoring maps on a robot.

This page records the static-delivery checkpoint. Later [startup findings](../reference/maps/startup.md), [service and MCU findings](../reference/services/heartbeat.md), and the [completed stopped backup](../guides/stopped-backup.md) resolve some of its operational unknowns. The original evidence and review scope remain unchanged.

## What the recovered paths establish

[Buffered persistence](../../analysis/re/evidence/components/persistence.json) distinguishes accepting a snapshot from finishing its background writes. Cancellation removes pending destinations but does not undo completed renames or join the writer. The temporary suffix is the task index, not the owner PID. Loads may restore a matching buffer rather than the file; state-one rejection does not fall back to disk. Multipart streams inflate independently, while some restore errors do not clear parse-success reporting.

[Catalog evidence](../../analysis/re/evidence/components/catalog.json) separates catalog flags, external IDs and filenames. The catalog contains four primary/backup associations; allocation is not reservation, and returned shared pointers outlive their local guard. Catalog serialization uses generic type-one persistence, not the asynchronous map-save API. [Grid evidence](../../analysis/re/evidence/components/grid.json) identifies the 30-byte RRSLAM v2 prefix, cell block and digest. Cache hits can bypass disk, and a good stream state does not necessarily mean the format was accepted. Grid wrapper success is sampled before close.

[Orchestration evidence](../../analysis/re/evidence/components/orchestration.json) records local order rather than an atomic transaction: navigation loads grid/interface state before persistence, and earlier changes can survive later failure. The ordinary AppProxy load series can reply `ok` after sending save-last without waiting for that save result. Distinct-backup recovery waits for its save-set result, then reaches an unchecked database helper. These observations do not close the RoboController task/result bridge or establish durable completion.

[Supervision evidence](../../analysis/re/evidence/components/watchdoge.json) distinguishes PID refresh from process start. Exclusion reload can disable tracked processes and send an acknowledgment-like packet without proving writer exit or flush. Reset selection uses `strlen`, not the packet-length field; normal-stop heartbeat behavior depends on the stop mode. Kernel watchdog acceptance and MCU command semantics remain unverified.

## Artifacts and replay

The seven [schema-v1 annotation documents](../../analysis/re/annotations) preserve exact preconditions and surviving symbols. [Focused generated C](../../analysis/re/decompiled) is decompiler output, not recovered source, and need not compile. Each program's `evidence/<program>/selected.json` and `types.json` retain instruction and observational-layout evidence. Component statements about formerly missing AppProxy `0x3c5b4` and WatchDoge `0x1af18` are preserved historically; [separate bounded recovery evidence](../../analysis/re/evidence/recovery/handoff.json) owns their added entries.

The [integration validation](../../analysis/re/evidence/validation.json) passed 31,137 checks and 17 commands, including separate reopen without annotation replay. The [delivery replay check](../../analysis/re/evidence/replay-validation.json) compares a fresh baseline copy. A [clean-checkout replay](../../analysis/re/evidence/clean-checkout-validation.json) imports the tracked binaries without cached projects or ignored inputs and reproduces all 154 C files.

For a new replay, use Python 3 and the pinned local Ghidra installation described in [shared tooling](../reference/tools/retool.md). From the repository root, with a new output directory:

```sh
PYTHONDONTWRITEBYTECODE=1 python3 analysis/re/evidence/replay.py --plan
PYTHONDONTWRITEBYTECODE=1 python3 analysis/re/evidence/replay.py \
  --out "$PWD/analysis/re/canonical/replay-review"
```

The helper copies a closed local baseline if available, otherwise imports manifest binaries privately through the shared harness. It applies the two unchanged recovery requests before merged annotations and exports only index-selected entries. It uses no ignored lane, rootfs or private proof inputs. Both the cache-copy and clean-checkout import paths reproduced the indexed C hashes. `evidence/integrate.py` remains the historical integration builder, not the repository-only replay entry point.

## Map restore follow-ups

The [restore investigation board](../../analysis/re/evidence/restore/board.json) tracks additional evidence outside the original 154-function index. The [first follow-up review](../../analysis/re/evidence/restore/review/flow-lifecycle.md) accepts bounded controller/lifecycle findings; its [metadata/consistency companion](../../analysis/re/evidence/restore/review/metadata-consistency.md) accepts conditional segmentation and snapshot findings. Neither approves device restore. WatchDoge `0x1abd8` is now recovered as a bounded helper; it no longer remains an entry gap.

The [second follow-up](../../analysis/re/evidence/restore/second-wave.json), with [parent validation](../../analysis/re/evidence/restore/second-validation.json), adds four static checkpoints. Independent [native/host](../../analysis/re/evidence/restore/review/native-host.md) and [room/backup](../../analysis/re/evidence/restore/review/room-backup.md) reviews accepted them with no issues:

- [Native route](../../analysis/re/evidence/restore/native-route/handoff.json): identifies the actual navigation request decoder, distinct from the controller route. Load-task capture, candidate completion dispatch and result encoding are bounded observations; intervening scheduler/subscriber edges remain unclosed.
- [Writer host](../../analysis/re/evidence/restore/writer-host/handoff.json): authenticated decoding identifies navigation/SLAM in embedded loader defaults. SIGHUP sets a flag; generic cleanup joins threads and calls plugin callbacks. Active configuration and concrete persistence-worker completion remain unproved.
- [Room reconciliation](../../analysis/re/evidence/restore/room-reconcile/handoff.json): post-ID fills depend on geometry and neighboring labels. AppProxy can retain names while replacing IDs from ordered response bytes; automatic reconciliation after arbitrary grid edits is not established.
- [Backup dependencies](../../analysis/re/evidence/restore/backup-dependencies/handoff.json): identifies the `robot.db` opener and `slam_info.cfg` companion, including staged config writes. At that checkpoint the deployed DB base, journal mode and concrete vmap I/O were unresolved. The later [matching-set reference](../reference/maps/matching-set.md) identifies the deployed base and captured database format; runtime journal policy and concrete vmap I/O remain distinct questions. A main-file-only backup is not established as sufficient.

## Static-delivery limits

Startup seed `librrnavdrv.so:0x20bac0` is interior; candidate entry `0x20babc` remains unrecovered. Navigation candidate `0x683e0` has bounded read-only instruction evidence, not a recovered function or complete completion route. AppProxy error callback `0x4afa8` remains a gap. No substitute handwritten C is supplied.

This delivery alone established neither a complete backup dependency set nor an all-writer snapshot barrier, cache invalidation, concrete shutdown/restart contract or durable restore. It did not validate metadata/room transformations, kernel/MCU behavior, malformed-input safety or concurrency. No firmware was executed or device accessed during that static work. Its acceptance covers static-analysis artifacts, not device use; the later operational result remains limited to an untouched stopped backup.
