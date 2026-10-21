# Room reconciliation — bounded static checkpoint

Start: `6cd68d6`. Static local sources only. No device, original firmware execution, internet, imports, annotations, function creation or shared baseline changes. All C under `exports/` is **decompiler output, not recovered source**; inferred prototypes are not ABI corrections. Surviving names/signatures remain unchanged.

## Supported findings

### R01: Post-ID processing is still geometry/occupancy dependent

`librrnavdrv.so:0x132c30` calls the three existing entries in order at **0x133090**, **0x13309c**, **0x1330a6**, after the predecessor's conditional ID assignment. These are real baseline entries, not interior anchors. `exports/librrnavdrv.so/entries.json` preserves inventory metadata; complete selected instruction streams and executable original-ELF mappings are checked by `validate.py`. No guessed entry was needed.

* **0x12e95c** builds a walk over the active rectangle at object offsets `+0x100010..+0x10001c`, starts from the passed XY seed, calls **0x12e714** with neighborhood radius 1, and updates the passed bounds through two calls to **0x1285a4**. The walk compares an unresolved virtual coordinate predicate against `1` and `-1`, uses **0x148b94** to convert XY into a cell index, and distinguishes zero from nonzero grid bytes. At **0x12e8ee..0x12e8fe**, a nonzero source low-six-bit ID is copied into an eligible zero neighbor with bit `0x40` set. The destination eligibility depends on the predicate and source/neighbor positions; this is not byte-preserving copying of the old grid.
* **0x12e12c** constructs a local radius from `roundf(object[+0x1000bc] * float32(0.02))`, sets up the passed rectangle and calls **0x12dda4** with radius 1. That walk can choose a labeled source/current/nearby cell, with additional fallback **0x12d884** not expanded here, then writes `ID | 0x40` at **0x12e074..0x12e07a**. Do not label the unresolved predicate's return values as obstacle/free/unknown without following its concrete implementation.
* **0x12cb14** derives another radius from `roundf(object[+0x1000b8] * float32(0.02))`, expands the supplied rectangle by radius+2 and intersects it through **0x12883c**. It scans the rectangle's horizontal midpoint for a nonzero low-six-bit cell, then runs bounded four-neighbor traversals through **0x12c860** and **0x12ca58**. The latter uses visited/exclusion bitsets and fills an eligible zero-low-six-bit destination from its predecessor's ID with `0x40` at **0x12cafc..0x12cb0a**. The former reaches unexpanded virtual/shared-pointer callbacks. Radius constants are recorded as original ELF data, not inferred units.

Evidence groups: `ordered-postprocessing`, `seed-bounds-and-walk`, `coordinate-dependent-fill`, `bounds-update`, `radius-and-bounds`, `second-neighbor-fill`, `third-radius`, `third-stage-fill` in `evidence.json`.

**Consequence (inference):** unchanged dimensions do not freeze the neighborhood traversal, seed reachability, overlap with the prior labels or the final labeled area. Same-sized occupancy edits can change which cell supplies an ID and which zero cells inherit it. These selected writes propagate an existing low-six-bit value; they do **not** establish promotion of temporary IDs 1..15 to stable IDs 16..31. The predecessor's conditional reuse branch remains conditional. No universal final-ID-stability claim is supported.

### R02: Actual name/ID persistence writers are separate AppProxy operations

The navigation inventory and original ELF dynamic symbols expose `ClearRoomIdMapping`, but no imported `SetRoomIdMapping`. This is a direct-import observation, **not exclusion of indirect writers**. AppProxy imports the setter and its existing PLT entry **0x18990** has two recognized callers, both exported here:

* **0x3c194** gets the current mapping, traverses 28-byte records, and filters **out** records whose 32-bit ID at `record+24` appears in the supplied byte-ID list. Zero list length retains all records. Retained records have a zeroed 24-byte name field, `__strcpy_chk(..., 24)` from the old name, and the original ID. The result is written through `SetRoomIdMapping` at **0x3c264**. Its caller is **0x6adfc**, which subsequently reaches other unexpanded update helpers. This is conditional record/name retention, not geometric matching.
* **0x3c2a0** iterates the supplied 28-byte-record vector **in order**, zeroes and copies each 24-byte name with the same checked C-string operation, replaces `record+24` with successive unsigned bytes from a separate array (**0x3c328..0x3c330**), and calls the setter at **0x3c33e**. It does not look up an old ID or compare geometry while pairing a name with a new ID.
* Its recognized caller **0x670dc** first requires message payload length `0x20`. The name-result branch matches two response words with pending state at object `+0xb00/+0xb04` (**0x671f4..0x67204**), then requires nonzero status byte (**0x672b8..0x672be**). It copies the pending record vector at `+0x3dcc/+0x3dd0` and passes response IDs beginning at stack `+0x82` to **0x3c2a0** (**0x67332..0x6733e**). The subsequent report emits `oldId`/`newId` pairs. This establishes a local, successful-result-dependent writer, not a coherent transaction or durable save completion.

The mapping selector **0x3c148** compares a locally obtained string prefix with `miot`; instructions normalize the comparison into 0 for equal, 1 otherwise. The decompiler infers `void`, omitting this return value in C; no prototype was changed. The literal string appears in generated C and original executable uses its address; this is not a decoded user room name.

Evidence groups: `preserve-filter-names`, `replace-id-preserve-name`, `name-transaction-match`, `matching-name-result`, `result-old-new-report`, `filter-caller`, `iot-type-selection`.

**Consequence:** names can survive as strings while their associated IDs are explicitly replaced, or can be removed by a list-based filter. Preservation requires the ordered pending-name records and returned ID array to correspond. The selected caller does not itself prove that relationship to the output of navigation **0x132c30**. No automatic rename/reconciliation after an arbitrary edited RRSLAM load is established. A 24-byte checked string copy is not proof that arbitrary edited records are terminated, encoded correctly or safe; the fixed 32-record allocation also does not certify malformed lengths.

## Edit contract and limits

For same-sized edits, preserve the coordinate frame, all cell bits, unknown persistence bytes and coherent mapping/restriction state unless an independently validated transformation/regeneration contract exists. Fixed dimensions and a repaired grid MD5 validate neither overlap nor room identity/name association. Inference: even unchanged coordinates can acquire different semantic ownership after a split/merge or changed connectivity. The full/grid-only setter ranges are predecessor findings and are deliberately not re-established here.

No opaque region 6/13/14 decoder was pursued: no direct named region getter/setter edge was identified in the selected functions; indirect dependencies are unresolved, not absent. Unknown concrete coordinate predicates, seed recovery **0x130f1c**, fallback **0x12d884**, callback implementations reached through **0x12c860**, upstream response production/order and linkage to automatic regeneration remain next targets. No safety claim for malformed input, algorithm correctness, concurrent snapshotting, cache refresh, power loss or runtime restore.

## Reproduction

From repository root, with `PYTHONDONTWRITEBYTECODE=1`:

```
python3 analysis/re/evidence/restore/room-reconcile/validate.py
python3 -m unittest discover -s analysis/re/evidence/restore/room-reconcile -p test_validate.py -v
python3 analysis/re/evidence/restore/room-reconcile/replay.py --out analysis/re/evidence/restore/room-reconcile/scratch/replay-NEW
```

The replay uses source-root `retool.py` to COPY the closed baseline, then sequentially exports navigation and AppProxy. It never opens the baseline itself. Projects, full inventories and logs stay ignored under lane scratch. `entries.json` is a bounded inventory extract, not a full inventory. Complete selected records and C must match the fresh copy; two input SHA256s, 15 existing entries, 3,707 instruction records, focused anchors and two radius literals are verified against original ELF mappings/bytes. Five host-side checker tests include C/selection tampering and executable/cross-boundary rejection. No checker bug was encountered or fixed. Replay/byte equality establishes reproducibility only, never semantic or runtime safety.
