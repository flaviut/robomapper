/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x00017664
 */

/* Ordinary synchronous zlib compressor. ABI arguments are source base, byte offset, byte length,
   opaque std::string output reference. Does not inspect task cancellation. compress receives
   source+offset and length; zlib failures are logged, not returned to PersistSave. */

void CompressRegionWorker(void *source,uint offset,uint length,void *output_string)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined4 local_30;
  int local_2c;
  
  piVar3 = *(int **)(DAT_00017738 + 0x17676 + DAT_0001773c);
  local_2c = *piVar3;
  local_30 = compressBound(length);
  std::string::resize((uint)output_string,(char)local_30);
  iVar2 = *(int *)output_string;
  if (-1 < *(int *)(iVar2 + -4)) {
    std::string::_M_leak_hard();
    iVar2 = *(int *)output_string;
  }
  iVar1 = DAT_00017740;
  iVar2 = compress(iVar2,&local_30,(int)source + offset,length);
  iVar4 = DAT_00017748 + 0x176d2;
  _rrlogm(0x15,6,0x154,iVar1 + 0x176c0,iVar4,DAT_00017744 + 0x176ce,length,local_30,offset);
  if (iVar2 == 0) {
    std::string::resize((uint)output_string,(char)local_30);
  }
  else {
    _rrlogm(0x15,4,0x157,iVar1 + 0x176c0,iVar4,DAT_0001774c + 0x17718,iVar2,length,local_30);
    rr_event_int(1,5,iVar2);
  }
  if (local_2c == *piVar3) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

