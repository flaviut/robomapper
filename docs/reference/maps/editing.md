# Offline map edits: keep the frame; let the vendor own room operations

For firmware `4.3.5_1612`, the bounded offline candidate is a **small occupancy/confidence patch in an existing RRSLAM frame**, followed, if needed, by ordinary vendor room operations. Do not transplant structs from OpenSLAM, change coordinate frames, or paint room IDs into the occupancy raster. A correct digest establishes file integrity, not navigation safety. A false-free patch over a real obstacle is dangerous even when every byte-level constraint holds.

Map editing and restoration remain unperformed. The [maintenance procedure](../../guides/stopped-backup.md) demonstrates service stop, untouched backup and normal reboot; it does not establish safe import of an edited map. Keep original firmware and backup data unchanged while preparing a candidate.

## First bounded edit

Start from one known-good matching snapshot. Keep an untouched copy of all slots and companions. Use the *actual boot-consumed slot*, not an assumption that `user_map0` alone is authoritative: the native last-map path requests flag 1 (`last_map`), while primary flag 2 is `user_map0` and backup flag 6 is `user_map4`. Do not edit the genuine backup slot merely to make every file identical.

The [offline codec](../../../tools/map-maint/map_codec.py) implements this narrow encoding recipe; the [storage reference](storage.md#rrslam-version-2-raster) describes the fields:

* Preserve the exact first **30 bytes**, including magic `RRSLAM`, little-endian version 2, view-header size 20, scale 20, signed left/top and unsigned width/height (`<6sHHIiiII`). The value 20 is not the complete file-prefix length.
* Keep exactly `width * height` raw one-byte cells in their original order. Change only the intended patch; preserve intermediate confidence values elsewhere. Do not globally threshold, rotate, resample, palette-convert or flip the exported PGM.
* Replace only the final **16 raw bytes** with `MD5(cells)`, not an ASCII hex digest and not a hash of header+cells. Total length remains `30 + width*height + 16`.
* Keep `PersistData_<flag>.data`, catalog `SharedMultiMapInfo`, `slam_info.cfg`, vmaps, map-related pose/config companions and `robot.db` with present SQLite companions unchanged for this occupancy-only candidate. Preserve unknown regions, names, restrictions and all other map slots. Whether current boot needs a deliberately patched runtime copy as well is a slot-selection observation, not permission to replace every slot.

## What each edit changes

| Effect | Offline change / preservation rule | Native regeneration boundary |
| --- | --- | --- |
| Small free/occupied/confidence patch, fixed frame | Only selected RRSLAM cells and trailing MD5; exact prefix and all persistence companions preserved. | No automatic regeneration on edited-file load is established. Prefer patches away from doors and room boundaries. Even a local patch may change traversability; do not start cleaning merely because the file loads. |
| Origin, dimensions, resolution, crop, pad, translation, rotation | **Outside this recipe.** A new RRSLAM header/digest is insufficient; segmentation, poses, walls, zones, objects, obstacle points and unresolved regions may carry coordinates. | No complete native arbitrary-frame rebase/import interface is established. Retain original frame rather than attempting partial transformation. |
| Room split/merge | Do not edit occupancy bytes to encode a room or manually renumber region-5 cells. Keep the occupancy frame and issue a vendor room operation after normal startup. | Native split/merge owns label manipulation and publication through the [room-command path](room-operations.md). This is not a full automatic-resegmentation promise. |
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
| Room segmentation and both name arrays | [Region 5 layouts](regions.md#region-5); preserve outer presence, flags and tail too |
| Other spatial state | All region 9 (`0x2460` bytes), region 10 (`0x15f98`), opaque regions 6/13/14, and all unknown bytes of region 5 |
| Slot associations | Complete `SharedMultiMapInfo` / region 8 (`0x9c` bytes), including current flag and primary/backup pairing |

There is no reason to recompress or repair persistence for the occupancy-only candidate. Native room operations instead update shared regions and use the native serializer; let it own protobuf part sizes, compression and file replacement. The RRSLAM cell MD5 does not cover any of these companions or even the RRSLAM header.

## Room-state boundary

Segmentation and room names live in persistence, separately from occupancy. The [region layouts](regions.md) own those offsets; the [room-operation reference](room-operations.md) follows naming, ID promotion, split/merge and manual regeneration. No arbitrary-raster-to-room reconciliation workflow is established.

Use the [local raster-edit guide](../../guides/raster-edit.md) to prepare a candidate. Deployment still requires the [maintenance plan](../../plans/map-maintenance.md); a valid header and digest are not evidence of navigation safety.
