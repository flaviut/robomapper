set -eu
umask 077

fail() {
    printf '%s\n' "$1" >&2
    exit 1
}

[ "$(id -u)" = 0 ] || fail 'Root SSH access is required.'
grep -qx 'ROBOROCK_VERSION=4.3.5_1612' /etc/os-release || fail 'Unsupported firmware.'
IFS= read -r key
case "$key" in
    'ssh-ed25519 '*) ;;
    *) fail 'Expected an ED25519 public key.' ;;
esac

dir=/mnt/data/robomapper-ssh
keys="$dir/authorized_keys"
hook=/mnt/reserve/_root.sh
marker='# robomapper SSH authorization'

[ -f "$hook" ] && [ ! -L "$hook" ] || fail 'Expected a regular /mnt/reserve/_root.sh startup hook.'
sh -n "$hook" || fail 'Existing startup hook has invalid syntax.'
[ ! -L "$dir" ] && [ ! -L "$keys" ] || fail 'Refusing symlinked key storage.'

mkdir /tmp/robomapper-authorize.lock || fail 'Another authorization is running; check /tmp/robomapper-authorize.lock.'
tmp=
trap '[ -z "$tmp" ] || rm -f "$tmp"; rmdir /tmp/robomapper-authorize.lock' EXIT

# Keep the firmware key so existing SSH access survives the writable overlay.
mkdir -p "$dir"
chmod 700 "$dir"
if [ ! -e "$keys" ]; then
    cp /root/.ssh/authorized_keys "$keys"
fi
[ -f "$keys" ] || fail 'Expected a regular authorized_keys file.'
chmod 600 "$keys"
if ! grep -qxF "$key" "$keys"; then
    printf '\n%s\n' "$key" >> "$keys"
fi

# Replace the hook atomically, preserving its existing Valetudo configuration.
if ! grep -qxF "$marker" "$hook"; then
    backup="$dir/root-hook.backup"
    [ ! -e "$backup" ] || fail 'A startup-hook backup already exists; inspect it before retrying.'
    cp -p "$hook" "$backup"
    tmp=$(mktemp /mnt/reserve/.robomapper-hook.XXXXXX)
    cp -p "$hook" "$tmp"
    cat >> "$tmp" <<'HOOK'

# robomapper SSH authorization
if [ -s /mnt/data/robomapper-ssh/authorized_keys ]; then
    if ! grep -q ' /root/.ssh/authorized_keys ' /proc/mounts; then
        mount -o bind /mnt/data/robomapper-ssh/authorized_keys /root/.ssh/authorized_keys
    fi
fi
HOOK
    sh -n "$tmp"
    mv "$tmp" "$hook"
    tmp=
fi
sync

if ! grep -q ' /root/.ssh/authorized_keys ' /proc/mounts; then
    mount -o bind "$keys" /root/.ssh/authorized_keys
fi
grep -qxF "$key" /root/.ssh/authorized_keys || fail 'The active key mount differs from robomapper storage; inspect existing mounts.'
printf '%s\n' 'robomapper authorized. Return to Home Assistant and select Submit.'
