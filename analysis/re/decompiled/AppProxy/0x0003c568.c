/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x0003c568
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Calls GetBakMapList(primary_flag), reads returned byte after catalog guard release; NULL gives
   -1. Signed backup >=6 stores backup and returns 1; otherwise stores original primary and returns
   0. No upper bound or file existence/load check. Narrow external-ID wrapper bytes at 0x3c5b4 load
   ID through r1 pointer, add2, call here, then subtract2 from output; that location has no baseline
   function and is intentionally not annotated. */

bool CatalogSelectBackup(void *context_unknown,MapPersistFlag primary_flag,
                        MapPersistFlag *selected_flag_out)

{
  byte *pbVar1;
  int iVar2;
  uint uVar3;
  
  pbVar1 = (byte *)GetBakMapList(primary_flag);
  uVar3 = 0xffffffff;
  if (pbVar1 != (byte *)0x0) {
    uVar3 = (uint)*pbVar1;
  }
  iVar2 = GetBakMapFlagStartPos();
  if ((int)uVar3 < iVar2) {
    *selected_flag_out = primary_flag;
  }
  else {
    *selected_flag_out = uVar3;
    FUN_00026228(0x5420,DAT_0003c5b0,1,6,"#10573`%d",uVar3);
  }
  return (int)uVar3 >= iVar2;
}

