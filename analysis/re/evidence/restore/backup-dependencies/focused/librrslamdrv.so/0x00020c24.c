/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrslamdrv.so
 * SHA256: b48f5f56eb1b2d22abbf727725ea558762337f8f0103229d8da6c1ab6275608a
 * Function VA: 0x00020c24
 */

void FUN_00020c24(int param_1,int *param_2)

{
  bool bVar1;
  void *pvVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  undefined4 uVar7;
  code *pcVar8;
  int *piVar9;
  undefined1 auStack_2c [4];
  int local_28;
  int local_24;
  
  iVar5 = DAT_00020d54 + 0x20c34;
  local_28 = *param_2;
  piVar9 = *(int **)(iVar5 + DAT_00020d58);
  local_24 = *piVar9;
  if (5 < **(uint **)(iVar5 + DAT_00020d5c)) {
    (*(code *)**(undefined4 **)(iVar5 + DAT_00020d60))
              (4,6,0xd3,DAT_00020d64 + 0x20cda,DAT_00020d68 + 0x20c5c,local_28);
    local_28 = *param_2;
  }
  piVar6 = *(int **)(param_1 + 0x44);
  pvVar2 = (void *)(local_28 + -0xc);
  piVar4 = (int *)(local_28 + -4);
  pcVar8 = *(code **)(*piVar6 + 0xc);
  if (*(int *)(local_28 + -4) < 0) {
    local_28 = FUN_0001dcdc(pvVar2,auStack_2c,0);
    if (pcVar8 != *(code **)(iVar5 + DAT_00020d70)) goto LAB_00020d1e;
    uVar7 = 1;
LAB_00020cbe:
    pvVar2 = (void *)(local_28 + -0xc);
    if (pvVar2 == *(void **)(iVar5 + DAT_00020d6c)) goto LAB_00020c94;
    iVar3 = *(int *)(iVar5 + DAT_00020d74);
  }
  else {
    if (pvVar2 == *(void **)(iVar5 + DAT_00020d6c)) {
      if (pcVar8 == *(code **)(iVar5 + DAT_00020d70)) {
        uVar7 = 1;
        goto LAB_00020c94;
      }
LAB_00020d1e:
      uVar7 = (*pcVar8)(piVar6,&local_28);
      goto LAB_00020cbe;
    }
    iVar3 = *(int *)(iVar5 + DAT_00020d74);
    if (iVar3 == 0) {
      *(int *)(local_28 + -4) = *(int *)(local_28 + -4) + 1;
    }
    else {
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar4);
        bVar1 = (bool)hasExclusiveAccess(piVar4);
      } while (!bVar1);
      *piVar4 = *piVar4 + 1;
      DataMemoryBarrier(0x1b);
    }
    if (pcVar8 != *(code **)(iVar5 + DAT_00020d70)) goto LAB_00020d1e;
    uVar7 = 1;
  }
  if (iVar3 == 0) {
    iVar5 = *(int *)(local_28 + -4);
    *(int *)(local_28 + -4) = iVar5 + -1;
  }
  else {
    piVar4 = (int *)(local_28 + -4);
    DataMemoryBarrier(0x1b);
    do {
      ExclusiveAccess(piVar4);
      iVar5 = *piVar4;
      bVar1 = (bool)hasExclusiveAccess(piVar4);
    } while (!bVar1);
    *piVar4 = iVar5 + -1;
    DataMemoryBarrier(0x1b);
  }
  if (iVar5 < 1) {
    operator_delete(pvVar2);
  }
LAB_00020c94:
  if (local_24 != *piVar9) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(uVar7);
  }
  return;
}

