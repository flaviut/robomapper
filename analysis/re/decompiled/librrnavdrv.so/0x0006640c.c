/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x0006640c
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Clears core byte +0x271 between memory barriers; diagnostic ResetNeededToRecoverLastMap. Called
   only after successful persistence restore for native flag 1 in LoadSLAMMap, also from clear-map
   state. */

void MapFlowClearRecoverLast(void *core)

{
  DataMemoryBarrier(0x1b);
  *(undefined1 *)((int)core + 0x271) = 0;
  DataMemoryBarrier(0x1b);
  DataMemoryBarrier(0x1b);
  DataMemoryBarrier(0x1b);
  _rrlogmP(3,7,1,0x575,DAT_00066460 + 0x66440,DAT_0006645c + 0x6643e,DAT_00066458 + 0x6643a,
           *(char *)((int)core + 0x271) != '\0');
  return;
}

