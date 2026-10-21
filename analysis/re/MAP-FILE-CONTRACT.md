# Offline map matching-set contract — S7 4.3.5_1612

Use a whole, untouched matching set from the **same robot and firmware**, after the map hosts have stopped. Do not restore only `user_map0`, and do not extract the entire saved configuration archive over `/mnt/data`. This document owns the disk set and cold-start selection; the service/heartbeat lane owns obtaining and retaining the stopped window. No firmware or device was executed, and no tests, validators or replay suites were run.

## Captured map identity and database

The source-root `map-and-config.tar` contains precisely three native grid/persistence pairs:

| Native flag | Grid | Persistence | Meaning in captured catalog |
| --- | --- | --- | --- |
| 1 | `last_map` | `PersistData_1.data` | Last/runtime map |
| 2 | `user_map0` | `PersistData_2.data` | Current primary |
| 6 | `user_map4` | `PersistData_6.data` | Backup associated with primary 2 |

All names in this table are relative to `/mnt/data/rockrobo`. `SharedMultiMapInfo` stores region 8: its first entry associates primary 2 with backup 6, current flag is 2, and the other entries are empty. Native flags and user-map suffixes are **not the same numbering**: flags 2–11 use `user_map<flag-2>`, but persistence uses the flag itself. AppProxy's external IDs are native flag minus two: captured `bakmaps` rows 0 and 4 correspond to primary 2 and backup 6. Sources: source-root `analysis/REGIONS.md` catalog decoding; `librrslamdrv.so:0x26b60/0x26a70`; `librobopersist.so:0x1ab94`; AppProxy `0x3a430` and `0x23210`.

The six entries in `map-files-before.md5` and `map-files-after.md5` agree. In those observations, flags 1 and 2 have equal grids and equal persistence files; flag 6 differs. That is useful snapshot evidence, not proof that the database/config/catalog were acquired in one transaction or that every historical save completed.

Read-only inspection of the archived `robot.db` establishes:

* Size 338,944 bytes; SQLite page size 1,024; header read/write format bytes **1/1**, not WAL format 2/2.
* Archive has **no** `robot.db-journal`, `robot.db-wal` or `robot.db-shm`. This is observed archive absence, not a promise about another acquisition.
* Tables: `cleanrecords` (20 rows), `cleanmaps` (20), `snapshot` (0), and `bakmaps` (2). `bakmaps(id integer primary key, map blob)` has IDs 0 and 4, blob lengths 6,961 and 8,670.
* Application blobs are gzip `rr` messages, not native `RRSLAM` files. Preserve the whole database, including shared non-map/history contents; it is not a replacement for grids and persistence.

Header 1/1 plus absent companions identifies this captured database as rollback-format, with no captured transaction sidecar. It does **not** distinguish DELETE/TRUNCATE/PERSIST/MEMORY/OFF as the runtime journal policy. AppProxy database initializer `0x20440` opens read/write/create (flags 6); its audited initializer SQL does not set `journal_mode`. Neither the compiled SQLite parser keyword nor an unrelated vacuum pragma establishes a live reconfiguration. Do not issue a pragma to “normalize” a database while taking this backup.

The saved `etc/init/RRENV` sets `RR_UDATA=/mnt/data` and `NAV_DYNAMIC_CONFIG_PATH=/mnt/data/rockrobo`. Grids are hardcoded under `/mnt/data/rockrobo`; persistence uses the cached dynamic path (fallback `/mnt/data/rockrobo`); catalog appends `/rockrobo/SharedMultiMapInfo` to user-data root. AppProxy `0x20440` appends `/rockrobo/robot.db` to its initialized user-data base. The earlier unresolved base is now closed: Thumb instructions at `AppProxy:0x1b6a6–0x1b6c4` call `getenv("RR_UDATA")` and copy the result into BSS `0x35367c` with a 256-byte bound. The null-environment branch `0x1b9d4–0x1b9f6` copies literal `/mnt/data` there instead. Thus the saved configuration and fallback both produce **`/mnt/data/rockrobo/robot.db`**, not `/rockrobo/robot.db` at filesystem root. A current device can still override `RR_UDATA`.

## Preserve complete native state, not decoded regions

The complete `PersistData_*.data` bytes preserve room labels/names, restrictions, poses, objects and opaque regions without rebuilding them. Region 5 contains robot/dock poses, forbidden zones, virtual walls, mop exclusions, segmentation and room mappings; regions 6/13/14 remain partly or wholly opaque. `SharedMultiMapInfo` is separate catalog persistence, not another per-map file. `slam_info.cfg` is one shared configuration file, including `Map1`, `Map2`, `Map6`, temporary `Map-2` settings and new-map/moved/using state; preserve it unchanged.

The captured archive also contains `appproxy.map`, `StartPos.data`, `ChargerPos.data`, `ChargerType.data`, `Rotater.cfg`, `robot.setting` and `RoboController.cfg`. Keep these byte-preserving companions provisionally with the map set, rather than attempting to reproduce their values. It contains an empty `map/` directory and **no** vmap files. Preserve present vmaps in future stopped snapshots; never fabricate them merely because firmware constructs the names.

`slam_info.cfg.cache` is an in-progress write/rename product, not the normal configuration load input (`librrnavdrv.so:0x1a6374`, `0x141600`). Persistence writers use final-name + `.tmp<owner_pid>` (`librobopersist.so:0x1dc4c–0x1de00`); an earlier summary's `.tmp<task-index>` spelling is superseded by `analysis/PERSISTENCE.md`. Keep such interrupted work separately, not as authoritative restore inputs. Runtime `/BufferedMapInfo`, POSIX semaphores and `/dev/shm` grids/persistence must not be archived back into a new process lifetime.

## Cold-start facts established so far

`OnStateLoadLastMap` begins at **`librrnavdrv.so:0x20babc`**, not `0x20bac0` (that is its `push`, after a literal load and `movs r2,#0`). Instructions `0x20baca–0x20bad6` pass native flag 1 and load mode 0 to `LoadSLAMMap:0x68428`. It therefore loads `last_map` and `PersistData_1.data`; selecting catalog primary 2 does not mean this state reads `user_map0`. On load failure it clears relocation flags and sets state+0x323 (`0x20bade–0x20baec`) before continuing its state transitions, not directly loading backup 6 in that failure block.

`LoadSLAMMap` first reads the grid, then reconciles the map flag/configuration, then loads persistence (`0x68544`, `0x687aa–0x687fa`, `0x685ba`). In-process relocation-config manager byte+0x22 starts zero and flag+0x28 starts −1 (`0x1a6374`); on the first flag-1 reconciliation it adopts the catalog flag into that manager. Only subsequent loads with the initialized predicate set push the manager flag back into the catalog. This removes the earlier ambiguity about that predicate: it is process-local initialization, not a different saved catalog selection.

A separate startup state `0x83940` can load catalog current flag ≥2 when lab/use-new-map gates permit. Its failure selects reset state; it does not roll back partially changed grid/catalog/config. Preserve **both runtime and catalog-selected slots** rather than depending on only one startup branch. Catalog deserializer `0xe164` initializes region 8, then loads the catalog; an inaccessible catalog path can synthesize only primary/current 2 from accessible `user_map0`, not scan/recover all slots. An existing unloadable file follows the load-failure branch, not this inaccessible-path fallback.
