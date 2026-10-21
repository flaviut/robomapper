#!/bin/sh
# Build only. This script never executes the resulting ARM program.
set -eu
if [ "$#" -ne 3 ]; then
    echo 'Usage: CC=/path/to/unwrapped-armhf-gcc BINUTILS=/path/to/target/bin sh build.sh ROOTFS LIBC_DEV LINUX_HEADERS' >&2
    exit 1
fi
: "${CC:?Set CC to an unwrapped ARM hard-float GCC (not the Nix compiler wrapper)}"
: "${BINUTILS:?Set BINUTILS to the target directory containing unwrapped as and ld}"
root=$(realpath "$1")
dev=$(realpath "$2")
linux=$(realpath "$3")
here=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
out="$here/build"
lib="$root/lib/arm-linux-gnueabihf"
crt="$dev/usr/lib/arm-linux-gnueabihf"
inc=$($CC -print-file-name=include)
begin=$($CC -print-file-name=crtbegin.o)
end=$($CC -print-file-name=crtend.o)
gcc=$($CC -print-libgcc-file-name)
mkdir -p "$out"

# Use the 2.19 development headers/start files, never the compiler's current libc.
"$CC" -B"$BINUTILS/" -std=c11 -O2 -Wall -Wextra -Werror -fstack-protector-strong \
    -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -marm \
    -fno-pie -nostdinc \
    -isystem "$inc" -isystem "$dev/usr/include/arm-linux-gnueabihf" \
    -isystem "$dev/usr/include" -isystem "$linux/include" \
    -c "$here/map-maint.c" -o "$out/map-maint.o"

# Exact saved runtime files provide libc/dl and the symbol-version ceiling.
# Static libgcc contains only any compiler arithmetic support actually needed.
"$CC" -B"$BINUTILS/" -no-pie -nostdlib -Wl,--hash-style=both,-z,relro,-z,now \
    -Wl,--dynamic-linker=/lib/ld-linux-armhf.so.3 \
    -Wl,-rpath-link,"$lib" \
    "$crt/crt1.o" "$crt/crti.o" "$begin" "$out/map-maint.o" \
    "$lib/libdl.so.2" "$lib/libc.so.6" "$lib/ld-linux-armhf.so.3" \
    "$crt/libc_nonshared.a" "$gcc" \
    "$end" "$crt/crtn.o" -o "$out/map-maint"
printf 'Built %s (not executed).\n' "$out/map-maint"
