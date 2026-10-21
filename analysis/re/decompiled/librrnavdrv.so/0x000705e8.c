/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x000705e8
 */

/* NavCore initialization includes clearing core+0x271 at instruction 0x70756. Most object layout
   and constructor ABI are unknown; no layout type inferred. See bounded recovery-state findings for
   consumers of this byte. */

void FUN_000705e8(int *param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int *piVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 *puVar10;
  _Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *p_Var11;
  int *piVar12;
  uint uVar13;
  undefined4 uVar14;
  int iVar15;
  int *piVar16;
  int local_34;
  _Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *local_30;
  int local_2c;
  
  iVar15 = DAT_0007134c + 0x705fe;
  piVar12 = *(int **)(iVar15 + DAT_00071350);
  local_2c = *piVar12;
  FUN_00163160(param_1,0);
  iVar6 = DAT_00071354;
  param_1[0x66] = (int)(param_1 + 0x6c);
  param_1[0x73] = (int)(param_1 + 0x79);
  *param_1 = iVar6 + 0x7062c;
  param_1[0x67] = 1;
  param_1[0x68] = 0;
  param_1[0x69] = 0;
  param_1[0x6b] = 0;
  param_1[0x6c] = 0;
  param_1[0x6d] = 0;
  param_1[0x6a] = 0x3f800000;
  param_1[0x6e] = 0;
  param_1[0x6f] = 0;
  param_1[0x70] = 0;
  param_1[0x71] = 0;
  param_1[0x72] = 0;
  param_1[0x74] = 1;
  param_1[0x75] = 0;
  param_1[0x76] = 0;
  param_1[0x77] = 0x3f800000;
  param_1[0x78] = 0;
  param_1[0x79] = 0;
  param_1[0x7a] = 0;
  param_1[0x7b] = 0;
  param_1[0x7c] = 0;
  param_1[0x7d] = 0;
  param_1[0x7e] = 0;
  param_1[0x7f] = 0;
  param_1[0x81] = 1;
  param_1[0x82] = 0;
  param_1[0x83] = 0;
  param_1[0x84] = 0x3f800000;
  param_1[0x80] = (int)(param_1 + 0x86);
  param_1[0x85] = 0;
  param_1[0x86] = 0;
  param_1[0x87] = 0;
  param_1[0x88] = 0;
  param_1[0x89] = 0;
  param_1[0x8a] = 0;
  param_1[0x8b] = 0;
  param_1[0x8c] = 0;
  param_1[0x8d] = 0;
  param_1[0x8e] = 0;
  FUN_001703f8(param_1 + 0x8f);
  iVar6 = DAT_00071358;
  param_1[0x91] = 0;
  param_1[0x92] = 0;
  param_1[0x93] = 0;
  uVar13 = *(int *)(iVar6 + 0x706de) - *(int *)(iVar6 + 0x706da) >> 2;
  if (uVar13 == 0) {
    param_1[0x93] = 0;
    puVar10 = (undefined4 *)0x0;
  }
  else {
    if (0x1fffffff < uVar13) {
                    /* WARNING: Subroutine does not return */
      std::__throw_bad_alloc();
    }
    puVar4 = operator_new(uVar13 * 8);
    puVar10 = puVar4 + uVar13 * 2;
    param_1[0x91] = (int)puVar4;
    param_1[0x93] = (int)puVar10;
    param_1[0x92] = (int)puVar4;
    do {
      if (puVar4 != (undefined4 *)0x0) {
        *puVar4 = 0;
        puVar4[1] = 0xffffffff;
      }
      uVar13 = uVar13 - 1;
      puVar4 = puVar4 + 2;
    } while (uVar13 != 0);
  }
  param_1[0x92] = (int)puVar10;
  param_1[0x94] = 0;
  param_1[0x95] = 0;
  param_1[0xa2] = 0x3f800000;
  param_1[0x9e] = (int)(param_1 + 0xa4);
  param_1[0x96] = 0;
  param_1[0x97] = 0;
  param_1[0x98] = 0;
  param_1[0x99] = 0;
  *(undefined1 *)((int)param_1 + 0x271) = 0;
  param_1[0xa0] = 0;
  param_1[0xa1] = 0;
  param_1[0xa3] = 0;
  param_1[0xa4] = 0;
  param_1[0xa5] = 0;
  param_1[0x9f] = 1;
  param_1[0xa6] = 0;
  param_1[0xa7] = 0;
  param_1[0xa8] = 0;
  param_1[0xa9] = 0;
  param_1[0xaa] = 0;
  param_1[0xaf] = 1;
  param_1[0xab] = 0;
  param_1[0xac] = 0;
  param_1[0xad] = 0;
  param_1[0xae] = 0;
  param_1[0xb0] = 0;
  param_1[0xb1] = 0;
  param_1[0xb2] = 0;
  param_1[0xb3] = 0;
  param_1[0xb4] = 0;
  param_1[0xb5] = 0;
  param_1[0xb6] = 0;
  param_1[0xb7] = 0;
  FUN_00186878(param_1 + 0xb8);
  FUN_00138d4c(param_1 + 0xf6,0,1);
  iVar6 = DAT_0007135c;
  param_1[0x11e] = 0;
  param_1[0x11f] = 0;
  iVar2 = DAT_00071360;
  param_1[0x120] = 0;
  param_1[0x121] = 0;
  iVar3 = DAT_00071364;
  param_1[0x122] = 0;
  param_1[0x123] = 0;
  param_1[0x124] = 0;
  param_1[0x125] = 0;
  param_1[0x126] = 0;
  param_1[0x127] = 0;
  param_1[0x128] = 0;
  param_1[0x129] = 0;
  param_1[0x12a] = 0;
  param_1[299] = 0;
  param_1[300] = 0;
  param_1[0x12d] = 0;
  param_1[0x12e] = 0;
  param_1[0x12f] = 0;
  param_1[0x130] = 0;
  param_1[0x131] = 0;
  param_1[0x132] = 0;
  param_1[0x133] = 0;
  param_1[0x134] = 0;
  param_1[0x135] = 0;
  param_1[0x136] = 0;
  param_1[0x137] = 0;
  param_1[0x138] = 0;
  param_1[0x139] = 0;
  param_1[0x13a] = 0;
  param_1[0x13b] = 0;
  param_1[0x13c] = 0;
  param_1[0x13d] = 0;
  _rrlogmP(3,7,1,0x94,iVar3 + 0x7080c,iVar2 + 0x707f0,iVar6 + 0x707de);
  FUN_00204064();
  piVar5 = (int *)FUN_00205d68();
  (**(code **)(*piVar5 + 8))();
  FUN_0014d1dc();
  piVar5 = operator_new(0x1c0);
  local_34 = param_1[0x8f];
  piVar5[1] = 1;
  piVar5[2] = 1;
  local_30 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)param_1[0x90];
  *piVar5 = DAT_00071368 + 0x708a8;
  if (local_30 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    if (*(int *)(iVar15 + DAT_0007136c) == 0) {
      *(int *)(local_30 + 4) = *(int *)(local_30 + 4) + 1;
    }
    else {
      p_Var11 = local_30 + 4;
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(p_Var11);
        bVar1 = (bool)hasExclusiveAccess(p_Var11);
      } while (!bVar1);
      *(int *)p_Var11 = *(int *)p_Var11 + 1;
      DataMemoryBarrier(0x1b);
    }
  }
  FUN_0018e848(piVar5 + 4,&local_34);
  if (local_30 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(local_30);
  }
  uVar14 = *(undefined4 *)(iVar15 + DAT_00071370);
  iVar6 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)param_1[0x8e];
  param_1[0x8e] = (int)piVar5;
  param_1[0x8d] = iVar6;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  uVar7 = FUN_00204064();
  uVar8 = FUN_0014d1dc();
  uVar9 = FUN_00205d68();
  iVar6 = FUN_001133e0(uVar7,uVar8,uVar9);
  param_1[0x11a] = iVar6;
  iVar6 = FUN_0012147c();
  param_1[0x11b] = iVar6;
  iVar6 = FUN_0015bff4();
  piVar16 = param_1 + 0x9e;
  param_1[0x11c] = iVar6;
  local_34 = 0;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x228);
  iVar6 = DAT_00071374;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x70960;
  FUN_00081600(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 1;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x230);
  iVar6 = DAT_00071378;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x709ac;
  FUN_00079378(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 2;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x230);
  iVar6 = DAT_0007137c;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x709f8;
  FUN_000812ac(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 8;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x230);
  iVar6 = DAT_00071380;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x70a44;
  FUN_00085c44(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 0x17;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x218);
  iVar6 = DAT_00071384;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x70a90;
  FUN_00077ea0(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 0xc;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0xa20);
  iVar6 = DAT_00071388;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x70adc;
  FUN_000a62ec(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 0x16;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x228);
  iVar6 = DAT_0007138c;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x70b28;
  FUN_0007dcf4(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 0xd;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x2d0);
  iVar6 = DAT_00071390;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x70b74;
  FUN_000985b0(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 6;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x270);
  iVar6 = DAT_00071394;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x70bc0;
  FUN_00085334(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 0x1f;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x230);
  iVar6 = DAT_00071398;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x70c0c;
  FUN_0007752c(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 0x20;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x368);
  iVar6 = DAT_0007139c;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x70c58;
  FUN_00074f28(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 0x12;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x310);
  iVar6 = DAT_000713a0;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x70ca4;
  FUN_000abfb8(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 0xe;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x6778);
  iVar6 = DAT_000713a4;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x70cf0;
  FUN_0009e4bc(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 0xf;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x340);
  iVar6 = DAT_000713a8;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x70d3c;
  FUN_000a2cf8(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 0x10;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x2b8);
  iVar6 = DAT_000713ac;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x70d88;
  FUN_000a9efc(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 0x11;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x19f8);
  iVar6 = DAT_000713b0;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x70dd4;
  FUN_000a85a0(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 7;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x440);
  iVar6 = DAT_000713b4;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x70e20;
  FUN_0007c3bc(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 9;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x228);
  iVar6 = DAT_000713b8;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x70e6c;
  FUN_0007febc(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 10;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x220);
  iVar6 = DAT_000713bc;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x70eb8;
  FUN_00087114(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 0x13;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x298);
  iVar6 = DAT_000713c0;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x70f04;
  FUN_000a0554(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 0x14;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x270);
  iVar6 = DAT_000713c4;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x70f50;
  FUN_000a0768(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 0xb;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x220);
  iVar6 = DAT_000713c8;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x70f9c;
  FUN_00085f34(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 0x15;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x288);
  iVar6 = DAT_000713cc;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x70fe6;
  FUN_0008087c(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 0x1c;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x220);
  iVar6 = DAT_000713d0;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x71030;
  FUN_000875e0(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 0x18;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x2a0);
  iVar6 = DAT_000713d4;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x7107a;
  FUN_000a922c(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 3;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x248);
  iVar6 = DAT_000713d8;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x710c4;
  FUN_000771d8(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 4;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x230);
  iVar6 = DAT_000713dc;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x7110e;
  FUN_000752d0(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 5;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x260);
  iVar6 = DAT_000713e0;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x71158;
  FUN_00081f38(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 0x1a;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x230);
  iVar6 = DAT_000713e4;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x711a2;
  FUN_000782cc(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 0x1e;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x228);
  iVar6 = DAT_000713e8;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x711ec;
  FUN_0007a914(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 0x1d;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x328);
  iVar6 = DAT_000713ec;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x71236;
  FUN_00089404(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  local_34 = 0x21;
  puVar10 = (undefined4 *)FUN_0006b218(piVar16,&local_34);
  piVar5 = operator_new(0x228);
  iVar6 = DAT_000713f0;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x71280;
  FUN_00078bc4(piVar5 + 4,param_1);
  uVar7 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)puVar10[1];
  *puVar10 = uVar7;
  puVar10[1] = piVar5;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  DataMemoryBarrier(0x1b);
  param_1[0x9b] = 0;
  DataMemoryBarrier(0x1b);
  local_34 = 0;
  piVar5 = (int *)FUN_0006b218(piVar16,&local_34);
  param_1[0x96] = *piVar5;
  std::__shared_count<(__gnu_cxx::_Lock_policy)2>::operator=
            ((__shared_count<(__gnu_cxx::_Lock_policy)2> *)(param_1 + 0x97),
             (__shared_count *)(piVar5 + 1));
  param_1[0x94] = param_1[0x96];
  std::__shared_count<(__gnu_cxx::_Lock_policy)2>::operator=
            ((__shared_count<(__gnu_cxx::_Lock_policy)2> *)(param_1 + 0x95),
             (__shared_count *)(param_1 + 0x97));
  DataMemoryBarrier(0x1b);
  param_1[0x9a] = 0;
  DataMemoryBarrier(0x1b);
  piVar5 = operator_new(0x20);
  iVar6 = DAT_000713f4;
  piVar5[1] = 1;
  piVar5[2] = 1;
  *piVar5 = iVar6 + 0x71306;
  FUN_00077d7c(piVar5 + 3,0);
  iVar6 = (**(code **)(*piVar5 + 0x10))(piVar5,uVar14);
  p_Var11 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)param_1[0x99];
  param_1[0x99] = (int)piVar5;
  param_1[0x98] = iVar6;
  if (p_Var11 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var11);
  }
  (**(code **)(*(int *)param_1[0x94] + 0x60))((int *)param_1[0x94],param_1 + 0x98);
  _rrlogmP(3,7,1,0xd3,&UNK_0007134a + DAT_00071400,DAT_000713fc + 0x71346,DAT_000713f8 + 0x71344);
  if (local_2c != *piVar12) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(param_1);
  }
  return;
}

