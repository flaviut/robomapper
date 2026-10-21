# Offline map edits: keep the frame; let the vendor own room operations

For firmware `4.3.5_1612`, the bounded offline candidate is a **small occupancy/confidence patch in an existing RRSLAM frame**, followed, if needed, by ordinary vendor room operations. Do not transplant structs from OpenSLAM, change coordinate frames, or paint room IDs into the occupancy raster. A correct digest establishes file integrity, not navigation safety. A false-free patch over a real obstacle is dangerous even when every byte-level constraint holds.

This is static guidance, not observed device behavior. Service stop/restart and cold-start prerequisites are in [the offline workflow](OFFLINE-MAP-WORKFLOW.md). Those prerequisites must hold before replacing anything. Saved source data under `/home/user/tmp/illegalplainape/analysis` is read-only reference material here.

## First bounded edit

Start from one known-good matching snapshot. Keep an untouched copy of all slots and companions. Use the *actual boot-consumed slot*, not an assumption that `user_map0` alone is authoritative: the native last-map path requests flag 1 (`last_map`), while primary flag 2 is `user_map0` and backup flag 6 is `user_map4`. Do not edit the genuine backup slot merely to make every file identical.

Source-root `analysis/map_codec.py`, `HEADER`, `load_map`, `load_pgm` and `main`, establishes this narrow encoding recipe:

* Preserve the exact first **30 bytes**, including magic `RRSLAM`, little-endian version 2, view-header size 20, scale 20, signed left/top and unsigned width/height (`<6sHHIiiII`). The value 20 is not the complete file-prefix length.
* Keep exactly `width * height` raw one-byte cells in their original order. Change only the intended patch; preserve intermediate confidence values elsewhere. Do not globally threshold, rotate, resample, palette-convert or flip the exported PGM.
* Replace only the final **16 raw bytes** with `MD5(cells)`, not an ASCII hex digest and not a hash of header+cells. Total length remains `30 + width*height + 16`.
* Keep `PersistData_<flag>.data`, catalog `SharedMultiMapInfo`, `slam_info.cfg`, vmaps, map-related pose/config companions and `robot.db` with present SQLite companions unchanged for this occupancy-only candidate. Preserve unknown regions, names, restrictions and all other map slots. Whether current boot needs a deliberately patched runtime copy as well is a slot-selection observation, not permission to replace every slot.

The existing codec can stage a same-sized candidate off-device; these commands do not deploy it:

```sh
python3 /home/user/tmp/illegalplainape/analysis/map_codec.py export SNAPSHOT.map /tmp/map-original.pgm
# Make a small, deliberate byte-preserving grayscale edit into /tmp/map-edited.pgm.
python3 /home/user/tmp/illegalplainape/analysis/map_codec.py pack SNAPSHOT.map /tmp/map-edited.pgm /tmp/map-candidate.map
```

Both output paths must be new. Keep the original PGM unchanged as well. The codec checks its input dimensions and digest; it does not establish obstacle truth, robot clearance, room connectivity or correspondence with the captured persistence. No new editor or checker is introduced here.

## What each edit changes

| Effect | Offline change / preservation rule | Native regeneration boundary |
| --- | --- | --- |
| Small free/occupied/confidence patch, fixed frame | Only selected RRSLAM cells and trailing MD5; exact prefix and all persistence companions preserved. | No automatic regeneration on edited-file load is established. Prefer patches away from doors and room boundaries. Even a local patch may change traversability; do not start cleaning merely because the file loads. |
| Origin, dimensions, resolution, crop, pad, translation, rotation | **Outside this recipe.** A new RRSLAM header/digest is insufficient; segmentation, poses, walls, zones, objects, obstacle points and unresolved regions may carry coordinates. | No complete native arbitrary-frame rebase/import interface is established. Retain original frame rather than attempting partial transformation. |
| Room split/merge | Do not edit occupancy bytes to encode a room or manually renumber region-5 cells. Keep the occupancy frame and issue a vendor room operation after normal startup. | Native split/merge should own label generation and publication; the exact command path is being traced below. This is not a full automatic-resegmentation promise. |
| Room rename / ID-to-name association | Use the vendor name operation with current room IDs and the full intended name set; do not hand-edit 28-byte persistence records. | AppProxy's successful-result writer reassigns IDs positionally, not by geometry. Caller ordering must match response ordering. |
| Restrictions / poses | Preserve byte-for-byte for fixed-frame edits. If the intended patch conflicts with a zone, wall, dock or robot pose, stop rather than erase it as a side effect. | No general offline transform is supplied. Use ordinary vendor restriction controls where available; pose edits are not covered. |

## Why segmentation is a separate state

The decompressed region-5 segmentation begins at `S=0x31da0`. Its full span is `[0x31da0,0x131f44)` (`0x1001a4` bytes): presence at `S`, grid-valid at `S+4`, dimensions at `S+8/+0xc`, then 1,048,576 label bytes at `S+0x10`, and 404 trailing metadata bytes. Cells use low-six-bit IDs and may also carry bit `0x40`; preserve upper bits rather than treating the whole byte as an ID.

`librobopersist.so` full setter entry `0x157fc` copies the full span; grid setter `0x15898` copies only `[0x31da4,0x131db0)`, retaining the leading four bytes and tail. Neither updates room mapping arrays or restrictions. Default mapping count/data are `0x131fac/0x131fb0`; alternate count/data `0x13e9f0/0x13e9f4`. Records are 24 name bytes plus a 32-bit ID; setter `0x15c84` caps count at 32. Do not infer safe malformed-input/name handling from these capacity limits.

Navigation `0x132c30` calls `rs::segment_gridmap` at `0x132f44`, conditionally reuses old low-six-bit IDs 16..31 through `0x13223c`, and can allocate candidate IDs 1..15. Its later walks (`0x12e95c`, `0x12e12c`, `0x12cb14`) propagate labels according to geometry and unresolved occupancy predicates. Full publication at `0x13311a` follows zero allocation and copies grid data at `+4`, so this native path zeroes the 404-byte tail; that is **not** an instruction to zero it offline.

AppProxy `0x3c194` removes specified IDs from the persisted mapping, retaining other names/IDs; `0x3c2a0` preserves an ordered name vector while replacing each ID with the corresponding returned byte. Result handler `0x670dc` requires a matching pending transaction, nonzero status and a 32-byte response before using pending records at object `+0x3dcc`. An arbitrary raster load is not this transaction.

Sources: [metadata handoff](evidence/restore/metadata/handoff.json), its `exports/librrnavdrv.so/0x00132c30.c`, [room reconciliation](evidence/restore/room-reconcile/FINDINGS.md) and `exports/AppProxy/0x000670dc.c`; source-root `analysis/REGIONS.md` and `PERSISTENCE.md`. The metadata handoff's entry addresses supersede older prose that cited interior instruction anchors as entries.

## Direct edges still being resolved

The first checkpoint establishes the byte-preserving recipe and excludes arbitrary frame surgery. The remaining focused work is the native response-ID producer, population/order of AppProxy `+0x3dcc`, the caller that actually invokes full segmentation, persistence after room operations, and local Valetudo generation compatibility. Until those edges are resolved, do not present split/merge/rename as a general raster-to-metadata repair command.
