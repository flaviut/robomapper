/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrutils.so
 * SHA256: 75927f4b9161a3b7a8c01771ca8496e061184c7b9c28f58958a10d6cba0a4f0b
 * Function VA: 0x00001ae0
 */

/* Returns matching entry+4 name-byte pointer or static fallback pointer; four entries, stride 0x24.
   Pointer is not locked and 32 stored name bytes need not be NUL-terminated; no
   validation/termination added here. */

char * rr_get_multimap_name(MapPersistFlag flag)

{
  byte *pbVar1;
  byte *pbVar2;
  
  pbVar1 = (byte *)GetSharedUserMapInfo();
  pbVar2 = pbVar1 + 0x90;
  do {
    if ((uint)*pbVar1 == flag) {
      return (char *)(pbVar1 + 4);
    }
    pbVar1 = pbVar1 + 0x24;
  } while (pbVar1 != pbVar2);
  return (char *)(DAT_00001b04 + 0x1afe);
}

