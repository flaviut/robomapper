# Unchanged matching-set restore passed

On October 21, 2026, S7 firmware `4.3.5_1612` completed a fresh stopped backup, byte-preserving reinstallation and controlled reboot. The loaded map matched the pre-test map. No map edits, cleaning or vendor recover/load/save RPCs were issued.

## Sequence and observations

Times are UTC.

- **13:18:07:** fresh vendor status was docked, battery 100%, error/cleaning/returning/locating/dock-error flags zero; vendor OTA state was `idle`. Valetudo also reported its updater idle. Vendor files contained only the two DND guards; Valetudo timers were empty.
- **13:18:09:** service-stop interval began after independent, boot-pinned recovery was armed. Valetudo was stopped; WatchDoge exclusions stopped the loader, controller, AppProxy and bridge. WatchDoge, SSH, networking and logging remained running. The native MCU helper returned 0 after its ownership checks; this was a transport acknowledgment, not sentinel readback.
- A fresh stopped set contained **17 regular files and the empty `map/` directory**. The snapshot recorded the entire finite namespace, including absence. Its off-device transfer hash was verified before installation was authorized.
- The set was extracted into a same-filesystem stage and repacked for comparison. Current managed members and interrupted work were quarantined, then the stage was installed. A second tar comparison proved the installed bytes and archived metadata identical; absent members remained absent. The completion marker was written only after verification and `sync`.
- **13:18:30:** recovery had ended the private operations group and restored the original supervision file on disk. It then requested normal reboot, without live exclusion reload. Whole-set rollback was not needed.
- **13:19:19:** a different boot ID and the normal service identities were observed. The loader again owned both MCU UART devices. Original exclusion bytes, uid/gid `0:0` and mode `0644` were restored.
- **13:20:03:** fresh status was again docked at 100%, with all reported activity/error flags zero and vendor OTA state `idle`.

The first post-boot HTTP map was Valetudo's **startup placeholder** (`metaData.defaultMap=true`), not evidence of a lost map. Once the real map arrived, all **11 layers and all three entities** matched the pre-test JSON exactly: path, charger location and robot position, including its angle. Size and pixel size also matched. Only map metadata such as nonce and vendor map ID changed.

A separate post-boot disk comparison found the six native grid/persistence files and `SharedMultiMapInfo` still byte-identical to the stopped snapshot. No recovery RPC was used to make the map appear.

## Retained evidence

Private off-device directory:

```text
/home/user/.local/state/pi/map-backups/map-reload-20261021T1315Z/
```

`untouched-stopped-backup.tar` is 1,116,160 bytes, SHA256:

```text
2fa9a84e12700ff49676419660b1a2159aa4753b58ec2d5539ff7289ccd1a85f
```

`returned-session-records.tar` is 5,662,720 bytes, SHA256:

```text
d91e42cf8d305fb39659a343ab5904e63c71b4c112a4c4d43645b65b2ff75da7
```

The directory also retains exact session launchers, original supervision settings, pre-/post-boot HTTP maps, admission/final telemetry, native-file hashes and `result.json`. The robot retains the matching session under `/mnt/data/map-reload-20261021T1315Z/`, including quarantine. These private artifacts are not checkout dependencies or reusable launchers.

## What this establishes

The [restore procedure](../../guides/matching-set-restore.md) works for reinstallation of a newly acquired, unchanged set on this robot and firmware, followed by normal cold startup. It does not establish edited-map import, restoration of an older map, warm reload, navigation safety after an edit, power-loss recovery or an independent rescue connection.

The [cleaned scripts](../../reference/tools/matching-set.md) were extracted after this run. They have **not** been rerun on the robot; the successful run used the retained private, boot-pinned launchers. Device rollback was not exercised.
