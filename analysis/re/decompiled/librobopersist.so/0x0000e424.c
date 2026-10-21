/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0000e424
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Returns region8+1, start of four 0x24-byte catalog entries. Region guard has already been
   released before return: this is a live shared pointer, not a locked snapshot. MapCatalogEntry
   leaves entry+2 unknown; +3 is stored name length and +4 has 32 name bytes. */

MapCatalogEntry * GetSharedUserMapInfo(void)

{
  __pid_t _Var1;
  int iVar2;
  int iVar3;
  int *piVar4;
  SharedRegionLockGuard aSStack_24 [8];
  int local_1c;
  
  piVar4 = *(int **)(_LAB_0000e490 + 0xe42e + _LAB_0000e494);
  iVar3 = _LAB_0000e498 + 0xe440;
  local_1c = *piVar4;
  iVar2 = _LAB_0000e49c + 0xe4b4;
  SharedRegionLockGuard::SharedRegionLockGuard(aSStack_24,1,8);
  _Var1 = getpid();
  _rrlogm(0x15,6,0x8c,_LAB_0000e4a0 + 0xe458,iVar2,iVar3,_Var1);
  iVar2 = GetSharedRegion(8,0x9c);
  SharedRegionLockGuard::~SharedRegionLockGuard(aSStack_24);
  if (local_1c == *piVar4) {
    return (MapCatalogEntry *)(iVar2 + 1);
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

