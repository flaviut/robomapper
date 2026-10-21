/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0000e290
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Stores full 32-bit flag at region8+0x94 under guard, releases guard, then SerializeMultiMapInfo.
   No flag range validation or load-success check here. */

void SetSharedCurrentMapFlag(MapPersistFlag flag)

{
  __pid_t _Var1;
  int iVar2;
  int *piVar3;
  SharedRegionLockGuard aSStack_24 [8];
  int local_1c;
  
  piVar3 = *(int **)(_LAB_0000e300 + 0xe29a + _LAB_0000e304);
  local_1c = *piVar3;
  iVar2 = _LAB_0000e308 + 0xe2ae;
  SharedRegionLockGuard::SharedRegionLockGuard(aSStack_24,1,8);
  _Var1 = getpid();
  _rrlogm(0x15,6,0x65,_LAB_0000e310 + 0xe2c4,_LAB_0000e30c + 0xe2f0,iVar2,_Var1);
  iVar2 = GetSharedRegion(8,0x9c);
  *(MapPersistFlag *)(iVar2 + 0x94) = flag;
  SharedRegionLockGuard::~SharedRegionLockGuard(aSStack_24);
  SerializeMultiMapInfo();
  if (local_1c == *piVar3) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

