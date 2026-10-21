# Why the maintenance attempt stopped

> Historical record, retained as written. Later findings supersede some conclusions. Do not reuse its PIDs, staging paths or launch commands. See the [history index](../README.md) and [demonstrated backup procedure](../../guides/stopped-backup.md).

**The October 21, 2026 attempt ended in a safe refusal, not a stopped backup.** Independent recovery restored the original exclusion bytes and requested a normal reboot; the robot returned with its ordinary services and loader UART ownership. No map archive was created, no map files were acquired or edited, and the helper never reached the heartbeat request or its UART initialization path. This investigation used only saved local files. It made no robot connection, service stop, UART operation, firmware change or original-user-file change.

The [session record](first-session.md#approval-and-actual-outcome) gives the observed recovery and post-boot status. The exact scripts and logs remain privately under `/tmp/map-maint-session-20261021T0455Z`. Those files describe one spent authorization, not a ready-to-run retry.

## Two absence checks asked different questions

In saved `operations.sh`, `blocked_absent()` walks `/proc/[0-9]*/exe`. It rejects a finite set of exact executable paths and skips every failed `readlink`. It neither inspects task names nor enumerates each process's threads. After TERM to the identified Valetudo instance and disappearance of its executable link, the exclusion helper returned 0 after writing its packet. Operations passed `blocked_absent()`, its protected-service checks and the maintenance-content comparison, then invoked `mcu-disable` once.

The [native helper](../../../tools/map-maint/map-maint.c) has a deliberately broader gate. `owners_absent()` opens each process directory, and `tasks_absent()` opens every numeric entry in its `task/` directory. For each task, `loader_absent()` first checks the executable **basename**, including `rr_loader (deleted)`, and then checks `comm` for exactly `rr_loader\n`. An executable lookup returning `ENOENT` or `ESRCH` does not skip the name check. Only after the loader check passes does that task's UART-descriptor check run. Other inspection errors refuse rather than establish absence.

The operation log ends with:

```text
Exclusion packet written. This does not acknowledge event handling, host exit or storage flush.
Loader still exists; MCU disable refused.
```

At baseline commit `d502085`, both the executable-match and comm-match branches print that same refusal. The log records neither the offending PID/TID nor its state or matching branch. Consequently, even a **comm-only match is not established**, much less a particular zombie diagnosis. The shell's earlier result and the helper's refusal are mechanically compatible: they inspect different things at different times. Exact-path versus basename matching, a deleted executable, or a process appearing between scans can also produce disagreement; none is identified in the saved evidence.

Linux process states explain several distinct possibilities, not a finding about which occurred:

* An unreaped zombie can retain `comm` after losing its executable memory mapping. Its executable link can be unavailable while its task name still causes refusal. A zombie alone does not execute userspace or retain the UART descriptor table it had while alive.
* An exited thread-group leader is not proof that the whole process has finished. Its `/proc/PID/exe` can be unavailable while other threads remain. A surviving thread can still execute code or own descriptors, and the helper intentionally checks it separately.
* A still-running or exiting loader task could therefore be a genuine remaining owner or producer. An executable-only leader scan is not enough to rule it out. Signal delivery and a FIFO write do not establish completion of exit.
* `comm` is a per-task, mutable name, inherited when tasks are created; it is not an executable identity or an ownership record. A matching inherited or explicitly set name need not prove current loader code is running. Conversely, dismissing that name without examining the task could hide a real remaining thread. Ordinary `exec` updates the name; inheritance is not evidence that an unrelated executable automatically keeps it.

WatchDoge's [reload implementation](../../../analysis/re/evidence/WatchDoge/selected.json) sends signal 9 to a positive tracked matching PID and clears that stored PID without waiting or accounting for descendants. That explains why exclusion handling does not itself prove every task has gone. It does **not** identify the state encountered by this attempt. Reboot ended the historical process namespace; reused post-boot PIDs, especially 448, cannot answer that question now.

## Preserve the refusal; record the missing observation

The observed refusal is real, but the process state needed to reproduce a defect is missing. No zombie bypass, wait policy, owner-check relaxation or service-control fix is justified. The helper still refuses every match and every inspection failure it refused before.

The only code change adds a refusal diagnostic: the enumerated process PID, task TID, a best-effort state character from that already-open task directory's `stat`, and whether `exe` or `comm` matched. State `?` means the diagnostic read could not supply a state. It never converts refusal into success, including when the task disappears during the diagnostic read. The state read follows the match and is not an atomic snapshot. It opens no device node, loads no vendor library and adds no CLI, mode or framework. All function names remain shorter than 30 characters.

The smallest missing observation is the **matched PID/TID, match reason and contemporaneous task state**. To distinguish a lone zombie from an exited leader with live siblings, a separately authorized observation would also need the same process's task list and sibling states, executable-link result and UART-descriptor ownership, tied to that boot and process start time. A state of `Z` on one task alone would not justify weakening the full gate. The diagnostic is preparation for evidence, not a reproduction or authorization to deploy or invoke the helper again. The saved-sysroot ARM cross-build completed locally; its output was not executed or uploaded. No tests, suites, validators, replay, emulator or agents were run.

## The exclusion timestamp has no established writer

The original tar header records 19 bytes, owner/group `0:0`, mode `0644`, and modification time **October 20, 2026, 07:43:19 UTC**. The saved recovery script extracts that archive into a private directory, compares the bytes, renames the extracted file onto the active path, compares again, syncs and requests reboot. It does not deliberately set a new modification time. Its completion marker confirms that path was reached; it is not a pre-reboot timestamp observation.

The saved post-boot listing at **October 21, 2026, 05:12:15 UTC** shows the original bytes, owner/group and mode, but an mtime displayed only to the minute as **05:09**, near startup. A rewrite of identical content can change mtime without changing its hash, owner or mode. However, no saved observation shows when the timestamp changed or which process did it. The minute-resolution listing is not proof of a particular startup writer or of failed restoration.

The exact previously fetched Valetudo source is local at `/tmp/map-status-source.JJMaii`: `package.json` reports **2026.05.0**, and its saved archive root is `Hypfer-Valetudo-4a56bfe`, consistent with the recorded deployed commit **`4a56bfe876c1f9b298fc5a1b3c8b213ad749ffa1`**. The older `~/dev/co/Valetudo` was not used. Bounded searches of this revision's `backend/lib` found no `exclude_process`, `rriot` or `WatchDoge` references. `Valetudo.js:78` calls `robot.startup()`; `robots/roborock/RoborockValetudoRobot.js:520–540` calls its superclass and, when embedded, reads/logs firmware and kernel-command-line information. The superclass `robots/MiioValetudoRobot.js:497–502` logs transport identity; it does not write exclusions. No startup exclusion rewrite was substantiated in this source. No source download was needed.

WatchDoge does have a proven writer: [the IPC handler](../../../analysis/re/decompiled/WatchDoge/0x0001e7a8.c) calls [WdogWriteExclusions](../../../analysis/re/evidence/WatchDoge/selected.json), which opens the file with `"w"`, writes the payload and closes it. That explains the maintenance-content write **before recovery**, not the later original-content timestamp by itself. [Ordinary WatchDoge startup and event 8](../../../analysis/re/decompiled/WatchDoge/0x000142e4.c) call the input-only reload routine; startup then refreshes/stops/starts tracked hosts. Reloading is not rewriting the file. The saved `/etc/rc.local`, `analysis/reserve-root.sh`, inittab and vendor `provision.sh`/`pipes.sh` provide no exclusion writer. In particular, the reserve launcher starts Valetudo but does not write exclusions. Its unrelated Wi-Fi/log actions are not a timestamp explanation.

Thus the changed mtime remains **unestablished**, not attributed to Valetudo. There is no source basis here for asserting that startup automatically replaces maintenance exclusions, nor for treating durable exclusions as a sufficient persistent maintenance-boot gate. If a startup writer is later demonstrated, it could erase that gate; a disk rewrite alone would not prove when WatchDoge's in-memory exclusions change. Even without such a writer, an unsupervised Valetudo relaunch restores a command producer and invalidates the assumed Valetudo-off interval. Do not relaunch it during maintenance or rerun the reserve script as a shortcut.

**The exact next safe action is to leave the robot running normally and retain these local records.** Any future maintenance proposal needs a new authorization and evidence identifying the refusing task before a behavioral fix. Any future timestamp observation needs a pre-reboot restored-file timestamp and a post-startup timestamp with writer evidence; neither warrants another boot or remote attempt under this task.
