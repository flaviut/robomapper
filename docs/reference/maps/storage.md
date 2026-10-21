# Native map storage

An S7 map is a set of files, not just an occupancy raster. The raster stores occupancy/confidence cells; persistence stores room labels, restrictions, poses and other state. The catalog selects primary/backup associations, and SQLite holds application-facing messages and history. Preserve the [whole matching set](matching-set.md) when backing up or restoring.

This reference covers firmware `4.3.5_1612`. For the demonstrated service stop and untouched backup, use the [maintenance procedure](../../guides/stopped-backup.md). Edited-map loading and restoration have not been demonstrated.

## Map flags and filenames

The grid suffix and persistence suffix use different numbering schemes:

| Native flag | Grid | Persistence | Role |
| --- | --- | --- | --- |
| 0 | Firmware mobility-test map | Not established here | Mobility test |
| 1 | `last_map` | `PersistData_1.data` | Runtime/last map |
| 2–5 | `user_map0`–`user_map3` | `PersistData_2.data`–`PersistData_5.data` | Allocated primary slots |
| 6–9 | `user_map4`–`user_map7` | `PersistData_6.data`–`PersistData_9.data` | Allocated backup slots |
| 10–11 | `user_map8`–`user_map9` | `PersistData_10.data`–`PersistData_11.data` | Supported filenames outside the traced allocator |
| 12 | `/dev/shm/tmp_map` | Different temporary convention | Temporary grid |

Persistence flag **−2** selects `/dev/shm/PersistData_Temp.data`; it is not grid flag 12. Ordinary files live under `/mnt/data/rockrobo`. Persistence paths can use `NAV_DYNAMIC_CONFIG_PATH`, whereas the grid constructor uses absolute filenames. Confirm the deployed paths before copying.

AppProxy converts external user-map IDs to native flags by adding two. Thus external ID 0 selects native flag 2; a catalog association with backup flag 6 corresponds to external backup ID 4. Filename support does not imply allocation or selection. The [catalog findings](../../../analysis/re/evidence/components/catalog.json) follow these conversions; [region 8](regions.md#catalog-region-8) describes the stored entries.

Normal loading can select runtime flag 1, while recovery can select primary 2 or copy an associated backup over runtime/primary files. These files can differ. Never infer equality from the old capture or invoke an extra restore RPC merely to make startup load a replacement. The [file contract](matching-set.md) follows the startup and backup-copy paths.

## RRSLAM version 2 raster

`last_map` and `user_map*` use this packed little-endian format:

| Offset | Size | Field |
| --- | --- | --- |
| `0x00` | 6 | ASCII `RRSLAM`, no terminator |
| `0x06` | 2 | Version: `uint16`, value 2 |
| `0x08` | 2 | View-header length: `uint16`, value 20 |
| `0x0a` | 4 | Scale: `uint32`, value 20 |
| `0x0e` | 4 | Left: `int32` |
| `0x12` | 4 | Top: `int32` |
| `0x16` | 4 | Width: `uint32` |
| `0x1a` | 4 | Height: `uint32` |
| `0x1e` | `width × height` | Row-major cell bytes |
| `0x1e + width × height` | 16 | Raw `MD5(cells)` |

The complete prefix is **30 bytes**; 20 describes the view header starting at `0x0a`. In Python, use `struct.Struct("<6sHHIiiII")`, not native alignment. Local cell `(x,y)` is at byte `30 + y*width + x`.

The digest excludes the prefix. A valid digest alone does not establish valid dimensions, origin or navigation geometry. The [grid findings](../../../analysis/re/evidence/components/grid.json) follow writer `0x1ab84` and version-2 reader `0x1d21c` in `librrslamdrv.so`.

The cell interpretation is consistent with 0 = free, 128 = unknown and 255 = occupied. Intermediate values carry confidence information; their exact probability mapping is unresolved. Preserve them outside a deliberate patch. Application previews can invert occupancy and encode room IDs, so their bytes are not interchangeable with this raster.

The [offline codec](../../../tools/map-maint/map_codec.py) checks this header, dimensions and digest, exports raw cells as binary PGM, and repacks a same-sized PGM with the original prefix. See the [codec commands](../../guides/raster-edit.md#offline-codec) before using it. Its result is one raster, not a complete saved map or proof of safe navigation.

## Persistence, catalog and application messages

`PersistData_*.data` and `SharedMultiMapInfo` use the same [protobuf envelope](persistence.md#protobuf-envelope). Each region value contains a separate firmware-specific binary layout after decompression. Region 5 holds poses, restrictions, segmentation and room mappings; regions 9 and 10 hold object and obstacle data. Other regions remain partly or wholly opaque. The [region reference](regions.md) records the known offsets and unknown fields.

Encoding flags do not by themselves describe the actual transforms. The traced map serializers record `encrypt` without encrypting those bytes, and branch on `compress`. The [persistence reference](persistence.md) explains independent compressed parts, asynchronous saves, cancellation and buffered loads. A successful save reply is not a durable commit across the file set.

`robot.db` includes `cleanrecords`, `cleanmaps`, `snapshot` and `bakmaps`. Its application-map blobs are gzip-compressed `rr` messages, not `RRSLAM` files. Their IMAGE blocks combine occupancy information with room labels, but do not replace native persistence. Preserve the whole stopped database and its actual same-epoch sidecars; editing a preview blob is not an established native-map import interface.

AppProxy's map commands select native flags and invoke controller/navigation work; the persistence filename overloads do not supply arbitrary-path import/export. For room edits, use the [traced native routes](room-operations.md) rather than assuming a database edit or segmentation request repairs an arbitrary raster change.

## Address conventions

Addresses in the linked findings are virtual instruction addresses, with the Thumb bit cleared. In the cited shared-library executable ranges, virtual address equals file offset. For AppProxy and WatchDoge executable code, subtract `0x10000`; do not apply that conversion blindly to writable segments.
