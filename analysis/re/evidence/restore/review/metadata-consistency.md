## Review

**Merge verdict: OK with notes — bounded static-evidence acceptance only, not approval for device restore.**

Reviewed the supplied `4c804b4..d93894f` diff artifact, board, assigned handoffs, checker/replay sources, generated C, focused instruction records, dependency records, and original-ELF mapping/byte readouts.

The parent’s execution at tested commit `d93894f` passed **all four validators, 15 tests, both captured pairs, committed-diff whitespace checking, and all four fresh sequential Ghidra replays**. The parent also reports byte-for-byte agreement of all 32 committed C exports with fresh replay output, including all seven metadata and eight consistency exports.

These are **parent-executed results inspected by this reviewer**, not independent reviewer execution; my tools provided no command runner. No duplicate replay was performed.

### Correct

- **Segmentation copy intervals and tail-reset claims are supported.**  
  `metadata/evidence.json`, anchors `0x15840..0x15860` and `0x158da..0x158f8`, establish:
  - Full setter: `[0x31da0, 0x131f44)`, length `0x1001a4`.
  - Grid-only setter: `[0x31da4, 0x131db0)`, length `0x10000c`.

  Grid-only replacement preserves four leading bytes and the 404-byte tail. Navigation anchors `0x1330ea..0x13311a` show full allocation/zeroing, copying at `+4`, setting presence, and full publication. The zero-tail conclusion applies to that path, not arbitrary unknown-byte clearing.

- **Conditional ID reuse is appropriately qualified.**  
  Anchors `0x1324ba..0x1324d4` show the active-grid check and low-six-bit `16..31` reuse branch. Anchors `0x132488..0x132496` conditionally regenerate bit `0x40`; `0x132620` onward supplies new-ID allocation and saturation. Subsequent postprocessing remains visible in `metadata/exports/librrnavdrv.so/0x00132c30.c`. The handoff does not promise final room-ID/name stability.

- **Original ELF mappings support byte provenance.**  
  Inspected `/tmp/map-restore-review-d93894f/metadata-consistency-elf.txt`: original SHA256 results, `readelf` program headers, and independently struct-decoded mappings/raw bytes for 13 persistence and seven navigation anchors. The reviewed code lies in executable file-backed `PT_LOAD` ranges. Writable segments have nonidentity VA/file offsets; the validators derive offsets from program headers rather than assuming universal identity mapping.

- **The mmap/fd conclusion is correctly limited to local control flow.**  
  `consistency/focused/selected.json`, anchors `0x1ca04..0x1ca4a`, show `shm_open`, `mmap`, success branches to `0x1c778`, and the direct close on the failure route. The common restore exit adds no direct close or munmap. Worker anchors `0x1d1e8..0x1d212` release its task resources, not the foreign loader’s stack-local resources. This establishes the disclosed local-success observation—not a measured process-wide leak rate or exhaustive exclusion of external cleanup.

- **Dependency and barrier claims remain conservative.**  
  `consistency/dependencies.json:132–219` separates acceptance, ordinary cleanup, cancellation/repair, cache-drop branches and unnamed state 6. `restore-contract.json` does not equate these with a coherent snapshot, all-writer barrier, fresh disk-backed load or power-loss durability. Database, vmap and configuration requirements remain explicitly provisional.

### Finding and correction

- **P2 — consistency replay scratch was not ignored in `d93894f`.**  
  `consistency/replay.py:19–23` requires “ignored lane-local scratch,” and `consistency/handoff.json:16` describes ignored scratch. That commit supplied no consistency `.gitignore`; root `.gitignore` excludes project databases/logs but not generated JSON/C exports beneath this evidence directory. Running the helper could expose replay outputs as untracked project files.

  **Smallest correction:** add `consistency/.gitignore` containing `/scratch/`.

  **Resolved after the reviewed commit:** parent fixed this in `6c61e62`. I inspected `.gitignore:1`; `/tmp/map-restore-review-d93894f/consistency-output-policy.txt` confirms the scratch validation path is ignored. No reviewer edits were made.

### Commands and results

Parent executions used `PYTHONDONTWRITEBYTECODE=1`. Logs and `execution-status.tsv` are under `/tmp/map-restore-review-d93894f`.

| Command | Inspected result |
|---|---|
| `python3 analysis/re/evidence/restore/metadata/validate.py` | Passed: 2 binaries, 7 functions, 2,132 instruction records, 207 claim anchors |
| `python3 analysis/re/evidence/restore/metadata/test_metadata.py -v` | 4 tests passed |
| `python3 analysis/re/evidence/restore/metadata/check_saved.py --analysis-root /home/user/tmp/illegalplainape/analysis` | Passed: two captured pairs; 351,780 application/segmentation cells compared |
| `python3 analysis/re/evidence/restore/consistency/validate.py` | Passed: 2,090 focused and 4,637 contextual instruction records; 25 path literals |
| `python3 -m unittest discover -s analysis/re/evidence/restore/consistency -p test_validate.py -v` | 7 tests passed |
| `python3 analysis/re/evidence/restore/metadata/replay.py --out /tmp/map-restore-review-d93894f/metadata-replay` | Passed: seven C exports and selected records reproduced |
| `python3 analysis/re/evidence/restore/consistency/replay.py --out analysis/re/evidence/restore/consistency/scratch/parent-review-d93894f` | Passed subsequently: fresh baseline copy, guarded annotations, separate reopen and comparison |
| `git diff 4c804b4 d93894f --check` | Passed |

### Notes and limitations

- **Output-location deviation:** consistency intentionally rejects `/tmp` destinations (`replay.py:22–23`). The supplied transcript confirms exit 2 with no destination created. Its successful fresh replay used lane scratch. Evidence reproduction passed, but the literal request to place both helper outputs under `/tmp` was not fulfilled. This is a usability limitation, not a semantic blocker.
- Neither assigned helper reads private lane scratch as an input. They use committed artifacts and the explicit source-root harness/closed baseline. Integrated-root success supports reproduction after cherry-pick **in this environment**, not portability to another checkout or machine.
- The saved checker is capture-specific, not a general malformed-input validator. Its negative tests cover mapping, origin and IMAGE/segmentation mismatch despite a valid native digest. Tail contents and reuse-range membership are returned observations (`metadata/check_saved.py:116–120`), not universal acceptance conditions.
- Byte matching and reproducibility are not semantic proof. Consistency additionally pins `selected.json` by digest; metadata’s fresh replay compares complete selected records. Neither establishes arbitrary malformed-evidence safety, full algorithm correctness or runtime restore safety.
- No original firmware execution, device access, internet research or nested agents occurred. No private payloads are reproduced here.
- Explicitly disclosed future/runtime gaps are not new merge blockers.

**No P0/P1 semantic issue was found in the assigned metadata/consistency scope.**