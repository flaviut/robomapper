/* Decompiled C, NOT recovered source; need not compile.
 * Binary: WatchDoge
 * SHA256: 3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6
 * Function VA: 0x0001abd8
 */

/* Lane-local bounded recovery. Exact EHABI entry 0x1abd8 at 0x23090; next EHABI start 0x1ac20 is
   only an outer ceiling. Reachable Thumb body ends 0x1ac07: normal return 0x1ac02 or
   __stack_chk_fail PLT call 0x1ac04. Existing launcher at 0x1ac08 is not absorbed. Calls
   sigfillset(&local), then pthread_sigmask(0,&local,NULL); both returns ignored. No direct watchdog
   ioctl, UART call or writer synchronization. Interpretation as blocking mask is ABI inference;
   effective runtime signal state not measured. Preserve recovered ABI/signature. */

void FUN_0001abd8(void)

{
  sigset_t sStack_8c;
  int iStack_c;
  
  iStack_c = __stack_chk_guard;
  sigfillset(&sStack_8c);
  pthread_sigmask(0,&sStack_8c,(__sigset_t *)0x0);
  if (iStack_c == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

