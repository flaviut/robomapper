/* Decompiled C, NOT recovered source; need not compile.
 * Binary: WatchDoge
 * SHA256: 3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6
 * Function VA: 0x0001d074
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* All handled signals first refresh/check PIDs, close watchdog fd, and remove failure_count. Signal
   10 stops in mode 0 and disables MCU heartbeat; signal 12 stops in mode 1 and disables MCU
   heartbeat; both mark supervisor byte +0=1 and return. Other handled signals stop in mode 1 and
   enter teardown/exit (signal 15 also disables MCU heartbeat); signal 11 can early-return when
   recovery flag set, but only AFTER common prelude. SIGHUP is not reload-only. Static control flow
   does not establish kernel/MCU reset safety or async-signal safety. */

void WdogSignalHandler(int signal_number)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  undefined8 uVar4;
  
  uVar4 = get_cur_time_ms();
  iVar1 = signal_number;
  __printf_chk(1,"%llu,wdog,#11673`%d\n",(int)uVar4,(int)((ulonglong)uVar4 >> 0x20),signal_number);
  fflush(stdout);
  WdogRefreshAndCheckPids(&DAT_00034600);
  WdogHwClose();
  FUN_0001ca7c(&DAT_00034660,"failure_count");
  if (signal_number == 0xb) {
    if (DAT_00034760 != 0) {
      return;
    }
    uVar4 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11684\n",(int)uVar4,(int)((ulonglong)uVar4 >> 0x20));
    fflush(stdout);
    WdogStopProcesses(&DAT_00034600,WdogStopWaitAll);
    FUN_0001cf2c(0);
LAB_0001d102:
    uVar4 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11687\n",(int)uVar4,(int)((ulonglong)uVar4 >> 0x20),iVar1);
    fflush(stdout);
    FUN_00015e68();
    uVar4 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11688\n",(int)uVar4,(int)((ulonglong)uVar4 >> 0x20));
    fflush(stdout);
    WdogHwStopFeeder();
    FUN_000167b4();
    uVar4 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11689\n",(int)uVar4,(int)((ulonglong)uVar4 >> 0x20));
    fflush(stdout);
    FUN_0001ebb8();
                    /* WARNING: Subroutine does not return */
    exit(2);
  }
  if (signal_number == 0xc) {
    uVar4 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11679\n",(int)uVar4,(int)((ulonglong)uVar4 >> 0x20));
    fflush(stdout);
    FUN_0001cf2c(0);
    uVar4 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11680\n",(int)uVar4,(int)((ulonglong)uVar4 >> 0x20));
    fflush(stdout);
    FUN_0001c584();
    uVar4 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11681\n",(int)uVar4,(int)((ulonglong)uVar4 >> 0x20));
    fflush(stdout);
    WdogStopProcesses(&DAT_00034600,WdogStopWaitAll);
    DAT_00034600 = 1;
    iVar1 = disable_mcu_heartbeat();
    if (iVar1 < 0) {
      uVar4 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11682`%d\n",(int)uVar4,(int)((ulonglong)uVar4 >> 0x20),iVar1);
      goto LAB_00013bb8;
    }
    uVar4 = get_cur_time_ms();
    pcVar3 = "%llu,wdog,#11683\n";
  }
  else {
    if (signal_number != 10) {
      uVar4 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11684\n",(int)uVar4,(int)((ulonglong)uVar4 >> 0x20));
      fflush(stdout);
      WdogStopProcesses(&DAT_00034600,WdogStopWaitAll);
      FUN_0001cf2c(0);
      if (signal_number == 0xf) {
        iVar2 = disable_mcu_heartbeat();
        if (iVar2 < 0) {
          uVar4 = get_cur_time_ms();
          __printf_chk(1,"%llu,wdog,#11685`%d\n",(int)uVar4,(int)((ulonglong)uVar4 >> 0x20),iVar2);
          fflush(stdout);
          iVar1 = iVar2;
        }
        else {
          uVar4 = get_cur_time_ms();
          __printf_chk(1,"%llu,wdog,#11686\n",(int)uVar4,(int)((ulonglong)uVar4 >> 0x20));
          fflush(stdout);
        }
      }
      goto LAB_0001d102;
    }
    DAT_00034760 = 1;
    uVar4 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11674\n",(int)uVar4,(int)((ulonglong)uVar4 >> 0x20));
    fflush(stdout);
    FUN_0001cf2c(0);
    uVar4 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11675\n",(int)uVar4,(int)((ulonglong)uVar4 >> 0x20));
    fflush(stdout);
    FUN_0001c584();
    uVar4 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11676\n",(int)uVar4,(int)((ulonglong)uVar4 >> 0x20));
    fflush(stdout);
    WdogStopProcesses(&DAT_00034600,WdogStopNoWait);
    DAT_00034600 = 1;
    iVar1 = disable_mcu_heartbeat();
    if (iVar1 < 0) {
      uVar4 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11677`%d\n",(int)uVar4,(int)((ulonglong)uVar4 >> 0x20),iVar1);
      goto LAB_00013bb8;
    }
    uVar4 = get_cur_time_ms();
    pcVar3 = "%llu,wdog,#11678\n";
  }
  __printf_chk(1,pcVar3,(int)uVar4,(int)((ulonglong)uVar4 >> 0x20));
LAB_00013bb8:
  (*(code *)PTR_fflush_00034214)(stdout);
  return;
}

