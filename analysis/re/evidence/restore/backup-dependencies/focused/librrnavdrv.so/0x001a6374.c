/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x001a6374
 */

int * FUN_001a6374(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar3 = DAT_001a63fc;
  param_1[2] = DAT_001a63f8 + 0x1a6386;
  iVar1 = DAT_001a6410;
  iVar5 = DAT_001a6400 + 0x1a6392;
  iVar2 = DAT_001a6404 + 0x1a639a;
  iVar4 = DAT_001a6408 + 0x1a639e;
  iVar6 = DAT_001a640c + 0x1a63a0;
  *param_1 = iVar3 + 0x1a6394;
  param_1[3] = iVar2;
  param_1[4] = iVar4;
  param_1[5] = iVar6;
  param_1[6] = iVar1 + 0x1a63a6;
  param_1[1] = iVar5;
  *(undefined1 *)((int)param_1 + 0x1d) = 0;
  *(undefined1 *)((int)param_1 + 0x1e) = 0;
  *(undefined1 *)((int)param_1 + 0x1f) = 0;
  *(undefined1 *)(param_1 + 8) = 0;
  *(undefined1 *)((int)param_1 + 0x21) = 0;
  *(undefined1 *)((int)param_1 + 0x22) = 0;
  param_1[0xb] = 0;
  param_1[10] = -1;
  param_1[0xc] = -1;
  FUN_00141e28(param_1 + 0xd,iVar5,2,0,param_4);
  FUN_001a6064(param_1);
  iVar3 = FUN_0026a4a0();
  *(bool *)(param_1 + 7) = iVar3 != 0;
  return param_1;
}

