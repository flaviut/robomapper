/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x0020c3d8
 */

/* WARNING: Heritage AFTER dead removal. Example location: s1 : 0x0020c430 */
/* WARNING: Restarted to delay deadcode elimination for space: register */
/* Warmup/local-relocation state callback: if relocation did not succeed and state+0x321 or +0x322
   is set, marks +0x324 and calls SetNeededToRecoverLastMap(core) at 0x20c500; successful relocation
   clears map/recovery state. Original ABI has register/stack decompiler uncertainties, so signature
   intentionally unchanged. */

void FUN_0020c3d8(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 int param_5)

{
  undefined1 uVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  float fVar5;
  int local_58;
  _Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *local_54;
  undefined4 local_50;
  _Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *p_Stack_4c;
  undefined4 local_48;
  undefined4 local_40;
  undefined1 auStack_34 [8];
  code *local_2c;
  int local_24;
  
  piVar3 = *(int **)(DAT_0020c60c + 0x20c3ea + DAT_0020c610);
  local_24 = *piVar3;
  FUN_001cb9b0(&local_58,*(undefined4 *)(param_5 + 0x374));
  if (*(char *)(param_5 + 0x330) == '\0') {
    uVar4 = *(undefined4 *)(DAT_0020c61c + 0x20c470);
LAB_0020c462:
    fVar5 = (float)(longlong)*(int *)(DAT_0020c620 + 0x20c472) / DAT_0020c608;
  }
  else {
    if (local_58 == 0) {
      uVar4 = *(undefined4 *)(DAT_0020c63c + 0x20c5a6);
    }
    else {
      FUN_00120790(*(undefined4 *)(param_5 + 0x370));
      FUN_00169ea8(&local_50,local_58);
      (**(code **)(**(int **)(param_5 + 0x1b8) + 0x2c))(local_50,param_2,local_48,param_4,local_40);
      uVar4 = *(undefined4 *)(DAT_0020c614 + 0x20c450);
      if (*(char *)(param_5 + 0x330) == '\0') {
        uVar4 = *(undefined4 *)(DAT_0020c614 + 0x20c44c);
        goto LAB_0020c462;
      }
    }
    fVar5 = (float)(longlong)*(int *)(DAT_0020c618 + 0x20c456) / DAT_0020c608;
  }
  _rrlogmP(3,7,1,0x3bf);
  uVar1 = FUN_0013fb80(fVar5,param_2,uVar4,*(undefined4 *)(param_5 + 0x364));
  *(undefined1 *)(param_5 + 0x32d) = uVar1;
  iVar2 = FUN_002096ac(param_5);
  if (iVar2 == 0) {
    if (*(char *)(param_5 + 0x32d) == '\0') {
      if (*(char *)(param_5 + 0x321) == '\0') {
        if (*(char *)(param_5 + 0x322) == '\0') {
          FUN_00067a84(*(undefined4 *)(param_5 + 0x368));
          if (*(char *)(param_5 + 0x31b) == '\0') {
            FUN_0020b308(param_5);
            MapFlowClearMapState(*(void **)(param_5 + 0x368));
          }
          else {
            FUN_0020b308(param_5);
            MapFlowClearMapState(*(void **)(param_5 + 0x368));
            FUN_00209728(param_5,0x34);
          }
          goto LAB_0020c504;
        }
      }
      *(undefined1 *)(param_5 + 0x324) = 1;
      FUN_0020b308(param_5);
      MapFlowSetRecoverLast(*(void **)(param_5 + 0x368));
    }
    else {
      _rrlogmP(3,7,1,0x3df);
      *(undefined1 *)(param_5 + 0x321) = 0;
      *(undefined1 *)(param_5 + 0x322) = 0;
      MapFlowClearMapState(*(void **)(param_5 + 0x368));
      FUN_00120790(*(undefined4 *)(param_5 + 0x370));
    }
  }
LAB_0020c504:
  local_2c = (code *)0x0;
  local_50 = 0;
  p_Stack_4c = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0;
  FUN_0020b694(param_5 + 0x1e0,7,0,auStack_34);
  if (p_Stack_4c != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Stack_4c);
  }
  if (local_2c != (code *)0x0) {
    (*local_2c)(auStack_34,auStack_34,3);
  }
  if (local_54 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
    std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(local_54);
  }
  if (local_24 == *piVar3) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

