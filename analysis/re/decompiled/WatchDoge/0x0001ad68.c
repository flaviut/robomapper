/* Decompiled C, NOT recovered source; need not compile.
 * Binary: WatchDoge
 * SHA256: 3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6
 * Function VA: 0x0001ad68
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Opens /dev/watchdog with flags 1; failure exits -1. Sets FD flag via fcntl(fd,2,1). Requests
   timeout 16 through ioctl 0xc0045706 (failure exits -1); option from HWDOG_OPTION parsed base 10,
   default 1, via vendor ioctl 0xc004570b; then option 2 via ioctl 0x80045704. Last two ioctl
   results ignored. Kernel/vendor semantics and magic-close acceptance are not established by
   userspace. */

void WdogHwInit(void)

{
  char *pcVar1;
  int iVar2;
  int *piVar3;
  undefined8 uVar4;
  undefined4 uVar5;
  undefined4 local_24;
  long local_20;
  int local_1c;
  
  local_24 = 0x10;
  local_20 = 2;
  local_1c = __stack_chk_guard;
  pcVar1 = getenv("HWDOG_OPTION");
  DAT_000345e8 = open("/dev/watchdog",1);
  if (DAT_000345e8 == -1) {
    uVar4 = get_cur_time_ms();
    piVar3 = __errno_location();
    pcVar1 = strerror(*piVar3);
    __printf_chk(1,"%llu,wdog,#11575`%s\n",(int)uVar4,(int)((ulonglong)uVar4 >> 0x20),pcVar1);
    fflush(stdout);
                    /* WARNING: Subroutine does not return */
    exit(-1);
  }
  fcntl(DAT_000345e8,2,1);
  uVar4 = get_cur_time_ms();
  uVar5 = local_24;
  __printf_chk(1,"%llu,wdog,#11576`%d\n",(int)uVar4,(int)((ulonglong)uVar4 >> 0x20),local_24);
  fflush(stdout);
  iVar2 = ioctl(DAT_000345e8,0xc0045706,&local_24);
  if (iVar2 == 0) {
    if (pcVar1 == (char *)0x0) {
      local_20 = 1;
    }
    else {
      local_20 = strtol(pcVar1,(char **)0x0,10);
    }
    uVar4 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11578`%d\n",(int)uVar4,(int)((ulonglong)uVar4 >> 0x20),local_20);
    fflush(stdout);
    ioctl(DAT_000345e8,0xc004570b,&local_20);
    local_20 = 2;
    ioctl(DAT_000345e8,0x80045704,&local_20);
    if (local_1c == __stack_chk_guard) {
      return;
    }
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  uVar4 = get_cur_time_ms();
  __printf_chk(1,"%llu,wdog,#11577\n",(int)uVar4,(int)((ulonglong)uVar4 >> 0x20),uVar5);
  fflush(stdout);
                    /* WARNING: Subroutine does not return */
  exit(-1);
}

