/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0000e72c
 */

/* retained_flag=-1 resets all 0x9c bytes then initialized=1,current=-1,use_new_map=0. Otherwise
   clears nonmatching entries primary/backup/name length/32 name bytes, leaving unknown entry+2;
   invalidates current if not retained. Guard released before serialization. Does not delete map
   files. */

void ClearMultiMapExcept(MapPersistFlag retained_flag)

{
  bool bVar1;
  __pid_t _Var2;
  undefined1 *__s;
  undefined *puVar3;
  undefined1 *__s_00;
  int iVar4;
  int *piVar5;
  SharedRegionLockGuard aSStack_34 [8];
  int local_2c;
  
  piVar5 = *(int **)(DAT_0000e820 + 0xe734 + DAT_0000e824);
  local_2c = *piVar5;
  iVar4 = DAT_0000e82c + 0xe748;
  puVar3 = &UNK_0000e81e + DAT_0000e828;
  _Var2 = getpid();
  _rrlogm(0x15,6,0xf5,DAT_0000e830 + 0xe75c,puVar3,iVar4,_Var2);
  __s = (undefined1 *)GetSharedRegion(8,0x9c);
  if (retained_flag == -1) {
    SharedRegionLockGuard::SharedRegionLockGuard(aSStack_34,1,8);
    memset(__s,0,0x9c);
    *__s = 1;
    __s[0x98] = 0;
    *(undefined4 *)(__s + 0x94) = 0xffffffff;
    SharedRegionLockGuard::~SharedRegionLockGuard(aSStack_34);
    SerializeMultiMapInfo();
  }
  else {
    bVar1 = false;
    __s_00 = __s + 5;
    SharedRegionLockGuard::SharedRegionLockGuard(aSStack_34,1,8);
    do {
      if (retained_flag != (uint)(byte)__s_00[-4]) {
        __s_00[-3] = 0;
        __s_00[-4] = 0;
        __s_00[-1] = 0;
        memset(__s_00,0,0x20);
        bVar1 = true;
      }
      __s_00 = __s_00 + 0x24;
    } while (__s + 0x95 != __s_00);
    if (retained_flag == *(int *)(__s + 0x94)) {
      SharedRegionLockGuard::~SharedRegionLockGuard(aSStack_34);
      if (!bVar1) goto LAB_0000e7ce;
    }
    else {
      *(undefined4 *)(__s + 0x94) = 0xffffffff;
      SharedRegionLockGuard::~SharedRegionLockGuard(aSStack_34);
    }
    SerializeMultiMapInfo();
  }
LAB_0000e7ce:
  if (local_2c != *piVar5) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}

