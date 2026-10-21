/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x00046e9c
 */

/* Builds application result response from saved request ID and supplied result string; queued map
   success and recovery no-op branches pass literal ok at 0xf3398. Sending this reply does not
   itself check native storage. */

void MapFlowReplyOk(undefined4 param_1,int param_2,char *param_3)

{
  char *pcVar1;
  undefined4 *puVar2;
  undefined4 extraout_r1;
  char *pcVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 local_64;
  void *local_60;
  void *local_5c;
  undefined1 *local_58;
  undefined1 *local_54;
  undefined4 local_50;
  undefined4 *local_4c;
  undefined4 local_48;
  void *local_44;
  void *local_40;
  int local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined1 local_30;
  int local_2c;
  
  local_64 = 0;
  local_2c = __stack_chk_guard;
  local_60 = (void *)0x0;
  local_5c = (void *)0x0;
  local_58 = (undefined1 *)0x0;
  local_54 = (undefined1 *)0x0;
  local_48 = 0;
  local_44 = (void *)0x0;
  local_40 = (void *)0x0;
  local_3c = 0;
  local_38 = 0;
  local_30 = 0;
  local_50 = 0x100;
  local_34 = 0x100;
  local_4c = &local_64;
  FUN_0006f990(&local_4c);
  pcVar1 = DAT_001208f8;
  pcVar3 = DAT_001208f8;
  if (*DAT_001208f8 == '\0') {
    iVar7 = 0;
  }
  else {
    do {
      pcVar3 = pcVar3 + 1;
    } while (*pcVar3 != '\0');
    iVar7 = (int)pcVar3 - (int)DAT_001208f8;
  }
  FUN_0006f888(&local_4c,5);
  FUN_000704e8(&local_4c,pcVar1,iVar7);
  uVar6 = *(undefined4 *)(param_2 + 8);
  uVar8 = *(undefined4 *)(param_2 + 0xc);
  FUN_0006f888(&local_4c,6);
  FUN_0003d11c(&local_4c,extraout_r1,uVar6,uVar8);
  pcVar1 = DAT_001208fc;
  pcVar3 = DAT_001208fc;
  if (*DAT_001208fc == '\0') {
    iVar7 = 0;
  }
  else {
    do {
      pcVar3 = pcVar3 + 1;
    } while (*pcVar3 != '\0');
    iVar7 = (int)pcVar3 - (int)DAT_001208fc;
  }
  FUN_0006f888(&local_4c,5);
  FUN_000704e8(&local_4c,pcVar1,iVar7);
  FUN_0006f904(&local_4c);
  pcVar3 = param_3;
  if (*param_3 == '\0') {
    iVar7 = 0;
  }
  else {
    do {
      pcVar3 = pcVar3 + 1;
    } while (*pcVar3 != '\0');
    iVar7 = (int)pcVar3 - (int)param_3;
  }
  FUN_0006f888(&local_4c,5);
  FUN_000704e8(&local_4c,param_3,iVar7);
  puVar2 = local_4c;
  local_3c = local_3c + -8;
  puVar5 = (undefined1 *)local_4c[3];
  puVar4 = puVar5 + 1;
  if ((undefined1 *)local_4c[4] <= puVar4) {
    FUN_0002bad8(local_4c,1);
    puVar5 = (undefined1 *)puVar2[3];
    puVar4 = puVar5 + 1;
  }
  puVar2[3] = puVar4;
  puVar2 = local_4c;
  *puVar5 = 0x5d;
  local_3c = local_3c + -8;
  puVar5 = (undefined1 *)local_4c[3];
  puVar4 = puVar5 + 1;
  if ((undefined1 *)local_4c[4] <= puVar4) {
    FUN_0002bad8(local_4c,1);
    puVar5 = (undefined1 *)puVar2[3];
    puVar4 = puVar5 + 1;
  }
  puVar2[3] = puVar4;
  *puVar5 = 0x7d;
  puVar4 = local_58 + 1;
  if (local_54 <= puVar4) {
    FUN_0002bad8(&local_64,1);
    puVar4 = local_58 + 1;
  }
  *local_58 = 0;
  local_58 = puVar4 + -1;
  FUN_0003f70c(param_1,param_2,local_5c);
  free(local_40);
  operator_delete(local_44);
  free(local_5c);
  operator_delete(local_60);
  if (local_2c != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}

