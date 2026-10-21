# Investigation history

These records preserve observations and decisions, including conclusions superseded by later work. They are not reusable procedures or current readiness checks. Private `/tmp` paths may no longer exist, and one-attempt authorizations have been spent.

The [offline feasibility assessment](offline-feasibility.md) predates the completed heartbeat analysis and backup. Use the [reference index](../README.md) for consolidated findings.

## October 21, 2026

Times below are UTC.

1. **04:20–04:26 — [Device observations](2026-10-21/device-observations.md).** Process/library identities, map-file metadata and the A14.G1 MCU build label. Runtime and primary persistence sizes already differed.
2. **04:34–04:39 — [Initial readiness](2026-10-21/readiness.md).** Passive Valetudo status, launch/stop behavior, administrative access and the 46-byte exclusion proposal. Vendor timers and update readiness were still unresolved.
3. **04:48–04:49 — [Vendor readiness](2026-10-21/vendor-readiness.md).** Saved timer interpretation, one OTA-state reply and fresh status resolved those questions for that instant. No cleaning timers were enabled.
4. **04:55 preparation; 05:08 attempt — [First session](2026-10-21/first-session.md).** Exclusion delivery succeeded, but the helper refused a remaining loader record before opening UART. No backup was created; independent recovery restored supervision and rebooted normally.
5. **After the first attempt — [Refusal analysis](2026-10-21/first-refusal.md).** Explains why executable-only absence and task-name checks could disagree. That first log did not identify the refusing task; the analysis added diagnostics, not a zombie exception.
6. **12:01–12:03 — [Completed stopped backup](../guides/stopped-backup.md).** After a second refusal and a narrow zombie-check correction, the third attempt acquired an untouched stopped set and returned normally. The guide records the archive hash and private off-device location; the [helper reference](../reference/tools/map-maint.md#requesting-mcu-hold-off) describes the current guard.

7. **13:18–13:20 — [Unchanged restore](2026-10-21/unchanged-restore.md).** A fresh stopped backup was verified off-device, reinstalled byte-for-byte and loaded by normal reboot. All map layers/entities matched; no rollback or map edit was needed. Valetudo briefly showed its startup placeholder before the real map arrived.

Exact device-run launchers, logs and map backups remain private. The [cleaned scripts](../reference/tools/matching-set.md) provide file operations and bounded recovery/orchestration without stale PIDs or credentials; they have not been rerun on the device. Edited-map import remains untested.

## Reading historical evidence

Static review reports and machine handoffs remain under [`analysis/re/evidence/`](../../analysis/re/evidence/) and [`analysis/re/recovery/`](../../analysis/re/recovery/). Their acceptance applies to the stated checkpoint, not later device behavior. Older references to `analysis/re/*.md`, `tooling/README.md` and `recovery/USAGE.md` name the former document locations; the maintained material now lives under `docs/`.

The changed exclusion-file timestamp still has no established startup writer. Original bytes, owner and mode survived the demonstrated return; exact timestamp preservation across startup is not established.
