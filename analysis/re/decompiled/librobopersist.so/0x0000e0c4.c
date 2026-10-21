/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0000e0c4
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Region 8 catalog initialization: subscribes persistence type 1 to region 8, acquires
   SharedRegionLockGuard(1,8), obtains 0x9c bytes, clears all bytes, sets initialized=1, signed
   current_flag at +0x94=-1 and use_new_map at +0x98=0. MapCatalogPayload is a byte-layout proposal,
   not an original C++ class. */

void InitSharedMultiMapInfo(void)

{
  __pid_t _Var1;
  undefined1 *__s;
  int iVar2;
  int iVar3;
  int *piVar4;
  SharedRegionLockGuard aSStack_24 [8];
  int local_1c;
  
  piVar4 = *(int **)(_LAB_0000e150 + 0xe0cc + _LAB_0000e154);
  local_1c = *piVar4;
  iVar3 = _LAB_0000e158 + 0xe0dc;
  iVar2 = _LAB_0000e15c + 0xe0de;
  _Var1 = getpid();
  _rrlogm(0x15,6,0x4c,_LAB_0000e160 + 0xe0f0,iVar2,iVar3,_Var1);
  SubscribePersistSharedRegion(1,8,1);
  SharedRegionLockGuard::SharedRegionLockGuard(aSStack_24,1,8);
  __s = (undefined1 *)GetSharedRegion(8,0x9c);
  memset(__s,0,0x9c);
  *(undefined4 *)(__s + 0x94) = 0xffffffff;
  *__s = 1;
  __s[0x98] = 0;
  SharedRegionLockGuard::~SharedRegionLockGuard(aSStack_24);
  if (local_1c == *piVar4) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

