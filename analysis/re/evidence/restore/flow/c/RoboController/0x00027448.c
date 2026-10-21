/* Decompiled C, NOT recovered source; need not compile.
 * Binary: RoboController
 * SHA256: bf1d43313dd8beaa0c802f9ae4c666138b3bb518f69b4909a746285f3f3947cf
 * Function VA: 0x00027448
 */

int FUN_00027448(undefined4 param_1,int *param_2,int *param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  param_3[2] = 0;
  memset(param_3 + 3,0,0x40);
  iVar1 = (**(code **)(*param_2 + 0xc))(param_2);
  if (iVar1 == 0) {
    (**(code **)(*param_2 + 8))(param_2);
    iVar1 = FUN_000268e8();
    *param_3 = iVar1;
    if (iVar1 != 0) {
      return 0;
    }
    uVar3 = (**(code **)(*param_2 + 8))(param_2);
    iVar1 = FUN_000272fc(DAT_00027638,uVar3,param_3,param_2);
    if (iVar1 == -0x80000000) {
      __printf_chk(1,"%s,%d: ",DAT_00027618,0x107a);
      uVar3 = (**(code **)(*param_2 + 8))(param_2);
      uVar2 = (**(code **)(*param_2 + 8))(param_2);
      __printf_chk(1,"<FATAL> Unrecognized EventID %d(0x%x)",uVar3,uVar2);
      _IO_putc(10,stdout);
    }
    if (*param_3 != 0) {
      return 0;
    }
    __printf_chk(1,"%s,%d: ",DAT_00027618,0x107d);
    __printf_chk(1,"%s failed\n","Packet->MessageId != 0");
    goto LAB_00027500;
  }
  switch(param_1) {
  case 2:
    iVar1 = FUN_00026288(param_2,param_3);
    uVar3 = DAT_0002761c;
    break;
  case 3:
    iVar1 = FUN_00025ee4(param_2,param_3);
    uVar3 = DAT_00027630;
    break;
  case 4:
    iVar1 = FUN_000266ac(param_2,param_3);
    uVar3 = DAT_00027634;
    break;
  case 5:
    iVar1 = FUN_00025dcc(param_2,param_3);
    uVar3 = DAT_00027620;
    break;
  case 6:
    iVar1 = FUN_00025d28(param_2,param_3);
    uVar3 = DAT_00027624;
    break;
  case 7:
    iVar1 = FUN_00025e38(param_2,param_3);
    uVar3 = DAT_00027628;
    break;
  case 8:
    iVar1 = FUN_00025d80(param_2,param_3);
    uVar3 = DAT_0002762c;
    break;
  case 9:
    iVar1 = FUN_00026898(param_2,param_3);
    uVar3 = DAT_00027614;
    break;
  default:
    uVar3 = 0;
    goto LAB_000274ac;
  }
  if (iVar1 != -0x7ffffffe) {
    return iVar1;
  }
LAB_000274ac:
  uVar2 = (**(code **)(*param_2 + 8))(param_2);
  iVar1 = FUN_000272fc(uVar3,uVar2,param_3,param_2,param_4);
  if (iVar1 != -0x80000000) {
    return iVar1;
  }
  __printf_chk(1,"%s,%d: ",DAT_00027618,0x10b5);
  uVar3 = (**(code **)(*param_2 + 8))(param_2);
  uVar2 = (**(code **)(*param_2 + 8))(param_2);
  __printf_chk(1,"<FATAL> Unrecognized EventID %d(0x%x)",uVar3,uVar2);
LAB_00027500:
  _IO_putc(10,stdout);
  return -0x80000000;
}

