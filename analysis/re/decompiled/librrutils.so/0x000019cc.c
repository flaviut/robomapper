/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrutils.so
 * SHA256: 75927f4b9161a3b7a8c01771ca8496e061184c7b9c28f58958a10d6cba0a4f0b
 * Function VA: 0x000019cc
 */

/* Copies each 0x24-byte entry from live unlocked catalog while scanning primary. If matching entry
   has nonzero backup byte, uses GetOldestMapFlagIndex (constant 0 in this build) to return that
   backup; otherwise tail-calls rr_get_unused_persist_map_flag(true). Imported helper receives
   start-of-array pointer, not selected copy; with constant index 0 this does not alter selection.
   No file-existence or validity check; environment/path buffer setup does not choose a file here.
    */

MapPersistFlag rr_get_available_bak_map_flag_for_multimap(MapPersistFlag primary_flag)

{
  MapPersistFlag MVar1;
  char *__src;
  SharedUserMapInfo *pSVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  SharedUserMapInfo *pSVar6;
  SharedUserMapInfo *pSVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  int *piVar11;
  undefined4 local_c8;
  undefined4 auStack_c4 [8];
  char acStack_a4 [128];
  int local_24;
  
  piVar11 = *(int **)(DAT_00001a88 + 0x19d4 + DAT_00001a8c);
  local_24 = *piVar11;
  __src = getenv((char *)(DAT_00001a90 + 0x19e8));
  if (__src == (char *)0x0) {
    strncpy(acStack_a4,(char *)(DAT_00001a94 + 0x1a5a),0x7f);
  }
  else {
    strncpy(acStack_a4,__src,0x7f);
  }
  pSVar2 = (SharedUserMapInfo *)GetSharedUserMapInfo();
  iVar8 = 0;
  while( true ) {
    pSVar6 = pSVar2 + iVar8;
    puVar9 = &local_c8;
    do {
      pSVar7 = pSVar6 + 0x10;
      uVar3 = *(undefined4 *)(pSVar6 + 4);
      uVar4 = *(undefined4 *)(pSVar6 + 8);
      puVar10 = puVar9 + 4;
      uVar5 = *(undefined4 *)(pSVar6 + 0xc);
      *puVar9 = *(undefined4 *)pSVar6;
      puVar9[1] = uVar3;
      puVar9[2] = uVar4;
      puVar9[3] = uVar5;
      pSVar6 = pSVar7;
      puVar9 = puVar10;
    } while (pSVar7 != pSVar2 + iVar8 + 0x20);
    *puVar10 = *(undefined4 *)pSVar7;
    if (((byte)pSVar2[iVar8] != 0) && ((uint)(byte)pSVar2[iVar8] == primary_flag)) break;
    iVar8 = iVar8 + 0x24;
    if (iVar8 == 0x90) {
LAB_00001a3a:
      if (local_24 == *piVar11) {
                    /* WARNING: Could not recover jumptable at 0x00001504. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        MVar1 = (*(code *)PTR_rr_get_unused_persist_map_flag_00014018)(1);
        return MVar1;
      }
LAB_00001a84:
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail();
    }
  }
  if (local_c8._1_1_ != '\0') {
    iVar8 = GetOldestMapFlagIndex(pSVar2);
    if (local_24 == *piVar11) {
      return (uint)*(byte *)((int)auStack_c4 + iVar8 + -3);
    }
    goto LAB_00001a84;
  }
  goto LAB_00001a3a;
}

