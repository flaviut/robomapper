# Replay the two bounded recoveries

The recovery driver creates the bounded AppProxy `0x3c5b4` and WatchDoge `0x1af18` functions before applying their annotations. The [two-copy proof](../../analysis/re/evidence/recovery/proof-final/validation.json) records the original validation. Startup seed `0x20bac0` is interior to candidate `0x20babc`; neither startup address is recovered by this driver.

For the full indexed delivery, prefer the [repository-only replay](../research/static-recovery.md#artifacts-and-replay). The commands below require a closed local baseline and the pinned Ghidra installation described in [shared tooling](../reference/tools/retool.md).

Keep executable sources in sibling `analysis/re/recovery/` and `analysis/re/tooling/` directories. The driver loads `../tooling/retool.py` and uses recovery's **`scripts/`** as Ghidra's script path. Moving documentation does not change that dependency.

## Recover, annotate and reopen

Run from the repository root. Choose new project/output directories and keep projects closed:

```sh
T="$PWD/analysis/re/tooling/retool.py"
R="$PWD/analysis/re/recovery"
W=$(mktemp -d /tmp/recovery-replay.XXXXXX)
P="$W/project"
python3 "$T" copy "$P"
python3 "$R/recover.py" "$P" "$R/requests/AppProxy.json" --out "$W/recover-AppProxy"
python3 "$R/recover.py" "$P" "$R/requests/WatchDoge.json" --out "$W/recover-WatchDoge"
python3 "$T" run "$P" AppProxy --annotations "$R/annotations/AppProxy.json" --functions 0x3c5b4 --inventory --out "$W/applied-AppProxy"
python3 "$T" run "$P" WatchDoge --annotations "$R/annotations/WatchDoge.json" --functions 0x1af18 --inventory --out "$W/applied-WatchDoge"
python3 "$T" run "$P" AppProxy --functions 0x3c5b4 --inventory --out "$W/reopened-AppProxy"
python3 "$T" run "$P" WatchDoge --functions 0x1af18 --inventory --out "$W/reopened-WatchDoge"
```

Expect `OK`, `result.json` status `ok`, and `invocation.json` success/save confirmation. Compare C, `selected.json` and `types.json` between applied and reopened exports. Reopen commands replay neither recovery nor annotations. Recovery refuses an already-created function; do not rerun it on the annotated project.

## Evidence and limits

The [handoff](../../analysis/re/recovery/handoff.json) records candidate decisions, bounds and semantics. The [promotion manifest](../../analysis/re/recovery/promotion-manifest.json) hashes essential source and proof artifacts; paths to private projects are historical. [Diagnostics](../../analysis/re/recovery/diagnostics.json) preserves superseded root-script-path OSGi failures and the transaction-rollback diagnosis. Only the final proof is passing evidence.

No types or signatures were imposed by recovery. Annotation expectations come from pristine after-recovery exports. Generated C is decompiler output, not recovered source; no cross-process completion, MCU behavior or persistence durability follows from this proof.
