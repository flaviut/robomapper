/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x000179bc
 */

/* Initializes metadata mutex at +0x14 with type=1, pshared=1 and robust=1. Metadata layout
   otherwise remains unmodeled; no original C++ layout asserted. */

void InitPersistInfo(PersistInfo *param_1)

{
  int iVar1;
  int iVar2;
  __pid_t _Var3;
  int *piVar4;
  pthread_mutexattr_t pStack_18;
  int local_14;
  
  piVar4 = *(int **)(DAT_00017a50 + 0x179c4 + DAT_00017a54);
  local_14 = *piVar4;
  if (param_1 == (PersistInfo *)0x0) {
    _rrlogm(0x15,4,0x32,DAT_00017a6c + 0x17a40,DAT_00017a64 + 0x17a82,DAT_00017a68 + 0x17a3c);
  }
  else {
    pthread_mutexattr_init(&pStack_18);
    pthread_mutexattr_settype(&pStack_18,1);
    pthread_mutexattr_setpshared(&pStack_18,1);
    pthread_mutexattr_setrobust(&pStack_18,1);
    iVar1 = DAT_00017a58;
    iVar2 = pthread_mutex_init((pthread_mutex_t *)(param_1 + 0x14),&pStack_18);
    _Var3 = getpid();
    _rrlogm(0x15,6,0x2e,DAT_00017a60 + 0x17a1a,(int)&DAT_00017a58 + DAT_00017a5c,iVar1 + 0x17a00,
            iVar2,_Var3);
  }
  if (local_14 == *piVar4) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

