# Keep the MCU heartbeat alive during map maintenance

**The concrete candidate maintenance mechanism is the existing UART API `rua_keep_mcu_heartbeat(-1)`, after the old loader has exited, while WatchDoge stays alive.** It requests an acknowledged disable of MCU missing-heartbeat supervision. The inspected chassis MCU candidate leaves `-1` unchanged and skips its heartbeat-loss handling indefinitely; all six packaged chassis candidates have the same `0`/`-1` conversion rule. This is conditional on the installed MCU accepting that protocol, not observed device behavior. No installed safe one-shot shell command for invoking the API was identified.

Stopping `rr_loader` removes chassis as well as navigation and SLAM. Its normal finalizer sends a finite hold-off of 120, but SIGKILL bypasses it. Do not call disable while the normal chassis callback still runs: its next zero-valued heartbeat replaces that state. Leaving WatchDoge alive preserves only the separate Linux watchdog feeder.

This is static inspection of saved `4.3.5_1612`, not a device procedure. No firmware was executed and no device was accessed. Source-root paths below mean `/home/user/tmp/illegalplainape`; only this document is changed.

## Confirmed configuration

The embedded loader configuration sets these chassis fields:

| Field | Value |
| --- | ---: |
| `open_heart_beat` | `true` |
| `heart_beat_period_to_mcu` | `1000` |
| `heart_beat_timeout_from_mcu` | `10000` |
| `heart_beat_timeout_to_slam` | `1000` |

These are decoded defaults, not active-device observations. The configuration decoder in [writer-host/config_data.py](evidence/restore/writer-host/config_data.py) was used only to inspect saved configuration data through its existing host-native OpenSSL path. No keys or unrelated configuration are published. [Writer-host findings](evidence/restore/writer-host/README.md) establish that the saved normal argv is `rr_loader -d` and that `-c FILE` can override its embedded configuration. Chassis, SLAM and navigation normally share this process.

`librr_plugin_chassis.so` has SHA256 `aa6091221e16f0c32456539c025361d78b698b5522258d4f2d6af0e162ed67c0`; its `rr_load_plugin` entry is Thumb VA `0xddd4`. A private copy of the closed baseline was made with source-root `analysis/re/tooling/retool.py copy`, then this library was imported into that private `/tmp` project. The shared baseline was not opened.

## Which MCU image is named by the saved firmware package?

Despite their executable-looking names, `firmware/bin/MCU_FIRMWARE_MATCH` and `MCU_FIRMWARE_SCAN_FOLDER` are **text files**, not matching executables. The former contains exactly:

```text
/opt/rockrobo/firmware/img/RR_TANOSS_MP_STM32.A3.G1_M4.0.2_RELEASE_20221102-212320_FULL.bin
```

The latter contains `/opt/rockrobo/firmware/img/`. This identifies a packaged preferred image, not proof that A3.G1 is installed. A14, A3.G3 and INV images coexist; carpet images are separate. Saved `etc/rr-info` says `A.01.0057-V1612`; `build.txt` identifies build 1612 and its packaging date, not MCU architecture. Saved `robot-state.json` contains map/state attributes but no MCU architecture field. Selecting an active image still needs the updater's selection rule or an allowlisted MCU architecture/version observation.

## What not to stop

The [offline workflow](OFFLINE-MAP-WORKFLOW.md) and [service-control reference](MAP-SERVICE-CONTROL.md) trace WatchDoge's independent `/dev/watchdog` feed thread: requested timeout 16, feed every eight seconds. Leave that process running. Its exclusion SIGKILL path does not first call `rua_keep_mcu_heartbeat(120)`; its normal all-process-stop path does. Do not substitute either signal handling or an empty exclusion payload for a maintenance command.

## Chassis initialization, sending and finalization

The configuration reader at chassis Thumb `0x4de0`, called by constructor `0x101cc`, loads `open_heart_beat` and the two MCU timing fields. In the constructed driver these become byte `+0x40`, receive timeout `+0x44`, and send period `+0x48`. Missing fields default to false, 10000 and 1000 respectively. Initialization `0xbe10` opens UART with `init_uart`, checks MCU mode, starts worker threads and installs a timer callback. When `+0x40` is true it calls `0xbde4`, which passes `+0x48` to the timer interval setter `0x554c`.

The installed callback is Thumb `0xf7b4` (stored Thumb-tagged `0xf7b5` in the callback binding at `0xc004`). Its `0xf7d0–0xf7e6` instructions send **command `0xd3`, four zero bytes, flag 0** through `sent_cmd`. This differs from `rua_keep_mcu_heartbeat(0)`, whose wrapper substitutes 60. Thus normal heartbeat comes from the chassis plugin in `rr_loader`; keeping WatchDoge's Linux feed thread alive does not replace it.

There is also a useful vendor cleanup path absent from SIGKILL: plugin callback table VA `0x2929c` has final slot `+0x14 = 0x80ad`. The Thumb `0x80ac` wrapper calls `0x7f04`; that function sends **`sent_cmd(0xd3, 4, &120, 0)` at `0x7f28–0x7f3a` before stopping/joining workers and closing UART**. This is independent of WatchDoge's normal-stop call. Loader graceful finalization can therefore establish a finite hold-off itself, if it actually reaches chassis finalization. The loader first joins its timer and finalizes plugins in reverse order; do not equate delivering SIGHUP with reaching this send.

The baseline importer did not recognize several address-taken Thumb functions as function entries (`0x106b0`, `0x6488`, `0xefd0`, `0xf7b4`). One focused export rejected `0x106b0`; no annotation committed. Those edges were read directly from original instructions and callback-table words using LLVM objdump in Thumb mode, not inferred from nonexistent decompiler output.

## Why the packaged image does not settle applicability

WatchDoge `0x16b34` reads the named text file and passes its contents to `upgrade_mcu_if_not_match`. In `libuart_api.so.4.0.2:0xa4c0`, that function first calls `upgrade_mcu_normal`; result `-20` selects a fallback that obtains MCU identification (`0x7b1c`), calls `find_match_jtagId_firmware`, then uses the selected image. Therefore `MCU_FIRMWARE_MATCH` is a first choice, not a hardware identifier. The exact missing saved input is the running MCU's identification/architecture **and gyro ID**, not merely Linux firmware build 1612. `upgrade_mcu_normal:0xa2e4` reads those using `get_mcuId_gyroId_from_mcuUart`, converts MCU ID with `McuId_To_JtagId`, compares the image's JTAG and gyro IDs, and otherwise calls `find_match_jtagId_gyroId_firmware:0x99b0`. The fallback scanner `find_match_jtagId_firmware:0x970c` handles older identification. No active image is selected here.

## What `0xd3`, 120 and −1 actually do

Focused Thumb disassembly used the packaged A3.G1 image named above (SHA256 `5f5ec6256deef76f60b2acd3890aa6c02186a5e3c586af758c9f55b72be5decd`). Its boot vector is at file offset 0, application vector at `0x8800`, with VTOR set to `0x08008800` at `0x0802a196`. MCU addresses in this section are flash VAs: `0x08000000 + file offset`. Linux shared-library addresses elsewhere are ELF VAs, not MCU addresses.

The receive-handler candidate at **`0x0801335a`** checks length 4, copies the payload into RAM `0x20008c70`, and logs `Rx heartbeat … interval 0x%xs` (`0x080137ec`/`0x08013814`). At `0x080133a8–0x080133c6`, it leaves zero and `0xffffffff` unchanged; other values are unsigned-clamped below `0x01000000`, then multiplied by 100. Thus 120 becomes **12,000 countdown dispatches**, while −1 remains a sentinel, not a very large finite interval.

The consumer **`0x0801324c`** returns immediately for −1 and for MCU system mode 8. Otherwise a positive hold-off is decremented only when called with argument 1 (`0x0801331e–0x08013324`). At zero it runs missing-traffic handling: argument 0 clears the missing-traffic counter, while argument 1 can advance it. The command-dispatch loop calls this consumer with 0 after invoking a registered command callback (`0x08011aea–0x08011aee`). Timer event `0x6a` calls it with 1 (`0x08011be0 -> 0x0801dc60 -> 0x0801dc8a`). This means ordinary received commands can also clear the loss counter **when hold-off is zero**; the condition is not exclusively absence of opcode `0xd3`.

Event `0x6a` is posted every ten invocations of `0x0802a208` (`0x0802a230–0x0802a25c`), called from TIM6 IRQ at `0x08032040`. Thus 120 defers the consumer for **12,000 processed event-`0x6a` dispatches**, originating from 120,000 TIM6 interrupts if no events are lost. The handler's diagnostic labels the incoming argument in seconds, consistent with an intended 1 ms interrupt/10 ms event. **That diagnostic is not a wall-clock proof or a 120-second maintenance guarantee.** The record starting at `0x08032b84` names TIM6 and contains adjacent halfwords 99/719, but its complete initialization-to-clock path was not joined; no exact wall-clock budget is assigned here. Installed image, hardware clock and interrupt/task delivery have not been observed. The indefinite sentinel path avoids needing this remaining timing edge; do not budget extra missing-traffic escalation after a finite request expires.

The reset concern is concrete: in ordinary low-numbered modes, missing-traffic counter 6500 reaches `0x08013298–0x080132a2`, delays and branches to **`0x08023194`**, which masks faults and writes `0x05fa0004` to SCB AIRCR `0xe000ed0c`, then loops. That requests an MCU system reset. Higher-numbered modes take other escalation branches. The `-1` sentinel returns before both counting and mode-dependent escalation in this consumer; it does not disable unrelated MCU protections.

Only bounded handler comparisons were made across the other packaged chassis images. Their receive-handler entries are:

| Candidate | Thumb receive entry | Special-value/conversion block |
| --- | --- | --- |
| A14.G1 M4.0.1 | `0x08013442` | `0x08013490` |
| A14.G3 M4.0.1 | `0x08013256` | `0x080132a4` |
| A14 INV M4.0.1 | `0x0801317e` | `0x080131cc` |
| A3.G1 M4.0.2 | `0x0801335a` | `0x080133a8` |
| A3.G3 M4.0.2 | `0x0801316e` | `0x080131bc` |
| A3 INV M4.0.2 | `0x0801308a` | `0x080130d8` |

All six have identical original instruction bytes for the length-check prologue and the complete zero/−1/clamp/multiply block. That closes the conversion ambiguity across the package, **not active-image identity or every candidate's complete reset state machine**. Carpet binaries are not chassis heartbeat substitutes and were excluded. The receive role is supported by the adjacent heartbeat diagnostics and matching userspace protocol; a full reconstruction of the MCU's initialized registration table was not undertaken.

## Supported userspace call, without stopping WatchDoge

`libuart_api.so.4.0.2` SHA256 is `914317e600a73255cb6523e987ab3ab99b5168c47026503fcb3fe797f9961529`. The exported **`rua_keep_mcu_heartbeat:0x11564`** does more than the chassis finalizer's unacknowledged send:

1. Check whether this process has initialized UART. If not, call `init_uart:0x5e64`; return its error on failure.
2. Replace argument 0 with 60; preserve every other value, including −1.
3. Call `sent_cmd_sigle_thread(0xd3, 4, &value, 1)`, trying up to three times with 20 ms pauses on failure. Return 0 after nonnegative send/ack result, otherwise the error.
4. Close UART if this call opened it; otherwise leave the existing owner intact.

`disable_mcu_heartbeat:0x11690` is just the wrapper passing −1. Prefer the named integer-argument API when documenting the return contract; do not invent an argument for the no-argument wrapper. In native C ABI terms the one-shot request is **`int result = rua_keep_mcu_heartbeat(-1);`**; proceed only on `result == 0`. The misspelling `sent_cmd_sigle_thread` is the library's exported spelling.

Transport is not raw `echo` into a serial device. `sent_cmd:0x10a9c` adds command/length bytes; `sent_package:0x1084c` adds sequence/framing/checksum and distinguishes acknowledged from unacknowledged sends. `rua_uart_init:0x7144` opens/configures the TTY, obtains `flock(fd, LOCK_EX | LOCK_NB)`, opens the companion UART driver, performs its ioctl/mmap setup and clears the receive buffer. `init_uart` supplies `/dev/ttyS2`, `/dev/uart_mcu`, baud 1152000 and driver parameters. These initialization side effects and the exclusive lock are reasons **not** to inject a second owner while chassis is alive. The wrapper supports a temporary owner after chassis has closed/exited, rather than requiring a permanent replacement heartbeat daemon.

The saved `firmware/uart_test-4.0.2-20221102` advertises an interactive `b` heartbeat toggle among factory controls. That is not a grounded standalone maintenance command: its broader startup/shutdown effects were not bounded, so it is not recommended. No saved target Python installation or safe installed one-shot CLI was established. A target-native caller of the exported API is therefore an explicit missing invocation component, not a shell command claimed to exist.

## Candidate maintenance boundary

This lane excludes map-file selection and edits. The host-control lane owns exclusions and process commands. Its finding that the public loader stop method does not provide a separate map-only shutdown rules out simply stopping nav/SLAM while leaving this **same** chassis instance alive. A new chassis-only loader configuration would be a different deployment requiring dependency/configuration work; it is not the recommended shortcut.

Use the following heartbeat prerequisite with the whole-host offline path:

1. Leave WatchDoge and its Linux feeder running. Prevent new robot commands and arrange application supervision so the stopped loader will not respawn. Do not stop WatchDoge to obtain UART ownership.
2. Prefer a graceful loader exit when reachable; its chassis finalizer requests finite hold-off 120. Confirm the host has actually exited. SIGHUP is a quit request, not an acknowledgment of finalization. Exclusion SIGKILL alone supplies **no** hold-off.
3. After the old UART owner is gone, invoke `rua_keep_mcu_heartbeat(-1)` from the target-native caller and require return 0 **before entering the copying/replacement window**. Abort replacement on init/lock/send failure. Do not count time from signal delivery or assume the finalizer's request arrived; its send is unacknowledged.
4. Keep the loader absent and WatchDoge alive for the offline work. Conditional on the matching −1 MCU behavior above, heartbeat supervision imposes **no finite duration** until a later `0xd3` request or MCU reset changes it. This is not a guarantee about power, other watchdogs or arbitrary MCU modes.
5. Finish storage work before restarting consumers or rebooting. The normal chassis callback's next raw-zero heartbeat returns the MCU consumer to ordinary traffic supervision. `rua_keep_mcu_heartbeat(0)` is **not** an explicit re-enable-to-zero operation: it sends 60. A real MCU reset also loses the RAM sentinel; a Linux-only reboot need not reset the MCU. Do not carry either assumption silently across reboot.

**Boot with disk exclusions alone is not an indefinite rescue window.** WatchDoge startup temporarily initializes UART for MCU checks and later closes it (`WdogMain:0x142e4`, close before process startup); the regular zero-valued heartbeat producer is still the absent chassis plugin. No startup −1 request or persistent heartbeat exemption is established by editing exclusions. If maintenance occurs after a new boot, its gate must run the acknowledged −1 request on that boot before relying on an unbounded service-off window. Otherwise finish replacement before reboot and return to normal startup rather than booting into a chassis-free system for extended editing.

The remaining input is bounded: an allowlisted installed MCU ID/JTAG, gyro ID and version (or confirmation that its relevant handler matches a packaged candidate), plus a target-native invocation route for the documented API. Return 0 is transport acknowledgment, not observation that a robot survives the window. No live behavior is promised here; no firmware execution, service changes, tests, suites, validators or new evidence infrastructure were performed. All extractions and focused Ghidra work stayed in `/tmp/map-heartbeat`; only this document is committed.
