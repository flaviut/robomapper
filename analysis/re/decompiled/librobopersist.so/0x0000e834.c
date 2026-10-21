/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0000e834
 */

/* First matching backup byte is cleared under region8 guard, then guard released and catalog
   serialized. No match means no save. Does not unlink map files. */

void ClearBakMap(MapPersistFlag backup_flag)

{
  __pid_t _Var1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  SharedRegionLockGuard aSStack_24 [8];
  int local_1c;
  
  piVar4 = *(int **)(DAT_0000e8c0 + 0xe83c + DAT_0000e8c4);
  local_1c = *piVar4;
  iVar5 = DAT_0000e8c8 + 0xe84c;
  _Var1 = getpid();
  _rrlogm(0x15,6,0x125,DAT_0000e8d0 + 0xe866,DAT_0000e8cc + 0xe948,iVar5,_Var1);
  iVar2 = GetSharedRegion(8,0x9c);
  SharedRegionLockGuard::SharedRegionLockGuard(aSStack_24,1,8);
  iVar3 = 0;
  iVar5 = iVar2;
  do {
    if (backup_flag == (uint)*(byte *)(iVar5 + 2)) {
      *(undefined1 *)(iVar3 * 0x24 + iVar2 + 2) = 0;
      SharedRegionLockGuard::~SharedRegionLockGuard(aSStack_24);
      SerializeMultiMapInfo();
      goto LAB_0000e898;
    }
    iVar3 = iVar3 + 1;
    iVar5 = iVar5 + 0x24;
  } while (iVar3 != 4);
  SharedRegionLockGuard::~SharedRegionLockGuard(aSStack_24);
LAB_0000e898:
  if (local_1c == *piVar4) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

