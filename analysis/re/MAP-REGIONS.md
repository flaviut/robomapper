# Shared-memory region layouts

After decoding the [persistence envelope](MAP-PERSISTENCE.md#protobuf-envelope) and decompressing its values, each shared-memory region is a firmware-specific binary buffer. Region IDs are independent of [map flags and filenames](MAP-STORAGE.md#map-flags-and-filenames).

These layouts apply to firmware `4.3.5_1612`. Offsets are relative to the decompressed region. Preserve unknown fields; this reference is not a recipe for transforming map geometry. The [edit contract](MAP-EDIT-CONTRACT.md) explains which changes require coordinated updates.

| Region | Bytes | Contents |
| --- | ---: | --- |
| 5 | 1,306,912 | Poses, restrictions, segmentation, room mappings and other map state |
| 9 | 9,312 | Objects, ignored objects and parallel detail records |
| 14 | 1,184,780 | Allocation identified; layout unresolved |
| 13 | 131,080 | Layout unresolved |
| 6 | 262,168 | Allocation and some backing pointers identified; layout unresolved |
| 10 | 90,008 | Packed obstacle points |
| 8 | 156 | Map catalog; stored separately in `SharedMultiMapInfo` |

## Region 5

Region 5 has size `0x13f120`. `InitSharedMapInfo` clears it and sets its first byte to 4. Its meaning is unknown; room counts are stored elsewhere.

| Offset | Field | Layout / capacity |
| --- | --- | --- |
| `0x000001` | Robot pose valid | Byte |
| `0x000004` | Robot pose | `int16 x`, `int16 y`, `float angle` |
| `0x00000c` | Dock pose valid | Byte |
| `0x000010` | Dock pose | Same 8-byte layout |
| `0x0318e8` | Forbidden-zone count | `uint32`, at most 50 |
| `0x0318ec` | Forbidden zones | Four `(int16 x, int16 y)` vertices per zone; 16 bytes each |
| `0x031c0c` | Virtual-wall count | `uint32`, at most 50 |
| `0x031c10` | Virtual walls | `(int16 x1, y1, x2, y2)`; 8 bytes each |
| `0x031da0` | Segmentation | `0x1001a4` bytes; layout below |
| `0x131f44` | Clean-segment count | Associated records not decoded |
| `0x131fac` | Default room-mapping count | `uint32`, at most 32 |
| `0x131fb0` | Default room mappings | 28-byte records: 24-byte name field, then `uint32 room_id` |
| `0x132330` | Mop-forbidden-zone count | `uint32`, at most 50 |
| `0x132334` | Mop-forbidden zones | Same 16-byte quadrilateral layout |
| `0x13e9f0` | Alternate room-mapping count | `uint32`, at most 32 |
| `0x13e9f4` | Alternate room mappings | Same 28-byte records |
| `0x13edf8` | Dock type | 32-bit value |

The mapping accessor chooses the alternate array for `IotTypeEnum == 1` and the default array otherwise. The public meaning of that enum value is unresolved. Read the selected mapping array rather than assuming that both arrays contain the same names or IDs.

Restriction capacities follow the setters' count checks, not just the space between offsets. Object records in region 9 are separate from these restrictions.

### Segmentation

Let `S` be region 5 offset `0x31da0`:

| Offset from `S` | Field |
| --- | --- |
| `0x000000` | Presence byte; next three bytes unresolved |
| `0x000004` | Grid-valid byte; next three bytes unresolved |
| `0x000008` | `int32 width` |
| `0x00000c` | `int32 height` |
| `0x000010` | 1,048,576 cell bytes |
| `0x100010` | 404 bytes of unresolved metadata |

The fixed cell capacity is 1024 × 1024; read the stored dimensions before interpreting cells. `SetSharedSegmentMap` copies the entire `0x1001a4` structure. `SetSharedSegmentMapGridData` copies `0x10000c` bytes to `S+4`, leaving the outer presence byte and trailing metadata unchanged.

Room IDs occupy the low six bits of each cell. Bit `0x40` occurs in captured cells but its meaning remains unresolved. Treating the entire byte as a room ID would misread those cells.

Native navigation centers the segmentation grid using rounded `-width/2` and `-height/2` offsets. The application-map IMAGE block describes a cropped window. For the historical paired maps with a 1024 × 1024 segmentation grid:

```text
application_left = RRSLAM_left + 512
application_top  = RRSLAM_top  + 512

application_pixel >> 3 = segmentation_cell & 0x3f
```

This relationship concerns room labels, not native occupancy values. The application pixel's low three bits have not been fully related to the segmentation flags; do not copy preview bytes into a native raster.

### Poses and coordinate conversion

Shared poses use two signed 16-bit coordinates and a floating-point angle. Historical paired robot and dock positions use this application-message conversion:

```text
application_x = shared_x + 25600
application_y = shared_y + 25600
```

The angle values are consistent with radians in shared memory and degrees in application messages. The firmware's angle rounding and normalization have not been traced.

The positions are consistent with centered millimetres, a 51,200 mm application extent and 50 mm segmentation cells. Valetudo converts application positions to display centimetres as follows:

```text
display_x = round(application_x / 10)
display_y = round((51200 - application_y) / 10)
```

The [edit contract](MAP-EDIT-CONTRACT.md) follows the display-to-native conversion used by the room-edit handlers. These conversions do not establish a general rotation or frame-transformation procedure. Native cells and shared poses do not use the display's inverted y axis.

### Segmentation updates

The firmware calls `rs::segment_gridmap` to calculate room segmentation, then builds a new segmentation structure and passes it to `SetSharedSegmentMap`. Other code updates just the grid portion.

The [native room route](evidence/restore/room-reconcile/FINDINGS.md) can propagate labels and return replacement IDs, while AppProxy applies pending names in response order. That is not automatic reconciliation after loading an edited `RRSLAM` file. Room names are supplied separately through `SetRoomIdMapping`; recalculating boundaries alone does not restore names or restrictions.

**Code references:** `librobopersist.so` pose setters at `0x14754`/`0x1499e`; restriction setters at `0x15264`, `0x15562`, `0x15fee`; segmentation setter entries at `0x157fc`/`0x15898`; room-mapping setter entry at `0x15c84`. In `librrnavdrv.so`, segmentation grid setup is at `0x12a39a`, room calculation at `0x132f44`, and the call storing its result at `0x1330ea`.

## Region 9

Region 9 has size `0x2460`:

| Offset | Field |
| --- | --- |
| `0x0000` | Initialization byte, set to 1; next three bytes unresolved |
| `0x0004` | `uint32 object_count` |
| `0x0008` | Up to 500 objects, 6 bytes each |
| `0x0bc0` | `uint32 ignored_object_count` |
| `0x0bc4` | Up to 50 ignored objects, 6 bytes each |
| `0x0cf0` | Up to 500 detail records, 12 bytes each |

The object and detail arrays share `object_count`. Their members remain unresolved. The available region is empty apart from its initialization byte, so it provides no examples from which to validate object coordinates or types.

`SetMapObjects` copies the object and detail arrays separately, then stores the count. These records are not the forbidden-zone quadrilaterals in region 5.

**Code references:** `librobopersist.so:InitSharedMapElement` at `0x13dac`; object setter at `0x13e64`; object/detail getters at `0x14080`/`0x14108`; ignored-object setter at `0x1423a`.

## Region 10

Region 10 has size `0x15f98`: four unresolved bytes, a 32-bit count at offset 4, then up to 30,000 three-byte points starting at offset 8.

Each point packs two signed 12-bit coordinates:

```text
byte[0] = (x >> 4) & 255
byte[1] = ((x << 4) | (y & 15)) & 255
byte[2] = (y >> 4) & 255
```

Decode by assembling each 12-bit value and sign-extending it. The representable range is −2048 through 2047 on each axis. The setter checks capacity but does not check coordinate range; out-of-range inputs are truncated, not saturated.

The coordinate units are unknown. The accessor packs its input without conversion; the caller still needs to be checked. Although the functions call these points temporary, they are saved in the persistence file.

**Code references:** `librobopersist.so` initialization at `0x16a06`, insertion at `0x16a1c`, decoding at `0x16a9c`.

## Catalog: region 8

`SharedMultiMapInfo` contains region 8 under protobuf `persistInfo.id = 1`. Its decompressed size is `0x9c`:

| Offset | Field |
| --- | --- |
| `0x00` | Initialization byte, set to 1 |
| `0x01` | Four catalog entries, stride `0x24` |
| `0x91` | Three unresolved bytes |
| `0x94` | `int32 current_flag`, initialized to −1 |
| `0x98` | Use-new-map byte, initialized to zero |
| `0x99` | Three unresolved bytes |

Within each catalog entry:

| Entry offset | Field |
| --- | --- |
| `0x00` | Primary map flag; zero marks an unused entry |
| `0x01` | Backup map flag |
| `0x02` | Two unresolved bytes |
| `0x04` | Name storage; full capacity/termination rules unresolved |

Read the actual entries and `current_flag` rather than inferring selection from filenames. `InsertMultiMap` inserts into the first empty primary entry, updates the current flag, and serializes the catalog. `UpdateBakMapForMultiMap` replaces the matching entry's backup flag and serializes when it changes.

The allocator searches flags 2–5 for primaries and 6–9 for backups. Although filenames exist for flags 10 and 11, the traced allocator does not return them.

**Code references:** `librobopersist.so` initialization at `0xe0c4`; primary-list iteration at `0xe580`; backup lookup at `0xe614`; backup update at `0xe9fc`; insertion at `0xeb82`. See [map flags](MAP-STORAGE.md#map-flags-and-filenames) for filename conversion and the [file contract](MAP-FILE-CONTRACT.md) for startup and recovery selection.

## Undecoded state

Region 6 is allocated as `0x40018` bytes, with navigation retaining pointers at base+4 and base+`0x14`. Region 14 is allocated as `0x12140c` bytes. These sizes match the decompressed payloads. Their contents and purpose, and the layout of region 13, still need to be decoded.

The segmentation tail, region-9 record members, restriction coordinate units, obstacle-point units, and firmware rotation transforms also need further work. Copying these bytes unchanged is sufficient for format preservation; changing map geometry may require understanding how they are used.
