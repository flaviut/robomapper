/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0000e924
 */

/* Despite surviving name, this build always returns index 0 (r6 initialized zero, copied to r0 on
   success). Reads entry backup byte, constructs user_map(backup-2), calls GetFileModifyTime but
   does not compare its result. No oldest-of-multiple selection is implemented here. */

int GetOldestMapFlagIndex(MapCatalogEntry *entry)

{
  byte bVar1;
  int *piVar2;
  undefined1 auStack_128 [12];
  char acStack_11c [128];
  char acStack_9c [127];
  undefined1 local_1d;
  int local_1c;
  
  piVar2 = *(int **)(DAT_0000e998 + 0xe92c + DAT_0000e99c);
  local_1c = *piVar2;
  GetUserDataPath(acStack_11c);
  bVar1 = entry->backup_flag_byte;
  strncpy(acStack_9c,acStack_11c,0x7f);
  __strcat_chk(acStack_9c,DAT_0000e9a0 + 0xe958,0x80);
  __sprintf_chk(auStack_128,1,10,DAT_0000e9a4 + 0xe96c,bVar1 - 2);
  __strncat_chk(acStack_9c,auStack_128,0x7f,0x80);
  local_1d = 0;
  GetFileModifyTime(acStack_9c);
  if (local_1c == *piVar2) {
    return 0;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

