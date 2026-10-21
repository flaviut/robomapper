/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrslamdrv.so
 * SHA256: b48f5f56eb1b2d22abbf727725ea558762337f8f0103229d8da6c1ab6275608a
 * Function VA: 0x0001ab84
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* RRSLAM v2 stream writer. 0x1abc0-0x1abde writes 10-byte RRSLAM/version=2/header-length=20 prefix;
   0x1ac00-0x1ac78 writes five LE words: scale=20,left,top,width,height. GridDiskHeaderV2 is
   byte-aligned disk documentation ONLY, never an in-memory grid cast. Extracts active view from
   metadata+0x10 into row-major byte buffer; initializes to 0x80, copies rows using full bounds
   stride. Product is low 32 bits of width*height; width loop is signed >0, row limit unsigned.
   0x1ad0a-0x1ad38 writes cells then 16-byte MD5 of cells only. Skips later stages on stream state
   bit 1 (badbit), not failbit. Does not rename, fsync, or select a filename. Returns stream
   pointer; does not establish durability. Zero product uses NULL buffer and helper emits zero
   digest, not MD5(empty). Occupancy probability mapping unresolved. */

void * GridWriteV2(void *stream,GridBufferRef *grid)

{
  uint uVar1;
  uchar *cells;
  int iVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  uchar *puVar6;
  int iVar7;
  uchar *puVar8;
  uchar *puVar9;
  int iVar11;
  uchar *puVar12;
  undefined4 local_5c;
  uint local_58;
  uint local_54;
  uint local_50;
  uint local_4c;
  undefined4 local_48;
  undefined2 local_44;
  undefined2 local_42;
  undefined2 local_40;
  uchar auStack_3c [16];
  int local_2c;
  uchar *puVar10;
  
  iVar7 = DAT_0001ad7c + 0x1ab96;
  piVar4 = *(int **)(iVar7 + DAT_0001ad80);
  local_2c = *piVar4;
  if (-1 < *(int *)((int)stream + *(int *)(*(int *)stream + -0xc) + 0x14) << 0x1f) {
    local_42 = 2;
    local_40 = 0x14;
    local_48 = *(undefined4 *)(DAT_0001ad84 + 0x1abca);
    local_44 = (undefined2)*(undefined4 *)(DAT_0001ad84 + 0x1abce);
    std::ostream::write(stream,&local_48,10);
    uVar5 = *(uint *)((int)stream + *(int *)(*(int *)stream + -0xc) + 0x14) & 1;
    if (uVar5 == 0) {
      local_5c = 0x14;
      local_58 = uVar5;
      local_54 = uVar5;
      local_50 = uVar5;
      local_4c = uVar5;
      local_58 = GridRectLeft(&grid->metadata->view);
      local_54 = GridRectTop(&grid->metadata->view);
      local_50 = GridRectWidth(&grid->metadata->view);
      local_4c = GridRectHeight(&grid->metadata->view);
      if (5 < **(uint **)(iVar7 + DAT_0001ad88)) {
        (*(code *)**(undefined4 **)(iVar7 + DAT_0001ad8c))
                  (4,6,0x136,&UNK_0001ad5c + DAT_0001ad94,DAT_0001ad90 + 0x1ac6a,local_42,local_5c,
                   local_58,local_54,local_50,local_4c);
      }
      std::ostream::write(stream,&local_5c,0x14);
      if ((*(uint *)((int)stream + *(int *)(*(int *)stream + -0xc) + 0x14) & 1) == 0) {
        uVar5 = local_50 * local_4c;
        if (uVar5 == 0) {
          puVar12 = (uchar *)0x0;
          cells = (uchar *)0x0;
        }
        else {
          cells = operator_new(uVar5);
          puVar12 = cells + uVar5;
          puVar8 = cells;
          do {
            GridCellSet(puVar8,0x80);
            puVar8 = puVar8 + 1;
          } while (puVar8 != puVar12);
        }
        uVar5 = 0;
        if (local_4c != 0) {
          do {
            uVar1 = local_58;
            puVar8 = grid->cells;
            iVar7 = GridRectLeft(&grid->metadata->bounds);
            iVar11 = uVar5 + local_54;
            iVar2 = GridRectTop(&grid->metadata->bounds);
            iVar3 = GridRectWidth(&grid->metadata->bounds);
            if (0 < (int)local_50) {
              puVar6 = cells + uVar5 * local_50 + -1;
              puVar10 = puVar8 + iVar3 * (iVar11 - iVar2) + (uVar1 - iVar7);
              do {
                puVar9 = puVar10 + 1;
                puVar6 = puVar6 + 1;
                *puVar6 = *puVar10;
                puVar10 = puVar9;
              } while (puVar9 != puVar8 + iVar3 * (iVar11 - iVar2) + (uVar1 - iVar7) + local_50);
            }
            uVar5 = uVar5 + 1;
          } while (uVar5 < local_4c);
        }
        std::ostream::write(stream,cells,(int)puVar12 - (int)cells);
        if (-1 < *(int *)((int)stream + *(int *)(*(int *)stream + -0xc) + 0x14) << 0x1f) {
          GridCellDigest(cells,(int)puVar12 - (int)cells,auStack_3c);
          std::ostream::write(stream,auStack_3c,0x10);
        }
        if (cells != (uchar *)0x0) {
          operator_delete(cells);
        }
      }
    }
  }
  if (local_2c == *piVar4) {
    return stream;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

