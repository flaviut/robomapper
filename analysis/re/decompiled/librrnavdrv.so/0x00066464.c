/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x00066464
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Clears observed bytes/word core+0x270/+0x274, then calls clear-recover-last (+0x271); offsets are
   observations, not an original C++ layout. */

void MapFlowClearMapState(void *core)

{
  int iVar1;
  
  DataMemoryBarrier(0x1b);
  *(undefined1 *)((int)core + 0x270) = 0;
  DataMemoryBarrier(0x1b);
  DataMemoryBarrier(0x1b);
  *(undefined4 *)((int)core + 0x274) = 0;
  iVar1 = DAT_000664c0;
  DataMemoryBarrier(0x1b);
  MapFlowClearRecoverLast(core);
  DataMemoryBarrier(0x1b);
  DataMemoryBarrier(0x1b);
  _rrlogmP(3,7,1,0x569,DAT_000664c8 + 0x664ac,DAT_000664c4 + 0x664a2,iVar1 + 0x66496,
           *(char *)((int)core + 0x270) != '\0');
  return;
}

