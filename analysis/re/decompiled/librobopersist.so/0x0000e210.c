/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0000e210
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Returns signed 32-bit catalog current_flag at region8+0x94 under SharedRegionLockGuard(1,8). -1
   is initialized/no-current sentinel; this is not an external ID or grid index. */

MapPersistFlag GetSharedCurrentMapFlag(void)

{
  __pid_t _Var1;
  int iVar2;
  MapPersistFlag MVar3;
  int iVar4;
  int *piVar5;
  SharedRegionLockGuard aSStack_24 [8];
  int local_1c;
  
  piVar5 = *(int **)(_LAB_0000e27c + 0xe21a + _LAB_0000e280);
  iVar4 = _LAB_0000e284 + 0xe22c;
  local_1c = *piVar5;
  iVar2 = _LAB_0000e288 + 0xe248;
  SharedRegionLockGuard::SharedRegionLockGuard(aSStack_24,1,8);
  _Var1 = getpid();
  _rrlogm(0x15,6,0x5a,_LAB_0000e28c + 0xe244,iVar2,iVar4,_Var1);
  iVar2 = GetSharedRegion(8,0x9c);
  MVar3 = *(MapPersistFlag *)(iVar2 + 0x94);
  SharedRegionLockGuard::~SharedRegionLockGuard(aSStack_24);
  if (local_1c == *piVar5) {
    return MVar3;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

