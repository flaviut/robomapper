/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x00039b84
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* After accepted load-result advancement: updates proxy timestamp under mutex+0xf54; clears
   routing; sets shared current flag to request native flag; sends save request 0x02033203 with
   destination 1. Returns 1 (request wait), but ordinary load has no callback remaining, so 0x24450
   overrides it and sends ok immediately after this send, before the save result. Does not update
   bakmaps DB. */

int MapFlowSaveLastStep(void *capture,void *context,int *native_flag)

{
  undefined4 uVar1;
  time_t tVar2;
  undefined4 extraout_r1;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  
  uVar1 = DAT_00039c34;
  iVar6 = *native_flag;
  uVar4 = *(undefined4 *)((int)context + 0x10);
  uVar5 = *(undefined4 *)((int)context + 0x14);
  FUN_00026228(0x5658,DAT_00039c34,2,6,"#10631`%d",iVar6);
  pthread_mutex_lock((pthread_mutex_t *)(*(int *)capture + 0xf54));
  iVar7 = *(int *)capture;
  tVar2 = time((time_t *)0x0);
  iVar3 = *(int *)capture;
  *(time_t *)(iVar7 + 0xf6c) = tVar2;
  pthread_mutex_unlock((pthread_mutex_t *)(iVar3 + 0xf54));
  FUN_00026228(0x565d,uVar1,2,6,"#10632");
  ClearCleanRouting();
  FUN_00026228(0x565f,uVar1,2,6,"#10633");
  SetSharedCurrentMapFlag(iVar6);
  MapFlowSendSave(*(undefined4 *)capture,extraout_r1,uVar4,uVar5,1);
  FUN_0008c46c(*(undefined4 *)(*(int *)capture + 0x4e8));
  return 1;
}

