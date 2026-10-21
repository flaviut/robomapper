/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0000e164
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Initializes catalog before access(path,F_OK). access result -1 (not proven ENOENT specifically)
   takes fallback: only checks user_map0; if accessible sets first primary byte and current_flag to
   2 under region-8 guard, unlocks then PersistSave(1,path). Other access results call
   PersistLoad(1,path) once and ignore result; unloadable existing catalogs do not trigger fallback.
    */

void DeserializeMultiMapInfo(void)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  SharedRegionLockGuard aSStack_11c [8];
  char acStack_114 [128];
  char acStack_94 [127];
  undefined1 local_15;
  int local_14;
  
  piVar3 = *(int **)(_LAB_0000e204 + 0xe174 + _LAB_0000e208);
  local_14 = *piVar3;
  GetMultiMapFilePath(acStack_114);
  InitSharedMultiMapInfo();
  iVar2 = access(acStack_114,0);
  if (iVar2 == -1) {
    GetUserDataPath(acStack_94);
    __strcat_chk(acStack_94,_LAB_0000e20c + 0xe1b4,0x80);
    local_15 = 0;
    iVar2 = access(acStack_94,0);
    bVar1 = false;
    if (iVar2 != -1) {
      SharedRegionLockGuard::SharedRegionLockGuard(aSStack_11c,1,8);
      iVar2 = GetSharedRegion(8,0x9c);
      *(undefined1 *)(iVar2 + 1) = 2;
      *(undefined4 *)(iVar2 + 0x94) = 2;
      SharedRegionLockGuard::~SharedRegionLockGuard(aSStack_11c);
      bVar1 = PersistSave(1,acStack_114);
    }
  }
  else {
    bVar1 = PersistLoad(1,acStack_114);
  }
  if (local_14 == *piVar3) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(bVar1);
}

