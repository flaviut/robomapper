/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x00019ba4
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* For type==0 extracts a destination flag from filename and delegates to buffer-aware
   PersistLoadMapInfo. For nonzero type delegates to ForcePersistLoad. Use ForcePersistLoad only
   when describing a file-only call boundary. */

bool PersistLoad(int persistence_type,char *filename)

{
  bool bVar1;
  bool bVar2;
  int flag;
  int *piVar3;
  int iVar4;
  int *piVar5;
  allocator aaStack_20 [8];
  int local_18;
  int local_14;
  
  iVar4 = _LAB_00019c64 + 0x19bb0;
  piVar5 = *(int **)(iVar4 + _LAB_00019c68);
  local_14 = *piVar5;
  if (persistence_type == 0) {
    _rrlogm(0x15,3,0x1e8,_LAB_00019c74 + 0x19bce,_LAB_00019c6c + 0x19d1e,_LAB_00019c70 + 0x19bc8);
    std::string::string((string *)&local_18,filename,aaStack_20);
    flag = FUN_00017898((string *)&local_18);
    bVar2 = PersistLoadMapInfo(flag);
    if ((allocator *)(local_18 + -0xc) != *(allocator **)(iVar4 + _LAB_00019c78)) {
      if (*(int *)(iVar4 + _LAB_00019c7c) == 0) {
        iVar4 = *(int *)(local_18 + -4);
        *(int *)(local_18 + -4) = iVar4 + -1;
      }
      else {
        piVar3 = (int *)(local_18 + -4);
        DataMemoryBarrier(0x1b);
        do {
          ExclusiveAccess(piVar3);
          iVar4 = *piVar3;
          bVar1 = (bool)hasExclusiveAccess(piVar3);
        } while (!bVar1);
        *piVar3 = iVar4 + -1;
        DataMemoryBarrier(0x1b);
      }
      if (iVar4 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_18 + -0xc));
      }
    }
  }
  else {
    bVar2 = ForcePersistLoad(persistence_type,filename);
  }
  if (local_14 != *piVar5) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return bVar2;
}

