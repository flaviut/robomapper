# S7 Map Editor

Edit a robot's native occupancy map and room IDs from Home Assistant. Saving backs up the stopped robot, installs the edits and reboots it. No MQTT or existing vacuum integration is required.

**Saving is experimental. Edited-map installation still needs hardware validation.** Supported firmware: `4.3.5_1612` only. Keep the robot idle and powered throughout saving and restart verification. A valid map file does not establish safe navigation; read the [edit constraints](docs/reference/maps/editing.md).

## Install

Requires Home Assistant 2026.10 or later and root SSH key access to the robot.

1. In HACS, add `https://github.com/flaviut/robomapper` under **Custom repositories**, category **Integration**.
2. Download **S7 Map Editor** and restart Home Assistant.
3. Place a dedicated, unencrypted SSH private key at `/config/map_editor/id_ed25519` inside Home Assistant. Restrict the directory to mode `700` and the key to `600`. Its public key must already be authorized for root on the robot.
4. Verify the robot's SSH host-key fingerprint through a trusted connection. Use its `SHA256:…` fingerprint, not the client key's fingerprint. Changed host keys are rejected.
5. Under **Settings → Devices & services → Add integration**, select **S7 Map Editor**. Enter the robot address, port, private-key path and trusted fingerprint.

The key path must be accessible to the Home Assistant process. A key held only inside a separate SSH add-on or on your laptop is not enough. Home Assistant backups may include this key; protect those backups accordingly.

Open **S7 Map Editor** in the sidebar as an administrator. Select the configured robot and choose **Load map**. Edit, then choose **Save** and confirm the restart. The browser needs no SSH credentials. No Node server or add-on runs in Home Assistant.

You may select an existing vacuum entity during setup or **Reconfigure**. This only adds **Open vacuum**, which opens Home Assistant's entity dialog. The editor neither reads its status nor sends it commands. Keep the configured robot address when reconfiguring; add a new entry for a different address.

## Saving and backups

Only one save can run at a time, even if the same robot is configured under two addresses. Closing or reloading the editor does not stop it; reopening the editor reconnects to its progress. Reconfiguration and unloading are refused during a save.

Saving overwrites the robot's map even if it changed since loading. Avoid commands, scheduled cleaning and updates until verification finishes. The editor does not change schedules or updater settings.

Backups are stored under `<HA config>/map_editor/backups/<save ID>/`, outside the integration directory:

- `untouched-stopped-backup.tar`: original robot files, persisted before installation is authorized.
- `candidate.tar`: edited files sent to the robot.
- `request.json`: source fingerprint and robot work directory.
- `receipt.json`: successful restart verification.

Keep backups until you have inspected the restarted robot. They are not automatically deleted or exposed as public downloads. The robot also retains its work directory and `save.log` under `/mnt/data/map-editor-<save ID>/`.

If Home Assistant restarts or the connection fails, the outcome may be unknown. There is no automatic retry or recovery job. Check the robot and its log before trying again. The robot script attempts rollback on installation failure, but software rollback cannot repair power loss during replacement. For manual recovery, use the [matching-set restore guide](docs/guides/matching-set-restore.md).

## Development

The Svelte source remains in `map-editor/`. The Python backend and bundled release assets live in `custom_components/map_editor/`.

```sh
cd map-editor
nix develop
pnpm install --frozen-lockfile
pnpm build:hass
pnpm test
pnpm test:ui
```

Browser tests require Chromium, either on `PATH` or set through `CHROMIUM_PATH`. `pnpm test:ui` checks both the standalone editor and the compiled HA panel. For the standalone development server, see [map-editor/README.md](map-editor/README.md).

Run backend tests with Python 3.14:

```sh
python3.14 -m venv .venv
.venv/bin/pip install -r tests/requirements.txt
.venv/bin/python -m unittest discover -s tests -v
```

Tests use synthetic native files, a local SSH server and Home Assistant 2026.10.2. They never connect to a real robot. The robot executable runs only on the robot, not the HA host.

After changing the robot tools, copy `tools/map-maint/save.sh` and `tools/map-maint/bin/map-maint` into `custom_components/map_editor/tools/`. Rebuild and commit the frontend after UI changes. Tests check that the packaged robot tools match their sources.

## Publish

Keep the compiled frontend and robot tools in the published tree; HACS installs only `custom_components/map_editor/`. Increment the manifest version for releases. Public HACS directory inclusion is separate from installing a custom repository.
