/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x00141e28
 */

int FUN_00141e28(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  
  *(undefined4 *)(param_1 + 0x104) = 0;
  *(undefined4 *)(param_1 + 0x108) = 0;
  puVar1 = (undefined4 *)FUN_00141d68();
  FUN_00141600(param_1,param_2,*puVar1,param_3);
  return param_1;
}

