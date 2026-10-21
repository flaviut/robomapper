/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x0012ca58
 */

undefined4 FUN_0012ca58(int param_1,undefined4 *param_2,int *param_3,undefined4 param_4)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  
  iVar3 = *param_3;
  if ((((*(int *)(param_1 + 4) <= iVar3) && (iVar3 <= *(int *)(param_1 + 0xc))) &&
      (iVar4 = param_3[1], *(int *)(param_1 + 8) <= iVar4)) &&
     (((iVar4 <= *(int *)(param_1 + 0x10) &&
       (uVar2 = (*(int *)(param_1 + 0x30) * (iVar4 - *(int *)(param_1 + 0x24)) + iVar3) -
                *(int *)(param_1 + 0x20),
       -1 < ((int)(uint)*(byte *)(*(int *)(param_1 + 0x38) + ((int)uVar2 >> 3)) >> (uVar2 & 7)) <<
            0x1f)) &&
      (uVar5 = param_4,
      uVar2 = FUN_00148b94(**(undefined4 **)(param_1 + 0x40),iVar3,iVar4,
                           *(undefined4 **)(param_1 + 0x40),param_4),
      (1 << (uVar2 & 0x1f) & *(uint *)(**(int **)(param_1 + 0x44) + (uVar2 >> 5) * 4)) == 0)))) {
    if ((*(byte *)(*(int *)(param_1 + 0x48) + uVar2 + 0x10) & 0x3f) == 0) {
      iVar3 = FUN_00148b94(**(undefined4 **)(param_1 + 0x40),*param_2,param_2[1],
                           *(undefined4 **)(param_1 + 0x40),uVar5);
      bVar1 = *(byte *)(iVar3 + *(int *)(param_1 + 0x48) + 0x10);
      if ((bVar1 & 0x3f) == 0) {
        return 0;
      }
      *(byte *)(uVar2 + *(int *)(param_1 + 0x48) + 0x10) = bVar1 & 0x3f | 0x40;
      **(undefined1 **)(param_1 + 0x4c) = 1;
    }
    FUN_001250ac(param_1 + 0x1c,*param_3,param_3[1]);
    FUN_0012ba88(param_4,param_3);
  }
  return 0;
}

