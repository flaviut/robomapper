/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x0004705c
 */

/* Configured success callback (installed at 0x64af2): copies saved request context, sends literal
   ok through 0x46e9c, then unlocks action via 0x3a714(proxy,0). Does not inspect writes or DB
   return codes. Failure callback Thumb 0x4afa9 is absent from baseline function inventory; see
   bounded instructions. */

void MapFlowSeriesSuccess(undefined4 *param_1,void *param_2,undefined4 param_3,int *param_4)

{
  int iVar1;
  undefined1 auStack_74 [4];
  undefined1 auStack_70 [8];
  undefined1 auStack_68 [76];
  int local_1c;
  
  local_1c = __stack_chk_guard;
  iVar1 = *param_4;
  *param_4 = DAT_000470dc;
  memcpy(auStack_70,param_2,0x50);
  MapFlowReplyOk(*param_1,auStack_68,&DAT_000f3398);
  FUN_0003a714(*param_1,0);
  if ((undefined1 *)(iVar1 + -0xc) != std::string::_Rep::_S_empty_rep_storage) {
    FUN_00037650((undefined1 *)(iVar1 + -0xc),auStack_74);
  }
  if (local_1c == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

