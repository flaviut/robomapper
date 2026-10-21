/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0000e4a4
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Under region8 guard, counts four entries whose primary flag byte is nonzero (stride 0x24). No
   primary-range validation. */

uint GetSharedUserMapCount(void)

{
  __pid_t _Var1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  SharedRegionLockGuard aSStack_24 [8];
  int local_1c;
  
  piVar4 = *(int **)(_LAB_0000e520 + 0xe4ae + _LAB_0000e524);
  iVar5 = _LAB_0000e528 + 0xe4c0;
  local_1c = *piVar4;
  iVar2 = _LAB_0000e52c + 0xe54c;
  SharedRegionLockGuard::SharedRegionLockGuard(aSStack_24,1,8);
  _Var1 = getpid();
  _rrlogm(0x15,6,0x96,_LAB_0000e530 + 0xe4d8,iVar2,iVar5,_Var1);
  iVar2 = GetSharedRegion(8,0x9c);
  iVar5 = iVar2 + 0x90;
  uVar3 = 0;
  do {
    if (*(char *)(iVar2 + 1) != '\0') {
      uVar3 = uVar3 + 1;
    }
    iVar2 = iVar2 + 0x24;
  } while (iVar2 != iVar5);
  SharedRegionLockGuard::~SharedRegionLockGuard(aSStack_24);
  if (local_1c == *piVar4) {
    return uVar3;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

