/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x0012e714
 */

void FUN_0012e714(int param_1,int *param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int *piVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int local_64;
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  undefined4 local_50;
  int *local_4c;
  int *local_48;
  int *local_44;
  int local_40;
  int *local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  
  piVar7 = *(int **)(DAT_0012e954 + 0x12e722 + DAT_0012e958);
  local_2c = *piVar7;
  if (((*(int *)(param_1 + 4) <= *param_2) && (*param_2 <= *(int *)(param_1 + 0xc))) &&
     (iVar2 = FUN_00124fe4(param_1 + 4,param_2 + 1), iVar2 != 0)) {
    local_64 = 0;
    local_60 = 0;
    local_5c = 0;
    local_58 = 0;
    local_54 = 0;
    local_50 = 0;
    local_4c = (int *)0x0;
    local_48 = (int *)0x0;
    local_44 = (int *)0x0;
    local_40 = 0;
    local_3c = (int *)0x0;
    local_38 = 0;
    local_34 = 0;
    local_30 = 0;
    FUN_000e66f8(&local_54,0);
    FUN_0012ba24(&local_54,param_2);
    while (((int)local_3c - local_38 >> 3) + ((local_30 - local_40 >> 2) + -1) * 0x40 +
           ((int)local_44 - (int)local_4c >> 3) != 0) {
      local_64 = *local_4c;
      local_60 = local_4c[1];
      if (local_4c == local_44 + -2) {
        operator_delete(local_48);
        local_4c = *(int **)(local_40 + 4);
        local_44 = local_4c + 0x80;
        local_48 = local_4c;
        local_40 = local_40 + 4;
      }
      else {
        local_4c = local_4c + 2;
      }
      iVar2 = -param_3;
      if (iVar2 <= param_3) {
        iVar9 = iVar2;
        iVar10 = iVar2;
        do {
          if (iVar9 != 0 || iVar10 != 0) {
            local_5c = local_64 + iVar10;
            local_58 = local_60 + iVar9;
            if (((*(int *)(param_1 + 4) <= local_5c) && (local_5c <= *(int *)(param_1 + 0xc))) &&
               ((*(int *)(param_1 + 8) <= local_58 && (local_58 <= *(int *)(param_1 + 0x10))))) {
              if (local_64 < **(int **)(param_1 + 0x40)) {
                **(int **)(param_1 + 0x40) = local_64;
              }
              if (local_60 < **(int **)(param_1 + 0x44)) {
                **(int **)(param_1 + 0x44) = local_60;
              }
              if (**(int **)(param_1 + 0x48) < local_64) {
                **(int **)(param_1 + 0x48) = local_64;
              }
              if (**(int **)(param_1 + 0x4c) < local_60) {
                **(int **)(param_1 + 0x4c) = local_60;
              }
              iVar3 = (**(code **)(*(int *)**(undefined4 **)(param_1 + 0x50) + 0x18))
                                ((int *)**(undefined4 **)(param_1 + 0x50),&local_5c,&local_58);
              if ((iVar3 == 1) ||
                 (iVar4 = FUN_00148b94(**(undefined4 **)(param_1 + 0x54),local_5c,local_58),
                 *(char *)(*(int *)(param_1 + 0x58) + iVar4 + 0x10) != '\0')) {
LAB_0012e866:
                uVar8 = (*(int *)(param_1 + 0x30) * (local_58 - *(int *)(param_1 + 0x24)) + local_5c
                        ) - *(int *)(param_1 + 0x20);
                uVar5 = uVar8 & 7;
                iVar3 = (int)uVar8 >> 3;
                bVar1 = *(byte *)(*(int *)(param_1 + 0x38) + iVar3);
                if (((int)(uint)bVar1 >> uVar5 & 1U) == 0) {
                  *(byte *)(*(int *)(param_1 + 0x38) + iVar3) = bVar1 | (byte)(1 << uVar5);
                  if (local_3c == (int *)(local_34 + -8)) {
                    FUN_000e67f8(&local_54,&local_5c);
                  }
                  else {
                    if (local_3c != (int *)0x0) {
                      *local_3c = local_5c;
                      local_3c[1] = local_58;
                    }
                    local_3c = local_3c + 2;
                  }
                }
              }
              else {
                iVar6 = (**(code **)(*(int *)**(undefined4 **)(param_1 + 0x50) + 0x18))
                                  ((int *)**(undefined4 **)(param_1 + 0x50),&local_64,&local_60);
                if (iVar3 == -1 && iVar6 != 1) {
                  iVar3 = FUN_00148b94(**(undefined4 **)(param_1 + 0x54),local_64,local_60);
                  bVar1 = *(byte *)(iVar3 + *(int *)(param_1 + 0x58) + 0x10);
                  if ((bVar1 & 0x3f) != 0) {
                    *(byte *)(iVar4 + *(int *)(param_1 + 0x58) + 0x10) = bVar1 & 0x3f | 0x40;
                    **(undefined1 **)(param_1 + 0x5c) = 1;
                    goto LAB_0012e866;
                  }
                }
              }
            }
          }
          iVar9 = iVar9 + 1;
        } while ((iVar9 <= param_3) || (iVar10 = iVar10 + 1, iVar9 = iVar2, iVar10 <= param_3));
      }
    }
    FUN_000d0198(&local_54);
  }
  if (local_2c == *piVar7) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(0);
}

