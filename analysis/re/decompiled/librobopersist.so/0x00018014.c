/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x00018014
 */

/* Registers region ID, compress/encrypt flags and callback in persistence metadata, using
   process-shared robust region mutexes. Region definitions/layouts are outside this engine slice.
    */

void SubscribePersistSharedRegion
               (int param_1,int param_2,undefined1 param_3,undefined1 param_4,undefined4 param_5)

{
  int *piVar1;
  void *pvVar2;
  int iVar3;
  __pid_t _Var4;
  int iVar5;
  int *piVar6;
  void *pvVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  pthread_mutexattr_t pStack_30;
  int local_2c;
  
  piVar6 = *(int **)(DAT_000181a0 + 0x18026 + DAT_000181a4);
  iVar10 = DAT_000181ac + 0x18036;
  uVar8 = *(undefined4 *)(DAT_000181a8 + 0x18032);
  local_2c = *piVar6;
  iVar9 = DAT_000181b4 + 0x1811c;
  iVar5 = param_1;
  iVar3 = param_2;
  _rrlogm(0x15,6,0xf5,iVar10,iVar9,DAT_000181b0 + 0x1804a,uVar8,param_1,param_2);
  pvVar2 = LockPersistInfo(param_1);
  if (pvVar2 == (void *)0x0) {
    _rrlogm(0x15,3,0xf9,iVar10,iVar9,DAT_000181e0 + 0x18192,uVar8,iVar5,iVar3);
  }
  else {
    iVar5 = *(int *)((int)pvVar2 + 0x2c);
    if (iVar5 == 0) {
LAB_0001809a:
      iVar10 = iVar5 * 0x24;
      *(int *)((int)pvVar2 + 0x2c) = iVar5 + 1;
      *(int *)((int)pvVar2 + iVar10 + 0x30) = param_2;
      pthread_mutexattr_init(&pStack_30);
      pthread_mutexattr_settype(&pStack_30,1);
      pthread_mutexattr_setpshared(&pStack_30,1);
      pthread_mutexattr_setrobust(&pStack_30,1);
      iVar5 = DAT_000181b8;
      iVar9 = pthread_mutex_init((pthread_mutex_t *)(iVar10 + 0x38 + (int)pvVar2),&pStack_30);
      iVar3 = getpid();
      _rrlogm(0x15,6,0x115,DAT_000181c0 + 0x18100,(int)&DAT_000181c0 + DAT_000181bc,iVar5 + 0x180e2,
              param_2,iVar9,iVar3);
      *(undefined1 *)((int)pvVar2 + iVar10 + 0x34) = param_3;
      *(undefined1 *)((int)pvVar2 + iVar10 + 0x35) = param_4;
      *(undefined4 *)((int)pvVar2 + iVar10 + 0x50) = param_5;
    }
    else {
      if (param_2 == *(int *)((int)pvVar2 + 0x30)) {
        iVar9 = 0;
      }
      else {
        iVar9 = 0;
        pvVar7 = pvVar2;
        do {
          iVar9 = iVar9 + 1;
          if (iVar9 == iVar5) goto LAB_0001809a;
          piVar1 = (int *)((int)pvVar7 + 0x54);
          pvVar7 = (void *)((int)pvVar7 + 0x24);
        } while (param_2 != *piVar1);
      }
      _Var4 = getpid();
      _rrlogm(0x15,6,0x103,DAT_000181dc + 0x18174,DAT_000181d4 + 0x18230,DAT_000181d8 + 0x18168,
              param_2,_Var4,iVar3);
      *(undefined4 *)((int)pvVar2 + iVar9 * 0x24 + 0x50) = param_5;
    }
    iVar5 = DAT_000181c4;
    UnlockPersistInfo(param_1);
    _rrlogm(0x15,7,0x11c,DAT_000181d0 + 0x1813e,DAT_000181cc + 0x181f6,iVar5 + 0x18122,
            *(undefined4 *)(DAT_000181c8 + 0x18124),param_2,iVar3);
  }
  if (local_2c != *piVar6) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}

