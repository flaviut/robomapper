# Current robot status before map maintenance

**Do not stop the map services from this snapshot.** Valetudo reported **idle, 96% battery, discharging**, not docked or charging. There were no Valetudo schedules, but the vendor schedule file could not be interpreted within this read-only inspection. Valetudo's updater was idle; vendor firmware-update inactivity remains unconfirmed. These are reasons to leave the robot running, not to send a docking or status-refresh command.

The observations below were made on **October 21, 2026, 04:34–04:39 UTC**. The useful status events arrived during a passive subscription from **04:37:22 to 04:38:32 UTC**. This snapshot expires: check readiness again immediately before any later stop. Nothing here authorizes stopping services, opening UART or replacing map files.

## What the robot reported

| Question | Observation | What it establishes |
| --- | --- | --- |
| Docked and stationary? | Status `idle`, flag `none`, in two attribute events | No cleaning or movement state was reported. Docking was not reported; physical stillness was not independently measured. |
| Battery and charge state? | Level `96`, flag `discharging`, in both events | Valetudo did not report charging. The flag comes from its interpretation of robot status, not a separate charger measurement. |
| Idle and not cleaning? | `idle`, without a resumable flag | This was the reported state during the subscription, not a promise about the next command. |
| Valetudo schedules? | `GET /api/v2/timers/` returned zero timers, including zero enabled timers | No Valetudo timer was imminent in that configuration. External automation and vendor timers are separate. |
| Other schedules? | `apptimer.cfg` was a 159-byte regular file, mode `0644`, owner `0:0`; it was not plain JSON. `servertimer.cfg` was empty. | Enabled vendor schedules and their next execution time remain unknown. No decoder or vendor query was run. |
| Updating? | Cached Valetudo updater state was `ValetudoUpdaterIdleState`, `busy=false`; no `SysUpdate` process was present | Valetudo was not reporting its own update in progress. This does not establish that vendor firmware updating is inactive. |
| Other command sources? | MQTT was enabled; `miio_client` was running. Neither rriot bridge was present. | Zero Valetudo timers does not close remote command paths. |

No `crond` executable was found in the process inventory. The usual system crontab, cron interval directories and the three inspected cron spool/config directories were absent. That limited observation does not account for remote MQTT automation or vendor controller timers.

### The status reads did not request a refresh

The supplied Valetudo checkout was **2026.02.0**, so it was not used as the authority for the deployed routes. The public **2026.05.0** source was obtained with `gh` into a private directory under `/tmp`, at commit **`4a56bfe876c1f9b298fc5a1b3c8b213ad749ffa1`**. The live cached version endpoint returned that same release and commit.

At that revision, `backend/lib/webserver/RobotRouter.js` makes ordinary `/state` and `/state/attributes` GETs call `pollState()`. `RoborockValetudoRobot.pollState()` sends `get_status`; those routes are **not cached reads** and were not called. Instead, `/api/v2/robot/state/attributes/sse` subscribes to existing attribute events without requesting robot activity. Two events arrived during a bounded 70-second read. No full-state or map endpoint was read, and no requested miio/vendor RPC was sent, including `get_mcu_info`.

The version, timers and updater-state GET handlers return existing process/configuration state. The listener on port **80** was identified from Valetudo's `/proc` socket descriptors and `/proc/net/tcp`, not a port scan. An initial unauthenticated version GET received HTTP 401. After the parent approved ordinary authentication, only the source-defined HTTP-auth object was selected privately from the configured file. Credentials stayed in memory and the HTTP header, not command arguments, URLs, files, output or Git. Authenticated GETs used an SSH-forwarded loopback connection. Initial short SSE attempts closed before any event; they supplied no status evidence.

Every SSH connection used `BatchMode=yes`, `ConnectTimeout=10` and `StrictHostKeyChecking=yes`. No trust or authentication check was disabled.

## How Valetudo stops and starts here

At the final process observation, **04:39:01 UTC**, Valetudo was still **PID 371**, executable `/mnt/data/valetudo`, with no arguments and parent PID 1. Its configured file was `/mnt/data/valetudo_config.json`. The human-readable-system-ID environment variable was also set; its value is deliberately omitted here.

The live `/etc/rc.local` launches `/mnt/reserve/_root.sh`, which starts that executable once in the background with `VALETUDO_CONFIG_PATH` set. No Valetudo restart loop appeared in the complete reserve launcher, inittab or the inspected WatchDoge lists. **Do not rerun the reserve script just to restart Valetudo:** it also contains Wi-Fi-related edits and log deletion. A later restart should launch the same executable with its saved launch environment and output handling, after confirming that no instance is already running. No new service unit or config rewrite is needed.

For this exact source revision, `backend/index.js` handles **SIGTERM** by awaiting `Valetudo.shutdown()` and then exiting. A later authorized stop can therefore target the freshly identified Valetudo PID with TERM and wait for actual exit. `Valetudo.shutdown()` stops the scheduler, MQTT controller, webserver and robot sockets; its normal shutdown has a five-second forced-exit fallback. No signal was sent in this inspection.

Stopping the scheduler clears its minute-evaluation interval. It **does not cancel an already executing timer action**: `Scheduler.executeTimer()` can be awaiting pre-actions or its five-second delay. `MiioSocket.shutdown()` disconnects/closes the socket; it does not retract an already delivered command or explicitly clear every pending request timeout. Actual Valetudo exit removes its remaining JavaScript work, but not work already accepted by the vendor hosts. Later maintenance must establish idle state before stopping, then wait for process exit; TERM delivery alone is not a command-drain acknowledgment.

Version 2026.05.0 also has **Phoenix**, an internal `execve` restart path for memory pressure and applied updates. It is not an external supervisor that restarts a dead Valetudo process. It does mean PID identity alone is insufficient while Valetudo is running: recheck its executable, argv and version before a later operation. Boot launches Valetudo again regardless of a prior manual stop.

## A reversible command gate for a later maintenance window

The useful proposal is to **stop Valetudo without changing its timers or MQTT configuration, then exclude the vendor command producers together with the map hosts**. Simply killing `miio_client` would let WatchDoge restart it. Leave WatchDoge, logging, SSH and networking running. The [service-control explanation](MAP-SERVICE-CONTROL.md) covers the native sender, abrupt exclusion behavior and cold-start restoration; the [heartbeat explanation](MAP-HEARTBEAT-CONTROL.md) remains a separate requirement before relying on a loader-free interval.

The current exclusion file still matched the original **19 bytes**, `rriot_tuya,rriot_rr`, with no trailing newline. Saving its exact bytes, presence, owner and mode independently of the map backup is necessary before any later exclusion request. Save Valetudo's launch details privately as well. Do not save or rewrite the whole configuration merely to turn schedules off.

Appending all five full process names would require 76 content bytes, exceeding the native sender's 63-byte content bound. The known substring parser allows this smaller proposal, approved for documentation only:

```text
rriot_tuya,rriot_rr
rr_l
RoboC
AppP
miio
SysU
```

Keep the original 19 bytes unchanged and append `\nrr_l\nRoboC\nAppP\nmiio\nSysU\n`. That gives **46 content bytes, 47 including the terminating NUL**, within the 64-byte native field. Every new token is longer than three characters and on its own line; there are no empty comma fields. This selects event 8 rather than the destructive short-content event 9. No payload was sent.

The complete live normal list contained `rrlogd`, `rr_loader`, `RoboController`, `AppProxy`, `wlanmgr`, `SysUpdate`, `rriot_rr` and `miio_client`. Both alternate lists were also read by name only. Their common records were `rrlogd`, `rr_loader`, `AppProxy` and `wlanmgr`, with `RoboControllerR` in FR and `RoboControllerM` in MT.

| New token | Normal-list match | Alternate-list match |
| --- | --- | --- |
| `rr_l` | `rr_loader` only | `rr_loader` only, both lists |
| `RoboC` | `RoboController` only | `RoboControllerR` in FR; `RoboControllerM` in MT |
| `AppP` | `AppProxy` only | `AppProxy` only, both lists |
| `miio` | `miio_client` only | None |
| `SysU` | `SysUpdate` only | None |

None matches `rrlogd`, `wlanmgr`, WatchDoge, Dropbear, `adbd` or Valetudo. The original rriot tokens remain intact; they cover the known bridge that can independently restart AppProxy. Neither rriot bridge was running. The current ordinary controller and `miio_client` processes agree with the normal list, but this inspection did not read WatchDoge's in-memory list selection. Checking all three lists avoids assuming the shortened controller token refers only to the normal variant. Reconsider the complete mapping if the lists or restart sources change.

After readiness has been established and the other maintenance work permits a stop, the proposed order is:

1. Save the reversible launch/exclusion state privately, retain the administrative connection and hold external automation. Recheck dock/charge, idle, schedules and update state immediately before proceeding.
2. Gracefully stop the exact Valetudo instance and observe its exit. Do not edit the empty timer set or disable MQTT in persistent configuration.
3. Use the separately prepared native sender for the complete exclusion content above. This simultaneously prevents supervised restart of the map hosts, `miio_client` and `SysUpdate`. It kills tracked matching processes abruptly; it is **not a graceful map-save operation**. Observe actual exits and obtain the separately required acknowledged MCU heartbeat hold-off before file work.
4. Preserve maintenance exclusions during the whole file transaction. When the matching set is complete, restore the saved original exclusion file **on disk only**, without live reload, then use the planned controlled cold restart. Do not send empty content or re-enable missing key hosts in the live supervisor. Retain the external automation hold until normal state is observed after boot, when Valetudo will start again.

This closes the payload-size problem without requiring an extra boot merely to enter exclusions. It does not resolve the current readiness problems or establish that abrupt host exit finishes a pending save.

## Administrative access remains separate

Dropbear's listener was **PID 374**, parent PID 1, executable `/usr/sbin/dropbear`, argv `/usr/sbin/dropbear -F`. Live inittab independently respawns it; it is not launched by Valetudo or the map hosts. WatchDoge remained PID **372**. The loader, controller, AppProxy and miio client remained **448, 507, 509 and 513** respectively. These processes were not stopped or restarted.

A separate **`adbd` process, PID 373**, was also independently respawned by inittab. The existing USB gadget reported enabled with function `adb`; no USB connection or authorization was exercised, so this is an identifiable possible recovery route, not a demonstrated one. `/dev/ttyS0` existed, but the serial getty entry was commented out. No UART was opened and no serial shell was established. No pre-boot recovery connection or recovery partition was independently established by this work. Do not assume a failed boot can be repaired just because SSH currently works.

**No deliberate robot changes occurred.** No service signal, UART access, configuration or map write, boot change, reboot, cleaning, motion, cloud command or firmware operation was performed. Ordinary SSH/HTTP activity and the robot's existing background work continued. No tests, suites, validators, replay or review machinery were run. The immediate unresolved issues are the lack of a docked/charging observation, unread vendor schedule state, and unconfirmed vendor firmware-update inactivity; leave services running until those are resolved in an authorized observation window.
