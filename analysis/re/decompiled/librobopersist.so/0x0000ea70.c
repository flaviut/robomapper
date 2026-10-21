/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0000ea70
 */

/* Matches primary, stores low length byte at entry+3, clears 32 bytes at entry+4, then memcpy with
   full caller-supplied length (no bound check in this function). Exactly 32 bytes need not have
   terminator. Unlocks, serializes and returns 1; missing primary returns 0. Success is not a
   write/durability acknowledgment. */

bool NameMultiMap(MapPersistFlag primary_flag,char *name_bytes,int name_length)

{
  bool bVar1;
  __pid_t _Var2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  void *__s;
  SharedRegionLockGuard aSStack_2c [8];
  int local_24;
  
  piVar6 = *(int **)(DAT_0000eb20 + 0xea7e + DAT_0000eb24);
  local_24 = *piVar6;
  _Var2 = getpid();
  _rrlogm(0x15,6,0x1a9,DAT_0000eb30 + 0xeaac,DAT_0000eb28 + 0xebae,DAT_0000eb2c + 0xeaa0,_Var2);
  iVar3 = GetSharedRegion(8,0x9c);
  SharedRegionLockGuard::SharedRegionLockGuard(aSStack_2c,1,8);
  iVar5 = 0;
  iVar4 = iVar3;
  do {
    if ((uint)*(byte *)(iVar4 + 1) == primary_flag) {
      iVar3 = iVar5 * 0x24 + iVar3;
      __s = (void *)(iVar3 + 5);
      *(char *)(iVar3 + 4) = (char)name_length;
      memset(__s,0,0x20);
      memcpy(__s,name_bytes,name_length);
      SharedRegionLockGuard::~SharedRegionLockGuard(aSStack_2c);
      SerializeMultiMapInfo();
      bVar1 = true;
      goto LAB_0000eae0;
    }
    iVar5 = iVar5 + 1;
    iVar4 = iVar4 + 0x24;
  } while (iVar5 != 4);
  SharedRegionLockGuard::~SharedRegionLockGuard(aSStack_2c);
  bVar1 = false;
LAB_0000eae0:
  if (local_24 == *piVar6) {
    return bVar1;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

