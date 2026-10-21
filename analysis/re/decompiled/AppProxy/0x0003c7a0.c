/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x0003c7a0
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* After successful load step: timestamp mutex, ClearCleanRouting, SetSharedCurrentMapFlag(requested
   native flag), then save request 0x02033212 with vector [1,requested native flag] via 0x3c6bc.
   Returns 1 (wait). No atomic transaction between flags is asserted. */

int MapFlowRecoverSaveStep(void *capture,void *context,int *native_flag)

{
  time_t tVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  undefined4 uVar9;
  undefined4 *local_38;
  undefined4 *local_34;
  undefined4 *local_30;
  undefined4 local_2c;
  int local_28;
  int local_24;
  
  iVar8 = *native_flag;
  uVar5 = *(undefined4 *)((int)context + 0x10);
  uVar6 = *(undefined4 *)((int)context + 0x14);
  local_24 = __stack_chk_guard;
  FUN_00026228(0x5520,DAT_0003c8cc,2,6,"#10593`%d",iVar8);
  pthread_mutex_lock((pthread_mutex_t *)(*(int *)capture + 0xf54));
  iVar4 = *(int *)capture;
  tVar1 = time((time_t *)0x0);
  iVar3 = *(int *)capture;
  *(time_t *)(iVar4 + 0xf6c) = tVar1;
  pthread_mutex_unlock((pthread_mutex_t *)(iVar3 + 0xf54));
  FUN_00026228(0x5528,DAT_0003c8cc,2,6,"#10595");
  ClearCleanRouting();
  FUN_00026228(0x552a,DAT_0003c8cc,2,6,"#10596");
  SetSharedCurrentMapFlag(iVar8);
  local_2c = 1;
  local_28 = iVar8;
  puVar2 = operator_new(8);
  uVar9 = *(undefined4 *)capture;
  local_38 = (undefined4 *)0x0;
  local_34 = (undefined4 *)0x0;
  local_30 = (undefined4 *)0x0;
  *puVar2 = local_2c;
  puVar2[1] = local_28;
  local_38 = operator_new(8);
  uVar7 = puVar2[1];
  *local_38 = *puVar2;
  local_34 = local_38 + 2;
  local_38[1] = uVar7;
  local_30 = local_34;
  MapFlowSendSaveSet(uVar9,local_38,uVar5,uVar6,iVar8,&local_38);
  if (local_38 != (undefined4 *)0x0) {
    operator_delete(local_38);
  }
  FUN_0008c46c(*(undefined4 *)(*(int *)capture + 0x4e8));
  operator_delete(puVar2);
  if (local_24 == __stack_chk_guard) {
    return 1;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

