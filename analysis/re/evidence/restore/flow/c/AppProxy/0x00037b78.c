/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x00037b78
 */

void FUN_00037b78(undefined4 param_1,undefined4 *param_2,byte param_3,int param_4)

{
  undefined4 uVar1;
  byte local_64 [4];
  undefined4 local_60 [19];
  int local_14;
  
  local_14 = __stack_chk_guard;
  local_64[0] = local_64[0] & 0xfe | param_3 & 1;
  if ((param_4 != 0) && (*(char *)((int)param_2 + 3) == '\x01')) {
    memset(local_60,0,0x4c);
    local_60[0] = 0x1030029;
    SendPacket(local_60,local_64);
  }
  uVar1 = SendPacket(param_2,local_64);
  FUN_00026228(0x5f0,DAT_00037bf8,2,7,"#9274`%u`%d",*param_2,uVar1);
  if (local_14 == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar1);
}

