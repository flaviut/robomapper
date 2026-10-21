/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x000157fc
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* SetSharedSegmentMap(SharedSegmentMapData const&) */

void SetSharedSegmentMap(SharedSegmentMapData *param_1)

{
  __pid_t _Var1;
  int iVar2;
  int iVar3;
  int *piVar4;
  SharedRegionLockGuard aSStack_24 [8];
  int local_1c;
  
  piVar4 = *(int **)(_LAB_00015884 + 0x1580e + _LAB_00015888);
  iVar2 = _LAB_0001588c + 0x159f6;
  local_1c = *piVar4;
  iVar3 = _LAB_00015890 + 0x15822;
  SharedRegionLockGuard::SharedRegionLockGuard(aSStack_24,5);
  _Var1 = getpid();
  _rrlogm(0x15,6,0x141,_LAB_00015894 + 0x15836,iVar2,iVar3,_Var1);
  iVar2 = GetSharedRegion(5,0x13f120);
  memcpy((void *)(iVar2 + 0x31da0),param_1,0x1001a4);
  SharedRegionLockGuard::~SharedRegionLockGuard(aSStack_24);
  if (local_1c == *piVar4) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

