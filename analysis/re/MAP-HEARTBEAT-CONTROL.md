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

Further concrete heartbeat and duration findings belong below as their code paths are resolved. No safe duration is inferred from the literal `120`.
