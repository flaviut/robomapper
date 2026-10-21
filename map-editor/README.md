# S7 Map Editor

Offline map editor scaffold using Svelte, TypeScript, Vite, Tailwind, and daisyUI’s dark theme. File loading, canvas rendering, editing, and export are not implemented; their controls are disabled.

## Develop

Requires Nix with flakes and direnv with nix-direnv integration.

```sh
cd map-editor
direnv allow
pnpm install --frozen-lockfile
pnpm dev
```

Open the localhost URL printed by Vite. The locked flake provides Node.js and pnpm; no Corepack or global JavaScript tools are needed. Without direnv, run `nix develop` in this directory instead.

```sh
pnpm check
pnpm build
pnpm preview
```

The build includes type checks and writes `dist/`. Serve that directory with a local HTTP server for offline use; `file://` is unsupported. Dependencies require internet access on first installation, but the built app has no external runtime assets, backend, or robot connection. It does not install a service worker.

## Structure

Generated with `pnpm create vite … --template svelte-ts` (create-vite 9.3.1). The generated Svelte and TypeScript configuration is retained; demo content is replaced with the editor shell.

- `src/App.svelte`: responsive workspace and disabled controls.
- `src/app.css`: Tailwind and daisyUI theme configuration; no custom component CSS.
- `vite.config.ts`: Svelte and Tailwind build plugins.

Keep future binary codecs and editor logic independent of UI components. Follow the [occupancy edit constraints](../docs/reference/maps/editing.md): preserve the frame, originals, and companion files. A valid file does not establish safe navigation.
