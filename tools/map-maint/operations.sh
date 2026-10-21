#!/bin/sh
# Session preparation pins this boot's identities before recovery is armed.
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
TOOLS=$(cd "$(dirname "$0")" && pwd -P)
[ ! -e "$B/operations.identity" ] && [ ! -e "$WORK" ] || fail 'Session already used'
[ "$(cat "$B/boot-id")" = "$(cat /proc/sys/kernel/random/boot_id)" ] || fail 'Wrong boot'
[ -f "$TOOLS/session.sh" ] && [ ! -L "$TOOLS/session.sh" ] || fail 'Missing session driver'
(cd "$B"; md5sum -c inputs.md5) >/dev/null
read -r recovery tick deadline < "$B/recovery.ready"
case "$recovery:$tick:$deadline" in *[!0-9:]*|:*|*:) fail 'Invalid recovery identity';; esac
[ "$(awk '{print $5 ":" $6 ":" $22}' "/proc/$recovery/stat")" = "$recovery:$recovery:$tick" ] || fail 'Recovery is not running'
read -r uptime rest < /proc/uptime
[ "$((deadline - ${uptime%%.*}))" -ge 100 ] || fail 'Rearm in a fresh session'
identity=$(awk '{print $5 ":" $6 ":" $22}' /proc/$$/stat)
case "$identity" in "$$:$$:"*) ;; *) fail 'Launch with setsid';; esac
[ "$(readlink /proc/$$/fd/0)" = /dev/null ] || fail 'Close stdin with /dev/null'
printf '%s %s\n' "$$" "${identity##*:}" > "$B/operations.identity"

# Keep the leader inspectable until independent recovery ends its whole group.
failed() {
    trap - EXIT
    printf 'Operation failed; recover a whole epoch.\n' > "$B/recover.now"
    while :; do sleep 1; done
}
trap failed EXIT
trap 'trap - EXIT; exit 1' TERM HUP INT
printf 'Service stop may begin.\n' > "$B/services.touched"
/bin/sh "$TOOLS/session.sh" stop "$B"
/bin/sh "$TOOLS/matching-set.sh" capture "$ROOT" "$WORK"
tar -cpf "$B/untouched-stopped-backup.tar" -C "$WORK" snapshot snapshot.md5 capture.complete
sync
printf 'Stopped archive ready for off-device verification.\n' > "$B/backup.ready"

n=0
while [ ! -e "$WORK/offdevice.verified" ]; do
    n=$((n + 1))
    [ "$n" -le 40 ] || fail 'Off-device verification timed out'
    sleep 1
done
read -r uptime rest < /proc/uptime
[ "$((deadline - ${uptime%%.*}))" -ge 30 ] || fail 'Insufficient recovery budget'
action=install
[ ! -e "$B/editor-upload" ] || action=apply
/bin/sh "$TOOLS/matching-set.sh" "$action" "$ROOT" "$WORK"
trap - EXIT
while :; do sleep 1; done
