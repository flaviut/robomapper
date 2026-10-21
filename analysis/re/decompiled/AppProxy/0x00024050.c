/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x00024050
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Invokes one queued callable, removes it and updates timer. Returns callable result (0 for
   synchronous terminal step, 1 for wait). No generic disk completion wait. */

int MapFlowRunNextStep(void *pending)

{
  int iVar1;
  time_t tVar2;
  int iVar3;
  code *pcVar4;
  undefined4 uVar5;
  undefined4 local_7c;
  undefined1 auStack_78 [8];
  code *local_70;
  code *local_6c;
  undefined1 auStack_68 [84];
  int local_14;
  
  local_14 = __stack_chk_guard;
  if (*(int *)((int)pending + 0x60) == *(int *)((int)pending + 0x70)) {
    iVar1 = 0;
  }
  else {
    FUN_0002470c(auStack_78);
    uVar5 = *(undefined4 *)pending;
    memcpy(auStack_68,(void *)((int)pending + 8),0x50);
    local_7c = uVar5;
    if (local_70 == (code *)0x0) {
      std::__throw_bad_function_call();
      if (local_70 != (code *)0x0) {
        (*local_70)(auStack_78,auStack_78,3);
      }
                    /* WARNING: Subroutine does not return */
      __cxa_end_cleanup();
    }
    iVar1 = (*local_6c)(auStack_78,auStack_68,&local_7c);
    iVar3 = *(int *)((int)pending + 0x60);
    pcVar4 = *(code **)(iVar3 + 8);
    if (iVar3 == *(int *)((int)pending + 0x68) + -0x10) {
      if (pcVar4 != (code *)0x0) {
        (*pcVar4)(iVar3,iVar3,3);
      }
      operator_delete(*(void **)((int)pending + 100));
      iVar3 = *(int *)((int)pending + 0x6c);
      *(int *)((int)pending + 0x6c) = iVar3 + 4;
      iVar3 = *(int *)(iVar3 + 4);
      *(int *)((int)pending + 0x68) = iVar3 + 0x200;
      *(int *)((int)pending + 100) = iVar3;
      *(int *)((int)pending + 0x60) = iVar3;
    }
    else {
      if (pcVar4 != (code *)0x0) {
        (*pcVar4)(iVar3,iVar3,3);
        iVar3 = *(int *)((int)pending + 0x60);
      }
      *(int *)((int)pending + 0x60) = iVar3 + 0x10;
    }
    tVar2 = time((time_t *)0x0);
    *(time_t *)((int)pending + 8) = tVar2;
    if (local_70 != (code *)0x0) {
      (*local_70)(auStack_78,auStack_78,3);
    }
  }
  if (local_14 == __stack_chk_guard) {
    return iVar1;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

