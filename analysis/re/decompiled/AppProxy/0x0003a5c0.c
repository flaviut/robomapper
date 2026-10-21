/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x0003a5c0
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Final recovery step invokes backup-DB write for requested native flag then returns zero
   unconditionally, even if DB helper logged a failure. Series runner can consequently send success
   after a failed DB write. */

int MapFlowBackupDbStep(void *capture,void *context,int *native_flag)

{
  int native_flag_00;
  
  native_flag_00 = *native_flag;
  FUN_00026228(0x566a,DAT_0003a5f0,2,6,"#10634`%d",native_flag_00);
  MapFlowWriteBackupDb(*(void **)capture,native_flag_00);
  return 0;
}

