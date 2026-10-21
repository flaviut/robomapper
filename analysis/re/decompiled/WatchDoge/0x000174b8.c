/* Decompiled C, NOT recovered source; need not compile.
 * Binary: WatchDoge
 * SHA256: 3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6
 * Function VA: 0x000174b8
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Attempts PID discovery/adoption for record name +4; positive PID is stored at +0 and returns
   true. Multiple-PID result -2 invokes killall -9 for that name and returns false. No per-writer
   drain/flush protocol. */

int WdogAdoptPid(void *supervisor,void *record)

{
  bool bVar1;
  undefined8 uVar2;
  undefined1 auStack_214 [508];
  undefined4 local_18;
  int local_14;
  
  local_14 = WdogFindPid(supervisor,*(char **)((int)record + 4));
  if (local_14 != -2) {
    bVar1 = 0 < local_14;
    if (bVar1) {
      *(int *)record = local_14;
      uVar2 = get_cur_time_ms();
      local_18 = *(undefined4 *)((int)record + 4);
      __printf_chk(1,"%llu,wdog,#11564`%s`%d\n",(int)uVar2,(int)((ulonglong)uVar2 >> 0x20));
      fflush(stdout);
    }
    return (uint)bVar1;
  }
  local_14 = __stack_chk_guard;
  uVar2 = get_cur_time_ms();
  __printf_chk(1,"%llu,wdog,#11563\n",(int)uVar2,(int)((ulonglong)uVar2 >> 0x20));
  fflush(stdout);
  __snprintf_chk(auStack_214,0x200,1,0x200,"killall -9 %s",*(undefined4 *)((int)record + 4));
  FUN_00016d44(auStack_214);
  if (local_14 == __stack_chk_guard) {
    return 0;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

