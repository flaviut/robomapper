/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x001a7624
 */

void FUN_001a7624(int param_1,undefined4 param_2)

{
  bool bVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int local_38;
  int local_34;
  int *local_30;
  int *local_2c;
  int *local_28;
  int local_24;
  int local_20;
  int local_1c;
  
  iVar3 = DAT_001a770c + 0x1a7636;
  piVar4 = *(int **)(iVar3 + DAT_001a7710);
  local_38 = 1;
  local_1c = *piVar4;
  FUN_001a73b4(&local_34,param_1,param_2);
  local_20 = *(int *)(param_1 + 8);
  local_30 = (int *)0x0;
  local_24 = local_34;
  local_2c = (int *)0x0;
  local_28 = (int *)0x0;
  local_30 = operator_new(8);
  local_2c = local_30 + 2;
  *local_30 = local_24;
  local_30[1] = local_20;
  local_28 = local_2c;
  FUN_0015d268(param_1 + 0x34,&local_30,0xffffffff,&local_38);
  if (local_30 != (int *)0x0) {
    operator_delete(local_30);
  }
  if ((allocator *)(local_34 + -0xc) != *(allocator **)(iVar3 + DAT_001a7714)) {
    if (*(int *)(iVar3 + DAT_001a7718) == 0) {
      iVar3 = *(int *)(local_34 + -4);
      *(int *)(local_34 + -4) = iVar3 + -1;
    }
    else {
      piVar2 = (int *)(local_34 + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar2);
        iVar3 = *piVar2;
        bVar1 = (bool)hasExclusiveAccess(piVar2);
      } while (!bVar1);
      *piVar2 = iVar3 + -1;
      DataMemoryBarrier(0x1b);
    }
    if (iVar3 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_34 + -0xc));
    }
  }
  if (local_1c != *piVar4) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(local_38 != 0);
  }
  return;
}

