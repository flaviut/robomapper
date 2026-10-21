# Keep the MCU heartbeat alive during map maintenance

Stopping `rr_loader` also removes its chassis plugin, not just navigation and SLAM. Keep WatchDoge running: its Linux watchdog feeder is separate from this MCU link. The useful alternative is a loader that retains chassis while omitting the map plugins, if its dependencies and invocation can be bounded. A finite MCU hold-off is a second option, not yet a duration guarantee.

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

[Offline workflow](OFFLINE-MAP-WORKFLOW.md) and source-root `analysis/SUPERVISION.md` trace WatchDoge's independent `/dev/watchdog` feed thread: requested timeout 16, feed every eight seconds. Leave that process running. Its exclusion SIGKILL path does not first call `rua_keep_mcu_heartbeat(120)`; its normal all-process-stop path does. Do not substitute either signal handling or an empty exclusion payload for a maintenance command.

## Chassis initialization, sending and finalization

The configuration reader at chassis Thumb `0x4de0`, called by constructor `0x101cc`, loads `open_heart_beat` and the two MCU timing fields. In the constructed driver these become byte `+0x40`, receive timeout `+0x44`, and send period `+0x48`. Missing fields default to false, 10000 and 1000 respectively. Initialization `0xbe10` opens UART with `init_uart`, checks MCU mode, starts worker threads and installs a timer callback. When `+0x40` is true it calls `0xbde4`, which passes `+0x48` to the timer interval setter `0x554c`.

The installed callback is Thumb `0xf7b4` (stored Thumb-tagged `0xf7b5` in the callback binding at `0xc004`). Its `0xf7d0–0xf7e6` instructions send **command `0xd3`, four zero bytes, flag 0** through `sent_cmd`. This differs from `rua_keep_mcu_heartbeat(0)`, whose wrapper substitutes 60. Thus normal heartbeat comes from the chassis plugin in `rr_loader`; keeping WatchDoge's Linux feed thread alive does not replace it.

There is also a useful vendor cleanup path absent from SIGKILL: plugin callback table VA `0x2929c` has final slot `+0x14 = 0x80ad`. The Thumb `0x80ac` wrapper calls `0x7f04`; that function sends **`sent_cmd(0xd3, 4, &120, 0)` at `0x7f28–0x7f3a` before stopping/joining workers and closing UART**. This is independent of WatchDoge's normal-stop call. Loader graceful finalization can therefore establish a finite hold-off itself, if it actually reaches chassis finalization. The loader first joins its timer and finalizes plugins in reverse order; do not equate delivering SIGHUP with reaching this send.

The baseline importer did not recognize several address-taken Thumb functions as function entries (`0x106b0`, `0x6488`, `0xefd0`, `0xf7b4`). One focused export rejected `0x106b0`; no annotation committed. Those edges were read directly from original instructions and callback-table words using LLVM objdump in Thumb mode, not inferred from nonexistent decompiler output.

## Why the packaged image does not settle applicability

WatchDoge `0x16b34` reads the named text file and passes its contents to `upgrade_mcu_if_not_match`. In `libuart_api.so.4.0.2:0xa4c0`, that function first calls `upgrade_mcu_normal`; result `-20` selects a fallback that obtains MCU identification (`0x7b1c`), calls `find_match_jtagId_firmware`, then uses the selected image. Therefore `MCU_FIRMWARE_MATCH` is a first choice, not a hardware identifier. The exact missing saved input is the running MCU's identification/architecture (including the JTAG-selection discriminator), not merely Linux firmware build 1612.
