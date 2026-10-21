/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x0003c194
 */

void FUN_0003c194(undefined4 param_1,int param_2,byte *param_3)

{
  undefined4 uVar1;
  int iVar2;
  byte *pbVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint local_44;
  void *local_40;
  void **local_3c [2];
  code *local_34;
  code *local_30;
  int local_2c;
  
  uVar4 = 0;
  local_2c = __stack_chk_guard;
  local_44 = 0;
  uVar1 = FUN_0003c148();
  iVar2 = GetRoomIdMapping(uVar1,&local_44);
  local_40 = operator_new__(0x380);
  local_30 = (code *)0x371f1;
  local_34 = (code *)0x36fc9;
  local_3c[0] = &local_40;
  if (local_44 == 0) {
    iVar5 = 0;
  }
  else {
    iVar5 = 0;
    uVar7 = local_44;
    do {
      if (param_2 == 0) {
LAB_0003c21c:
        iVar6 = iVar5 * 0x1c;
        iVar5 = iVar5 + 1;
        *(undefined4 *)((int)local_40 + iVar6) = 0;
        *(undefined4 *)((int)local_40 + iVar6 + 4) = 0;
        *(undefined4 *)((int)local_40 + iVar6 + 8) = 0;
        *(undefined4 *)((int)local_40 + iVar6 + 0xc) = 0;
        *(undefined4 *)((int)local_40 + iVar6 + 0x10) = 0;
        *(undefined4 *)((int)local_40 + iVar6 + 0x14) = 0;
        __strcpy_chk((void *)((int)local_40 + iVar6),iVar2,0x18);
        *(undefined4 *)((int)local_40 + iVar6 + 0x18) = *(undefined4 *)(iVar2 + 0x18);
        uVar7 = local_44;
      }
      else if (*(uint *)(iVar2 + 0x18) != (uint)*param_3) {
        pbVar3 = param_3;
        do {
          pbVar3 = pbVar3 + 1;
          if (param_3 + param_2 == pbVar3) goto LAB_0003c21c;
        } while ((uint)*pbVar3 != *(uint *)(iVar2 + 0x18));
      }
      uVar4 = uVar4 + 1;
      iVar2 = iVar2 + 0x1c;
    } while (uVar4 < uVar7);
  }
  uVar1 = FUN_0003c148(param_1);
  SetRoomIdMapping(uVar1,local_40,iVar5);
  if ((local_34 != (code *)0x0) && ((*local_30)(local_3c), local_34 != (code *)0x0)) {
    (*local_34)(local_3c,local_3c,3);
  }
  if (local_2c == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

