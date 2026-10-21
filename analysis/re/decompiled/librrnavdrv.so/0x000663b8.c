/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x000663b8
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Sets core byte +0x271 to 1 between memory barriers. Source diagnostic SetNeededToRecoverLastMap.
   This blocks last-map saves through MapFlowSaveGridState. Relationship to RoboController
   need_recover_map configuration key is not established. */

void MapFlowSetRecoverLast(void *core)

{
  DataMemoryBarrier(0x1b);
  *(undefined1 *)((int)core + 0x271) = 1;
  DataMemoryBarrier(0x1b);
  DataMemoryBarrier(0x1b);
  DataMemoryBarrier(0x1b);
  _rrlogmP(3,7,1,0x56f,DAT_00066408 + 0x663ec,DAT_00066404 + 0x663ea,DAT_00066400 + 0x663e6,
           *(char *)((int)core + 0x271) != '\0');
  return;
}

