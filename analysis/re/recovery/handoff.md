Implemented and packaged two bounded recoveries; overall status **partial**.

- **Ready:** AppProxy `0x3c5b4`, body `0x3c5b4..0x3c5e9`, 21 instructions; annotated `CatalogBackupExternal`.
- **Ready:** WatchDoge `0x1af18`, body `0x1af18..0x1af69`, 27 instructions; annotated `WdogFeederThread`.
- **Deferred:** librrnavdrv.so seed `0x20bac0` is interior. EHABI and existing Thumb instructions identify candidate `0x20babc`; no startup function, annotation or C was fabricated.

Changed files: `recover.py`, `scripts/RecoverBounded.java`, `validate_recovery.py`, two `requests/*.json`, two `annotations/*.json`; packaging adds `handoff.json`, `USAGE.md`, `diagnostics.json`, `promotion-manifest.json` and this report. All are under `/home/user/tmp/illegalplainape/analysis/re/recovery`.

Validation: `proof-final/validation.json` passed on two pristine private copies. Four recovery results confirm byte identity and unchanged existing functions. Nine rejection cases preserve semantic fingerprints, including failure after disassembly. Baseline/binary bytes are unchanged; relevant C, selected metadata and types match across copies and after reopening without replay. Parent independently confirmed current source/request hashes and no project locks/live Ghidra process in `../tooling/recovery-timeout-snapshot.json`.

Packaging resumed after the original 1800000ms timeout. It changed no validated source, request or annotation and reran no validation, Ghidra, import or discovery. Historical OSGi failures are summarized in `diagnostics.json`; the validated isolated source path is **`scripts/`**.

Artifacts:

- Machine handoff and exact replay commands: `handoff.json`.
- Essential file paths/hashes for promotion: `promotion-manifest.json`.
- Usage and dependency layout: `USAGE.md`.
- Final C/instructions: `proof-final/{a,b}/reopened-AppProxy/` and `proof-final/{a,b}/reopened-WatchDoge/`.
- Pristine after-recovery expectations: `proof-final/a/pristine-{AppProxy,WatchDoge}/selected.json`.
- Candidate evidence: `raw-evidence.json`, `assessment/{AppProxy,WatchDoge,librrnavdrv.so}/evidence.txt`.

Open risks/questions: independent reviewer gate remains required; startup callback and WatchDoge callee `0x1abd8` remain unresolved. Generated C is not recovered source. No cross-process completion, MCU behavior, watchdog acceptance or persistence durability is established.

Recommended next step: preserve executable source in sibling `analysis/re/recovery` and `analysis/re/tooling`, as the parent approved. Allowlist only source/requests/annotations/docs/essential proof, copy evidence summaries as needed, and test the final tracked-layout invocation on a fresh private copy before merging annotations. Do not relocate the unchanged driver under `evidence/recovery`; it loads `../tooling/retool.py`.

```acceptance-report
{
  "criteriaSatisfied": [
    {
      "id": "criterion-1",
      "status": "satisfied",
      "evidence": "Only the two supported hash/entry/bound tuples are recoverable. The interior startup seed is explicitly deferred. Packaging preserved all validated source, requests and annotations."
    },
    {
      "id": "criterion-2",
      "status": "satisfied",
      "evidence": "proof-final/validation.json records two pristine copies, four successful recoveries, nine rejection/no-mutation checks, unchanged original bytes/functions and deterministic reopen exports; promotion-manifest.json identifies essential artifacts by SHA256."
    }
  ],
  "changedFiles": [
    "analysis/re/recovery/recover.py",
    "analysis/re/recovery/scripts/RecoverBounded.java",
    "analysis/re/recovery/validate_recovery.py",
    "analysis/re/recovery/requests/AppProxy.json",
    "analysis/re/recovery/requests/WatchDoge.json",
    "analysis/re/recovery/annotations/AppProxy.json",
    "analysis/re/recovery/annotations/WatchDoge.json",
    "analysis/re/recovery/handoff.json",
    "analysis/re/recovery/USAGE.md",
    "analysis/re/recovery/diagnostics.json",
    "analysis/re/recovery/promotion-manifest.json",
    "analysis/re/recovery/handoff.md"
  ],
  "testsAddedOrUpdated": [
    "analysis/re/recovery/validate_recovery.py"
  ],
  "commandsRun": [
    {
      "command": "python3 validate_recovery.py --out \"$PWD/proof-final\" > proof-final-driver.log 2>&1",
      "result": "passed",
      "summary": "Original run: two pristine copies, four recoveries, nine rejection checks; no rerun during packaging."
    },
    {
      "command": "Python packaging SHA256/reference checks against proof-final/validation.json and promotion-manifest.json",
      "result": "passed",
      "summary": "Current validated source/request hashes match; listed essential files and handoff artifact references exist."
    }
  ],
  "validationOutput": [
    "proof-final/validation.json: status passed",
    "Two functions recovered on each of two pristine private baseline copies",
    "Nine rejected requests: identical before/after semantic fingerprints",
    "Baseline tree and pinned binaries unchanged; existing-function inventory identical except new entry",
    "Relevant C, selected.json and types.json identical across copies and close/reopen without replay"
  ],
  "residualRisks": [
    "Independent reviewer approval and final tracked-layout invocation test remain parent integration steps.",
    "Startup seed 0x20bac0 is interior; candidate 0x20babc remains deferred.",
    "WatchDoge callee 0x1abd8 and cross-process/MCU/durability behavior remain unresolved."
  ],
  "noStagedFiles": true,
  "diffSummary": "Narrow recovery driver/source, two hash-bound requests, schema-v1 name/comment annotations, replay proof and handoff packaging; no shared-tooling/baseline/device edits.",
  "reviewFindings": [
    "No additional packaging blockers found; required independent reviewer gate remains open.",
    "Historical root-script-path OSGi failures are not passing evidence; scripts/ is the validated source path."
  ],
  "manualNotes": "No Git commands or staging performed by this worker. noStagedFiles describes worker actions, not an independent examination of a pre-existing Git index. Parent explicitly approved preserving the sibling recovery/tooling layout."
}
```
