/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0000e314
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Reads catalog byte region8+0x98 under region guard and returns it zero-extended. Does not
   normalize arbitrary loaded bytes. */

uchar GetSharedUseNewMap(void)

{
  uchar uVar1;
  __pid_t _Var2;
  undefined *puVar3;
  int iVar4;
  int *piVar5;
  SharedRegionLockGuard aSStack_24 [8];
  int local_1c;
  
  piVar5 = *(int **)(_LAB_0000e380 + 0xe31e + _LAB_0000e384);
  iVar4 = _LAB_0000e388 + 0xe330;
  local_1c = *piVar5;
  puVar3 = &UNK_0000e37c + _LAB_0000e38c;
  SharedRegionLockGuard::SharedRegionLockGuard(aSStack_24,1,8);
  _Var2 = getpid();
  _rrlogm(0x15,6,0x71,_LAB_0000e390 + 0xe348,puVar3,iVar4,_Var2);
  iVar4 = GetSharedRegion(8,0x9c);
  uVar1 = *(uchar *)(iVar4 + 0x98);
  SharedRegionLockGuard::~SharedRegionLockGuard(aSStack_24);
  if (local_1c == *piVar5) {
    return uVar1;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

