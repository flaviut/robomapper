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

### Reboot recovery is native-map loading, not a DB-to-grid converter

Focused inspection closes the saved lab/config inputs. `librrutils.so:rr_get_lab_status:0x17c4` reads `RR_UDATA + /rockrobo/lab.cfg` (fallback `/mnt/data`) and parses decimal text, returning zero on missing/read failure. The archive's `lab.cfg` contains ASCII `1`. `librrnavdrv.so:0x1a6064` copies its low bit to relocation-manager bytes +0x1d/+0x1e; accessors `0x1a5f88/0x1a5f8c` return those bytes. These are the previously unnamed gates in startup/reboot handling. Preserve `lab.cfg`; do not toggle it to try to select a map.

`OnStateRecoverFromReboot` is **`librrnavdrv.so:0x20c7f0`** (EHABI entry at table VA `0x2f1be4`; next entry `0x20cad0`). Before `LoadLastMap`, this state may load a native primary chosen in state+0x390, or a candidate vector at +0x384, using `LoadSLAMMap(...,flag,1)`. Candidate construction `0x20e78c` gets the **primary** list from `GetSharedMultiMapList`, starts selected flag at 2, records a primary with `Map<flag>.Using`, and can prefer the current primary when runtime flag 1 is not marked moved. Captured config has `Map1.Using=1`, `Map2.Using=0`, `Map6.Using=0`, `Map1.Moved=0`, catalog current=2 and sole primary=2. Thus this candidate selection resolves to **primary 2**, not backup 6. Preserve primary 2 and runtime 1 because both recovery and last-map states can consume them.

The invocation at `0x759e0` (enclosing function `0x7589c`) initializes relocation state via `0x20b174` with +0x31d=1, +0x31e=0; the later task entry `0x82224` can enable +0x31e and provide an explicit flag. `OnStateRecoverFromReboot` checks those request bits and the saved lab gates before choosing a primary/vector. Its failed-load fallback calls `RecoverAfterReboot:0x66888`: this reads saved navigation/start/charger configuration through `0x15da28`, `0x15d7b0`, `0x15d7c0`, then restores device/start/dock state. That fallback is not an implicit `user_map4` selection or an SQLite blob import. The point is not to depend on one branch: retain its native and pose/config inputs together.

Older **native backup** bytes can deliberately replace the primary/runtime set through AppProxy recovery commands. `recover_multi_map:0x51628` selects the catalog backup; `0x68c14` sends a native load for that selection; successful continuation `0x3c7a0` resets routing, makes the requested primary current, then requests native save destinations **[1, requested primary]** through `0x3c6bc`. Finally `0x3a5c0/0x3a430` regenerates the application DB row. Do not issue a recover/load/save command as an extra step after restoring a set: it can overwrite restored flags 1/2 with older flag 6.

The audited DB read of `bakmaps` (`0x23070`) has two direct callers: backup-row compare/update `0x3a430` and application response worker `0x1d728`. The latter packages the blob into a response object; it does not install a native grid. Together with the native recovery series, this establishes the direction for these paths: **native map → app projection/DB**, not **DB backup blob → full native map**. AppProxy constructor `0x8c720` attaches shared regions and constructs `RR_UDATA + /rockrobo/appproxy.map`; the 40-byte captured file is not a hidden occupancy grid. No automatic DB-to-native recovery edge was found in these bounded paths. This is not a claim that every firmware command was audited; gate command producers throughout restoration/startup instead of relying on that negative claim.

`RoboController` config is a separate recovery input worth retaining intact. Static import of the saved binary (private `/tmp` project, never execution) establishes `0x1d618` defaults missing `RoboController.runtime.need_recover_map` to 0; `0x1e0e4` reads it into config-object+0x1f4; `0x1ce00` updates the field and writes the existing config file. Capture has **0**. Its read at `0x2e098` gates the start/control path when nonzero; clear callers include `0x2266a/0x226e6`, `0x2e220`, `0x3e5e4/0x3e842`. This does not establish identity with NavCore's unrelated byte+0x271. **Do not invent that identity or manually reset either flag.** Restoring the unchanged same-device `RoboController.cfg` retains the observed zero and its map bookkeeping.

### Why a full reboot removes the buffered-load override

Saved `etc/init/rcS:11–22` mounts a new tmpfs `/run`, makes `/run/shm`, and symlinks `/dev/shm` to it. `S03mountall` subsequently runs `mount -a`; `etc/fstab` also declares tmpfs for `/run/shm`. A genuine kernel reboot therefore removes the old named `/BufferedMapInfo` object, task backing, semaphore and other shared regions **for this mount layout**. It does not replay their mutexes/pointers from disk. `librobopersist.so:0x1a990` opens/creates the buffer root, and `0x1a898` initializes missing/new magic/version state. Initial metadata/shared-region creation (`0x17a70`, region-8 `0xe0c4`) precedes use/subscription/load. Consumers can then initialize new shared state from the restored disk set; a new buffer created by a new save contains post-boot work, not the pre-stop task.

That conclusion applies to a real reboot, **not** restarting AppProxy/rr_loader alone, and not merely calling cancellation or robust-mutex recovery. Confirm the actual `/dev/shm` mount is still tmpfs and that no custom boot hook imports saved shared-memory bytes. Private grid caches also disappear at process exit. Native recovery can still select a different restored disk slot; reboot is cache clearing, not a guarantee that only `last_map` is read.

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

## Candidate backup/restore steps after hosts are stopped

These are a **conditional offline procedure**, not commands executed on the robot. Prerequisite: the service/heartbeat lane has stopped every actual map host and command producer, kept required hardware feeding alive, prevented respawn and retained that window through `sync` and controlled reboot. The robot must be stationary/idle with a known-good map, not paused halfway through a cleaning/save/recovery. Copying a stopped set preserves disk bytes; it does not repair an interrupted historical save. Use enough free space for the snapshot, staged replacement and quarantine, and uninterrupted power. Any command failure means **do not resume consumers** until the old complete set or chosen complete set is installed.

### 1. Back up the whole stopped namespace

For the saved environment, the following shell fragment builds the finite namespace and records presence/absence. It is an acquisition recipe, not a checker or a device invocation performed here. Run as root in the stopped window; choose a new, private `WORK` directory outside `rockrobo`, on the same data filesystem. Keep the resulting archive off-device as well.

```sh
ROOT=/mnt/data/rockrobo
WORK=/mnt/data/map-maintenance-CHOOSE-NEW-ID
umask 077
mkdir "$WORK" || exit 1
cd "$ROOT" || exit 1

# Keep this exact namespace with the snapshot; it owns absence as well as bytes.
{
    printf '%s\n' last_map last_vmap mobility_test_vmap
    for n in 0 1 2 3 4 5 6 7 8 9; do
        printf '%s\n' "user_map$n" "user_vmap$n"
    done
    for n in 0 1 2 3 4 5 6 7 8 9 10 11; do
        printf '%s\n' "PersistData_$n.data"
    done
    printf '%s\n' SharedMultiMapInfo slam_info.cfg \
        robot.db robot.db-journal robot.db-wal robot.db-shm \
        appproxy.map StartPos.data ChargerPos.data ChargerType.data Rotater.cfg \
        RoboController.cfg robot.setting lab.cfg map
} > "$WORK/namespace"

: > "$WORK/present"
: > "$WORK/absent"
set --
while IFS= read -r name; do
    if [ -e "$name" ] || [ -L "$name" ]; then
        printf '%s\n' "$name" >> "$WORK/present"
        set -- "$@" "$name"
    else
        printf '%s\n' "$name" >> "$WORK/absent"
    fi
done < "$WORK/namespace"
tar -cpf "$WORK/files.tar" "$@" || exit 1

# Retain interrupted work separately; never use it as a final-file restore set.
set --
while IFS= read -r name; do
    for path in "$name".cache "$name".tmp*; do
        if [ -e "$path" ] || [ -L "$path" ]; then
            set -- "$@" "$path"
        fi
    done
done < "$WORK/namespace"
if [ "$#" -gt 0 ]; then
    tar -cpf "$WORK/interrupted-work.tar" "$@" || exit 1
fi
sync
```

This finite set is for the observed flat root. If current configuration points persistence or AppProxy elsewhere, **stop here and adapt the destination mapping** rather than copying the wrong directory. Do not source an untrusted old environment file into a live shell. The archived `map/` directory is the only recursive member. The second loop preserves any pre-existing managed `.cache`/`.tmp*` files in a separate private interruption archive, not `files.tar`. Keep existing absence/presence lists with the immutable snapshot; do not reconstruct them from the target at restore time. The source `map-and-config.tar` is broader than this manifest: extract only the table's present members to prepare a restore set, never run an unrestricted root extraction of it.

### 2. Stage an untouched matching set, then remove the whole current epoch

Have a chosen `files.tar`, `namespace`, `present` and `absent` from the **same** stopped acquisition. For the historical capture, construct these using the literal captured membership above; missing sidecars are intentional. No map decoding or SQL modification is involved. `map_codec.py` is not used for untouched matching-set restore: its `pack` operation changes one RRSLAM raster plus digest, not catalog/persistence/DB/poses.

Prepare a new root-owned, mode-0700 working directory on `/mnt/data`, outside the restore namespace. Extract the chosen tar into a `stage/` directory there **while all hosts remain stopped**. Preserve numeric ownership and permissions using the root tar implementation; on a host-side staging machine, do not lose metadata in a non-root extraction/repack. Only the final relative names above may be present. Stage on the destination filesystem so installation renames do not cross devices.

Then move **every currently present member of the finite namespace** to a separate same-filesystem `quarantine/` directory, retaining its metadata and missing-member list. This includes current sidecars even when the chosen snapshot lacks them, all now-present map slots absent from the snapshot, and the entire current `map/` directory. Move managed `.cache`/`.tmp*` work products out of the active namespace too. Do not move unrelated excluded files. After this removal, install all and only the chosen snapshot's `present` members from `stage/`; absence members stay absent. This is the crucial difference from “extract tar over the directory,” which leaves newer slots/journals behind.

For example, after trusted snapshot files have been placed under a newly selected `RESTORE` directory, these are the grounded rename operations (not a generic untrusted-archive importer):

```sh
ROOT=/mnt/data/rockrobo
RESTORE=/mnt/data/map-restore-CHOOSE-NEW-ID
# RESTORE/files.tar, namespace and present already came from the chosen snapshot.
mkdir -m 700 "$RESTORE/stage" "$RESTORE/quarantine" \
    "$RESTORE/interrupted-work" || exit 1
tar -xpf "$RESTORE/files.tar" -C "$RESTORE/stage" || exit 1

# Hosts must still be stopped; no SQLite handle may be opened on either set.
while IFS= read -r name; do
    if [ -e "$ROOT/$name" ] || [ -L "$ROOT/$name" ]; then
        mv "$ROOT/$name" "$RESTORE/quarantine/$name" || exit 1
    fi
done < "$RESTORE/namespace"
# Quarantine only work-product suffixes of managed names, never an unrelated glob.
while IFS= read -r name; do
    for path in "$ROOT/$name".cache "$ROOT/$name".tmp*; do
        if [ -e "$path" ] || [ -L "$path" ]; then
            mv "$path" "$RESTORE/interrupted-work/" || exit 1
        fi
    done
done < "$RESTORE/namespace"
while IFS= read -r name; do
    mv "$RESTORE/stage/$name" "$ROOT/$name" || exit 1
done < "$RESTORE/present"
sync
```

The work-product loop expands only the managed final names with suffix `.cache` or `.tmp*`; its existence check ignores unmatched literal glob patterns. It moves these bytes into a private interruption subdirectory. A blanket `rm *.tmp*` could destroy unrelated state. Do not combine main DB from one acquisition with journal/WAL/SHM from another, copy only the main file from a WAL snapshot, or delete a chosen snapshot's hot rollback journal to avoid recovery. If sidecars exist in a future stopped acquisition, preserve them as one opaque set; normal SQLite opening may recover/checkpoint that same epoch. The captured archive needs no sidecar installation because it has none.

These per-file renames are **not** multi-file atomic. Keep the hosts stopped after a partial failure. If power fails halfway through, normal startup can see a mixed set unless an independently available persistent service/boot gate prevents it. No such gate is established by this file lane; uninterrupted power through complete installation is therefore an assumption, not a proved interruption-recovery guarantee. The whole quarantine set is the rollback, not individual files cherry-picked from it. `sync` is a practical flush before startup, not a guarantee against failing flash or loss of power during the replacement window.

### 3. Cold-start using normal supervision, not a restore/recover RPC

After all files and metadata are installed and flushed, the service lane prepares the persistent exclusion configuration for normal next boot **without reloading exclusions into the running supervisor**, then performs a controlled reboot while maintaining its hardware-safety assumptions. Do not start any map consumer between replacement and reboot. Do not restore `exclude_process.conf` from this snapshot to accomplish this step.

On the saved boot, tmpfs/shared objects are fresh before normal services start. Saved `ProcessList.conf` orders `rr_loader -d`, `RoboController`, then `AppProxy` (rrlogd precedes them); this is launch order, not a promise of fully serial initialization. Let normal boot/subscription/load logic establish new shared state rather than manually starting AppProxy first or replaying raw shared buffers. Continue blocking new app/cloud/Valetudo/timer operations while the map loads. The map can pass through catalog-primary recovery and flag-1 last-map loading as above. Keep the untouched snapshot and whole quarantine until the operator has observed the expected map, rooms/restrictions and stationary pose; do not immediately start cleaning. No command forcing a native load/recover/save is part of this procedure.

## Minimal device-specific inputs still needed

This file lane does **not** need opaque-region decoding or a new replay project to restore unchanged bytes. It needs only the following operational inputs from the actual stopped device/service lane:

1. Actual `RR_UDATA`, `NAV_DYNAMIC_CONFIG_PATH`, firmware identity, normal process/module argv and `/dev/shm` mount layout still match the saved configuration; any extra **map-specific final file** added since capture must be identified before the finite namespace is used.
2. The selected snapshot is from an idle known-good state of this same robot/firmware, with actual member metadata and sidecar presence retained. The saved six-file MD5 observations do not retrospectively certify the entire live-acquired tar; a newly stopped backup is preferable as the first rollback anchor.
3. A stopped/respawn-blocked interval and controlled reboot route that are hardware-safe. This lane does not prescribe MCU commands or claim that an arbitrary `reboot` makes a partial set safe. If interruption-safe recovery is required beyond the uninterrupted-power candidate, the additional missing input is an independently available pre-consumer boot gate/rescue route; this document does not invent one.

Current runtime journal **policy** need not be determined or changed for this opaque stopped-copy route: sidecar presence and matching main-file epoch are sufficient acquisition inputs. The captured header/sidecar observations are concrete, while actual shutdown completeness, flash health, physical relocation and device behavior after restart remain device facts, not conclusions from static disassembly.

## Supporting sources and address conventions

All sources were read locally; captures and prior analysis remain unchanged. Source-root is `/home/user/tmp/illegalplainape`, not necessarily this worktree. The primary capture sources are `inventory.txt`, `map-and-config.tar`, `map-files-before.md5` and `map-files-after.md5`; private `/tmp/map-file-contract` extraction was used for archive listing and read-only SQLite header/schema/count inspection (`mode=ro&immutable=1`, no journal-mode pragma).

Existing evidence: [offline workflow](OFFLINE-MAP-WORKFLOW.md), [backup dependencies](evidence/restore/backup-dependencies/dependencies.json), [consistency dependencies](evidence/restore/consistency/dependencies.json), [AppProxy DB initializer](evidence/restore/backup-dependencies/focused/AppProxy/0x00020440.c), [backup DB writer](evidence/restore/backup-dependencies/focused/AppProxy/0x0003a430.c), and selected function/instruction exports under `evidence/{AppProxy,librrnavdrv.so,librobopersist.so,librrutils.so}`. Source-root `analysis/PERSISTENCE.md`, `REGIONS.md`, `ASSESSMENT.md`, `map_codec.py`, rootfs startup files and the canonical selected decompilations supplied the named seams.

New focused findings above identify binary/function/VA directly; no new evidence/test infrastructure was added. Ghidra work used `analysis/re/tooling/retool.py copy` into `/tmp/map-file-contract/project`, then only that private copy. The additional `RoboController` import and temporary discovery/decompilation scripts also stayed under `/tmp`. LLVM disassembly used Thumb mode for these functions; ARM PLT veneers were not interpreted as Thumb implementation bodies. `0x20babc` and `0x20c7f0` entries were distinguished from interior prologues with actual instructions/unwind metadata. Addresses are even virtual addresses; AppProxy/RoboController executable file offsets are VA−0x10000 in their cited code segments, while the cited shared-library text has VA=file offset. BSS `0x35367c` is a virtual address, **not** a file-offset lookup.
