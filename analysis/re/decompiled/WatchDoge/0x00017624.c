/* Decompiled C, NOT recovered source; need not compile.
 * Binary: WatchDoge
 * SHA256: 3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6
 * Function VA: 0x00017624
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Refreshes tracked PIDs, logs records with signed PID <1, and returns 1 unconditionally on normal
   completion. Its success value is not confirmation that all expected processes are alive. */

int WdogRefreshAndCheckPids(void *supervisor)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined8 uVar11;
  
  WdogRefreshPids(supervisor);
  iVar10 = *(int *)((int)supervisor + 0x18);
  iVar9 = *(int *)((int)supervisor + 0x28);
  iVar7 = *(int *)((int)supervisor + 0x1c);
  iVar6 = *(int *)((int)supervisor + 0x20);
  iVar2 = *(int *)((int)supervisor + 0xc);
  iVar8 = *(int *)((int)supervisor + 0x14);
  if ((iVar8 - iVar2 >> 2) * -0x49249249 +
      ((iVar9 - iVar10 >> 2) + -1) * 0x12 + (iVar7 - iVar6 >> 2) * -0x49249249 != 0) {
    uVar5 = 0;
    do {
      uVar3 = (iVar2 - *(int *)((int)supervisor + 0x10) >> 2) * -0x49249249 + uVar5;
      if (uVar3 < 0x12) {
        iVar4 = *(int *)(uVar5 * 0x1c + iVar2);
      }
      else {
        if ((int)uVar3 < 1) {
          uVar1 = ~(~uVar3 / 0x12);
        }
        else {
          uVar1 = (int)uVar3 / 0x12;
        }
        iVar4 = *(int *)((uVar3 + uVar1 * -0x12) * 0x1c + *(int *)(iVar10 + uVar1 * 4));
      }
      if (iVar4 < 1) {
        uVar11 = get_cur_time_ms();
        uVar3 = (*(int *)((int)supervisor + 0xc) - *(int *)((int)supervisor + 0x10) >> 2) *
                -0x49249249 + uVar5;
        if (uVar3 < 0x12) {
          iVar2 = uVar5 * 0x1c + *(int *)((int)supervisor + 0xc);
        }
        else {
          if ((int)uVar3 < 1) {
            uVar1 = ~(~uVar3 / 0x12);
          }
          else {
            uVar1 = (int)uVar3 / 0x12;
          }
          iVar2 = (uVar3 + uVar1 * -0x12) * 0x1c +
                  *(int *)(*(int *)((int)supervisor + 0x18) + uVar1 * 4);
        }
        __printf_chk(1,"%llu,wdog,#11529`%s\n",(int)uVar11,(int)((ulonglong)uVar11 >> 0x20),
                     *(undefined4 *)(iVar2 + 4));
        fflush(stdout);
        iVar10 = *(int *)((int)supervisor + 0x18);
        iVar2 = *(int *)((int)supervisor + 0xc);
        iVar9 = *(int *)((int)supervisor + 0x28);
        iVar7 = *(int *)((int)supervisor + 0x1c);
        iVar6 = *(int *)((int)supervisor + 0x20);
        iVar8 = *(int *)((int)supervisor + 0x14);
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 < (uint)((iVar8 - iVar2 >> 2) * -0x49249249 +
                           ((iVar9 - iVar10 >> 2) + -1) * 0x12 + (iVar7 - iVar6 >> 2) * -0x49249249)
            );
  }
  return 1;
}

