/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x0012e95c
 */

void FUN_0012e95c(int param_1,undefined4 *param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  int *piVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int *piVar6;
  undefined4 uVar7;
  int iVar8;
  char local_a9;
  int *local_a8;
  int *local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  int local_90;
  int local_8c;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  undefined1 auStack_74 [36];
  undefined4 *local_50;
  undefined4 *local_4c;
  undefined4 *local_48;
  undefined4 *local_44;
  int **local_40;
  int **local_3c;
  int local_38;
  char *local_34;
  int local_2c;
  
  piVar6 = *(int **)(DAT_0012eaec + 0x12e96a + DAT_0012eaf0);
  iVar8 = 0;
  local_2c = *piVar6;
  piVar2 = (int *)FUN_00205d68();
  local_a8 = (int *)(**(code **)(*piVar2 + 0x30))();
  local_a4 = (int *)FUN_0014d1dc();
  local_a9 = '\0';
  local_a0 = 0;
  local_9c = 0;
  local_98 = 0;
  local_94 = 0;
  FUN_001b2214(&local_90);
  local_8c = *(int *)(&DAT_00100010 + param_1);
  local_88 = *(int *)(&DAT_00100014 + param_1);
  local_84 = *(int *)(&DAT_00100018 + param_1);
  local_80 = *(int *)(&DAT_0010001c + param_1);
  if (-1 < local_84 - local_8c) {
    iVar8 = (local_84 - local_8c) + 1;
  }
  local_90 = DAT_0012eaf4 + 0x12e9d4;
  if (local_80 - local_88 < 0) {
    local_78 = 0;
  }
  else {
    local_78 = (local_80 - local_88) + 1;
  }
  local_7c = iVar8;
  FUN_00126344(auStack_74,&DAT_00100010 + param_1);
  local_40 = &local_a8;
  local_3c = &local_a4;
  local_34 = &local_a9;
  local_50 = &local_a0;
  local_4c = &local_9c;
  local_48 = &local_98;
  local_44 = &local_94;
  local_38 = param_1;
  FUN_001250d4(auStack_74);
  FUN_0012e714(&local_90,param_2,1);
  puVar1 = param_2 + 1;
  uVar7 = *puVar1;
  uVar5 = *param_2;
  uVar3 = (**(code **)(*local_a8 + 0x18))(local_a8,param_2,puVar1);
  uVar4 = (**(code **)(*local_a4 + 0x38))(local_a4,param_2,puVar1);
  _rrlogmP(3,6,1,0x240,DAT_0012eb00 + 0x12ea60,DAT_0012eafc + 0x12ea5c,DAT_0012eaf8 + 0x12ea5a,uVar5
           ,uVar7,uVar3,uVar4);
  if (local_a9 == '\0') {
    _rrlogmP(3,6,1,0x242,DAT_0012eb0c + 0x12ea9a,DAT_0012eb08 + 0x12ea92,DAT_0012eb04 + 0x12ea8e,
             *(undefined4 *)(param_1 + 0x100020),*(undefined4 *)(param_1 + 0x100024),uVar3,uVar4);
  }
  FUN_001285a4(param_3,&local_a0,&local_9c);
  FUN_001285a4(param_3,&local_98,&local_94);
  FUN_00124b04(&local_90);
  if (local_2c != *piVar6) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(1);
  }
  return;
}

