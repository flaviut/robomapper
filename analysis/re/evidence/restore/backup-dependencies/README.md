# Backup dependencies: bounded static checkpoint

`evidence.json` owns hash-bound claims BD01–BD05 and their instruction anchors.
`dependencies.json` adds conditional companion roles to the reviewed consistency
predecessor; it is not a complete snapshot manifest or a device procedure.
`focused/*/*.c` is verbatim **decompiler output, not recovered source**, and need not
compile. All 16 entries already existed in the copied baseline. No symbol,
signature, ABI, function boundary or shared annotation was changed.

From the repository root:

```sh
PYTHONDONTWRITEBYTECODE=1 python3 analysis/re/evidence/restore/backup-dependencies/validate.py
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s analysis/re/evidence/restore/backup-dependencies -p test_validate.py -v
PYTHONDONTWRITEBYTECODE=1 python3 analysis/re/evidence/restore/backup-dependencies/replay.py \
  --out "$PWD/analysis/re/evidence/restore/backup-dependencies/scratch/replay-new"
```

Use a new output name. Scratch was ignored before any generation. The replay uses
source-root `retool.py copy`, never directly opens the immutable closed baseline,
then sequentially exports each binary and separately reopens without annotations.
It verifies original input hashes, mapped ELF instruction bytes, path/SQL literal
pointers, a bounded existing thunk branch, all selected C hashes and semantic type
JSON. No firmware is executed. Full projects, inventories and logs stay ignored.
The pinned Ghidra path is supplied by the source-root harness:
`/nix/store/cw1zbnv33wxw1svbsw2a6jl0j6rq7jxh-ghidra-12.0.4/lib/ghidra`.

The checker is a bounded artifact/provenance check, not a semantic proof. The seven
negative/control tests cover byte tampering, nonidentity segment mapping, BSS and
unmapped ranges, odd/wrong entry mappings, absent entry instruction, duplicates
and invalid ELF/ranges. No known predecessor checker bug was changed.

Discovery requested one absent entry (`0x141d1c`); the harness rejected it. No
function was created; a subsequent valid-entry-only batch succeeded. This rejection
was not an infrastructure failure or an authorization to recover that entry.

Open targets: database base initializer and actual journal mode/header; concrete
vmap virtual implementer; deployment configuration roots/existence. A complete
backup/restore or durability conclusion still requires an all-writer epoch/barrier.
