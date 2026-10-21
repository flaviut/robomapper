/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrutils.so
 * SHA256: 75927f4b9161a3b7a8c01771ca8496e061184c7b9c28f58958a10d6cba0a4f0b
 * Function VA: 0x000018a8
 */

/* Builds 12-element used array from nonzero primary entries and their nonzero backup bytes, via
   unlocked GetSharedUserMapInfo pointer. Returns first unused primary 2..5 (want_backup=0) or
   backup 6..9 (nonzero), otherwise -1. GetBakMapFlagStartPos=6 in librobopersist. No
   locking/reservation here; no checks before using loaded flag bytes as array indexes. Flags 10/11
   are not allocator candidates. */

MapPersistFlag rr_get_unused_persist_map_flag(bool want_backup)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  MapPersistFlag MVar5;
  int *piVar6;
  int *piVar7;
  int aiStack_4c [12];
  int local_1c;
  
  piVar7 = *(int **)(DAT_00001948 + 0x18b2 + DAT_0000194c);
  local_1c = *piVar7;
  memset(aiStack_4c,0,0x30);
  pbVar2 = (byte *)GetSharedUserMapInfo();
  pbVar4 = pbVar2 + 0x90;
  do {
    if (*pbVar2 != 0) {
      bVar1 = pbVar2[1];
      aiStack_4c[*pbVar2] = 1;
      if (bVar1 != 0) {
        aiStack_4c[bVar1] = 1;
      }
    }
    pbVar2 = pbVar2 + 0x24;
  } while (pbVar2 != pbVar4);
  if (want_backup) {
    MVar5 = GetBakMapFlagStartPos();
    piVar6 = aiStack_4c + MVar5 + -1;
    for (; iVar3 = GetBakMapFlagStartPos(), MVar5 <= iVar3 + 3; MVar5 = MVar5 + 1) {
      piVar6 = piVar6 + 1;
      if (*piVar6 == 0) goto LAB_0000190e;
    }
  }
  else {
    piVar6 = aiStack_4c + 1;
    for (MVar5 = 2; iVar3 = GetBakMapFlagStartPos(), MVar5 < iVar3; MVar5 = MVar5 + 1) {
      piVar6 = piVar6 + 1;
      if (*piVar6 == 0) goto LAB_0000190e;
    }
  }
  MVar5 = -1;
LAB_0000190e:
  if (local_1c != *piVar7) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return MVar5;
}

