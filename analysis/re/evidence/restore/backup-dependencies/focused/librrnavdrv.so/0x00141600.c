/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x00141600
 */

void FUN_00141600(undefined1 *param_1,char *param_2,char *param_3,int param_4)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  char *__dest;
  uint uVar6;
  int *piVar7;
  int iVar8;
  char *pcVar9;
  allocator *paVar10;
  int iVar11;
  int iVar12;
  int *piVar13;
  allocator aaStack_40 [4];
  allocator aaStack_3c [4];
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  
  iVar12 = DAT_00141b7c + 0x141616;
  piVar7 = *(int **)(iVar12 + DAT_00141b80);
  local_2c = *piVar7;
  piVar3 = operator_new(0x18);
  iVar8 = DAT_00141b84 + 0x141638;
  piVar3[1] = 1;
  piVar3[2] = 1;
  *piVar3 = iVar8;
  libconfig::Config::Config((Config *)(piVar3 + 3));
  uVar4 = (**(code **)(*piVar3 + 0x10))(piVar3,*(undefined4 *)(iVar12 + DAT_00141b88));
  piVar13 = *(int **)(param_1 + 0x108);
  *(int **)(param_1 + 0x108) = piVar3;
  *(undefined4 *)(param_1 + 0x104) = uVar4;
  if (piVar13 != (int *)0x0) {
    if (*(int *)(iVar12 + DAT_00141b8c) == 0) {
      iVar8 = piVar13[1];
      piVar13[1] = iVar8 + -1;
      if (iVar8 != 1) goto LAB_00141684;
      (**(code **)(*piVar13 + 8))(piVar13);
      iVar8 = piVar13[2];
      piVar13[2] = iVar8 + -1;
    }
    else {
      piVar3 = piVar13 + 1;
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar3);
        iVar8 = *piVar3;
        bVar1 = (bool)hasExclusiveAccess(piVar3);
      } while (!bVar1);
      *piVar3 = iVar8 + -1;
      DataMemoryBarrier(0x1b);
      if (iVar8 != 1) goto LAB_00141684;
      (**(code **)(*piVar13 + 8))(piVar13);
      piVar3 = piVar13 + 2;
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar3);
        iVar8 = *piVar3;
        bVar1 = (bool)hasExclusiveAccess(piVar3);
      } while (!bVar1);
      *piVar3 = iVar8 + -1;
      DataMemoryBarrier(0x1b);
    }
    if (iVar8 == 1) {
      (**(code **)(*piVar13 + 0xc))(piVar13);
    }
  }
LAB_00141684:
  iVar2 = DAT_00141b98;
  iVar11 = DAT_00141b94;
  iVar8 = DAT_00141b90;
  param_1[0x110] = 1;
  *(undefined4 *)(param_1 + 0x10c) = 0;
  __dest = param_1 + 1;
  *param_1 = 0;
  _rrlogmP(3,7,1,0x20,iVar2 + 0x1416b4,iVar11 + 0x1416b0,iVar8 + 0x1416ae,param_3);
  std::string::string((string *)&local_34,param_3,aaStack_3c);
  piVar3 = (int *)std::string::append((char *)&local_34,DAT_00141b9c + 0x1416e2);
  local_30 = *piVar3;
  paVar10 = *(allocator **)(iVar12 + DAT_00141ba0);
  *piVar3 = (int)(paVar10 + 0xc);
  strlen(param_2);
  puVar5 = (undefined4 *)std::string::append((char *)&local_30,(uint)param_2);
  pcVar9 = (char *)*puVar5;
  *puVar5 = paVar10 + 0xc;
  strncpy(__dest,pcVar9,0x80);
  if ((allocator *)(pcVar9 + -0xc) != paVar10) {
    if (*(int *)(iVar12 + DAT_00141b8c) == 0) {
      iVar8 = *(int *)(pcVar9 + -4);
      *(int *)(pcVar9 + -4) = iVar8 + -1;
    }
    else {
      piVar3 = (int *)(pcVar9 + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar3);
        iVar8 = *piVar3;
        bVar1 = (bool)hasExclusiveAccess(piVar3);
      } while (!bVar1);
      *piVar3 = iVar8 + -1;
      DataMemoryBarrier(0x1b);
    }
    if (iVar8 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(pcVar9 + -0xc));
    }
  }
  if ((allocator *)(local_30 + -0xc) != paVar10) {
    if (*(int *)(iVar12 + DAT_00141b8c) == 0) {
      iVar8 = *(int *)(local_30 + -4);
      *(int *)(local_30 + -4) = iVar8 + -1;
    }
    else {
      piVar3 = (int *)(local_30 + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar3);
        iVar8 = *piVar3;
        bVar1 = (bool)hasExclusiveAccess(piVar3);
      } while (!bVar1);
      *piVar3 = iVar8 + -1;
      DataMemoryBarrier(0x1b);
    }
    if (iVar8 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_30 + -0xc));
    }
  }
  if ((allocator *)(local_34 + -0xc) != paVar10) {
    if (*(int *)(iVar12 + DAT_00141b8c) == 0) {
      iVar8 = *(int *)(local_34 + -4);
      *(int *)(local_34 + -4) = iVar8 + -1;
    }
    else {
      piVar3 = (int *)(local_34 + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar3);
        iVar8 = *piVar3;
        bVar1 = (bool)hasExclusiveAccess(piVar3);
      } while (!bVar1);
      *piVar3 = iVar8 + -1;
      DataMemoryBarrier(0x1b);
    }
    if (iVar8 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_34 + -0xc));
    }
  }
  std::string::string((string *)&local_38,param_3,aaStack_40);
  piVar3 = (int *)std::string::append((char *)&local_38,DAT_00141ba4 + 0x141766);
  local_34 = *piVar3;
  *piVar3 = (int)(paVar10 + 0xc);
  strlen(param_2);
  piVar3 = (int *)std::string::append((char *)&local_34,(uint)param_2);
  local_30 = *piVar3;
  uVar6 = DAT_00141ba8 + 0x14179a;
  *piVar3 = (int)(paVar10 + 0xc);
  puVar5 = (undefined4 *)std::string::append((char *)&local_30,uVar6);
  pcVar9 = (char *)*puVar5;
  *puVar5 = paVar10 + 0xc;
  strncpy(param_1 + 0x81,pcVar9,0x80);
  if ((allocator *)(pcVar9 + -0xc) != paVar10) {
    if (*(int *)(iVar12 + DAT_00141b8c) == 0) {
      iVar8 = *(int *)(pcVar9 + -4);
      *(int *)(pcVar9 + -4) = iVar8 + -1;
    }
    else {
      piVar3 = (int *)(pcVar9 + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar3);
        iVar8 = *piVar3;
        bVar1 = (bool)hasExclusiveAccess(piVar3);
      } while (!bVar1);
      *piVar3 = iVar8 + -1;
      DataMemoryBarrier(0x1b);
    }
    if (iVar8 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(pcVar9 + -0xc));
    }
  }
  if ((allocator *)(local_30 + -0xc) != paVar10) {
    if (*(int *)(iVar12 + DAT_00141b8c) == 0) {
      iVar8 = *(int *)(local_30 + -4);
      *(int *)(local_30 + -4) = iVar8 + -1;
    }
    else {
      piVar3 = (int *)(local_30 + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar3);
        iVar8 = *piVar3;
        bVar1 = (bool)hasExclusiveAccess(piVar3);
      } while (!bVar1);
      *piVar3 = iVar8 + -1;
      DataMemoryBarrier(0x1b);
    }
    if (iVar8 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_30 + -0xc));
    }
  }
  if ((allocator *)(local_34 + -0xc) != paVar10) {
    if (*(int *)(iVar12 + DAT_00141b8c) == 0) {
      iVar8 = *(int *)(local_34 + -4);
      *(int *)(local_34 + -4) = iVar8 + -1;
    }
    else {
      piVar3 = (int *)(local_34 + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar3);
        iVar8 = *piVar3;
        bVar1 = (bool)hasExclusiveAccess(piVar3);
      } while (!bVar1);
      *piVar3 = iVar8 + -1;
      DataMemoryBarrier(0x1b);
    }
    if (iVar8 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_34 + -0xc));
    }
  }
  if ((allocator *)(local_38 + -0xc) != paVar10) {
    if (*(int *)(iVar12 + DAT_00141b8c) == 0) {
      iVar8 = *(int *)(local_38 + -4);
      *(int *)(local_38 + -4) = iVar8 + -1;
    }
    else {
      piVar3 = (int *)(local_38 + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar3);
        iVar8 = *piVar3;
        bVar1 = (bool)hasExclusiveAccess(piVar3);
      } while (!bVar1);
      *piVar3 = iVar8 + -1;
      DataMemoryBarrier(0x1b);
    }
    if (iVar8 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_38 + -0xc));
    }
  }
  if (param_4 - 1U < 2) {
    libconfig::Config::readFile(*(char **)(param_1 + 0x104));
    iVar8 = libconfig::Config::getRoot();
    *(int *)(param_1 + 0x10c) = iVar8;
  }
  else {
    iVar8 = libconfig::Config::getRoot();
    *(int *)(param_1 + 0x10c) = iVar8;
  }
  if (iVar8 == 0) {
    _rrlogmP(3,3,1,0x43,DAT_00141bc0 + 0x141886,DAT_00141bbc + 0x141882,DAT_00141bb8 + 0x141880,
             __dest);
  }
  else {
    iVar12 = DAT_00141bac + 0x14180c;
    iVar8 = DAT_00141bb0 + 0x14180e;
    iVar11 = DAT_00141bb4 + 0x141814;
    param_1[0x110] = 0;
    _rrlogmP(3,7,1,0x3f,iVar11,iVar8,iVar12,__dest);
  }
  if (local_2c != *piVar7) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}

