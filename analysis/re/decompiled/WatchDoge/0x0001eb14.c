/* Decompiled C, NOT recovered source; need not compile.
 * Binary: WatchDoge
 * SHA256: 3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6
 * Function VA: 0x0001eb14
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Internal SysV event receive: retries msgrcv on errno 4, copies four-byte event and returns 1 on
   success. On failure with flags 0x800 also returns 1 without updating output; blocking failure
   logs and returns 0. Main uses flags 0. No direct map-writer synchronization. */

int WdogReadEvent(uint *event_code,int flags)

{
  int iVar1;
  int *piVar2;
  ssize_t sVar3;
  undefined8 uVar4;
  undefined1 auStack_24 [4];
  uint local_20;
  int local_1c;
  
  local_1c = __stack_chk_guard;
  iVar1 = msgget(-0x7ffff000,0x3b6);
  do {
    sVar3 = msgrcv(iVar1,auStack_24,4,0,flags);
    if (sVar3 != -1) {
      iVar1 = 1;
      *event_code = local_20;
      goto LAB_0001eb5e;
    }
    piVar2 = __errno_location();
  } while (*piVar2 == 4);
  if (flags == 0x800) {
    iVar1 = 1;
  }
  else {
    uVar4 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11781\n",(int)uVar4,(int)((ulonglong)uVar4 >> 0x20));
    fflush(stdout);
    iVar1 = 0;
  }
LAB_0001eb5e:
  if (local_1c != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return iVar1;
}

