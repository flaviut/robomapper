/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0001a530
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Cancellable zlib deflate helper. Arguments: base+offset input, length, opaque std::string output,
   pointer to task state. Continues only while *state==3; checks between deflate calls, not per
   byte. Clears output when canceled. Boolean success is local to helper; async save caller has no
   worker error channel. */

bool PersistDeflateCancellable
               (void *source,uint offset,uint length,void *output_string,PersistTaskState *state)

{
  uint uVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  char cVar6;
  undefined4 uVar7;
  int *piVar8;
  int local_64;
  int local_60;
  uint local_5c;
  int local_58;
  int local_54;
  uint local_50;
  int local_2c;
  
  piVar8 = *(int **)(DAT_0001a800 + 0x1a542 + DAT_0001a804);
  local_2c = *piVar8;
  memset(&local_64,0,0x38);
  iVar3 = deflateInit_(&local_64,0xffffffff,DAT_0001a808 + 0x1a56a,0x38);
  if (iVar3 != 0) {
    bVar2 = false;
    goto LAB_0001a570;
  }
  uVar4 = compressBound(length);
  cVar6 = (char)uVar4;
  if (0x3ffff < uVar4) {
    cVar6 = '\0';
  }
  std::string::resize((uint)output_string,cVar6);
  local_58 = *(int *)output_string;
  local_54 = *(int *)(local_58 + -0xc);
  if (-1 < *(int *)(local_58 + -4)) {
    std::string::_M_leak_hard();
    local_58 = *(int *)output_string;
  }
  iVar3 = 0;
  uVar4 = length;
  if (*state == PersistTaskEncoding) {
    local_60 = length - local_5c;
    local_64 = local_5c + offset + (int)source;
    do {
      if (*state != PersistTaskEncoding) break;
      if (*(uint *)(*(int *)output_string + -0xc) <= local_50) {
        std::string::resize((uint)output_string,(char)(*(uint *)(*(int *)output_string + -0xc) << 1)
                           );
        uVar1 = local_50;
        iVar3 = *(int *)output_string;
        if (-1 < *(int *)(iVar3 + -4)) {
          std::string::_M_leak_hard();
          iVar3 = *(int *)output_string;
        }
        local_58 = iVar3 + uVar1;
        local_54 = *(int *)(iVar3 + -0xc) - local_50;
      }
      iVar3 = deflate(&local_64,4);
      if (iVar3 == -2) {
        _rrlogm(0x15,3,0x140,DAT_0001a844 + 0x1a752,DAT_0001a83c + 0x1a764,DAT_0001a840 + 0x1a74e);
        iVar5 = rrlog_get_model_ver();
        if (iVar5 == 2) goto LAB_0001a7fc;
        if (local_60 != 0) goto LAB_0001a76a;
        goto LAB_0001a5be;
      }
    } while (local_54 == 0);
    if (local_60 != 0) {
      if (iVar3 == 1) {
LAB_0001a688:
        _rrlogm(0x15,3,0x14b,DAT_0001a820 + 0x1a6b0,DAT_0001a818 + 0x1a6ae,DAT_0001a81c + 0x1a69a,
                local_5c,length,local_60);
        iVar3 = rrlog_get_model_ver();
        if (iVar3 == 2) {
LAB_0001a7fc:
                    /* WARNING: Subroutine does not return */
          abort();
        }
        goto LAB_0001a6bc;
      }
LAB_0001a76a:
      std::string::resize((uint)output_string,(char)local_50);
      deflateEnd(&local_64);
      uVar7 = *(undefined4 *)(*(int *)output_string + -0xc);
      _rrlogm(0x15,6,0x151,DAT_0001a850 + 0x1a7aa,DAT_0001a84c + 0x1a7b4,DAT_0001a848 + 0x1a792,
              length,uVar7,offset);
      if (*state != PersistTaskEncoding) goto LAB_0001a708;
      goto LAB_0001a7b2;
    }
    if (iVar3 != 1) goto LAB_0001a5be;
    if (length != local_5c) goto LAB_0001a688;
LAB_0001a6bc:
    std::string::resize((uint)output_string,(char)local_50);
    deflateEnd(&local_64);
    uVar7 = *(undefined4 *)(*(int *)output_string + -0xc);
    _rrlogm(0x15,6,0x151,DAT_0001a82c + 0x1a6fa,DAT_0001a828 + 0x1a704,DAT_0001a824 + 0x1a6e2,length
            ,uVar7,offset);
    uVar4 = length;
    if (*state == PersistTaskEncoding) {
      bVar2 = true;
      goto LAB_0001a570;
    }
  }
  else {
LAB_0001a5be:
    std::string::resize((uint)output_string,(char)local_50);
    deflateEnd(&local_64);
    uVar7 = *(undefined4 *)(*(int *)output_string + -0xc);
    _rrlogm(0x15,6,0x151,DAT_0001a814 + 0x1a5fe,DAT_0001a810 + 0x1a608,DAT_0001a80c + 0x1a5e6,length
            ,uVar7,offset);
    if (*state == PersistTaskEncoding) {
LAB_0001a7b2:
      _rrlogm(0x15,4,0x15a,DAT_0001a85c + 0x1a7d6,DAT_0001a854 + 0x1a7de,DAT_0001a858 + 0x1a7ce,
              iVar3,length,*(undefined4 *)(*(int *)output_string + -0xc));
      rr_event_int(1,5,iVar3);
      bVar2 = false;
      goto LAB_0001a570;
    }
  }
LAB_0001a708:
  iVar3 = DAT_0001a830;
  std::string::_M_mutate((uint)output_string,0,*(uint *)(*(int *)output_string + -0xc));
  _rrlogm(0x15,7,0x155,DAT_0001a838 + 0x1a72c,DAT_0001a834 + 0x1a73c,iVar3 + 0x1a722,uVar4,uVar7,
          offset);
  bVar2 = false;
LAB_0001a570:
  if (local_2c == *piVar8) {
    return bVar2;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

