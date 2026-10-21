/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x00083940
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Loads catalog current flag only under the lab/use-new-map gating branches, after signed
   current>=2 check. Calls LoadSLAMMap at 0x83b8a; failure switches reset state rather than
   restoring old grid/current flag. Initializes shared dock/robot poses after this branch. Not the
   missing OnStateLoadLastMap function. */

void MapFlowStartupMapSelect(void *state)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  uint native_flag;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  int *piVar9;
  bool bVar10;
  uint local_4c;
  undefined4 local_48;
  int *local_44;
  byte local_30 [4];
  int local_2c;
  
  iVar8 = DAT_00083d5c + 0x83954;
  piVar9 = *(int **)(iVar8 + DAT_00083d60);
  local_2c = *piVar9;
  uVar1 = FUN_0013f578();
  FUN_0013ce58();
  FUN_00066254(*(undefined4 *)((int)state + 0x198));
  FUN_001a6414();
  iVar2 = FUN_001a5f88();
  if (iVar2 == 0) {
    FUN_001a6414();
    iVar2 = FUN_001a5f8c();
    if ((iVar2 != 0) && (iVar2 = GetSharedUseNewMap(), iVar2 == 0)) goto LAB_00083b0a;
LAB_00083988:
    bVar10 = true;
  }
  else {
    iVar2 = GetSharedUseNewMap();
    if (iVar2 != 0) goto LAB_00083988;
LAB_00083b0a:
    iVar2 = GetSharedCurrentMapFlag();
    if (iVar2 < 2) goto LAB_00083988;
    native_flag = GetSharedCurrentMapFlag();
    iVar5 = DAT_00083d74 + 0x83b2c;
    iVar2 = DAT_00083d78 + 0x83b2e;
    local_4c = 0;
    GetSharedMultiMapList(local_30,&local_4c);
    _rrlogmP(3,6,1,0x1ef,iVar2,iVar5,DAT_00083d7c + 0x83b48,local_4c);
    if (native_flag == 0xffffffff) {
      if (local_4c == 1) {
        native_flag = (uint)local_30[0];
        goto LAB_00083b5e;
      }
      _rrlogmP(3,6,1,500,iVar2,iVar5,DAT_00083d8c + 0x83cde,0xffffffff);
LAB_00083b90:
      FUN_00066264(*(undefined4 *)((int)state + 0x198),0);
      FUN_0013f5e0(uVar1,1,1);
    }
    else {
LAB_00083b5e:
      _rrlogmP(3,6,1,500,DAT_00083d88 + 0x83b78,DAT_00083d84 + 0x83b70,DAT_00083d80 + 0x83b6e,
               native_flag);
      iVar2 = MapFlowLoadSLAMMap(*(void **)((int)state + 0x198),native_flag,1);
      if (iVar2 == 0) goto LAB_00083b90;
    }
    uVar4 = FUN_0013f578();
    FUN_0013d090(uVar4,1);
    InitSharedDockPosi();
    InitSharedRobotPosi();
    FUN_00221ff4(*(undefined4 *)((int)state + 0x244),0);
    local_48 = *(undefined4 *)((int)state + 0x244);
    local_44 = *(int **)((int)state + 0x248);
    if (local_44 != (int *)0x0) {
      if (*(int *)(iVar8 + DAT_00083d70) == 0) {
        local_44[1] = local_44[1] + 1;
      }
      else {
        piVar3 = local_44 + 1;
        DataMemoryBarrier(0x1b);
        do {
          ExclusiveAccess(piVar3);
          bVar10 = (bool)hasExclusiveAccess(piVar3);
        } while (!bVar10);
        *piVar3 = *piVar3 + 1;
        DataMemoryBarrier(0x1b);
      }
    }
    FUN_00083880(state,&local_48);
    piVar3 = local_44;
    if (local_44 != (int *)0x0) {
      if (*(int *)(iVar8 + DAT_00083d70) == 0) {
        iVar2 = local_44[1];
        local_44[1] = iVar2 + -1;
        if (iVar2 == 1) {
          (**(code **)(*local_44 + 8))(local_44);
          iVar2 = piVar3[2];
          piVar3[2] = iVar2 + -1;
          goto LAB_00083d0e;
        }
      }
      else {
        piVar7 = local_44 + 1;
        DataMemoryBarrier(0x1b);
        do {
          ExclusiveAccess(piVar7);
          iVar2 = *piVar7;
          bVar10 = (bool)hasExclusiveAccess(piVar7);
        } while (!bVar10);
        *piVar7 = iVar2 + -1;
        DataMemoryBarrier(0x1b);
        if (iVar2 == 1) {
          (**(code **)(*local_44 + 8))(local_44);
          DataMemoryBarrier(0x1b);
          piVar7 = piVar3 + 2;
          do {
            ExclusiveAccess(piVar7);
            iVar2 = *piVar7;
            bVar10 = (bool)hasExclusiveAccess(piVar7);
          } while (!bVar10);
          *piVar7 = iVar2 + -1;
          DataMemoryBarrier(0x1b);
LAB_00083d0e:
          if (iVar2 == 1) {
            (**(code **)(*piVar3 + 0xc))(piVar3);
          }
        }
      }
    }
    iVar2 = FUN_002096ac(*(undefined4 *)((int)state + 0x244));
    bVar10 = iVar2 != 0;
  }
  FUN_0013f5e0(uVar1,bVar10,1);
  FUN_00066264(*(undefined4 *)((int)state + 0x198),0);
  FUN_00066694(*(undefined4 *)((int)state + 0x198));
  FUN_0013edf0(uVar1);
  FUN_00066240(*(undefined4 *)((int)state + 0x198),0);
  iVar6 = DAT_00083d64 + 0x839ca;
  iVar5 = DAT_00083d68 + 0x839cc;
  iVar2 = DAT_00083d6c + 0x839d8;
  *(undefined1 *)((int)state + 600) = 1;
  *(undefined1 *)((int)state + 0x255) = 1;
  _rrlogmP(3,7,1,0x21b,iVar2,iVar5,iVar6);
  uVar1 = FUN_001cb230();
  piVar3 = (int *)FUN_00205d68();
  (**(code **)(*piVar3 + 0x28))(&local_48,piVar3);
  FUN_001cb6e0(uVar1,&local_48);
  FUN_001703f8(&local_48);
  local_4c = 0x7a;
  FUN_0006784c(local_48,&local_4c,0);
  piVar3 = local_44;
  if (local_44 != (int *)0x0) {
    if (*(int *)(iVar8 + DAT_00083d70) == 0) {
      iVar2 = local_44[1];
      local_44[1] = iVar2 + -1;
      if (iVar2 == 1) {
        (**(code **)(*local_44 + 8))(local_44);
        iVar2 = piVar3[2];
        piVar3[2] = iVar2 + -1;
        goto LAB_00083ca6;
      }
    }
    else {
      piVar7 = local_44 + 1;
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar7);
        iVar2 = *piVar7;
        bVar10 = (bool)hasExclusiveAccess(piVar7);
      } while (!bVar10);
      *piVar7 = iVar2 + -1;
      DataMemoryBarrier(0x1b);
      if (iVar2 == 1) {
        (**(code **)(*local_44 + 8))(local_44);
        piVar7 = piVar3 + 2;
        DataMemoryBarrier(0x1b);
        do {
          ExclusiveAccess(piVar7);
          iVar2 = *piVar7;
          bVar10 = (bool)hasExclusiveAccess(piVar7);
        } while (!bVar10);
        *piVar7 = iVar2 + -1;
        DataMemoryBarrier(0x1b);
LAB_00083ca6:
        if (iVar2 == 1) {
          (**(code **)(*piVar3 + 0xc))(piVar3);
        }
      }
    }
  }
  FUN_001ca4c4(*(undefined4 *)((int)state + 0x208));
  local_48 = 3;
  FUN_001ca4b8(*(undefined4 *)((int)state + 0x208),&local_48,0);
  local_48 = *(undefined4 *)((int)state + 0x208);
  local_44 = *(int **)((int)state + 0x20c);
  if (local_44 != (int *)0x0) {
    if (*(int *)(iVar8 + DAT_00083d70) == 0) {
      local_44[1] = local_44[1] + 1;
    }
    else {
      piVar3 = local_44 + 1;
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar3);
        bVar10 = (bool)hasExclusiveAccess(piVar3);
      } while (!bVar10);
      *piVar3 = *piVar3 + 1;
      DataMemoryBarrier(0x1b);
    }
  }
  FUN_000775fc(state,&local_48);
  piVar3 = local_44;
  if (local_44 != (int *)0x0) {
    if (*(int *)(iVar8 + DAT_00083d70) == 0) {
      iVar2 = local_44[1];
      local_44[1] = iVar2 + -1;
      if (iVar2 != 1) goto LAB_00083aba;
      (**(code **)(*local_44 + 8))(local_44);
      iVar2 = piVar3[2];
      piVar3[2] = iVar2 + -1;
    }
    else {
      piVar7 = local_44 + 1;
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar7);
        iVar2 = *piVar7;
        bVar10 = (bool)hasExclusiveAccess(piVar7);
      } while (!bVar10);
      *piVar7 = iVar2 + -1;
      DataMemoryBarrier(0x1b);
      if (iVar2 != 1) goto LAB_00083aba;
      (**(code **)(*local_44 + 8))(local_44);
      piVar7 = piVar3 + 2;
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar7);
        iVar2 = *piVar7;
        bVar10 = (bool)hasExclusiveAccess(piVar7);
      } while (!bVar10);
      *piVar7 = iVar2 + -1;
      DataMemoryBarrier(0x1b);
    }
    if (iVar2 == 1) {
      (**(code **)(*piVar3 + 0xc))(piVar3);
    }
  }
LAB_00083aba:
  if (local_2c != *piVar9) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}

