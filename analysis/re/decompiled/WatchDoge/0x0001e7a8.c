/* Decompiled C, NOT recovered source; need not compile.
 * Binary: WatchDoge
 * SHA256: 3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6
 * Function VA: 0x0001e7a8
 */

/* WARNING: Restarted to delay deadcode elimination for space: ram */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* For IPC ID 0x07030342: writes payload as C string to exclusions file, then strlen(payload)
   unsigned <=2 queues event 9 (destructive reset), >2 queues event 8 (reload). This is C-string
   length, NOT packet length; embedded NUL truncates interpretation. File-write failure is not
   propagated, so event still queued. Internal event sender is nonblocking and may fail; no
   bounds/terminator guarantee from RecvPacket established here. */

void WdogIpcReceiveLoop(void)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  size_t sVar4;
  undefined8 uVar5;
  uint uVar6;
  undefined4 local_ac;
  int local_a8;
  undefined1 auStack_a4 [8];
  undefined4 local_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 local_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined1 local_7c;
  uint local_78 [2];
  undefined4 local_70;
  uint local_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 local_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 local_4c;
  int local_2c;
  
  local_2c = __stack_chk_guard;
  memset(local_78,0,0x4c);
  uVar5 = get_cur_time_ms();
  __printf_chk(1,"%llu,wdog,#11782\n",(int)uVar5,(int)((ulonglong)uVar5 >> 0x20));
  fflush(stdout);
  DAT_00034c80 = 1;
  do {
    while (iVar2 = RecvPacket(local_78), iVar2 < 1) {
      uVar5 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11794`%d\n",(int)uVar5,(int)((ulonglong)uVar5 >> 0x20),iVar2);
      fflush(stdout);
LAB_0001e83e:
      if (DAT_00034c80 == 0) goto LAB_0001e898;
    }
    uVar5 = get_cur_time_ms();
    uVar6 = local_78[0];
    __printf_chk(1,"%llu,wdog,#11783`%d`%d\n",(int)uVar5,(int)((ulonglong)uVar5 >> 0x20),local_78[0]
                 ,iVar2);
    fflush(stdout);
    uVar3 = local_6c;
    if (local_78[0] == 0x7030342) {
      uVar5 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11793\n",(int)uVar5,(int)((ulonglong)uVar5 >> 0x20),uVar6,iVar2);
      fflush(stdout);
      WdogWriteExclusions((char *)&local_6c);
      sVar4 = strlen((char *)&local_6c);
      if (sVar4 < 3) {
        uVar3 = 9;
      }
      else {
        uVar3 = 8;
      }
      WdogQueueEvent(uVar3);
      goto LAB_0001e83e;
    }
    if (local_78[0] < 0x7030343) {
      if (local_78[0] == 0x701076d) {
        local_ac = 0;
        uVar5 = get_cur_time_ms();
        __printf_chk(1,"%llu,wdog,#11790\n",(int)uVar5,(int)((ulonglong)uVar5 >> 0x20),uVar6,iVar2);
        fflush(stdout);
        __memcpy_chk(&local_ac,&local_6c,local_70,4);
        FUN_0001bf8c(local_ac);
      }
      else if (local_78[0] == 0x703008e) {
        time(&local_a8);
        DAT_00034c88 = 1;
        DAT_00034c84 = uVar3 - local_a8;
        uVar5 = get_cur_time_ms();
        __printf_chk(1,"%llu,wdog,#11792`%d`%d`%d\n",(int)uVar5,(int)((ulonglong)uVar5 >> 0x20),
                     uVar3,local_a8,DAT_00034c84);
        fflush(stdout);
      }
      else if (local_78[0] == 0x701002f) {
        uVar5 = get_cur_time_ms();
        __printf_chk(1,"%llu,wdog,#11784\n",(int)uVar5,(int)((ulonglong)uVar5 >> 0x20),uVar6,iVar2);
        fflush(stdout);
        local_9c = local_6c;
        uStack_98 = uStack_68;
        uStack_94 = uStack_64;
        uStack_90 = uStack_60;
        DAT_0003433c = local_6c >> 0x10 & 0xff;
        local_8c = local_5c;
        uStack_88 = uStack_58;
        uStack_84 = uStack_54;
        uStack_80 = uStack_50;
        local_7c = (undefined1)local_4c;
        uVar5 = get_cur_time_ms();
        uVar3 = DAT_0003433c;
        __printf_chk(1,"%llu,wdog,#11785`%d\n",(int)uVar5,(int)((ulonglong)uVar5 >> 0x20),
                     DAT_0003433c);
        fflush(stdout);
        if (local_9c._3_1_ != '\0') {
          memset(&DAT_00034ca4,0,0x1e);
          strncpy(&DAT_00034ca4,(char *)((int)&local_9c + 3),0x1e);
          sVar4 = strlen(&DAT_00034ca4);
          uVar1 = DAT_00022394;
          *(undefined4 *)(&DAT_00034ca4 + sVar4) = DAT_00022390;
          (&DAT_00034ca8)[sVar4] = uVar1;
        }
        if ((local_9c & 0xfd) == 1) {
          uVar5 = get_cur_time_ms();
          __printf_chk(1,"%llu,wdog,#11786\n",(int)uVar5,(int)((ulonglong)uVar5 >> 0x20),uVar3);
          fflush(stdout);
          WdogQueueEvent(5);
        }
        else if ((local_9c & 0xff) == 4) {
          uVar5 = get_cur_time_ms();
          __printf_chk(1,"%llu,wdog,#11787\n",(int)uVar5,(int)((ulonglong)uVar5 >> 0x20),uVar3);
          fflush(stdout);
          WdogQueueEvent(7);
        }
        else {
          uVar5 = get_cur_time_ms();
          __printf_chk(1,"%llu,wdog,#11788\n",(int)uVar5,(int)((ulonglong)uVar5 >> 0x20),uVar3);
          fflush(stdout);
          WdogQueueEvent(6);
        }
      }
      goto LAB_0001e83e;
    }
    if (local_78[0] == 0x7050776) {
      uVar5 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11791\n",(int)uVar5,(int)((ulonglong)uVar5 >> 0x20),uVar6,iVar2);
      fflush(stdout);
      __memcpy_chk(auStack_a4,&local_6c,local_70,8);
      FUN_0001c148(auStack_a4);
      FUN_0001cd64();
      goto LAB_0001e83e;
    }
    if (local_78[0] == 0x708032e) {
      uVar5 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11789\n",(int)uVar5,(int)((ulonglong)uVar5 >> 0x20),uVar6,iVar2);
      fflush(stdout);
      WdogQueueEvent(3);
      goto LAB_0001e83e;
    }
    if (local_78[0] != 0x7040334) goto LAB_0001e83e;
    WdogQueueEvent(6);
  } while (DAT_00034c80 != 0);
LAB_0001e898:
  iVar2 = DAT_00034c80;
  uVar5 = get_cur_time_ms();
  __printf_chk(1,"%llu,wdog,#11795\n",(int)uVar5,(int)((ulonglong)uVar5 >> 0x20));
  fflush(stdout);
  if (local_2c != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(iVar2);
  }
  return;
}

