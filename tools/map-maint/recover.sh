#!/bin/sh
# Run in a private session before stopping services; never live-reload exclusions.
set -eu
umask 077
PATH=/usr/sbin:/usr/bin:/sbin:/bin
export PATH
unset LD_PRELOAD LD_AUDIT LD_LIBRARY_PATH

fail() {
    printf '%s\n' "$*" >&2
    exit 1
}

[ "$#" = 2 ] && [ "$2" = approved-once ] || fail "Usage: $0 SESSION approved-once"
[ "$(id -u)" = 0 ] || fail 'Root required'
grep -q '^ROBOROCK_VERSION=4.3.5_1612$' /etc/os-release || fail 'Unexpected firmware'
[ -d "$1" ] && [ ! -L "$1" ] || fail 'SESSION must be a real directory'
B=$(cd "$1" && pwd -P)
[ "$(dirname "$B")" = /mnt/data ] || fail 'Use a private /mnt/data/map-* session'
case "${B##*/}" in map-*) ;; *) fail 'Use a map-* session name';; esac
ROOT=/mnt/data/rockrobo
WORK=$B/matching
E=$ROOT/exclude_process.conf
TOOLS=$(cd "$(dirname "$0")" && pwd -P)
[ ! -e "$B/recovery.ready" ] || fail 'Recovery already armed'
[ "$(cat "$B/boot-id")" = "$(cat /proc/sys/kernel/random/boot_id)" ] || fail 'Wrong boot'
(
    cd "$B"
    md5sum boot-id exclude.original original-exclusions.tar
) > "$B/original-check.md5"
cmp "$B/original.md5" "$B/original-check.md5"
[ -s "$B/exclude.original" ] && [ ! -L "$B/exclude.original" ] || fail 'Expected nonempty original'
[ "$(tar -tf "$B/original-exclusions.tar")" = exclude_process.conf ] || fail 'Unexpected original archive'
[ ! -L "$E" ] || fail 'Exclusion symlink refused'
if grep -q -e 'cfg_by=tuya' -e 'cfg_by=rriot' /mnt/data/miio/wifi.conf; then
    fail 'Resolve the optional Wi-Fi rewrite branch before reboot'
fi
mkdir -m 700 "$B/original-stage"
tar -xpf "$B/original-exclusions.tar" -C "$B/original-stage"
R=$B/original-stage/exclude_process.conf
[ -f "$R" ] && [ ! -L "$R" ] || fail 'Original must be a regular file'
cmp "$R" "$B/exclude.original"

identity=$(awk '{print $5 ":" $6 ":" $22}' /proc/$$/stat)
case "$identity" in "$$:$$:"*) ;; *) fail 'Launch with setsid';; esac
[ "$(readlink /proc/$$/fd/0)" = /dev/null ] || fail 'Close stdin with /dev/null'
read -r uptime rest < /proc/uptime
deadline=$((${uptime%%.*} + 120))
printf '%s %s %s\n' "$$" "${identity##*:}" "$deadline" > "$B/recovery.ready"
while :; do
    [ ! -e "$B/recover.now" ] || break
    [ ! -e "$WORK/install.complete" ] || break
    read -r uptime rest < /proc/uptime
    [ "${uptime%%.*}" -lt "$deadline" ] || break
    sleep 1
done

# The operation leader must remain alive on success/failure until recovery ends it.
if [ -f "$B/operations.identity" ]; then
    read -r op tick < "$B/operations.identity"
    case "$op:$tick" in *[!0-9:]*|:*|*:) fail 'Invalid operations identity';; esac
    [ "$op" -gt 1 ] && [ "$op" != "$$" ] || fail 'Invalid operations PID'
    if [ -e "/proc/$op/stat" ]; then
        actual=$(awk '{print $5 ":" $6 ":" $22}' "/proc/$op/stat")
        [ "$actual" = "$op:$op:$tick" ] || fail 'Operations identity changed'
        /bin/busybox kill -TERM "-$op" || :
        /bin/busybox kill -KILL "-$op" 2>/dev/null || :
        sleep 1
    fi
    # Do not race a surviving child, including an uninterruptible rename/copy.
    for stat in /proc/[0-9]*/stat; do
        [ -r "$stat" ] || continue
        if awk -v group="$op" '$5 == group && $3 != "Z" {found=1} END {exit !found}' "$stat"; then
            fail 'Operations group still alive; keep consumers excluded'
        fi
    done
elif [ -e "$B/services.touched" ]; then
    fail 'Missing operations identity; keep consumers excluded'
fi

[ -e "$B/services.touched" ] || {
    printf 'No services touched; no reboot requested.\n' > "$B/recovery.finished"
    exit 0
}
if [ -e "$WORK/install.started" ] && [ ! -e "$WORK/install.complete" ]; then
    /bin/sh "$TOOLS/matching-set.sh" rollback "$ROOT" "$WORK"
fi

# Refuse normal startup until one whole disk epoch has passed verification.
if [ -e "$WORK/install.started" ]; then
    /bin/sh "$TOOLS/matching-set.sh" verify "$ROOT" "$WORK"
fi
[ ! -L "$E" ] || fail 'Exclusion symlink refused'
mv "$R" "$E"
cmp "$E" "$B/exclude.original"
sync
printf 'Original exclusions restored on disk; requesting normal reboot.\n' > "$B/recovery.finished"
sync
/sbin/reboot
