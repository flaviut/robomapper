/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x0003b908
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Adds 2 to external_id in 32-bit register arithmetic. Primary branch (want_backup=0) requires
   signed native flag >1 and <6 plus catalog primary membership. Backup branch requires signed
   native flag >=6 and <=11, without catalog association check. Accepted branches tail-jump to
   shared path code at 0x37448: checks access(F_OK) for configured-base
   /rockrobo/user_map<external_id>. Existence only, not loadability. No database access. Baseline
   function body includes that shared tail; no function creation performed. */

bool CatalogExternalMapExists(void *context_unknown,int external_id,int want_backup)

{
  int iVar1;
  int iVar2;
  undefined1 auStack_120 [12];
  char acStack_114 [255];
  undefined1 local_15;
  int local_14;
  
  iVar2 = external_id + 2;
  if (want_backup == 0) {
    if (((1 < iVar2) && (iVar1 = GetBakMapFlagStartPos(), iVar2 < iVar1)) &&
       (iVar2 = rr_check_mapflag_is_multimap(iVar2), iVar2 != 0)) {
LAB_00037448:
      local_14 = __stack_chk_guard;
      strncpy(acStack_114,(char *)&DAT_0035367c,0xff);
      __strcat_chk(acStack_114,"/rockrobo/user_map",0x100);
      __sprintf_chk(auStack_120,1,10,"%d",external_id);
      __strncat_chk(acStack_114,auStack_120,0xff,0x100);
      local_15 = 0;
      iVar2 = access(acStack_114,0);
      if (local_14 != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail();
      }
      return iVar2 == 0;
    }
  }
  else {
    iVar1 = GetBakMapFlagStartPos();
    if (iVar1 <= iVar2 && iVar2 < 0xc) goto LAB_00037448;
  }
  return false;
}

