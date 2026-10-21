/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x0012c860
 */

void FUN_0012c860(int param_1,undefined4 param_2,int *param_3,undefined4 param_4)

{
  bool bVar1;
  _Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *p_Var2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int *piVar9;
  _Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *p_Var10;
  int iVar11;
  int iVar12;
  int *piVar13;
  undefined4 uVar14;
  _Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *local_34;
  _Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *local_30;
  int local_2c;
  
  iVar12 = DAT_0012ca44 + 0x12c872;
  iVar4 = *param_3;
  piVar13 = *(int **)(iVar12 + DAT_0012ca48);
  local_2c = *piVar13;
  if ((((*(int *)(param_1 + 4) <= iVar4) && (iVar4 <= *(int *)(param_1 + 0xc))) &&
      (iVar6 = param_3[1], *(int *)(param_1 + 8) <= iVar6)) &&
     ((iVar6 <= *(int *)(param_1 + 0x10) &&
      (uVar8 = (*(int *)(param_1 + 0x30) * (iVar6 - *(int *)(param_1 + 0x24)) + iVar4) -
               *(int *)(param_1 + 0x20),
      -1 < ((int)(uint)*(byte *)(*(int *)(param_1 + 0x38) + ((int)uVar8 >> 3)) >> (uVar8 & 7)) <<
           0x1f)))) {
    FUN_001250ac(param_1 + 0x1c);
    iVar4 = *param_3;
    if (((*(int *)(param_1 + 4) <= iVar4) &&
        ((iVar4 <= *(int *)(param_1 + 0xc) &&
         (iVar6 = FUN_00124fe4(param_1 + 4,param_3 + 1), iVar6 != 0)))) &&
       ((uVar8 = FUN_00148b94(**(undefined4 **)(param_1 + 0x40),iVar4,param_3[1]), (int)uVar8 < 0 ||
        ((*(int *)(*(int *)(param_1 + 0x44) + 0x10003c) <= (int)uVar8 ||
         ((*(byte *)(*(int *)(param_1 + 0x44) + uVar8 + 0x10) & 0x3f) == 0)))))) {
      **(undefined1 **)(param_1 + 0x48) = 0;
      iVar4 = *param_3;
      iVar6 = param_3[1];
      piVar9 = *(int **)(param_1 + 0x50);
      uVar14 = *(undefined4 *)(param_1 + 0x54);
      **(undefined1 **)(param_1 + 0x4c) = 0;
      *piVar9 = iVar4;
      piVar9[1] = iVar6;
      FUN_00128cb8(&local_34,*(undefined4 *)(param_1 + 0x58));
      FUN_001b3b5c(uVar14,&local_34);
      if (local_30 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
        std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(local_30);
      }
      p_Var10 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)(uint)**(byte **)(param_1 + 0x48);
      if (p_Var10 == (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
        uVar14 = *(undefined4 *)(param_1 + 0x54);
        piVar9 = *(int **)(param_1 + 0x5c);
        local_34 = p_Var10;
        local_30 = p_Var10;
        p_Var2 = operator_new(0x20);
        iVar6 = DAT_0012ca50;
        iVar4 = DAT_0012ca4c;
        iVar3 = *piVar9;
        iVar5 = piVar9[1];
        iVar7 = piVar9[2];
        iVar11 = piVar9[3];
        *(int *)(p_Var2 + 8) = 1;
        *(int *)p_Var2 = iVar4 + 0x12c9b0;
        *(int *)(p_Var2 + 4) = 1;
        *(int *)(p_Var2 + 0xc) = DAT_0012ca54 + 0x12c9be;
        *(int *)(p_Var2 + 0x10) = iVar3;
        *(int *)(p_Var2 + 0x14) = iVar5;
        *(int *)(p_Var2 + 0x18) = iVar7;
        *(int *)(p_Var2 + 0x1c) = iVar11;
        local_34 = (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)
                   FUN_001249c0(p_Var2,*(undefined4 *)(iVar12 + iVar6));
        p_Var10 = local_30;
        bVar1 = local_30 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0;
        local_30 = p_Var2;
        if (bVar1) {
          std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(p_Var10);
        }
        FUN_001b3b5c(uVar14,&local_34);
        if (local_30 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
          std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(local_30);
        }
      }
      else {
        if (**(char **)(param_1 + 0x4c) == '\0') {
          **(byte **)(param_1 + 0x48) = 0;
          uVar14 = *(undefined4 *)(param_1 + 100);
          FUN_00128cb8(&local_34,*(undefined4 *)(param_1 + 0x58));
          FUN_001b3b5c(uVar14,&local_34);
          if (local_30 != (_Sp_counted_base<(__gnu_cxx::_Lock_policy)2> *)0x0) {
            std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release(local_30);
          }
          if (**(char **)(param_1 + 0x4c) != '\0') {
            *(uint *)(**(int **)(param_1 + 0x60) + (uVar8 >> 5) * 4) =
                 *(uint *)(**(int **)(param_1 + 0x60) + (uVar8 >> 5) * 4) | 1 << (uVar8 & 0x1f);
          }
        }
        else {
          *(uint *)(**(int **)(param_1 + 0x60) + (uVar8 >> 5) * 4) =
               1 << (uVar8 & 0x1f) | *(uint *)(**(int **)(param_1 + 0x60) + (uVar8 >> 5) * 4);
        }
        FUN_0012ba88(param_4,param_3);
      }
    }
  }
  if (local_2c == *piVar13) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(0);
}

