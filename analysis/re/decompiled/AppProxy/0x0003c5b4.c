/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x0003c5b4
 */

/* Recovered from original Thumb bytes with exact EHABI start 0x3c5b4 and next start 0x3c5ec.
   Dereferences r1 as external-ID pointer, adds 2, calls 0x3c568 with a selected-native-flag output
   initialized to -1, and returns that selected output minus 2. The helper boolean is not the
   wrapper return. No external-ID bounds, file validity or cross-process completion inferred. */

int CatalogBackupExternal(void *param_1,int *param_2)

{
  MapPersistFlag MStack_18;
  int iStack_14;
  
  MStack_18 = -1;
  iStack_14 = __stack_chk_guard;
  CatalogSelectBackup(param_1,*param_2 + 2,&MStack_18);
  if (iStack_14 == __stack_chk_guard) {
    return MStack_18 + -2;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

