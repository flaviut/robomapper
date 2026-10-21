/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x0003a430
 */

void FUN_0003a430(int param_1,int param_2)

{
  int iVar1;
  int local_44 [2];
  int local_3c;
  undefined4 local_38;
  undefined4 local_34;
  int local_30 [2];
  void *local_28;
  int local_24;
  undefined4 local_20;
  int local_1c;
  
  local_1c = __stack_chk_guard;
  FUN_00026228(0x2fc3,DAT_0003a5bc,5,7,"#9942");
  FUN_0008cddc(*(undefined4 *)(param_1 + 0x4e8),1);
  local_44[0] = param_2 + -2;
  local_38 = *(undefined4 *)(*(int *)(param_1 + 0x4e8) + 0x48002c);
  local_3c = *(int *)(param_1 + 0x4e8) + 0x30002c;
  local_34 = 0x80000;
  local_30[1] = 0;
  local_28 = (void *)0x0;
  local_24 = 0;
  local_20 = 0;
  local_30[0] = local_44[0];
  local_28 = operator_new__(0x80000);
  local_20 = 0x80000;
  iVar1 = FUN_00023070(*(undefined4 *)(param_1 + 0x68),local_30);
  if (iVar1 == 0) {
    if (local_24 == 0) {
      iVar1 = FUN_00022f84();
      if (iVar1 == 0) {
        FUN_00026228(0x2fe3,DAT_0003a5bc,2,7,"#9947`%d`%d",local_44[0],local_38);
      }
      else {
        FUN_00026228(0x2fe5,DAT_0003a5bc,2,6,"#9948`%d");
      }
    }
    else {
      iVar1 = FUN_00023210(*(undefined4 *)(param_1 + 0x68),local_44);
      if (iVar1 == 0) {
        FUN_00026228(0x2fe9,DAT_0003a5bc,2,7,"#9949`%d`%d",local_44[0],local_38);
      }
      else {
        FUN_00026228(0x2feb,DAT_0003a5bc,2,6,"#9950`%d",local_44[0]);
      }
    }
    if (local_28 != (void *)0x0) {
      operator_delete__(local_28);
    }
  }
  else {
    FUN_00026228(0x2fd7,DAT_0003a5bc,5,6,"#9944");
    if (local_28 != (void *)0x0) {
      operator_delete__(local_28);
    }
    local_28 = (void *)0x0;
    iVar1 = FUN_00022f84(*(undefined4 *)(param_1 + 0x68),local_44);
    if (iVar1 == 0) {
      FUN_00026228(0x2fdc,DAT_0003a5bc,2,7,"#9945`%d`%d",local_44[0],local_38);
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

