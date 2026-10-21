/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x0006905c
 */

/* Task captures core at capture+0x10, native flag at +8 and request words at +0/+4. Calls
   LoadSLAMMap(core,flag,1) at 0x69076 and stores its result in completion capture+0x2c; completion
   callback pointer is read from vtable-like data 0x304b78 -> Thumb 0x683e1, which lacks baseline
   function/disassembly. Does not itself send a network reply. */

void MapFlowLoadTask(undefined4 *param_1,undefined4 *param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  int *piVar10;
  int iVar11;
  int iVar12;
  int *piVar13;
  int iVar14;
  int *piVar15;
  int iVar16;
  int iVar17;
  
  iVar12 = DAT_00069270;
  piVar8 = (int *)*param_1;
  piVar13 = (int *)param_2[1];
  *param_2 = 0;
  param_2[1] = 0;
  iVar3 = MapFlowLoadSLAMMap((void *)piVar8[4],piVar8[2],1);
  iVar17 = piVar8[4];
  iVar7 = piVar8[2];
  iVar14 = *piVar8;
  iVar16 = piVar8[1];
  iVar11 = *(int *)(iVar17 + 0x498);
  iVar9 = piVar8[5];
  piVar8 = operator_new(0x30);
  iVar2 = DAT_0006927c;
  iVar5 = DAT_00069278;
  *piVar8 = DAT_00069274 + 0x690a8;
  piVar8[6] = iVar9;
  piVar8[8] = iVar14;
  piVar8[9] = iVar16;
  piVar8[10] = iVar7;
  piVar15 = piVar8 + 1;
  piVar8[4] = iVar2 + 0x690b4;
  piVar8[1] = 1;
  piVar8[2] = 1;
  piVar8[7] = iVar17;
  piVar8[0xb] = iVar3;
  uVar4 = FUN_000650c4(piVar8,*(undefined4 *)(iVar12 + 0x69072 + iVar5));
  iVar5 = DAT_00069280;
  piVar10 = *(int **)(iVar11 + 8);
  *(undefined4 *)(iVar11 + 4) = uVar4;
  iVar12 = *(int *)(iVar12 + 0x69072 + iVar5);
  if (piVar8 != piVar10) {
    if (iVar12 == 0) {
      piVar8[1] = piVar8[1] + 1;
      if ((piVar10 != (int *)0x0) && (iVar5 = piVar10[1], piVar10[1] = iVar5 + -1, iVar5 == 1)) {
        (**(code **)(*piVar10 + 8))(piVar10);
        iVar5 = piVar10[2];
        piVar10[2] = iVar5 + -1;
LAB_00069252:
        if (iVar5 == 1) {
          (**(code **)(*piVar10 + 0xc))(piVar10);
        }
      }
    }
    else {
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar15);
        bVar1 = (bool)hasExclusiveAccess(piVar15);
      } while (!bVar1);
      *piVar15 = *piVar15 + 1;
      DataMemoryBarrier(0x1b);
      piVar10 = *(int **)(iVar11 + 8);
      if (piVar10 != (int *)0x0) {
        piVar6 = piVar10 + 1;
        DataMemoryBarrier(0x1b);
        do {
          ExclusiveAccess(piVar6);
          iVar5 = *piVar6;
          bVar1 = (bool)hasExclusiveAccess(piVar6);
        } while (!bVar1);
        *piVar6 = iVar5 + -1;
        DataMemoryBarrier(0x1b);
        if (iVar5 == 1) {
          (**(code **)(*piVar10 + 8))(piVar10);
          piVar6 = piVar10 + 2;
          DataMemoryBarrier(0x1b);
          do {
            ExclusiveAccess(piVar6);
            iVar5 = *piVar6;
            bVar1 = (bool)hasExclusiveAccess(piVar6);
          } while (!bVar1);
          *piVar6 = iVar5 + -1;
          DataMemoryBarrier(0x1b);
          goto LAB_00069252;
        }
      }
    }
    *(int **)(iVar11 + 8) = piVar8;
  }
  if (iVar12 == 0) {
    iVar5 = piVar8[1];
    piVar8[1] = iVar5 + -1;
    if (iVar5 != 1) goto LAB_00069136;
    (**(code **)(*piVar8 + 8))(piVar8);
    iVar5 = piVar8[2];
    piVar8[2] = iVar5 + -1;
  }
  else {
    DataMemoryBarrier(0x1b);
    do {
      ExclusiveAccess(piVar15);
      iVar5 = *piVar15;
      bVar1 = (bool)hasExclusiveAccess(piVar15);
    } while (!bVar1);
    *piVar15 = iVar5 + -1;
    DataMemoryBarrier(0x1b);
    if (iVar5 != 1) goto LAB_00069136;
    (**(code **)(*piVar8 + 8))(piVar8);
    piVar10 = piVar8 + 2;
    DataMemoryBarrier(0x1b);
    do {
      ExclusiveAccess(piVar10);
      iVar5 = *piVar10;
      bVar1 = (bool)hasExclusiveAccess(piVar10);
    } while (!bVar1);
    *piVar10 = iVar5 + -1;
    DataMemoryBarrier(0x1b);
  }
  if (iVar5 == 1) {
    (**(code **)(*piVar8 + 0xc))(piVar8);
  }
LAB_00069136:
  if (piVar13 != (int *)0x0) {
    if (iVar12 == 0) {
      iVar12 = piVar13[1];
      piVar13[1] = iVar12 + -1;
      if (iVar12 != 1) {
        return;
      }
      (**(code **)(*piVar13 + 8))(piVar13);
      iVar12 = piVar13[2];
      piVar13[2] = iVar12 + -1;
    }
    else {
      piVar8 = piVar13 + 1;
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar8);
        iVar12 = *piVar8;
        bVar1 = (bool)hasExclusiveAccess(piVar8);
      } while (!bVar1);
      *piVar8 = iVar12 + -1;
      DataMemoryBarrier(0x1b);
      if (iVar12 != 1) {
        return;
      }
      (**(code **)(*piVar13 + 8))(piVar13);
      piVar8 = piVar13 + 2;
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar8);
        iVar12 = *piVar8;
        bVar1 = (bool)hasExclusiveAccess(piVar8);
      } while (!bVar1);
      *piVar8 = iVar12 + -1;
      DataMemoryBarrier(0x1b);
    }
    if (iVar12 == 1) {
                    /* WARNING: Could not recover jumptable at 0x0006922e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*piVar13 + 0xc))(piVar13);
      return;
    }
  }
  return;
}

