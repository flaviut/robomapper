/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x001a7488
 */

void FUN_001a7488(int param_1,undefined4 param_2,undefined4 param_3)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  allocator *paVar5;
  int *piVar6;
  undefined4 local_44 [2];
  int local_3c;
  int *local_38;
  int *local_34;
  int *local_30;
  int local_2c;
  int local_28;
  int local_24;
  
  iVar4 = DAT_001a7608 + 0x1a749a;
  piVar6 = *(int **)(iVar4 + DAT_001a760c);
  local_24 = *piVar6;
  local_44[0] = param_3;
  FUN_001a73b4(&local_38,param_1,param_2);
  _rrlogmP(3,6,1,0xcd,DAT_001a7618 + 0x1a74d0,DAT_001a7614 + 0x1a74c6,DAT_001a7610 + 0x1a74c2,
           local_38,local_44[0]);
  paVar5 = *(allocator **)(iVar4 + DAT_001a761c);
  if ((allocator *)(local_38 + -3) != paVar5) {
    if (*(int *)(iVar4 + DAT_001a7620) == 0) {
      iVar2 = local_38[-1];
      local_38[-1] = iVar2 + -1;
    }
    else {
      piVar3 = local_38 + -1;
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar3);
        iVar2 = *piVar3;
        bVar1 = (bool)hasExclusiveAccess(piVar3);
      } while (!bVar1);
      *piVar3 = iVar2 + -1;
      DataMemoryBarrier(0x1b);
    }
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_38 + -3));
    }
  }
  FUN_001a73b4(&local_3c,param_1,param_2);
  local_28 = *(int *)(param_1 + 8);
  local_38 = (int *)0x0;
  local_2c = local_3c;
  local_34 = (int *)0x0;
  local_30 = (int *)0x0;
  local_38 = operator_new(8);
  local_34 = local_38 + 2;
  *local_38 = local_2c;
  local_38[1] = local_28;
  local_30 = local_34;
  FUN_0015cd40(param_1 + 0x34,&local_38,0xffffffff,local_44);
  if (local_38 != (int *)0x0) {
    operator_delete(local_38);
  }
  if ((allocator *)(local_3c + -0xc) != paVar5) {
    if (*(int *)(iVar4 + DAT_001a7620) == 0) {
      iVar4 = *(int *)(local_3c + -4);
      *(int *)(local_3c + -4) = iVar4 + -1;
    }
    else {
      piVar3 = (int *)(local_3c + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar3);
        iVar4 = *piVar3;
        bVar1 = (bool)hasExclusiveAccess(piVar3);
      } while (!bVar1);
      *piVar3 = iVar4 + -1;
      DataMemoryBarrier(0x1b);
    }
    if (iVar4 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_3c + -0xc));
    }
  }
  FUN_00141c24(param_1 + 0x34);
  if (local_24 == *piVar6) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

