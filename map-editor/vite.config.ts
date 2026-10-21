import tailwindcss from '@tailwindcss/vite'
import { svelte } from '@sveltejs/vite-plugin-svelte'
import { defineConfig } from 'vite'
import { mapApi } from './server/api.ts'

// https://vite.dev/config/
export default defineConfig(({ mode }) => ({
  plugins: [tailwindcss(), svelte(), ...(mode === 'hass' ? [] : [mapApi()])],
  base: './',
  server: { host: '127.0.0.1' },
  preview: { host: '127.0.0.1' },
  ...(mode === 'hass' ? {
    build: {
      outDir: '../custom_components/map_editor/frontend',
      emptyOutDir: true,
      lib: { entry: 'src/panel.ts', formats: ['es'], fileName: 'panel', cssFileName: 'panel' },
    },
  } : {}),
}))
