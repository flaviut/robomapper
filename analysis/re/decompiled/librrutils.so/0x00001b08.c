/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrutils.so
 * SHA256: 75927f4b9161a3b7a8c01771ca8496e061184c7b9c28f58958a10d6cba0a4f0b
 * Function VA: 0x00001b08
 */

/* Returns zero-extended primary byte for first matching backup byte, else -1. No
   nonzero-primary/backup check; reads unlocked pointer; passing zero can match an empty entry. */

MapPersistFlag rr_get_multimap_by_bakmap(MapPersistFlag backup_flag)

{
  byte *pbVar1;
  byte *pbVar2;
  
  pbVar1 = (byte *)GetSharedUserMapInfo();
  pbVar2 = pbVar1 + 0x90;
  do {
    if (backup_flag == (uint)pbVar1[1]) {
      return (uint)*pbVar1;
    }
    pbVar1 = pbVar1 + 0x24;
  } while (pbVar1 != pbVar2);
  return -1;
}

