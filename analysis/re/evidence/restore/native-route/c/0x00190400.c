/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x00190400
 */

void FUN_00190400(undefined4 param_1,byte *param_2,undefined4 *param_3)

{
  undefined1 uVar1;
  bool bVar2;
  _Sp_counted_ptr_inplace<std::mutex,std::allocator<std::mutex>,(__gnu_cxx::_Lock_policy)2> *p_Var3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  int *piVar8;
  undefined4 uVar9;
  undefined1 uVar10;
  int *piVar11;
  int *piVar12;
  int iVar13;
  _Sp_counted_ptr_inplace<std::mutex,std::allocator<std::mutex>,(__gnu_cxx::_Lock_policy)2> *p_Var14
  ;
  int iVar15;
  type_info *ptVar16;
  int *piVar17;
  int iVar18;
  int iVar19;
  int *local_84;
  int *local_80;
  int local_7c;
  undefined4 local_78;
  int *local_74;
  int local_70 [2];
  condition_variable acStack_68 [48];
  undefined4 local_38;
  _Sp_counted_ptr_inplace<std::mutex,std::allocator<std::mutex>,(__gnu_cxx::_Lock_policy)2>
  *local_34;
  int local_2c;
  
  iVar15 = DAT_001908c4 + 0x190418;
  piVar11 = *(int **)(iVar15 + DAT_001908c8);
  local_70[0] = DAT_001908cc + 0x19042e;
  local_2c = *piVar11;
  std::condition_variable::condition_variable(acStack_68);
  local_38 = 0;
  local_34 = (_Sp_counted_ptr_inplace<std::mutex,std::allocator<std::mutex>,(__gnu_cxx::_Lock_policy)2>
              *)0x0;
  local_34 = operator_new(0x24);
  iVar5 = DAT_001908d4;
  iVar7 = DAT_001908d0;
  *(undefined4 *)(local_34 + 4) = 1;
  *(undefined4 *)(local_34 + 8) = 1;
  *(int *)local_34 = *(int *)(iVar15 + iVar7) + 8;
  *(undefined4 *)(local_34 + 0xc) = 0;
  *(undefined4 *)(local_34 + 0x10) = 0;
  *(undefined4 *)(local_34 + 0x14) = 0;
  *(undefined4 *)(local_34 + 0x18) = 0;
  *(undefined4 *)(local_34 + 0x1c) = 0;
  *(undefined4 *)(local_34 + 0x20) = 0;
  ptVar16 = *(type_info **)(iVar15 + iVar5);
  local_38 = std::
             _Sp_counted_ptr_inplace<std::mutex,std::allocator<std::mutex>,(__gnu_cxx::_Lock_policy)2>
             ::_M_get_deleter(local_34,ptVar16);
  piVar4 = operator_new(0x14);
  iVar7 = DAT_001908d8;
  piVar4[1] = 1;
  piVar4[2] = 1;
  *piVar4 = iVar7 + 0x19048c;
  piVar4[3] = 0;
  *(undefined1 *)(piVar4 + 4) = 0;
  *(undefined1 *)((int)piVar4 + 0x11) = 0;
  iVar5 = FUN_0018df4c(piVar4,ptVar16);
  piVar6 = operator_new(0xa0);
  iVar7 = DAT_001908dc;
  piVar6[1] = 1;
  piVar6[2] = 1;
  *piVar6 = iVar7 + 0x1904b4;
  FUN_00138d4c(piVar6 + 4,0);
  piVar17 = piVar4 + 1;
  iVar7 = (**(code **)(*piVar6 + 0x10))(piVar6,ptVar16);
  iVar15 = *(int *)(iVar15 + DAT_001908e0);
  if (iVar15 == 0) {
    iVar13 = piVar6[1];
    piVar4[1] = piVar4[1] + 1;
    piVar6[1] = iVar13 + 1;
  }
  else {
    DataMemoryBarrier(0x1b);
    do {
      ExclusiveAccess(piVar17);
      bVar2 = (bool)hasExclusiveAccess(piVar17);
    } while (!bVar2);
    *piVar17 = *piVar17 + 1;
    DataMemoryBarrier(0x1b);
    piVar8 = piVar6 + 1;
    DataMemoryBarrier(0x1b);
    do {
      ExclusiveAccess(piVar8);
      bVar2 = (bool)hasExclusiveAccess(piVar8);
    } while (!bVar2);
    *piVar8 = *piVar8 + 1;
    DataMemoryBarrier(0x1b);
  }
  local_84 = piVar6 + 1;
  piVar8 = operator_new(0x10);
  *piVar8 = iVar5;
  piVar8[1] = (int)piVar4;
  if (iVar15 == 0) {
    iVar13 = piVar6[1];
    iVar18 = piVar4[1];
    piVar8[2] = iVar7;
    piVar8[3] = (int)piVar6;
    piVar4[1] = iVar18 + 1;
    if (iVar13 == 0) {
      (**(code **)(*piVar6 + 8))(piVar6);
      iVar13 = piVar6[2];
      piVar6[2] = iVar13 + -1;
      goto LAB_001907a0;
    }
LAB_0019056c:
    if (iVar15 != 0) goto LAB_00190572;
LAB_001906c4:
    iVar13 = piVar4[1];
    piVar4[1] = iVar13 + -1;
    if (iVar13 == 1) {
      (**(code **)(*piVar4 + 8))(piVar4);
      iVar13 = piVar4[2];
      piVar4[2] = iVar13 + -1;
      goto LAB_0019086e;
    }
  }
  else {
    DataMemoryBarrier(0x1b);
    do {
      ExclusiveAccess(piVar17);
      bVar2 = (bool)hasExclusiveAccess(piVar17);
    } while (!bVar2);
    *piVar17 = *piVar17 + 1;
    DataMemoryBarrier(0x1b);
    piVar8[3] = (int)piVar6;
    piVar8[2] = iVar7;
    DataMemoryBarrier(0x1b);
    do {
      ExclusiveAccess(local_84);
      bVar2 = (bool)hasExclusiveAccess(local_84);
    } while (!bVar2);
    *local_84 = *local_84 + 1;
    DataMemoryBarrier(0x1b);
    DataMemoryBarrier(0x1b);
    do {
      ExclusiveAccess(local_84);
      iVar13 = *local_84;
      bVar2 = (bool)hasExclusiveAccess(local_84);
    } while (!bVar2);
    *local_84 = iVar13 + -1;
    DataMemoryBarrier(0x1b);
    if (iVar13 != 1) goto LAB_0019056c;
    (**(code **)(*piVar6 + 8))(piVar6);
    piVar12 = piVar6 + 2;
    DataMemoryBarrier(0x1b);
    do {
      ExclusiveAccess(piVar12);
      iVar13 = *piVar12;
      bVar2 = (bool)hasExclusiveAccess(piVar12);
    } while (!bVar2);
    *piVar12 = iVar13 + -1;
    DataMemoryBarrier(0x1b);
LAB_001907a0:
    if (iVar13 != 1) goto LAB_0019056c;
    (**(code **)(*piVar6 + 0xc))(piVar6);
    if (iVar15 == 0) goto LAB_001906c4;
LAB_00190572:
    DataMemoryBarrier(0x1b);
    do {
      ExclusiveAccess(piVar17);
      iVar13 = *piVar17;
      bVar2 = (bool)hasExclusiveAccess(piVar17);
    } while (!bVar2);
    *piVar17 = iVar13 + -1;
    DataMemoryBarrier(0x1b);
    if (iVar13 == 1) {
      (**(code **)(*piVar4 + 8))(piVar4);
      piVar12 = piVar4 + 2;
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar12);
        iVar13 = *piVar12;
        bVar2 = (bool)hasExclusiveAccess(piVar12);
      } while (!bVar2);
      *piVar12 = iVar13 + -1;
      DataMemoryBarrier(0x1b);
LAB_0019086e:
      if (iVar13 == 1) {
        (**(code **)(*piVar4 + 0xc))(piVar4);
      }
    }
  }
  local_78 = param_3[1];
  iVar13 = DAT_001908e4 + 0x1905a2;
  iVar18 = DAT_001908e8 + 0x1905a6;
  iVar19 = DAT_001908ec + 0x1905b8;
  local_7c = DAT_001908f0 + 0x1905cc;
  *param_2 = *param_2 | 2;
  local_74 = piVar8;
  _rrlogmP(3,7,1,0x4e4,iVar13,iVar19,iVar18,local_78);
  uVar9 = SendPacketEx(param_1,param_2,&local_7c);
  local_80 = local_70;
  iVar7 = FUN_0011dd5c(local_80,&local_80,*param_3,iVar7);
  if (iVar7 == 0) {
    uVar1 = *(undefined1 *)(param_3 + 3);
    uVar10 = 1;
    *(undefined1 *)((int)param_3 + 0xd) = 1;
  }
  else {
    uVar10 = *(undefined1 *)((int)param_3 + 0xd);
    uVar1 = *(undefined1 *)(iVar5 + 4);
    *(undefined1 *)(param_3 + 3) = uVar1;
  }
  _rrlogmP(3,7,1,0x4f2,DAT_001908fc + 0x190620,DAT_001908f8 + 0x19061c,DAT_001908f4 + 0x19061a,uVar9
           ,uVar1,uVar10);
  if (iVar15 == 0) {
    iVar7 = piVar6[1];
    piVar6[1] = iVar7 + -1;
    if (iVar7 == 1) {
      (**(code **)(*piVar6 + 8))(piVar6);
      iVar7 = piVar6[2];
      piVar6[2] = iVar7 + -1;
      goto LAB_001907d8;
    }
  }
  else {
    DataMemoryBarrier(0x1b);
    do {
      ExclusiveAccess(local_84);
      iVar7 = *local_84;
      bVar2 = (bool)hasExclusiveAccess(local_84);
    } while (!bVar2);
    *local_84 = iVar7 + -1;
    DataMemoryBarrier(0x1b);
    if (iVar7 == 1) {
      (**(code **)(*piVar6 + 8))(piVar6);
      piVar8 = piVar6 + 2;
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar8);
        iVar7 = *piVar8;
        bVar2 = (bool)hasExclusiveAccess(piVar8);
      } while (!bVar2);
      *piVar8 = iVar7 + -1;
      DataMemoryBarrier(0x1b);
LAB_001907d8:
      if (iVar7 == 1) {
        (**(code **)(*piVar6 + 0xc))(piVar6);
      }
    }
  }
  if (iVar15 == 0) {
    iVar7 = piVar4[1];
    piVar4[1] = iVar7 + -1;
    if (iVar7 == 1) {
      (**(code **)(*piVar4 + 8))(piVar4);
      iVar7 = piVar4[2];
      piVar4[2] = iVar7 + -1;
      goto LAB_0019083c;
    }
  }
  else {
    DataMemoryBarrier(0x1b);
    do {
      ExclusiveAccess(piVar17);
      iVar7 = *piVar17;
      bVar2 = (bool)hasExclusiveAccess(piVar17);
    } while (!bVar2);
    *piVar17 = iVar7 + -1;
    DataMemoryBarrier(0x1b);
    if (iVar7 == 1) {
      (**(code **)(*piVar4 + 8))(piVar4);
      piVar6 = piVar4 + 2;
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar6);
        iVar7 = *piVar6;
        bVar2 = (bool)hasExclusiveAccess(piVar6);
      } while (!bVar2);
      *piVar6 = iVar7 + -1;
      DataMemoryBarrier(0x1b);
LAB_0019083c:
      if (iVar7 == 1) {
        (**(code **)(*piVar4 + 0xc))(piVar4);
      }
    }
  }
  p_Var3 = local_34;
  local_70[0] = DAT_00190900 + 0x19068c;
  if (local_34 !=
      (_Sp_counted_ptr_inplace<std::mutex,std::allocator<std::mutex>,(__gnu_cxx::_Lock_policy)2> *)
      0x0) {
    if (iVar15 == 0) {
      iVar7 = *(int *)(local_34 + 4);
      *(int *)(local_34 + 4) = iVar7 + -1;
      if (iVar7 != 1) goto LAB_001906aa;
      (**(code **)(*(int *)local_34 + 8))(local_34);
      iVar7 = *(int *)(p_Var3 + 8);
      *(int *)(p_Var3 + 8) = iVar7 + -1;
    }
    else {
      p_Var14 = local_34 + 4;
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(p_Var14);
        iVar7 = *(int *)p_Var14;
        bVar2 = (bool)hasExclusiveAccess(p_Var14);
      } while (!bVar2);
      *(int *)p_Var14 = iVar7 + -1;
      DataMemoryBarrier(0x1b);
      if (iVar7 != 1) goto LAB_001906aa;
      (**(code **)(*(int *)local_34 + 8))(local_34);
      p_Var14 = p_Var3 + 8;
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(p_Var14);
        iVar7 = *(int *)p_Var14;
        bVar2 = (bool)hasExclusiveAccess(p_Var14);
      } while (!bVar2);
      *(int *)p_Var14 = iVar7 + -1;
      DataMemoryBarrier(0x1b);
    }
    if (iVar7 == 1) {
      (**(code **)(*(int *)p_Var3 + 0xc))(p_Var3);
    }
  }
LAB_001906aa:
  std::condition_variable::~condition_variable(acStack_68);
  if (local_2c != *piVar11) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(uVar9);
  }
  return;
}

