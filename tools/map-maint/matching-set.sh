#!/bin/sh
# File operations only: callers own service exclusion, MCU hold-off and recovery.
set -eu
umask 077

fail() {
    printf '%s\n' "$*" >&2
    exit 1
}

[ "$#" = 3 ] || fail "Usage: $0 capture|check|install|apply|verify|rollback ROOT WORK"
action=$1
case "$action" in capture|check|install|apply|verify|rollback) ;; *) fail 'Unknown action';; esac
[ -d "$2" ] && [ ! -L "$2" ] || fail 'ROOT must be a real directory'
ROOT=$(cd "$2" && pwd -P)
[ "$ROOT" != / ] || fail 'ROOT cannot be /'
parent=$(cd "$(dirname "$3")" && pwd -P)
base=$(basename "$3")
case "$base" in ''|.|..|*[!a-zA-Z0-9._-]*) fail 'Use a simple WORK basename';; esac
WORK=$parent/$base
case "$WORK/" in "$ROOT/"*) fail 'WORK must be outside ROOT';; esac
case "$ROOT/" in "$WORK/"*) fail 'ROOT must be outside WORK';; esac
W=$WORK/snapshot

namespace() {
    printf '%s\n' last_map last_vmap mobility_test_vmap
    for n in 0 1 2 3 4 5 6 7 8 9; do
        printf '%s\n' "user_map$n" "user_vmap$n"
    done
    for n in 0 1 2 3 4 5 6 7 8 9 10 11; do
        printf '%s\n' "PersistData_$n.data"
    done
    printf '%s\n' SharedMultiMapInfo slam_info.cfg \
        robot.db robot.db-journal robot.db-wal robot.db-shm \
        appproxy.map StartPos.data ChargerPos.data ChargerType.data Rotater.cfg \
        RoboController.cfg robot.setting lab.cfg map
}

# Refuse live hosts or surviving handles; this is not an atomic writer barrier.
stopped() {
    for p in /proc/[0-9]*; do
        exe=$(readlink "$p/exe") || continue
        case "${exe##*/}" in
            valetudo|rr_loader|RoboController|RoboControllerR|RoboControllerM|\
            AppProxy|miio_client|rriot_rr|rriot_tuya|SysUpdate)
                fail "Host still running: $p $exe";;
        esac
        if [ -r "$p/maps" ] && grep -Fq "$ROOT/" "$p/maps"; then
            fail "Mapped files remain: $p"
        fi
        for fd in "$p"/fd/*; do
            target=$(readlink "$fd") || continue
            case "$target" in "$ROOT/"*) ;; *) continue;; esac
            relative=${target#"$ROOT/"}
            while IFS= read -r name; do
                case "$relative" in
                    "$name"|"$name/"*|"$name (deleted)"|"$name.cache"|"$name.tmp"*)
                        fail "Open managed file: $fd";;
                esac
            done <<EOF
$(namespace)
EOF
        done
    done
}

member_ok() {
    path=$1
    name=$2
    [ ! -L "$path" ] || fail "Symlink refused: $path"
    if [ "$name" != map ]; then
        [ -f "$path" ] || fail "Not a regular file: $path"
        return
    fi
    [ -d "$path" ] && [ -z "$(ls -A "$path")" ] || fail 'Only an empty map/ is supported'
}

hashes() {
    (
        cd "$W"
        md5sum root namespace present absent interrupted files.tar
        [ ! -s interrupted ] || md5sum interrupted.tar
    )
}

check_set() {
    [ -f "$WORK/capture.complete" ] || fail 'Capture is incomplete'
    [ "$(cat "$W/root")" = "$ROOT" ] || fail 'Snapshot belongs to another ROOT'
    namespace > "$WORK/expected-namespace"
    cmp "$WORK/expected-namespace" "$W/namespace"
    cat "$W/present" "$W/absent" | sort > "$WORK/partition"
    sort "$W/namespace" > "$WORK/sorted-namespace"
    cmp "$WORK/partition" "$WORK/sorted-namespace"
    hashes > "$WORK/check.md5"
    cmp "$WORK/snapshot.md5" "$WORK/check.md5"
    # Restrict extraction to flat regular files and the empty map directory.
    tar -tf "$W/files.tar" > "$WORK/archive-names"
    awk '{sub(/\/$/, ""); print}' "$WORK/archive-names" > "$WORK/archive-members"
    cmp "$W/present" "$WORK/archive-members"
    tar -tvf "$W/files.tar" > "$WORK/archive-metadata"
    awk 'substr($1, 1, 1) != "-" && substr($1, 1, 1) != "d" {exit 1}' \
        "$WORK/archive-metadata" || fail 'Archive links or special files refused'
}

pack() {
    directory=$1
    destination=$2
    set --
    while IFS= read -r name; do set -- "$@" "$name"; done < "$W/present"
    [ "$#" -gt 0 ] || fail 'Empty snapshot refused'
    tar -cpf "$destination" -C "$directory" "$@"
}

verify() {
    while IFS= read -r name; do
        member_ok "$ROOT/$name" "$name"
    done < "$W/present"
    while IFS= read -r name; do
        [ ! -e "$ROOT/$name" ] && [ ! -L "$ROOT/$name" ] || fail "Expected absence: $name"
    done < "$W/absent"
    pack "$ROOT" "$WORK/verified.tar"
    reference=$W/files.tar
    if [ -f "$WORK/candidate.tar" ] && [ ! -e "$WORK/rollback.started" ]; then
        (cd "$WORK" && md5sum -c candidate.md5)
        reference=$WORK/candidate.tar
    fi
    cmp "$reference" "$WORK/verified.tar"
}

stage() {
    directory=$1
    mkdir -m 700 "$directory"
    tar -xpf "$W/files.tar" -C "$directory"
    while IFS= read -r name; do
        member_ok "$directory/$name" "$name"
    done < "$W/present"
    pack "$directory" "$WORK/stage-check.tar"
    cmp "$W/files.tar" "$WORK/stage-check.tar"
}

install_stage() {
    directory=$1
    while IFS= read -r name; do
        mv "$directory/$name" "$ROOT/$name"
    done < "$W/present"
    verify
    stopped
    sync
}

if [ "$action" = capture ]; then
    [ ! -e "$WORK" ] && [ ! -L "$WORK" ] || fail 'WORK already exists'
    stopped
    mkdir -m 700 "$WORK" "$W"
    [ "$(stat -c %d "$ROOT")" = "$(stat -c %d "$WORK")" ] || fail 'Use the same filesystem'
    printf '%s\n' "$ROOT" > "$W/root"
    namespace > "$W/namespace"
    : > "$W/present"
    : > "$W/absent"
    : > "$W/interrupted"
    set --
    while IFS= read -r name; do
        if [ -e "$ROOT/$name" ] || [ -L "$ROOT/$name" ]; then
            member_ok "$ROOT/$name" "$name"
            printf '%s\n' "$name" >> "$W/present"
        else
            printf '%s\n' "$name" >> "$W/absent"
        fi
        for path in "$ROOT/$name".cache "$ROOT/$name".tmp*; do
            if [ -e "$path" ] || [ -L "$path" ]; then
                member_ok "$path" interrupted
                printf '%s\n' "${path##*/}" >> "$W/interrupted"
                set -- "$@" "${path##*/}"
            fi
        done
    done < "$W/namespace"
    # Limit disk use before copying; leave room for staging and rollback too.
    size=$(
        cat "$W/present" "$W/interrupted" | while IFS= read -r name; do
            du -sk "$ROOT/$name"
        done | awk '{total += $1} END {print total + 0}'
    )
    available=$(df -Pk "$WORK" | awk 'END {print $4}')
    [ "$available" -ge "$((size * 4 + 8192))" ] || fail 'Insufficient free space'
    [ "$#" = 0 ] || tar -cpf "$W/interrupted.tar" -C "$ROOT" "$@"
    pack "$ROOT" "$W/files.tar"
    stopped
    hashes > "$WORK/snapshot.md5"
    sync
    printf 'Stopped snapshot acquired.\n' > "$WORK/capture.complete"
    sync
    exit 0
fi

[ -d "$WORK" ] && [ ! -L "$WORK" ] || fail 'WORK must be a real directory'
[ -d "$W" ] && [ ! -L "$W" ] || fail 'Missing snapshot directory'
[ "$(stat -c %d "$ROOT")" = "$(stat -c %d "$WORK")" ] || fail 'Use the same filesystem'
check_set
[ "$action" != check ] || exit 0
stopped
[ "$action" != verify ] || { verify; exit 0; }

if [ "$action" = install ] || [ "$action" = apply ]; then
    [ ! -e "$WORK/install.started" ] || fail 'Installation already started; inspect or roll back'
    [ -f "$WORK/offdevice.verified" ] || fail 'Verify an off-device copy before installation'
    [ ! -e "$WORK/candidate.tar" ] || fail 'Candidate already exists'
    stage "$WORK/stage"
    if [ "$action" = apply ]; then
        [ -f "$WORK/patch.ready" ] || fail 'Missing verified patch'
        [ -d "$WORK/patch" ] && [ ! -L "$WORK/patch" ] || fail 'Invalid patch directory'
        [ "$(wc -l < "$WORK/patch.files")" -eq 4 ] || fail 'Expected runtime and primary pairs'
        primary=$(grep '^user_map[0-3]$' "$WORK/patch.files")
        case "$primary" in user_map[0-3]) ;; *) fail 'Invalid primary patch';; esac
        flag=$((${primary#user_map} + 2))
        printf '%s\n' last_map PersistData_1.data "$primary" "PersistData_$flag.data" | sort > "$WORK/expected-patch"
        sort "$WORK/patch.files" > "$WORK/sorted-patch"
        cmp "$WORK/expected-patch" "$WORK/sorted-patch"
        (cd "$WORK/patch" && md5sum -c ../patch.md5)
        while IFS= read -r name; do
            member_ok "$WORK/patch/$name" "$name"
            member_ok "$WORK/stage/$name" "$name"
            cat "$WORK/patch/$name" > "$WORK/stage/$name"
            touch -r "$ROOT/$name" "$WORK/stage/$name"
            cmp "$WORK/patch/$name" "$WORK/stage/$name"
        done < "$WORK/patch.files"
        pack "$WORK/stage" "$WORK/candidate.tar"
        (cd "$WORK" && md5sum candidate.tar > candidate.md5)
        sync
    fi
    mkdir -m 700 "$WORK/quarantine" "$WORK/interrupted-work"
    printf 'Whole-set installation begun.\n' > "$WORK/install.started"
    sync
    while IFS= read -r name; do
        if [ -e "$ROOT/$name" ] || [ -L "$ROOT/$name" ]; then
            mv "$ROOT/$name" "$WORK/quarantine/$name"
        fi
        for path in "$ROOT/$name".cache "$ROOT/$name".tmp*; do
            if [ -e "$path" ] || [ -L "$path" ]; then
                mv "$path" "$WORK/interrupted-work/"
            fi
        done
    done < "$W/namespace"
    install_stage "$WORK/stage"
    printf 'Exact snapshot installed and verified.\n' > "$WORK/install.complete"
    sync
    exit 0
fi

[ -f "$WORK/install.started" ] || fail 'No installation to roll back'
printf 'Restore the original snapshot.\n' > "$WORK/rollback.started"
sync
# Re-extract before removal so recovery can retry an interrupted rollback.
rm -rf "$WORK/rollback-stage"
stage "$WORK/rollback-stage"
if [ ! -e "$WORK/rollback-work" ] && [ ! -L "$WORK/rollback-work" ]; then
    mkdir -m 700 "$WORK/rollback-work"
fi
[ -d "$WORK/rollback-work" ] && [ ! -L "$WORK/rollback-work" ] || fail 'Invalid rollback-work directory'
while IFS= read -r name; do
    # An early quarantine failure can leave work products beside untouched finals.
    for path in "$ROOT/$name".cache "$ROOT/$name".tmp*; do
        if [ -e "$path" ] || [ -L "$path" ]; then
            destination=$WORK/rollback-work/${path##*/}
            [ ! -e "$destination" ] && [ ! -L "$destination" ] || fail 'Rollback work collision'
            mv "$path" "$destination"
        fi
    done
    rm -rf "${ROOT:?}/${name:?}"
done < "$W/namespace"
install_stage "$WORK/rollback-stage"
printf 'Whole snapshot restored and verified.\n' > "$WORK/rollback.complete"
sync
