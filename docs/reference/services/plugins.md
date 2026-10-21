# Loader and map-plugin shutdown

`rr_loader` hosts navigation, SLAM and chassis together in the saved defaults. No public map-only shutdown interface or complete persistence flush barrier is established. The [supervision reference](supervision.md) uses actual host exit as the file-work boundary.

## Concrete plugin exit: cooperative loops, not a public map-only stop

Focused Thumb disassembly closes the generic-callback edge left by the writer-host report. SLAM `rr_load_plugin:0x6c14` returns the callback table at VA `0x5440c` (file offset `0x4440c`); navigation `rr_load_plugin:0x5f830` returns VA `0x3044f8` (file offset `0x2f44f8`). Both tables have **null slot +0x10**, so neither provides a pre-join stop callback. Their thread and post-join callbacks are:

| Plugin | Thread slot +8 | Post-join slot +0x14 | Directly established behavior |
| --- | --- | --- | --- |
| SLAM | Thumb `0x534d` | Thumb `0x5299` | Loop at `0x537c–0x538e` dispatches messages until `rr_check_quit` is true. Post-join callback sends `0x090907d0`, calls `0x6c48`, then `ReleaseSharedRegion(1)` at `0x530a–0x530c`. |
| Navigation | Thumb `0x63e69` | Thumb `0x61175` | Thread wrapper calls singleton `0x6110c`, then `0x63d10`. Loop at `0x63dc4–0x63dd8` dispatches until `rr_check_quit`; after exit it calls `0x162938` with argument 1. Post-join wrapper tail-calls singleton vtable slot +0x10. |

These establish cooperative host cleanup, not a map-save barrier or a callable maintenance RPC. [`RRPlugin::final:0x19058`](../../../analysis/re/evidence/restore/writer-host/proof/c/0x00019058.c) sets the per-plugin quit flag, wakes waiters, joins the thread, then calls the post-join slot. [`RRLoader::final:0x187fc`](../../../analysis/re/evidence/restore/writer-host/proof/c/0x000187fc.c) joins the timer first, then finalizes **all** plugins, not just map plugins. Loader SIGHUP sets the loader quit flag at +0x9c; it does not select navigation/SLAM independently. No external plugin-unload or map-only shutdown interface is established by these callbacks. Calling a callback address from another process is not an alternative.

The SLAM shutdown notification and shared-region release happen after thread exit, but detached persistence workers elsewhere in the host are not covered by that join. For offline file work, actual host exit remains the useful boundary. Retaining chassis would instead require an independently grounded chassis-only host/configuration; this document does not authorize modifying the embedded plugin set.

Provenance: original tracked `librrslamdrv.so` SHA256 `b48f5f56eb1b2d22abbf727725ea558762337f8f0103229d8da6c1ab6275608a`; `librrnavdrv.so` SHA256 `603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475`. Export entries were read using a private `/tmp` copy made by source-root `retool.py copy`; callback instructions were read directly with pinned LLVM objdump in Thumb mode. The baseline did not identify these callback addresses as separate function entries; failed bounded exports were not treated as evidence. No baseline changes or new function definitions were made.

The timer join is now connected to the loader quit flag: timer init `0x16848` starts Thumb `0x16ce5`; its loop calls `updatetime`, sleeps 2,500 microseconds, then calls `RRLoader::checkQuit:0x18834` at `0x16d02`. That reads +0x9c. Thus SIGHUP can let the timer join advance to plugin cleanup once its current work returns; it is not an unconditional deadlock. `rr_check_quit:0x19164` follows the plugin control's +4 pointer and reads the plugin +0x184 quit byte set by finalization. The exported method named `RRLoader::stop:0x1845c` merely returns 1; its name is not a shutdown API.
