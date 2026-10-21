## Review

**Target:** `416aef9` against `9dc8abc`  
**Scope:** `analysis/re/evidence/restore/native-route/**` and `analysis/re/evidence/restore/writer-host/**` only.

Reviewed the supplied committed-diff artifact, handoffs, claims, focused generated C, instruction/ELF records, replay/checker sources, tests, and parent execution artifacts. No edits, command execution, firmware execution, device access, internet access, or nested agents were performed.

Paths below use:
- **N:** `analysis/re/evidence/restore/native-route`
- **H:** `analysis/re/evidence/restore/writer-host`

### Correct

#### Native receiver and conditional completion

- **Receiver lookup direction and channel distinction are supported.** The receive path supplies `r0=2` to `RecvPacketEx`. Its table loop compares the complete received wire word, then reads the native event from the eight-byte row. Original table records distinguish load/save/save-set events `0x55/0x54/0xb3` from result events `0x52/0x70`. Predecessor IPC instructions give channel index **53 for `(3,2)`**, not controller index 19. No controller forwarding edge is asserted. Evidence: `N/bounded.json:463–510,759–874`; `N/elf-evidence.json:5–36`; predecessor `flow/instructions.json:15655–15693`.

- **Payload forwarding does not establish validation or scheduling.** Zero packet length leaves a null payload pointer; nonzero length selects packet `+0xc`. The callback loop forwards the event and payload pointer without establishing a required 16-byte load request or validating map flags. Subscriber registration and scheduling into the selected load task remain explicitly unclosed. Evidence: `N/bounded.json:865–901,1291–1418`; `N/claims.json`, `payload-forwarding-boundary`.

- **The load-task capture is supported by register flow, not merely generated C.** `0x69076` calls `0x68428`, and `0x69080` saves its raw `r0` return. Subsequent stores place two captured words at allocation `+0x20/+0x24`, flag at `+0x28`, and saved return at `+0x2c`; selector and core are separately captured. The original pointer calculation reaches VA `0x304b78`, file offset **`0x2f4b78`**, containing Thumb-tagged `0x683e1`. Evidence: `N/selected.json:78–287`; `N/elf-evidence.json:64–69`; parent raw-ELF readout.

- **The candidate completion remains pseudo-disassembly, not a recovered function.** The bounded bytes show comparison against selector `0x55`, `ITE EQ` selecting event `0x52` versus `0x70`, payload address subobject `+0x10`, and dispatch through `0x67ad0`. The explicit IT instruction supplies the condition despite the exporter using a fresh private context per instruction. Actual invocation, timing, function-boundary/CFG recovery and scheduling are not established. Evidence: `N/bounded.json:3–183`; `N/RouteBounded.java:24–27`; `N/claims.json`, `load-return-to-local-completion` and limits.

- **Four-word serialization is supported for both claimed result events.** The encoder searches event-to-wire in the opposite direction. Its bit-test branch includes `0x52` and `0x70`; `0x18fa06..0x18fa1a` copies input words `+0,+4,+8,+12` unchanged and sets length 16. The outgoing region calls this encoder and selects direct `SendPacket` or the `0x190400` branch. This does not close the subscriber connection from local completion to outgoing dispatch. Evidence: `N/selected.json:2499–2615,3035–3088,6311–6365`; `N/c/0x0018f1d4.c:490–499`; `N/bounded.json:3190–3219,4040–4088,4682–4713`.

- **ARM/Thumb interworking is corroborated.** I inspected the refreshed original-ELF readout’s ARM-mode native PLT disassembly. The `RecvPacketEx` veneer at `0x3c320` resolves through GOT `0x317100`, and `SendPacket` at `0x3c444` through GOT `0x31715c`, matching their `R_ARM_JUMP_SLOT` records. The raw bytes are unchanged. The earlier forced-Thumb PLT mnemonics were not used in the semantic assessment. Evidence: `/tmp/map-restore-review-416aef9/original-elf-readout.txt:401–446`.

#### Writer-host configuration, ABI and cleanup

- **Embedded versus external configuration selection is correctly bounded.** The hidden-result call copies the configuration-path string; its length at string data `−0xc` controls the branch. Empty selects the embedded pointer/length and `rr_unpacking`; nonempty opens the external path. Argument parsing supports `-c FILE` and a positional path. The `./config.json` string is not treated as proof of a default external open. Evidence: `H/proof/selected.json:7489–7575`; `H/proof/c/0x000181f0.c:9–18`; `H/proof/c/0x00017fbc.c:32–65`.

- **CCM extraction matches the call ABI, and host-library loading is guarded.** Instructions construct the 16-byte XOR key, subtract four bytes for the trailing tag, and supply AAD length 8, tag length 4 and nonce length 13 through registers and stack arguments. The original-ELF readout corroborates the embedded pointer, length and nonce pointer. Before loading the host crypto library, the decoder verifies its pinned SHA256 and ELF64/little-endian/x86-64 identity. Authentication requires successful `EVP_DecryptUpdate`; altered ciphertext, tag and AAD have rejection tests. Evidence: `H/proof/selected.json:8571–8820`; `H/config_data.py:34–76`; `H/test_writer_host.py:36–64`.

- **Configured plugins are not overstated as active deployment.** The authenticated embedded configuration identifies seven configured plugins, including SLAM index 4 and navigation index 5. Generic loading narrows indices to a byte, constructs the configured path, uses numeric `dlopen` flags `0x102`, resolves `rr_load_plugin`, validates slots `+4/+8/+0x14`, and calls slot `+4` with plugin-control pointer `+0x9c`. Export presence is kept distinct from execution or successful writer completion. Evidence: `H/proof/configuration.json`; `H/proof/selected.json:2384–2419,6360–6550`; `H/claims.json`, `configured-navigation-host` and `plugin-loading-contract`.

- **Signal 1 sets a flag; it is not a flush barrier.** The signal-table record binds signal 1 to Thumb pointer `0x18ad5`. The trampoline obtains the loader in `r0`, moves the original signal into `r1`, and tail-branches to `dealSignal`. Signal 1 reaches `strb 1,[loader,+0x9c]`, avoiding the diagnostic/raise arm. This correctly relies on instructions rather than the misleading surviving prototype. Evidence: `H/proof/elf-evidence.json:298–305`; `H/proof/selected.json:5420–5520,5687–5736`.

- **Cleanup callback/join ordering is accurately qualified.** Loader final calls timer final before plugin-manager final. Per-plugin final sets its local quit byte, wakes conditions/queue, calls optional slot `+0x10`, joins the recorded thread when nonzero, then calls slot `+0x14`. The join branch returns to the slot-`+0x14` path. These facts do not establish successful timer termination or concrete navigation/SLAM persistence-worker completion. Evidence: `H/proof/selected.json:3950–4020,7218–7415`; `H/proof/c/0x00016874.c:11–20`; `H/proof/c/0x00017038.c:24–35`.

#### Replay isolation and publication

- Both replays require **new lane-local ignored scratch outputs**, obtain private projects through the source-root closed-baseline copy operation, and execute sequentially. Host import checks tracked input identity and does not extend the baseline index. No annotation or entry-repair request is supplied. Evidence: `N/replay.py:43–65`; `H/replay.py:18–58`; `H/import_export.py:31–47`; `analysis/re/tooling/retool.py:109–143`.
- Configuration publication is restricted to selected fields, hashes and extraction provenance—not full plaintext. Projects, inventories and logs remain scratch outputs. Generated C is explicitly labeled decompiler output. Canonical JSON packaging preserves fields rather than treating ordering differences as semantic drift. Evidence: `H/config_data.py:80–86`; `H/evidence.py:65–94`; lane `.gitignore`/`.gitattributes`; `N/replay.py:16–35` and its regression test.

### Findings and fixes

**No issues found.**

No fixes were applied. Disclosed subscriber/scheduler, active-deployment and writer-quiescence gaps are not additional defects or blockers for this bounded static checkpoint. The corrected external readout changes neither committed evidence nor the verdict.

### Checked commands and results

These are **parent-executed results inspected by this reviewer**, not independently executed commands.

| Command/check | Inspected result |
|---|---|
| Native `validate.py` | PASS: 1 binary hash, 4 C files, 2,616 instruction-byte checks, 9 claim anchors, 6 ELF-boundary checks |
| Native unittest discovery, `test_native_route.py` | PASS: 6 tests |
| Host `evidence.py` | PASS: 19 original-ELF entries, 1,299 selected instruction records, 99 pseudo records, authenticated configuration and seven plugin identities |
| Host unittest discovery, `test_writer_host.py` | PASS: 8 tests |
| Fresh native replay into `scratch/parent-review-416aef9` | PASS: fresh copy, separate reopen, six helper-selected focused artifacts identical |
| Fresh host replay into `.scratch/parent-review-416aef9` | PASS: private import/reopen, authenticated decode and helper-defined focused comparisons |
| `git diff 9dc8abc 416aef9 --check` | Exit 0; empty diagnostic log |

Inspected sources: `/tmp/map-restore-review-416aef9/execution-status.json`, `replay-status.json`, corresponding native/host validator/test/replay logs, and the refreshed `original-elf-readout.txt`.

**Final parent status:** all four validators, 26 tests, committed diff-check and all four fresh sequential replays passed at exact `416aef9`; no replay failure remains pending. Replay acceptance means **each helper’s defined comparisons passed**, not that every generated artifact was compared. The other two lanes’ semantics are outside this review.

### Limitations and acceptance boundary

- No command runner was available to this reviewer. Original-ELF corroboration used the requested supervisor-provided readout, including its corrected ARM-mode native PLT decoding.
- Replays require supported ignored source-tree scratch; arbitrary external-output replay support is not claimed.
- Equality, hashes and CCM authentication establish artifact consistency/authenticated decoding—not semantic correctness, trusted origin, active deployment or runtime safety.
- No function-entry repair was performed. Native `0x683e0` remains a candidate pseudo-decode; host `0x18314` is not presented as a recovered CFG or proven heartbeat producer.
- End-to-end result provenance, all-writer quiescence, flush/durability, coherent backup/restore and hardware/watchdog acceptance remain unestablished.
- The review target remains `416aef9`; subsequent integration metadata is not included in this verdict.

### Merge verdict: **OK with notes**

Accept these two lanes as a **bounded static evidence checkpoint** at `416aef9`, retaining their stated qualifications. This is **not approval for a device stop or restore procedure**.