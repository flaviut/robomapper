/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x00068428
 */

/* WARNING: Heritage AFTER dead removal. Example location: s1 : 0x0006886c */
/* WARNING: Restarted to delay deadcode elimination for space: register */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grid load (0x68544) must succeed before flag reconciliation. Signed native_flag > 1 updates
   shared catalog current flag at 0x68556; flag 1 uses manager byte +0x22 and saved flag +0x28
   (0x687aa..0x687fa). Then per-map/config updates precede PersistLoadMapInfo at 0x685ba.
   Persistence failure returns zero without undoing grid/current flag/config changes. Success
   restores poses and downstream state before common unlock/resume cleanup. Locks core+0x2c8 and
   manager mutex from 0x170850 when threading enabled; no cross-file transaction or disk-write
   completion implied. Third argument is a mode, not a reconstructed C++ field. */

int MapFlowLoadSLAMMap(void *core,int native_flag,uint load_mode)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  undefined4 uVar4;
  pthread_mutex_t *__mutex;
  int iVar5;
  undefined4 uVar6;
  int *piVar7;
  void *pvVar8;
  uint uVar9;
  int *piVar10;
  int iVar11;
  _Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *p_Var12;
  _Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *p_Var13;
  int iVar14;
  allocator aaStack_9c [3];
  undefined1 local_99;
  int local_98;
  int local_94;
  undefined4 local_90;
  _Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *local_8c;
  short local_88;
  short local_86;
  float local_84;
  short local_80;
  short local_7e;
  float local_7c;
  undefined4 local_78;
  _Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *local_74;
  double local_70;
  double local_68;
  double local_60;
  undefined4 local_58;
  _Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *local_54;
  void *local_3c [2];
  code *local_34;
  int local_30;
  int local_2c;
  
  iVar14 = DAT_000689e0 + 0x6843e;
  piVar10 = *(int **)(iVar14 + DAT_000689e4);
  local_2c = *piVar10;
  _rrlogmP(3,6,1,0x79d);
  local_99 = 1;
  FUN_001703f8(&local_58);
  local_70 = (double)CONCAT44(local_70._4_4_,0x83);
  FUN_00067ad0(local_58,&local_70,&local_99);
  if (local_54 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(local_54);
  }
  iVar11 = *(int *)(iVar14 + DAT_000689f4);
  if ((iVar11 != 0) &&
     (iVar3 = pthread_mutex_lock((pthread_mutex_t *)((int)core + 0x2c8)), iVar3 != 0)) {
                    /* WARNING: Subroutine does not return */
    std::__throw_system_error(iVar3);
  }
  uVar4 = FUN_0013f578();
  iVar3 = FUN_0013cf78();
  __mutex = (pthread_mutex_t *)FUN_00170850();
  if ((iVar11 != 0) && (iVar5 = pthread_mutex_lock(__mutex), iVar5 != 0)) {
                    /* WARNING: Subroutine does not return */
    std::__throw_system_error(iVar5);
  }
  DataMemoryBarrier(0x1b);
  cVar1 = __mutex[1].__size[0];
  DataMemoryBarrier(0x1b);
  if (cVar1 != '\0') {
    FUN_0017055c(__mutex);
  }
  if (iVar3 != 0) {
    FUN_0013ce58(uVar4);
  }
  FUN_00120784(*(undefined4 *)((int)core + 0x46c));
  FUN_0015c568(*(undefined4 *)((int)core + 0x470));
  FUN_0013f5e0(uVar4,0,load_mode);
  if (load_mode == 0) {
    uVar6 = FUN_00170850();
    FUN_001708b8(uVar6,1);
  }
  else {
    uVar6 = FUN_00170850();
    FUN_001708b8(uVar6,0);
  }
  piVar7 = (int *)FUN_00205d68();
  (**(code **)(*piVar7 + 0x10))();
  pvVar8 = (void *)FUN_001a6414();
  iVar5 = MapFlowGridLoad(pvVar8,native_flag);
  if (iVar5 == 0) {
    iVar14 = 0;
    goto LAB_00068712;
  }
  if (native_flag < 2) {
    if (native_flag == 1) {
      pvVar8 = (void *)FUN_001a6414();
      iVar5 = MapFlowGetStoredFlag(pvVar8);
      pvVar8 = (void *)FUN_001a6414();
      uVar9 = MapFlowHasStoredFlag(pvVar8);
      GetSharedCurrentMapFlag();
      _rrlogmP(3,7,1,0x7ca);
      if (uVar9 == 0) {
        pvVar8 = (void *)FUN_001a6414();
        iVar5 = GetSharedCurrentMapFlag();
        MapFlowSetStoredFlag(pvVar8,iVar5);
      }
      else {
        SetSharedCurrentMapFlag(iVar5);
      }
    }
  }
  else {
    SetSharedCurrentMapFlag(native_flag);
  }
  uVar6 = FUN_001a6414();
  iVar5 = FUN_001a7624(uVar6,native_flag);
  if (iVar5 == 0) {
    MapFlowClearMapState(core);
  }
  else {
    FUN_00066348(core);
  }
  _rrlogmP(3,6,1,0x7e1);
  FUN_001a69e0(uVar6,0);
  FUN_001a771c(uVar6,native_flag,1);
  FUN_001a71b4(&local_94,native_flag);
  iVar5 = PersistLoadMapInfo(local_94,native_flag);
  iVar14 = *(int *)(iVar14 + DAT_00068a04);
  if (local_94 + -0xc != iVar14) {
    FUN_00065d38(local_94 + -0xc,&local_58);
  }
  _rrlogmP(3,7,1,0x7e9);
  if (iVar5 == 0) {
    _rrlogmP(3,3,1,0x7ec);
    iVar14 = 0;
    goto LAB_00068712;
  }
  if (native_flag == 1) {
    MapFlowClearRecoverLast(core);
  }
  FUN_00192e68();
  FUN_001918d0();
  p_Var13 = *(_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> **)((int)core + 0x4d4);
  iVar5 = *(int *)((int)core + 0x4d0);
  if (p_Var13 == (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    if (iVar5 != 0) goto LAB_0006863e;
  }
  else {
    if (iVar11 == 0) {
      *(int *)(p_Var13 + 4) = *(int *)(p_Var13 + 4) + 1;
    }
    else {
      p_Var12 = p_Var13 + 4;
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(p_Var12);
        bVar2 = (bool)hasExclusiveAccess(p_Var12);
      } while (!bVar2);
      *(int *)p_Var12 = *(int *)p_Var12 + 1;
      DataMemoryBarrier(0x1b);
    }
    if (iVar5 != 0) {
LAB_0006863e:
      FUN_0018c90c();
      if (p_Var13 == (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) goto LAB_0006864a;
    }
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var13);
  }
LAB_0006864a:
  std::string::string((string *)&local_98,(char *)(DAT_00068a14 + 0x68654),aaStack_9c);
  local_30 = DAT_00068a18 + 0x6866e;
  local_34 = (code *)(DAT_00068a1c + 0x68670);
  local_3c[0] = core;
  FUN_0018ce7c(&local_78,2,(string *)&local_98,local_3c);
  p_Var13 = *(_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> **)((int)core + 0x4d4);
  *(undefined4 *)((int)core + 0x4d0) = local_78;
  *(_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> **)((int)core + 0x4d4) = local_74;
  local_74 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0;
  local_78 = 0;
  if ((p_Var13 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) &&
     (std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var13),
     local_74 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0)) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(local_74);
  }
  if (local_34 != (code *)0x0) {
    (*local_34)(local_3c,local_3c,3);
  }
  if (local_98 + -0xc != iVar14) {
    FUN_00065d38(local_98 + -0xc,&local_58);
  }
  FUN_0018c6f4(*(undefined4 *)((int)core + 0x4d0));
  iVar14 = GetSharedDockPosiValid();
  if (iVar14 != 0) {
    piVar7 = (int *)FUN_001cb230();
    GetSharedDockPosi();
    uVar6 = GetSharedDockType();
    local_70 = (double)(longlong)(int)local_88;
    local_68 = (double)(longlong)(int)local_86;
    for (local_60 = (double)local_84; local_60 < DAT_000689c8; local_60 = local_60 + DAT_000689d0) {
    }
    for (; DAT_000689d8 <= local_60; local_60 = local_60 - DAT_000689d0) {
    }
    FUN_001cb8f8(&local_58,&local_70);
    FUN_001cbef8(piVar7,&local_58,&local_70,uVar6);
    (**(code **)(*piVar7 + 0x70))(piVar7,1);
  }
  iVar14 = GetSharedRobotPosiValid();
  if (iVar14 != 0) {
    FUN_00120790(*(undefined4 *)((int)core + 0x46c));
    GetSharedRobotPosi();
    piVar7 = (int *)FUN_00205d68();
    (**(code **)(*piVar7 + 0x2c))
              (SUB84((double)(longlong)(int)local_80,0),
               (int)((ulonglong)(double)(longlong)(int)local_80 >> 0x20),
               SUB84((double)(longlong)(int)local_7e,0),
               (int)((ulonglong)(double)(longlong)(int)local_7e >> 0x20),SUB84((double)local_7c,0));
  }
  FUN_0014d1dc();
  FUN_0014c818();
  if (load_mode != 0) {
    FUN_0014d1dc();
    FUN_00148984();
  }
  FUN_000667a0(core);
  iVar14 = 1;
LAB_00068712:
  FUN_00120790(*(undefined4 *)((int)core + 0x46c));
  FUN_0015c55c(*(undefined4 *)((int)core + 0x470));
  if (iVar3 == 0) {
    piVar7 = (int *)FUN_00205d68();
    piVar7 = (int *)(**(code **)(*piVar7 + 0x30))();
    (**(code **)(*piVar7 + 0x24))();
  }
  else {
    FUN_0013edf0(uVar4);
  }
  if (cVar1 != '\0') {
    FUN_00170614(__mutex,*(undefined4 *)((int)__mutex + 0x28));
  }
  if (iVar11 != 0) {
    pthread_mutex_unlock(__mutex);
  }
  local_99 = 0;
  FUN_001703f8(&local_90);
  local_58 = 0x83;
  FUN_00067ad0(local_90,&local_58,&local_99);
  if (local_8c != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(local_8c);
  }
  if (iVar11 != 0) {
    pthread_mutex_unlock((pthread_mutex_t *)((int)core + 0x2c8));
  }
  if (local_2c == *piVar10) {
    return iVar14;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

