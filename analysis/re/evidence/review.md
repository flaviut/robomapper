## Review

**Target:** Integrated static-analysis delivery for firmware `4.3.5_1612`, input commit `668cc07`, including the five component lanes, merged annotations, focused exports, replay tooling, and two bounded function recoveries.

**No issues found.**

No concrete P0, P1, or P2 defect qualified against the reviewed integration. This is an **OK-with-notes assessment of the static-analysis artifacts**, not acceptance of a restore procedure, completion of the unresolved analysis scope, or approval for device use.

### Review boundaries

This review was read-only. I inspected the entry-point documents, integration handoff, five lane handoffs/evidence, seven merged annotation documents, exported instruction/type records, risk-selected generated C, recovery requests and implementation, and replay/validation code. I also read the actual ELF inputs, although text-mode binary reads do **not** independently establish their cryptographic hashes.

I ran **no firmware, Ghidra, replay, hash, or test commands**, and made no repository/project changes. The recorded validation successes below are existing evidence whose implementation and outputs were inspected—not tests independently rerun by this reviewer. Semantic inspection was risk-selected, not an exhaustive instruction-by-instruction reanalysis of all 154 functions.

## Correct: integration, identities, and replay

### Identity and scope are explicit

The manifest identifies seven unique binary contents; the three UART names share one identity. WatchDoge is correctly located under `opt/rockrobo/watchdog/`, not `cleaner/bin/`. The published program counts total 154 functions: persistence 49, utilities 6, AppProxy 25, grid 27, navigation 18, WatchDoge 27, and UART 2. See `analysis/re/manifest.json:4–51` and `analysis/re/evidence/validation.json:31163–31250`.

The manifest identities reviewed were:

| Program | SHA256 |
|---|---|
| `librobopersist.so` | `8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c` |
| `librrutils.so` | `75927f4b9161a3b7a8c01771ca8496e061184c7b9c28f58958a10d6cba0a4f0b` |
| `librrslamdrv.so` | `b48f5f56eb1b2d22abbf727725ea558762337f8f0103229d8da6c1ab6275608a` |
| `librrnavdrv.so` | `603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475` |
| `AppProxy` | `24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457` |
| `WatchDoge` | `3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6` |
| `libuart_api.so.4.0.2` | `914317e600a73255cb6523e987ab3ab99b5168c47026503fcb3fe797f9961529` |

These are the **recorded identities**, not independently recomputed reviewer hashes.

### Guarded annotation replay is implemented faithfully

- Field changes require either the desired current value or an exact expected predecessor. Unsupported fields, duplicate anchors, incompatible shared types, and ambiguous names are rejected. Signature replay also checks the saved actual prototype rather than treating type equivalence alone as sufficient. See `analysis/re/tooling/ReTool.java:140–218`.
- Binary identity is checked before annotation mutation, and annotation application is transactional. See `analysis/re/tooling/ReTool.java:239–273`.
- Integration checks exact selected-entry union, preservation of existing bodies and surviving names, approved additions only, component instruction agreement, and separate reopen persistence. The nineteen propagated prototype changes are explicitly recorded rather than hidden. See `analysis/re/evidence/integrate.py:226–308` and `analysis/re/evidence/validation.json:31266` onward.
- Ownership distinguishes selection from annotation ownership. In particular, persistence’s contextual selection of `librobopersist.so:0x1ab94` does not displace catalog ownership. See `analysis/re/canonical/handoff.json`, `annotation_merge.ownership`, and the corresponding function record in `analysis/re/evidence/index.json`.

The delivery replay reads manifest/binaries, shared tooling, unchanged recovery sources/requests, merged annotations, and the final index—not ignored component proofs. It applies recovery before annotations and verifies focused selection and every emitted C hash. See `analysis/re/evidence/replay.py:37–132`.

The existing records report 31,137 original integration checks, 17 successful commands, and a subsequent ten-command fresh-copy replay with seven matching selected/type exports and 154 byte-identical C files. The **no-cache import branch remains untested**, as the delivery documentation explicitly acknowledges (`analysis/re/RESULTS.md:19–30`; `analysis/re/evidence/replay-validation.json:1–85`).

### Types, unknowns, Thumb entries, and generated-C labeling remain appropriately bounded

The annotations preserve observational layouts and unknown storage rather than asserting recovered C++ classes: catalog entry/payload unknowns, task/root mutex storage, byte-array disk-header fields, and the backup-row unknown word remain explicit. See:

- `analysis/re/annotations/librobopersist.so.json:14–31`
- `analysis/re/annotations/librrslamdrv.so.json:6–7`
- `analysis/re/annotations/AppProxy.json:10–11`

Even VAs are used as function anchors while Thumb state remains separate. Sampled ARM PLT entries are not indiscriminately marked Thumb. The recovered WatchDoge callback correctly distinguishes even entry `0x1af18` from launcher pointer `0x1af19`.

The exporter unconditionally labels generated files **“Decompiled C, NOT recovered source; need not compile”**, with binary, SHA256, and VA. Sampled final files agree. See `analysis/re/tooling/ReTool.java:220–237`.

## Correct: bounded missing-entry recovery

### AppProxy `0x3c5b4`

The recovery is bounded to `0x3c5b4–0x3c5e9`, file offset `0x2c5b4`, with exact EHABI start and next start `0x3c5ec`. The generated `CatalogBackupExternal` correctly dereferences the external-ID argument, adds two, initializes the selected output to `-1`, calls `0x3c568`, and returns **selected output minus two**, not the helper’s boolean.

Evidence: `analysis/re/recovery/handoff.json:21–89`; `analysis/re/decompiled/AppProxy/0x0003c5b4.c:7–25`.

### WatchDoge `0x1af18`

The recovery is bounded to `0x1af18–0x1af69`, file offset `0xaf18`, with next EHABI start `0x1af6c`. Its observed sequence—unresolved `0x1abd8`, initialization, feed/sleep loop controlled by `0x345ec`, then close—is preserved without imposing a source-level callback ABI or claiming hardware acceptance.

Evidence: `analysis/re/recovery/handoff.json:92–159`; `analysis/re/decompiled/WatchDoge/0x0001af18.c:7–30`.

The recovery implementation checks original bytes, executable mapping, absent code/data/function conflicts, context, EHABI boundaries, reachable CFG, and every requested instruction before creating the function. It checks existing-function and byte identity afterward and rolls back rejection transactionally. See `analysis/re/recovery/scripts/RecoverBounded.java:51–128`.

### Navigation startup remains correctly blocked

`librrnavdrv.so:0x20bac0` is an interior seed, not the demonstrated entry. Candidate `0x20babc` has incomplete body/CFG recovery and is not promoted or replaced with handwritten C. See `analysis/re/recovery/handoff.json:161–196`.

Historical component comments about the formerly missing AppProxy and feeder entries are intentionally preserved and explicitly superseded by separate recovery ownership. They are **not current missing-entry findings**; the reconciliation is stated in `analysis/re/RESULTS.md:17`.

## Correct: safety-relevant semantic distinctions

These are consequential firmware behaviors accurately represented by the delivery—not newly introduced integration defects.

### 1. Acceptance, cancellation, and completion are not conflated

- `librobopersist.so:0x1bb20` publishes state 2 and starts a detached writer; its success is snapshot acceptance/no-op, not completed disk writes. The thread argument is the task at root+8. See `decompiled/librobopersist.so/0x0001bb20.c:90–93,361–382`.
- `0x1b564` removes destination bits under the root mutex, skipping states 0 and unknown 6. It does not join the writer, flush, or undo prior renames. See `decompiled/librobopersist.so/0x0001b564.c:7–10,62–80`.
- `0x1d10c` uses the **task index**, not owner PID, in its temporary suffix. Serialization result is ignored, destinations are handled separately, and cleanup returns the task to idle and posts capacity even after unsuccessful work. See `decompiled/librobopersist.so/0x0001d10c.c:11–16,299–311,918–925`.

No all-destination transaction or power-loss durability follows from those paths.

### 2. RAM restore and file loading remain distinct

`librobopersist.so:0x1c620` can restore a matching buffered snapshot. State-one rejection is not ordinary disk fallback. `ForcePersistLoad` at `0x192c4` can retain parse-success despite downstream restore failures.

The unusual single-value raw-copy count is also grounded in instructions: `0x19692` loads the count into `r6`, and `0x19756` moves it to the copy-length argument. See `evidence/librobopersist.so/selected.json:22998–23002,23488–23510`. It is not silently described as copying the raw payload size.

### 3. Earlier mutations can survive later load failure

`librrnavdrv.so:0x68428` loads grid/interface state first, reconciles current flag, and performs per-map/configuration changes before `PersistLoadMapInfo`. A later persistence failure does not roll those earlier effects back.

The ordering is supported by calls at `0x68544`, `0x68556`, and `0x685ba` (`evidence/librrnavdrv.so/selected.json:3638,3680,3914`; `decompiled/librrnavdrv.so/0x00068428.c:109–162`).

### 4. Grid integrity and stream success are narrowly scoped

- `librrslamdrv.so:0x1ab84` writes the 30-byte prefix/view header separately; the digest covers **cell bytes only**, not that header (`decompiled/librrslamdrv.so/0x0001ab84.c:54–112`).
- `0x1d21c` uses low-32-bit dimension multiplication and compares the digest before resetting/merging cells; this is not a demonstrated malformed-input safety boundary (`decompiled/librrslamdrv.so/0x0001d21c.c:70–95`).
- `0x1dd88` can bypass disk on cache hit. Rejection paths that leave stream state good can still yield a valid cached initialized grid (`decompiled/librrslamdrv.so/0x0001dd88.c:8–14,136–146`).
- `0x12c34` samples stream success **before close**. Instructions `0x12dd2–0x12de0` independently support the generated-C ordering (`evidence/librrslamdrv.so/selected.json:1398–1423`).

### 5. Application replies are not durable-write acknowledgments

AppProxy `0x24450` clears the wait result when no callbacks remain; `0x39b84` sends save-last and returns wait=1. Together, the ordinary load series can finish without waiting for that last save result (`decompiled/AppProxy/0x00024450.c:43–46`; `0x00039b84.c:40–43`).

Distinct-backup recovery at `0x51628` waits for its save-set result but does not establish durable persistence or checked database completion. The observed database error-path unlock discrepancy—acquired `+0x160`, error unlock `+0x178`—is retained rather than normalized away (`decompiled/AppProxy/0x00023210.c:9–10,23–50`).

### 6. WatchDoge exclusions and acknowledgments do not establish quiescence

- `WatchDoge:0x18400` disables matching records, sends `SIGKILL` to positive tracked PIDs, and sets tracked PID to `-1` without a wait/descendant barrier (`decompiled/WatchDoge/0x00018400.c:356–374`).
- `0x1e7a8` selects event 9 for C-string `strlen < 3`, not based on packet payload length. Event 9 kills network clients and resets configuration before falling through to exclusion reload and an acknowledgment-like send (`decompiled/WatchDoge/0x0001e7a8.c:73–81`; `0x000142e4.c:537–549`).
- `0x19ae0` has mode-dependent heartbeat control and bounded disappearance polling with fallback killing—not a general writer completion barrier (`decompiled/WatchDoge/0x00019ae0.c:8–14`).
- `0x1aec8` increments its feed counter regardless of ioctl success. UART `0x11690` sends the `-1` bit pattern through command `0xd3`; neither fact establishes kernel/MCU behavior (`decompiled/WatchDoge/0x0001aec8.c:8–25`; `decompiled/libuart_api.so.4.0.2/0x00011690.c:8–20`).

## Required scope still missing or partial

The delivery discloses these gaps; integration and the two recoveries do **not** close them.

| Lane | Remaining scope |
|---|---|
| **Persistence** | State-6 meaning/producers; complete locking/cooperating-setter audit; foreign-process mapping/fd lifecycle; malformed multipart/bounds/overflow behavior; caller-level completion and safe shutdown/restart. See `lanes/persistence/handoff.json:204–211`. |
| **Catalog** | Caller-wide synchronization/reservation; naming bounds/termination policy; cross-file/catalog/database transaction and durability. Recovery closes only the former `AppProxy:0x3c5b4` body gap—not its caller/ID-validity contract. See `lanes/catalog/handoff.json:524–529` and recovery handoff. |
| **Grid** | Legacy readers `0x1ca54`/`0x1cf60`; short-read exception behavior; full cache invalidation/concurrency coverage; startup/flag-12 behavior; occupancy-value meaning and unknown metadata. See `lanes/grid/handoff.json:247–263`. |
| **Orchestration** | Startup `librrnavdrv.so:0x20babc`, completion `0x683e0`, AppProxy error callback `0x4afa8`; RoboController IPC/task/result correlation; configuration-key mapping; destination helpers `0x68b48 → 0x68ae8`; alternative command paths only bounded for context. See `lanes/orchestration/handoff.json:342–355`. |
| **Watchdoge** | Target `WatchDoge:0x1abd8`; active Linux watchdog implementation/configuration; actual MCU handler/image and normal heartbeat producer; reset safety; non-destructive all-writer stop/restart. Recovering `0x1af18` does not close these. See `lanes/watchdoge/handoff.json:263–268`; `lanes/watchdoge/evidence.json:10117–10124`. |

Highest-priority follow-up remains the request/result bridge, shutdown/restart barriers, and kernel/MCU behavior. None supports a claim of safe all-writer quiescence, durable cross-file completion, or safe hardware reset today.

## Findings, corrections, and acceptance

- **P0:** None identified.
- **P1:** None identified against the integration.
- **P2:** None identified against the integration.
- **Fixed:** None; review-only.
- **Minimal correction required:** None for the bounded static-analysis delivery. Preserve the explicit gaps, historical-comment qualification, and untested no-cache replay disclosure.
- **Unsupported/untested acceptance claims:** Runtime restore safety, malformed-input safety, full concurrency guarantees, durable completion, all-writer restart, and hardware/MCU reset safety remain unsupported. Independent full hash recomputation and replay execution were not performed in this review.

The artifacts are suitable for merging **as qualified static-analysis evidence**. Parent acceptance remains separate.

Merge verdict: OK with notes