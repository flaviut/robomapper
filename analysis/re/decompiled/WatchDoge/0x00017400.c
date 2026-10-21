/* Decompiled C, NOT recovered source; need not compile.
 * Binary: WatchDoge
 * SHA256: 3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6
 * Function VA: 0x00017400
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Runs pidof for process_name through popen and parses output. Returns positive parsed PID, -1 on
   failure/no result, -2 when a space indicates multiple PIDs. Does not enumerate/confirm
   descendants or provide a PID identity lifetime guarantee. */

int WdogFindPid(void *supervisor,char *process_name)

{
  FILE *__stream;
  char *pcVar1;
  int iVar2;
  undefined8 uVar3;
  char acStack_614 [512];
  char acStack_414 [1024];
  int local_14;
  
  local_14 = __stack_chk_guard;
  __snprintf_chk(acStack_614,0x200,1,0x200,"pidof %s",process_name);
  __stream = popen(acStack_614,"r");
  if (__stream == (FILE *)0x0) {
    uVar3 = get_cur_time_ms();
    iVar2 = -1;
    __printf_chk(1,"%llu,wdog,#11562\n",(int)uVar3,(int)((ulonglong)uVar3 >> 0x20));
    fflush(stdout);
  }
  else {
    iVar2 = -1;
    while (pcVar1 = fgets(acStack_414,0x400,__stream), pcVar1 != (char *)0x0) {
      pcVar1 = strchr(acStack_414,0x20);
      iVar2 = -2;
      if (pcVar1 == (char *)0x0) {
        iVar2 = strtol(acStack_414,(char **)0x0,10);
      }
    }
    pclose(__stream);
  }
  if (local_14 == __stack_chk_guard) {
    return iVar2;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

