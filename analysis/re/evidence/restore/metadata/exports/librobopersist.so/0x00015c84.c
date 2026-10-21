/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x00015c84
 */

/* SetRoomIdMapping(IotTypeEnum, RoomIdMapping const*, unsigned int) */

void SetRoomIdMapping(int param_1,void *param_2,uint param_3)

{
  __pid_t _Var1;
  size_t __n;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  SharedRegionLockGuard aSStack_34 [8];
  int local_2c;
  
  piVar6 = *(int **)(DAT_00015dc0 + 0x15c8e + DAT_00015dc4);
  local_2c = *piVar6;
  iVar3 = DAT_00015dc8 + 0x15cac;
  SharedRegionLockGuard::SharedRegionLockGuard(aSStack_34,5);
  _Var1 = getpid();
  iVar4 = param_1;
  _rrlogm(0x15,6,0x18c,DAT_00015dd0 + 0x15cce,DAT_00015dcc + 0x15f34,iVar3,_Var1,param_1);
  iVar3 = GetSharedRegion(5,0x13f120);
  if (param_3 < 0x21) {
    __n = param_3 * 0x1c;
  }
  else {
    _Var1 = getpid();
    _rrlogm(0x15,6,0x191,DAT_00015de8 + 0x15d78,DAT_00015de0 + 0x15fe4,DAT_00015de4 + 0x15d76,_Var1,
            iVar4);
    rr_event_int(1,9,6);
    __n = 0x380;
    param_3 = 0x20;
  }
  if (param_1 == 1) {
    memcpy((void *)(iVar3 + 0x13e9f4),param_2,__n);
    *(uint *)(iVar3 + 0x13e9f0) = param_3;
  }
  else {
    memcpy((void *)(iVar3 + 0x131fb0),param_2,__n);
    *(uint *)(iVar3 + 0x131fac) = param_3;
  }
  if (param_3 != 0) {
    uVar2 = 0;
    iVar3 = DAT_00015dd8 + 0x15d22;
    iVar4 = DAT_00015dd4 + 0x15f94;
    iVar5 = DAT_00015ddc + 0x15d28;
    do {
      _rrlogm(0x15,6,0x19f,iVar3,iVar4,iVar5,uVar2,param_2,*(undefined4 *)((int)param_2 + 0x18));
      uVar2 = uVar2 + 1;
      param_2 = (void *)((int)param_2 + 0x1c);
    } while (param_3 != uVar2);
  }
  SharedRegionLockGuard::~SharedRegionLockGuard(aSStack_34);
  if (local_2c != *piVar6) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}

