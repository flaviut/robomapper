/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0000e08c
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Catalog serialization boundary: builds catalog path, calls generic PersistSave(type=1,path). This
   is not PersistSaveMapInfo. Callers do not consume the save result; this wrapper adds no
   transaction/durability guarantee. */

void SerializeMultiMapInfo(void)

{
  bool bVar1;
  int *piVar2;
  char acStack_94 [128];
  int local_14;
  
  piVar2 = *(int **)(DAT_0000e0bc + 0xe094 + DAT_0000e0c0);
  local_14 = *piVar2;
  GetMultiMapFilePath(acStack_94);
  bVar1 = PersistSave(1,acStack_94);
  if (local_14 == *piVar2) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(bVar1);
}

