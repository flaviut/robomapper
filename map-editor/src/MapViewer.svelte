<script lang="ts">
  import { untrack } from 'svelte'
  import type { RobotMap } from './lib/maps'
  import { fitView, zoomView, mapImage, roomLabels, type View } from './lib/view'

  let { map, source, initialView, onview }: {
    map: RobotMap
    source: string
    initialView?: View
    onview?: (view: View) => void
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
  let pointer: { id: number, x: number, y: number } | null = null
  const labels = $derived(roomLabels(map))

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
    view = fittedMap !== map ? initialView ?? fitView(width, height, map) : {
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
    const context = canvas?.getContext('2d')
    if (!context) return
    context.putImageData(new ImageData(mapImage(map), map.width, map.height), 0, 0)
  })

  function fit() {
    view = fitView(width, height, map)
  }

  function zoom(factor: number) {
    view = zoomView(view, factor, width / 2, height / 2)
  }

  function wheelZoom(node: HTMLDivElement) {
    const wheel = (event: WheelEvent) => {
      event.preventDefault()
      const rect = node.getBoundingClientRect()
      const delta = event.deltaY * (event.deltaMode === 1 ? 16 : event.deltaMode === 2 ? height : 1)
      view = zoomView(view, Math.exp(-Math.max(-500, Math.min(500, delta)) * 0.002),
        event.clientX - rect.left, event.clientY - rect.top)
    }
    node.addEventListener('wheel', wheel, { passive: false })
    return { destroy() { node.removeEventListener('wheel', wheel) } }
  }

  function startDrag(event: PointerEvent) {
    if (event.button !== 0 || pointer || !viewport) return
    viewport.focus()
    viewport.setPointerCapture(event.pointerId)
    pointer = { id: event.pointerId, x: event.clientX, y: event.clientY }
    dragging = true
  }

  function moveDrag(event: PointerEvent) {
    if (!pointer || pointer.id !== event.pointerId) return
    view = { ...view, x: view.x + event.clientX - pointer.x, y: view.y + event.clientY - pointer.y }
    pointer = { id: event.pointerId, x: event.clientX, y: event.clientY }
  }

  function endDrag(event: PointerEvent) {
    if (pointer?.id !== event.pointerId) return
    pointer = null
    dragging = false
  }

  function keydown(event: KeyboardEvent) {
    if (event.key === '+' || event.key === '=') zoom(1.25)
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

<div class="relative min-h-0 min-w-0 flex-1">
  <!-- svelte-ignore a11y_no_noninteractive_tabindex, a11y_no_noninteractive_element_interactions (Interactive map supports keyboard zoom and pan.) -->
  <div bind:this={viewport} use:wheelZoom
    class="absolute inset-0 touch-none overflow-hidden outline-offset-[-2px]"
    class:cursor-grab={!dragging} class:cursor-grabbing={dragging}
    role="application" aria-label="Map from {source}" tabindex="0"
    onpointerdown={startDrag} onpointermove={moveDrag} onpointerup={endDrag}
    onpointercancel={endDrag} onlostpointercapture={endDrag} onkeydown={keydown}>
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
  </div>
  <div class="join absolute right-4 top-4 shadow" role="group" aria-label="Zoom">
    <button class="btn btn-sm join-item" onclick={() => zoom(0.8)} aria-label="Zoom out">−</button>
    <button class="btn btn-sm join-item" onclick={fit}>Fit</button>
    <button class="btn btn-sm join-item" onclick={() => zoom(1.25)} aria-label="Zoom in">+</button>
  </div>
</div>
