/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x00067144
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Flag 1 refuses saving when manager+0x1f or core+0x271 is set. Otherwise grid-save wrapper
   0x1a60c4 runs first; on success stores catalog current flag as manager stored flag for
   destination 1, or destination flag for >1. Then captures shared poses and metadata/config
   (0x1a7488 under core+0x2e0 lock) and returns one. No PersistSaveMapInfo here. */

int MapFlowSaveGridState(void *core,int native_flag)

{
  undefined4 uVar1;
  void *pvVar2;
  int iVar3;
  int *piVar4;
  undefined4 uVar5;
  int *piVar6;
  double *local_48;
  _Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *local_44;
  undefined2 local_40;
  undefined2 local_3e;
  float local_3c;
  double local_38;
  double local_30;
  double local_28;
  int local_1c;
  
  piVar6 = *(int **)(_LAB_00067318 + 0x6714e + _LAB_0006731c);
  local_1c = *piVar6;
  if (native_flag == 1) {
    FUN_001a6414();
    iVar3 = FUN_001a5f90();
    if (iVar3 == 0) {
      DataMemoryBarrier(0x1b);
      DataMemoryBarrier(0x1b);
      if (*(char *)((int)core + 0x271) == '\0') {
        uVar1 = FUN_0014d1dc();
        pvVar2 = (void *)FUN_001a6414();
        iVar3 = MapFlowGridSave(pvVar2,1);
        if (iVar3 != 0) {
          pvVar2 = (void *)FUN_001a6414();
          iVar3 = GetSharedCurrentMapFlag();
          MapFlowSetStoredFlag(pvVar2,iVar3);
          goto LAB_000671a8;
        }
        goto LAB_00067172;
      }
    }
    FUN_001a6414();
    iVar3 = _LAB_00067320;
    uVar1 = FUN_001a5f90();
    DataMemoryBarrier(0x1b);
    DataMemoryBarrier(0x1b);
    _rrlogmP(3,4,1,0x72c,_LAB_00067328 + 0x672b0,iVar3 + 0x67296,_LAB_00067324 + 0x672a2,uVar1,
             *(char *)((int)core + 0x271) != '\0');
    iVar3 = 0;
  }
  else {
    uVar1 = FUN_0014d1dc();
    pvVar2 = (void *)FUN_001a6414();
    iVar3 = MapFlowGridSave(pvVar2,native_flag);
    if (iVar3 != 0) {
      if (1 < native_flag) {
        pvVar2 = (void *)FUN_001a6414();
        MapFlowSetStoredFlag(pvVar2,native_flag);
        DataMemoryBarrier(0x1b);
        DataMemoryBarrier(0x1b);
        if (*(char *)((int)core + 0x270) == '\0') {
          uVar5 = FUN_001a6414();
          FUN_001a6e20(uVar5,0);
        }
      }
LAB_000671a8:
      piVar4 = (int *)FUN_00205d68();
      (**(code **)(*piVar4 + 0x28))(&local_38,piVar4);
      local_40 = (undefined2)(longlong)local_38;
      local_3e = (undefined2)(longlong)local_30;
      local_3c = (float)local_28;
      SetSharedRobotPosi((SharedPosi *)&local_40);
      uVar5 = FUN_001cb230();
      FUN_001cb9b0(&local_48,uVar5);
      if (local_48 != (double *)0x0) {
        local_3c = (float)local_48[2];
        local_40 = (undefined2)(longlong)*local_48;
        local_3e = (undefined2)(longlong)local_48[1];
        FUN_001cb230();
        uVar5 = FUN_001cb9fc();
        SetSharedDockPosi((SharedPosi *)&local_40,uVar5);
      }
      FUN_0014d258(uVar1);
      if (local_44 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
        std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(local_44);
      }
      FUN_00186640((int)core + 0x2e0);
      uVar1 = FUN_001a6414();
      DataMemoryBarrier(0x1b);
      DataMemoryBarrier(0x1b);
      FUN_001a7488(uVar1,native_flag,*(char *)((int)core + 0x270) != '\0');
      FUN_00186b10((int)core + 0x2e0);
      iVar3 = 1;
      goto LAB_00067174;
    }
LAB_00067172:
    iVar3 = 0;
  }
LAB_00067174:
  if (local_1c == *piVar6) {
    return iVar3;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

