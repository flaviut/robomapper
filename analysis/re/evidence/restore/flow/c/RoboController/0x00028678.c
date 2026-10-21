/* Decompiled C, NOT recovered source; need not compile.
 * Binary: RoboController
 * SHA256: bf1d43313dd8beaa0c802f9ae4c666138b3bb518f69b4909a746285f3f3947cf
 * Function VA: 0x00028678
 */

void FUN_00028678(undefined4 param_1,undefined4 param_2,int *param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  uint local_6c;
  undefined1 auStack_68 [64];
  undefined4 local_28;
  undefined4 local_24;
  int local_20;
  int local_1c;
  
  uVar1 = DAT_0006a690;
  local_24 = (**(code **)(*param_3 + 8))(param_3);
  local_28 = param_2;
  local_20 = param_4;
  FUN_00020728(0x7b1,DAT_000286c4,uVar1 & 0x2000,"#12451`%d`%d`%d");
  local_1c = __stack_chk_guard;
  iVar2 = FUN_00027448(param_2,param_3,auStack_68);
  if (iVar2 < 0) {
    __printf_chk(1,"%s,%d: ",DAT_00027714,0x10fb);
    piVar3 = __errno_location();
    __printf_chk(1,"return failed (%d)\n",*piVar3);
    _IO_putc(10,stdout);
  }
  else {
    local_6c = (uint)(param_4 != 0);
    iVar2 = SendPacket(auStack_68,&local_6c);
    uVar1 = DAT_0006a690;
    if (iVar2 < 1) {
      uVar4 = FUN_000208c8(param_3);
      iVar2 = -0x7ffffffd;
      FUN_00020728(0x1110,DAT_00027714,uVar1 & 0x4000,"#12389`%p`%s`%d",param_3,uVar4,param_2);
    }
    else {
      iVar2 = 0;
    }
  }
  if (local_1c != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(iVar2);
  }
  return;
}

