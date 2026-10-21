/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x00017ee4
 */

/* Finds subscribed region by ID and unlocks that region mutex. The map snapshot caller releases one
   region before acquiring the next. */

void UnlockSharedRegion(undefined4 param_1,int param_2)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  code *pcVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  
  uVar2 = *(undefined4 *)(DAT_00017f94 + 0x17ef0);
  iVar6 = DAT_00017f98 + 0x17efc;
  pcVar5 = PersistInfoLockGuard::PersistInfoLockGuard + DAT_00017f9c;
  uVar7 = param_1;
  iVar8 = param_2;
  _rrlogm(0x15,6,0xc3,iVar6,pcVar5,DAT_00017fa0 + 0x17f08,uVar2,param_1,param_2);
  iVar3 = GetPersistInfo(param_1);
  if (iVar3 == 0) {
    _rrlogm(0x15,3,199,iVar6,pcVar5,DAT_00017fb4 + 0x17f8a,uVar2,uVar7,iVar8);
  }
  else {
    if (*(int *)(iVar3 + 0x2c) != 0) {
      if (param_2 == *(int *)(iVar3 + 0x30)) {
        iVar4 = 0;
      }
      else {
        iVar4 = 0;
        iVar6 = iVar3;
        do {
          iVar4 = iVar4 + 1;
          if (iVar4 == *(int *)(iVar3 + 0x2c)) goto LAB_00017f42;
          piVar1 = (int *)(iVar6 + 0x54);
          iVar6 = iVar6 + 0x24;
        } while (param_2 != *piVar1);
      }
      pthread_mutex_unlock((pthread_mutex_t *)(iVar4 * 0x24 + iVar3 + 0x38));
    }
LAB_00017f42:
    _rrlogm(0x15,7,0xd7,DAT_00017fb0 + 0x17f66,DAT_00017fac + 0x18010,DAT_00017fa8 + 0x17f52,
            *(undefined4 *)(DAT_00017fa4 + 0x17f4e),param_2,iVar8);
  }
  return;
}

