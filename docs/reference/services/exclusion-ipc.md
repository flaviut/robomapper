# WatchDoge exclusion IPC

The [native helper](../tools/map-maint.md) implements this firmware-specific interface. A successful write is delivery to a FIFO, not an exit or flush acknowledgment. The [supervision reference](supervision.md) owns parser behavior, destructive short-content handling and restart rules.

## Sending exclusions: existing native API, not miio JSON

The available Valetudo checkout (`/home/user/dev/co/Valetudo`, commit `5d905ec2239dd14bbc11ee3785837562306a508e`) sends Roborock commands through `MiioValetudoRobot.js` and `miio/MiioSocket.js`, using encrypted UDP miio. `RoborockBasicControlCapability.stop()` sends `app_stop`: that stops cleaning, not the application processes. It is not a WatchDoge IPC sender. The saved native `miio_send_line` advertises `Usage: %s msg` and sends a string to a local server; it does not link `libroboipc` or provide the exclusion interface. No generic preinstalled exclusion command was found in the saved rootfs. Do not substitute either tool for the native IPC API.

The native library **does** provide enough framing and lifecycle to specify a small one-shot sender without guessing socket packets. `libroboipc.so` SHA256 is `a7a693c8edd37aa9367f680d2f742ef81f4b8007c97a7720fc02f35ded57a832`. Its `Packet_t` wire representation on this ARM little-endian firmware is 76 bytes:

| Offset | Size | Exclusion request value |
| --- | --- | --- |
| 0 | 4 | Message ID `0x07030342` (destination WatchDog=7, source AppProxy=3) |
| 4 | 4 | Sequence, assigned by native `GetNextSequenceNumber` |
| 8 | 4 | Message size: payload byte count including terminating NUL |
| 12 | 64 | NUL-terminated exclusion file content, remaining bytes zero |

`SendPacket:0x63ec` gets a sequence, forces nonblocking option bit 0, and calls `pDoSendPacket:0x637c`, which writes **all 0x4c bytes**, not just MessageSize. Channel selection is `g_Channels[((id>>16)&255)*17+(id>>24)]`. WatchDoge's `RecvPacket` stack buffer is also 0x4c bytes; it treats the data at +12 as a C string, ignoring MessageSize for file write and event selection. **Keep content at most 63 bytes, with no embedded NUL, and length greater than two.** `SendPacketEx` adds completion/echo machinery; it is not a way to send an arbitrary-sized exclusion file to this receiver.

### Minimal one-shot helper contract

This is the static API contract implemented by [map-maint](../tools/map-maint.md), not an operational stop sequence:

1. Run with a unique basename/argv[0], `map-maint` for this helper, which matches none of `GetProcIndex:0x5530`'s known prefixes. Link/load the matching `libroboipc.so` normally. Its `.init_array` entry at VA `0x1bec8` invokes `DllInit:0x3324`; **do not invoke DllInit again**. It creates the sequence mutex and receive thread. For the unknown name, `DoInitialize` resolves process index 0; the pinned process matrix row and column 0 contain only −1, so no application channels are opened.
2. Call `pChannelOpen(AppProxy=3, WatchDog=7)`, exported as `_Z12pChannelOpen16ProcessAbbrIndexS_`. The pinned matrix has both `[3][7]=1` and `[7][3]=1`. `pChannelOpen:0x5e14` opens existing `/tmp/ApWd` write-only/nonblocking and `/tmp/WdAp` read-only/nonblocking. The saved vendor `opt/rockrobo/scripts/pipes.sh` creates both FIFOs. It does not create or unlink them in this library call. Null is failure; a nonnull handle can still have failed descriptor opens, so send must be checked.
3. **Keep that handle private; do not register it in `g_Channels` and do not call `DoInitialize("AppProxy")`.** The latter would open all AppProxy channels and let this helper's receiver compete with the real AppProxy for its messages. A private handle's reverse read descriptor is never read; merely opening it does not consume another process's reply. The helper's receive thread sees no registered channels from row 0.
4. Prepare the zeroed 76-byte packet above. Call `_Z21GetNextSequenceNumberP8Packet_t` (`0x5a94`) with its address, then `_Z13pChannelWritePvS_ji` (`0x5adc`) as `pChannelWrite(handle, &packet, 76, 0x800)`. Ignore SIGPIPE in the helper so loss of the reader is an error rather than an uncontrolled termination. Require return **76**, not merely nonnegative. This uses the same native channel-write primitive as SendPacket without installing a new consumer for live application traffic. Do not retry blindly after an ambiguous result.
5. Call `_Z13pChannelClosePv` (`0x6110`) on that handle, then exit normally. Close releases local descriptors and allocation, not the FIFO pathname. The library's `.fini_array` entry at VA `0x1bed0` invokes `DllUninit:0x2f64`, cancels/joins its own receive thread and tears down its local state. Do not call DllUninit twice.

This closes channel coexistence at the static API level: no second AppProxy process name, no registration/read of its channels, and no FIFO deletion. The 76-byte FIFO write is one native packet, but a successful write still means only delivery to the pipe. It neither waits for event 8 nor establishes host exit. Local sequence numbers can overlap another sender's numbers; this path requests no echo/completion and does not consume replies. Actual library/ABI/FIFO availability must still be checked for each deployment; the helper was used during the demonstrated backup.

For the captured original exclusions `rriot_tuya,rriot_rr`, adding `\nrr_loader\nRoboController\nAppProxy\n` remains below the cap (a pre-existing trailing newline also fits). Add any further command-producer exclusions only if the complete content still fits. **Do not truncate the original file or shorten tokens blindly to make it fit.** When the original plus required targets exceeds 63 bytes, the [untested maintenance-boot alternative](supervision.md#live-entry-and-untested-maintenance-boot-alternative) avoids the IPC payload limit but adds boot and heartbeat dependencies.

Provenance: native `SendPacket`/`pDoSendPacket` are already [exported in the flow evidence](../../../analysis/re/evidence/restore/flow/c/libroboipc.so/0x000063ec.c). Constructor, index lookup, channel open/write/close, sequence and destructor were exported by a focused import of the tracked library into the same private baseline copy under `/tmp`; source-root tooling and shared evidence were not changed. Native data matrix is VA `0x1c5bc` (file `0xc5bc`); abbreviation table VA `0x1c48c` (file `0xc48c`) maps indices 3/7 to `Ap`/`Wd`. No internet source searches were used.
