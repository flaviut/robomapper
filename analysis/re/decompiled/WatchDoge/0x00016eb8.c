/* Decompiled C, NOT recovered source; need not compile.
 * Binary: WatchDoge
 * SHA256: 3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6
 * Function VA: 0x00016eb8
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Starts configured command at record +8 via command helper, with process-name/update-mode special
   cases. Nonzero return indicates command path attempted, not verified PID/execution or completed
   map loading. Called by enabled startup walk and non-key missing-process scan. Original object
   layouts remain unknown. */

int WdogStartRecord(void *supervisor,void *record)

{
  int iVar1;
  undefined4 uVar2;
  char *pcVar3;
  undefined8 uVar4;
  undefined4 uVar5;
  
  pcVar3 = (char *)((int)record + 4);
  iVar1 = std::string::find(pcVar3,0x20498,0);
  if (iVar1 == -1) {
    iVar1 = std::string::find(pcVar3,0x20554,0);
    if (iVar1 == -1) {
      iVar1 = std::string::find(pcVar3,0x2059c,0);
      if (iVar1 == -1) {
        iVar1 = std::string::find(pcVar3,0x205bc,0);
        if (iVar1 == -1) {
          iVar1 = std::string::find(pcVar3,0x205f0,0);
          if (iVar1 == -1) {
            iVar1 = std::string::find(pcVar3,0x20610,0);
            if ((iVar1 != -1) && (DAT_00034338 - 3U < 2)) {
              uVar4 = get_cur_time_ms();
              pcVar3 = "%llu,wdog,#11559\n";
              goto LAB_00017062;
            }
          }
          else if (DAT_00034338 - 3U < 2) {
            uVar4 = get_cur_time_ms();
            pcVar3 = "%llu,wdog,#11558\n";
LAB_00017062:
            __printf_chk(1,pcVar3,(int)uVar4,(int)((ulonglong)uVar4 >> 0x20));
            fflush(stdout);
            return 0;
          }
        }
        else if (DAT_00034338 - 3U < 2) {
          uVar4 = get_cur_time_ms();
          pcVar3 = "%llu,wdog,#11557\n";
          goto LAB_00017062;
        }
      }
      else if (DAT_00034338 - 3U < 2) {
        uVar4 = get_cur_time_ms();
        pcVar3 = "%llu,wdog,#11556\n";
        goto LAB_00017062;
      }
    }
    else {
      if (DAT_00034338 == 2) {
        FUN_00016d44("RoboController Updating 1&");
        return 1;
      }
      if (DAT_00034338 == 3) {
        FUN_00016d44("RoboController Updating 2&");
        return 1;
      }
    }
    FUN_00016d44(*(undefined4 *)((int)record + 8));
    return 1;
  }
  if (DAT_00034c68 != 1) {
    return 0;
  }
  iVar1 = FUN_00016c9c();
  uVar2 = get_cur_time_ms();
  uVar4 = FUN_00016cd8(DAT_00034338);
  uVar5 = (undefined4)uVar4;
  __printf_chk(1,"%llu,wdog,#11550`%s\n",uVar2,(int)((ulonglong)uVar4 >> 0x20),uVar5);
  fflush(stdout);
  if (DAT_000345d8 < 2) {
    if (DAT_000345d8 == 0) goto LAB_00016f62;
  }
  else if (DAT_000345dc != 0 && iVar1 - DAT_000345dc < 5) {
    DAT_000345d8 = 0;
    DAT_00034c68 = 0;
    DAT_000345dc = 0;
    BlSetUpdateProgressFlag(0);
    uVar4 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11551\n",(int)uVar4,(int)((ulonglong)uVar4 >> 0x20),uVar5);
    fflush(stdout);
    WdogSendIpcPacket(0x107077b,(void *)0x0,0);
    return 0;
  }
  FUN_0001ecf4(pcVar3);
LAB_00016f62:
  DAT_000345dc = FUN_00016c9c();
  DAT_000345d8 = DAT_000345d8 + 1;
  if (DAT_00034338 == 1) {
    FUN_00016d44("SysUpdate -p 0&");
    uVar4 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11552\n",(int)uVar4,(int)((ulonglong)uVar4 >> 0x20));
    fflush(stdout);
    iVar1 = 1;
  }
  else if (DAT_00034338 == 2) {
    FUN_00016d44("SysUpdate -p 1&");
    uVar4 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11553\n",(int)uVar4,(int)((ulonglong)uVar4 >> 0x20));
    fflush(stdout);
    iVar1 = 1;
  }
  else if (DAT_00034338 == 3) {
    FUN_00016d44("SysUpdate -p 2&");
    uVar4 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11554\n",(int)uVar4,(int)((ulonglong)uVar4 >> 0x20));
    fflush(stdout);
    iVar1 = 1;
  }
  else {
    uVar2 = get_cur_time_ms();
    uVar4 = FUN_00016cd8(DAT_00034338);
    __printf_chk(1,"%llu,wdog,#11555`%s\n",uVar2,(int)((ulonglong)uVar4 >> 0x20),(int)uVar4);
    fflush(stdout);
    iVar1 = 0;
  }
  return iVar1;
}

