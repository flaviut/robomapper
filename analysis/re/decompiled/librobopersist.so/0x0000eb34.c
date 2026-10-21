/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0000eb34
 */

/* Scans four primary bytes for first zero. Stores low flag byte there and full flag at
   current+0x94, unlocks, serializes and returns 1; full catalog returns 0 without save. No
   duplicate/range check, no backup/name clearing here. Success does not reflect serialization
   result. */

bool InsertMultiMap(MapPersistFlag flag)

{
  bool bVar1;
  __pid_t _Var2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  SharedRegionLockGuard aSStack_24 [8];
  int local_1c;
  
  piVar5 = *(int **)(DAT_0000ebc4 + 0xeb3c + DAT_0000ebc8);
  local_1c = *piVar5;
  iVar6 = DAT_0000ebcc + 0xeb4c;
  _Var2 = getpid();
  _rrlogm(0x15,6,0x1ca,DAT_0000ebd4 + 0xeb68,DAT_0000ebd0 + 0xec7c,iVar6,_Var2);
  iVar3 = GetSharedRegion(8,0x9c);
  SharedRegionLockGuard::SharedRegionLockGuard(aSStack_24,1,8);
  iVar4 = 0;
  iVar6 = iVar3;
  do {
    if (*(char *)(iVar6 + 1) == '\0') {
      *(char *)(iVar4 * 0x24 + iVar3 + 1) = (char)flag;
      *(MapPersistFlag *)(iVar3 + 0x94) = flag;
      SharedRegionLockGuard::~SharedRegionLockGuard(aSStack_24);
      SerializeMultiMapInfo();
      bVar1 = true;
      goto LAB_0000eb9a;
    }
    iVar4 = iVar4 + 1;
    iVar6 = iVar6 + 0x24;
  } while (iVar4 != 4);
  SharedRegionLockGuard::~SharedRegionLockGuard(aSStack_24);
  bVar1 = false;
LAB_0000eb9a:
  if (local_1c == *piVar5) {
    return bVar1;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

