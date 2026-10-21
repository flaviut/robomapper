# Native map-maintenance helper

The helper sends WatchDoge exclusion content through the private IPC API or requests MCU heartbeat hold-off through `rua_keep_mcu_heartbeat(-1)`. Both operations ran during the successful [stopped backup](MAINTENANCE-PROCEDURE.md); the robot then returned through normal reboot. Neither operation starts automatically.

The source is [tools/map-maint/map-maint.c](../../tools/map-maint/map-maint.c). Its two operation functions, `send_exclusions` and `disable_mcu`, keep library loading and vendor calls out of the argument and input handling. [Service control](MAP-SERVICE-CONTROL.md#minimal-one-shot-helper-contract) supplies the IPC contract; [heartbeat control](MAP-HEARTBEAT-CONTROL.md#supported-userspace-call-without-stopping-watchdoge) supplies the UART API. The later [A14 investigation](A14-HEARTBEAT.md) establishes the matching variant's sentinel branch and explains why an acknowledgment is not semantic confirmation.

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

Both inputs must be regular files, not symlinks, with at most 63 bytes and no NUL. The candidate must exceed two bytes, because the receiver selects destructive event 9 for shorter content. The helper also refuses empty comma fields, more than three fields per line, short final tokens that the vendor parser would ignore, and a candidate containing no tokens at all. Blank lines between real tokens are accepted. The content is never truncated. If preserving the original plus all required targets exceeds the limit, this interface refuses it; the parent must choose another documented approach rather than dropping exclusions.

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

That distinction matters on A14.G1. The library accepts a sequence-matched `0xd1` reply. The MCU queues that reply while handling the `0xd0` transport envelope, **before** the following `0xd3` callback stores the sentinel. The traced callback stores `-1`, and its heartbeat-loss consumer returns before counting or escalation for that value, but return 0 does not read it back or prove an offline interval survived. The runtime build-label correspondence and the complete A14 branch are explained in [A14 heartbeat findings](A14-HEARTBEAT.md).

Process inspection is not an atomic ownership reservation. An independently restarted loader or another UART user could appear after a scan; the library lock is an additional check, not a command gate. Keep the actual producers stopped through the separately approved procedure. UART initialization changes termios and receive state and can discard pending traffic; the inspected userspace path contains no flash, reset or motor command, but the kernel driver's internal effects were not reconstructed.

There is deliberately no re-enable command. `rua_keep_mcu_heartbeat(0)` sends 60, not raw zero. Ordinary chassis startup supplies raw-zero heartbeats; an MCU reset also loses the sentinel. Neither behavior is invoked by this helper, and no hold-off is assumed to survive a restart.

## Rebuilding without introducing a newer libc

The saved rootfs identifies **Ubuntu EGLIBC 2.19-0ubuntu6.6**. Its development headers and start files are absent. This build uses the compatible Ubuntu `libc6-dev_2.19-0ubuntu6_armhf.deb` headers, start objects and `libc_nonshared.a`, but links dynamically against the **exact saved runtime** files, not that package's libc or the current Nix libc. The development package is the initial 2.19 Ubuntu release, not the device's later security revision. The final imported symbols were inspected against the saved libraries.

All preparation stays local. From the repository root, obtain the ARM compiler and extract the development package into a new private temporary directory:

```sh
NIXPKGS='https://api.flakehub.com/f/pinned/DeterminateSystems/nixpkgs-weekly/0.1.1090327%2Brev-7fd4004d0511991fff3a0524856a9be09e28c5f0/01a157d3-12a4-7a20-aeab-772b0493858f/source.tar.gz'
CROSS="$NIXPKGS#pkgsCross.armv7l-hf-multiplatform"
nix build --no-link --print-out-paths "$CROSS.stdenv.cc"
GCC=$(nix eval --raw "$CROSS.stdenv.cc.cc.outPath")
BT=$(nix eval --raw "$CROSS.stdenv.cc.bintools.bintools.outPath")
KH=$(nix eval --raw "$CROSS.linuxHeaders.outPath")

work=$(mktemp -d /tmp/map-helper-build.XXXXXX)
curl --fail --location --silent --show-error \
  --output "$work/libc6-dev.deb" \
  https://ports.ubuntu.com/ubuntu-ports/pool/main/e/eglibc/libc6-dev_2.19-0ubuntu6_armhf.deb
sha256sum "$work/libc6-dev.deb"
# Expected: 82328ca2989c3bfd75b40bb0adc282559b1a86711b5619a00b5639f2a339858a
mkdir "$work/dev"
ar p "$work/libc6-dev.deb" data.tar.xz | tar -xJf - -C "$work/dev"

CC="$GCC/bin/armv7l-unknown-linux-gnueabihf-gcc" \
BINUTILS="$BT/armv7l-unknown-linux-gnueabihf/bin" \
  sh tools/map-maint/build.sh \
  /home/user/tmp/illegalplainape/analysis/rootfs "$work/dev" "$KH"
```

Compare the displayed development-package hash with the recorded value before extraction. This is a local download and build, not an installation or upgrade. The pinned Nix input resolved to revision `7fd4004d0511991fff3a0524856a9be09e28c5f0`, supplying GCC 16.2.0, binutils 2.46 and Linux headers 7.2. The kernel headers provide declarations only; the program uses the old saved libc and its syscall wrappers, not a new target kernel/runtime.

[build.sh](../../tools/map-maint/build.sh) uses the unwrapped cross compiler and explicitly selected assembler/linker. It excludes default libc headers and default start libraries. The only dynamic link inputs are the saved `libdl.so.2`, `libc.so.6` and `ld-linux-armhf.so.3`; the 2.19 development package supplies the old start/nonshared pieces. This avoids silently importing a new `__libc_start_main` or stat ABI. Stack protection remains enabled. Initial link attempts identified a missing unwrapped linker path and the loader-owned stack guard; the final script supplies both explicitly.

The output and object file stay under ignored `tools/map-maint/build/`. Only source, the build script, its ignore rule and this document are tracked. The script does not run the output. Do not use an emulator, execute vendor firmware or copy the binary to the robot as part of building it.

## Build identities and ELF inspection

The successfully deployed binary is **21,500 bytes**, with SHA256 **`fb75e397eb09c51aa1a0402918fe55c357363be5843e6e7f896e6b7d7d8987f0`**. Its source SHA256 is `637ca1de45ee0082dad6eeeaf429be97ead58365bb07125c1ecbcb8fc7341b0f`.

The initial binary, before refusal diagnostics and the zombie correction, was **17,312 bytes**, SHA256 `4ace18a953eff862a6c3815179a6e35ec3e1bf5e4d5e86cd19f39eb2944d51a0`. The following ELF observations came from that initial build:

```sh
readelf -h -l -d -V -A -n tools/map-maint/build/map-maint
readelf --dyn-syms -W tools/map-maint/build/map-maint
```

The ELF is little-endian ARM32, EABI5 hard-float, ARMv7-A with VFPv3-D16. These architecture attributes match the saved loader. Its interpreter is `/lib/ld-linux-armhf.so.3`; its GNU ABI note says Linux 2.6.32, below the observed Linux 3.4.39. It has a non-executable stack, immediate binding and RELRO, with no RPATH or RUNPATH.

Its only `DT_NEEDED` entries are `libdl.so.2`, `libc.so.6` and `ld-linux-armhf.so.3`. Every required versioned dynamic symbol is **GLIBC_2.4**. The individual imported symbols were found in the exact saved libc, dl library and loader, including the loader's `__stack_chk_guard`. There is no new GLIBC requirement from the Nix compiler, and no startup dependency on either vendor library. The vendor libraries are loaded only in the selected operation.

The saved vendor dependencies are present: IPC needs rrlog, libconfig, pthread, rt, libstdc++, libgcc and libc/loader; the UART library needs dl, pthread, m and libc/loader. Inspecting their `DT_NEEDED` entries and GLIBC requirements found no requirement beyond the saved glibc 2.19. This does not arrange library search paths on the robot: a later deployment decision must retain a trusted vendor dependency search path and the matching installed files. The helper's absolute `dlopen` path alone does not set the search path for a vendor library's dependencies.

The locally rechecked MD5 values for the saved IPC and UART libraries are respectively `ebc857c5b2bd067cf36b6269d5368ac3` and `5c9d6a7b81bc2d9467b6d0f791ae6ace`, matching the prior [device observations](DEVICE-FACTS.md). Other dependency files were inspected locally, not newly compared with the running robot.

## Runtime limits

Target startup, the dependency search path, exclusion delivery and native return 0 were observed during the [completed stopped backup](MAINTENANCE-PROCEDURE.md). No map file was edited or restored. There is still no semantic sentinel readback or demonstrated independent rescue connection. A successful backup does not make arbitrary map replacement safe or remove the need for fresh status, ownership checks and independent recovery on another run.
