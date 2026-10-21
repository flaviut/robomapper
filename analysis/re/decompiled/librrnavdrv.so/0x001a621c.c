/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x001a621c
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Calls SLAM interface virtual slot +0x68 with native flag (0x1a6236), preserves result code,
   returns one iff result code equals zero. Unsigned result<4 selects logging text, not success.
   Target implementation is outside this annotation ownership. */

int MapFlowGridLoad(void *manager,int native_flag)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  allocator aaStack_24 [4];
  string asStack_20 [4];
  int local_1c;
  
  iVar4 = DAT_001a6330 + 0x1a622a;
  piVar5 = *(int **)(iVar4 + DAT_001a6334);
  local_1c = *piVar5;
  piVar1 = (int *)FUN_00205d68(manager);
  uVar2 = (**(code **)(*piVar1 + 0x68))(piVar1,native_flag);
  if (uVar2 < 4) {
    if ((-1 < *(int *)(DAT_001a6348 + 0x1a627e) << 0x1f) &&
       (iVar3 = __cxa_guard_acquire(), iVar3 != 0)) {
      std::string::string(asStack_20,(char *)(DAT_001a6350 + 0x1a62a0),aaStack_24);
      FUN_0016b510(DAT_001a6354 + 0x1a62ae,asStack_20,0x2c);
      __cxa_guard_release(DAT_001a6358 + 0x1a62b6);
                    /* WARNING: Subroutine does not return */
      __aeabi_atexit(DAT_001a6364 + 0x1a62c6,*(undefined4 *)(iVar4 + DAT_001a635c),
                     DAT_001a6360 + 0x1a62c2);
    }
    iVar4 = *(int *)(*(int *)(DAT_001a634c + 0x1a6288) + uVar2 * 4);
  }
  else {
    iVar4 = DAT_001a6338 + 0x1a6246;
  }
  _rrlogmP(3,7,1,0x9c,DAT_001a6344 + 0x1a625a,DAT_001a6340 + 0x1a6256,DAT_001a633c + 0x1a6252,iVar4)
  ;
  if (local_1c == *piVar5) {
    return (uint)(uVar2 == 0);
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

