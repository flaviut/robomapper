/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x0012dda4
 */

void FUN_0012dda4(int param_1,int *param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  byte bVar7;
  int *piVar8;
  int *piVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  undefined1 *puVar16;
  int local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  int *local_4c;
  undefined4 local_48;
  int local_44;
  int local_40;
  int *local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  
  piVar9 = *(int **)(DAT_0012e118 + 0x12ddb2 + DAT_0012e11c);
  local_2c = *piVar9;
  if (((*(int *)(param_1 + 4) <= *param_2) && (*param_2 <= *(int *)(param_1 + 0xc))) &&
     (iVar2 = FUN_00124fe4(param_1 + 4,param_2 + 1), iVar2 != 0)) {
    local_6c = 0;
    local_68 = 0;
    local_64 = 0;
    local_60 = 0;
    local_54 = 0;
    local_50 = 0;
    local_4c = (int *)0x0;
    local_48 = 0;
    local_44 = 0;
    local_40 = 0;
    local_3c = (int *)0x0;
    local_38 = 0;
    local_34 = 0;
    local_30 = 0;
    FUN_000e66f8(&local_54,0);
    FUN_0012ba24(&local_54,param_2);
    while (((int)local_3c - local_38 >> 3) + ((local_30 - local_40 >> 2) + -1) * 0x40 +
           (local_44 - (int)local_4c >> 3) != 0) {
      local_6c = *local_4c;
      local_68 = local_4c[1];
      if (local_4c == (int *)(local_44 + -8)) {
        FUN_00124ffc(&local_54);
      }
      else {
        local_4c = local_4c + 2;
      }
      for (iVar2 = -param_3; iVar12 = -param_3, iVar2 <= param_3; iVar2 = iVar2 + 1) {
        do {
          while (iVar2 == 0 && iVar12 == 0) {
LAB_0012de60:
            iVar12 = iVar12 + 1;
            if (param_3 < iVar12) goto LAB_0012df10;
          }
          local_64 = local_6c + iVar2;
          local_60 = local_68 + iVar12;
          if (((local_64 < *(int *)(param_1 + 4)) || (*(int *)(param_1 + 0xc) < local_64)) ||
             ((local_60 < *(int *)(param_1 + 8) || (*(int *)(param_1 + 0x10) < local_60))))
          goto LAB_0012de60;
          iVar3 = (**(code **)(*(int *)**(undefined4 **)(param_1 + 0x40) + 0x18))
                            ((int *)**(undefined4 **)(param_1 + 0x40),&local_64,&local_60);
          if (iVar3 == 0) goto LAB_0012de60;
          iVar3 = FUN_00148b94(**(undefined4 **)(param_1 + 0x44),local_64,local_60);
          if (*(char *)(*(int *)(param_1 + 0x48) + iVar3 + 0x10) == '\0') {
            iVar5 = (**(code **)(*(int *)**(undefined4 **)(param_1 + 0x40) + 0x18))
                              ((int *)**(undefined4 **)(param_1 + 0x40),&local_6c,&local_68);
            iVar6 = *(int *)(param_1 + 0x48);
            if (iVar5 == -1) {
              iVar15 = *(int *)(iVar6 + 8);
              iVar11 = *(int *)(&DAT_00100014 + iVar6);
              iVar5 = *(int *)(&DAT_00100010 + iVar6);
              iVar14 = (iVar15 * (local_68 - iVar11) + local_6c) - iVar5;
              if (((iVar14 < 0) || (*(int *)(iVar6 + 0x10003c) <= iVar14)) ||
                 (bVar1 = *(byte *)(iVar14 + iVar6 + 0x10), bVar7 = bVar1 & 0x3f,
                 (bVar1 & 0x3f) == 0)) goto LAB_0012df5a;
            }
            else {
              iVar15 = *(int *)(iVar6 + 8);
              iVar11 = *(int *)(&DAT_00100014 + iVar6);
              iVar5 = *(int *)(&DAT_00100010 + iVar6);
LAB_0012df5a:
              iVar14 = 1;
              while( true ) {
                iVar13 = 1;
                while( true ) {
                  iVar5 = (iVar15 * ((iVar13 + local_60) - iVar11) + local_64 + iVar14) - iVar5;
                  if ((((-1 < iVar5) && (iVar5 < *(int *)(iVar6 + 0x10003c))) &&
                      (bVar1 = *(byte *)(iVar5 + iVar6 + 0x10), bVar7 = bVar1 & 0x3f,
                      (bVar1 & 0x3f) != 0)) &&
                     (local_74 = local_64 + iVar14, local_70 = iVar13 + local_60,
                     iVar5 = (**(code **)(*(int *)**(undefined4 **)(param_1 + 0x40) + 0x18))
                                       ((int *)**(undefined4 **)(param_1 + 0x40),&local_74,&local_70
                                       ), iVar5 == -1)) {
                    iVar6 = *(int *)(param_1 + 0x48);
                    goto LAB_0012e06e;
                  }
                  iVar13 = iVar13 + -1;
                  if (iVar13 == -2) break;
                  iVar6 = *(int *)(param_1 + 0x48);
                  iVar15 = *(int *)(iVar6 + 8);
                  iVar11 = *(int *)(&DAT_00100014 + iVar6);
                  iVar5 = *(int *)(&DAT_00100010 + iVar6);
                }
                iVar14 = iVar14 + -1;
                if (iVar14 == -2) break;
                iVar6 = *(int *)(param_1 + 0x48);
                iVar15 = *(int *)(iVar6 + 8);
                iVar11 = *(int *)(&DAT_00100014 + iVar6);
                iVar5 = *(int *)(&DAT_00100010 + iVar6);
              }
              iVar5 = *(int *)(param_1 + 0x4c);
              memset(*(void **)(iVar5 + 0x38),0,
                     (*(int *)(iVar5 + 0x34) * *(int *)(iVar5 + 0x30) >> 3) + 1);
              puVar16 = *(undefined1 **)(param_1 + 0x54);
              piVar8 = *(int **)(param_1 + 0x50);
              *piVar8 = local_64;
              piVar8[1] = local_60;
              *puVar16 = 0;
              local_5c = 0;
              local_58 = 0;
              FUN_0012d884(*(undefined4 *)(param_1 + 0x4c),&local_5c);
              iVar6 = *(int *)(param_1 + 0x48);
              bVar7 = **(byte **)(param_1 + 0x54);
              if ((bVar7 == 0) &&
                 (((iVar5 = (*(int *)(iVar6 + 8) * (local_68 - *(int *)(&DAT_00100014 + iVar6)) +
                            local_6c) - *(int *)(&DAT_00100010 + iVar6), iVar5 < 0 ||
                   (*(int *)(iVar6 + 0x10003c) <= iVar5)) ||
                  (bVar1 = *(byte *)(iVar5 + iVar6 + 0x10), bVar7 = bVar1 & 0x3f,
                  (bVar1 & 0x3f) == 0)))) {
                _rrlogmP(3,7,1,0x296,DAT_0012e128 + 0x12e0a2,DAT_0012e124 + 0x12e098,
                         DAT_0012e120 + 0x12e094,local_64,local_60);
                goto LAB_0012debe;
              }
            }
LAB_0012e06e:
            *(byte *)(iVar3 + iVar6 + 0x10) = bVar7 | 0x40;
          }
LAB_0012debe:
          uVar10 = (*(int *)(param_1 + 0x30) * (local_60 - *(int *)(param_1 + 0x24)) + local_64) -
                   *(int *)(param_1 + 0x20);
          uVar4 = uVar10 & 7;
          iVar3 = (int)uVar10 >> 3;
          bVar7 = *(byte *)(*(int *)(param_1 + 0x38) + iVar3);
          if (((int)(uint)bVar7 >> uVar4 & 1U) != 0) goto LAB_0012de60;
          *(byte *)(*(int *)(param_1 + 0x38) + iVar3) = bVar7 | (byte)(1 << uVar4);
          if (local_3c == (int *)(local_34 + -8)) {
            FUN_000e67f8(&local_54,&local_64);
            goto LAB_0012de60;
          }
          if (local_3c != (int *)0x0) {
            *local_3c = local_64;
            local_3c[1] = local_60;
          }
          iVar12 = iVar12 + 1;
          local_3c = local_3c + 2;
        } while (iVar12 <= param_3);
LAB_0012df10:
      }
    }
    FUN_000d0198(&local_54);
  }
  if (local_2c == *piVar9) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(0);
}

