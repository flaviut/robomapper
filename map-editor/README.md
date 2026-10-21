# S7 Map Editor

Edit a robot’s occupancy map and room IDs, then save the changes over SSH.

## Develop

Requires Nix with flakes and direnv with nix-direnv integration.

```sh
cd map-editor
direnv allow
pnpm install --frozen-lockfile
pnpm dev
```

Open the localhost URL printed by Vite. The locked flake provides Node.js, pnpm, and OpenSSH. Without direnv, run `nix develop` in this directory instead.

## Load a robot map

First establish root SSH key access and verify the robot’s host key through a trusted channel:

```sh
ssh root@robot.local
```

Enter that hostname in the editor and select **Load map**. The helper reads `/mnt/data/rockrobo/last_map`, checks its header, dimensions, and grid MD5, then displays the raw grayscale raster without flipping or thresholding cells. The hostname is saved in browser local storage; the backend keeps no robot configuration. SSH uses your local keys, agent, and SSH configuration, with password prompts and automatic host-key acceptance disabled.

Keep the robot idle during reading. Loading is read-only; a live raster is not a consistent matching-set backup.

## Save changes

**Save** installs the edits and restarts the loaded robot after confirmation. It updates the runtime and catalog-selected primary map pairs, preserving the genuine backup and other files. Room names remain unchanged.

Save runs [`save.sh`](../tools/map-maint/save.sh): stop writers, back up the files off-device, install the edits, and reboot. The bundled native helper performs the vendor stop sequence. No manual setup is required. The supported firmware is `4.3.5_1612`.

Keep the robot idle and avoid commands, scheduled cleaning, or updates until restart verification finishes. The editor does not query or alter Wi-Fi, schedules, or updater settings.

If writing fails, the script restores the affected files before rebooting. A changed source map or room grid aborts the save rather than overwriting newer data. Stages, robot output, SSH exit codes, and failures are logged to server stdout; the robot also retains `save.log` beside its backup.

Backups and receipts stay under `$XDG_STATE_HOME/map-editor/backups/`, or `~/.local/state/map-editor/backups/`. Keep them until you have inspected the restarted robot. Saving never starts cleaning. Uninterrupted power remains required; software rollback does not repair power loss during replacement.

Edited-map installation still needs hardware validation. A valid file does not establish safe navigation; follow the [edit constraints](../docs/reference/maps/editing.md).

## Checks

```sh
pnpm test
pnpm check
pnpm build
pnpm preview
```

The build includes type checks and writes `dist/`. Use `pnpm dev` or `pnpm preview` for SSH loading; serving `dist/` alone does not provide the backend. Keep the helper bound to localhost. It accepts only same-origin JSON requests. Dependencies require internet access on first installation; the UI has no external runtime assets or service worker.

## Structure

Generated with `pnpm create vite … --template svelte-ts` (create-vite 9.3.1). The generated Svelte and TypeScript configuration is retained; demo content is replaced with the editor shell.

- `src/App.svelte`: hostname form, raster preview, and map details.
- `src/lib/maps.ts`: frontend map API.
- `server/api.ts`: local HTTP boundary, registered by Vite for development and preview.
- `server/map.ts`: map loading and integrity checks.
- `server/deploy.ts`: save, backup and restart orchestration.
- `server/ssh.ts`: bounded SSH transport.

Keep binary codecs and editor logic independent of UI components. Follow the [occupancy edit constraints](../docs/reference/maps/editing.md): preserve the frame, originals, and companion files. A valid file does not establish safe navigation.
