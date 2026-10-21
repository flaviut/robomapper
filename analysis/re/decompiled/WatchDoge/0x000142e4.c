/* Decompiled C, NOT recovered source; need not compile.
 * Binary: WatchDoge
 * SHA256: 3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6
 * Function VA: 0x000142e4
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Startup/dispatcher boundary. Loads process list at 0x1461e, exclusions at 0x14644, refreshes PIDs
   at 0x1467e, stops prior processes (mode 1) at 0x146a8, then starts enabled records at 0x146d0.
   Event 9 at 0x147fe kills three network clients and calls destructive configuration removal, then
   FALLS THROUGH to event 8. Event 8 reloads exclusions at 0x1483a and attempts zero-payload IPC
   0x03070343 at 0x1484e; this is not proof of delivery, request correlation or writer quiescence.
   Periodic event 2 scans only while supervisor byte +0 is zero. */

int WdogMain(int argc,char **argv)

{
  bool bVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  size_t sVar6;
  char *__s1;
  int extraout_r1;
  undefined8 uVar7;
  allocator aaStack_130 [4];
  int local_12c;
  uint local_128;
  int local_124;
  int local_120;
  string asStack_11c [4];
  string asStack_118 [4];
  int local_114;
  undefined4 local_110;
  undefined4 local_10c;
  stat local_108;
  undefined1 auStack_ac [128];
  int local_2c;
  
  local_2c = __stack_chk_guard;
  memset(auStack_ac,0,0x80);
  FUN_00016d44("iptables -I INPUT -j DROP -p tcp --dport 29");
  FUN_0001df50();
  local_124 = DAT_0001445c;
  local_120 = DAT_0001445c;
  rr_init_locale();
  rr_init_timezone();
  FUN_0001deb8();
  FUN_0001c978(&local_12c);
  uVar7 = get_cur_time_ms();
  __printf_chk(1,"%llu,wdog,#11705`%d\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20),local_12c);
  fflush(stdout);
  uVar7 = get_cur_time_ms();
  uVar2 = FUN_00016cd8(DAT_00034338);
  __printf_chk(1,"%llu,wdog,#11706`%s\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20),uVar2);
  fflush(stdout);
  FUN_0001cec8();
  iVar3 = FUN_0001cb34();
  uVar2 = FUN_0001cbd4();
  DAT_00034c98 = (undefined1)iVar3;
  DAT_00034c99 = (undefined1)uVar2;
  FUN_0001dd5c();
  uVar7 = get_cur_time_ms();
  __printf_chk(1,"%llu,wdog,#11707`%s\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20),"v0.00.39");
  fflush(stdout);
  uVar7 = get_cur_time_ms();
  __printf_chk(1,"%llu,wdog,#11708`%d`%d\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20),iVar3,uVar2);
  fflush(stdout);
  if (9 < iVar3) {
    FUN_0001cc6c(9);
    iVar4 = access("/opt/rockrobo/rrlog/devtest.conf",0);
    if ((iVar4 == 0) || (iVar4 = rrlog_get_model_ver(), iVar4 == 2)) {
      FUN_00016d44("touch /mnt/data/rockrobo/rrlog/core.2817276374.12.recovery");
    }
    else {
      uVar7 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11709\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
      fflush(stdout);
      sleep(100);
    }
  }
  iVar4 = FUN_0001dabc("/dev/shm/watchdoge.pid");
  if (iVar4 != 0) {
    iVar3 = 0;
LAB_0001442a:
    if ((undefined1 *)(local_120 + -0xc) != std::string::_Rep::_S_empty_rep_storage) {
      FUN_0001c9e8((undefined1 *)(local_120 + -0xc),&local_108);
    }
    if ((undefined1 *)(local_124 + -0xc) != std::string::_Rep::_S_empty_rep_storage) {
      FUN_0001c9e8((undefined1 *)(local_124 + -0xc),&local_108);
    }
    if (local_2c == __stack_chk_guard) {
      return iVar3;
    }
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  FUN_0001cac0();
  WdogInstallSignals();
  if (argc == 2) {
    std::string::operator=((string *)&local_124,argv[1]);
  }
  else {
    uVar7 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11710\n`%s\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20),
                 "/opt/rockrobo/watchdog");
    fflush(stdout);
    std::string::operator=((string *)&local_124,"/opt/rockrobo/watchdog");
  }
  WdogHwInit();
  WdogHwFeedOnce();
  WdogHwClose();
  WdogHwStartFeeder();
  std::string::assign((string *)&local_120);
  iVar4 = init_uart();
  if (iVar4 < 0) {
    uVar7 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11711`%d\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20),iVar4);
    fflush(stdout);
    close_uart();
    iVar3 = -1;
    goto LAB_0001442a;
  }
  iVar4 = FUN_0001c688();
  if (iVar4 == 0) {
    iVar4 = FUN_00016b34("/opt/rockrobo/firmware/bin/MCU_FIRMWARE_MATCH");
    uVar7 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11712`%d`%d\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20),iVar4,
                 DAT_00034338);
    fflush(stdout);
    if ((iVar4 == -0x5e) && (DAT_00034338 - 1U < 5)) {
      uVar7 = get_cur_time_ms();
      iVar3 = DAT_00034338;
      __printf_chk(1,"%llu,wdog,#11713`%d`%d\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20),
                   0xffffffa2,DAT_00034338);
      fflush(stdout);
      iVar4 = 0;
      do {
        uVar7 = get_cur_time_ms();
        __printf_chk(1,"%llu,wdog,add crash time %d \n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20),
                     iVar4,iVar3);
        fflush(stdout);
        iVar5 = FUN_0001cb34();
        FUN_0001cc6c(iVar5 + 1);
        iVar4 = iVar4 + 1;
      } while (iVar4 != 10);
      uVar7 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11714\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
      fflush(stdout);
      close_uart();
      uVar7 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11715\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
      fflush(stdout);
      uVar7 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11716\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
      fflush(stdout);
      WdogHwStopFeeder();
      FUN_00016d44(&DAT_00021b1c);
      WdogHwInit();
      uVar7 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11717\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
      fflush(stdout);
      do {
        sleep(0xe10);
      } while( true );
    }
    FUN_00016b28();
  }
  else {
    uVar7 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11720\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
    fflush(stdout);
  }
  FUN_0001e218();
  iVar4 = FUN_000167f4();
  DAT_00034ca0 = iVar4;
  DAT_00034c64 = FUN_0001d4d8();
  if (iVar4 < 0) {
    iVar5 = FUN_0001dd14();
    if (iVar5 == 0) {
      uVar7 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11721\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
      fflush(stdout);
      FUN_0001c584();
      close_uart();
      do {
        sleep(0xe10);
      } while( true );
    }
  }
  else {
    iVar5 = FUN_0001dd14();
    if ((iVar5 == 0) && (iVar5 = FUN_0001dd38(), iVar5 == 0)) {
      uVar7 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11724\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
      fflush(stdout);
    }
  }
  FUN_000158f8();
  if (iVar4 == 9) {
    __s1 = (char *)rr_get_location();
    iVar4 = strcmp(__s1,"prc");
    if (iVar4 == 0) {
      uVar7 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11733`%d\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20),9);
      fflush(stdout);
      DAT_00034ca0 = FUN_00016c18();
      std::string::append((char *)&local_124);
      goto LAB_00014570;
    }
    uVar7 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11732\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
    fflush(stdout);
    std::string::append((char *)&local_124);
    std::string::append((char *)&local_124);
  }
  else {
    if (iVar4 < 10) {
      if (iVar4 == 4) {
        close_uart();
        uVar7 = get_cur_time_ms();
        __printf_chk(1,"%llu,wdog,#11728\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
        fflush(stdout);
        __sprintf_chk(auStack_ac,1,0x80,"uart_test -t AT#AUTO_BIT%% -pa -c &");
        FUN_00016d44(auStack_ac);
        FUN_0001c584();
        uVar7 = get_cur_time_ms();
        __printf_chk(1,"%llu,wdog,#11729\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
        fflush(stdout);
        WdogHwStopFeeder();
        FUN_000167b4();
        uVar7 = get_cur_time_ms();
        __printf_chk(1,"%llu,wdog,#11730\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
        fflush(stdout);
        do {
          sleep(1);
        } while( true );
      }
      if (iVar4 == 5) {
        uVar7 = get_cur_time_ms();
        __printf_chk(1,"%llu,wdog,#11731\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
        fflush(stdout);
        FUN_0001ca7c(DAT_0001503c,"CompassBumper.cfg");
        std::string::append((char *)&local_124);
        std::string::append((char *)&local_124);
        goto LAB_0001457e;
      }
      if (iVar4 == 3) {
        close_uart();
        uVar7 = get_cur_time_ms();
        __printf_chk(1,"%llu,wdog,#11725\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
        fflush(stdout);
        __sprintf_chk(auStack_ac,1,0x80,"uart_test -t AT#BIT%% -pa -c &");
        FUN_00016d44(auStack_ac);
        FUN_0001c584();
        uVar7 = get_cur_time_ms();
        __printf_chk(1,"%llu,wdog,#11726\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
        fflush(stdout);
        WdogHwStopFeeder();
        FUN_000167b4();
        uVar7 = get_cur_time_ms();
        __printf_chk(1,"%llu,wdog,#11727\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
        fflush(stdout);
        do {
          sleep(1);
        } while( true );
      }
    }
    else if ((iVar4 == 0x22) || (iVar4 == 0x42)) {
      uVar7 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11735\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
      fflush(stdout);
      FUN_0001ca7c(DAT_000153e0,"miio/wifi.conf");
      FUN_0001ca7c(DAT_000153e4,"endpoint.bin");
      FUN_0001ca7c(DAT_000153e4,"endpoint.bin.old");
      FUN_0001ca7c(DAT_000153e0,"miio/device.uid");
      FUN_0001ca7c(DAT_000153e0,"miio/device.token");
      FUN_0001ca7c(DAT_000153e0,"miio/device.country");
      FUN_0001ca7c(DAT_000153e0,"miio/config.db");
      FUN_0001ca7c(DAT_000153e0,"rockrobo/VacuumAndBrush.cfg");
      FUN_0001ca7c(DAT_000153e0,"rockrobo/apptimer.cfg");
      FUN_0001ca7c(DAT_000153e0,"rockrobo/rrlog/upload_en");
      FUN_0001ca7c(DAT_000153e0,"rriot/tuya_db/tuya_user.db");
      FUN_0001ca7c(DAT_000153e0,"rriot/tuya_db/tuya_user.db_bak");
      FUN_0001ca7c(DAT_000153e0,"rriot/roborock/iot.json");
      FUN_0001ca7c(DAT_000153e0,"rockrobo/exclude_process.conf");
      rr_set_child_lock_status(0);
      rr_set_carpet_clean_mode(1);
    }
    else if (iVar4 == 10) {
      uVar7 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11734\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
      fflush(stdout);
      std::string::append((char *)&local_124);
      std::string::append((char *)&local_124);
      goto LAB_0001457e;
    }
    uVar7 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11737`%d\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20),iVar4);
    fflush(stdout);
    std::string::append((char *)&local_124);
LAB_00014570:
    std::string::append((char *)&local_124);
  }
LAB_0001457e:
  FUN_00016980();
  FUN_00016864();
  FUN_00016100(&local_120);
  close_uart();
  std::string::string(asStack_11c,"apple",(allocator *)&local_108);
  std::string::string(asStack_118,"apple",(allocator *)&local_108);
  iVar4 = std::string::compare(asStack_11c);
  if (iVar4 == 0) {
    DAT_00034658 = 0xfffffff6;
    DAT_0003465c = 10;
  }
  else {
    DAT_00034658 = 1;
    DAT_0003465c = 0;
  }
  FUN_0001d6ec();
  uVar7 = get_cur_time_ms();
  __printf_chk(1,"%llu,wdog,#11738\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
  fflush(stdout);
  WdogLoadProcessList(&DAT_00034600,&local_124);
  std::string::string((string *)&local_114,"/mnt/data/rockrobo/exclude_process.conf",
                      (allocator *)&local_110);
  WdogReloadExclusions(&DAT_00034600,&local_114);
  if ((undefined1 *)(local_114 + -0xc) != std::string::_Rep::_S_empty_rep_storage) {
    FUN_0001c9e8((undefined1 *)(local_114 + -0xc),&local_108);
  }
  uVar7 = get_cur_time_ms();
  __printf_chk(1,"%llu,wdog,#11739\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
  fflush(stdout);
  WdogRefreshPids(&DAT_00034600);
  uVar7 = get_cur_time_ms();
  __printf_chk(1,"%llu,wdog,#11740\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
  fflush(stdout);
  WdogStopProcesses(&DAT_00034600,WdogStopWaitAll);
  uVar7 = get_cur_time_ms();
  __printf_chk(1,"%llu,wdog,#11741\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
  fflush(stdout);
  WdogStartEnabled(&DAT_00034600);
  sleep(1);
  uVar7 = get_cur_time_ms();
  __printf_chk(1,"%llu,wdog,#11742\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
  fflush(stdout);
  WdogRefreshAndCheckPids(&DAT_00034600);
  uVar7 = get_cur_time_ms();
  __printf_chk(1,"%llu,wdog,#11743\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
  fflush(stdout);
  if (iVar3 < 5) {
    FUN_0001c584();
    FUN_0001c710();
  }
  else {
    uVar7 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11744\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
    fflush(stdout);
  }
  uVar7 = get_cur_time_ms();
  __printf_chk(1,"%llu,wdog,#11745\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
  fflush(stdout);
  FUN_0001eba0();
  FUN_0001dcc4();
  FUN_0001679c();
  if (local_12c - 1U < 3) {
LAB_00014760:
    DAT_00034c68 = 1;
  }
  else {
    if (local_12c == 4) {
      iVar3 = FUN_0001c89c();
      if (iVar3 == 1) {
        uVar7 = get_cur_time_ms();
        __printf_chk(1,"%llu,wdog,#11753\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
        fflush(stdout);
        uVar2 = BlSetUpdateProgressFlag(3);
        uVar7 = get_cur_time_ms();
        __printf_chk(1,"%llu,wdog,#11754`%d\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20),uVar2);
        fflush(stdout);
        DAT_00034338 = 3;
        local_110 = 2;
        local_10c = 1;
        uVar7 = get_cur_time_ms();
        __printf_chk(1,"%llu,wdog,#11755\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
        fflush(stdout);
        WdogSendIpcPacket(0x1070778,&local_110,8);
        goto LAB_00014760;
      }
      uVar7 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11746\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
      fflush(stdout);
      iVar3 = __xstat(3,DAT_000153e8,&local_108);
      if (iVar3 == 0) {
        uVar7 = get_cur_time_ms();
        __printf_chk(1,"%llu,wdog,#11747`%s\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20),
                     DAT_000153e8);
        fflush(stdout);
        unlink(DAT_000153e8);
      }
      else {
        uVar7 = get_cur_time_ms();
        __printf_chk(1,"%llu,wdog,#11748\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
        fflush(stdout);
      }
      uVar2 = BlSetUpdateProgressFlag(0);
      uVar7 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11749`%d\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20),uVar2);
      fflush(stdout);
      uVar7 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11750\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
      fflush(stdout);
      uVar2 = bl_set_quiet_upgrade(0);
      uVar7 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11751`%d\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20),uVar2);
      fflush(stdout);
      DAT_00034338 = 0;
      local_110 = 2;
      local_10c = 2;
      uVar7 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11752\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
    }
    else {
      if (local_12c != 5) goto LAB_00014766;
      uVar7 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11761\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
      fflush(stdout);
      uVar2 = BlSetUpdateProgressFlag(0);
      uVar7 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11762`%d\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20),uVar2);
      fflush(stdout);
      uVar7 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11763\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
      fflush(stdout);
      uVar2 = bl_set_quiet_upgrade(0);
      uVar7 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11764`%d\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20),uVar2);
      fflush(stdout);
      DAT_00034338 = 0;
      local_110 = 3;
      local_10c = 1;
      uVar7 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11765\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
    }
    fflush(stdout);
    WdogSendIpcPacket(0x1070778,&local_110,8);
  }
LAB_00014766:
  rr_overwrite_int(6,3,DAT_00034c99);
  rr_overwrite_int(6,4,DAT_00034c98);
  bVar1 = false;
  do {
    do {
      iVar3 = WdogReadEvent(&local_128,0);
    } while (iVar3 == 0);
    switch(local_128) {
    case 2:
      __aeabi_idivmod(DAT_000345f0,10);
      if (extraout_r1 == 0) {
        if (bVar1) {
          uVar7 = get_cur_time_ms();
          __printf_chk(1,"%llu,wdog,#11766`%d\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20),
                       DAT_000345f0);
          fflush(stdout);
        }
        bVar1 = false;
      }
      else {
        bVar1 = true;
      }
      if (DAT_00034600 == 0) {
        local_108.st_dev._0_4_ = (uint)DAT_00034600;
        iVar3 = WdogScanProcesses(&DAT_00034600);
        if (iVar3 == 2) {
          iVar3 = FUN_0001cbd4();
          if (iVar3 == 4) {
            uVar7 = get_cur_time_ms();
            __printf_chk(1,"%llu,wdog,#11767\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
            fflush(stdout);
            iVar3 = 6;
          }
          else {
            iVar3 = 2;
          }
          iVar4 = FUN_0001cb34();
          FUN_0001cc6c(iVar4 + 1);
          FUN_00016d44(
                      "tail -n 1000 /mnt/data/rockrobo/rrlog/watchdog.log > /mnt/reserve/failure_info.log"
                      );
          FUN_00016d44("ls -al /mnt/data/rockrobo/rrlog/core.* >> /mnt/reserve/failure_info.log");
          iVar4 = FUN_0001cd78();
          iVar4 = iVar4 * 0x3c;
          if (iVar4 < 0) {
            iVar4 = iVar4 + 7;
          }
          if (DAT_000345f0 != iVar4 >> 3) goto LAB_00014856;
        }
        else {
          if (iVar3 == 3) {
            WdogRefreshAndCheckPids(&DAT_00034600);
          }
          iVar3 = FUN_0001cd78();
          iVar3 = iVar3 * 0x3c;
          if (iVar3 < 0) {
            iVar3 = iVar3 + 7;
          }
          if (DAT_000345f0 != iVar3 >> 3) break;
          iVar3 = 0;
        }
        uVar7 = get_cur_time_ms();
        __printf_chk(1,"%llu,wdog,#11768\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
        fflush(stdout);
        FUN_0001ca7c(DAT_0001503c,"failure_count");
        if (iVar3 != 0) goto LAB_00014856;
      }
      break;
    case 3:
      uVar7 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11769\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
      fflush(stdout);
      FUN_00016d44("pidof -x miio_client | xargs kill -9");
      FUN_00016d44("pidof -x rriot_tuya | xargs kill -9");
      FUN_00016d44("pidof -x rriot_rr | xargs kill -9");
      DAT_00034328 = 1;
      WdogSendIpcPacket(0x807032f,(void *)0x0,0);
      break;
    case 5:
      goto switchD_000147ac_caseD_5;
    case 6:
      iVar3 = 5;
      goto LAB_00014856;
    case 7:
      iVar3 = 7;
      goto LAB_00014856;
    case 9:
      FUN_00016d44("pidof -x miio_client | xargs kill -9");
      FUN_00016d44("pidof -x rriot_tuya | xargs kill -9");
      FUN_00016d44("pidof -x rriot_rr | xargs kill -9");
      WdogResetConfigFiles();
    case 8:
      std::string::string((string *)&local_108,"/mnt/data/rockrobo/exclude_process.conf",aaStack_130
                         );
      WdogReloadExclusions(&DAT_00034600,&local_108);
      if ((undefined1 *)((uint)local_108.st_dev - 0xc) != std::string::_Rep::_S_empty_rep_storage) {
        FUN_0001c9e8((undefined1 *)((uint)local_108.st_dev - 0xc),&local_114);
      }
      WdogSendIpcPacket(0x3070343,(void *)0x0,0);
    }
  } while( true );
switchD_000147ac_caseD_5:
  iVar3 = 4;
LAB_00014856:
  uVar7 = get_cur_time_ms();
  __printf_chk(1,"%llu,wdog,#11770\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
  fflush(stdout);
  FUN_00015e68();
  uVar7 = get_cur_time_ms();
  __printf_chk(1,"%llu,wdog,#11771\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
  fflush(stdout);
  WdogHwStopFeeder();
  FUN_000167b4();
  uVar7 = get_cur_time_ms();
  __printf_chk(1,"%llu,wdog,#11772\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
  fflush(stdout);
  FUN_0001ebb8();
  FUN_0001c7f0();
  uVar7 = get_cur_time_ms();
  uVar2 = FUN_0001cb34();
  __printf_chk(1,"%llu,wdog,#11773`%d\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20),uVar2);
  fflush(stdout);
  if ((iVar3 - 4U < 2) || (iVar3 == 7)) {
    FUN_0001ca7c(DAT_0001503c,"failure_count");
    sVar6 = strlen(&DAT_00034ca4);
    if (sVar6 != 0) {
      FUN_0001f068();
    }
    WdogSendIpcPacket(0x1070030,(void *)0x0,0);
    FUN_00016d44("/opt/rockrobo/scripts/cpu.sh performance");
    uVar7 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11774\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
    fflush(stdout);
    WdogStopProcesses(&DAT_00034600,WdogStopWaitRrlogd);
    if (sVar6 != 0) {
      FUN_0001f080();
    }
    if (iVar3 == 4) {
      uVar7 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11775",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
      fflush(stdout);
      FUN_00016d44("poweroff");
      goto LAB_00014e92;
    }
    uVar7 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11776",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
  }
  else {
    if (iVar3 != 6) {
      FUN_0001cf2c(1);
      iVar3 = WdogStopProcesses(&DAT_00034600,WdogStopWaitAll);
      if (iVar3 == 0) {
        uVar7 = get_cur_time_ms();
        __printf_chk(1,"%llu,wdog,#11780\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
        fflush(stdout);
      }
      else {
        uVar7 = get_cur_time_ms();
        __printf_chk(1,"%llu,wdog,#11779\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
        fflush(stdout);
        FUN_00016d44("reboot");
      }
                    /* WARNING: Subroutine does not return */
      exit(1);
    }
    FUN_00016d44("/opt/rockrobo/scripts/cpu.sh performance");
    uVar7 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11777\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20),uVar2);
    fflush(stdout);
    WdogStopProcesses(&DAT_00034600,WdogStopWaitRrlogd);
    uVar7 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11778\n",(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
  }
  fflush(stdout);
  FUN_00016d44("reboot");
LAB_00014e92:
                    /* WARNING: Subroutine does not return */
  exit(0);
}

