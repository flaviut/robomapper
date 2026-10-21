/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x00022f84
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Observed prepared statement pointer database+0x134, SQL global 0x120830: insert into bakmaps
   (id,map) values (?,?). Locks database+0x160, binds row ID and blob, steps expecting 101, resets
   statement and unlocks. Returns 0/-1. No broader transaction/durability inferred. */

int MapFlowInsertBackupDb(void *database,MapFlowBackupRowView *row)

{
  int iVar1;
  undefined4 uVar2;
  pthread_mutex_t *__mutex;
  char *pcVar3;
  
  if ((row != (MapFlowBackupRowView *)0x0) && (row->blob != (void *)0x0)) {
    __mutex = (pthread_mutex_t *)((int)database + 0x160);
    pthread_mutex_lock(__mutex);
    iVar1 = FUN_000a8120(*(undefined4 *)((int)database + 0x134),1,row->external_id);
    if (iVar1 == 0) {
      iVar1 = FUN_000a7fc8(*(undefined4 *)((int)database + 0x134),2,row->blob,row->blob_size,
                           0xffffffff);
      if (iVar1 == 0) {
        iVar1 = FUN_000cee04(*(undefined4 *)((int)database + 0x134));
        if (iVar1 == 0x65) {
          FUN_000c79ac(*(undefined4 *)((int)database + 0x134));
          pthread_mutex_unlock(__mutex);
          return 0;
        }
        pcVar3 = "#9031`%s";
        uVar2 = 0x719;
      }
      else {
        pcVar3 = "#9030`%s";
        uVar2 = 0x710;
      }
    }
    else {
      pcVar3 = "#9029`%s";
      uVar2 = 0x708;
    }
    FUN_00026228(uVar2,DAT_0002306c,4,7,pcVar3,DAT_00120830);
    FUN_000c79ac(*(undefined4 *)((int)database + 0x134));
    pthread_mutex_unlock(__mutex);
    return -1;
  }
  return -1;
}

