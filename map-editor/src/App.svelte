<div class="flex min-h-dvh flex-col bg-base-200">
  <header class="navbar flex-wrap gap-3 border-b border-base-300 bg-base-100 px-6">
    <h1 class="flex-1 text-xl font-semibold">S7 Map Editor</h1>
    <span class="badge badge-outline">Local only · No robot connection</span>
  </header>

  <main class="grid flex-1 gap-4 p-4 lg:grid-cols-[16rem_minmax(0,1fr)_18rem]">
    <aside class="card border border-base-300 bg-base-100" aria-labelledby="files-title">
      <div class="card-body">
        <h2 id="files-title" class="card-title">Map files</h2>
        <p>Work on a copy of a matching backup. Keep the original untouched.</p>
        <button class="btn btn-primary mt-2" disabled>Open map</button>
        <p class="text-sm">File loading is not implemented yet.</p>
      </div>
    </aside>

    <section class="card min-w-0 border border-base-300 bg-base-100" aria-labelledby="workspace-title">
      <div class="flex flex-wrap items-center justify-between gap-3 border-b border-base-300 p-4">
        <h2 id="workspace-title" class="text-lg font-semibold">Map workspace</h2>
        <div class="join" role="group" aria-label="Map actions">
          <button class="btn join-item btn-sm" disabled>Undo</button>
          <button class="btn join-item btn-sm" disabled>Redo</button>
          <button class="btn join-item btn-sm" disabled>Export copy</button>
        </div>
      </div>
      <div class="flex min-h-80 flex-1 items-center justify-center p-8">
        <div class="max-w-sm space-y-3 text-center">
          <span class="badge badge-neutral">Scaffold</span>
          <h3 class="text-2xl font-semibold">No map loaded</h3>
          <p>Canvas preview, occupancy editing, and export will live here.</p>
        </div>
      </div>
    </section>

    <aside class="card border border-base-300 bg-base-100" aria-labelledby="details-title">
      <div class="card-body">
        <h2 id="details-title" class="card-title">Map details</h2>
        <p>Dimensions, origin, and integrity checks will appear after loading.</p>
        <div class="divider"></div>
        <h3 class="font-semibold">Edit boundary</h3>
        <p>Planned scope: occupancy cells only. Preserve the frame and companion files.</p>
        <p class="alert alert-warning mt-3">A valid file does not establish safe navigation. Edited-map restoration remains unverified.</p>
      </div>
    </aside>
  </main>

  <footer class="px-6 pb-4 text-sm">Scaffold only · No file reads, writes, or uploads</footer>
</div>
