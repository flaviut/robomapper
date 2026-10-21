# Replay the two bounded recoveries

Keep `analysis/re/recovery` beside the existing `analysis/re/tooling`. The validated driver loads `../tooling/retool.py` and uses **`scripts/`**, not the recovery root, as Ghidra's script path. Do not relocate the executable driver under `evidence/recovery` or duplicate the harness.

AppProxy `0x3c5b4` and WatchDoge `0x1af18` passed the two-pristine-copy proof in `proof-final/validation.json`. Startup seed `0x20bac0` is interior to the EHABI candidate `0x20babc`; neither startup address is recovered here.

Run recovery **before** merging annotations. Use a new private copy and fresh output directories; keep projects closed. From this directory:

```sh
T="$PWD/../tooling/retool.py"
P="$PWD/integration-private/project"
python3 "$T" copy "$P"
python3 recover.py "$P" requests/AppProxy.json --out "$PWD/integration-private/recover-AppProxy"
python3 recover.py "$P" requests/WatchDoge.json --out "$PWD/integration-private/recover-WatchDoge"
python3 "$T" run "$P" AppProxy --annotations "$PWD/annotations/AppProxy.json" --functions 0x3c5b4 --inventory --out "$PWD/integration-private/applied-AppProxy"
python3 "$T" run "$P" WatchDoge --annotations "$PWD/annotations/WatchDoge.json" --functions 0x1af18 --inventory --out "$PWD/integration-private/applied-WatchDoge"
python3 "$T" run "$P" AppProxy --functions 0x3c5b4 --inventory --out "$PWD/integration-private/reopened-AppProxy"
python3 "$T" run "$P" WatchDoge --functions 0x1af18 --inventory --out "$PWD/integration-private/reopened-WatchDoge"
```

Expect `OK`, `result.json` status `ok`, and `invocation.json` success/save confirmation. Compare relevant C, `selected.json` and `types.json` between applied and reopened exports. Reopen commands replay neither recovery nor annotations. Recovery itself intentionally refuses an already-created function.

`handoff.json` records candidate decisions, bounds, semantics and exact artifact paths. `promotion-manifest.json` hashes the essential source and proof files; exclude private projects. Parent integration will preserve the sibling source layout, copy essential evidence summaries into tracked evidence, and test that final invocation path on a fresh private project. That integration test was not run during packaging.

`diagnostics.json` preserves superseded root-script-path OSGi failures and the transaction-rollback diagnosis. Only `proof-final` is authoritative. No types or signatures were imposed; annotation expectations come from pristine **after-recovery** exports. Generated C is decompiler output, not recovered source. No cross-process completion, MCU behavior or persistence durability is inferred.
