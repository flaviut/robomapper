# Shared Ghidra tooling

Use one private copy of the saved baseline per component worker. `retool.py` reopens that copy, replays hash-bound annotations, and exports only the functions you select. It never runs firmware. C files are **decompiler output, not recovered source**, and need not compile.

## Start in a private project

Use Python 3 and the Ghidra 12.0.4 installation pinned in the [manifest](../../../analysis/re/manifest.json). The harness selects its headless launcher and OpenJDK; no pip packages or Java PATH changes are needed. This copy workflow requires the local, untracked `analysis/re/baseline/` cache. Without it, use the [repository-only replay](../../research/static-recovery.md#artifacts-and-replay), which can import tracked binaries privately.

Close private projects before headless operations. Never open or modify the baseline itself. From the repository root, choose a new workspace:

```sh
T="$PWD/analysis/re/tooling"
W=$(mktemp -d /tmp/retool.XXXXXX)
cd "$W"
P="$PWD/ghidra-project"
python3 "$T/retool.py" copy "$P"
python3 "$T/retool.py" run "$P" librobopersist.so \
  --functions 0x1ab94 --out "$PWD/exports-initial"
```

The destination and every output directory must be new. A successful run prints `OK`, exits zero, and leaves `result.json` with `status: ok`. `invocation.json` records the actual headless argv, return code, script result, and successful project-save check. If Ghidra reports an error but exits zero, the wrapper still fails. Inspect `console.log`, `ghidra.log`, `script.log`, and `result.json` in that output directory.

`selected.json` contains verified entry addresses, signatures, comments, caller addresses, instructions/bytes, Thumb state, and loader-derived entry file offsets. Each selected function has its own `0x........c` file with program identity, SHA256, and VA. `types.json` lists persisted `/shared` types. Add `--inventory` to write metadata for all functions and memory blocks **without** decompiling the whole binary.

Program selectors are exact program names or full SHA256 values from the private project's copied `index.json`:

- `librobopersist.so`, `librrslamdrv.so`, `librrnavdrv.so`, `librrutils.so`
- `AppProxy`, `WatchDoge`, `libuart_api.so.4.0.2`

All three manifest `libuart_api.so*` aliases map to the single resolved-content program `libuart_api.so.4.0.2`. The tracked [baseline summary](../../../analysis/re/tooling/baseline-summary.json) records import, architecture, image-base and executable-range metadata. Its log paths may name untracked local artifacts. The cache is `analysis/re/baseline/pinned.gpr` plus `pinned.rep`; the empty `.gpr` marker is normal. The harness copies both and the identity index.

## Apply your findings, then reopen and recheck

Keep one annotation document per binary SHA256. After writing `annotations.json` in the private workspace using the format below, run:

```sh
python3 "$T/retool.py" run "$P" librobopersist.so \
  --annotations "$PWD/annotations.json" \
  --functions 0x1ab94 --out "$PWD/exports-annotated"

# A separate process closes/reopens the saved database. No replay in this command.
python3 "$T/retool.py" run "$P" librobopersist.so \
  --functions 0x1ab94 --inventory --out "$PWD/exports-rechecked"
```

Compare the relevant `selected.json`, `types.json`, and C files. The harness emits no timestamps in semantic exports; the first C comment is an identity header. Logs and `invocation.json` contain run-specific paths/timing and should not be compared as semantic output. Do not run two Ghidra processes against the same private project.

### Annotation format (version 1)

The [annotation schema](../../../analysis/re/tooling/annotations.schema.json) is an editor/reference schema. Runtime checks reject unsupported fields, wrong hashes, non-entry/odd anchors, duplicate anchors, ambiguous names, and conflicting annotations. The following is the **smoke fixture**, not a component finding; artificial `ReSmoke*` names belong only in disposable smoke projects:

```json
{
  "version": 1,
  "sha256": "3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6",
  "types": [
    {"name": "ReSmokeU32", "declaration": "typedef unsigned int ReSmokeU32;"}
  ],
  "functions": [
    {
      "address": "0x1ad68",
      "name": "ReSmokeHwInit",
      "signature": "void ReSmokeHwInit(void)",
      "plate_comment": "Tooling smoke only: verified Thumb entry; void/no-argument init signature.",
      "expect": {
        "name": "FUN_0001ad68",
        "signature": "undefined FUN_0001ad68()",
        "plate_comment": null
      }
    }
  ]
}
```

Use exact current `name`, `signature`, and `plate_comment` values from `selected.json` as `expect` values for fields you change. Omit fields you are not changing. An already-applied identical value is allowed. A different existing value requires an explicit matching expectation; never change expectations just to suppress an unexplained conflict. Signature replay also records the normalized resulting prototype in the program, so the same annotation remains replayable after renaming and after reopening.

Signatures use C declarations without a trailing semicolon. Their identifier is parsed but does not rename the function: `name` controls renaming separately. Existing calling conventions are preserved. This is an ABI-level annotation path, not a C++ source/ABI reconstruction engine; check hidden result pointers and other demangler mistakes against instructions before proposing signatures. Plate comments are durable comments at function entries; `null` removes one only when the current value matches `expect`.

Shared type proposals are ordered `name`/C `declaration` pairs. Each declaration must yield the named type (for example a typedef, named structure, or enum). Proposals are parsed with the target program's data organization and existing types, then stored under `/shared`. Use globally distinct type names and list dependencies first. Reuse the same proposals in the `types` arrays of other binary-specific documents when needed. Incompatible existing definitions or dependency types fail rather than creating `.conflict` types or silently overwriting them. This is not a general header importer: keep each proposal to one named definition and avoid embedded named definitions or includes. Conflicting proposals must be reconciled explicitly before integration.

Annotations run in a transaction: any anchor, conflict, parsing, or decompilation failure rolls back that run's annotations. A failed run's partial exports are **not** authoritative. Python rejects a mismatched annotation hash before launching Ghidra; the Java script independently hashes the stored original imported file bytes and checks both request and annotation identities before mutation. Existing baseline symbols are retained; bootstrap applies no annotation documents.

### Addresses: do not subtract a fixed base

All keys and `--functions` arguments are **even virtual instruction addresses**, not file offsets or Thumb-tagged symbol values. An address inside a function is rejected rather than guessed into an entry. Use inventory plus actual instructions to identify boundaries.

The importer explicitly uses the minimum ELF PT_LOAD VA as its image base: `0` for these shared objects and `0x10000` for AppProxy/WatchDoge. This avoids Ghidra's default extra `0x10000` relocation for ET_DYN. The pinned language is `ARM:LE:32:v8`, compiler `default`; this is the selected Ghidra language, not a claim that the device CPU implements ARMv8. ARM/Thumb state is per instruction context (`TMode`), not inferred from a binary-wide label.

The verified librobopersist entry `0x1ab94` has file offset `0x1ab94`, ELF symbol value `0x1ab95` (Thumb), and first bytes `2de9f047`. The verified WatchDoge entry `0x1ad68` has file offset `0xad68` and first bytes `2de9f041`. `entry_file_offsets` and inventory block `sources` come from Ghidra's actual loader mappings; use those instead of assuming a constant subtraction, especially for data/BSS or relocated regions.

## Reproduce the disposable proof

The historical reviewed proof was under `analysis/re/tooling/smoke-proof-reviewed/`; it is untracked local state. The command below creates two new private baseline copies **only inside tooling**, imports no additional firmware, applies a rename/signature/shared type/comment, verifies caller C, reopens, replays onto the other copy, and checks rollback/rejection cases and pinned hashes:

```sh
python3 "$T/smoke_test.py" --out "$T/smoke-proof-$(date +%s)"
```

If the historical `smoke-proof-reviewed/annotations.json` fixture is available locally, use another disposable tooling copy for the same apply/export path by hand. These commands do not work from a clean checkout without that fixture:

```sh
S="$T/smoke-doc-$(date +%s)"
python3 "$T/retool.py" copy "$S/project"
python3 "$T/retool.py" run "$S/project" WatchDoge \
  --annotations "$T/smoke-proof-reviewed/annotations.json" \
  --functions 0x1ad68 0x142e4 --out "$S/applied"
python3 "$T/retool.py" run "$S/project" WatchDoge \
  --functions 0x1ad68 0x142e4 --out "$S/reopened"
```

The real caller at `0x142e4` has direct calls at `0x144a6` and `0x14dce`; both caller C sites reflect the rename. The librobopersist smoke exports only `GetMapInfoPersistFileName` at `0x1ab94`. No map-persistence or watchdog behavior conclusions are introduced by this proof.

## Boundaries and diagnostics

Local-variable renames, arbitrary instruction comments, automatic function creation, calling-convention changes, general C++ declarations, and multi-program atomic transactions are not supported. Apply one binary/document per invocation; keep shared proposals reviewable as JSON. Ghidra's analysis/decompiler warnings remain in logs; inferred types and C output still require component-level instruction review.

The tracked [API evidence](../../../analysis/re/tooling/api-evidence.json) records the installed source archives/examples used to verify the APIs. Historical `smoke/`, `bootstrap/` and bootstrap-finalization logs are untracked local state, not checkout requirements for reading the reference. Bootstrap is one-time and refuses an existing baseline. Do not rerun it over a cache, remove locks, or bypass failed dependency/API checks; preserve the logs and resolve the cause.
