/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x00023210
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Prepared statement database+0x140, SQL global 0x120838: update bakmaps set map=? where id=?.
   Locks database+0x160; binds blob then signed ID (sign word from ASR #31), expects step 101.
   Success resets/unlocks +0x160. Error path at 0x2329e unlocks +0x178 instead: instruction-level
   observed discrepancy, not corrected by annotation. */

int MapFlowUpdateBackupDb(void *database,MapFlowBackupRowView *row)

{
  int iVar1;
  undefined4 uVar2;
  char *pcVar3;
  
  if (row == (MapFlowBackupRowView *)0x0) {
    return -1;
  }
  pthread_mutex_lock((pthread_mutex_t *)((int)database + 0x160));
  iVar1 = FUN_000a7fc8(*(undefined4 *)((int)database + 0x140),1,row->blob,row->blob_size,0xffffffff)
  ;
  if (iVar1 == 0) {
    iVar1 = FUN_000a80c0(*(undefined4 *)((int)database + 0x140),2,row->external_id,
                         row->external_id >> 0x1f);
    if (iVar1 == 0) {
      iVar1 = FUN_000cee04(*(undefined4 *)((int)database + 0x140));
      if (iVar1 == 0x65) {
        FUN_000c79ac(*(undefined4 *)((int)database + 0x140));
        pthread_mutex_unlock((pthread_mutex_t *)((int)database + 0x160));
        return 0;
      }
      pcVar3 = "#9038`%s";
      uVar2 = 0x783;
    }
    else {
      pcVar3 = "#9037`%s";
      uVar2 = 0x77a;
    }
  }
  else {
    pcVar3 = "#9036`%s";
    uVar2 = 0x772;
  }
  FUN_00026228(uVar2,DAT_000232f4,4,7,pcVar3,DAT_00120838);
  FUN_000c79ac(*(undefined4 *)((int)database + 0x140));
  pthread_mutex_unlock((pthread_mutex_t *)((int)database + 0x178));
  return -1;
}

