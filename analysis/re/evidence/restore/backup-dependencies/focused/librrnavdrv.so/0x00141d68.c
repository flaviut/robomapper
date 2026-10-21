/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x00141d68
 */

void FUN_00141d68(void)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  int *piVar4;
  char *__name;
  allocator aaStack_1c [4];
  allocator aaStack_18 [4];
  int local_14;
  
  iVar3 = DAT_00141df4 + 0x141d74;
  piVar4 = *(int **)(iVar3 + DAT_00141df8);
  local_14 = *piVar4;
  if ((-1 < *(int *)(DAT_00141dfc + 0x141d7a) << 0x1f) &&
     (iVar1 = __cxa_guard_acquire(), iVar1 != 0)) {
    __name = (char *)(DAT_00141e04 + 0x141da0);
    pcVar2 = getenv(__name);
    if (pcVar2 == (char *)0x0) {
      std::string::string((string *)(DAT_00141e20 + 0x141dde),(char *)(DAT_00141e1c + 0x141ddc),
                          aaStack_18);
    }
    else {
      pcVar2 = getenv(__name);
      std::string::string((string *)(DAT_00141e08 + 0x141db6),pcVar2,aaStack_1c);
    }
    __cxa_guard_release(DAT_00141e0c + 0x141dbe);
                    /* WARNING: Subroutine does not return */
    __aeabi_atexit(DAT_00141e18 + 0x141dce,*(undefined4 *)(iVar3 + DAT_00141e10),
                   DAT_00141e14 + 0x141dca);
  }
  if (local_14 == *piVar4) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(DAT_00141e00 + 0x141d8e);
}

