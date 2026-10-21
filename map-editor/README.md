# S7 Map Editor

Read a robot’s RRSLAM v2 occupancy map over SSH and preview it locally. Editing and export remain disabled.

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

Keep the robot idle during reading. A live raster is not a consistent matching-set backup, and a valid MD5 does not establish navigation safety. No files are written on the robot.

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
- `server/ssh.ts`: bounded, read-only SSH transport.

Keep binary codecs and editor logic independent of UI components. Follow the [occupancy edit constraints](../docs/reference/maps/editing.md): preserve the frame, originals, and companion files. A valid file does not establish safe navigation.
