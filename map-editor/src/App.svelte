<script lang="ts">
  import { onMount } from 'svelte'
  import { loadMap, saveMap, saveStatus, type RobotMap } from './lib/maps'
  import { inHass, request, type RobotEntry } from './lib/hass'
  import MapViewer from './MapViewer.svelte'
  import { loadSession, saveSession, saveView, saveDraft } from './lib/session'
  import type { View } from './lib/view'

  const homeAssistant = inHass()
  let entries = $state<RobotEntry[]>([])
  let hostname = $state('')
  let loading = $state(false)
  let error = $state('')
  let map = $state<RobotMap | null>(null)
  let source = $state('')
  const sourceName = $derived(homeAssistant ? entries.find(entry => entry.id === source)?.name ?? source : source)
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
    if (!homeAssistant) {
      try { hostname = localStorage.getItem('robot-hostname') ?? '' } catch { /* Storage may be disabled. */ }
    }
    void (async () => {
      if (homeAssistant) entries = await request<RobotEntry[]>('entries')
      const saved = await loadSession().catch(() => null)
      if (revision) return
      if (saved && (!homeAssistant || entries.some(entry => entry.id === saved.source))) {
        map = saved.map
        source = saved.source
        sessionId = saved.id
        initialView = saved.view
        initialCells = saved.draft
        initialRooms = saved.draftRooms
        hostname ||= saved.source
      }
      if (!homeAssistant) return
      hostname ||= entries[0]?.id ?? ''
      await resumeSave()
    })().catch(cause => { error = cause instanceof Error ? cause.message : 'Could not connect to Home Assistant.' })
  })

  async function resumeSave() {
    if (!homeAssistant || !hostname || action !== 'idle') return
    const host = hostname
    let current = await saveStatus(host)
    if (current.state !== 'saving') {
      if (current.state === 'error') error = current.error ?? 'Check the robot before retrying.'
      return
    }
    action = 'save'
    try {
      while (current.state === 'saving') {
        status = current.stage
        await new Promise(resolve => setTimeout(resolve, 2000))
        current = await saveStatus(host)
      }
      if (current.state !== 'done') throw new Error(current.error ?? 'Save interrupted. Check the robot before retrying.')
      await adoptMap(await loadMap(host), host)
      status = 'Saved. Robot restarted.'
    } catch (cause) {
      error = cause instanceof Error ? cause.message : 'Could not check save progress.'
    } finally { action = 'idle' }
  }

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
      const installed = await saveMap(source, map, draft?.cells ?? initialCells ?? map.cells, draft?.rooms ?? initialRooms ?? map.rooms,
        current => { status = current.stage })
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
      if (!homeAssistant) {
        try { localStorage.setItem('robot-hostname', host) } catch { /* Loading works without storage. */ }
      }
      const loaded = await loadMap(host)
      await adoptMap(loaded, host)
    } catch (cause) {
      error = cause instanceof Error ? cause.message : 'Map loading failed.'
    } finally {
      loading = false
    }
  }
</script>

<div data-theme="dark" class="flex h-dvh flex-col bg-base-200">
  {#snippet controls()}
    <div class="flex flex-wrap items-center gap-2">
    <form onsubmit={openMap} class="flex flex-wrap items-center gap-2">
      {#if homeAssistant}
        <label for="robot" class="text-sm">Robot</label>
        <select id="robot" class="select select-sm w-48" bind:value={hostname}
          onchange={() => { void resumeSave().catch(cause => { error = String(cause) }) }}
          disabled={loading || action !== 'idle'}>
          {#each entries as entry}<option value={entry.id}>{entry.name}</option>{/each}
        </select>
      {:else}
        <label for="hostname" class="text-sm">Robot hostname</label>
        <input id="hostname" class="input input-sm w-48" bind:value={hostname}
          placeholder="robot.local" required disabled={loading || action !== 'idle'} />
      {/if}
      <button class="btn btn-primary btn-sm" disabled={loading || action !== 'idle' || !hostname.trim()}>
        {loading ? 'Loading…' : 'Load map'}
      </button>
    </form>
    <button class="btn btn-sm" disabled={!map || loading || action !== 'idle'} onclick={() => confirmation?.showModal()}>
      {action === 'save' ? 'Saving…' : 'Save'}
    </button>
    </div>
  {/snippet}

  {#if error}<p class="alert alert-error m-4" role="alert">{error}</p>{/if}
  {#if status}<p class="px-4 py-2 text-sm" role="status">{status}</p>{/if}

  <main class="flex min-h-0 flex-1 justify-center" aria-busy={loading || action !== 'idle'} inert={action !== 'idle'}>
    {#if map}
      {#key sessionId}
        <MapViewer {controls} {map} source={sourceName} {initialView} {initialCells} {initialRooms} onview={rememberView} onedit={rememberEdit} />
      {/key}
    {:else}
      <div class="flex min-h-0 flex-1 flex-col">
        <div class="flex justify-end border-b border-base-300 bg-base-100 px-4 py-3">
          {@render controls()}
        </div>
        <p class="flex flex-1 items-center justify-center text-sm text-base-content/50">No map loaded</p>
      </div>
    {/if}
  </main>
  <dialog bind:this={confirmation} class="modal" aria-labelledby="save-title">
    <div class="modal-box">
      <h2 id="save-title" class="text-lg font-semibold">Save changes?</h2>
      <p class="py-4">Save changes to {sourceName} and restart the robot?</p>
      <div class="modal-action">
        <button class="btn btn-sm" onclick={() => confirmation?.close()}>Cancel</button>
        <button class="btn btn-primary btn-sm" onclick={save}>Save and restart</button>
      </div>
    </div>
    <form method="dialog" class="modal-backdrop"><button aria-label="Close">Close</button></form>
  </dialog>
</div>
