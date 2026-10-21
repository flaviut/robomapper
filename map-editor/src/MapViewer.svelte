<script lang="ts">
  import { untrack } from 'svelte'
  import type { RobotMap } from './lib/maps'
  import { fitView, zoomView, mapImage, roomLabels, type View } from './lib/view'
  import { Cell, CellEditor, cellRect, type CellRect, type Point } from './lib/editor'

  const Tool = { Pan: 'Pan', Select: 'Select', Erase: 'Erase', Line: 'Line' } as const
  type Tool = typeof Tool[keyof typeof Tool]

  let { map, source, initialView, initialCells, onview, onedit }: {
    map: RobotMap
    source: string
    initialView?: View
    initialCells?: Uint8Array
    onview?: (view: View) => void
    onedit?: (cells: Uint8Array) => void
  } = $props()
  let viewport = $state<HTMLDivElement>()
  let canvas = $state<HTMLCanvasElement>()
  let width = $state(0)
  let height = $state(0)
  let view = $state<View>({ x: 0, y: 0, scale: 1 })
  let dragging = $state(false)
  let ready = $state(false)
  let fittedMap: RobotMap | null = null
  let size = { width: 0, height: 0 }
  let pointer: { id: number, point: Point, screen: Point, tool: Tool } | null = null
  let tool = $state<Tool>(Tool.Pan)
  let selection = $state<CellRect | null>(null)
  let editVersion = $state(0)
  const editor = $derived(new CellEditor(map.width, map.height, initialCells ?? map.cells))
  const labels = $derived(roomLabels(map))
  const canUndo = $derived.by(() => { editVersion; return editor.canUndo })
  const canRedo = $derived.by(() => { editVersion; return editor.canRedo })

  $effect(() => {
    if (!viewport) return
    const observer = new ResizeObserver(([entry]) => {
      if (!entry) return
      width = entry.contentRect.width
      height = entry.contentRect.height
    })
    observer.observe(viewport)
    return () => observer.disconnect()
  })

  $effect(() => {
    if (!width || !height) return
    const current = untrack(() => view)
    view = fittedMap !== map ? initialView ?? fitView(width, height, { ...map, cells: editor.cells }) : {
      ...current, x: current.x + (width - size.width) / 2, y: current.y + (height - size.height) / 2,
    }
    fittedMap = map
    size = { width, height }
    ready = true
  })

  $effect(() => {
    const current = view
    const save = onview
    if (!ready || !save) return
    const timer = setTimeout(() => save(current), 150)
    return () => clearTimeout(timer)
  })

  $effect(() => {
    editVersion
    const context = canvas?.getContext('2d')
    if (!context) return
    const image = mapImage({ ...map, cells: editor.cells })
    context.putImageData(new ImageData(image, map.width, map.height), 0, 0)
  })

  function fit() {
    view = fitView(width, height, { ...map, cells: editor.cells })
  }

  function zoom(factor: number) {
    view = zoomView(view, factor, width / 2, height / 2)
  }

  function wheelZoom(node: HTMLDivElement) {
    const wheel = (event: WheelEvent) => {
      event.preventDefault()
      if (pointer) return
      const rect = node.getBoundingClientRect()
      const delta = event.deltaY * (event.deltaMode === 1 ? 16 : event.deltaMode === 2 ? height : 1)
      view = zoomView(view, Math.exp(-Math.max(-500, Math.min(500, delta)) * 0.002),
        event.clientX - rect.left, event.clientY - rect.top)
    }
    node.addEventListener('wheel', wheel, { passive: false })
    return { destroy() { node.removeEventListener('wheel', wheel) } }
  }

  function pointAt(event: PointerEvent): Point {
    const rect = viewport!.getBoundingClientRect()
    return {
      x: Math.floor((event.clientX - rect.left - view.x) / view.scale),
      y: Math.floor((event.clientY - rect.top - view.y) / view.scale),
    }
  }

  function changed() {
    editVersion++
    onedit?.(editor.cells)
  }

  function eraseSelection() {
    if (!selection || pointer) return
    editor.fill(selection, Cell.Unknown)
    if (editor.commit()) changed()
  }

  function undo() {
    if (!pointer && editor.undo()) changed()
  }

  function redo() {
    if (!pointer && editor.redo()) changed()
  }

  function startDrag(event: PointerEvent) {
    if ((event.button !== 0 && event.button !== 1) || pointer || !viewport) return
    const active = event.button === 1 || event.altKey ? Tool.Pan : tool
    const point = pointAt(event)
    if (active !== Tool.Pan && (point.x < 0 || point.y < 0 || point.x >= map.width || point.y >= map.height)) {
      selection = null
      return
    }

    event.preventDefault()
    viewport.focus()
    viewport.setPointerCapture(event.pointerId)
    pointer = { id: event.pointerId, point, screen: { x: event.clientX, y: event.clientY }, tool: active }
    dragging = active === Tool.Pan
    if (active === Tool.Select) selection = cellRect(point, point, map.width, map.height)
    if (active === Tool.Pan || active === Tool.Select) return

    selection = null
    editor.line(point, point, active === Tool.Line ? Cell.Wall : Cell.Unknown)
    editVersion++
  }

  function moveDrag(event: PointerEvent) {
    if (!pointer || pointer.id !== event.pointerId) return
    if (pointer.tool === Tool.Pan) {
      view = { ...view, x: view.x + event.clientX - pointer.screen.x, y: view.y + event.clientY - pointer.screen.y }
      pointer.screen = { x: event.clientX, y: event.clientY }
      return
    }

    const point = pointAt(event)
    if (pointer.tool === Tool.Select) {
      selection = cellRect(pointer.point, point, map.width, map.height)
      return
    }

    if (pointer.tool === Tool.Line) {
      // Replace the preview from the fixed anchor, preserving cells under old previews.
      editor.cancel()
      editor.line(pointer.point, point, Cell.Wall)
    } else {
      editor.line(pointer.point, point, Cell.Unknown)
      pointer.point = point
    }
    editVersion++
  }

  function endDrag(event: PointerEvent) {
    if (pointer?.id !== event.pointerId) return
    moveDrag(event)
    const active = pointer.tool
    pointer = null
    dragging = false
    if ((active === Tool.Erase || active === Tool.Line) && editor.commit()) changed()
  }

  function cancelDrag() {
    if (!pointer) return
    const id = pointer.id
    if (pointer.tool === Tool.Erase || pointer.tool === Tool.Line) {
      editor.cancel()
      editVersion++
    }
    if (pointer.tool === Tool.Select) selection = null
    pointer = null
    dragging = false
    if (viewport?.hasPointerCapture(id)) viewport.releasePointerCapture(id)
  }

  function keydown(event: KeyboardEvent) {
    const key = event.key.toLowerCase()
    if (key === 'escape') { cancelDrag(); selection = null }
    else if (pointer) return
    else if ((event.ctrlKey || event.metaKey) && key === 'z') { if (event.shiftKey) redo(); else undo() }
    else if ((event.ctrlKey || event.metaKey) && key === 'y') redo()
    else if (event.ctrlKey || event.metaKey) return
    else if ((key === 'delete' || key === 'backspace') && selection) eraseSelection()
    else if (event.key === '+' || event.key === '=') zoom(1.25)
    else if (event.key === '-') zoom(0.8)
    else if (event.key === '0') fit()
    else if (event.key === 'ArrowLeft') view = { ...view, x: view.x + 40 }
    else if (event.key === 'ArrowRight') view = { ...view, x: view.x - 40 }
    else if (event.key === 'ArrowUp') view = { ...view, y: view.y + 40 }
    else if (event.key === 'ArrowDown') view = { ...view, y: view.y - 40 }
    else return
    event.preventDefault()
  }
</script>

<div class="flex min-h-0 min-w-0 flex-1 flex-col">
  <div class="flex shrink-0 flex-wrap items-center justify-between gap-2 border-b border-base-300 bg-base-100 px-4 py-3">
    <div class="flex flex-wrap gap-2">
      <div class="join" role="group" aria-label="Tools">
        {#each Object.values(Tool) as mode}
          <button class="btn btn-sm join-item" class:btn-primary={tool === mode}
            aria-pressed={tool === mode} onclick={() => tool = mode}>{mode}</button>
        {/each}
      </div>
      <div class="join" role="group" aria-label="Edits">
        <button class="btn btn-sm join-item" disabled={!selection} onclick={eraseSelection}>Delete</button>
        <button class="btn btn-sm join-item" disabled={!canUndo} onclick={undo}>Undo</button>
        <button class="btn btn-sm join-item" disabled={!canRedo} onclick={redo}>Redo</button>
      </div>
    </div>
    <div class="join" role="group" aria-label="Zoom">
      <button class="btn btn-sm join-item" onclick={() => zoom(0.8)} aria-label="Zoom out">−</button>
      <button class="btn btn-sm join-item" onclick={fit}>Fit</button>
      <button class="btn btn-sm join-item" onclick={() => zoom(1.25)} aria-label="Zoom in">+</button>
    </div>
  </div>
  <!-- svelte-ignore a11y_no_noninteractive_tabindex, a11y_no_noninteractive_element_interactions (Interactive map supports keyboard zoom and pan.) -->
  <div bind:this={viewport} use:wheelZoom
    class="relative min-h-0 flex-1 touch-none overflow-hidden outline-offset-[-2px]"
    class:cursor-grab={tool === Tool.Pan && !dragging} class:cursor-grabbing={dragging}
    class:cursor-crosshair={tool !== Tool.Pan && !dragging}
    role="application" aria-label="Map from {source}" tabindex="0"
    onpointerdown={startDrag} onpointermove={moveDrag} onpointerup={endDrag}
    onpointercancel={cancelDrag} onlostpointercapture={cancelDrag} onkeydown={keydown}>
    <canvas bind:this={canvas} width={map.width} height={map.height}
      class="pointer-events-none absolute left-0 top-0 origin-top-left [image-rendering:pixelated]"
      style:transform="translate({view.x}px, {view.y}px) scale({view.scale})"
      aria-label="Room map"></canvas>
    {#each labels as label (label.id)}
      <span class="pointer-events-none absolute -translate-x-1/2 -translate-y-1/2 select-none rounded bg-base-100/85 px-2 py-0.5 text-xs font-medium"
        style:left="{view.x + label.x * view.scale}px" style:top="{view.y + label.y * view.scale}px">
        Room {label.id}
      </span>
    {/each}
    {#if selection}
      <div class="pointer-events-none absolute border border-info bg-info/10" aria-hidden="true"
        style:left="{view.x + selection.left * view.scale}px"
        style:top="{view.y + selection.top * view.scale}px"
        style:width="{(selection.right - selection.left + 1) * view.scale}px"
        style:height="{(selection.bottom - selection.top + 1) * view.scale}px"></div>
    {/if}
  </div>
</div>
