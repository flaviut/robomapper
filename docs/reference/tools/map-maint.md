# Native map-maintenance helper

The helper sends WatchDoge exclusion content through the private IPC API or requests MCU heartbeat hold-off through `rua_keep_mcu_heartbeat(-1)`. Both operations ran during the successful [stopped backup](../../guides/stopped-backup.md); the robot then returned through normal reboot. Neither operation starts automatically.

The source is [tools/map-maint/map-maint.c](../../../tools/map-maint/map-maint.c). Its two operation functions, `send_exclusions` and `disable_mcu`, keep library loading and vendor calls out of the argument and input handling. [Service control](../services/exclusion-ipc.md#minimal-one-shot-helper-contract) supplies the IPC contract; [heartbeat control](../services/heartbeat.md#supported-userspace-call-without-stopping-watchdoge) supplies the UART API. The later [A14 investigation](../services/a14-heartbeat.md) establishes the matching variant's sentinel branch and explains why an acknowledgment is not semantic confirmation.

## What the commands mean

These commands are interfaces, not a complete maintenance sequence. Preserve the original exclusions and arm independent recovery before stopping services:

```text
map-maint --help
map-maint exclusions ORIGINAL_FILE CONTENT_FILE
map-maint mcu-disable
```

No arguments prints help and returns 1; `--help` returns 0. Unknown operations or wrong argument counts return 1. These paths do not load vendor libraries, inspect UART metadata or open device nodes. Explicit operations require root and a process named `map-maint`. Before loading a library, the helper checks both the basename in its actual `/proc/self/cmdline` and its kernel process name. It refuses ambiguous or overlong launch paths rather than impersonating AppProxy or WatchDoge.

### Sending exclusions

First preserve the current original exclusion file independently. The helper reads that saved copy as `ORIGINAL_FILE`, and the complete intended replacement as `CONTENT_FILE`. It requires the candidate to start with the exact original bytes; any appended targets must start on a new line. It does not obtain or create the original backup itself. An empty stand-in for a previously absent original is meaningful only when that absence has actually been recorded separately. Never substitute an invented empty original to make content fit.

Both inputs must be regular files, not symlinks, with at most 63 bytes and no NUL. The candidate must exceed two bytes, because the receiver selects destructive event 9 for shorter content. The helper also refuses empty comma fields, more than three fields per line, short final tokens that the vendor parser would ignore, and a candidate containing no tokens at all. Blank lines between real tokens are accepted. The content is never truncated. If preserving the original plus all required targets exceeds the limit, this interface refuses it; choose another documented approach rather than dropping exclusions.

After those checks, the helper ignores SIGPIPE and loads the matching `libroboipc.so`. Under its unknown process name, the library constructor selects process index zero, whose channel matrix row and column contain no application channels. The helper does not call `DllInit`, `DllUninit` or `DoInitialize` itself. It opens only a private `pChannelOpen(3, 7)` handle, never installs it in `g_Channels`, and never reads its reverse descriptor. The library's own receive thread therefore has no registered application channel to drain.

The sender zeroes a 76-byte packet, uses message ID `0x07030342`, includes the terminating NUL in the message size, obtains the native sequence, and calls `pChannelWrite(handle, packet, 76, 0x800)`. Only a return of exactly 76 is reported as delivery. It closes its private handle and unloads the library without retrying an ambiguous write.

**Delivery is only a FIFO write.** It does not confirm that WatchDoge handled event 8, that processes exited, or that data reached durable storage. Handling this message can SIGKILL supervised hosts and overwrite their persistent exclusion file. Preserve the original copy and keep the separate command, service and heartbeat decisions in place. Restore an originally absent or empty exclusion file on disk through the separately approved restart procedure, not through short IPC content.

### Requesting MCU hold-off

`mcu-disable` checks ownership before loading `libuart_api.so.4.0.2`, and checks again immediately before calling it. It reads device metadata for `/dev/ttyS2` and `/dev/uart_mcu`, then inspects every visible process task, including tasks with unshared descriptor tables. It rejects a remaining `rr_loader` executable or task name and any character-device descriptor whose device number matches either UART node. The task-name check permits only a positively observed zombie (`Z`) whose executable lookup failed with `ENOENT` or `ESRCH`; that task's descriptor checks and all sibling-task checks still run. An unknown state or inspection error never grants this exception. Loader refusals identify the PID, thread ID, best-effort state and matching rule. Matching device numbers also catches aliases and open descriptors to a removed node. Permission errors, incomplete directory reads or other inspection failures cause refusal; processes and descriptors that disappear during inspection are skipped.

The helper never opens UART directly and sends no raw ioctls or packets. Only after the checks does it call `rua_keep_mcu_heartbeat(-1)` once. The existing vendor API supplies initialization, its nonblocking exclusive TTY lock, framing, its own retries, the acknowledged exchange and temporary ownership cleanup. A nonzero API result produces exit 1 and a message telling the operator not to begin file maintenance. The helper adds no retries, service actions or signal handling for WatchDoge.

A successful call prints:

```text
MCU hold-off request acknowledged. The transport reply does not confirm the sentinel was stored.
Keep the loader absent; normal chassis startup replaces this request.
```

That distinction matters on A14.G1. The library accepts a sequence-matched `0xd1` reply. The MCU queues that reply while handling the `0xd0` transport envelope, **before** the following `0xd3` callback stores the sentinel. The traced callback stores `-1`, and its heartbeat-loss consumer returns before counting or escalation for that value, but return 0 does not read it back or prove an offline interval survived. The runtime build-label correspondence and the complete A14 branch are explained in [A14 heartbeat findings](../services/a14-heartbeat.md).

Process inspection is not an atomic ownership reservation. An independently restarted loader or another UART user could appear after a scan; the library lock is an additional check, not a command gate. Keep the actual producers stopped through the separately approved procedure. UART initialization changes termios and receive state and can discard pending traffic; the inspected userspace path contains no flash, reset or motor command, but the kernel driver's internal effects were not reconstructed.

There is deliberately no re-enable command. `rua_keep_mcu_heartbeat(0)` sends 60, not raw zero. Ordinary chassis startup supplies raw-zero heartbeats; an MCU reset also loses the sentinel. Neither behavior is invoked by this helper, and no hold-off is assumed to survive a restart.

## Build and runtime identity

The deployed binary was 21,500 bytes, SHA256 `fb75e397eb09c51aa1a0402918fe55c357363be5843e6e7f896e6b7d7d8987f0`. See [cross-building and ELF inspection](../../guides/build-map-maint.md) for the pinned toolchain, development-package hash, runtime linkage and historical build identities. The build recipe does not deploy or execute the helper.

## Runtime limits

Target startup, the dependency search path, exclusion delivery and native return 0 were observed during the [completed stopped backup](../../guides/stopped-backup.md). No map file was edited or restored. There is still no semantic sentinel readback or demonstrated independent rescue connection. A successful backup does not make arbitrary map replacement safe or remove the need for fresh status, ownership checks and independent recovery on another run.
