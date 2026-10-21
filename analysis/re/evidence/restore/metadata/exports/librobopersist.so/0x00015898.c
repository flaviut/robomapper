/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x00015898
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* SetSharedSegmentMapGridData(SharedSegmentMapGridData const&) */

void SetSharedSegmentMapGridData(SharedSegmentMapGridData *param_1)

{
  __pid_t _Var1;
  int iVar2;
  int *piVar3;
  SharedRegionLockGuard aSStack_24 [8];
  int local_1c;
  
  piVar3 = *(int **)(_LAB_0001591c + 0x158a2 + _LAB_00015920);
  local_1c = *piVar3;
  iVar2 = _LAB_00015924 + 0x158b4;
  SharedRegionLockGuard::SharedRegionLockGuard(aSStack_24,5);
  _Var1 = getpid();
  _rrlogm(0x15,6,0x14a,_LAB_0001592c + 0x158ce,_LAB_00015928 + 0x15ab8,iVar2,_Var1);
  iVar2 = GetSharedRegion(5,0x13f120);
  memcpy((void *)(iVar2 + 0x31da4),param_1,0x10000c);
  SharedRegionLockGuard::~SharedRegionLockGuard(aSStack_24);
  if (local_1c == *piVar3) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

