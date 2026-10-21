# Storage and supervision recovery — firmware 4.3.5_1612

Use the [function evidence index](evidence/index.json) to review 154 selected functions across seven binary identities. It links each even virtual entry address to its binary SHA256, generated C, instruction bytes, annotation owner and component evidence. [Independent review](evidence/review.md) found no blockers in this bounded static-analysis delivery; it is **not** a validated procedure for restoring maps on a robot.

## What the recovered paths establish

[Buffered persistence](evidence/components/persistence.json) distinguishes accepting a snapshot from finishing its background writes. Cancellation removes pending destinations but does not undo completed renames or join the writer. The temporary suffix is the task index, not the owner PID. Loads may restore a matching buffer rather than the file; state-one rejection does not fall back to disk. Multipart streams inflate independently, while some restore errors do not clear parse-success reporting.

[Catalog evidence](evidence/components/catalog.json) separates catalog flags, external IDs and filenames. The catalog contains four primary/backup associations; allocation is not reservation, and returned shared pointers outlive their local guard. Catalog serialization uses generic type-one persistence, not the asynchronous map-save API. [Grid evidence](evidence/components/grid.json) identifies the 30-byte RRSLAM v2 prefix, cell block and digest. Cache hits can bypass disk, and a good stream state does not necessarily mean the format was accepted. Grid wrapper success is sampled before close.

[Orchestration evidence](evidence/components/orchestration.json) records local order rather than an atomic transaction: navigation loads grid/interface state before persistence, and earlier changes can survive later failure. The ordinary AppProxy load series can reply `ok` after sending save-last without waiting for that save result. Distinct-backup recovery waits for its save-set result, then reaches an unchecked database helper. These observations do not close the RoboController task/result bridge or establish durable completion.

[Supervision evidence](evidence/components/watchdoge.json) distinguishes PID refresh from process start. Exclusion reload can disable tracked processes and send an acknowledgment-like packet without proving writer exit or flush. Reset selection uses `strlen`, not the packet-length field; normal-stop heartbeat behavior depends on the stop mode. Kernel watchdog acceptance and MCU command semantics remain unverified.

## Artifacts and replay

The seven [schema-v1 annotation documents](annotations/) preserve exact preconditions and surviving symbols. [Focused generated C](decompiled/) is decompiler output, not recovered source, and need not compile. Each program's `evidence/<program>/selected.json` and `types.json` retain instruction and observational-layout evidence. Component statements about formerly missing AppProxy `0x3c5b4` and WatchDoge `0x1af18` are preserved historically; [separate bounded recovery evidence](evidence/recovery/handoff.json) owns their added entries.

The [integration validation](evidence/validation.json) passed 31,137 checks and 17 commands, including separate reopen without annotation replay. The [delivery replay check](evidence/replay-validation.json) compares a fresh baseline copy. A [clean-checkout replay](evidence/clean-checkout-validation.json) imports the tracked binaries without cached projects or ignored inputs and reproduces all 154 C files.

For a new replay, use Python 3 and the pinned local Ghidra installation described in [shared tooling](tooling/README.md). From the repository root, with a new output directory:

```sh
PYTHONDONTWRITEBYTECODE=1 python3 analysis/re/evidence/replay.py --plan
PYTHONDONTWRITEBYTECODE=1 python3 analysis/re/evidence/replay.py \
  --out "$PWD/analysis/re/canonical/replay-review"
```

The helper copies a closed local baseline if available, otherwise imports manifest binaries privately through the shared harness. It applies the two unchanged recovery requests before merged annotations and exports only index-selected entries. It uses no ignored lane, rootfs or private proof inputs. Both the cache-copy and clean-checkout import paths reproduced the indexed C hashes. `evidence/integrate.py` remains the historical integration builder, not the repository-only replay entry point.

## Map restore follow-ups

The [restore investigation board](evidence/restore/board.json) tracks additional evidence outside the original 154-function index. The [first follow-up review](evidence/restore/review/flow-lifecycle.md) accepts bounded controller/lifecycle findings; its [metadata/consistency companion](evidence/restore/review/metadata-consistency.md) accepts conditional segmentation and snapshot findings. Neither approves device restore. WatchDoge `0x1abd8` is now recovered as a bounded helper; it no longer remains an entry gap.

The [second follow-up](evidence/restore/second-wave.json), with [parent validation](evidence/restore/second-validation.json), adds four static checkpoints. Independent [native/host](evidence/restore/review/native-host.md) and [room/backup](evidence/restore/review/room-backup.md) reviews accepted them with no issues:

- [Native route](evidence/restore/native-route/handoff.json): identifies the actual navigation request decoder, distinct from the controller route. Load-task capture, candidate completion dispatch and result encoding are bounded observations; intervening scheduler/subscriber edges remain unclosed.
- [Writer host](evidence/restore/writer-host/handoff.json): authenticated decoding identifies navigation/SLAM in embedded loader defaults. SIGHUP sets a flag; generic cleanup joins threads and calls plugin callbacks. Active configuration and concrete persistence-worker completion remain unproved.
- [Room reconciliation](evidence/restore/room-reconcile/handoff.json): post-ID fills depend on geometry and neighboring labels. AppProxy can retain names while replacing IDs from ordered response bytes; automatic reconciliation after arbitrary grid edits is not established.
- [Backup dependencies](evidence/restore/backup-dependencies/handoff.json): identifies the `robot.db` opener and `slam_info.cfg` companion, including staged config writes. The deployed DB base, journal mode and concrete vmap I/O remain unresolved. A main-file-only backup is not established as sufficient.

## Remaining limits

Startup seed `librrnavdrv.so:0x20bac0` is interior; candidate entry `0x20babc` remains unrecovered. Navigation candidate `0x683e0` has bounded read-only instruction evidence, not a recovered function or complete completion route. AppProxy error callback `0x4afa8` remains a gap. No substitute handwritten C is supplied.

Consistent backup still needs a complete dependency set and all-writer snapshot barrier. Safe editing needs validated metadata/room-identity transformations. Restore still needs cache invalidation, concrete plugin/persistence shutdown and restart contracts, cold-start recovery and durability checks. Kernel/MCU behavior, malformed-input safety and concurrency remain unverified. No firmware was executed or device accessed. Acceptance covers static-analysis artifacts only, not device use.
