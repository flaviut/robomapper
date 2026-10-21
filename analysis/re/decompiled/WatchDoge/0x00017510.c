/* Decompiled C, NOT recovered source; need not compile.
 * Binary: WatchDoge
 * SHA256: 3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6
 * Function VA: 0x00017510
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Refreshes each tracked PID via WdogFindPid(name). DOES NOT start processes; this is the target of
   startup call site 0x1467e previously described as process start. Name at record +4; record stride
   0x1c. */

void WdogRefreshPids(void *supervisor)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int *piVar10;
  uint uVar11;
  int iVar12;
  
  iVar12 = *(int *)((int)supervisor + 0x18);
  iVar1 = *(int *)((int)supervisor + 0xc);
  if ((*(int *)((int)supervisor + 0x14) - iVar1 >> 2) * -0x49249249 +
      ((*(int *)((int)supervisor + 0x28) - iVar12 >> 2) + -1) * 0x12 +
      (*(int *)((int)supervisor + 0x1c) - *(int *)((int)supervisor + 0x20) >> 2) * -0x49249249 == 0)
  {
    return;
  }
  iVar9 = 0;
  uVar4 = 0;
  do {
    iVar7 = iVar1 - *(int *)((int)supervisor + 0x10) >> 2;
    uVar8 = iVar7 * -0x49249249 + uVar4;
    if (uVar8 < 0x12) {
      piVar10 = (int *)(iVar1 + iVar9);
    }
    else {
      if ((int)uVar8 < 1) {
        uVar11 = ~(~uVar8 / 0x12);
      }
      else {
        uVar11 = (int)uVar8 / 0x12;
      }
      piVar10 = (int *)((uVar8 + uVar11 * -0x12) * 0x1c + *(int *)(iVar12 + uVar11 * 4));
    }
    uVar8 = iVar7 * -0x49249249 + uVar4;
    if (uVar8 < 0x12) {
      iVar1 = iVar1 + iVar9;
    }
    else {
      if ((int)uVar8 < 1) {
        uVar11 = ~(~uVar8 / 0x12);
      }
      else {
        uVar11 = (int)uVar8 / 0x12;
      }
      iVar1 = (uVar8 + uVar11 * -0x12) * 0x1c + *(int *)(iVar12 + uVar11 * 4);
    }
    uVar4 = uVar4 + 1;
    iVar7 = WdogFindPid(supervisor,*(char **)(iVar1 + 4));
    iVar5 = *(int *)((int)supervisor + 0x1c);
    iVar12 = *(int *)((int)supervisor + 0x18);
    iVar9 = iVar9 + 0x1c;
    iVar3 = *(int *)((int)supervisor + 0x28);
    iVar2 = *(int *)((int)supervisor + 0x20);
    iVar1 = *(int *)((int)supervisor + 0xc);
    iVar6 = *(int *)((int)supervisor + 0x14);
    *piVar10 = iVar7;
  } while (uVar4 < (uint)((iVar6 - iVar1 >> 2) * -0x49249249 +
                         ((iVar3 - iVar12 >> 2) + -1) * 0x12 + (iVar5 - iVar2 >> 2) * -0x49249249));
  return;
}

