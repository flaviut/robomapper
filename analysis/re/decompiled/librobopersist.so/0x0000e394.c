/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0000e394
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Stores region8+0x98; when input is nonzero also stores current_flag=-1. Releases region guard
   before SerializeMultiMapInfo. */

void SetSharedUseNewMap(bool use_new_map)

{
  __pid_t _Var1;
  int iVar2;
  int *piVar3;
  SharedRegionLockGuard aSStack_24 [8];
  int local_1c;
  
  piVar3 = *(int **)(_LAB_0000e410 + 0xe39e + _LAB_0000e414);
  local_1c = *piVar3;
  iVar2 = _LAB_0000e418 + 0xe3b2;
  SharedRegionLockGuard::SharedRegionLockGuard(aSStack_24,1,8);
  _Var1 = getpid();
  _rrlogm(0x15,6,0x7c,_LAB_0000e420 + 0xe3c8,&LAB_0000e420 + _LAB_0000e41c,iVar2,_Var1);
  iVar2 = GetSharedRegion(8,0x9c);
  *(bool *)(iVar2 + 0x98) = use_new_map;
  if (use_new_map) {
    *(undefined4 *)(iVar2 + 0x94) = 0xffffffff;
  }
  SharedRegionLockGuard::~SharedRegionLockGuard(aSStack_24);
  SerializeMultiMapInfo();
  if (local_1c == *piVar3) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

