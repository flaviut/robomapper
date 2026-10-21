/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x00024450
 */

/* WARNING: Removing unreachable block (ram,0x000245a8) */
/* WARNING: Removing unreachable block (ram,0x000245b4) */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* ABI-level register words: r1 unused/alignment; request key in r2:r3. If matching pending series
   exists, runs next queued callback 0x24050. A callback returning 1 pauses only when more queued
   callbacks remain. Otherwise invokes success callback series+0x38 with succeed text, erases
   pending series under mutex+0x4c, returns 1. Unknown request returns 0. No load/save/write
   completion independent of result messages. */

int MapFlowAdvanceSeries(void *series,uint reserved_r1,uint request_lo,uint request_hi)

{
  bool bVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  undefined4 uVar6;
  uint local_90;
  uint uStack_8c;
  undefined1 auStack_84 [4];
  undefined4 *local_80;
  int local_7c;
  int local_78;
  undefined4 local_74;
  undefined1 auStack_70 [84];
  int local_1c;
  
  local_1c = __stack_chk_guard;
  local_90 = request_lo;
  uStack_8c = request_hi;
  iVar3 = FUN_0002473c(series,&local_90);
  uVar4 = 0;
  if (iVar3 != 0) {
    local_80 = (undefined4 *)FUN_00024c58(series,&local_90);
    local_80 = (undefined4 *)*local_80;
    if (local_80[0x1c] != local_80[0x18]) {
      uVar4 = MapFlowRunNextStep(local_80);
      if (local_80[0x18] == local_80[0x1c]) {
        uVar4 = 0;
      }
      else {
        uVar4 = uVar4 & 1;
      }
      if (uVar4 != 0) goto LAB_0002449a;
    }
    std::string::string((string *)&local_7c,"succeed",(allocator *)&local_74);
    puVar2 = local_80;
    uVar6 = *local_80;
    std::string::string((string *)&local_78,(string *)&local_7c);
    memcpy(auStack_70,puVar2 + 2,0x50);
    local_74 = uVar6;
    if (*(int *)((int)series + 0x34) == 0) {
      std::__throw_bad_function_call();
      if ((undefined1 *)(local_78 + -0xc) != std::string::_Rep::_S_empty_rep_storage) {
        FUN_00019518((undefined1 *)(local_78 + -0xc),auStack_84);
      }
      if ((undefined1 *)(local_7c + -0xc) != std::string::_Rep::_S_empty_rep_storage) {
        FUN_00019518((undefined1 *)(local_7c + -0xc),auStack_84);
      }
                    /* WARNING: Subroutine does not return */
      __cxa_end_cleanup();
    }
    (**(code **)((int)series + 0x38))((int)series + 0x2c,auStack_70,&local_74,&local_78);
    if ((allocator *)(local_78 + -0xc) != (allocator *)std::string::_Rep::_S_empty_rep_storage) {
      piVar5 = (int *)(local_78 + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar5);
        iVar3 = *piVar5;
        bVar1 = (bool)hasExclusiveAccess(piVar5);
      } while (!bVar1);
      *piVar5 = iVar3 + -1;
      DataMemoryBarrier(0x1b);
      if (iVar3 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_78 + -0xc));
      }
    }
    pthread_mutex_lock((pthread_mutex_t *)((int)series + 0x4c));
    FUN_00024424(series,&local_90);
    pthread_mutex_unlock((pthread_mutex_t *)((int)series + 0x4c));
    FUN_00024924(&local_80);
    FUN_00026228(0x51,DAT_000245f4,2,6,"#9069`%d",*(undefined4 *)((int)series + 0xc));
    if ((allocator *)(local_7c + -0xc) != (allocator *)std::string::_Rep::_S_empty_rep_storage) {
      piVar5 = (int *)(local_7c + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar5);
        iVar3 = *piVar5;
        bVar1 = (bool)hasExclusiveAccess(piVar5);
      } while (!bVar1);
      *piVar5 = iVar3 + -1;
      DataMemoryBarrier(0x1b);
      if (iVar3 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_7c + -0xc));
      }
    }
    uVar4 = 1;
  }
LAB_0002449a:
  if (local_1c != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar4;
}

