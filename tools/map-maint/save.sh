#!/bin/sh
set -eu
umask 077
PATH=/usr/sbin:/usr/bin:/sbin:/bin
export PATH
unset LD_PRELOAD LD_AUDIT
LD_LIBRARY_PATH=/lib:/lib/arm-linux-gnueabihf:/usr/lib:/usr/lib/arm-linux-gnueabihf:/opt/rockrobo/cleaner/lib:/mnt/default
export LD_LIBRARY_PATH
B=$1
ROOT=/mnt/data/rockrobo
E=$ROOT/exclude_process.conf
stage=starting
touched=0
installing=0

log() {
    stage=$*
    printf '[map-save] %s\n' "$stage" >&2 || :
    printf '[map-save] %s\n' "$stage" >> "$B/save.log" || :
}

reboot_robot() {
    sync
    log 'Requesting reboot'
    /sbin/reboot
}

restore_supervision() {
    cp -p "$B/original/exclude_process.conf" "$E"
}

finish() {
    code=$1
    trap - EXIT
    trap '' HUP INT TERM PIPE
    [ "$code" = 0 ] && return
    log "FAILED: $stage (exit $code)"
    [ "$touched" = 1 ] || return "$code"
    if [ "$installing" = 1 ]; then
        log 'Restoring original map files'
        while read -r hash name; do
            mv "$B/original/$name" "$ROOT/$name" || exit 1
        done < "$B/patch/patch.md5"
    fi
    log 'Restoring supervision'
    restore_supervision || exit 1
    reboot_robot
    exit "$code"
}
trap 'finish $?' EXIT
trap 'exit 1' HUP INT TERM PIPE

writers_gone() {
    for proc in /proc/[0-9]*; do
        exe=$(readlink "$proc/exe") || continue
        case "${exe##*/}" in
            valetudo|rr_loader|RoboController|RoboControllerR|RoboControllerM|AppProxy|miio_client|rriot_rr|rriot_tuya|SysUpdate) return 1;;
        esac
    done
}

stop_writers() {
    [ "$(id -u)" = 0 ]
    grep -q '^ROBOROCK_VERSION=4.3.5_1612$' /etc/os-release
    { cat "$E"; printf '\nrr_l\nRoboC\nAppP\nmiio\nSysU\nrriot\n'; } > "$B/exclusions"
    [ "$(wc -c < "$B/exclusions")" -le 63 ]
    touched=1
    log 'Stopping Valetudo'
    for proc in /proc/[0-9]*; do
        [ "$(readlink "$proc/exe")" = /mnt/data/valetudo ] || continue
        kill -TERM "${proc##*/}"
        n=0
        while [ -e "$proc/exe" ]; do
            n=$((n + 1)); [ "$n" -le 8 ]
            sleep 1
        done
    done
    log 'Stopping vendor writers'
    "$B/map-maint" exclusions "$B/original/exclude_process.conf" "$B/exclusions" >&2
    n=0
    until writers_gone; do
        n=$((n + 1)); [ "$n" -le 8 ]
        sleep 1
    done
    log 'Requesting MCU hold-off'
    "$B/map-maint" mcu-disable >&2
}

mkdir -m 700 "$B/original" "$B/patch" "$B/stage"
cp -p "$E" "$B/original/exclude_process.conf"
stop_writers

log 'Backing up map files'
cd "$ROOT"
for name in last_map PersistData_1.data SharedMultiMapInfo user_map[0-3] PersistData_[2-5].data; do
    [ -f "$name" ] && [ ! -L "$name" ]
    cp -p "$name" "$B/original/$name"
done
(cd "$B/original"; tar -cpf "$B/backup.tar" *)
hash=$(md5sum "$B/backup.tar")
printf 'BACKUP %s %s\n' "$(wc -c < "$B/backup.tar")" "${hash%% *}"
cat "$B/backup.tar"

# The server authorizes writes only after fsyncing its backup.
log 'Waiting for verified off-device backup and patch'
read -r -t 45 approval
[ "$approval" = PATCH ]
tar -xpf - -C "$B/patch"
[ "$(wc -l < "$B/patch/patch.md5")" = 4 ]
(cd "$B/patch"; md5sum -c patch.md5) >&2
while read -r hash name; do
    case "$name" in last_map|user_map[0-3]|PersistData_[1-5].data) ;; *) exit 1;; esac
    cp -p "$B/original/$name" "$B/stage/$name"
    cat "$B/patch/$name" > "$B/stage/$name"
    touch -r "$B/original/$name" "$B/stage/$name"
done < "$B/patch/patch.md5"

log 'Installing map files'
installing=1
while read -r hash name; do mv "$B/stage/$name" "$ROOT/$name"; done < "$B/patch/patch.md5"
(cd "$ROOT"; md5sum -c "$B/patch/patch.md5") >&2
log 'Restoring supervision'
restore_supervision
sync
printf 'INSTALLED\n'
reboot_robot
