<script lang="ts">
  import { onMount } from 'svelte'
  import { loadMap, type RobotMap } from './lib/maps'
  import MapViewer from './MapViewer.svelte'
  import { loadSession, saveSession, saveView } from './lib/session'
  import type { View } from './lib/view'

  let hostname = $state('')
  let loading = $state(false)
  let error = $state('')
  let map = $state<RobotMap | null>(null)
  let source = $state('')
  let sessionId = $state('')
  let initialView = $state<View>()
  let revision = 0

  onMount(() => {
    try { hostname = localStorage.getItem('robot-hostname') ?? '' } catch { /* Storage may be disabled. */ }
    void loadSession().then(saved => {
      if (!saved || revision) return
      map = saved.map
      source = saved.source
      sessionId = saved.id
      initialView = saved.view
      hostname ||= saved.source
    }).catch(() => {})
  })

  function rememberView(view: View) {
    if (!sessionId) return
    void saveView(sessionId, view).catch(() => {})
  }

  async function openMap(event: SubmitEvent) {
    event.preventDefault()
    if (loading) return

    const host = hostname.trim()
    revision++
    loading = true
    error = ''
    try {
      try { localStorage.setItem('robot-hostname', host) } catch { /* Loading works without storage. */ }
      const loaded = await loadMap(host)
      const session = { id: crypto.randomUUID(), source: host, map: loaded }
      await saveSession(session).catch(() => {})
      sessionId = session.id
      initialView = undefined
      map = loaded
      source = host
    } catch (cause) {
      error = cause instanceof Error ? cause.message : 'Map loading failed.'
    } finally {
      loading = false
    }
  }
</script>

<div class="flex h-dvh flex-col bg-base-200">
  <header class="flex flex-wrap items-center gap-4 border-b border-base-300 bg-base-100 px-4 py-3">
    <h1 class="mr-auto text-lg font-semibold">S7 Map Editor</h1>
    <form onsubmit={openMap} class="flex flex-wrap items-center gap-2">
      <label for="hostname" class="text-sm">Robot hostname</label>
      <input id="hostname" class="input input-sm w-48" bind:value={hostname}
        placeholder="robot.local" required disabled={loading} />
      <button class="btn btn-primary btn-sm" disabled={loading || !hostname.trim()}>
        {loading ? 'Loading…' : 'Load map'}
      </button>
    </form>
  </header>

  {#if error}<p class="alert alert-error m-4" role="alert">{error}</p>{/if}

  <main class="flex min-h-0 flex-1 justify-center" aria-busy={loading}>
    {#if map}
      <MapViewer {map} {source} {initialView} onview={rememberView} />
    {:else}
      <p class="self-center text-sm text-base-content/50">No map loaded</p>
    {/if}
  </main>
</div>
