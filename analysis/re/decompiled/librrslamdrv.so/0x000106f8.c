/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrslamdrv.so
 * SHA256: b48f5f56eb1b2d22abbf727725ea558762337f8f0103229d8da6c1ab6275608a
 * Function VA: 0x000106f8
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Loops flags 1 through 11 inclusive with base index 11 and calls GridDropCacheSlot. Drops last_map
   and user_map0..9 caches only; excludes mobility flag0 and tmp_map flag12. No disk deletion; no
   synchronization in this loop. Outer caller scope not recovered. */

void GridDropSavedCaches(void)

{
  int iVar1;
  void *store;
  int iVar2;
  int *piVar3;
  int local_24;
  int local_20;
  int local_1c;
  
  iVar1 = DAT_00010768 + 0x10700;
  piVar3 = *(int **)(iVar1 + DAT_0001076c);
  local_1c = *piVar3;
  if (5 < **(uint **)(iVar1 + DAT_00010770)) {
    (*(code *)**(undefined4 **)(iVar1 + DAT_00010774))
              (4,6,0x19c,DAT_00010778 + 0x107aa,DAT_0001077c + 0x1072c);
  }
  iVar1 = 1;
  do {
    store = (void *)FUN_00026e80();
    iVar2 = iVar1 + 1;
    local_24 = 0xb;
    local_20 = iVar1;
    GridDropCacheSlot(store,&local_24,&local_20);
    iVar1 = iVar2;
  } while (iVar2 != 0xc);
  if (local_1c == *piVar3) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

