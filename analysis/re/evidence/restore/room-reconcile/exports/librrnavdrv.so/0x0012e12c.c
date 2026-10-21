/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x0012e12c
 */

void FUN_0012e12c(int param_1,undefined4 param_2,int *param_3)

{
  int *piVar1;
  int *piVar2;
  float fVar3;
  int iVar4;
  undefined1 local_111;
  undefined4 local_110;
  undefined4 local_10c;
  undefined4 local_108;
  undefined4 local_104;
  int local_100;
  int local_fc;
  int local_f8;
  int local_f4;
  int local_f0;
  int local_ec;
  int local_e8;
  int local_e4;
  int local_e0;
  int local_dc;
  int local_d8;
  int local_d4;
  int local_d0;
  undefined1 auStack_cc [36];
  undefined4 *local_a8;
  undefined4 *local_a4;
  int local_a0;
  int *local_9c;
  undefined4 *local_98;
  undefined1 *local_94;
  int local_8c;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  undefined1 auStack_70 [36];
  undefined4 *local_4c;
  undefined4 *local_48;
  undefined4 *local_44;
  undefined4 *local_40;
  undefined4 *local_3c;
  int local_38;
  undefined1 *local_34;
  int local_2c;
  
  piVar2 = *(int **)(DAT_0012e328 + 0x12e13e + DAT_0012e32c);
  local_2c = *piVar2;
  _rrlogmP(3,6,1,0x24b,DAT_0012e338 + 0x12e162,DAT_0012e334 + 0x12e15e,DAT_0012e330 + 0x12e14e);
  piVar1 = (int *)FUN_00205d68();
  local_110 = (**(code **)(*piVar1 + 0x30))();
  local_10c = FUN_0014d1dc();
  local_108 = 0;
  local_104 = 0;
  local_111 = 0;
  fVar3 = roundf((float)(longlong)*(int *)((int)&DAT_001000bc + param_1) * DAT_0012e324);
  iVar4 = (int)fVar3;
  local_f8 = iVar4 + -1;
  local_100 = -iVar4;
  if (local_f8 + iVar4 < 0) {
    local_f0 = 0;
  }
  else {
    local_f0 = local_f8 + iVar4 + 1;
  }
  local_fc = local_100;
  local_f4 = local_f8;
  local_ec = local_f0;
  FUN_001b2214(&local_8c);
  local_88 = local_100;
  local_84 = local_fc;
  local_8c = DAT_0012e33c + 0x12e1ec;
  local_80 = local_f8;
  local_7c = local_f4;
  if (local_f8 - local_100 < 0) {
    local_78 = 0;
  }
  else {
    local_78 = (local_f8 - local_100) + 1;
  }
  if (local_f4 - local_fc < 0) {
    local_74 = 0;
  }
  else {
    local_74 = (local_f4 - local_fc) + 1;
  }
  FUN_00126344(auStack_70,&local_100);
  local_4c = &local_108;
  local_48 = &local_10c;
  local_44 = &local_110;
  local_40 = &local_108;
  local_3c = &local_110;
  local_38 = param_1;
  local_34 = &local_111;
  FUN_001250d4(auStack_70);
  FUN_001b2214(&local_e8);
  local_e4 = *param_3;
  local_e0 = param_3[1];
  local_dc = param_3[2];
  local_d8 = param_3[3];
  if (local_dc - local_e4 < 0) {
    local_d4 = 0;
  }
  else {
    local_d4 = (local_dc - local_e4) + 1;
  }
  local_e8 = DAT_0012e340 + 0x12e284;
  if (local_d8 - local_e0 < 0) {
    local_d0 = 0;
  }
  else {
    local_d0 = (local_d8 - local_e0) + 1;
  }
  FUN_00126344(auStack_cc,param_3);
  local_a8 = &local_110;
  local_a4 = &local_10c;
  local_a0 = param_1;
  local_9c = &local_8c;
  local_98 = &local_108;
  local_94 = &local_111;
  FUN_001250d4(auStack_cc);
  FUN_0012dda4(&local_e8,param_2,1);
  _rrlogmP(3,6,1,0x29f,DAT_0012e34c + 0x12e2ce,DAT_0012e348 + 0x12e2ca,DAT_0012e344 + 0x12e2c8);
  FUN_00124b4c(&local_e8);
  FUN_00124b94(&local_8c);
  if (local_2c == *piVar2) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(1);
}

