/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrutils.so
 * SHA256: 75927f4b9161a3b7a8c01771ca8496e061184c7b9c28f58958a10d6cba0a4f0b
 * Function VA: 0x00001ac0
 */

/* Returns 1 only for matching nonzero primary byte among four entries; reads unlocked catalog
   pointer and does not check any map file. */

bool rr_check_mapflag_is_multimap(MapPersistFlag flag)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = GetSharedUserMapInfo();
  iVar3 = 0;
  while( true ) {
    pbVar1 = (byte *)(iVar2 + iVar3);
    iVar3 = iVar3 + 0x24;
    if ((*pbVar1 != 0) && ((uint)*pbVar1 == flag)) break;
    if (iVar3 == 0x90) {
      return false;
    }
  }
  return true;
}

