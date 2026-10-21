/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x00023070
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Prepared statement database+0x138, SQL global 0x12082c: select id,map from bakmaps where id=?.
   Locks +0x160, expects step 100, gets blob size and copies only when 0<size<=capacity; returns 0
   even if capacity prevents copying. Error returns -1. */

int MapFlowReadBackupDb(void *database,MapFlowBackupRowView *row)

{
  int iVar1;
  void *__src;
  size_t __n;
  undefined4 uVar2;
  pthread_mutex_t *__mutex;
  char *pcVar3;
  
  if ((row != (MapFlowBackupRowView *)0x0) && (row->blob != (void *)0x0)) {
    __mutex = (pthread_mutex_t *)((int)database + 0x160);
    pthread_mutex_lock(__mutex);
    iVar1 = FUN_000a8120(*(undefined4 *)((int)database + 0x138),1,row->external_id);
    if (iVar1 == 0) {
      iVar1 = FUN_000cee04(*(undefined4 *)((int)database + 0x138));
      if (iVar1 == 100) {
        iVar1 = FUN_0009d524(*(undefined4 *)((int)database + 0x138),0);
        row->external_id = iVar1;
        __src = (void *)FUN_000a2d44(*(undefined4 *)((int)database + 0x138),1);
        if (__src == (void *)0x0) {
          row->blob_size = 0;
        }
        else {
          __n = FUN_000a2c18(*(undefined4 *)((int)database + 0x138),1);
          row->blob_size = __n;
          if ((0 < (int)__n) && ((int)__n <= (int)row->capacity)) {
            memcpy(row->blob,__src,__n);
          }
        }
        FUN_000c79ac(*(undefined4 *)((int)database + 0x138));
        pthread_mutex_unlock(__mutex);
        return 0;
      }
      pcVar3 = "#9033`%s";
      uVar2 = 0x737;
    }
    else {
      pcVar3 = "#9032`%s";
      uVar2 = 0x72f;
    }
    FUN_00026228(uVar2,DAT_00023160,4,7,pcVar3,DAT_0012082c);
    FUN_000c79ac(*(undefined4 *)((int)database + 0x138));
    pthread_mutex_unlock(__mutex);
    return -1;
  }
  return -1;
}

