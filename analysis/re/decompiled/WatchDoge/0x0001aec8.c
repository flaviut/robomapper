/* Decompiled C, NOT recovered source; need not compile.
 * Binary: WatchDoge
 * SHA256: 3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6
 * Function VA: 0x0001aec8
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* If fd!=-1, issues ioctl(fd,0x80045705,1) and increments global feed counter 0x345f0 regardless of
   ioctl result. fd==-1 only logs. Counter is NOT proof of kernel watchdog feed acceptance. Periodic
   thread bytes exist at 0x1af18 but baseline has no function/instructions there; no synthetic
   function created. */

void WdogHwFeedOnce(void)

{
  undefined8 uVar1;
  
  if (DAT_000345e8 == -1) {
    uVar1 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11579\n",(int)uVar1,(int)((ulonglong)uVar1 >> 0x20));
    (*(code *)PTR_fflush_00034214)(stdout);
    return;
  }
  ioctl(DAT_000345e8,0x80045705,1);
  DAT_000345f0 = DAT_000345f0 + 1;
  return;
}

