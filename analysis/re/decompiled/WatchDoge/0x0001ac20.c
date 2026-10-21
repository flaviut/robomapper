/* Decompiled C, NOT recovered source; need not compile.
 * Binary: WatchDoge
 * SHA256: 3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6
 * Function VA: 0x0001ac20
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* If fd!=-1, writes one byte 0x56 (V) from 0x2095c, logs write result, closes fd and sets fd=-1.
   Does not stop/join feeder thread. Whether kernel accepts magic close and whether hardware resets
   later remain unresolved. */

void WdogHwClose(void)

{
  ssize_t sVar1;
  int iVar2;
  undefined8 uVar3;
  
  if (DAT_000345e8 != -1) {
    sVar1 = write(DAT_000345e8,&DAT_0002095c,1);
    if (sVar1 == -1) {
      uVar3 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11572`%d\n",(int)uVar3,(int)((ulonglong)uVar3 >> 0x20),0xffffffff);
      fflush(stdout);
    }
    else {
      uVar3 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11573`%d`%d\n",(int)uVar3,(int)((ulonglong)uVar3 >> 0x20),
                   DAT_000345e8,sVar1);
      fflush(stdout);
    }
    iVar2 = close(DAT_000345e8);
    uVar3 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11574`%d`%d\n",(int)uVar3,(int)((ulonglong)uVar3 >> 0x20),
                 DAT_000345e8,iVar2);
    fflush(stdout);
    DAT_000345e8 = -1;
  }
  return;
}

