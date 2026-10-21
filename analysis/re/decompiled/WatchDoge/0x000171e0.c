/* Decompiled C, NOT recovered source; need not compile.
 * Binary: WatchDoge
 * SHA256: 3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6
 * Function VA: 0x000171e0
 */

/* WARNING: Removing unreachable block (ram,0x000173c0) */
/* WARNING: Removing unreachable block (ram,0x000173cc) */
/* WARNING: Removing unreachable block (ram,0x000173b4) */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Walks 0x1c-byte records; skips enabled byte +0x18==0 and exits if supervisor byte +0 is nonzero.
   Calls WdogStartRecord and sleeps record delay +0x14 for enabled records. Not a quiescence
   barrier. */

void WdogStartEnabled(void *supervisor)

{
  bool bVar1;
  allocator *paVar2;
  int iVar3;
  int *piVar4;
  string *psVar5;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  int *local_54;
  undefined4 local_48;
  int local_44;
  int local_40;
  undefined4 local_3c;
  undefined4 local_38;
  uint local_34;
  string local_30;
  int local_2c;
  
  local_2c = __stack_chk_guard;
  uVar8 = get_cur_time_ms();
  __printf_chk(1,"%llu,wdog,#11560`%d\n",(int)uVar8,(int)((ulonglong)uVar8 >> 0x20),DAT_00034338);
  fflush(stdout);
  local_54 = *(int **)((int)supervisor + 0x18);
  iVar6 = *(int *)((int)supervisor + 0xc);
  iVar7 = *(int *)((int)supervisor + 0x14);
  do {
    psVar5 = (string *)(iVar6 + 8);
    do {
      while( true ) {
        if ((*(int *)((int)supervisor + 0x1c) == iVar6) || (*(char *)supervisor != '\0')) {
          if (local_2c != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
            __stack_chk_fail();
          }
          return;
        }
        local_48 = *(undefined4 *)(psVar5 + -8);
        std::string::string((string *)&local_44,(string *)(iVar6 + 4));
        std::string::string((string *)&local_40,psVar5);
        local_3c = *(undefined4 *)(psVar5 + 4);
        local_30 = psVar5[0x10];
        local_38 = *(undefined4 *)(psVar5 + 8);
        local_34 = *(uint *)(psVar5 + 0xc);
        if (local_30 != (string)0x0) break;
        if ((allocator *)(local_40 + -0xc) != (allocator *)std::string::_Rep::_S_empty_rep_storage)
        {
          piVar4 = (int *)(local_40 + -4);
          DataMemoryBarrier(0x1b);
          do {
            ExclusiveAccess(piVar4);
            iVar3 = *piVar4;
            bVar1 = (bool)hasExclusiveAccess(piVar4);
          } while (!bVar1);
          *piVar4 = iVar3 + -1;
          DataMemoryBarrier(0x1b);
          if (iVar3 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_40 + -0xc));
          }
        }
        paVar2 = (allocator *)(local_44 + -0xc);
        if (paVar2 != (allocator *)std::string::_Rep::_S_empty_rep_storage) {
          piVar4 = (int *)(local_44 + -4);
          DataMemoryBarrier(0x1b);
          do {
            ExclusiveAccess(piVar4);
            iVar3 = *piVar4;
            bVar1 = (bool)hasExclusiveAccess(piVar4);
          } while (!bVar1);
          *piVar4 = iVar3 + -1;
          goto LAB_0001730c;
        }
LAB_0001726c:
        iVar6 = iVar6 + 0x1c;
        psVar5 = psVar5 + 0x1c;
        if (iVar7 == iVar6) goto LAB_00017324;
      }
      WdogStartRecord(supervisor,&local_48);
      uVar8 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11561`%d\n",(int)uVar8,(int)((ulonglong)uVar8 >> 0x20),local_34);
      fflush(stdout);
      sleep(local_34);
      if ((allocator *)(local_40 + -0xc) != (allocator *)std::string::_Rep::_S_empty_rep_storage) {
        piVar4 = (int *)(local_40 + -4);
        DataMemoryBarrier(0x1b);
        do {
          ExclusiveAccess(piVar4);
          iVar3 = *piVar4;
          bVar1 = (bool)hasExclusiveAccess(piVar4);
        } while (!bVar1);
        *piVar4 = iVar3 + -1;
        DataMemoryBarrier(0x1b);
        if (iVar3 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_40 + -0xc));
        }
      }
      paVar2 = (allocator *)(local_44 + -0xc);
      if (paVar2 == (allocator *)std::string::_Rep::_S_empty_rep_storage) goto LAB_0001726c;
      piVar4 = (int *)(local_44 + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar4);
        iVar3 = *piVar4;
        bVar1 = (bool)hasExclusiveAccess(piVar4);
      } while (!bVar1);
      *piVar4 = iVar3 + -1;
LAB_0001730c:
      DataMemoryBarrier(0x1b);
      if (0 < iVar3) goto LAB_0001726c;
      iVar6 = iVar6 + 0x1c;
      std::string::_Rep::_M_destroy(paVar2);
      psVar5 = psVar5 + 0x1c;
    } while (iVar7 != iVar6);
LAB_00017324:
    local_54 = local_54 + 1;
    iVar6 = *local_54;
    iVar7 = iVar6 + 0x1f8;
  } while( true );
}

