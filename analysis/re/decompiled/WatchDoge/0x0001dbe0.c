/* Decompiled C, NOT recovered source; need not compile.
 * Binary: WatchDoge
 * SHA256: 3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6
 * Function VA: 0x0001dbe0
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Registers WdogSignalHandler for signals 15,2,3,11,7,10,12,4,5,6,8,1, failing on first signal()
   error. Return 0 on completion or -1 on registration failure. No maintenance/reload-only signal
   contract is inferred. */

int WdogInstallSignals(void)

{
  __sighandler_t p_Var1;
  
  p_Var1 = signal(0xf,(__sighandler_t)0x1d075);
  if (((((p_Var1 != (__sighandler_t)0xffffffff) &&
        (p_Var1 = signal(2,(__sighandler_t)0x1d075), p_Var1 != (__sighandler_t)0xffffffff)) &&
       (p_Var1 = signal(3,(__sighandler_t)0x1d075), p_Var1 != (__sighandler_t)0xffffffff)) &&
      ((((p_Var1 = signal(0xb,(__sighandler_t)0x1d075), p_Var1 != (__sighandler_t)0xffffffff &&
         (p_Var1 = signal(7,(__sighandler_t)0x1d075), p_Var1 != (__sighandler_t)0xffffffff)) &&
        ((p_Var1 = signal(10,(__sighandler_t)0x1d075), p_Var1 != (__sighandler_t)0xffffffff &&
         ((p_Var1 = signal(0xc,(__sighandler_t)0x1d075), p_Var1 != (__sighandler_t)0xffffffff &&
          (p_Var1 = signal(4,(__sighandler_t)0x1d075), p_Var1 != (__sighandler_t)0xffffffff)))))) &&
       (p_Var1 = signal(5,(__sighandler_t)0x1d075), p_Var1 != (__sighandler_t)0xffffffff)))) &&
     (((p_Var1 = signal(6,(__sighandler_t)0x1d075), p_Var1 != (__sighandler_t)0xffffffff &&
       (p_Var1 = signal(8,(__sighandler_t)0x1d075), p_Var1 != (__sighandler_t)0xffffffff)) &&
      (p_Var1 = signal(1,(__sighandler_t)0x1d075), p_Var1 != (__sighandler_t)0xffffffff)))) {
    return 0;
  }
  return -1;
}

