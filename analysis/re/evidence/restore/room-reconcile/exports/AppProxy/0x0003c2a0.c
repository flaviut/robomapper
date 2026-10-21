/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x0003c2a0
 */

void FUN_0003c2a0(undefined4 param_1,int *param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  byte *pbVar8;
  void *local_40;
  void **local_3c [2];
  code *local_34;
  code *local_30;
  int local_2c;
  
  local_2c = __stack_chk_guard;
  local_40 = operator_new__(0x380);
  iVar7 = *param_2;
  local_30 = (code *)0x37225;
  local_3c[0] = &local_40;
  local_34 = (code *)0x36fed;
  if (iVar7 == param_2[1]) {
    iVar6 = 0;
  }
  else {
    iVar6 = 0;
    pbVar8 = (byte *)(param_3 + -1);
    iVar4 = iVar7;
    do {
      iVar3 = iVar4 - iVar7;
      *(undefined4 *)((int)local_40 + iVar3) = 0;
      iVar5 = iVar4 + 0x1c;
      iVar6 = iVar6 + 1;
      *(undefined4 *)((int)local_40 + iVar3 + 4) = 0;
      *(undefined4 *)((int)local_40 + iVar3 + 8) = 0;
      *(undefined4 *)((int)local_40 + iVar3 + 0xc) = 0;
      *(undefined4 *)((int)local_40 + iVar3 + 0x10) = 0;
      *(undefined4 *)((int)local_40 + iVar3 + 0x14) = 0;
      __strcpy_chk((int)local_40 + iVar3,iVar4,0x18);
      iVar2 = param_2[1];
      pbVar8 = pbVar8 + 1;
      *(uint *)((int)local_40 + iVar3 + 0x18) = (uint)*pbVar8;
      iVar4 = iVar5;
    } while (iVar2 != iVar5);
  }
  uVar1 = FUN_0003c148(param_1);
  SetRoomIdMapping(uVar1,local_40,iVar6);
  if (local_34 != (code *)0x0) {
    (*local_30)(local_3c);
    if (local_34 != (code *)0x0) {
      (*local_34)(local_3c,local_3c,3);
    }
  }
  if (local_2c == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

