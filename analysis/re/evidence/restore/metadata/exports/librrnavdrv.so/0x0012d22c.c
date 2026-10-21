/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x0012d22c
 */

void FUN_0012d22c(int param_1,int *param_2,int *param_3,undefined4 param_4)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  byte bVar9;
  int local_30;
  int local_2c;
  
  iVar6 = *param_3;
  piVar7 = *(int **)(DAT_0012d3f0 + 0x12d23e + DAT_0012d3f4);
  local_2c = *piVar7;
  if ((((*(int *)(param_1 + 4) <= iVar6) && (iVar6 <= *(int *)(param_1 + 0xc))) &&
      (iVar8 = param_3[1], *(int *)(param_1 + 8) <= iVar8)) && (iVar8 <= *(int *)(param_1 + 0x10)))
  {
    uVar4 = (*(int *)(param_1 + 0x30) * (iVar8 - *(int *)(param_1 + 0x24)) + iVar6) -
            *(int *)(param_1 + 0x20);
    if ((-1 < ((int)(uint)*(byte *)(*(int *)(param_1 + 0x38) + ((int)uVar4 >> 3)) >> (uVar4 & 7)) <<
              0x1f) && (iVar2 = FUN_00124fe4(param_1 + 4,param_3 + 1), iVar2 != 0)) {
      iVar2 = *(int *)(param_1 + 0x40);
      iVar5 = (*(int *)(iVar2 + 8) * (iVar8 - *(int *)(&DAT_00100014 + iVar2)) + iVar6) -
              *(int *)(&DAT_00100010 + iVar2);
      if ((iVar5 < 0) ||
         ((*(int *)(iVar2 + 0x10003c) <= iVar5 || ((*(byte *)(iVar5 + iVar2 + 0x10) & 0x3f) == 0))))
      {
        iVar6 = FUN_00148b94(**(undefined4 **)(param_1 + 0x44),iVar6,iVar8);
        local_30 = *(int *)(*(int *)(*(int *)(param_1 + 0x48) + 8) + iVar6 * 4);
        if (local_30 < 1) goto LAB_0012d254;
        pbVar3 = (byte *)std::
                         map<int,unsigned_char,std::less<int>,std::allocator<std::pair<int_const,unsigned_char>>>
                         ::operator[](*(map<int,unsigned_char,std::less<int>,std::allocator<std::pair<int_const,unsigned_char>>>
                                        **)(param_1 + 0x4c),&local_30);
        bVar9 = *pbVar3;
        if (bVar9 == 0) {
          iVar2 = *(int *)(param_1 + 0x40);
          iVar8 = (*(int *)(iVar2 + 8) * (param_2[1] - *(int *)(&DAT_00100014 + iVar2)) + *param_2)
                  - *(int *)(&DAT_00100010 + iVar2);
          if (((iVar8 < 0) || (*(int *)(iVar2 + 0x10003c) <= iVar8)) ||
             (bVar1 = *(byte *)(iVar8 + iVar2 + 0x10), bVar9 = bVar1 & 0x3f, (bVar1 & 0x3f) == 0)) {
            _rrlogmP(3,6,1,0x1fb,DAT_0012d400 + 0x12d344,DAT_0012d3fc + 0x12d340,
                     DAT_0012d3f8 + 0x12d33e,*param_2,param_2[1]);
            goto LAB_0012d254;
          }
          pbVar3 = (byte *)std::
                           map<int,unsigned_char,std::less<int>,std::allocator<std::pair<int_const,unsigned_char>>>
                           ::operator[](*(map<int,unsigned_char,std::less<int>,std::allocator<std::pair<int_const,unsigned_char>>>
                                          **)(param_1 + 0x4c),&local_30);
          iVar2 = DAT_0012d404 + 0x12d392;
          iVar8 = DAT_0012d408 + 0x12d398;
          iVar5 = DAT_0012d40c + 0x12d39c;
          *pbVar3 = bVar9;
          _rrlogmP(3,6,1,0x1f8,iVar5,iVar8,iVar2,*param_3,param_3[1],*param_2,param_2[1],local_30,
                   bVar9);
        }
        iVar8 = FUN_00127804(*(undefined4 *)(param_1 + 0x40),*param_3,param_3[1]);
        if (iVar8 == 0) {
          bVar9 = bVar9 | 0x40;
        }
        *(byte *)(iVar6 + *(int *)(param_1 + 0x40) + 0x10) = bVar9;
        iVar6 = *param_3;
        iVar8 = param_3[1];
      }
      FUN_001250ac(param_1 + 0x1c,iVar6,iVar8);
      FUN_0012ba88(param_4,param_3);
    }
  }
LAB_0012d254:
  if (local_2c == *piVar7) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(0);
}

