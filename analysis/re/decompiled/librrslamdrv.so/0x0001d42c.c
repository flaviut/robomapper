/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrslamdrv.so
 * SHA256: b48f5f56eb1b2d22abbf727725ea558762337f8f0103229d8da6c1ab6275608a
 * Function VA: 0x0001d42c
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Reads 10-byte prefix. Magic checks 0x1d488-0x1d4a6 compare RRSLAM (0x4c535252,0x4d41). Matching
   magic: version 2 requires uint16 header-length 20 then GridReadV2; version 1 requires 36 then
   legacy 0x1cf60. Unknown version/header length returns without setstate. Magic mismatch calls
   legacy 0x1ca54 after prefix read; legacy seek/format behavior not recovered here. Returns stream
   pointer, not format-validation status. Tests bit 1 only internally. */

void * GridReadDispatch(void *stream,GridBufferRef *target)

{
  uint uVar1;
  int *piVar2;
  void *local_38;
  GridBufferRef *pGStack_34;
  void *local_30;
  GridBufferRef *pGStack_2c;
  GridReadContext local_28;
  uint local_20;
  undefined4 local_1c;
  short local_18;
  int local_14;
  
  piVar2 = *(int **)(DAT_0001d4d8 + 0x1d436 + DAT_0001d4dc);
  local_14 = *piVar2;
  uVar1 = *(uint *)((int)stream + *(int *)(*(int *)stream + -0xc) + 0x14) & 1;
  local_38 = stream;
  pGStack_34 = target;
  local_30 = stream;
  pGStack_2c = target;
  local_28.stream = stream;
  local_28.target = target;
  if (uVar1 == 0) {
    local_18 = 0;
    local_20 = uVar1;
    local_1c = uVar1;
    std::istream::read(stream,&local_20,10);
    if (-1 < *(int *)((int)stream + *(int *)(*(int *)stream + -0xc) + 0x14) << 0x1f) {
      if ((local_20 == 0x4c535252) && ((local_1c & 0xffff) == 0x4d41)) {
        if (local_1c._2_2_ == 2) {
          if (local_18 == 0x14) {
            stream = GridReadV2(&local_28);
          }
        }
        else if ((local_1c._2_2_ == 1) && (local_18 == 0x24)) {
          stream = (void *)FUN_0001cf60(&local_30);
        }
      }
      else {
        stream = (void *)FUN_0001ca54(&local_38);
      }
    }
  }
  if (local_14 != *piVar2) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return stream;
}

