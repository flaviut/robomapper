## Review

**Target:** `d93894fa0efe95f16365ff8b8804f270f8615ff1` against `4c804b41c7bdee290e1675c0ab2c095e6e0f0e4d`, plus focused assessment of the lifecycle anchor correction reported committed as `2903748`.

**Scope:** flow and lifecycle static-analysis evidence—not approval for device restore.

Reviewed the supplied committed diff, board, handoffs, replay/validation sources, generated C, instruction records, original-ELF mapping readout, configuration excerpts, fresh execution artifacts, and corrected graph evidence string. I made no repository changes.

### Correct

- **Channel-index distinction is instruction-backed.** IPC instructions at `0x6388/0x6390/0x6398` and `0x63fe/0x6404/0x6408` implement `((id >> 16) & 255) * 17 + (id >> 24)`. AppProxy map IDs `0x02033204/03/12` select index **53**; controller event `0x3c`, encoded as `0x0201001b`, selects index **19**. The handoff correctly does not invent a forwarding edge. Evidence: `flow/instructions.json`, those IPC anchors and controller `0x263b4..0x263cc`; `flow/handoff.json`, `distinct-channel-selection`.

- **Selected controller result semantics are accurately bounded.** Instructions at `0x37376..0x373ae` reject an all-zero key and compare both words, with slots `+0x3b8` and `+0x3d0` preceding `+0x3a0`. Pending-record removal at `0x373f6` precedes comparison against result `1` at `0x37402`; recorded success/error branches clear the slot. Key reuse can still satisfy these local checks. No universal epoch, concurrency, map-flag, or stale-result barrier is claimed. See `flow/c/RoboController/0x000367ac.c:183–335`.

- **Original-entry proof is distinguished from inferred extents.** The validator reconstructs eight controller EHABI starts and two IPC dynamic FUNC-symbol entries from original ELFs. The inspected original-ELF readout supplies SHA256 values, PT_LOAD tables, and raw VA/file-offset anchors. Its executable mappings use delta `0x10000`; IPC’s executable mapping uses delta zero. Displayed raw bytes agree with selected instruction records. Evidence: `flow/validate.py:10–69`, `flow/entry-boundaries.json`, and `/tmp/map-restore-review-d93894f/flow-lifecycle-elf.txt`. This does not prove every automatically recovered function extent.

- **WatchDoge recovery is narrow and preserves neighboring functions.** The 19-instruction helper returns normally at `0x1ac02` or calls stack-check failure at `0x1ac04`; its body ends at `0x1ac07`, excluding the launcher at `0x1ac08`. Recovery verifies original bytes, EHABI evidence, conflicts, reachable CFG membership, existing-function identity, and memory identity. Nonreturn handling is local to the reviewed call rather than a mutation of the existing target. Fresh replay confirms preservation, reopen equality, and conflict-rejection rollback. Evidence: `lifecycle/scripts/RecoverLifecycle.java:49–127`, `lifecycle/request.json`, and fresh `lifecycle-replay/validation.json`.

- **Lifecycle and provenance qualifications are appropriate.** Event-8 reload is separated from event-9 destructive reset; non-key restart is separated from missing-key status-2 escalation. Internal stop candidates are not presented as an external maintenance interface. The helper establishes `sigfillset` and `pthread_sigmask(0, …, NULL)` calls—not measured masking or successful hardware configuration. Saved ProcessList files name plain/R/M variants, but active deployment and equivalence remain unproved. Writer coverage, plugin hosting, kernel watchdog behavior, and MCU acceptance remain explicitly bounded. Evidence: `lifecycle/graph.json:65–166`, `lifecycle/configuration.json`, and flow handoff applicability/unresolved-dependency sections.

### Finding against `d93894f`

**P2 — Mode-1 lifecycle edge cites mode-2 instruction anchors.**

- **Location:** `analysis/re/evidence/restore/lifecycle/graph.json:142–143`.
- **Issue:** The committed edge describes **mode 1**, but cites heartbeat `0x19c96` and wait `0x19cee`, which belong to the **mode-2 / rrlogd** arm.
- **Evidence:** The mode comparison at `0x19c18` and branch at `0x19c1a` select `0x19dc8`. That mode-1 arm calls heartbeat control at **`0x19de8`** and the wait helper at **`0x19e0a`**. The alternate path compares the mode with `2` at `0x19c20`. The original-ELF byte readout corroborates these anchors.
- **Scope:** Evidence-reference accuracy only; the high-level mode distinction is correct.
- **Smallest correction:** Cite the mode-1 selecting branch and `0x19de8/0x19e0a`, identifying `0x19c96/0x19cee` as mode 2.

### Fixed — correction content verified

I inspected the corrected `lifecycle/graph.json:143`. It now identifies:

- mode-1 selection at `0x19c18/0x19c1a`, branching to `0x19dc8`;
- mode-1 heartbeat/wait at `0x19de8/0x19e0a`;
- `0x19c96/0x19cee` as mode 2 after the rrlogd name check.

**This resolves the P2.** The parent reports the correction committed as `2903748`, with no firmware or generated-C changes, and reports that the lifecycle validator and diff check pass afterward. My focused assessment verifies the corrected content; no separate committed-range diff for `2903748` was supplied, so this is not a review of unrelated contents of that commit.

### Commands and results

These are **parent-executed results inspected by this reviewer**, not independent reviewer execution.

The final `/tmp/map-restore-review-d93894f/execution-status.tsv` records exit status **0** for all four validators, test/captured-data checks, diff check, and all four sequential fresh replays. The parent reports 15 tests and two captured pairs.

| Focused command/check | Result |
|---|---|
| `python3 analysis/re/evidence/restore/flow/validate.py` | PASS: 3 hashes, 14 functions, 2,383 instruction-byte checks, 14 claim anchors, 10 original-entry checks |
| Flow unittest discovery using `test_flow_evidence.py` | PASS: 4 tests, including changed bytes, odd VA, and unmapped VA rejection |
| Lifecycle validator with `--saved-rootfs "$PWD/analysis/rootfs"` | PASS: 616 instruction records, 9 configuration files, 91 tracked ELF-path screen |
| Fresh flow replay into `flow/scratch/parent-review-d93894f` | PASS: fresh baseline copy/imports, separate reopen, 15 focused artifacts byte-identical |
| Fresh lifecycle replay into `/tmp/map-restore-review-d93894f/lifecycle-replay` | PASS after flow: six commands, bounded recovery, preservation, reopen equality, rejection rollback |
| `git diff 4c804b4 d93894f --check` | PASS |

Fresh lifecycle C hashes match committed proof hashes. Replay source inspection found no dependency on private lane projects, inventories, or historical logs. Both helpers obtain baseline state through tooling-created copies rather than opening the closed baseline directly.

### Limitations

- **Flow’s external-`/tmp` restriction remains intentional and disclosed.** Its successful fresh replay used supported ignored source-tree scratch, not `/tmp`; `flow/replay.py:62` and `flow/discover.py:37` enforce that location. Lifecycle used a new `/tmp` output. All-`/tmp` replay compliance must not be claimed.
- No fresh replay failed; there are no new failure logs to preserve.
- Byte equality, reproducibility, reopen equality, and rollback fingerprints are **not semantic or runtime proof**. Semantic conclusions were separately checked against instruction branches and qualifications.
- No firmware execution, device access, internet research, or nested agents was used. Active boot selection, complete writer quiescence, heartbeat acceptance, durability, cold-start recovery, and restore safety remain outside this static review—not additional merge blockers.

### Merge verdict: **OK with notes**

No P0/P1 issue found. Exact commit `d93894f` contains the P2 anchor error; the inspected correction resolves it. Preserve the replay-output and static-versus-runtime qualifications.

**This verdict is not approval for device restore.**