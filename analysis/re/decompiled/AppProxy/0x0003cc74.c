/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x0003cc74
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* First series step: clears/gates map activity via 0x3cc18, sends 0x01033107 via 0x39dec, then
   sends load request 0x02033204 with original request words and native flag via 0x39aa4. Returns 1
   (wait for result), not load success. */

int MapFlowLoadStep(void *capture,void *context,int *native_flag)

{
  undefined4 uVar1;
  undefined4 extraout_r1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  uVar1 = DAT_0003cce0;
  iVar2 = *native_flag;
  uVar3 = *(undefined4 *)((int)context + 0x10);
  uVar4 = *(undefined4 *)((int)context + 0x14);
  FUN_00026228(0x564b,DAT_0003cce0,2,6,"#10629`%d",iVar2);
  FUN_0003cc18(*(undefined4 *)capture);
  FUN_00039dec(*(undefined4 *)capture);
  MapFlowSendLoad(*(undefined4 *)capture,extraout_r1,uVar3,uVar4,iVar2);
  FUN_00026228(0x5650,uVar1,1,7,"#10630`%d",iVar2);
  FUN_00039a38(*(undefined4 *)capture);
  return 1;
}

