/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrutils.so
 * SHA256: 75927f4b9161a3b7a8c01771ca8496e061184c7b9c28f58958a10d6cba0a4f0b
 * Function VA: 0x00001950
 */

/* Counts nonzero primary bytes from unlocked catalog pointer. Capacity limit is four only when
   mode==1, otherwise one; returns count below limit. This is not slot reservation. */

bool rr_get_multimap_flag_available(int mode)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar2 = GetSharedUserMapInfo();
  iVar4 = 0;
  iVar3 = 0;
  do {
    pcVar1 = (char *)(iVar2 + iVar4);
    iVar4 = iVar4 + 0x24;
    if (*pcVar1 != '\0') {
      iVar3 = iVar3 + 1;
    }
  } while (iVar4 != 0x90);
  if (mode == 1) {
    iVar2 = 4;
  }
  else {
    iVar2 = 1;
  }
  return iVar3 < iVar2;
}

