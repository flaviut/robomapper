/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0000e534
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Under region8 guard, emits primary bytes from four 0x24-byte entries when nonzero, stores count.
   Caller needs room for four bytes; no capacity argument. */

void GetSharedMultiMapList(uchar *flags_out,uint *count_out)

{
  __pid_t _Var1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  SharedRegionLockGuard aSStack_24 [8];
  int local_1c;
  
  piVar5 = *(int **)(_LAB_0000e5b8 + 0xe53e + _LAB_0000e5bc);
  local_1c = *piVar5;
  SharedRegionLockGuard::SharedRegionLockGuard(aSStack_24,1,8);
  _Var1 = getpid();
  _rrlogm(0x15,6,0xa9,_LAB_0000e5c8 + 0xe56c,_LAB_0000e5c0 + 0xe606,_LAB_0000e5c4 + 0xe56a,_Var1);
  iVar2 = GetSharedRegion(8,0x9c);
  iVar3 = iVar2 + 0x90;
  uVar4 = 0;
  do {
    if (*(uchar *)(iVar2 + 1) != '\0') {
      flags_out[uVar4] = *(uchar *)(iVar2 + 1);
      uVar4 = uVar4 + 1;
    }
    iVar2 = iVar2 + 0x24;
  } while (iVar2 != iVar3);
  *count_out = uVar4;
  SharedRegionLockGuard::~SharedRegionLockGuard(aSStack_24);
  if (local_1c == *piVar5) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

