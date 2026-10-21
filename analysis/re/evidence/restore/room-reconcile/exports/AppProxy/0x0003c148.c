/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x0003c148
 */

void FUN_0003c148(undefined4 param_1)

{
  int iVar1;
  char acStack_54 [64];
  int local_14;
  
  local_14 = __stack_chk_guard;
  memset(acStack_54,0,0x40);
  FUN_0003bff4(param_1,acStack_54);
  iVar1 = strncmp(acStack_54,"miot",4);
  if (local_14 == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(iVar1 != 0);
}

