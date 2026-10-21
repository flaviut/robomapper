# Back up the S7's maps with services stopped

Stop the map-writing services, request MCU heartbeat hold-off, copy the matching files, then restore supervision and reboot normally. This route worked on S7 firmware `4.3.5_1612` on October 21, 2026. WatchDoge, SSH, networking and logging stayed running throughout the copy.

The robot returned docked at 88%, with no reported error or activity. No map file was edited, replaced or restored. The MCU request received a transport acknowledgment; we did not read back the stored heartbeat setting.

```text
Normal operation
  -> arm independent recovery
  -> stop Valetudo and the vendor map services
  -> check UART ownership and request heartbeat hold-off
  -> copy the stopped matching set
  -> restore original supervision settings on disk
  -> normal reboot
  -> confirm normal operation and copy the backup off-device
```

## The acquired backup

The private off-device directory is:

```text
/home/user/.local/state/pi/map-backups/map-maint-session-20261021T1158Z/
```

Its `untouched-stopped-backup.tar` is **1,116,160 bytes**, with SHA256:

```text
37fb5d2a3dab0dd85ddd537e3571e957ce517f00c908c68a25dcfdd308129790
```

Robot and local MD5 both equal `7bd6af71635532868ff47f2cabbd3a05`. The robot retains its copy under `/mnt/data/map-maint-session-20261021T1158Z/`.

The outer archive contains `snapshot/files.tar`, file-presence and absence lists, metadata, hashes and the completion marker. The inner archive holds the stopped map files. The separate `returned-session-records.tar` is an operation log, not a map backup. Neither archive has been used for restoration.

The same private directory preserves the helper, `operations.sh`, `recover.sh`, `capture-refusal.sh` and the original supervision settings. These are the exact files used successfully, **not reusable launch scripts**: their paths, boot ID, process start times and hashes describe that run. Prepare fresh copies with current identities before another operation. The robot's temporary scripts disappeared on reboot.

## Prepare before stopping services

Use strict-trust SSH and the established read-only status and updater queries. Proceed only when the robot is idle or docked, has no reported cleaning, returning, locating or error activity, and the updater is idle. The completed run required at least 80% battery for its short window; it started docked at 88%. Keep external automation from issuing commands during maintenance. Do not move the robot merely to meet a charging preference.

Identify the current service executables, arguments and process start times. Do not reuse PIDs from an earlier boot. Preserve the **current** `exclude_process.conf` independently, including whether it exists, its exact bytes, owner, mode and timestamp. Keep a private off-device copy and a separate on-robot copy outside `/mnt/data/rockrobo`.

Build the [native helper](../reference/tools/map-maint.md) against the saved runtime. The successful binary's SHA256 is `fb75e397eb09c51aa1a0402918fe55c357363be5843e6e7f896e6b7d7d8987f0`. Prepare and inspect both the operation and recovery scripts before launching either.

## Stop, copy and return

1. **Arm recovery first.** Run it in its own `nohup`/`setsid` session with closed stdin and persistent private logs. Verify its identity and deadline before starting operations separately. The completed run used a 120-second uptime deadline, with early recovery on success or failure. Recovery must restore the saved exclusions on disk, sync and request normal reboot without depending on SSH.

2. **Stop the producers, not WatchDoge.** TERM the identified Valetudo instance. Use the helper to send the complete WatchDoge event-8 exclusion content once, preserving all original exclusions. The completed run appended `\nrr_l\nRoboC\nAppP\nmiio\nSysU\n`, producing 46 content bytes. Recheck these substring tokens against every installed process list before reusing them. Empty or very short content selects a destructive event and must never be used to clear exclusions.

3. **Wait for actual host exit, then request MCU hold-off.** Confirm the loader, controller, AppProxy and relevant bridges/updater have stopped while protected services remain alive. Exclusion delivery does not acknowledge exit or a completed save. Invoke `map-maint mcu-disable` once; require return 0 before copying. The helper checks every task and UART character-device ownership before using the vendor API. A zombie task with a missing executable no longer blocks solely because its name is `rr_loader`; its descriptors and every sibling are still checked. On refusal, capture the reported process/thread state and recover immediately without retrying or bypassing ownership checks.

4. **Copy one stopped set.** Use the [finite file contract](../reference/maps/matching-set.md), not a selection of convenient rasters. Include persistence, catalog, database and present sidecars, pose/config companions, vmaps, ownership/modes and recorded absence. Preserve interrupted work separately rather than treating it as current state. Check available space, keep consumers stopped throughout, and sync before writing a completion marker. The completed copy ran between the service-stop marker at 12:01:36 UTC and recovery at 12:01:41 UTC.

5. **Restore supervision on disk and reboot normally.** Recovery ends only its identified private operations group, restores the original exclusion bytes and metadata, compares the bytes, syncs and requests `/sbin/reboot`. Do not send a live exclusion-clear request while key services are missing, rerun the startup launcher, signal WatchDoge or force reboot. A real reboot clears the old tmpfs map buffers.

6. **Confirm return before acquiring the backup off-device.** Establish a new boot, expected service executable/argument identities, ordinary loader UART ownership, restored exclusion bytes/owner/mode and fresh quiet/update status. Then transfer the completed archive privately and compare transfer hashes. No completion marker means no completed backup. The completed run showed normal services by 12:03:08 UTC and quiet docked status at 12:03:13 UTC.

## Limits before editing or restoration

This establishes a practical stopped-backup window and normal return. It does **not** demonstrate map replacement, an unchanged restore or edited-map import. Use the [maintenance plan](../plans/map-maintenance.md) and [edit contract](../reference/maps/editing.md) before planning writes. Do not assume current runtime and primary persistence match, change map coordinates, or invoke segmentation/restore RPCs as an automatic repair step.

Recovery remains software-only. Its 120-second deadline does not bound flash flushing or reboot time, and no independent rescue connection or power-loss repair hook has been demonstrated. Power loss before exclusion restoration can leave the vendor services excluded at the next boot. Keep uninterrupted power and independent originals; do not treat this route as interruption-safe installation.

The successful recovery restored the original exclusion bytes and metadata before reboot. After boot, the same bytes, owner and mode remained, but the modification time was newer. Its writer is unidentified; exact timestamp preservation across startup is not established.
