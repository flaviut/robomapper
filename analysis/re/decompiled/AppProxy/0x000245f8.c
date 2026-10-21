/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x000245f8
 */

/* WARNING: Removing unreachable block (ram,0x000246da) */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Looks up request key, invokes configured error callback series+0x28 with error string, erases
   pending operation under mutex+0x4c and returns handled=1. Unknown key returns 0. ABI-level word
   signature uses unused/alignment r1 and request words in r2:r3; original C++ types are not
   reconstructed. */

int MapFlowFailSeries(void *series,uint reserved_r1,uint request_lo,uint request_hi,
                     void *error_string)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined4 *__src;
  undefined4 uVar5;
  uint local_88;
  uint uStack_84;
  undefined1 auStack_80 [4];
  undefined4 *local_7c;
  int local_78;
  undefined4 local_74;
  undefined1 auStack_70 [84];
  int local_1c;
  
  local_1c = __stack_chk_guard;
  local_88 = request_lo;
  uStack_84 = request_hi;
  iVar2 = FUN_0002473c(series,&local_88);
  iVar4 = 0;
  if (iVar2 != 0) {
    piVar3 = (int *)FUN_00024c58(series,&local_88);
    local_7c = (undefined4 *)*piVar3;
    __src = local_7c + 2;
    uVar5 = *local_7c;
    std::string::string((string *)&local_78,error_string);
    memcpy(auStack_70,__src,0x50);
    local_74 = uVar5;
    if (*(int *)((int)series + 0x24) == 0) {
      std::__throw_bad_function_call();
      if ((undefined1 *)(local_78 + -0xc) != std::string::_Rep::_S_empty_rep_storage) {
        FUN_00019518((undefined1 *)(local_78 + -0xc),auStack_80);
      }
                    /* WARNING: Subroutine does not return */
      __cxa_end_cleanup();
    }
    (**(code **)((int)series + 0x28))((int)series + 0x1c,auStack_70,&local_74,&local_78);
    if ((allocator *)(local_78 + -0xc) != (allocator *)std::string::_Rep::_S_empty_rep_storage) {
      piVar3 = (int *)(local_78 + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar3);
        iVar4 = *piVar3;
        bVar1 = (bool)hasExclusiveAccess(piVar3);
      } while (!bVar1);
      *piVar3 = iVar4 + -1;
      DataMemoryBarrier(0x1b);
      if (iVar4 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_78 + -0xc));
      }
    }
    pthread_mutex_lock((pthread_mutex_t *)((int)series + 0x4c));
    FUN_00024424(series,&local_88);
    pthread_mutex_unlock((pthread_mutex_t *)((int)series + 0x4c));
    FUN_00024924(&local_7c);
    FUN_00026228(100,DAT_00024708,2,6,"#9070`%d",*(undefined4 *)((int)series + 0xc));
    iVar4 = 1;
  }
  if (local_1c != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return iVar4;
}

