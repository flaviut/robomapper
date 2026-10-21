/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x001a60c4
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Calls SLAM interface virtual slot +0x6c with native flag; returns one iff result code equals
   zero. This wrapper alone does not establish disk durability. */

int MapFlowGridSave(void *manager,int native_flag)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  allocator aaStack_24 [4];
  string asStack_20 [4];
  int local_1c;
  
  iVar4 = DAT_001a61d8 + 0x1a60d2;
  piVar5 = *(int **)(iVar4 + DAT_001a61dc);
  local_1c = *piVar5;
  piVar1 = (int *)FUN_00205d68(manager);
  uVar2 = (**(code **)(*piVar1 + 0x6c))(piVar1,native_flag);
  if (uVar2 < 4) {
    if ((-1 < *(int *)(DAT_001a61f0 + 0x1a6126) << 0x1f) &&
       (iVar3 = __cxa_guard_acquire(), iVar3 != 0)) {
      std::string::string(asStack_20,(char *)(DAT_001a61f8 + 0x1a6148),aaStack_24);
      FUN_0016b510(DAT_001a61fc + 0x1a6156,asStack_20,0x2c);
      __cxa_guard_release(DAT_001a6200 + 0x1a615e);
                    /* WARNING: Subroutine does not return */
      __aeabi_atexit(DAT_001a620c + 0x1a616e,*(undefined4 *)(iVar4 + DAT_001a6204),
                     DAT_001a6208 + 0x1a616a);
    }
    iVar4 = *(int *)(*(int *)(DAT_001a61f4 + 0x1a6130) + uVar2 * 4);
  }
  else {
    iVar4 = DAT_001a61e0 + 0x1a60ee;
  }
  _rrlogmP(3,7,1,0x94,DAT_001a61ec + 0x1a6102,DAT_001a61e8 + 0x1a60fe,DAT_001a61e4 + 0x1a60fa,iVar4)
  ;
  if (local_1c == *piVar5) {
    return (uint)(uVar2 == 0);
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

