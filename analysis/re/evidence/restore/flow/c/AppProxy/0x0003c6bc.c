/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x0003c6bc
 */

void FUN_0003c6bc(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,int *param_6)

{
  undefined4 uVar1;
  uint __n;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 local_90;
  undefined4 uStack_8c;
  int local_88;
  undefined4 local_84;
  undefined4 local_80 [4];
  undefined4 local_70 [2];
  undefined4 local_68;
  undefined4 local_64;
  undefined4 uStack_60;
  int iStack_5c;
  undefined4 uStack_58;
  undefined4 local_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  int local_24;
  
  local_24 = __stack_chk_guard;
  memset(local_70,0,0x4c);
  local_70[0] = 0x2033212;
  memset(&local_90,0,0x20);
  iVar3 = param_6[1] - *param_6 >> 2;
  local_84 = param_5;
  local_90 = param_3;
  uStack_8c = param_4;
  local_88 = iVar3;
  FUN_00026228(0x542e,DAT_0003c79c,2,6,"#10574`%d",iVar3);
  __n = param_6[1] - *param_6;
  if (__n >> 2 != 0) {
    memcpy(local_80,(void *)*param_6,__n);
  }
  uVar1 = DAT_0003c79c;
  if (iVar3 != 0) {
    puVar4 = &local_84;
    iVar2 = 0;
    do {
      puVar4 = puVar4 + 1;
      iVar2 = iVar2 + 1;
      FUN_00026228(0x5431,uVar1,2,6,"#10575`%d",*puVar4);
    } while (iVar2 != iVar3);
  }
  local_68 = 0x20;
  local_64 = local_90;
  uStack_60 = uStack_8c;
  iStack_5c = local_88;
  uStack_58 = local_84;
  local_54 = local_80[0];
  uStack_50 = local_80[1];
  uStack_4c = local_80[2];
  uStack_48 = local_80[3];
  FUN_00037b78(param_1,local_70,1,0);
  if (local_24 == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

