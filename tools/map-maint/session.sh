#!/bin/sh
set -eu
umask 077
PATH=/usr/sbin:/usr/bin:/sbin:/bin
export PATH
unset LD_PRELOAD LD_AUDIT LD_LIBRARY_PATH
[ "$#" = 2 ] || { echo "Usage: $0 prepare|stop SESSION" >&2; exit 1; }
phase=$1
B=$2
TOOLS=$B/editor-tools
E=/mnt/data/rockrobo/exclude_process.conf

# Pin executable, argv and start time so PID reuse cannot authorize a signal.
record() {
    record_kind=$1
    record_pid=$2
    record_exe=$(readlink "/proc/$record_pid/exe")
    case "$record_exe" in *' '*|*'|'*) return 1;; esac
    record_tick=$(awk '{print $22}' "/proc/$record_pid/stat")
    record_hash=$(md5sum "/proc/$record_pid/exe")
    record_cmd=$(md5sum "/proc/$record_pid/cmdline")
    printf '%s|%s|%s|%s|%s|%s\n' "$record_kind" "$record_pid" "$record_tick" "${record_hash%% *}" "${record_cmd%% *}" "$record_exe" >> "$B/processes"
}

process_is() {
    [ "$(awk '{print $22}' "/proc/$1/stat")" = "$2" ] &&
    [ "$(readlink "/proc/$1/exe")" = "$5" ] &&
    [ "$(md5sum "/proc/$1/exe" | awk '{print $1}')" = "$3" ] &&
    [ "$(md5sum "/proc/$1/cmdline" | awk '{print $1}')" = "$4" ]
}

protected_alive() {
    while IFS='|' read -r kind pid tick hash cmd exe; do
        [ "$kind" = keep ] || continue
        process_is "$pid" "$tick" "$hash" "$cmd" "$exe" || return 1
    done < "$B/processes"
}

blocked_absent() {
    while IFS='|' read -r kind pid tick hash cmd exe; do
        [ "$kind" != keep ] || continue
        [ -e "/proc/$pid/stat" ] || continue
        [ "$(awk '{print $22}' "/proc/$pid/stat")" = "$tick" ] || continue
        [ "$(awk '{print $3}' "/proc/$pid/stat")" = Z ] && [ ! -e "/proc/$pid/exe" ] || return 1
    done < "$B/processes"
    for proc in /proc/[0-9]*; do
        current=$(readlink "$proc/exe") || continue
        case "${current##*/}" in
            valetudo|rr_loader|RoboController|RoboControllerR|RoboControllerM|AppProxy|miio_client|rriot_rr|rriot_tuya|SysUpdate) return 1;;
        esac
    done
}

snapshot_processes() {
    : > "$B/processes"
    : > "$B/parents"
    for proc in /proc/[0-9]*; do
        [ -r "$proc/stat" ] || continue
        awk '{print $1, $4}' "$proc/stat" >> "$B/parents" || continue
        current=$(readlink "$proc/exe") || continue
        kind=stop
        case "$current" in
            /opt/rockrobo/watchdog/WatchDoge) kind=keep; expected='WatchDoge /opt/rockrobo/watchdog ';;
            /opt/rockrobo/rrlog/rrlogd) kind=keep; expected='rrlogd /opt/rockrobo/rrlog/rrlog.conf ';;
            /opt/rockrobo/wlan/wlanmgr) kind=keep; expected='wlanmgr ';;
            /usr/sbin/dropbear)
                # Connection children retain the master's argv; pin only the init-owned master.
                [ "$(awk '{print $4}' "$proc/stat")" = 1 ] || continue
                [ "$(tr '\000' ' ' < "$proc/cmdline")" = '/usr/sbin/dropbear -F ' ] || continue
                kind=keep; expected='/usr/sbin/dropbear -F ';;
            /mnt/data/valetudo) expected='/mnt/data/valetudo ';;
            /opt/rockrobo/cleaner/bin/rr_loader) expected='rr_loader -d ';;
            /opt/rockrobo/cleaner/bin/RoboController) expected='RoboController ';;
            /opt/rockrobo/cleaner/bin/AppProxy) expected='AppProxy ';;
            /opt/rockrobo/cleaner/bin/SysUpdate) expected='SysUpdate ';;
            /opt/rockrobo/miio/miio_client) expected='miio_client -d /mnt/data/miio/ -l 1 ';;
            /opt/rockrobo/rriot/rriot_rr) expected='rriot_rr -d ';;
            *) continue;;
        esac
        [ "$(tr '\000' ' ' < "$proc/cmdline")" = "$expected" ] || return 1
        record "$kind" "${proc##*/}"
    done
    for required in /mnt/data/valetudo /opt/rockrobo/watchdog/WatchDoge /opt/rockrobo/rrlog/rrlogd \
        /opt/rockrobo/wlan/wlanmgr /usr/sbin/dropbear /opt/rockrobo/cleaner/bin/rr_loader \
        /opt/rockrobo/cleaner/bin/RoboController /opt/rockrobo/cleaner/bin/AppProxy; do
        [ "$(awk -F '|' -v path="$required" '$6 == path {n++} END {print n+0}' "$B/processes")" = 1 ] || return 1
    done
    # Retain child identities even if stopping their parent reparents them.
    awk -F '[| ]' 'FNR == NR {if ($1 == "stop") blocked[$2]=1; next} {parent[$1]=$2}
        END {for (pid in parent) {p=parent[pid]; for (n=0; n<64 && p>1; n++) {
            if (p in blocked) {if (!(pid in blocked)) print pid; break} p=parent[p]
        }}}' "$B/processes" "$B/parents" > "$B/children"
    while read -r child; do record child "$child"; done < "$B/children"
}

prepare() {
    [ "$(id -u)" = 0 ]
    grep -q '^ROBOROCK_VERSION=4.3.5_1612$' /etc/os-release
    md5sum -c "$TOOLS/profile.md5" >/dev/null
    [ -f "$E" ] && [ -s "$E" ] && [ ! -L "$E" ]
    if grep -q -e 'cfg_by=tuya' -e 'cfg_by=rriot' /mnt/data/miio/wifi.conf; then
        echo 'Unsupported Wi-Fi configuration.' >&2
        exit 1
    fi
    [ "$(df -Pk /mnt/data | awk 'END {print $4}')" -ge 20480 ]
    cat /proc/sys/kernel/random/boot_id > "$B/boot-id"
    cp -p "$E" "$B/exclude.original"
    tar -cpf "$B/original-exclusions.tar" -C /mnt/data/rockrobo exclude_process.conf
    {
        cat "$B/exclude.original"
        printf '\nrr_l\nRoboC\nAppP\nmiio\nSysU\nrriot\n'
    } > "$B/exclusions.content"
    [ "$(wc -c < "$B/exclusions.content")" -le 63 ]
    snapshot_processes
    chmod 700 "$TOOLS/map-maint"
    (cd "$B"
        md5sum boot-id exclude.original original-exclusions.tar > original.md5
        md5sum editor-tools/session.sh exclusions.content processes > inputs.md5
    )
    sync
}

stop() {
    LD_LIBRARY_PATH=/lib:/lib/arm-linux-gnueabihf:/usr/lib:/usr/lib/arm-linux-gnueabihf:/opt/rockrobo/cleaner/lib:/mnt/default
    export LD_LIBRARY_PATH
    [ "$(cat "$B/boot-id")" = "$(cat /proc/sys/kernel/random/boot_id)" ]
    (cd "$TOOLS"; md5sum -c tools.md5) >/dev/null
    md5sum -c "$TOOLS/profile.md5" >/dev/null
    (cd "$B"; md5sum -c original.md5; md5sum -c inputs.md5) >/dev/null
    cmp "$E" "$B/exclude.original"
    tar -cpf "$B/preflight-exclusions.tar" -C /mnt/data/rockrobo exclude_process.conf
    cmp "$B/original-exclusions.tar" "$B/preflight-exclusions.tar"
    while IFS='|' read -r kind pid tick hash cmd exe; do
        process_is "$pid" "$tick" "$hash" "$cmd" "$exe"
    done < "$B/processes"

    # Stop command producers before excluding vendor hosts; keep management alive.
    valetudo=$(awk -F '|' '$6 == "/mnt/data/valetudo" {print $2}' "$B/processes")
    kill -TERM "$valetudo"
    n=0
    while [ -e "/proc/$valetudo/exe" ]; do
        n=$((n + 1)); [ "$n" -le 8 ]
        sleep 1
    done
    protected_alive
    "$TOOLS/map-maint" exclusions "$B/exclude.original" "$B/exclusions.content"
    n=0
    until blocked_absent; do
        n=$((n + 1)); [ "$n" -le 8 ]
        sleep 1
    done
    protected_alive
    cmp "$E" "$B/exclusions.content"
    "$TOOLS/map-maint" mcu-disable > "$B/mcu-disable.log" 2>&1
    blocked_absent
    protected_alive
}

case "$phase" in
    prepare) prepare;;
    stop) stop;;
    *) echo "Unknown phase: $phase" >&2; exit 1;;
esac
