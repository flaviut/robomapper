/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x0008339c
 */

/* Calls LoadSLAMMap(core,-2,1), then SaveMap(core,1), then SetSharedCurrentMapFlag(saved manager
   word +0x30); load/save returns are ignored here. Capture and original task signature are not
   reconstructed. */

void MapFlowFallbackLoadTask(int *param_1,undefined4 *param_2)

{
  bool bVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  
  iVar4 = DAT_00083494;
  piVar6 = (int *)param_2[1];
  param_2[1] = 0;
  *param_2 = 0;
  FUN_001a6414();
  uVar2 = FUN_001a6060();
  uVar3 = FUN_001a6414();
  FUN_001a601c(uVar3,0,0xffffffff);
  MapFlowLoadSLAMMap(*(void **)(*param_1 + 0x198),-2,1);
  MapFlowSaveMap(*(void **)(*param_1 + 0x198),1);
  SetSharedCurrentMapFlag(uVar2);
  _rrlogmP(3,6,1,0x28a,DAT_000834a0 + 0x83400,DAT_0008349c + 0x833fc,DAT_00083498 + 0x833fa,uVar2);
  if (piVar6 != (int *)0x0) {
    if (*(int *)(iVar4 + 0x833b0 + DAT_000834a4) == 0) {
      iVar4 = piVar6[1];
      piVar6[1] = iVar4 + -1;
      if (iVar4 != 1) {
        return;
      }
      (**(code **)(*piVar6 + 8))(piVar6);
      iVar4 = piVar6[2];
      piVar6[2] = iVar4 + -1;
    }
    else {
      piVar5 = piVar6 + 1;
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar5);
        iVar4 = *piVar5;
        bVar1 = (bool)hasExclusiveAccess(piVar5);
      } while (!bVar1);
      *piVar5 = iVar4 + -1;
      DataMemoryBarrier(0x1b);
      if (iVar4 != 1) {
        return;
      }
      (**(code **)(*piVar6 + 8))(piVar6);
      piVar5 = piVar6 + 2;
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar5);
        iVar4 = *piVar5;
        bVar1 = (bool)hasExclusiveAccess(piVar5);
      } while (!bVar1);
      *piVar5 = iVar4 + -1;
      DataMemoryBarrier(0x1b);
    }
    if (iVar4 == 1) {
                    /* WARNING: Could not recover jumptable at 0x00083486. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*piVar6 + 0xc))(piVar6);
      return;
    }
  }
  return;
}

