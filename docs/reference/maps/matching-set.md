# Map matching-set reference

Preserve one complete disk epoch from the same robot and firmware (`4.3.5_1612`), including recorded absence and present SQLite sidecars. A raster alone is not a saved map. The [backup guide](../../guides/stopped-backup.md) demonstrates untouched acquisition; [whole-set restoration](../../guides/matching-set-restore.md) remains untested.

## Captured map identity and database

The source-root `map-and-config.tar` contains precisely three native grid/persistence pairs:

| Native flag | Grid | Persistence | Meaning in captured catalog |
| --- | --- | --- | --- |
| 1 | `last_map` | `PersistData_1.data` | Last/runtime map |
| 2 | `user_map0` | `PersistData_2.data` | Current primary |
| 6 | `user_map4` | `PersistData_6.data` | Backup associated with primary 2 |

All names in this table are relative to `/mnt/data/rockrobo`. `SharedMultiMapInfo` stores region 8: its first entry associates primary 2 with backup 6, current flag is 2, and the other entries are empty. Native flags and user-map suffixes are **not the same numbering**: flags 2–11 use `user_map<flag-2>`, but persistence uses the flag itself. AppProxy's external IDs are native flag minus two: captured `bakmaps` rows 0 and 4 correspond to primary 2 and backup 6. Sources: [catalog layout](regions.md#catalog-region-8); `librrslamdrv.so:0x26b60/0x26a70`; `librobopersist.so:0x1ab94`; AppProxy `0x3a430` and `0x23210`.

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

`slam_info.cfg.cache` is an in-progress write/rename product, not the normal configuration load input (`librrnavdrv.so:0x1a6374`, `0x141600`). Persistence writers use final-name + `.tmp<task_index>` (`librobopersist.so:0x1dc76` loads task+0, passed to the formatter at `0x1dc84`). Owner PID is the distinct task+4 field. The [persistence reference](persistence.md#destination-file-writes) explains the task-index suffix; [finding P05](../../../analysis/re/evidence/components/persistence.json) gives the instructions. Keep such interrupted work separately, not as authoritative restore inputs. Runtime `/BufferedMapInfo`, POSIX semaphores and `/dev/shm` grids/persistence must not be archived back into a new process lifetime.

## Inclusion/exclusion manifest

The restore namespace below is deliberately smaller than `/mnt/data/rockrobo`. **Absence is part of the snapshot:** a missing slot, vmap or DB sidecar must remain absent after restoration, even if a newer live set has created one. Names below are relative to `/mnt/data/rockrobo`; ranges mean exactly the listed decimal values, not arbitrary glob matches.

| Include if present | Captured membership | Reason |
| --- | --- | --- |
| `last_map`, `last_vmap` | `last_map` only | Native runtime grid and optional vmap |
| `user_map0` … `user_map9` | 0, 4 only | All supported saved grid slots, preserving absence of other slots |
| `user_vmap0` … `user_vmap9`, `mobility_test_vmap` | None | Preserve optional companion presence without assuming concrete vmap I/O is used |
| `PersistData_0.data` … `PersistData_11.data` | 1, 2, 6 only | Whole final persistence files; 0 retained only if actually present |
| `SharedMultiMapInfo`, `slam_info.cfg` | Both | Catalog/associations and per-map moved/using state |
| `robot.db`, `robot.db-journal`, `robot.db-wal`, `robot.db-shm` | Main DB only | Application map rows and **same-epoch** transaction companions |
| `appproxy.map` | Present | Application map-state companion |
| `StartPos.data`, `ChargerPos.data`, `ChargerType.data`, `Rotater.cfg` | All present | Pose/dock/navigation companions; do not recalculate |
| `RoboController.cfg`, `robot.setting`, `lab.cfg` | All present | Map/recovery/operational-mode configuration shared with other settings |
| `map/` and all its captured contents | Empty directory | Narrow map-output directory, not the whole data root |

For this archive that is **17 regular files and one empty directory**: the six native files, `SharedMultiMapInfo`, `slam_info.cfg`, `robot.db`, `appproxy.map`, the four pose/dock/navigation companions, `RoboController.cfg`, `robot.setting`, `lab.cfg`, and `map/`. Tar records these regular files as numeric uid/gid **0:0**, mode **0644**; `map/` is 0755. Future backups should preserve their actual metadata, not impose the captured metadata on a different owner layout. The three configuration files are indivisible shared files: restoring them also rolls back their non-map settings (for example fan/water/dock preferences). This narrow collateral rollback is explicit; there is no attempt to splice selected keys.

**Do not restore:** `exclude_process.conf` (owned by supervision), `apptimer.cfg`/`servertimer.cfg` (scheduling), `robot_status.db` and its sidecars (separate status DB, not the `bakmaps` database), `rrlog/`, `devtest/`, update/version/sound files, timezone/localtime/country configuration, `lds_info.txt`, `/mnt/data/valetudo_config.json`, `/mnt/data/miio`, `/mnt/data/wlan`, `/mnt/default` identity/calibration, `/mnt/reserve` boot hooks, firmware, or any `/run`/`/dev/shm` object. Keep a broader original archive privately if needed, but do not deploy it wholesale. No secrets need to be printed or entered for this file procedure.

**Quarantine, do not promote:** `slam_info.cfg.cache`, other managed-name `.cache` work products and `<managed-final>.tmp*`. The capture contains none. A forced stop may leave them with newer bytes; that is not permission to rename one into the final namespace. They should be retained separately for diagnosis and removed from active paths before restoring. Likewise, keep an old live database's sidecars only with that old database in quarantine—never next to the replacement main file.

## Preconditions

Confirm the deployed paths, firmware, file membership and metadata before acquisition. Obtain a new idle stopped snapshot rather than treating the original live capture as transactional. Journal policy need not be changed: keep the stopped main database and its same-epoch companions. See [cold-start selection](startup.md) for why runtime and primary slots both matter.

## Supporting sources and address conventions

All sources were read locally; captures and prior analysis remain unchanged. Source-root is `/home/user/tmp/illegalplainape`, not necessarily this worktree. The primary capture sources are `inventory.txt`, `map-and-config.tar`, `map-files-before.md5` and `map-files-after.md5`; private `/tmp/map-file-contract` extraction was used for archive listing and read-only SQLite header/schema/count inspection (`mode=ro&immutable=1`, no journal-mode pragma).

Existing evidence: the historical [offline feasibility assessment](../../history/offline-feasibility.md), [backup dependencies](../../../analysis/re/evidence/restore/backup-dependencies/dependencies.json), [consistency dependencies](../../../analysis/re/evidence/restore/consistency/dependencies.json), [AppProxy DB initializer](../../../analysis/re/evidence/restore/backup-dependencies/focused/AppProxy/0x00020440.c), [backup DB writer](../../../analysis/re/evidence/restore/backup-dependencies/focused/AppProxy/0x0003a430.c), and selected function/instruction exports under `evidence/{AppProxy,librrnavdrv.so,librobopersist.so,librrutils.so}`. The [storage reference](storage.md), [persistence behavior](persistence.md), [region layouts](regions.md), rootfs startup files and canonical decompilations describe the underlying formats and paths.

These findings and the [startup reference](startup.md) identify binary/function/VA directly; no new evidence/test infrastructure was added. Ghidra work used `analysis/re/tooling/retool.py copy` into `/tmp/map-file-contract/project`, then only that private copy. The additional `RoboController` import and temporary discovery/decompilation scripts also stayed under `/tmp`. LLVM disassembly used Thumb mode for these functions; ARM PLT veneers were not interpreted as Thumb implementation bodies. `0x20babc` and `0x20c7f0` entries were distinguished from interior prologues with actual instructions/unwind metadata. Addresses are even virtual addresses; AppProxy/RoboController executable file offsets are VA−0x10000 in their cited code segments, while the cited shared-library text has VA=file offset. BSS `0x35367c` is a virtual address, **not** a file-offset lookup.
