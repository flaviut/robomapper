/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0000e5cc
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Scans four primary bytes for exact integer equality and returns pointer to matching backup byte
   at region8+2+i*0x24, or NULL. Guard released before returning pointer; byte 0 means no backup in
   mutation/allocation paths. No rejection of primary_flag=0 here. */

uchar * GetBakMapList(MapPersistFlag primary_flag)

{
  __pid_t _Var1;
  int iVar2;
  int iVar3;
  int iVar4;
  uchar *puVar5;
  int *piVar6;
  SharedRegionLockGuard aSStack_24 [8];
  int local_1c;
  
  piVar6 = *(int **)(_LAB_0000e654 + 0xe5d6 + _LAB_0000e658);
  local_1c = *piVar6;
  iVar4 = _LAB_0000e65c + 0xe5ea;
  SharedRegionLockGuard::SharedRegionLockGuard(aSStack_24,1,8);
  _Var1 = getpid();
  _rrlogm(0x15,6,0xbc,_LAB_0000e664 + 0xe600,_LAB_0000e660 + 0xe6b4,iVar4,_Var1);
  iVar2 = GetSharedRegion(8,0x9c);
  iVar3 = 0;
  iVar4 = iVar2;
  do {
    if ((uint)*(byte *)(iVar4 + 1) == primary_flag) {
      puVar5 = (uchar *)(iVar3 * 0x24 + iVar2 + 2);
      goto LAB_0000e628;
    }
    iVar3 = iVar3 + 1;
    iVar4 = iVar4 + 0x24;
  } while (iVar3 != 4);
  puVar5 = (uchar *)0x0;
LAB_0000e628:
  SharedRegionLockGuard::~SharedRegionLockGuard(aSStack_24);
  if (local_1c == *piVar6) {
    return puVar5;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

