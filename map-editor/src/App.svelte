<script lang="ts">
  import { onMount } from 'svelte'
  import { loadMap, saveMap, type RobotMap } from './lib/maps'
  import MapViewer from './MapViewer.svelte'
  import { loadSession, saveSession, saveView, saveDraft } from './lib/session'
  import type { View } from './lib/view'

  let hostname = $state('')
  let loading = $state(false)
  let error = $state('')
  let map = $state<RobotMap | null>(null)
  let source = $state('')
  let sessionId = $state('')
  let initialView = $state<View>()
  let initialCells = $state<Uint8Array>()
  let initialRooms = $state<Uint8Array>()
  let revision = 0
  let action = $state<'idle' | 'save'>('idle')
  let status = $state('')
  let draft = $state<{ cells: Uint8Array, rooms: Uint8Array } | null>(null)
  let confirmation = $state<HTMLDialogElement>()

  onMount(() => {
    try { hostname = localStorage.getItem('robot-hostname') ?? '' } catch { /* Storage may be disabled. */ }
    void loadSession().then(saved => {
      if (!saved || revision) return
      map = saved.map
      source = saved.source
      sessionId = saved.id
      initialView = saved.view
      initialCells = saved.draft
      initialRooms = saved.draftRooms
      hostname ||= saved.source
    }).catch(() => {})
  })

  function rememberView(view: View) {
    if (!sessionId) return
    void saveView(sessionId, view).catch(() => {})
  }

  function rememberEdit(cells: Uint8Array, rooms: Uint8Array) {
    draft = { cells: cells.slice(), rooms: rooms.slice() }
    if (!sessionId) return
    void saveDraft(sessionId, cells, rooms).catch(() => {
      error = 'Could not save edits in this browser.'
    })
  }

  async function adoptMap(loaded: RobotMap, host: string) {
    const session = { id: crypto.randomUUID(), source: host, map: loaded }
    await saveSession(session).catch(() => {})
    sessionId = session.id
    initialView = undefined
    initialCells = undefined
    initialRooms = undefined
    draft = null
    map = loaded
    source = host
  }

  async function save() {
    confirmation?.close()
    if (!map || action !== 'idle' || loading) return
    action = 'save'
    revision++
    error = ''
    status = ''
    try {
      const installed = await saveMap(source, map, draft?.cells ?? initialCells ?? map.cells, draft?.rooms ?? initialRooms ?? map.rooms)
      await adoptMap(installed, source)
      status = 'Saved. Robot restarted.'
    } catch (cause) {
      error = cause instanceof Error ? cause.message : 'Could not save the map.'
    } finally { action = 'idle' }
  }

  async function openMap(event: SubmitEvent) {
    event.preventDefault()
    if (loading || action !== 'idle') return

    const host = hostname.trim()
    revision++
    loading = true
    error = ''
    status = ''
    try {
      try { localStorage.setItem('robot-hostname', host) } catch { /* Loading works without storage. */ }
      const loaded = await loadMap(host)
      await adoptMap(loaded, host)
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
        placeholder="robot.local" required disabled={loading || action !== 'idle'} />
      <button class="btn btn-primary btn-sm" disabled={loading || action !== 'idle' || !hostname.trim()}>
        {loading ? 'Loading…' : 'Load map'}
      </button>
    </form>
    <button class="btn btn-sm" disabled={!map || loading || action !== 'idle'} onclick={() => confirmation?.showModal()}>
      {action === 'save' ? 'Saving…' : 'Save'}
    </button>
  </header>

  {#if error}<p class="alert alert-error m-4" role="alert">{error}</p>{/if}
  {#if status}<p class="px-4 py-2 text-sm" role="status">{status}</p>{/if}

  <main class="flex min-h-0 flex-1 justify-center" aria-busy={loading || action !== 'idle'} inert={action !== 'idle'}>
    {#if map}
      {#key sessionId}
        <MapViewer {map} {source} {initialView} {initialCells} {initialRooms} onview={rememberView} onedit={rememberEdit} />
      {/key}
    {:else}
      <p class="self-center text-sm text-base-content/50">No map loaded</p>
    {/if}
  </main>
  <dialog bind:this={confirmation} class="modal" aria-labelledby="save-title">
    <div class="modal-box">
      <h2 id="save-title" class="text-lg font-semibold">Save changes?</h2>
      <p class="py-4">Save changes to {source} and restart the robot?</p>
      <div class="modal-action">
        <button class="btn btn-sm" onclick={() => confirmation?.close()}>Cancel</button>
        <button class="btn btn-primary btn-sm" onclick={save}>Save and restart</button>
      </div>
    </div>
    <form method="dialog" class="modal-backdrop"><button aria-label="Close">Close</button></form>
  </dialog>
</div>
