/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrslamdrv.so
 * SHA256: b48f5f56eb1b2d22abbf727725ea558762337f8f0103229d8da6c1ab6275608a
 * Function VA: 0x00021a94
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* 16-byte MD5-compatible helper for ordinary grids (<2^29 bytes): standard IV at0x3f434, 64-byte
   blocks, 0x80 padding and four output words. Bit-length low word is length<<3 and high word is
   forced zero; do not generalize to enormous inputs. Callers hash only width*height cell bytes,
   never header. NULL digest exits; NULL cells yields sixteen zero bytes, even for length0 (not
   standard MD5(empty)). Saved-file hashes verified with hashlib; helper/internal compression is not
   firmware-executed. */

void GridCellDigest(uchar *cells,uint length,uchar *digest)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 uVar4;
  uchar *puVar5;
  uchar *puVar6;
  uint __n;
  undefined4 *unaff_r7;
  uint uVar7;
  undefined4 *puVar8;
  uchar *puVar9;
  undefined4 local_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 local_6c [14];
  int local_34;
  undefined4 local_30;
  int local_2c;
  
  piVar3 = *(int **)(DAT_00021b94 + 0x21aa2 + DAT_00021b98);
  local_2c = *piVar3;
  if (digest != (uchar *)0x0) {
    digest[0] = '\0';
    digest[1] = '\0';
    digest[2] = '\0';
    digest[3] = '\0';
    digest[4] = '\0';
    digest[5] = '\0';
    digest[6] = '\0';
    digest[7] = '\0';
    digest[8] = '\0';
    digest[9] = '\0';
    digest[10] = '\0';
    digest[0xb] = '\0';
    digest[0xc] = '\0';
    digest[0xd] = '\0';
    digest[0xe] = '\0';
    digest[0xf] = '\0';
    if (cells != (uchar *)0x0) {
      uVar7 = length >> 6;
      if (uVar7 == 0) {
        unaff_r7 = local_6c;
      }
      local_7c = *(undefined4 *)(DAT_00021b9c + 0x21ace);
      uStack_78 = *(undefined4 *)(DAT_00021b9c + 0x21ad2);
      uStack_74 = *(undefined4 *)(DAT_00021b9c + 0x21ad6);
      uStack_70 = *(undefined4 *)(DAT_00021b9c + 0x21ada);
      if (uVar7 != 0) {
        unaff_r7 = local_6c;
        puVar6 = cells;
        do {
          puVar9 = puVar6 + 0x40;
          puVar5 = puVar6;
          puVar8 = unaff_r7;
          do {
            puVar6 = puVar5 + 0x10;
            uVar1 = *(undefined4 *)(puVar5 + 4);
            uVar2 = *(undefined4 *)(puVar5 + 8);
            uVar4 = *(undefined4 *)(puVar5 + 0xc);
            *puVar8 = *(undefined4 *)puVar5;
            puVar8[1] = uVar1;
            puVar8[2] = uVar2;
            puVar8[3] = uVar4;
            puVar5 = puVar6;
            puVar8 = puVar8 + 4;
          } while (puVar6 != puVar9);
          FUN_000212c0(&local_7c,unaff_r7);
        } while (cells + uVar7 * 0x40 != puVar6);
      }
      uVar7 = length & 0x3f;
      if ((length & 0xffffffc0) < length) {
        __memcpy_chk(unaff_r7,cells + (length & 0xffffffc0),uVar7,0x40);
      }
      __n = 0x40 - (uVar7 + 1);
      *(undefined1 *)((int)local_6c + uVar7) = 0x80;
      memset((void *)(uVar7 + 1 + (int)unaff_r7),0,__n);
      if (__n < 8) {
        FUN_000212c0(&local_7c,unaff_r7);
        memset(unaff_r7,0,0x38);
      }
      local_34 = length << 3;
      local_30 = 0;
      FUN_000212c0(&local_7c,unaff_r7);
      *(undefined4 *)digest = local_7c;
      *(undefined4 *)(digest + 4) = uStack_78;
      *(undefined4 *)(digest + 8) = uStack_74;
      *(undefined4 *)(digest + 0xc) = uStack_70;
    }
  }
  if (local_2c == *piVar3) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

