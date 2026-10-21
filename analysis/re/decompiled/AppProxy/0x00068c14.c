/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x00068c14
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* First recovery step: chooses backup again through 0x3c568, invokes destination helper 0x68b48,
   sends 0x01033107, then load 0x02033204 for selected backup flag; returns 1 (wait). Helper 0x68b48
   forwards a flag vector to unresolved 0x68ae8; its completion/cancellation semantics are not
   proven here. */

int MapFlowRecoverLoadStep(void *capture,void *context,int *native_flag)

{
  MapPersistFlag primary_flag;
  undefined4 uVar1;
  undefined4 uVar2;
  MapPersistFlag local_28;
  int local_24;
  
  primary_flag = *native_flag;
  uVar1 = *(undefined4 *)((int)context + 0x10);
  uVar2 = *(undefined4 *)((int)context + 0x14);
  local_24 = __stack_chk_guard;
  FUN_00026228(0x556d,DAT_00068cac,2,6,"#10605`%d",primary_flag);
  FUN_0003cc18(*(undefined4 *)capture);
  CatalogSelectBackup(*(void **)capture,primary_flag,&local_28);
  FUN_00039dec(*(undefined4 *)capture);
  FUN_00068b48(*(undefined4 *)capture,primary_flag);
  MapFlowSendLoad(*(undefined4 *)capture,local_28,uVar1,uVar2,local_28);
  FUN_00039a38(*(undefined4 *)capture);
  FUN_00026228(0x5575,DAT_00068cac,1,7,"#10606`%d",local_28);
  if (local_24 == __stack_chk_guard) {
    return 1;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

