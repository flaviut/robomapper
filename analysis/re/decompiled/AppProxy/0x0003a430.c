/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x0003a430
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Builds application map message through 0x8cddc, uses external DB ID native_flag-2. Looks up
   bakmaps via 0x23070; insert 0x22f84 if read failed or blob size is zero, else update 0x23210.
   Uses current application-map buffer at map object+0x30002c with size word+0x48002c. DB errors
   only logged; returns void, not success/failure. */

void MapFlowWriteBackupDb(void *proxy,int native_flag)

{
  int iVar1;
  MapFlowBackupRowView local_44;
  MapFlowBackupRowView local_30;
  int local_1c;
  
  local_1c = __stack_chk_guard;
  FUN_00026228(0x2fc3,DAT_0003a5bc,5,7,"#9942");
  FUN_0008cddc(*(undefined4 *)((int)proxy + 0x4e8),1);
  local_44.external_id = native_flag + -2;
  local_44.blob_size = *(uint *)(*(int *)((int)proxy + 0x4e8) + 0x48002c);
  local_44.blob = (void *)(*(int *)((int)proxy + 0x4e8) + 0x30002c);
  local_44.capacity = 0x80000;
  local_30.unknown04 = 0;
  local_30.blob = (void *)0x0;
  local_30.blob_size = 0;
  local_30.capacity = 0;
  local_30.external_id = local_44.external_id;
  local_30.blob = operator_new__(0x80000);
  local_30.capacity = 0x80000;
  iVar1 = MapFlowReadBackupDb(*(void **)((int)proxy + 0x68),&local_30);
  if (iVar1 == 0) {
    if (local_30.blob_size == 0) {
      iVar1 = MapFlowInsertBackupDb(*(void **)((int)proxy + 0x68),&local_44);
      if (iVar1 == 0) {
        FUN_00026228(0x2fe3,DAT_0003a5bc,2,7,"#9947`%d`%d",local_44.external_id,local_44.blob_size);
      }
      else {
        FUN_00026228(0x2fe5,DAT_0003a5bc,2,6,"#9948`%d");
      }
    }
    else {
      iVar1 = MapFlowUpdateBackupDb(*(void **)((int)proxy + 0x68),&local_44);
      if (iVar1 == 0) {
        FUN_00026228(0x2fe9,DAT_0003a5bc,2,7,"#9949`%d`%d",local_44.external_id,local_44.blob_size);
      }
      else {
        FUN_00026228(0x2feb,DAT_0003a5bc,2,6,"#9950`%d",local_44.external_id);
      }
    }
    if (local_30.blob != (void *)0x0) {
      operator_delete__(local_30.blob);
    }
  }
  else {
    FUN_00026228(0x2fd7,DAT_0003a5bc,5,6,"#9944");
    if (local_30.blob != (void *)0x0) {
      operator_delete__(local_30.blob);
    }
    local_30.blob = (void *)0x0;
    iVar1 = MapFlowInsertBackupDb(*(void **)((int)proxy + 0x68),&local_44);
    if (iVar1 == 0) {
      FUN_00026228(0x2fdc,DAT_0003a5bc,2,7,"#9945`%d`%d",local_44.external_id,local_44.blob_size);
    }
    else {
      FUN_00026228(0x2fde,DAT_0003a5bc,2,6,"#9946`%d");
    }
  }
  if (local_1c == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

