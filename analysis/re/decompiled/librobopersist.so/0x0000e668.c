/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0000e668
 */

/* First matching primary entry: clears primary, backup, stored name length and 32 name bytes;
   leaves entry+2 unknown byte untouched. Sets current=-1 if clearing current. Unlocks before
   catalog serialization; no match means no save. Does not delete grid/persistence files. */

void ClearMultiMap(MapPersistFlag primary_flag)

{
  __pid_t _Var1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  SharedRegionLockGuard aSStack_24 [8];
  int local_1c;
  
  piVar4 = *(int **)(DAT_0000e718 + 0xe670 + DAT_0000e71c);
  local_1c = *piVar4;
  iVar5 = DAT_0000e720 + 0xe680;
  _Var1 = getpid();
  _rrlogm(0x15,6,0xcd,DAT_0000e728 + 0xe698,DAT_0000e724 + 0xe756,iVar5,_Var1);
  iVar2 = GetSharedRegion(8,0x9c);
  SharedRegionLockGuard::SharedRegionLockGuard(aSStack_24,1,8);
  iVar3 = 0;
  iVar5 = iVar2;
  do {
    if ((uint)*(byte *)(iVar5 + 1) == primary_flag) {
      iVar5 = iVar3 * 0x24 + iVar2;
      *(undefined1 *)(iVar5 + 2) = 0;
      *(undefined1 *)(iVar5 + 1) = 0;
      *(undefined1 *)(iVar5 + 4) = 0;
      memset((void *)(iVar5 + 5),0,0x20);
      if (primary_flag == *(int *)(iVar2 + 0x94)) {
        *(undefined4 *)(iVar2 + 0x94) = 0xffffffff;
      }
      SharedRegionLockGuard::~SharedRegionLockGuard(aSStack_24);
      SerializeMultiMapInfo();
      goto LAB_0000e6ca;
    }
    iVar3 = iVar3 + 1;
    iVar5 = iVar5 + 0x24;
  } while (iVar3 != 4);
  SharedRegionLockGuard::~SharedRegionLockGuard(aSStack_24);
LAB_0000e6ca:
  if (local_1c != *piVar4) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}

