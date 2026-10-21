/* Decompiled C, NOT recovered source; need not compile.
 * Binary: WatchDoge
 * SHA256: 3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6
 * Function VA: 0x00017f68
 */

/* WARNING: Removing unreachable block (ram,0x00018322) */
/* WARNING: Removing unreachable block (ram,0x0001832e) */
/* WARNING: Removing unreachable block (ram,0x000182e8) */
/* WARNING: Restarted to delay deadcode elimination for space: ram */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Checks only records with enabled byte +0x18 !=0. Signed PID <=0 or kill(pid,0)!=0 takes
   missing-process handling; tries adoption first. Missing key flag==1 returns status 2 (caller
   recovery/escalation), not direct restart. Other eligible records call WdogStartRecord; status 3
   reflects a nonzero start result. Disabled records are skipped. String-refcount atomics are NOT
   writer synchronization. */

int WdogScanProcesses(void *supervisor)

{
  bool bVar1;
  void *pvVar2;
  int iVar3;
  allocator *paVar4;
  int *piVar5;
  uint uVar6;
  int *record;
  undefined4 *puVar7;
  undefined4 *puVar8;
  int *piVar9;
  int iVar10;
  undefined8 uVar11;
  int local_88;
  void *local_80;
  void *local_7c;
  int local_78;
  undefined4 *local_74;
  void *local_70;
  void *local_6c;
  int local_68;
  undefined4 *local_64;
  int local_60;
  int local_5c;
  char local_58;
  void *local_54;
  int local_50;
  void *local_4c;
  void *local_48;
  int local_44;
  undefined4 *local_40;
  void *local_3c;
  void *local_38;
  int local_34;
  undefined4 *local_30;
  int local_2c;
  
  local_2c = __stack_chk_guard;
  local_54 = (void *)0x0;
  local_4c = (void *)0x0;
  local_48 = (void *)0x0;
  local_44 = 0;
  local_40 = (undefined4 *)0x0;
  local_3c = (void *)0x0;
  local_38 = (void *)0x0;
  local_34 = 0;
  local_30 = (undefined4 *)0x0;
  local_50 = 8;
  pvVar2 = operator_new(0x20);
  uVar6 = local_50 - 1U >> 1;
  puVar8 = (undefined4 *)((int)pvVar2 + uVar6 * 4);
  local_54 = pvVar2;
  local_4c = operator_new(0x1f8);
  *(void **)((int)pvVar2 + uVar6 * 4) = local_4c;
  record = *(int **)((int)supervisor + 0xc);
  piVar9 = *(int **)((int)supervisor + 0x14);
  iVar10 = *(int *)((int)supervisor + 0x18);
  local_44 = (int)local_4c + 0x1f8;
  local_88 = 0;
  local_48 = local_4c;
  local_40 = puVar8;
  local_3c = local_4c;
  local_38 = local_4c;
  local_34 = local_44;
  local_30 = puVar8;
LAB_00017fee:
  if (*(int **)((int)supervisor + 0x1c) == record) {
LAB_000180b2:
    local_7c = local_48;
    local_78 = local_44;
    local_74 = local_40;
    local_70 = local_3c;
    local_6c = local_38;
    local_68 = local_34;
    local_64 = local_30;
    local_80 = local_4c;
    FUN_0001a610(&local_54,&local_80,&local_70);
    if (local_54 != (void *)0x0) {
      puVar7 = local_30 + 1;
      for (puVar8 = local_40; puVar8 < puVar7; puVar8 = puVar8 + 1) {
        operator_delete((void *)*puVar8);
      }
      operator_delete(local_54);
    }
    if (local_2c == __stack_chk_guard) {
      return local_88;
    }
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  do {
    local_70 = (void *)*record;
    std::string::string((string *)&local_6c,(string *)(record + 1));
    std::string::string((string *)&local_68,(string *)(record + 2));
    local_58 = (char)record[6];
    local_64 = (undefined4 *)record[3];
    local_60 = record[4];
    local_5c = record[5];
    if (local_58 == '\0') {
LAB_00018176:
      record = record + 7;
      if (record == piVar9) {
        record = *(int **)(iVar10 + 4);
        iVar10 = iVar10 + 4;
        piVar9 = record + 0x7e;
      }
      if ((allocator *)(local_68 + -0xc) != (allocator *)std::string::_Rep::_S_empty_rep_storage) {
        piVar5 = (int *)(local_68 + -4);
        DataMemoryBarrier(0x1b);
        do {
          ExclusiveAccess(piVar5);
          iVar3 = *piVar5;
          bVar1 = (bool)hasExclusiveAccess(piVar5);
        } while (!bVar1);
        *piVar5 = iVar3 + -1;
        DataMemoryBarrier(0x1b);
        if (iVar3 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_68 + -0xc));
        }
      }
      paVar4 = (allocator *)((int)local_6c + -0xc);
      if (paVar4 == (allocator *)std::string::_Rep::_S_empty_rep_storage) goto LAB_00017fee;
      piVar5 = (int *)((int)local_6c + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar5);
        iVar3 = *piVar5;
        bVar1 = (bool)hasExclusiveAccess(piVar5);
      } while (!bVar1);
      *piVar5 = iVar3 + -1;
    }
    else {
      if (((int)local_70 < 1) || (iVar3 = kill((__pid_t)local_70,0), iVar3 != 0)) {
        iVar3 = std::string::compare((char *)&local_6c);
        if (((((iVar3 == 0) && (DAT_00034338 - 3U < 2)) ||
             ((iVar3 = std::string::compare((char *)&local_6c), iVar3 == 0 &&
              (DAT_00034338 - 3U < 2)))) ||
            ((iVar3 = std::string::compare((char *)&local_6c), iVar3 == 0 && (DAT_00034338 - 3U < 2)
             ))) || ((iVar3 = std::string::compare((char *)&local_6c), iVar3 == 0 &&
                     (DAT_00034338 - 3U < 2)))) goto LAB_00018176;
        iVar3 = std::string::compare((char *)&local_6c);
        if (iVar3 != 0) {
          uVar11 = get_cur_time_ms();
          __printf_chk(1,"%llu,wdog,#11565`%d`%s\n",(int)uVar11,(int)((ulonglong)uVar11 >> 0x20),
                       local_70,local_6c);
          fflush(stdout);
        }
        iVar3 = std::string::compare((char *)&local_6c);
        if (iVar3 == 0) {
          DAT_00034328 = 0;
        }
        iVar3 = WdogAdoptPid(supervisor,record);
        if (iVar3 == 0) {
          if (local_64 == (undefined4 *)0x1) {
            uVar11 = get_cur_time_ms();
            __printf_chk(1,"%llu,wdog,#11566\n",(int)uVar11,(int)((ulonglong)uVar11 >> 0x20));
            fflush(stdout);
            FUN_0001ecf4(&local_6c);
            local_88 = 2;
            FUN_0001a1b0(&local_70);
            goto LAB_000180b2;
          }
          iVar3 = std::string::compare((char *)&local_6c);
          if (iVar3 != 0) {
            FUN_0001ecf4(&local_6c);
          }
          iVar3 = WdogStartRecord(supervisor,&local_70);
          if (iVar3 != 0) {
            uVar11 = get_cur_time_ms();
            __printf_chk(1,&DAT_00020780,(int)uVar11,(int)((ulonglong)uVar11 >> 0x20));
            fflush(stdout);
            local_88 = 3;
          }
        }
      }
      else {
        iVar3 = std::string::compare((char *)&local_6c);
        if (iVar3 == 0) {
          DAT_00034328 = 1;
        }
      }
      record = record + 7;
      if (record == piVar9) {
        record = *(int **)(iVar10 + 4);
        iVar10 = iVar10 + 4;
        piVar9 = record + 0x7e;
      }
      if ((allocator *)(local_68 + -0xc) != (allocator *)std::string::_Rep::_S_empty_rep_storage) {
        piVar5 = (int *)(local_68 + -4);
        DataMemoryBarrier(0x1b);
        do {
          ExclusiveAccess(piVar5);
          iVar3 = *piVar5;
          bVar1 = (bool)hasExclusiveAccess(piVar5);
        } while (!bVar1);
        *piVar5 = iVar3 + -1;
        DataMemoryBarrier(0x1b);
        if (iVar3 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_68 + -0xc));
        }
      }
      paVar4 = (allocator *)((int)local_6c + -0xc);
      if (paVar4 == (allocator *)std::string::_Rep::_S_empty_rep_storage) goto LAB_00017fee;
      piVar5 = (int *)((int)local_6c + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar5);
        iVar3 = *piVar5;
        bVar1 = (bool)hasExclusiveAccess(piVar5);
      } while (!bVar1);
      *piVar5 = iVar3 + -1;
    }
    DataMemoryBarrier(0x1b);
    if (0 < iVar3) goto LAB_00017fee;
    std::string::_Rep::_M_destroy(paVar4);
    if (*(int **)((int)supervisor + 0x1c) == record) goto LAB_000180b2;
  } while( true );
}

