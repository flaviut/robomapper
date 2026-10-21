/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0001a410
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Robust mutex helper: signed timeout_ms<0 uses pthread_mutex_lock; otherwise CLOCK_REALTIME
   timedlock. EOWNERDEAD (0x82) invokes pthread_mutex_consistent. Returns pthread status, 0 on
   success. Other errors log and only model-version 2 aborts: callers can continue after nonzero
   status, so intended locking is conditional on successful acquisition. */

int PersistLockRobust(void *mutex_storage,int timeout_ms)

{
  int __errnum;
  char *pcVar1;
  int iVar2;
  int *piVar3;
  timespec local_2c;
  int local_24;
  
  piVar3 = *(int **)(DAT_0001a510 + 0x1a418 + DAT_0001a514);
  local_24 = *piVar3;
  if (timeout_ms < 0) {
    __errnum = pthread_mutex_lock(mutex_storage);
  }
  else {
    local_2c.tv_nsec = 0;
    local_2c.tv_sec = 0;
    clock_gettime(0,&local_2c);
    local_2c.tv_sec = local_2c.tv_sec + timeout_ms / 1000;
    local_2c.tv_nsec = (timeout_ms % 1000) * 1000000 + local_2c.tv_nsec;
    if (999999999 < local_2c.tv_nsec) {
      local_2c.tv_sec = local_2c.tv_sec + 1;
      local_2c.tv_nsec = local_2c.tv_nsec + -1000000000;
    }
    __errnum = pthread_mutex_timedlock(mutex_storage,&local_2c);
  }
  if (__errnum == 0x82) {
    _rrlogm(0x15,3,0xb1,DAT_0001a52c + 0x1a4fe,DAT_0001a528 + 0x1a4f4,DAT_0001a524 + 0x1a4f0,
            mutex_storage);
    __errnum = pthread_mutex_consistent(mutex_storage);
  }
  iVar2 = DAT_0001a518;
  if (__errnum != 0) {
    pcVar1 = strerror(__errnum);
    _rrlogm(0x15,3,0xb6,DAT_0001a520 + 0x1a4c8,DAT_0001a51c + 0x1a4ba,iVar2 + 0x1a4b6,mutex_storage,
            pcVar1);
    iVar2 = rrlog_get_model_ver();
    if (iVar2 == 2) {
                    /* WARNING: Subroutine does not return */
      abort();
    }
  }
  if (local_24 != *piVar3) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return __errnum;
}

