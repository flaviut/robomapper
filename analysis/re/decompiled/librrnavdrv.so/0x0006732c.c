/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x0006732c
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Under core+0x2c8 lock, calls MapFlowSaveGridState sequentially for destination flags; after first
   false, later entries are skipped. Only if all grid stages succeed calls
   PersistSaveMapInfo(vector). If that call returns false, deletes grids via SLAM virtual +0x70 for
   every destination; errors from deletes are ignored. No rollback of already-written grids on an
   earlier grid-stage failure. Persistence success is API acceptance, not proof background writes
   finished. */

int MapFlowSaveMaps(void *core,void *flag_vector)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  int *piVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  int iVar8;
  int *piVar9;
  undefined1 auStack_2c [4];
  int local_28;
  int local_24;
  
  iVar2 = DAT_0006745c + 0x6733e;
  piVar9 = *(int **)(iVar2 + DAT_00067460);
  local_24 = *piVar9;
  iVar8 = *(int *)(iVar2 + DAT_00067464);
  if ((iVar8 != 0) &&
     (iVar1 = pthread_mutex_lock((pthread_mutex_t *)((int)core + 0x2c8)), iVar1 != 0)) {
                    /* WARNING: Subroutine does not return */
    std::__throw_system_error(iVar1);
  }
  GetMapFlagsNames((vector *)&local_28);
  iVar1 = local_28;
  _rrlogmP(3,7,1,0x712,DAT_00067470 + 0x67382,DAT_0006746c + 0x6737e,DAT_00067468 + 0x6737c,local_28
          );
  if (local_28 + -0xc != *(int *)(iVar2 + DAT_00067474)) {
    FUN_00065d38(local_28 + -0xc,auStack_2c);
  }
  piVar3 = *(int **)flag_vector;
  piVar5 = *(int **)((int)flag_vector + 4);
  if (piVar3 == piVar5) {
LAB_000673dc:
    iVar2 = PersistSaveMapInfo(flag_vector);
    if (iVar2 != 0) goto LAB_000673b4;
    _rrlogmP(3,3,1,0x71d,DAT_00067480 + 0x673fc,DAT_0006747c + 0x673f8,DAT_00067478 + 0x673f6,iVar1)
    ;
    puVar6 = *(undefined4 **)((int)flag_vector + 4);
    for (puVar4 = *(undefined4 **)flag_vector; puVar4 != puVar6; puVar4 = puVar4 + 1) {
      uVar7 = *puVar4;
      piVar3 = (int *)FUN_00205d68();
      (**(code **)(*piVar3 + 0x70))(piVar3,uVar7);
    }
  }
  else {
    iVar2 = 1;
    do {
      if (iVar2 != 0) {
        iVar2 = MapFlowSaveGridState(core,*piVar3);
      }
      piVar3 = piVar3 + 1;
    } while (piVar5 != piVar3);
    if (iVar2 != 0) goto LAB_000673dc;
  }
  iVar2 = 0;
LAB_000673b4:
  if (iVar8 != 0) {
    pthread_mutex_unlock((pthread_mutex_t *)((int)core + 0x2c8));
  }
  if (local_24 != *piVar9) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return iVar2;
}

