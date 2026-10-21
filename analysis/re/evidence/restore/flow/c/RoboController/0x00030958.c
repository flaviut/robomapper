/* Decompiled C, NOT recovered source; need not compile.
 * Binary: RoboController
 * SHA256: bf1d43313dd8beaa0c802f9ae4c666138b3bb518f69b4909a746285f3f3947cf
 * Function VA: 0x00030958
 */

void FUN_00030958(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  undefined4 uVar1;
  time_t tVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  int local_2c;
  
  local_2c = __stack_chk_guard;
  *(undefined4 *)(param_1 + 0x3a0) = param_3;
  *(undefined4 *)(param_1 + 0x3a4) = param_4;
  tVar2 = time((time_t *)0x0);
  local_40 = *(undefined4 *)(param_1 + 0x3a0);
  uStack_3c = *(undefined4 *)(param_1 + 0x3a4);
  local_50 = DAT_00030a7c;
  local_4c = 0x3c;
  *(undefined4 *)(param_1 + 0x3a8) = param_6;
  local_48 = 0;
  *(time_t *)(param_1 + 0x398) = tVar2;
  uStack_38 = 1;
  uStack_34 = 0;
  FUN_00028678(param_1,2,&local_50);
  iVar3 = FUN_0002d24c();
  local_68 = *(undefined4 *)(param_1 + 0x398);
  uStack_64 = *(undefined4 *)(param_1 + 0x39c);
  uStack_60 = *(undefined4 *)(param_1 + 0x3a0);
  uStack_5c = *(undefined4 *)(param_1 + 0x3a4);
  local_58 = *(undefined4 *)(param_1 + 0x3a8);
  uStack_54 = *(undefined4 *)(param_1 + 0x3ac);
  pthread_mutex_lock((pthread_mutex_t *)(iVar3 + 0x36c));
  puVar4 = *(undefined4 **)(iVar3 + 0x388);
  if (puVar4 == *(undefined4 **)(iVar3 + 0x38c)) {
    FUN_00034cdc(iVar3 + 900,&local_68);
  }
  else {
    if (puVar4 != (undefined4 *)0x0) {
      *puVar4 = local_68;
      puVar4[1] = uStack_64;
      puVar4[2] = uStack_60;
      puVar4[3] = uStack_5c;
      puVar4[4] = local_58;
      puVar4[5] = uStack_54;
    }
    *(undefined4 **)(iVar3 + 0x388) = puVar4 + 6;
  }
  uVar1 = DAT_00030a80;
  pthread_mutex_unlock((pthread_mutex_t *)(iVar3 + 0x36c));
  FUN_00020728(0x182d,DAT_00030a84,DAT_0006a690 & 0x2000,"#12621");
  local_78 = uVar1;
  local_6c = param_5;
  local_70 = 0;
  local_74 = 0x116;
  FUN_00028678(param_1,3,&local_78,0);
  FUN_00020728(0x1832,DAT_00030a84,DAT_0006a690 & 0x2000,"#12622");
  if (local_2c == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

