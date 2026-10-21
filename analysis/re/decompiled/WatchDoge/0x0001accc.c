/* Decompiled C, NOT recovered source; need not compile.
 * Binary: WatchDoge
 * SHA256: 3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6
 * Function VA: 0x0001accc
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* If running flag 0x345ec !=0, clears it, pthread_cancel(thread), then pthread_join(thread,NULL);
   logs join failure. Calls WdogHwClose afterward. This synchronization is only with the watchdog
   feeder, not map writers. */

void WdogHwStopFeeder(void)

{
  int unaff_r6;
  undefined8 uVar1;
  
  if (DAT_000345ec != 0) {
    DAT_000345ec = 0;
    pthread_cancel(DAT_000345e4);
    uVar1 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11569\n",(int)uVar1,(int)((ulonglong)uVar1 >> 0x20));
    fflush(stdout);
    unaff_r6 = pthread_join(DAT_000345e4,(void **)0x0);
    if (unaff_r6 != 0) {
      uVar1 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11570`%d\n",(int)uVar1,(int)((ulonglong)uVar1 >> 0x20),unaff_r6);
      fflush(stdout);
    }
  }
  WdogHwClose();
  uVar1 = get_cur_time_ms();
  __printf_chk(1,"%llu,wdog,#11571`%d\n",(int)uVar1,(int)((ulonglong)uVar1 >> 0x20),unaff_r6);
  (*(code *)PTR_fflush_00034214)(stdout);
  return;
}

