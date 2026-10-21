# Cross-build the native helper

Build locally against the exact saved runtime; do not install a newer libc on the robot. This requires the private saved rootfs, an ARM cross compiler and the development package below. The [helper reference](../reference/tools/map-maint.md) describes its API and ownership checks. All commands run from the repository root and stop at local build/inspection.

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

The locally rechecked MD5 values for the saved IPC and UART libraries are respectively `ebc857c5b2bd067cf36b6269d5368ac3` and `5c9d6a7b81bc2d9467b6d0f791ae6ace`, matching the prior [device observations](../history/2026-10-21/device-observations.md). Other dependency files were inspected locally, not newly compared with the running robot.
