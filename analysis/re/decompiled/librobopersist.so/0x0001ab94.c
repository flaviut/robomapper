/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0001ab94
 */

/* ABI-level signature: r0 is hidden std::string result storage, r1 is signed persistence flag;
   original std::string layout deliberately opaque. flag=-2 selects /dev/shm/PersistData_Temp.data.
   Otherwise cached getenv(NAV_DYNAMIC_CONFIG_PATH) or /mnt/data/rockrobo is followed by
   /PersistData_, signed decimal flag and .data; no range restriction. Persistence -2 is not Grid
   temporary flag 12. */

void GetMapInfoPersistFileName(void *string_result,MapPersistFlag flag)

{
  bool bVar1;
  uint *puVar2;
  int *piVar3;
  undefined4 *puVar4;
  int iVar5;
  char *pcVar6;
  uint uVar7;
  int iVar8;
  allocator *paVar9;
  int iVar10;
  int *piVar11;
  int iVar12;
  allocator aaStack_3c [8];
  int local_34;
  uint local_30;
  int local_2c;
  int local_28;
  int local_24;
  
  iVar8 = DAT_0001ae18;
  iVar10 = DAT_0001ae10 + 0x1aba6;
  piVar11 = *(int **)(iVar10 + DAT_0001ae14);
  local_24 = *piVar11;
  if (flag == -2) {
    std::string::string(string_result,(char *)(DAT_0001ae3c + 0x1acda),(allocator *)&local_28);
    goto LAB_0001ac76;
  }
  if (*(int *)(DAT_0001ae18 + 0x1abc4) << 0x1f < 0) {
LAB_0001abc2:
    pcVar6 = *(char **)(iVar8 + 0x1abc8);
  }
  else {
    iVar12 = DAT_0001ae18 + 0x1abc4;
    iVar5 = __cxa_guard_acquire(iVar12);
    if (iVar5 == 0) goto LAB_0001abc2;
    pcVar6 = getenv((char *)(DAT_0001ae30 + 0x1acb0));
    *(char **)(iVar8 + 0x1abc8) = pcVar6;
    __cxa_guard_release(iVar12);
  }
  if (pcVar6 == (char *)0x0) {
    pcVar6 = (char *)(DAT_0001ae34 + 0x1accc);
    *(char **)(DAT_0001ae38 + 0x1acda) = pcVar6;
  }
  std::string::string((string *)&local_34,pcVar6,aaStack_3c);
  puVar2 = (uint *)std::string::append((char *)&local_34,DAT_0001ae1c + 0x1abde);
  iVar8 = DAT_0001ae24;
  local_30 = *puVar2;
  paVar9 = *(allocator **)(iVar10 + DAT_0001ae20);
  *puVar2 = (uint)(paVar9 + 0xc);
  __gnu_cxx::__to_xstring<std::string,char>
            ((__gnu_cxx *)&local_2c,*(_func_int_char_ptr_uint_char_ptr___va_list **)(iVar10 + iVar8)
             ,0x10,(char *)(DAT_0001ae28 + 0x1ac06),flag);
  uVar7 = *(int *)(local_2c + -0xc) + *(int *)(local_30 - 0xc);
  if ((*(uint *)(local_30 - 8) < uVar7) && (uVar7 <= *(uint *)(local_2c + -8))) {
    piVar3 = (int *)std::string::insert((uint)&local_2c,(char *)0x0,local_30);
  }
  else {
    piVar3 = (int *)std::string::append((string *)&local_30);
  }
  local_28 = *piVar3;
  *piVar3 = (int)(paVar9 + 0xc);
  puVar4 = (undefined4 *)std::string::append((char *)&local_28,DAT_0001ae2c + 0x1ac40);
  *(undefined4 *)string_result = *puVar4;
  *puVar4 = paVar9 + 0xc;
  if ((allocator *)(local_28 + -0xc) != paVar9) {
    if (*(int *)(iVar10 + DAT_0001ae40) == 0) {
      iVar8 = *(int *)(local_28 + -4);
      *(int *)(local_28 + -4) = iVar8 + -1;
    }
    else {
      piVar3 = (int *)(local_28 + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar3);
        iVar8 = *piVar3;
        bVar1 = (bool)hasExclusiveAccess(piVar3);
      } while (!bVar1);
      *piVar3 = iVar8 + -1;
      DataMemoryBarrier(0x1b);
    }
    if (iVar8 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_28 + -0xc));
    }
  }
  if ((allocator *)(local_2c + -0xc) != paVar9) {
    if (*(int *)(iVar10 + DAT_0001ae40) == 0) {
      iVar8 = *(int *)(local_2c + -4);
      *(int *)(local_2c + -4) = iVar8 + -1;
    }
    else {
      piVar3 = (int *)(local_2c + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar3);
        iVar8 = *piVar3;
        bVar1 = (bool)hasExclusiveAccess(piVar3);
      } while (!bVar1);
      *piVar3 = iVar8 + -1;
      DataMemoryBarrier(0x1b);
    }
    if (iVar8 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_2c + -0xc));
    }
  }
  if ((allocator *)(local_30 - 0xc) != paVar9) {
    if (*(int *)(iVar10 + DAT_0001ae40) == 0) {
      iVar8 = *(int *)(local_30 - 4);
      *(int *)(local_30 - 4) = iVar8 + -1;
    }
    else {
      piVar3 = (int *)(local_30 - 4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar3);
        iVar8 = *piVar3;
        bVar1 = (bool)hasExclusiveAccess(piVar3);
      } while (!bVar1);
      *piVar3 = iVar8 + -1;
      DataMemoryBarrier(0x1b);
    }
    if (iVar8 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_30 - 0xc));
    }
  }
  if ((allocator *)(local_34 + -0xc) != paVar9) {
    if (*(int *)(iVar10 + DAT_0001ae40) == 0) {
      iVar8 = *(int *)(local_34 + -4);
      *(int *)(local_34 + -4) = iVar8 + -1;
    }
    else {
      piVar3 = (int *)(local_34 + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar3);
        iVar8 = *piVar3;
        bVar1 = (bool)hasExclusiveAccess(piVar3);
      } while (!bVar1);
      *piVar3 = iVar8 + -1;
      DataMemoryBarrier(0x1b);
    }
    if (iVar8 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_34 + -0xc));
    }
  }
LAB_0001ac76:
  if (local_24 == *piVar11) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(string_result);
}

