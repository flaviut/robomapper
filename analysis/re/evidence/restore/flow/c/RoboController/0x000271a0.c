/* Decompiled C, NOT recovered source; need not compile.
 * Binary: RoboController
 * SHA256: bf1d43313dd8beaa0c802f9ae4c666138b3bb518f69b4909a746285f3f3947cf
 * Function VA: 0x000271a0
 */

int FUN_000271a0(undefined4 *param_1,undefined4 *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  undefined *puVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  switch(*(undefined1 *)((int)param_1 + 2)) {
  case 2:
    iVar4 = FUN_00023768();
    puVar3 = &DAT_0006d5bc;
    break;
  case 3:
    iVar4 = FUN_00024458();
    puVar3 = DAT_00027270;
    break;
  case 4:
    iVar4 = FUN_00022e14();
    puVar3 = DAT_00027274;
    break;
  case 5:
    iVar4 = FUN_0002593c();
    puVar3 = DAT_00027278;
    break;
  default:
    puVar3 = (undefined *)0x0;
    goto LAB_0002725c;
  case 7:
    iVar4 = FUN_0002572c();
    puVar3 = DAT_0002727c;
    break;
  case 8:
    iVar4 = FUN_00025c48();
    puVar3 = DAT_00027280;
    break;
  case 9:
    iVar4 = FUN_00025c84();
    puVar3 = DAT_00027284;
    break;
  case 10:
    iVar4 = FUN_00025b1c();
    puVar3 = DAT_00027268;
  }
  if (iVar4 == -0x7ffffffe) {
LAB_0002725c:
    iVar4 = FUN_00027050(puVar3,param_2,param_1);
  }
  uVar1 = DAT_0006a690;
  if (-1 < iVar4) {
    uVar5 = *param_2;
    uVar6 = *param_1;
    uVar2 = FUN_000208c8(uVar5);
    FUN_00020728(0xb22,DAT_0002726c,uVar1 & 0x2000,"#12384`%x`%p`%s",uVar6,uVar5,uVar2);
  }
  return iVar4;
}

