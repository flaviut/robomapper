/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0000e9a8
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Matches primary byte, compares existing backup byte to full integer input. If changed, uses index
   0 or GetOldestMapFlagIndex (always 0 in this build), stores low input byte to backup location,
   unlocks then serializes. No flag range validation; no match/unchanged means no save. */

void UpdateBakMapForMultiMap(MapPersistFlag primary_flag,MapPersistFlag backup_flag)

{
  __pid_t _Var1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int *piVar7;
  SharedRegionLockGuard aSStack_2c [8];
  int local_24;
  
  piVar7 = *(int **)(_LAB_0000ea5c + 0xe9b0 + _LAB_0000ea60);
  iVar6 = 0;
  local_24 = *piVar7;
  _Var1 = getpid();
  _rrlogm(0x15,6,0x17c,_LAB_0000ea6c + 0xe9e2,_LAB_0000ea64 + 0xeace,_LAB_0000ea68 + 0xe9d8,_Var1);
  iVar2 = GetSharedRegion(8,0x9c);
  SharedRegionLockGuard::SharedRegionLockGuard(aSStack_2c,1,8);
  iVar4 = iVar2;
  do {
    if ((uint)*(byte *)(iVar4 + 1) == primary_flag) {
      iVar4 = iVar6 * 0x24 + iVar2;
      uVar5 = (uint)*(byte *)(iVar4 + 2);
      if (backup_flag != uVar5) {
        iVar3 = 0;
        if (uVar5 != 0) {
          iVar3 = GetOldestMapFlagIndex((MapCatalogEntry *)(iVar4 + 1));
        }
        *(char *)(iVar6 * 0x24 + iVar2 + iVar3 + 2) = (char)backup_flag;
        SharedRegionLockGuard::~SharedRegionLockGuard(aSStack_2c);
        SerializeMultiMapInfo();
        goto LAB_0000ea12;
      }
      break;
    }
    iVar6 = iVar6 + 1;
    iVar4 = iVar4 + 0x24;
  } while (iVar6 != 4);
  SharedRegionLockGuard::~SharedRegionLockGuard(aSStack_2c);
LAB_0000ea12:
  if (local_24 == *piVar7) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

