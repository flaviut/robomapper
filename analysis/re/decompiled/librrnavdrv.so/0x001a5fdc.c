/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x001a5fdc
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Stores byte 1 at manager+0x22 and native_flag at manager+0x28, then logs. No file write in this
   function. Called after grid-save success and during flag-1 reconciliation. */

void MapFlowSetStoredFlag(void *manager,int native_flag)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = DAT_001a6014;
  iVar1 = DAT_001a6010;
  iVar3 = DAT_001a600c + 0x1a5fee;
  *(undefined1 *)((int)manager + 0x22) = 1;
  *(int *)((int)manager + 0x28) = native_flag;
  _rrlogmP(3,6,1,0x6c,iVar2 + 0x1a5ff8,iVar1 + 0x1a5ff4,iVar3,native_flag);
  return;
}

