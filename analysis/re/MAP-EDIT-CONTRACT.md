# Offline map edits: keep the frame; let the vendor own room operations

For firmware `4.3.5_1612`, the bounded offline candidate is a **small occupancy/confidence patch in an existing RRSLAM frame**, followed, if needed, by ordinary vendor room operations. Do not transplant structs from OpenSLAM, change coordinate frames, or paint room IDs into the occupancy raster. A correct digest establishes file integrity, not navigation safety. A false-free patch over a real obstacle is dangerous even when every byte-level constraint holds.

Map editing and restoration remain unperformed. The [maintenance procedure](MAINTENANCE-PROCEDURE.md) demonstrates service stop, untouched backup and normal reboot; it does not establish safe import of an edited map. Keep original firmware and backup data unchanged while preparing a candidate.

## First bounded edit

Start from one known-good matching snapshot. Keep an untouched copy of all slots and companions. Use the *actual boot-consumed slot*, not an assumption that `user_map0` alone is authoritative: the native last-map path requests flag 1 (`last_map`), while primary flag 2 is `user_map0` and backup flag 6 is `user_map4`. Do not edit the genuine backup slot merely to make every file identical.

The [offline codec](../../tools/map-maint/map_codec.py) implements this narrow encoding recipe; the [storage reference](MAP-STORAGE.md#rrslam-version-2-raster) describes the fields:

* Preserve the exact first **30 bytes**, including magic `RRSLAM`, little-endian version 2, view-header size 20, scale 20, signed left/top and unsigned width/height (`<6sHHIiiII`). The value 20 is not the complete file-prefix length.
* Keep exactly `width * height` raw one-byte cells in their original order. Change only the intended patch; preserve intermediate confidence values elsewhere. Do not globally threshold, rotate, resample, palette-convert or flip the exported PGM.
* Replace only the final **16 raw bytes** with `MD5(cells)`, not an ASCII hex digest and not a hash of header+cells. Total length remains `30 + width*height + 16`.
* Keep `PersistData_<flag>.data`, catalog `SharedMultiMapInfo`, `slam_info.cfg`, vmaps, map-related pose/config companions and `robot.db` with present SQLite companions unchanged for this occupancy-only candidate. Preserve unknown regions, names, restrictions and all other map slots. Whether current boot needs a deliberately patched runtime copy as well is a slot-selection observation, not permission to replace every slot.

## Offline codec

The codec uses only Python's standard library. Run it locally from the repository root against a copied raster, not against the robot or the outer backup archive. `inspect` prints header fields and hashes; `export` writes raw cells as an 8-bit binary PGM; `pack` retains the original prefix and computes the new cell digest. These commands do not deploy anything:

```sh
work=$(mktemp -d /tmp/map-edit.XXXXXX)
python3 tools/map-maint/map_codec.py inspect SNAPSHOT.map
python3 tools/map-maint/map_codec.py export SNAPSHOT.map "$work/original.pgm"
# Save a deliberate same-size edit separately as "$work/edited.pgm".
python3 tools/map-maint/map_codec.py pack SNAPSHOT.map "$work/edited.pgm" "$work/candidate.map"
```

The private temporary directory keeps map contents out of shared output paths. Both output files must be new; the codec refuses to overwrite an existing destination. Keep the original raster and exported PGM unchanged. It rejects unsupported headers, dimension/length mismatches and a bad input digest; `pack` also requires a same-sized binary PGM with maximum value 255.

Native cell `(x,y)` is byte `30 + y*width + x`; no display-y inversion belongs here. Cells are consistent with 0=free, 128=unknown and 255=occupied, but intermediate probabilities are not calibrated. Do not copy display-preview colors or room-label bytes into the raster. The codec does not establish obstacle truth, robot clearance, room connectivity or correspondence with persistence.

## What each edit changes

| Effect | Offline change / preservation rule | Native regeneration boundary |
| --- | --- | --- |
| Small free/occupied/confidence patch, fixed frame | Only selected RRSLAM cells and trailing MD5; exact prefix and all persistence companions preserved. | No automatic regeneration on edited-file load is established. Prefer patches away from doors and room boundaries. Even a local patch may change traversability; do not start cleaning merely because the file loads. |
| Origin, dimensions, resolution, crop, pad, translation, rotation | **Outside this recipe.** A new RRSLAM header/digest is insufficient; segmentation, poses, walls, zones, objects, obstacle points and unresolved regions may carry coordinates. | No complete native arbitrary-frame rebase/import interface is established. Retain original frame rather than attempting partial transformation. |
| Room split/merge | Do not edit occupancy bytes to encode a room or manually renumber region-5 cells. Keep the occupancy frame and issue a vendor room operation after normal startup. | Native split/merge owns label manipulation and publication through the command path below. This is not a full automatic-resegmentation promise. |
| Room rename / ID-to-name association | Use the vendor name operation with current room IDs and the full intended name set; do not hand-edit 28-byte persistence records. | AppProxy's successful-result writer reassigns IDs positionally, not by geometry. Caller ordering must match response ordering. |
| Restrictions / poses | Preserve byte-for-byte for fixed-frame edits. If the intended patch conflicts with a zone, wall, dock or robot pose, stop rather than erase it as a side effect. | No general offline transform is supplied. Use ordinary vendor restriction controls where available; pose edits are not covered. |

## Preserve these companion ranges for occupancy-only edits

The following are **decompressed region-relative offsets**, not file offsets into the protobuf/zlib `PersistData` envelope. Copying the entire original persistence file is the recipe; these ranges explain why editing its convenient-looking room bytes is not included.

| State to preserve | Region / byte locations |
| --- | --- |
| Robot and dock poses | Region 5 validity bytes `0x1`, `0xc`; records `[0x4,0xc)`, `[0x10,0x18)` |
| Forbidden zones | Region 5 count `0x318e8`; vertices begin `0x318ec`, 16 bytes per quadrilateral, setter limit 50 |
| Virtual walls | Region 5 count `0x31c0c`; records begin `0x31c10`, 8 bytes each, limit 50 |
| Mop-forbidden zones | Region 5 count `0x132330`; vertices begin `0x132334`, 16 bytes each, limit 50 |
| Room segmentation and both name arrays | Region 5 ranges detailed below; preserve outer presence, flags and tail too |
| Other spatial state | All region 9 (`0x2460` bytes), region 10 (`0x15f98`), opaque regions 6/13/14, and all unknown bytes of region 5 |
| Slot associations | Complete `SharedMultiMapInfo` / region 8 (`0x9c` bytes), including current flag and primary/backup pairing |

There is no reason to recompress or repair persistence for the occupancy-only candidate. Native room operations instead update shared regions and use the native serializer; let it own protobuf part sizes, compression and file replacement. The RRSLAM cell MD5 does not cover any of these companions or even the RRSLAM header.

## Why segmentation is a separate state

The decompressed region-5 segmentation begins at `S=0x31da0`. Its full span is `[0x31da0,0x131f44)` (`0x1001a4` bytes): presence at `S`, grid-valid at `S+4`, dimensions at `S+8/+0xc`, then 1,048,576 label bytes at `S+0x10`, and 404 trailing metadata bytes. Cells use low-six-bit IDs and may also carry bit `0x40`; preserve upper bits rather than treating the whole byte as an ID.

`librobopersist.so` full setter entry `0x157fc` copies the full span; grid setter `0x15898` copies only `[0x31da4,0x131db0)`, retaining the leading four bytes and tail. Neither updates room mapping arrays or restrictions. Default mapping count/data are `0x131fac/0x131fb0`; alternate count/data `0x13e9f0/0x13e9f4`. Records are 24 name bytes plus a 32-bit ID; setter `0x15c84` caps count at 32. Do not infer safe malformed-input/name handling from these capacity limits.

Navigation `0x132c30` calls `rs::segment_gridmap` at `0x132f44`, conditionally reuses old low-six-bit IDs 16..31 through `0x13223c`, and can allocate candidate IDs 1..15. Its later walks (`0x12e95c`, `0x12e12c`, `0x12cb14`) propagate labels according to geometry and unresolved occupancy predicates. Full publication at `0x13311a` follows zero allocation and copies grid data at `+4`, so this native path zeroes the 404-byte tail; that is **not** an instruction to zero it offline.

AppProxy `0x3c194` removes specified IDs from the persisted mapping, retaining other names/IDs; `0x3c2a0` preserves an ordered name vector while replacing each ID with the corresponding returned byte. Result handler `0x670dc` requires a matching pending transaction, nonzero status and a 32-byte response before using pending records at object `+0x3dcc`. An arbitrary raster load is not this transaction.

Sources: [metadata handoff](evidence/restore/metadata/handoff.json), its `exports/librrnavdrv.so/0x00132c30.c`, [room reconciliation](evidence/restore/room-reconcile/FINDINGS.md) and `exports/AppProxy/0x000670dc.c`. The [region layouts](MAP-REGIONS.md) and [persistence reference](MAP-PERSISTENCE.md) describe the companion state and loading behavior.

## Names: request ordering and native ID promotion are now identified

AppProxy **`0x59994`** is the `name_segment` handler (registered by `0x625e8`). It resets the pending vector end at `+0x3dd0` to its start at `+0x3dcc`, then walks the JSON `params` array in input order. For each accepted record, it appends the 24-byte checked name plus original 32-bit ID to that vector **and appends that same ID as one byte to the request in the same iteration**. It accepts `miRoomId`, falling back to `iotRoomId`, together with numeric `robotRoomId`. The outgoing IPC is `0x02033209`, payload length 32: two transaction words, a 32-bit count, then ID bytes. Invalid entries can be skipped: use a complete, well-formed list, unique current IDs and short ASCII names, not arbitrary input lengths or encodings.

The native producer **`librrnavdrv.so:0x69e84`** initializes a 32-byte result with the same two transaction words, success byte at offset 8, count byte at offset 9, and result IDs at offset 10. It walks the input ID array **in request order**. IDs >=16 are echoed. IDs <16 call **`0x1295d4`**, which scans the current shared label map, chooses an unused stable ID through **`0x126e40`** (first unused 16..31; returns zero when exhausted), and replaces matching low-six-bit labels while retaining bit `0x40`. It marks grid-valid when replacement occurred. Missing temporary labels or ID exhaustion clear the result's success byte. This is the previously missing promotion path: **naming can change room IDs; it is not just a string update**.

`0x69e84` stores the completed result in the continuation associated with object `+0x4c0`; its callback pointer at VA `0x304c30` is Thumb `0x68199`. The callback at `0x68198..0x681ce` dispatches local `MODIFY_SEGMENT_MAP_RESULT` (`0x68`) through `0x67ad0`, preserving the result buffer. Event names are in the native enum string at `0x27600c`; `MODIFY_SEGMENT_MAP` is `0x67`. Combined with AppProxy `0x670dc`'s matched-success branch and `0x3c2a0`, this closes the **positional association**: accepted request names, requested IDs and returned IDs have the same order. It does not establish cross-process atomicity. A later failure may follow earlier per-ID label changes; do not blindly retry using stale IDs after failure.

The name-success branch calls AppProxy **`0x3c6bc`** after updating mappings. That sends save-set IPC **`0x02033212`**, with destinations runtime flag 1 and the current map flag, and the original transaction words. It is therefore not merely an in-memory rename. Native save still uses the [detached serializer](MAP-PERSISTENCE.md#map-dependent-saves); neither the name response nor the save request is a durable multi-file completion acknowledgment.

## Valetudo encoding and the S7 generation boundary

Local source `/home/user/dev/co/Valetudo`, commit `5d905ec2239dd14bbc11ee3785837562306a508e`, is a source comparison, **not evidence of the version installed on the device**. The [device observations](DEVICE-FACTS.md) identify this firmware as S7 / `roborock.vacuum.a15`. `RoborockS7ValetudoRobot.js` inherits `RoborockGen4ValetudoRobot.js`, whose constructor registers room edit and rename capabilities. The actual 1612 AppProxy dispatch registration contains these exact handlers:

| Operation | JSON method and `params` | 1612 handler / IPC |
| --- | --- | --- |
| Merge two rooms | `merge_segment`, `[idA,idB]` | `0x56030`; `0x02033207`, 24-byte payload |
| Split a room | `split_segment`, `[id,x1,y1,x2,y2]` | `0x563b4`; `0x02033208`, 32-byte payload |
| Name rooms | `name_segment`, `[{miRoomId:"Name",robotRoomId:id}, ...]` | `0x59994`; `0x02033209`, 32-byte payload |
| Read names | `get_room_mapping` | Existing Valetudo `fetchAndStoreSegmentNames()` supplies current IDs/names before rename. |

`RoborockMapSegmentEditCapability.js` encodes split endpoints from display centimetres as `floor(x*10)`, `floor(51200-y*10)`. Firmware `0x563b4` requires five parameters, room ID <32, and endpoint values 0..51200 inclusive, then subtracts 25600 from each endpoint coordinate for native IPC. Use display coordinates only through that conversion; do not pass RRSLAM cell indices as millimetres. The merge handler accepts room IDs <32 and up to nine input IDs; the two-ID Valetudo operation is the bounded candidate. Native routines still decide whether the requested geometry can be split or merged. This checkout's S7 autodetection explicitly accepts `roborock.vacuum.a14` and `roborock.vacuum.a15`; compatibility here is therefore grounded in the target model and firmware handlers, not borrowed from the older V1 implementation (which lacks these room capabilities).

`RoborockMapSegmentRenameCapability.js` sends the changed room first, then its cached other names; it reads `get_room_mapping` after the reply. It rejects empty names or JS string length >23, but the native 24-byte copy limit is a **byte** limit. Use 1..23 ASCII bytes for the candidate rather than relying on that JS character limit for multibyte names. Refresh names before renaming and after each split/merge; do not feed a stale full-name cache back into the vendor.

**Do not use the old empty-array segmentation quirk on this firmware.** `RoborockQuirkFactory.js` sends `manual_segment_map` with `[]`; S7 does not register that quirk (S5 does). Firmware 1612's registered handler **`0x6c6b8`** explicitly rejects an empty array and requires first element `{map_flag:N}`. A nonnegative external map ID is converted to native flag `N+2` and checked against existing multimaps. `-1` selects the new-map path, with rate/resource checks. It sends controller IPC **`0x01033111`**, length 4, containing the selected native flag; it can also request a save for an existing flag. Its controller route does schedule full native regeneration, as traced below, but also records map-save/control state; it is not a proven harmless offline-import repair API. **Do not use `map_flag:-1` as a repair trick:** it selects creation semantics. The local source's `RoborockMapSegmentationCapability` is room-targeted cleaning (`app_segment_clean`), not segmentation regeneration.

## Actual regeneration entry and what room operations avoid

The full algorithm is reached by worker **`0x696a8`**, calling `0x132c30` at **`0x696e8`** with the first two bytes of its task argument. Raw Thumb inspection of the dispatch region beginning **`0x6e1d8`** identifies event **`UPDATE_SEGMENT_MAP` (`0x61`)**: the `tbh` at `0x6e20a` selects `0x6eb60`; task slot `+0x4a8` must be absent or have status 3/4. The branch at `0x6f81e` constructs the worker with those bytes and the host object, storing Thumb pointer `0x696a9` at `0x6f852`. Thus this is a concrete scheduled regeneration entry, **not a file-reader side effect**. The original baseline has no function object spanning this dispatcher, so these dispatch claims are instruction-level, not newly recovered C.

### The manual command reaches that worker, not merely a similarly named method

The read-only RoboController export and raw Thumb instructions close the controller edge:

| Stage | Static evidence |
| --- | --- |
| AppProxy request | `0x6c6b8` sends `0x01033111` with a four-byte native map flag. |
| Controller packet parser | `0x24458`, comparison at `0x24882`, length check at `0x24910`, construction at `0x256cc`: low request ID `0x3111`, length 4, event **`0x840`**, selected flag at event `+0xc`. Event vtable `0x5115c`; name `RE_NS_App_ManualSegmentMap` at `0x4f1b4`. |
| Controller event handler | `0x367ac`, comparison at `0x36966`, branch to **`0x376d2`**: records manual-request state at context `+0x218` and selected flag at `+0x21c`. After request/timer bookkeeping, `0x37772..0x3778c` posts event **`0x9e`** (`RT_Nav_SegmentMap`) through `0x28678`, with event `+0xc/+0xd` bytes **`[1,0]`**. |
| Controller encoder | Initializer `0x16dfa..0x16e12` associates event `0x9e` with invoke Thumb **`0x22bd5`** (manager `0x22bbd`). Instructions **`0x22bd4..0x22c1a`** write wire **`0x02011203`**, payload length **2**, copying those two bytes. The neighboring invoke `0x27041` belongs to event `0x261`, not `0x9e`. |
| Native wire/event lookup | Original native table row at VA/file **`0x2a326c`** is `61 00 00 00 03 12 01 02`: little-endian event **`0x61`** and wire **`0x02011203`**. This is `UPDATE_SEGMENT_MAP`, whose task branch and algorithm entry are above. |

Controller **`0x31848`**, identified by the `RequestSegmentMap` string at `0x53620`, posts the same `0x9e` event with bytes `[0,param_2]`; the manual branch instead posts `[1,0]` directly. Do not conflate those request modes or the controller event number `0x9e` with the native event number `0x61`.

This establishes an actual vendor-command-to-regeneration path. It does **not** establish that a particular offline replacement is selected, loaded into the relevant native occupancy state, regenerated and durably saved in that order. In particular, the selected map flag is retained in controller state, **not carried in the two-byte regeneration payload**; a flag naming a stored slot is not itself evidence that segmentation consumed that slot's replacement raster. Native pending-task gating still applies. No command here was sent, and this static path is not authorization to add manual regeneration to the first candidate.

Native **merge `0x12a56c`** and **split `0x131824`** instead load existing shared segmentation through `0x12a35c` and publish with `SetSharedSegmentMapGridData`. Merge chooses a supplied stable ID if present, otherwise obtains one, then rewrites selected low-six-bit labels while preserving `0x40`. Split runs its line/geometry routines and publishes the resulting grid. Neither routine calls `rs::segment_gridmap`. They operate on existing room segmentation and are the simpler alternative to reimplementing the full segmentation algorithm, **but do not rebuild room ownership from arbitrary replacement occupancy**.

The hybrid decision is therefore concrete: **small fixed-frame occupancy patch + existing coherent labels + ordinary vendor split/merge/rename** is a bounded candidate. **Topology-changing raster replacement + presumed automatic resegmentation/reconciliation is not.** A new doorway, a filled passage, disconnected room islands, a new wing or a changed frame exceeds the first candidate even when dimensions and MD5 match. The manual command's scheduling edge is now identified; cold-load auto-regeneration and correct consumption of a newly replaced offline raster are not. A successful native regeneration can also reconcile/promote room IDs and discard old associations; it is not a promise to preserve room names or topology exactly. Keep this distinction between a reachable algorithm and a device-proven offline-import workflow.

## Bounded candidate after the service window

1. Stage only the selected fixed-frame occupancy patch with the existing codec; preserve the untouched matching set and genuine backup. Reject the candidate if its intended meaning requires a changed doorway, disconnected room, map extent, origin, dock/pose or restriction geometry.
2. Use the other lanes' established stopped-writer replacement and cold-start path. Keep automatic cleaning and other command producers gated; this document supplies no live IPC shell sender or supervision commands.
3. Once the intended map is loaded, obtain its **current** room IDs and name mapping through the ordinary client. Do not reuse IDs from a cached screenshot or pre-edit response. If existing room labels are absent/incoherent, stop the hybrid path; split/merge is not a substitute for full regeneration.
4. If room boundaries alone need adjustment, use one ordinary split or two-room merge at a time, with the encoding above. Let the native operation publish the label grid; then refresh the map and names before the next operation. Preserve the occupancy raster during these label operations; they are not obstacle editing commands.
5. Rename using a full refreshed list, unique current IDs and 1..23 ASCII bytes per name. Keep this first candidate to at most 16 rooms (the native stable-ID pool is 16..31), preferably the captured smaller room set. Retain the vendor `oldId`/`newId` association and refresh again: naming a temporary room can promote its ID. On failure, reacquire the current IDs instead of resending stale ones.
6. Allow ordinary native saves to settle before a later stopped snapshot. Preserve the resulting native matching set as a new state, separate from the original rollback set. A command reply or digest match alone is not evidence that the robot can safely navigate the edited geometry.

This path avoids implementing segmentation **only while the original occupancy frame and useful segmentation remain coherent**. Never delete a real obstacle to make a desired split succeed, or infer that a label merge opens a physical doorway.

## Where this checkpoint stops

The remaining device-dependent inputs are the actual boot slot/recovery selection, installed Valetudo/controller configuration and the service window prerequisites owned by other lanes. On the editing side, the manual vendor command reaches full regeneration, but no device-proven arbitrary occupancy-to-segmentation import workflow is established; do not wait for that to perform byte-preserving backup/restore, and do not need it for an occupancy-only candidate that leaves topology unchanged. If the desired correction requires new room geometry from raster connectivity, retain the original raster or remap with the vendor rather than inventing opaque-region transforms.

New focused observations used only original 1612 AppProxy (`24b52f58…c457`), librrnavdrv (`603a3b2f…1475`) and RoboController (`bf1d43313dd8beaa0c802f9ae4c666138b3bb518f69b4909a746285f3f3947cf`) bytes and private copies of the closed Ghidra baseline. The controller lane supplied read-only exports `/tmp/map-file-contract/RoboController-{24458,31848}.c` and `rc.asm`; this lane did not open or mutate its project. The controller route table above records the useful anchors independently of temporary-export lifetime. Temporary decompiler exports are under `/tmp/map-edit-app{1..6}` and `/tmp/map-edit-nav{1..8}`; no firmware, baseline, earlier evidence, source checkout or configuration was changed. LLVM raw disassembly used explicit `--triple=thumbv7-linux-gnueabi` for these Thumb ranges; default ARM decoding gives nonsense here. The relocated native `.data.rel.ro` block at VA `0x304428` maps to file offset `0x2f4428`: callback table VAs must not be read as file offsets. No tests, replay, firmware execution, robot access or new editing infrastructure were used.
