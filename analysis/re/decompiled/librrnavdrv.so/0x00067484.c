/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x00067484
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Under core+0x2c8 lock: grid/state save first, then one-element PersistSaveMapInfo vector.
   Persistence false triggers grid delete via virtual +0x70; returns zero. No cross-file
   commit/durability claim. */

int MapFlowSaveMap(void *core,int native_flag)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int *local_34;
  int *local_30;
  int *local_2c;
  int local_28;
  int local_24;
  
  piVar3 = *(int **)(DAT_00067588 + 0x67492 + DAT_0006758c);
  local_24 = *piVar3;
  iVar4 = *(int *)(DAT_00067588 + 0x67492 + DAT_00067590);
  if ((iVar4 != 0) &&
     (iVar1 = pthread_mutex_lock((pthread_mutex_t *)((int)core + 0x2c8)), iVar1 != 0)) {
                    /* WARNING: Subroutine does not return */
    std::__throw_system_error(iVar1);
  }
  _rrlogmP(3,7,1,0x701,DAT_0006759c + 0x674ce,DAT_00067598 + 0x674ca,DAT_00067594 + 0x674c8,
           native_flag);
  iVar1 = MapFlowSaveGridState(core,native_flag);
  if (iVar1 != 0) {
    local_34 = (int *)0x0;
    local_30 = (int *)0x0;
    local_2c = (int *)0x0;
    local_28 = native_flag;
    local_34 = operator_new(4);
    local_30 = local_34 + 1;
    *local_34 = local_28;
    local_2c = local_30;
    iVar1 = PersistSaveMapInfo((vector *)&local_34);
    if (local_34 != (int *)0x0) {
      operator_delete(local_34);
    }
    if (iVar1 != 0) goto LAB_000674e6;
    _rrlogmP(3,3,1,0x708,DAT_000675a8 + 0x6754a,DAT_000675a4 + 0x67546,DAT_000675a0 + 0x67544);
    piVar2 = (int *)FUN_00205d68();
    (**(code **)(*piVar2 + 0x70))(piVar2,native_flag);
  }
  iVar1 = 0;
LAB_000674e6:
  if (iVar4 != 0) {
    pthread_mutex_unlock((pthread_mutex_t *)((int)core + 0x2c8));
  }
  if (local_24 == *piVar3) {
    return iVar1;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

