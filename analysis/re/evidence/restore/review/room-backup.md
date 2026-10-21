# Independent static review: room reconciliation and backup dependencies

## Review

**Target:** `416aef9` against `9dc8abc`.

**Owned scope:** `analysis/re/evidence/restore/room-reconcile/**` and `analysis/re/evidence/restore/backup-dependencies/**`.

**Method:** Read-only inspection of the supplied committed-diff artifact, handoffs, findings/claims, focused generated C, selected instruction records, ELF/literal evidence, validators, replay scripts and tests. I also examined the supervisor-supplied original-ELF mapped bytes and LLVM disassembly for the requested ABI/control-flow seams. No repository edits, firmware execution, device access, internet access, nested agents or independent command execution occurred.

**No issues found.**

### Correct: room-reconciliation claims remain appropriately bounded

- **The post-ID helper order is supported, but does not establish final-ID stability.** The selected instruction stream calls `0x12e95c`, `0x12e12c` and `0x12cb14` in order at `0x133090`, `0x13309c` and `0x1330a6`. These are existing selected entries, not newly declared entries at interior anchors. The generated C agrees with that order (`room-reconcile/exports/librrnavdrv.so/0x00132c30.c:272–274`; `room-reconcile/evidence.json:69–280`).

- **The traversal is conditional on geometry, seed, predicates and existing labels.** In `0x12e714`, the instruction sequence calls virtual slot `+0x18`, compares its result with `1`, checks a destination byte, and later requires the neighbor predicate result `-1`, a source predicate result other than `1`, and a nonzero source low-six-bit value before storing `(source & 0x3f) | 0x40`. That is conditional propagation, not byte-preserving grid copying or demonstrated promotion into a stable-ID range (`room-reconcile/evidence.json:570–684, 917–1096`; `exports/librrnavdrv.so/0x0012e714.c:94–126`).

- **The other two stages also retain meaningful spatial dependencies.** The second stage constructs a radius and walks the supplied rectangle; its fallback `0x12d884` remains unexpanded. The third expands/intersects bounds, scans a horizontal midpoint for a labeled cell, then performs four-neighbor traversals using visited/exclusion state. Its selected fill masks the predecessor label and adds `0x40`. The conclusion that unchanged dimensions alone cannot guarantee identical output is a supported inference; full algorithm closure remains explicitly unclaimed (`exports/librrnavdrv.so/0x0012e12c.c:65–131`; `0x0012cb14.c:159–183, 209–220, 360–385`; `0x0012ca58.c:15–39`).

- **Name filtering and ordered replacement are correctly distinguished.** In `0x3c194`, matching a listed ID branches past the copy, while list exhaustion reaches the retained-record copy. Records advance by `0x1c`; the name copy uses a `0x18` bound and preserves the old ID. In `0x3c2a0`, each successive name record is paired with the next unsigned response byte, stored at record `+0x18`. There is no geometric lookup in this pairing (`room-reconcile/evidence.json:2110–2573`; `exports/AppProxy/0x0003c194.c:36–69`; `0x0003c2a0.c:33–60`).

- **The result writer is gated by the selected response branch, not established as automatic reconciliation.** Instructions compare both response words with object `+0xb00/+0xb04`, require a nonzero status byte, copy the pending vector at `+0x3dcc/+0x3dd0`, and pass response IDs beginning at stack `+0x82` to `0x3c2a0`. The later `oldId`/`newId` report does not itself prove correspondence with navigation regeneration, coherent transaction completion or durable persistence (`exports/AppProxy/0x000670dc.c:284–325, 353–368`; `room-reconcile/evidence.json:2575–2890, 3431–3519`).

- **The inferred-void selector is not mistaken for a missing ABI return.** Original-ELF disassembly shows `0x3c180–0x3c184` normalizing `strncmp`’s result in `r0` to zero/equal or one/not-equal, followed by normal return. The narrative correctly accounts for this despite the decompiler’s `void` prototype (`exports/AppProxy/0x0003c148.c:7–26`; `room-reconcile/evidence.json:3153–3342`; supplied `original-elf-readout.txt`, range `0x3c148..0x3c194`).

### Correct: backup-dependency claims preserve configured/active distinctions

- **The database object, first handle and path provenance are connected.** Constructor instructions store the allocated database object at proxy `+0x68` before calling `0x20440`. The opener builds the first pathname from global `0x35367c` and `/rockrobo/robot.db`, passes the output-handle address `database+0x40`, flags `6` and argument `0`, and checks the return. The bounded thunk at `0xe0c04` branches to `0xe06e0`. The prepared `bakmaps` statements use the first handle, while the backup helper retrieves the same proxy database object and forms external ID `native_flag-2` (`backup-dependencies/focused/AppProxy/selected.json:14558–14603`; `0x00020440.c:25–40, 156–193`; `0x0003a430.c:23–51`; `evidence.json:279–713, 2094–2104`).

- **Journal mode remains unresolved rather than inferred from SQLite strings.** The recorded SQL pointers `0x1207c0..0x1207ec` resolve to schema creation and migrations. Neither those calls nor open flags `6` establish the active journal/WAL mode. The manifest correctly leaves deployed base initialization, header state, open success, external users and companion presence unresolved; suffix candidates are conditional, not an unconditional acquisition recipe (`backup-dependencies/evidence.json:35–105, 714–812`; `dependencies.json:8–20`).

- **The configuration root is cached and has its own fallback.** Original instructions show guard-protected environment lookup, construction from `NAV_DYNAMIC_CONFIG_PATH` or the compiled empty string, and return of the cached object. In particular, the branch after `__aeabi_atexit` returns to the normal path; the generated C’s apparent non-returning annotation must not be treated as actual control flow. The caller consumes the returned value and passes it into the configuration constructor (`focused/librrnavdrv.so/selected.json:2547–2584`; `0x00141d68.c:22–39`; supplied original-ELF range `0x141d68..0x141df4`).

- **Final-file loading and staged writing are properly separated.** Constructor mode `2` reaches `Config::readFile` with the final filename. For writes, instructions place object `+0x81` in `r1` for `Config::writeFile`, then call `rename(cache, final)` using object `+0x81` and `+1`. This supports a staging role for `.cache`, not a second normal load source, freshness guarantee, cross-file barrier or power-loss durability claim (`focused/librrnavdrv.so/0x001a6374.c:39`; `0x00141600.c:251–257`; `0x00141c24.c:14–27`; supplied original-ELF ranges `0x141854..0x141862` and `0x141c24..0x141c64`).

- **Vmap dispatch is not conflated with concrete disk I/O.** The accessor computes `store + 4*(flag+6)`. Cases `5` and `6` route positive flags through the two wrappers. Those wrappers load the implementation object at `+0x44` and virtual slots `+0x10`/`+0x0c`; the matching-default branch returns `1` without invoking that virtual method. Original instructions confirm the explicit successful return despite the inferred-void generated C. The concrete implementation and actual file operations remain unresolved (`focused/librrslamdrv.so/selected.json:20–41, 1311–1337, 1519–1545`; `0x00020ad0.c:35–64`; `0x00020c24.c:35–64`; supplied original-ELF range `0x20b0c..0x20b70`).

### Correct: provenance, output policy and replay isolation

- Both lanes label generated C as **decompiler output, not recovered source**. Scratch is lane-local and ignored; generated-C whitespace exceptions do not require rewriting the exported bytes.
- Replay scripts require fresh lane-scratch output paths, copy the baseline before opening a project, and execute exports sequentially. Backup replay additionally reopens the private project for comparison (`room-reconcile/replay.py:17–56`; `backup-dependencies/replay.py:16–35`).
- The harness checks that the baseline is unlocked before copying and refuses direct baseline project runs. Export entry lookup requires an existing function and executable instruction; these replay invocations request no annotations (`analysis/re/tooling/retool.py:57–60, 109–142`; `ReTool.java:64–74, 220–234`).
- The checkers and tests are appropriately characterized as artifact/provenance checks—not algorithm emulation or semantic/runtime certification (`room-reconcile/validate.py:36–85`; `backup-dependencies/validate.py:44–135`).

## Checked commands and reported results

**These executions belong to the parent, not this reviewer.** I inspected the status records and relevant logs under `/tmp/map-restore-review-416aef9/`.

| Parent command/check | Recorded result |
|---|---|
| `python3 analysis/re/evidence/restore/room-reconcile/validate.py` | Pass: 2 binaries, 15 functions, 3,707 instruction records, 531 anchors |
| Room `unittest discover … -p test_validate.py -v` | Pass: 5 tests |
| `python3 analysis/re/evidence/restore/backup-dependencies/validate.py` | Pass: 16 functions, 4,363 instruction records, 36 literals |
| Backup `unittest discover … -p test_validate.py -v` | Pass: 7 tests |
| Room replay to `scratch/parent-review-416aef9` | Pass: fresh private copy; both program exports compared |
| Backup replay to `scratch/parent-review-416aef9` | Pass: fresh private copy; three program exports and separate reopens compared |
| `git diff 9dc8abc 416aef9 --check` | Exit code `0` |

`execution-status.json` records all four validators and the broader 26-test suite passing. `replay-status.json` now records all four fresh sequential replays passing. The other two lanes’ semantic reviews are outside my ownership.

## Limitations and bounded acceptance

I did not independently execute validators, tests, hashes, disassembly tools or Git. The committed-range review used the supplied diff artifact and focused files; `watchdog_diff` was not used as a substitute for committed-range evidence. The raw-ELF readout was produced by the supervisor; my instruction/ABI interpretation was independent. Incidental preceding-symbol labels and forced-Thumb renderings of ARM PLT bytes were not treated as function-entry or control-flow proofs.

The disclosed gaps remain open: complete postprocessor/fallback closure, upstream response/name-order correspondence, deployed roots and file existence, actual journal mode, concrete vmap implementation, cache freshness, all-writer quiescence and a shared snapshot epoch. None is converted here into a runtime guarantee or a generalized edit/restore-safety conclusion.

- **Fixed:** None; review-only.
- **Finding:** None qualifying within the assigned diff scope.
- **Merge verdict: OK** for this **bounded static-evidence checkpoint only**. This is not operational backup/restore approval, coherent-snapshot certification or durability certification.