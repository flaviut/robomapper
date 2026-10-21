/* Decompiled C, NOT recovered source; need not compile.
 * Binary: WatchDoge
 * SHA256: 3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6
 * Function VA: 0x00019ae0
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Reverse-order stop of positive tracked PIDs. First invokes WdogSignalTrackedPid(...,pid,0), which
   sends signal 1 to a non-zombie PID or signal 9 to a parsed parent for zombie state. mode 1 sends
   rua_keep_mcu_heartbeat(120), then bounded proc-status disappearance polling; mode 2 does that
   only for name rrlogd; mode 0 does not send this heartbeat control. Unsuccessful/no wait falls
   back to kill(pid,9). After sleep(1), kill(pid,0) checks return 1 if any tracked positive PID
   still exists, else 0. Successful waits clear tracked PID to zero. No waitpid, fsync, child-tree
   barrier or map-write acknowledgment; permission errors/PID reuse and ignored kill results limit
   interpretation. */

int WdogStopProcesses(void *supervisor,WdogStopMode mode)

{
  char *pcVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  __pid_t *p_Var6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int *piVar11;
  undefined4 uVar12;
  undefined8 uVar13;
  
  iVar8 = *(int *)((int)supervisor + 0x18);
  iVar10 = *(int *)((int)supervisor + 0xc);
  iVar4 = (*(int *)((int)supervisor + 0x14) - iVar10 >> 2) * -0x49249249 +
          ((*(int *)((int)supervisor + 0x28) - iVar8 >> 2) + -1) * 0x12 +
          (*(int *)((int)supervisor + 0x1c) - *(int *)((int)supervisor + 0x20) >> 2) * -0x49249249;
  iVar9 = iVar4 + -1;
  if (-1 < iVar9) {
    iVar4 = iVar4 * 0x1c;
    pcVar1 = "%llu,wdog,#11532`%d`%s\n";
    do {
      iVar4 = iVar4 + -0x1c;
      uVar5 = (iVar10 - *(int *)((int)supervisor + 0x10) >> 2) * -0x49249249 + iVar9;
      if (uVar5 < 0x12) {
        piVar11 = (int *)(iVar10 + iVar4);
      }
      else {
        if ((int)uVar5 < 1) {
          uVar2 = ~uVar5;
          uVar7 = ~(uVar2 / 0x12);
        }
        else {
          uVar7 = (int)uVar5 / 0x12;
          uVar2 = uVar5;
        }
        pcVar1 = (char *)(uVar2 * 0x38e38e39);
        piVar11 = (int *)((uVar5 + uVar7 * -0x12) * 0x1c + *(int *)(iVar8 + uVar7 * 4));
      }
      if (0 < *piVar11) {
        uVar13 = get_cur_time_ms(pcVar1);
        iVar8 = *(int *)((int)supervisor + 0xc);
        uVar5 = (iVar8 - *(int *)((int)supervisor + 0x10) >> 2) * -0x49249249 + iVar9;
        if (uVar5 < 0x12) {
          iVar10 = iVar8 + iVar4;
          uVar3 = *(undefined4 *)(iVar8 + iVar4);
        }
        else {
          if ((int)uVar5 < 1) {
            iVar8 = *(int *)((int)supervisor + 0x18);
            uVar7 = ~(~uVar5 / 0x12);
            uVar3 = *(undefined4 *)(*(int *)(iVar8 + uVar7 * 4) + (uVar5 + uVar7 * -0x12) * 0x1c);
          }
          else {
            iVar8 = *(int *)((int)supervisor + 0x18);
            uVar7 = (int)uVar5 / 0x12;
            uVar3 = *(undefined4 *)(*(int *)(iVar8 + uVar7 * 4) + ((int)uVar5 % 0x12) * 0x1c);
          }
          iVar10 = (uVar5 + uVar7 * -0x12) * 0x1c + *(int *)(iVar8 + uVar7 * 4);
        }
        uVar12 = *(undefined4 *)(iVar10 + 4);
        __printf_chk(1,"%llu,wdog,#11532`%d`%s\n",(int)uVar13,(int)((ulonglong)uVar13 >> 0x20),uVar3
                     ,uVar12);
        fflush(stdout);
        uVar5 = (*(int *)((int)supervisor + 0xc) - *(int *)((int)supervisor + 0x10) >> 2) *
                -0x49249249 + iVar9;
        if (uVar5 < 0x12) {
          piVar11 = (int *)(*(int *)((int)supervisor + 0xc) + iVar4);
        }
        else {
          if ((int)uVar5 < 1) {
            uVar7 = ~(~uVar5 / 0x12);
          }
          else {
            uVar7 = (int)uVar5 / 0x12;
          }
          piVar11 = (int *)((uVar5 + uVar7 * -0x12) * 0x1c +
                           *(int *)(*(int *)((int)supervisor + 0x18) + uVar7 * 4));
        }
        pcVar1 = (char *)WdogSignalTrackedPid(supervisor,*piVar11,0);
        if (mode == WdogStopWaitAll) {
          uVar13 = get_cur_time_ms();
          __printf_chk(1,"%llu,wdog,#11534\n",(int)uVar13,(int)((ulonglong)uVar13 >> 0x20),uVar3,
                       uVar12);
          fflush(stdout);
          rua_keep_mcu_heartbeat(0x78);
          iVar8 = *(int *)((int)supervisor + 0xc);
          uVar5 = (iVar8 - *(int *)((int)supervisor + 0x10) >> 2) * -0x49249249 + iVar9;
          if (uVar5 < 0x12) {
            iVar8 = WdogWaitProcGone(supervisor,*(int *)(iVar8 + iVar4),
                                     *(int *)(iVar8 + iVar4 + 0x10));
          }
          else {
            if ((int)uVar5 < 1) {
              iVar10 = *(int *)((int)supervisor + 0x18);
              uVar7 = ~(~uVar5 / 0x12);
              iVar8 = *(int *)(*(int *)(iVar10 + uVar7 * 4) + (uVar5 + uVar7 * -0x12) * 0x1c);
            }
            else {
              iVar10 = *(int *)((int)supervisor + 0x18);
              uVar7 = (int)uVar5 / 0x12;
              iVar8 = *(int *)(*(int *)(iVar10 + uVar7 * 4) + ((int)uVar5 % 0x12) * 0x1c);
            }
            iVar8 = WdogWaitProcGone(supervisor,iVar8,
                                     *(int *)((uVar5 + uVar7 * -0x12) * 0x1c +
                                              *(int *)(iVar10 + uVar7 * 4) + 0x10));
          }
          if (iVar8 != 0) {
            uVar13 = get_cur_time_ms();
            pcVar1 = "%llu,wdog,#11535\n";
LAB_00019e26:
            __printf_chk(1,pcVar1,(int)uVar13,(int)((ulonglong)uVar13 >> 0x20));
            pcVar1 = (char *)fflush(stdout);
            uVar5 = (*(int *)((int)supervisor + 0xc) - *(int *)((int)supervisor + 0x10) >> 2) *
                    -0x49249249 + iVar9;
            if (uVar5 < 0x12) {
              *(undefined4 *)(*(int *)((int)supervisor + 0xc) + iVar4) = 0;
            }
            else {
              if ((int)uVar5 < 1) {
                pcVar1 = (char *)~(~uVar5 / 0x12);
              }
              else {
                pcVar1 = (char *)((int)uVar5 / 0x12);
              }
              *(undefined4 *)
               ((uVar5 + (int)pcVar1 * -0x12) * 0x1c +
               *(int *)(*(int *)((int)supervisor + 0x18) + (int)pcVar1 * 4)) = 0;
            }
            goto joined_r0x00019d74;
          }
          uVar13 = get_cur_time_ms();
          pcVar1 = "%llu,wdog,#11536\n";
        }
        else if (mode == WdogStopNoWait) {
          uVar13 = get_cur_time_ms();
          pcVar1 = "%llu,wdog,#11533\n";
        }
        else {
          if (mode != WdogStopWaitRrlogd) goto joined_r0x00019d74;
          uVar5 = (*(int *)((int)supervisor + 0xc) - *(int *)((int)supervisor + 0x10) >> 2) *
                  -0x49249249 + iVar9;
          if (uVar5 < 0x12) {
            iVar8 = *(int *)((int)supervisor + 0xc) + iVar4;
          }
          else {
            if ((int)uVar5 < 1) {
              uVar7 = ~(~uVar5 / 0x12);
            }
            else {
              uVar7 = (int)uVar5 / 0x12;
            }
            iVar8 = (uVar5 + uVar7 * -0x12) * 0x1c +
                    *(int *)(*(int *)((int)supervisor + 0x18) + uVar7 * 4);
          }
          iVar8 = strcmp(*(char **)(iVar8 + 4),"rrlogd");
          if (iVar8 == 0) {
            uVar13 = get_cur_time_ms();
            __printf_chk(1,"%llu,wdog,#11537\n",(int)uVar13,(int)((ulonglong)uVar13 >> 0x20));
            fflush(stdout);
            rua_keep_mcu_heartbeat(0x78);
            iVar8 = *(int *)((int)supervisor + 0xc);
            uVar5 = (iVar8 - *(int *)((int)supervisor + 0x10) >> 2) * -0x49249249 + iVar9;
            if (uVar5 < 0x12) {
              iVar8 = WdogWaitProcGone(supervisor,*(int *)(iVar8 + iVar4),
                                       *(int *)(iVar8 + iVar4 + 0x10));
            }
            else {
              if ((int)uVar5 < 1) {
                iVar10 = *(int *)((int)supervisor + 0x18);
                uVar7 = ~(~uVar5 / 0x12);
                iVar8 = *(int *)(*(int *)(iVar10 + uVar7 * 4) + (uVar5 + uVar7 * -0x12) * 0x1c);
              }
              else {
                iVar10 = *(int *)((int)supervisor + 0x18);
                uVar7 = (int)uVar5 / 0x12;
                iVar8 = *(int *)(*(int *)(iVar10 + uVar7 * 4) + ((int)uVar5 % 0x12) * 0x1c);
              }
              iVar8 = WdogWaitProcGone(supervisor,iVar8,
                                       *(int *)((uVar5 + uVar7 * -0x12) * 0x1c +
                                                *(int *)(iVar10 + uVar7 * 4) + 0x10));
            }
            if (iVar8 != 0) {
              uVar13 = get_cur_time_ms();
              pcVar1 = "%llu,wdog,#11538\n";
              goto LAB_00019e26;
            }
            uVar13 = get_cur_time_ms();
            pcVar1 = "%llu,wdog,#11539\n";
          }
          else {
            uVar13 = get_cur_time_ms();
            pcVar1 = "%llu,wdog,#11540\n";
          }
        }
        __printf_chk(1,pcVar1,(int)uVar13,(int)((ulonglong)uVar13 >> 0x20));
        fflush(stdout);
        uVar5 = (*(int *)((int)supervisor + 0xc) - *(int *)((int)supervisor + 0x10) >> 2) *
                -0x49249249 + iVar9;
        if (uVar5 < 0x12) {
          p_Var6 = (__pid_t *)(*(int *)((int)supervisor + 0xc) + iVar4);
        }
        else {
          if ((int)uVar5 < 1) {
            uVar7 = ~(~uVar5 / 0x12);
          }
          else {
            uVar7 = (int)uVar5 / 0x12;
          }
          p_Var6 = (__pid_t *)
                   ((uVar5 + uVar7 * -0x12) * 0x1c +
                   *(int *)(*(int *)((int)supervisor + 0x18) + uVar7 * 4));
        }
        pcVar1 = (char *)kill(*p_Var6,9);
      }
joined_r0x00019d74:
      if (iVar9 == 0) break;
      iVar9 = iVar9 + -1;
      iVar10 = *(int *)((int)supervisor + 0xc);
      iVar8 = *(int *)((int)supervisor + 0x18);
    } while( true );
  }
  sleep(1);
  uVar13 = get_cur_time_ms();
  __printf_chk(1,"%llu,wdog,#11541\n",(int)uVar13,(int)((ulonglong)uVar13 >> 0x20));
  fflush(stdout);
  iVar10 = *(int *)((int)supervisor + 0x18);
  iVar9 = *(int *)((int)supervisor + 0xc);
  iVar4 = (*(int *)((int)supervisor + 0x14) - iVar9 >> 2) * -0x49249249 +
          ((*(int *)((int)supervisor + 0x28) - iVar10 >> 2) + -1) * 0x12 +
          (*(int *)((int)supervisor + 0x1c) - *(int *)((int)supervisor + 0x20) >> 2) * -0x49249249;
  iVar8 = iVar4 + -1;
  if (iVar8 < 0) {
LAB_0001a0c0:
    uVar13 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11543\n",(int)uVar13,(int)((ulonglong)uVar13 >> 0x20));
    fflush(stdout);
    return 0;
  }
  iVar4 = iVar4 * 0x1c;
  do {
    iVar4 = iVar4 + -0x1c;
    uVar5 = (iVar9 - *(int *)((int)supervisor + 0x10) >> 2) * -0x49249249 + iVar8;
    if (uVar5 < 0x12) {
      if (0 < *(int *)(iVar9 + iVar4)) {
        iVar9 = kill(*(__pid_t *)(iVar9 + iVar4),0);
        goto joined_r0x00019ee6;
      }
    }
    else {
      if ((int)uVar5 < 1) {
        uVar7 = ~(~uVar5 / 0x12);
      }
      else {
        uVar7 = (int)uVar5 / 0x12;
      }
      if (0 < *(int *)(*(int *)(iVar10 + uVar7 * 4) + (uVar5 + uVar7 * -0x12) * 0x1c)) {
        if ((int)uVar5 < 1) {
          uVar7 = ~(~uVar5 / 0x12);
        }
        else {
          uVar7 = (int)uVar5 / 0x12;
        }
        iVar9 = kill(*(__pid_t *)((uVar5 + uVar7 * -0x12) * 0x1c + *(int *)(iVar10 + uVar7 * 4)),0);
joined_r0x00019ee6:
        if (iVar9 == 0) {
          uVar13 = get_cur_time_ms();
          iVar4 = *(int *)((int)supervisor + 0xc);
          uVar5 = (iVar4 - *(int *)((int)supervisor + 0x10) >> 2) * -0x49249249 + iVar8;
          if (uVar5 < 0x12) {
            iVar9 = iVar4 + iVar8 * 0x1c;
            uVar3 = *(undefined4 *)(iVar4 + iVar8 * 0x1c);
          }
          else {
            if ((int)uVar5 < 1) {
              iVar4 = *(int *)((int)supervisor + 0x18);
              uVar7 = ~(~uVar5 / 0x12);
              uVar3 = *(undefined4 *)(*(int *)(iVar4 + uVar7 * 4) + (uVar5 + uVar7 * -0x12) * 0x1c);
            }
            else {
              iVar4 = *(int *)((int)supervisor + 0x18);
              uVar7 = (int)uVar5 / 0x12;
              uVar3 = *(undefined4 *)(*(int *)(iVar4 + uVar7 * 4) + ((int)uVar5 % 0x12) * 0x1c);
            }
            iVar9 = (uVar5 + uVar7 * -0x12) * 0x1c + *(int *)(iVar4 + uVar7 * 4);
          }
          __printf_chk(1,"%llu,wdog,#11542`%d`%s\n",(int)uVar13,(int)((ulonglong)uVar13 >> 0x20),
                       uVar3,*(undefined4 *)(iVar9 + 4));
          fflush(stdout);
          return 1;
        }
      }
    }
    if (iVar8 == 0) goto LAB_0001a0c0;
    iVar9 = *(int *)((int)supervisor + 0xc);
    iVar10 = *(int *)((int)supervisor + 0x18);
    iVar8 = iVar8 + -1;
  } while( true );
}

