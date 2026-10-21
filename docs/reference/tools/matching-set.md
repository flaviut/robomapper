# Matching-set scripts

Use these scripts only inside the [stopped maintenance window](../../guides/stopped-backup.md), on the same robot and firmware. They preserve a whole disk epoch; they do not decode maps or invoke vendor recovery commands. The [successful unchanged restore](../../history/2026-10-21/unchanged-restore.md) used private boot-pinned launchers. These cleaned versions have not been rerun on the device.

```text
review fresh status, identities and stop.sh
  -> arm recover.sh in its own session (120-second uptime deadline)
  -> operations.sh records its separate group identity
      -> stop.sh: exclude hosts, confirm exit, obtain MCU hold-off
      -> matching-set.sh capture
      -> transfer archive off-device and compare hashes
      -> matching-set.sh install: stage, quarantine, replace, verify
  -> recover.sh ends the operations group
      -> roll back an incomplete installation; verify the whole set
      -> restore original supervision on disk; sync; normal reboot
  -> observe real map, stationary pose and fresh quiet status
```

No script starts automatically. `approved-once` is an explicit invocation argument, not a substitute for checking readiness. Neither a deadline nor `sync` bounds blocked flash I/O or reboot time. Keep uninterrupted power and SSH available. A failed rollback or surviving operations child prevents normal reboot; services remain excluded and require intervention.

## File operations

[`matching-set.sh`](../../../tools/map-maint/matching-set.sh) takes:

```text
sh matching-set.sh capture|check|install|verify|rollback ROOT WORK
```

`ROOT` is the actual map directory; `WORK` must be a private sibling/outside directory on the same filesystem. `capture` creates it and refuses an existing path. The supported namespace is the [finite matching set](../maps/matching-set.md#inclusionexclusion-manifest). The script deliberately refuses symlinks, special files and a nonempty `map/`; review any changed device layout before extending it.

- `capture` records presence, absence, root path, interrupted-work names and tar archives. It preserves numeric ownership, permissions and tar timestamps, then hashes the snapshot and writes `capture.complete` after flushing.
- `check` validates snapshot hashes, canonical namespace, manifest partition and archive membership/types. It does not require services to be stopped and does not inspect map contents.
- `install` requires `WORK/offdevice.verified`, stages and repacks the archive, quarantines current members and managed `.cache`/`.tmp*` files, then installs exactly the snapshot's present members. It verifies archive equality and absence before writing `install.complete`. A failed installation leaves `install.started` for recovery; do not resume consumers.
- `verify` compares the current stopped set against the snapshot, including recorded absence and archived metadata. It is not a post-boot verifier: startup may legitimately update configuration companions.
- `rollback` reinstalls the **captured snapshot**, not selected quarantine files. It requires `install.started`, re-extracts before removing any active member and can be retried after interruption. Remaining managed work products move to `rollback-work/`; quarantine remains available for diagnosis.

Except for `check`, the script refuses known live hosts, mapped files beneath `ROOT`, or managed paths open in visible process descriptors. These observations are not an atomic barrier or a complete per-thread descriptor audit. The caller must still gate respawn/commands, check identified descendants and obtain MCU hold-off with the native helper. Run as root on the robot; do not extract/repack the deployed snapshot as an unprivileged host user.

Archives and manifests must come from a private, trusted session. MD5 detects accidental corruption and transfer mismatch here; it does not authenticate an archive. This is not a general importer for untrusted tar files. Do not edit the snapshot or splice epochs. Tar equality checks archived timestamp precision, not nanosecond timestamp preservation.

## Prepare a fresh session

[`operations.sh`](../../../tools/map-maint/operations.sh) and [`recover.sh`](../../../tools/map-maint/recover.sh) target the tested firmware and `/mnt/data/rockrobo`. They require a new private `/mnt/data/map-*` directory and the current boot ID. The cleaned recovery supports the demonstrated **present, nonempty, regular** original exclusion file, not absent/empty originals.

Before any service stop, stage the three shell scripts and the [native helper](map-maint.md) in a private tools directory. Check their hashes against your local copies. Prepare `SESSION` with:

```text
boot-id                  current /proc/sys/kernel/random/boot_id
exclude.original         exact current exclusion bytes
original-exclusions.tar  root tar of exclude_process.conf, retaining metadata
original.md5             hashes of the three files above, in that order
stop.sh                  reviewed prelude using this boot's process identities
exclusions.content       complete validated exclusion content, preserving originals
inputs.md5               hashes of stop.sh and exclusions.content, in that order
```

Create the hash records from within `SESSION`, so filenames are relative:

```sh
md5sum boot-id exclude.original original-exclusions.tar > original.md5
md5sum stop.sh exclusions.content > inputs.md5
```

Keep an independent off-device copy of the originals before arming recovery. Confirm current paths, firmware, process lists/modules, UART ownership, tmpfs layout, free space, quiet/docked status, battery and both updaters. Gate schedules and external automation throughout startup verification; the scripts do not do this for you.

### The stop prelude is intentionally session-specific

Do not reuse historical PIDs or executable-only absence checks. `stop.sh` receives `SESSION` as its first argument and must:

1. Validate fresh PID/start-tick/executable/argv/hash identities and original supervision bytes/metadata before any signal. Refuse changed inputs, unexpected process lists or the optional Wi-Fi rewrite branch described in the backup guide.
2. TERM only the identified Valetudo process and confirm its exit. Send the complete exclusions once with `map-maint exclusions SESSION/exclude.original SESSION/exclusions.content`.
3. Confirm actual map hosts, bridges, updaters and identified descendants have exited while WatchDoge, SSH, networking and logging remain alive. Inspect remaining managed-file handles/maps and every relevant task; delivery is not an exit/save acknowledgment.
4. Run `map-maint mcu-disable` **once**, after UART ownership checks, and return success only on native return 0. Capture refusal diagnostics and fail rather than retrying or bypassing ownership checks.

Set the helper's documented `LD_LIBRARY_PATH` in this prelude; the orchestration/recovery scripts clear inherited loader overrides. Stop nothing else, perform no map writes in the prelude, and never signal WatchDoge. A universal stop prelude is not supplied because its identities, command gates and exclusion-token coverage expire each boot/session.

## Arm, operate and verify

After reviewing all inputs, launch recovery first with closed stdin and persistent logs. Here `TOOLS` is the private staged directory and `SESSION` is the prepared private directory; choose new paths, not a historical session name.

```sh
(trap '' HUP; exec setsid /bin/sh "$TOOLS/recover.sh" "$SESSION" approved-once) \
    </dev/null >"$SESSION/recovery.log" 2>&1 &
```

Wait for `recovery.ready`. Its fields are PID, start tick and uptime deadline. Verify `/proc/PID/stat` fields 5/6/22 equal `PID/PID/start-tick`; then launch operations separately, within 20 seconds of arming:

```sh
(trap '' HUP; exec setsid /bin/sh "$TOOLS/operations.sh" "$SESSION" approved-once) \
    </dev/null >"$SESSION/operations.log" 2>&1 &
```

Operations publishes `backup.ready` after creating `untouched-stopped-backup.tar`. Transfer that archive privately, compare the robot/local digest, validate its snapshot and flush the off-device copy. **Only then** create `SESSION/matching/offdevice.verified`. The marker is operator attestation, not an automatic transfer check. Operations waits up to 40 seconds and refuses installation with less than 30 seconds left before recovery's deadline.

Recovery runs independently of SSH, stops only the identified operations group and refuses to proceed while a non-zombie child remains. It restores an incomplete installation from the whole snapshot before restoring supervision. It never live-reloads exclusions, starts consumers manually or forces reboot. If no services were touched, it exits without rebooting. `recover.now` requests early recovery on failure or operator abort.

After reboot, confirm a new boot ID, normal process identities/UART ownership, original exclusion bytes/owner/mode and fresh idle/docked status with no errors or update. Wait past Valetudo's startup placeholder (`metaData.defaultMap=true`) before comparing map layers/entities, rooms/restrictions and pose. Do not issue an extra vendor recover/load/save RPC. Retain snapshot and quarantine until inspection is complete; do not immediately clean.

## Compare the loaded map

Save authenticated read-only `/api/v2/robot/state/map` responses before maintenance and after the real map has loaded. Keep credentials and map JSON private. [`compare_maps.py`](../../../tools/map-maint/compare_maps.py) checks size, pixel size, layers, entities and map-format version exactly, ignoring refreshed vendor IDs/nonces:

```sh
python tools/map-maint/compare_maps.py before.json after.json
```

Exit 0 and `"match": true` mean the compared content matches. A startup placeholder is rejected rather than reported as a lost map. This does not replace fresh robot status, disk checks or visual inspection.

