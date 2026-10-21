/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x001a73b4
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_001a73b4(undefined4 *param_1,int param_2,undefined4 param_3)

{
  bool bVar1;
  undefined4 *puVar2;
  int *piVar3;
  allocator *paVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  char *__s;
  int local_28;
  int local_24;
  
  iVar6 = _LAB_001a7470 + 0x1a73c6;
  __s = *(char **)(param_2 + 0x18);
  piVar7 = *(int **)(iVar6 + _LAB_001a7474);
  local_24 = *piVar7;
  __gnu_cxx::__to_xstring<std::string,char>
            ((__gnu_cxx *)&local_28,
             *(_func_int_char_ptr_uint_char_ptr___va_list **)(iVar6 + _LAB_001a7478),0x10,
             (char *)(_LAB_001a747c + 0x1a73da),param_3);
  strlen(__s);
  puVar2 = (undefined4 *)std::string::insert((uint)&local_28,(char *)0x0,(uint)__s);
  iVar5 = _LAB_001a7480;
  *param_1 = *puVar2;
  paVar4 = *(allocator **)(iVar6 + iVar5);
  *puVar2 = paVar4 + 0xc;
  if ((allocator *)(local_28 + -0xc) != paVar4) {
    if (*(int *)(iVar6 + _LAB_001a7484) == 0) {
      iVar5 = *(int *)(local_28 + -4);
      *(int *)(local_28 + -4) = iVar5 + -1;
    }
    else {
      piVar3 = (int *)(local_28 + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar3);
        iVar5 = *piVar3;
        bVar1 = (bool)hasExclusiveAccess(piVar3);
      } while (!bVar1);
      *piVar3 = iVar5 + -1;
      DataMemoryBarrier(0x1b);
    }
    if (iVar5 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_28 + -0xc));
    }
  }
  if (local_24 != *piVar7) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(param_1);
  }
  return;
}

