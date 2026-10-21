/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x0012a35c
 */

void FUN_0012a35c(int param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  undefined4 uVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  undefined4 local_4c;
  undefined4 local_48;
  int local_44;
  
  piVar3 = *(int **)(DAT_0012a558 + 0x12a368 + DAT_0012a55c);
  local_44 = *piVar3;
  _rrlogmP(3,6,1,0x3d,DAT_0012a568 + 0x12a38c,DAT_0012a564 + 0x12a382,DAT_0012a560 + 0x12a380);
  iVar2 = GetSharedSegmentMap();
  if (iVar2 == 0) {
    FUN_0012a2c0(param_1,param_2);
  }
  else {
    memcpy((void *)(param_1 + 4),(void *)(iVar2 + 4),0x10000c);
    iVar8 = *(int *)(param_1 + 8);
    iVar4 = *(int *)(param_1 + 0xc);
    iVar2 = 0;
    *(int *)(param_1 + 0x10003c) = iVar4 * iVar8;
    dVar10 = round((double)(longlong)-(iVar8 / 2));
    dVar11 = round((double)(longlong)-(iVar4 / 2));
    dVar12 = round((double)(longlong)iVar8);
    dVar13 = round((double)(longlong)iVar4);
    local_5c = (int)(longlong)dVar10;
    local_58 = (int)(longlong)dVar11;
    dVar12 = round((double)(longlong)(int)(longlong)dVar12);
    dVar10 = round((double)(longlong)((int)(longlong)dVar12 + (int)(longlong)dVar10));
    dVar10 = round((double)(longlong)((int)(longlong)dVar10 + -1));
    dVar12 = round((double)(longlong)(int)(longlong)dVar13);
    dVar11 = round((double)(longlong)((int)(longlong)dVar12 + (int)(longlong)dVar11));
    dVar11 = round((double)(longlong)((int)(longlong)dVar11 + -1));
    local_4c = 0;
    local_48 = 0;
    local_50 = (int)(longlong)dVar11;
    local_54 = (int)(longlong)dVar10;
    FUN_000d5808(&local_5c);
    if (-1 < local_54 - local_5c) {
      iVar2 = (local_54 - local_5c) + 1;
    }
    if (local_50 - local_58 < 0) {
      iVar4 = 0;
    }
    else {
      iVar4 = (local_50 - local_58) + 1;
    }
    *(int *)(&DAT_00100010 + param_1) = local_5c;
    *(int *)(&DAT_00100014 + param_1) = local_58;
    *(int *)(&DAT_00100018 + param_1) = local_54;
    *(int *)(&DAT_0010001c + param_1) = local_50;
    *(int *)(param_1 + 0x100020) = iVar2;
    *(int *)(param_1 + 0x100024) = iVar4;
    *(undefined4 *)(param_1 + 0x100040) = 0x23;
    if (param_2 != 0) {
      FUN_0012a288(param_1);
    }
  }
  iVar2 = *(int *)(param_1 + 0x100070);
  puVar5 = *(undefined4 **)(param_1 + 0x100060);
  uVar6 = *(undefined4 *)(param_1 + 0x100054);
  uVar7 = *(undefined4 *)(param_1 + 0x100058);
  uVar9 = *(undefined4 *)(param_1 + 0x10005c);
  puVar1 = puVar5;
  while (puVar1 = puVar1 + 1, puVar1 < (undefined4 *)(iVar2 + 4)) {
    operator_delete((void *)*puVar1);
  }
  *(undefined4 *)(param_1 + 0x100064) = uVar6;
  iVar2 = *piVar3;
  *(undefined4 *)(param_1 + 0x100068) = uVar7;
  *(undefined4 *)(param_1 + 0x10006c) = uVar9;
  *(undefined4 **)(param_1 + 0x100070) = puVar5;
  if (local_44 == iVar2) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

