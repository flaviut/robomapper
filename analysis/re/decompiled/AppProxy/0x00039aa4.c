/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x00039aa4
 */

/* Builds 0x02033204 IPC message, payload length 16: original request key words, native flag, zero.
   Sends via 0x37b78. Cross-process RoboController bridge is outside pinned lane inputs. */

void MapFlowSendLoad(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                    undefined4 param_5)

{
  undefined4 local_68 [2];
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  int local_1c;
  
  local_1c = __stack_chk_guard;
  memset(local_68,0,0x4c);
  local_68[0] = 0x2033204;
  local_60 = 0x10;
  uStack_54 = param_5;
  uStack_50 = 0;
  local_5c = param_3;
  uStack_58 = param_4;
  FUN_00037b78(param_1,local_68,1);
  if (local_1c == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

