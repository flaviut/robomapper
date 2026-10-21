<script lang="ts">
  import { onMount } from 'svelte'
  import { loadMap, type RobotMap } from './lib/maps'

  let hostname = $state('')
  let loading = $state(false)
  let error = $state('')
  let map = $state<RobotMap | null>(null)
  let source = $state('')
  let canvas = $state<HTMLCanvasElement>()

  onMount(() => {
    try { hostname = localStorage.getItem('robot-hostname') ?? '' } catch { /* Storage may be disabled. */ }
  })

  $effect(() => {
    if (!map || !canvas) return

    const context = canvas.getContext('2d')
    if (!context) return

    const image = context.createImageData(map.width, map.height)
    for (let i = 0; i < map.cells.length; i++) {
      image.data.set([map.cells[i]!, map.cells[i]!, map.cells[i]!, 255], i * 4)
    }
    context.putImageData(image, 0, 0)
  })

  async function openMap(event: SubmitEvent) {
    event.preventDefault()
    if (loading) return

    const host = hostname.trim()
    loading = true
    error = ''
    try {
      try { localStorage.setItem('robot-hostname', host) } catch { /* Loading works without storage. */ }
      const loaded = await loadMap(host)
      map = loaded
      source = host
    } catch (cause) {
      error = cause instanceof Error ? cause.message : 'Map loading failed.'
    } finally {
      loading = false
    }
  }
</script>

<div class="flex min-h-dvh flex-col bg-base-200">
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

  <main class="flex min-h-80 flex-1 items-center justify-center p-4" aria-busy={loading}>
    {#if map}
      <canvas bind:this={canvas} width={map.width} height={map.height}
        class="h-auto max-w-full [image-rendering:pixelated]"
        aria-label="Map from {source}"></canvas>
    {:else}
      <p class="text-sm text-base-content/50">No map loaded</p>
    {/if}
  </main>
</div>
