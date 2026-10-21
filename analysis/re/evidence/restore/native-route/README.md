# Native map route — bounded partial static checkpoint

This lane starts at `6cd68d6` and owns only this subtree. `claims.json` contains the supported statements and unclosed edges; `elf-evidence.json` binds table rows, callback pointer and EHABI observations to original `librrnavdrv.so` bytes and SHA256. No firmware was executed and no device was accessed.

## Useful new seam

Native IPCClient receive-loop region `0x18e91c` calls `RecvPacketEx(2)` and translates complete wire IDs through the table at `0x2a2f4c`:

| AppProxy request | Native event |
|---|---|
| `0x02033203` save | `0x54` |
| `0x02033204` load | `0x55` |
| `0x02033212` save-set | `0xb3` |

These are the `(3,2)`, index-53 requests established by predecessor IPC instructions, **not** controller `(1,2)`, index-19 event `0x3c`. The lower-level queue-open implementation and native subscriber/task scheduling remain unclosed.

Existing load task `0x6905c` retains the load return in a four-word completion payload with the two captured request words and map flag. The original ELF callback table at VA `0x304b78` points to Thumb `0x683e1`. Bounded **read-only pseudo-disassembly**, not function recovery, shows the candidate completion selecting local result `0x52` for original selector `0x55`, otherwise `0x70`, and dispatching those four words via `0x67ad0`. The native encoder separately maps `0x52` to wire `0x03022302` and `0x70` to wire `0x01022106`, copying four words unchanged with length 16.

The subscriber connection into the load task, actual completion invocation/scheduling, and subscriber connection from local result dispatch to wire sender are **not established**. This is not an end-to-end AppProxy completion claim, completed persistence write, or runtime-safe restore procedure.

## Artifacts

- `c/*.c`: four selected **decompiler outputs, not recovered source**; original baseline signatures/names/ABI retained.
- `selected.json`: focused entry metadata, instruction bytes and C hashes.
- `bounded.json`: existing listing in two IPC regions plus separately labeled linear Thumb pseudo decode of `0x683e0..0x6841f`. No guessed function was created. The callback address is **not** an exact EHABI start.
- `RouteBounded.java`: read-only listing/pseudo-decoding exporter. Its extra discovery ranges remain ignored when packaging; pseudo context is private and never stored in the program.
- `RouteDiscover.java`: read-only original discovery script; no inventory or full discovery output is tracked.
- `validate.py`, `test_native_route.py`, `replay.py`: original-ELF consistency checks, rejection/regression tests, fresh sequential replay.

Projects, inventories, complete discovery outputs and logs are ignored under `scratch/`. Baseline copies are made only using `/home/user/tmp/illegalplainape/analysis/re/tooling/retool.py copy`; the closed baseline is never opened directly. The pinned Ghidra installation is the path in `replay.py`.

## Reproduce

From the worktree root:

```sh
PYTHONDONTWRITEBYTECODE=1 python3 analysis/re/evidence/restore/native-route/validate.py
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s analysis/re/evidence/restore/native-route -p test_native_route.py -v
PYTHONDONTWRITEBYTECODE=1 python3 analysis/re/evidence/restore/native-route/replay.py \
  --out analysis/re/evidence/restore/native-route/scratch/replay-NEW
```

The replay output must be new. It sequentially copies the baseline, exports existing entries, separately reopens/exports, performs the read-only bounded decode and compares six focused artifacts. It does not import extra firmware or apply annotations.

Initial replay reproduced a checker bug: Java `Map.of` JSON key ordering varies between JVM processes even when parsed records are identical. Packaging now canonicalizes bounded JSON, with a regression test exercising reordered keys. Instruction bytes and C remain exact comparisons. Exploratory pseudo-decoder API/context errors are retained in ignored scratch; the final exporter uses a fresh private context and Thumb low-bit target per pseudo instruction. Successful replay and byte equality are **not semantic or runtime proof**.

Next bounded target: event `0x55` and `0x52` subscriber registration/scheduler closure, without substituting controller fallback `0x70` or expanding into startup recovery. Independent review is required before integration.
