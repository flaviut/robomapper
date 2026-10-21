# robomapper standalone development

Run the editor locally to edit a robot’s occupancy map and room IDs over SSH. For Home Assistant installation, see the [project instructions](../README.md).

## Develop

Requires Nix with flakes. With direnv and nix-direnv installed:

```sh
cd map-editor
direnv allow
pnpm install --frozen-lockfile
pnpm dev
```

Without direnv, run `nix develop` in `map-editor` before the pnpm commands. The locked flake provides Node.js, pnpm, and OpenSSH. Open the localhost URL printed by Vite.

## Load and save

Set up root SSH key access, then verify the connection:

```sh
ssh -o BatchMode=yes root@robot.local
```

Enter the robot’s hostname in the editor and select **Load map**. The local backend uses your SSH keys, agent, and SSH configuration.

Edit the map, then select **Save** and confirm to install the changes and restart the robot.

Backups and receipts are stored under `$XDG_STATE_HOME/map-editor/backups/`, or `~/.local/state/map-editor/backups/`. Check server stdout for save stages and errors.

## Checks

```sh
pnpm test
pnpm check
pnpm build
pnpm preview
```

The build writes `dist/`. Use `pnpm dev` or `pnpm preview` to run both the editor and its local SSH backend.
