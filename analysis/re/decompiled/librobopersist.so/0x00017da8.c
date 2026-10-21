/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x00017da8
 */

/* Finds subscribed region by ID and locks mutex at metadata+0x38+0x24*index. EOWNERDEAD invokes
   pthread_mutex_consistent. Missing subscription does not lock a region. */

void LockSharedRegion(undefined4 param_1,int param_2)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  __pid_t _Var5;
  pthread_mutex_t *__mutex;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  
  uVar2 = *(undefined4 *)(DAT_00017eb4 + 0x17db4);
  iVar7 = DAT_00017eb8 + 0x17dc2;
  iVar6 = DAT_00017ebc + 0x17e6a;
  uVar8 = param_1;
  iVar4 = param_2;
  _rrlogm(0x15,6,0x9e,iVar7,iVar6,DAT_00017ec0 + 0x17dce,uVar2,param_1,param_2);
  iVar3 = GetPersistInfo(param_1);
  if (iVar3 == 0) {
    _rrlogm(0x15,3,0xa3,iVar7,iVar6,DAT_00017ee0 + 0x17eaa,uVar2,uVar8,iVar4);
  }
  else {
    if (*(int *)(iVar3 + 0x2c) != 0) {
      if (param_2 == *(int *)(iVar3 + 0x30)) {
        iVar6 = 0;
      }
      else {
        iVar6 = 0;
        iVar4 = iVar3;
        do {
          iVar6 = iVar6 + 1;
          if (iVar6 == *(int *)(iVar3 + 0x2c)) goto LAB_00017e08;
          piVar1 = (int *)(iVar4 + 0x54);
          iVar4 = iVar4 + 0x24;
        } while (param_2 != *piVar1);
      }
      __mutex = (pthread_mutex_t *)(iVar6 * 0x24 + iVar3 + 0x38);
      iVar4 = pthread_mutex_lock(__mutex);
      if ((iVar4 != 0) && (rr_event_int(1,3,iVar4), iVar3 = DAT_00017ed4, iVar4 == 0x82)) {
        iVar4 = pthread_mutex_consistent(__mutex);
        _Var5 = getpid();
        _rrlogm(0x15,6,0xb3,DAT_00017edc + 0x17e86,DAT_00017ed8 + 0x17f1e,iVar3 + 0x17e6a,param_2,
                _Var5,iVar4);
        if (iVar4 != 0) {
          rr_event_int(1,4,iVar4);
        }
      }
    }
LAB_00017e08:
    _rrlogm(0x15,7,0xbf,DAT_00017ed0 + 0x17e2a,(int)&DAT_00017ebc + DAT_00017ec8,
            DAT_00017ecc + 0x17e22,*(undefined4 *)(DAT_00017ec4 + 0x17e14),param_1,param_2);
  }
  return;
}

