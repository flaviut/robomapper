# rr_loader writer-host checkpoint

**Static analysis only; no safe stop/restore procedure is established.** Start ref
`6cd68d68070400ddd8a327f1c3e09538df01fd63`. Only this new evidence subtree is owned.
`proof/c/*.c` is **Ghidra decompiler output, not recovered source**, and need not
compile. No firmware execution, device access or internet source searches were
used. No surviving signature/name/ABI, shared annotation, tooling, manifest, prior
lane artifact, firmware or saved configuration was changed. No new function was
created. No `AGENTS.md` was found in this checkout, source root, or inspected
ancestor directories.

## Useful findings

1. **There is an embedded configuration.** Absence of a saved external
   `config.json` does not leave loader ownership wholly unknown. `RRConf::init`
   (`0x19da8`) uses `rr_unpacking(json_config,json_config_len)` when the copied
   path is empty; a nonempty path opens that file instead. `parseArg` (`0x17fbc`)
   accepts `-c FILE` and a positional path. The `./config.json` string is not by
   itself a default file-open contract.
2. **Embedded configured ownership includes navigation and SLAM.** Host-only
   AES-128-CCM decoding authenticated the embedded payload and produced
   `pluginsPath=/opt/rockrobo/cleaner/lib`, with plugins in order: support, logger,
   chassis, laser, SLAM (`librrslamdrv.so`), navigation (`librrnavdrv.so`), carpet.
   Only common plugin fields and hashes are published; not the full plaintext.
   All seven corresponding tracked binaries export `rr_load_plugin`.
   `librobopersist.so` is not a separate plugin in this list; the predecessor
   navigation import evidence identifies its persistence dependency.
3. **Generic host capability is separately instruction-backed.** The loader
   requires a plugins array, uses byte-sized array indices for IDs, constructs
   `pluginsPath + '/' + common.plugin`, calls `dlopen(...,0x102)` and
   `dlsym(...,"rr_load_plugin")`, validates callback slots and calls its generic
   initialization callback. See `claims.json` and `proof/selected.json`.
4. **SIGHUP is a flag request, not a flush barrier.** The signal-table record at
   VA `0x2f1c8` points signal 1 to `0x18ad5` (Thumb). The existing trampoline at
   `0x18ad4` forwards to `dealSignal`; for SIGHUP, the instruction path stores 1
   at loader `+0x9c`. It does not directly flush/join/acknowledge writers or emit
   a heartbeat. The preserved `dealSignal(int,siginfo_t*)` prototype does not
   correctly describe register usage; semantic claims use the instructions,
   not a speculative signature correction.
5. **Generic cleanup contains callbacks and joins, not a proven map barrier.**
   `main` calls loader final after successful init. Final first joins the timer
   thread, then finalizes plugins in reverse key order. Per-plugin final sets
   its quit byte, wakes conditions/queue, calls optional slot `+0x10`, joins its
   stored thread if nonzero, then calls slot `+0x14`. We have not connected all
   quit consumers, identified concrete nav/SLAM final callbacks, or shown that
   detached persistence workers and file/catalog/database/cache state finish.
   The timer join can block before plugin-final callbacks; successful shutdown
   is not inferred from this call order.

These are **embedded defaults and generic capability**, not active runtime
modules/argv/configuration. Saved ProcessList records in predecessor
`lifecycle/configuration.json` name `rr_loader -d` (and MT `-d -s`) without an
explicit config path, but are not authenticated active deployment. This remains
conditional linkage, not a device observation. The `0x18314` diagnostic thread
has a bounded pseudo-decode and original EHABI start evidence, **not a newly
created function or CFG recovery**; it is not claimed as a heartbeat producer.
The previous WatchDoge `0x1abd8` recovery was not redone.

## Replay and validation

Pinned source-root harness: `/home/user/tmp/illegalplainape/analysis/re/tooling`.
Pinned Ghidra:
`/nix/store/cw1zbnv33wxw1svbsw2a6jl0j6rq7jxh-ghidra-12.0.4/lib/ghidra`.
The replay first calls that harness's `retool.py copy` into a **new ignored
lane-local** project. Since rr_loader is not in the seven-program baseline,
`import_export.py` reuses the documented private tracked-input import path via
`retool.headless`; it checks tracked input SHA256 before import and never
extends the shared manifest/index. The private program retains
`ARM:LE:32:v8`, compiler `default`, image base `0x10000`, per-entry Thumb state.

```sh
L=analysis/re/evidence/restore/writer-host
PYTHONDONTWRITEBYTECODE=1 python3 "$L/evidence.py"
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s "$L" -p test_writer_host.py -v
PYTHONDONTWRITEBYTECODE=1 python3 "$L/replay.py" --out "$PWD/$L/.scratch/review-new"
git diff --check
```

Use a **new** output directory. Projects, full inventories and logs remain
ignored under `.scratch/`. Replay imports selected entries, separately reopens
without replay, checks selected/types/C equality, runs a read-only pseudo-decode,
reconstructs bounded ELF and configuration evidence, and compares every
published proof file. The standalone validator verifies original PT_LOAD bytes,
original FUNC-symbol/EHABI entry identities, C hashes/headers, plugin hashes and
exports, signal-table bytes, strings and claim anchors. Eight tests include
changed instruction, odd/unmapped VA, corrupted ciphertext/tag/AAD rejection.

The static data decoder calls a **native host ELF64 x86_64** OpenSSL library
whose architecture and SHA256 are checked **before loading**. Its exact pinned
path/version/hash, payload offsets, nonce/AAD/key-source coordinates and tag
parameters are in `proof/configuration.json`. The first dependency selection
attempt failed before decryption with `wrong ELF class: ELFCLASS32`; after
supervisor approval, a verified native ELF64 library was selected in the same
host-only saved-data protocol. No firmware library was loaded/executed. Host
CCM authentication corroborates the algorithm/extraction, not vendor origin,
runtime deployment or safety. Changing this host dependency requires explicit
review rather than silently changing decoding mode.

## Next bounded seam

Read the concrete `rr_load_plugin` export and callback table in **already pinned**
`librrnavdrv.so:0x5f830` and `librrslamdrv.so:0x6c14`; trace slots `+0x10/+0x14`
to persistence-worker joins/flushes or record the missing edges. Separately,
connect the loader quit byte to timer/plugin quit consumers. Normal MCU heartbeat
production and hardware acceptance remain open; no MCU image was selected.
No device stop sequence is proposed. Byte equality, replay, generic joins and
CCM success are not semantic proof, all-writer quiescence, durability or restore
safety. Independent static review is still required.
