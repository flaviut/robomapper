/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x0006adfc
 */

void FUN_0006adfc(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  void *__dest;
  int iVar1;
  uint uVar2;
  uint __n;
  void *local_44;
  int local_40;
  undefined4 local_3c;
  void *local_38;
  void *local_34;
  int local_30;
  int local_2c;
  
  local_2c = __stack_chk_guard;
  FUN_0003c194();
  local_44 = (void *)0x0;
  local_40 = 0;
  local_3c = 0;
  local_38 = (void *)GetSharedCurrentMapFlag();
  FUN_00071c64(&local_44,&local_38);
  local_38 = (void *)0x0;
  uVar2 = local_40 - (int)local_44;
  local_34 = (void *)0x0;
  local_30 = 0;
  if ((int)uVar2 >> 2 == 0) {
    iVar1 = 0;
    __dest = (void *)0x0;
    __n = uVar2;
  }
  else {
    if (0x3fffffff < (uint)((int)uVar2 >> 2)) {
                    /* WARNING: Subroutine does not return */
      std::__throw_bad_alloc();
    }
    __dest = operator_new(uVar2);
    __n = local_40 - (int)local_44;
    iVar1 = (int)__n >> 2;
  }
  local_30 = uVar2 + (int)__dest;
  local_38 = __dest;
  if (iVar1 != 0) {
    local_34 = __dest;
    memmove(__dest,local_44,__n);
  }
  local_34 = (void *)(__n + (int)__dest);
  FUN_00069300(param_1,param_2,param_3,&local_38);
  if (local_38 != (void *)0x0) {
    operator_delete(local_38);
  }
  FUN_0003b760(param_1,param_2,param_3);
  FUN_0003b834(param_1,param_2,param_3);
  FUN_0003bac4(param_1,param_2,param_3);
  if (local_44 != (void *)0x0) {
    operator_delete(local_44);
  }
  if (local_2c != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}

