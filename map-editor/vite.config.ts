import tailwindcss from '@tailwindcss/vite'
import { svelte } from '@sveltejs/vite-plugin-svelte'
import { defineConfig } from 'vite'
import { mapApi } from './server/api.ts'

// https://vite.dev/config/
export default defineConfig({
  plugins: [tailwindcss(), svelte(), mapApi()],
  base: './',
  server: { host: '127.0.0.1' },
  preview: { host: '127.0.0.1' },
})
