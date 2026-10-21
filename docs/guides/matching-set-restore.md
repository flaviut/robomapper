# Restore an untouched matching set

A fresh stopped backup was reinstalled unchanged and loaded by normal reboot on October 21, 2026, on S7 firmware `4.3.5_1612`. All map layers/entities and the six native map/persistence files plus catalog matched afterward. See the [run record](../history/2026-10-21/unchanged-restore.md) for evidence and archive hashes. **Edited-map import and restoration of an older map remain untested.**

The [cleaned scripts](../reference/tools/matching-set.md) implement capture, staging, quarantine, verification and whole-set rollback, plus independently armed recovery. They require a reviewed stop prelude with fresh identities; they are not a universal launcher. The cleaned versions have not been rerun on the robot. The fragments below explain the storage mechanics, not the full service/recovery sequence.

Restore one same-robot, same-firmware stopped snapshot, including absent members, after all writers are stopped. The [matching-set reference](../reference/maps/matching-set.md) owns the finite namespace and exclusions; [startup selection](../reference/maps/startup.md) explains why a cold start and multiple native slots matter.

## Prerequisites

The successful run added independent recovery, off-device backup verification before installation, and tar comparisons of both stage and installed set. Prerequisite: every actual map host and command producer is stopped, required watchdog feeding remains active, and respawn is blocked through `sync` and controlled reboot. The robot must be stationary/idle with a known-good map, not paused halfway through a cleaning/save/recovery. Copying a stopped set preserves disk bytes; it does not repair an interrupted historical save. Use enough free space for the snapshot, staged replacement and quarantine, and uninterrupted power. Any command failure means **do not resume consumers** until the old complete set or chosen complete set is installed.

The tested sequence was: stop hosts and obtain MCU hold-off; acquire one stopped set; verify its off-device transfer; stage and compare; quarantine current members; install and compare; restore supervision on disk; reboot. On any incomplete installation, recovery must end the operations group and restore one whole snapshot **before** allowing normal startup. Device rollback was not exercised.

## 1. Back up the whole stopped namespace

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

This finite set is for the observed flat root. If current configuration points persistence or AppProxy elsewhere, **stop here and adapt the destination mapping** rather than copying the wrong directory. Do not source an untrusted old environment file into a live shell. The archived `map/` directory is the only recursive member. The second loop preserves any pre-existing managed `.cache`/`.tmp*` files in a separate private interruption archive, not `files.tar`. Keep existing absence/presence lists with the immutable snapshot; do not reconstruct them from the target at restore time. The source `map-and-config.tar` is broader than this manifest: extract only the [manifest's present members](../reference/maps/matching-set.md#inclusionexclusion-manifest) to prepare a restore set, never run an unrestricted root extraction of it.

## 2. Stage the snapshot and quarantine the current epoch

Have a chosen `files.tar`, `namespace`, `present` and `absent` from the **same** stopped acquisition. For the historical capture, construct these using the [captured membership](../reference/maps/matching-set.md#inclusionexclusion-manifest); missing sidecars are intentional. No map decoding or SQL modification is involved. The [offline codec](../../tools/map-maint/map_codec.py) is not used for untouched matching-set restore: its `pack` operation changes one RRSLAM raster plus digest, not catalog/persistence/DB/poses.

Prepare a new root-owned, mode-0700 working directory on `/mnt/data`, outside the restore namespace. Extract the chosen tar into a `stage/` directory there **while all hosts remain stopped**. Preserve numeric ownership and permissions using the root tar implementation; on a host-side staging machine, do not lose metadata in a non-root extraction/repack. Only the final relative names in that manifest may be present. Stage on the destination filesystem so installation renames do not cross devices.

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

These per-file renames are **not** multi-file atomic. Keep the hosts stopped after a partial failure. Retain the [persistent maintenance exclusions](../reference/services/supervision.md) until installation or whole-set rollback is complete; they prevent normal map-host startup after a power interruption under the saved supervisor configuration. That is an application-start gate, not an independent hardware-safe rescue environment: the MCU gate is still required on the next maintenance boot. Uninterrupted power remains the first candidate's assumption. The whole quarantine set is the rollback, not individual files cherry-picked from it. `sync` is a practical flush before startup, not a guarantee against failing flash or loss of power during the replacement window.

## 3. Cold-start using normal supervision

After all files and metadata are installed and flushed, prepare the persistent exclusion configuration for normal next boot **without reloading exclusions into the running supervisor**, then perform a controlled reboot while maintaining the service window's hardware-safety assumptions. Do not start any map consumer between replacement and reboot. Do not restore `exclude_process.conf` from this snapshot to accomplish this step.

On the saved boot, tmpfs/shared objects are fresh before normal services start. Saved `ProcessList.conf` orders `rr_loader -d`, `RoboController`, then `AppProxy` (rrlogd precedes them); this is launch order, not a promise of fully serial initialization. Let normal boot/subscription/load logic establish new shared state rather than manually starting AppProxy first or replaying raw shared buffers. Continue blocking new app/cloud/Valetudo/timer operations while the map loads. The map can pass through catalog-primary recovery and flag-1 last-map loading as described in the [startup reference](../reference/maps/startup.md). Valetudo may initially return its startup placeholder (`metaData.defaultMap=true`). Wait for the real map before judging restoration; the successful run then matched all 11 layers and all entities exactly. Keep the untouched snapshot and whole quarantine until the operator has observed the expected map, rooms/restrictions and stationary pose; do not immediately start cleaning. No command forcing a native load/recover/save is part of this procedure.

## Minimal device-specific inputs still needed

Unchanged-byte restoration needs no opaque-region decoding or new replay project. It needs these operational inputs:

1. Actual `RR_UDATA`, `NAV_DYNAMIC_CONFIG_PATH`, firmware identity, normal process/module argv and `/dev/shm` mount layout still match the saved configuration; any extra **map-specific final file** added since capture must be identified before the finite namespace is used.
2. The selected snapshot is from an idle known-good state of this same robot/firmware, with actual member metadata and sidecar presence retained. The saved six-file MD5 observations do not retrospectively certify the entire live-acquired tar; a newly stopped backup is preferable as the first rollback anchor.
3. A stopped/respawn-blocked interval and controlled reboot route that are hardware-safe. This guide does not prescribe MCU commands or claim that an arbitrary `reboot` makes a partial set safe. If interruption-safe recovery is required beyond the uninterrupted-power candidate, the additional missing input is an independently available pre-consumer boot gate/rescue route; this document does not invent one.

Current runtime journal **policy** need not be determined or changed for this opaque stopped-copy route: sidecar presence and matching main-file epoch are sufficient acquisition inputs. The captured header/sidecar observations are concrete, while actual shutdown completeness, flash health, physical relocation and device behavior after restart remain device facts, not conclusions from static disassembly.
