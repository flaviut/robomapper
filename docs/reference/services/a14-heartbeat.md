# A14.G1 heartbeat hold-off for map maintenance

**The packaged A14.G1 implementation preserves `-1` and returns before heartbeat-loss counting or reset.** Its initialized command table really does connect opcode `0xd3` to that handler. The observed runtime label identifies this A14.G1 build, including its timestamp: the eight-hour difference from the package filename is explained by the firmware's own formatting code, not evidence of another build.

This supports preparing the existing `rua_keep_mcu_heartbeat(-1)` call for use **after the chassis/loader has exited**, with WatchDoge still running. This static analysis did not enter a service-off interval; the later [backup procedure](../../guides/stopped-backup.md) records one. The acknowledgment is a sequence acknowledgment, not a readback of the sentinel; in this MCU it is queued before the heartbeat callback runs. Do not stop services or replace map files on the strength of this document alone.

This is local static work on saved firmware, continuing [the heartbeat investigation](heartbeat.md) using [the observed device facts](../../history/2026-10-21/device-observations.md). No SSH connection, device open, robot command, service change or firmware execution occurred. No tests, suites, validators, replay or review machinery were run. The findings below describe that static investigation.

## Which build the runtime label identifies

The saved package contains six chassis images, plus three separate carpet images. The relevant chassis file is:

```text
binaries/4.3.5_1612/opt/rockrobo/firmware/img/
RR_TANOSS_MP_STM32.A14.G1_M4.0.1_RELEASE_20221102-212632_FULL.bin
```

The image is tracked in the repository. Its SHA256 is `7d3ae25d8d6a138807e72d8a617fc47e7f6f1cd375c4736b31d3b8e80af4d915`. MCU addresses below are flash virtual addresses, equal to `0x08000000 + file offset`; callback pointers include the Thumb bit. Linux library addresses are ELF virtual addresses, not MCU addresses.

**Neither timestamp exists as an ASCII version string in this image.** Nor does a complete literal `A14` or `M4.0.1` string. The 64-byte firmware-information record starts at file offset `0x8000`. Its version subrecord starts at `0x801c`, holding the little-endian epoch **`0x63627008`**, or **November 2, 2022, 13:26:32 UTC**. The architecture bytes encode A14 and G1; the version bytes encode 4.0.1 and release status. This is structured metadata, not a filename copied into the firmware.

The image's version formatter starts at `0x080199f0`. At **`0x08019be4–0x08019bea`** it loads that epoch and explicitly **adds 28,800 seconds** before calendar conversion and formatting as `%Y%m%d-%H%M%S` (`0x08019bf4–0x08019bfa`, format at `0x08019d20`). That yields **`20221102-212632`**, exactly the filename timestamp. This establishes the eight-hour formatting relationship. It does not reconstruct the external packaging script or require an assumption about the build machine's timezone.

The matching Linux UART library behaves differently. `FwInfo2Str:0xf828` passes the version subrecord at offset +28 to `FwVer2Str:0xecc8`. At **`0xf39e–0xf3c4`**, that formatter passes the **unadjusted epoch** to `localtime`, then `strftime` with the same date format. Thus a UTC local-time setting produces **`20221102-132632`**, the runtime label already observed. The effective timezone of that historical process was not newly measured here; the raw epoch, the explicit MCU addition and the observed Linux output agree without changing firmware identity.

The runtime file also has a grounded producer. In saved WatchDoge, **`0x16864`** calls `check_version` into a zeroed 64-byte buffer; results 0, −20 and −21 continue to the formatting/write path. At **`0x168f2–0x1692a`**, it opens **`/dev/shm/mcu_version` with `"w"`**, calls `FwInfo2Str`, writes its string through `%s`, and closes the file. The observed `/dev/shm` link makes that the same location as `/run/shm/mcu_version`. This is a saved userspace rendering of an MCU reply, not a flash-byte measurement or necessarily a query made at the instant the file is read.

`check_version:0x10f9c` requests opcode **`0x80`**, expects 64 bytes and checks protocol-version fields. In the A14 image, the registered `0x80` callback at **`0x08012352`** sends 64 bytes from **`0x08008000`** in response opcode 1 (`0x080130c4` supplies the record pointer). This connects the image's structured record to the library formatter and the runtime file.

The [prior device observation](../../history/2026-10-21/device-observations.md#running-software-and-launch-paths) matched the saved loader, chassis plugin and UART library by MD5. WatchDoge itself was identified by executable path, not byte-compared; its saved binary has SHA256 `3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6`. The UART and chassis matches establish that their relevant saved Linux call paths apply to those observed binaries. The file-writing path above is established in saved WatchDoge, not newly observed as it executes. The exact A14.G1/release/version/epoch match is strong build-label evidence for the corresponding packaged MCU implementation. **It is not proof that every installed flash byte equals this image.** A modified MCU could preserve its version record, and a saved file can become stale.

Numeric JTAG and gyro IDs are useful for the updater's hardware/image selection. They are **not an additional essential discriminator for this heartbeat analysis once the actual A14.G1 version record is known**. The relevant consumer is now traced for that variant rather than borrowed from A3.G1. Numeric IDs would not prove installed instruction bytes either. Nothing here justifies running an updater, flashing the preferred A3 package, or issuing extra hardware queries simply to obtain those numbers.

## The A14 command table, handler and reset branch

The dispatch table is initialized from compressed data, so searching for an aligned pointer in the raw image alone misses the connection. The startup loop at **`0x08032b1c`** walks initialization descriptors `0x08033ebc–0x08033ee0`. Its compressed-data descriptor begins at `0x08033ecc`; arguments at **`0x08033ed0`** are source-relative offset `0x258`, encoded size/flags `0x129c` and destination **`0x20000000`**. The initializer at **`0x08033c30`** therefore expands bytes **`0x08034128–0x08034a76`** into RAM. A bounded local extraction transcribed that initializer's literal/back-reference operations; it did not execute MCU code.

The receive dispatcher's base pointer is **`0x200054f4`**, loaded at `0x08011b9c` from `0x080126f0`. It searches 60 eight-byte records starting at base +`0x108`. The recovered records relevant here are:

| RAM record | Slot | Opcode | Thumb callback |
| --- | ---: | ---: | --- |
| `0x20005604` | 1 | `0xd0` | `0x08011f93` — envelope acknowledgment |
| `0x200056d4` | 27 | `0x80` | `0x08012353` — firmware information |
| **`0x200057cc`** | **58** | **`0xd3`** | **`0x08013443` — heartbeat receive** |

At **`0x08011c6e–0x08011c8a`**, the dispatcher compares the received opcode against each record, loads callback +4, and calls it with the payload pointer and byte length. After each invoked callback it calls heartbeat-loss consumer **`0x08013330` with argument 0** (`0x08011c8c–0x08011c8e`). This closes registration and invocation, not just similarity to the A3 handler.

The heartbeat callback **`0x08013442`** requires length 4 and copies the payload into **RAM `0x20008c7c`** at `0x08013460–0x08013468`. Its conversion block **`0x08013490–0x080134ae`** leaves both zero and `0xffffffff` unchanged. Other values are unsigned-clamped to `0x00ffffff`, then multiplied by 100. A request of 120 therefore becomes 12,000 countdown calls, not a proven wall-clock allowance. A request of −1 remains the sentinel.

The consumer **`0x08013330`** loads that same RAM word and tests −1 at **`0x08013336–0x0801333c`**. Equality branches straight to the return at `0x0801340a`, **before mode checks, countdown changes, loss-counter changes or escalation**. Mode 8 also returns. For a nonzero ordinary value, only argument 1 decrements it (`0x08013402–0x08013408`). When the value is zero, argument 0 clears the loss counter; argument 1 can advance it, subject to the other mode/status checks.

Timer event **`0x6a`** reaches `0x0801e1b8` through dispatch at **`0x08011d46/0x08011d80`**, then calls the consumer with **1** at **`0x0801e1e0–0x0801e1e2`**. Received callbacks use 0. Thus ordinary command traffic can clear the loss counter when the hold-off is zero; this is not solely a timer measuring time since the last `0xd3`.

The reset path is concrete for modes **0 and 5**: with zero hold-off, the loss counter reaches **6500** at **`0x0801336e–0x0801337a`**, calls delay `0x0801d05e` with 10, then branches at **`0x08013386`** to **`0x080239c4`**. That function masks faults, writes **`0x05fa0004` to SCB AIRCR `0xe000ed0c`**, then loops. This requests an MCU system reset. Other modes at least 32 have other escalation paths in the same consumer; modes below 32 other than 0/5 return without that counting branch. The −1 return precedes all of them.

The startup zero-initialization descriptor clears **`0x20005b50–0x20008de0`**, including the sentinel and loss counter. A real MCU reset therefore loses the hold-off. A later valid `0xd3` replaces it, including the normal chassis callback's raw-zero heartbeat. Neither a Linux-only reboot nor the disappearance of a process establishes which of those events happened. The sentinel disables this consumer's missing-traffic response, not unrelated MCU protections.

## What opening and closing UART actually does

The matching **`libuart_api.so.4.0.2`** has SHA256 `914317e600a73255cb6523e987ab3ab99b5168c47026503fcb3fe797f9961529`. The temporary-owner path is **`rua_keep_mcu_heartbeat:0x11564 → init_uart:0x5e64 → rua_uart_init:0x7144`**, followed by the acknowledged send and **`close_uart:0x5f00 → rua_uart_exit:0x6df0`** if this call opened UART. The return instructions at `0x115cc–0x115d8` preserve the send/init result across closing and return it in r0: require **0**, not just process completion.

Initialization is not an upgrade routine. It opens `/dev/ttyS2`, takes **nonblocking exclusive `flock`**, configures **1152000 baud, 8N1** using termios, flushes input, and opens `/dev/uart_mcu`. It uses **ioctl `0x40045810` with a 0x4000 receive-buffer size**, maps a metadata page and data region, initializes their FIFO, initializes a local mutex, and clears receive state. `rua_uart_clean:0x70a4` uses the mapped FIFO for this configuration; **`rua_fifo_clean:0xddcc` copies the write index to the read index**. Initialization can discard pending traffic and changes actual device state, even though it does not send a robot action packet. The lock is an additional safeguard, not a substitute for confirming that the loader exited and no other owner can race it.

Closing sets the library's local stop flag, waits in 60 ms increments for local activity flags to clear, with a roughly 300 ms deadline, then calls `rua_uart_exit`. That unmaps both regions, closes the companion descriptor, unlocks/closes the TTY through **`0x6dc8`**, frees its context and clears local initialization state. It sends **no additional `0xd3`**, no re-enable request, and no reset command. It does not explicitly restore the previous termios settings. In a one-shot process there are no library receive-worker threads started by `init_uart`; the acknowledged send reads its own response synchronously. The ELF's sole init/fini-array entries (`0x5a89`, `0x5a49`) are ordinary runtime bookkeeping, not an upgrade hook.

**No firmware-update, flash, MCU-reset/GPIO-control or motor-control call is on this inspected userspace init/send/close path.** Those capabilities elsewhere in the library are not called merely by opening UART through this API. The only command it deliberately sends here is `0xd3` with the supplied four bytes, inside transport framing. The kernel driver's internal open/ioctl/release behavior was not reconstructed, so this is not a blanket claim about electrical effects or installed hardware behavior. It is a reason to use the existing vendor API and its temporary-owner lifecycle rather than a factory tool or an invented raw-serial sequence.

This finding does not make chassis shutdown harmless during activity: chassis also handles motion and other protections. The [service-control plan](supervision.md) still requires a stationary, idle, update-free robot, blocked command producers, actual host exit, and WatchDoge's independent Linux watchdog feeder left running. No such interval was entered here.

## What a successful acknowledgment means

`rua_keep_mcu_heartbeat(-1)` preserves −1, calls **`sent_cmd_sigle_thread(0xd3, 4, &value, 1)`**, retries negative results up to three times with 20 ms pauses, then closes only its own temporary UART context. Unlike passing 0, it does not substitute a finite value of 60.

The send function at **`0x105d4`** places an acknowledgment-request envelope (`0xd0`, two bytes containing flag and sequence) before the actual command. Its success check at **`0x10716–0x1072a`** accepts **response opcode `0xd1`, length 1, payload equal to its sequence byte**, and returns 0. There is no returned heartbeat value or command-specific status.

The A14 table makes that distinction observable in code. Envelope handler **`0x08011f92`** checks the flag and queues a `0xd1` response carrying the sequence (`0x08011f9a–0x08011fa8`). The command dispatcher processes the envelope before the following `0xd3` record in the frame. **The ACK can therefore be queued before the heartbeat value is stored.** In the normal traced flow, the next callback stores the sentinel, but the ACK itself does not certify that later instruction ran.

Return 0 establishes that initialization succeeded enough to exchange a framed, sequence-matched reply with the peer. Together with the build-label and code evidence, that supports the intended one-shot hold-off mechanism. It does **not** prove the installed flash hash, semantic acceptance/readback of −1, completion of chassis cleanup, a stationary/docked state, persistence across reset, or successful survival of an offline maintenance interval. If initialization, locking or sending fails, do not start file replacement; do not replace that failure with blind raw writes or an updater invocation.

## Reproducing the static findings

Original firmware and the shared analysis baseline were left unchanged. Private copies, disassemblies and the bounded initialized-data extraction are in `/tmp/map-a14-heartbeat`. Earlier exported C files in `/tmp/map-heartbeat/uart-focused`, `uart-transport` and `mcu-match` were read only; its project was not opened. Current conclusions were tied back to original instructions with `arm-none-eabi-objdump`, ELF symbols/sections with `arm-none-eabi-readelf`, raw offsets with `xxd`, and SHA256 identities with `sha256sum`. No firmware or helper was run.

For an independent instruction lookup, disassemble the A14 binary with `-D -b binary -marm -Mforce-thumb --adjust-vma=0x08000000`, restricting `--start-address`/`--stop-address` to the addresses above. In particular, the registration result depends on expanding the descriptor with the **actual `0x08033c30` initializer**, not treating the compressed bytes around file offset `0x34a1d` as an aligned raw callback table. The heartbeat record becomes `0xd3` and `0x08013443` at RAM `0x200057cc`.

The remaining operational uncertainty is **installed behavior, not an unexplained A14 timestamp or missing A14 sentinel branch**. This static analysis supplies no UART takeover procedure. Use the [native helper reference](../tools/map-maint.md) and [demonstrated backup guide](../../guides/stopped-backup.md) for the later operational work.
