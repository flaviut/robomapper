/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrslamdrv.so
 * SHA256: b48f5f56eb1b2d22abbf727725ea558762337f8f0103229d8da6c1ab6275608a
 * Function VA: 0x0001d21c
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* V2 body; dispatcher has already consumed 10 bytes. Reads 20-byte view block:
   scale,left,top,width,height. Requires scale==20 at 0x1d29c; computes low-32-bit width*height at
   0x1d2ba with no explicit dimension/bounds/overflow validation. Reads byte cells and 16-byte
   digest. All four words must compare at 0x1d324/0x1d33e/0x1d346/0x1d34e before mutation. Digest
   excludes entire header. Success resets full existing target to 0x80, merges file rectangle into
   active view, copies rows using target bounds and stride. Width copy condition signed >0; height
   iteration unsigned. Scale or MD5 rejection returns same stream without explicit setstate; outer
   stream-state success does NOT prove cells accepted. Intermediate checks test only state bit 1
   (badbit), not failbit. No trailing-length or occupancy-value validation. No lock in this
   function; caller synchronization unresolved. */

void * GridReadV2(GridReadContext *context)

{
  int iVar1;
  uchar *cells;
  int iVar2;
  int iVar3;
  int iVar4;
  int *stream;
  uchar *puVar5;
  GridBufferRef *grid;
  uchar *puVar6;
  int iVar8;
  int *piVar9;
  uint uVar10;
  int iVar11;
  GridSize local_78;
  GridRect GStack_70;
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  uint local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  uchar *puVar7;
  
  iVar8 = DAT_0001d414 + 0x1d22e;
  piVar9 = *(int **)(iVar8 + DAT_0001d418);
  local_60 = 0;
  local_5c = 0;
  local_58 = 0;
  local_54 = 0;
  local_2c = *piVar9;
  local_50 = 0;
  std::istream::read(context->stream,&local_60,0x14);
  stream = context->stream;
  if ((*(uint *)((int)stream + *(int *)(*stream + -0xc) + 0x14) & 1) == 0) {
    if (5 < **(uint **)(iVar8 + DAT_0001d41c)) {
      (*(code *)**(undefined4 **)(iVar8 + DAT_0001d420))
                (4,6,0x234,DAT_0001d424 + 0x1d46a,DAT_0001d428 + 0x1d298,local_60,local_5c,local_58,
                 local_54,local_50);
    }
    if (local_60 == 0x14) {
      uVar10 = local_50 * local_54;
      if (uVar10 == 0) {
        uVar10 = 0;
        cells = (uchar *)0x0;
      }
      else {
        cells = operator_new(uVar10);
        puVar5 = cells;
        do {
          GridCellSet(puVar5,0x80);
          puVar5 = puVar5 + 1;
        } while (puVar5 != cells + uVar10);
      }
      std::istream::read(context->stream,cells,uVar10);
      stream = context->stream;
      if (-1 < *(int *)((int)stream + *(int *)(*stream + -0xc) + 0x14) << 0x1f) {
        std::istream::read(stream,&local_4c,0x10);
        stream = context->stream;
        if (-1 < *(int *)((int)stream + *(int *)(*stream + -0xc) + 0x14) << 0x1f) {
          GridCellDigest(cells,uVar10,(uchar *)&local_3c);
          if ((((local_4c == local_3c) && (local_48 == local_38)) && (local_44 == local_34)) &&
             (local_40 == local_30)) {
            uVar10 = 0;
            grid = context->target;
            GridCellSet((uchar *)&GStack_70,0x80);
            GridResetCells(grid,(uchar *)&GStack_70);
            local_78.width = local_54;
            local_78.height = local_50;
            GridRectSet(&GStack_70,local_5c,local_58,&local_78);
            GridRectMergeInto(&context->target->metadata->view,&GStack_70);
            if (local_50 != 0) {
              do {
                iVar1 = local_5c;
                iVar8 = local_54 * uVar10;
                puVar5 = context->target->cells;
                iVar2 = GridRectLeft(&context->target->metadata->bounds);
                iVar11 = uVar10 + local_58;
                iVar3 = GridRectTop(&context->target->metadata->bounds);
                iVar4 = GridRectWidth(&context->target->metadata->bounds);
                if (0 < local_54) {
                  puVar5 = puVar5 + iVar4 * (iVar11 - iVar3) + (iVar1 - iVar2) + -1;
                  puVar7 = cells + iVar8;
                  do {
                    puVar6 = puVar7 + 1;
                    puVar5 = puVar5 + 1;
                    *puVar5 = *puVar7;
                    puVar7 = puVar6;
                  } while (puVar6 != cells + iVar8 + local_54);
                }
                uVar10 = uVar10 + 1;
              } while (uVar10 < local_50);
            }
          }
          stream = context->stream;
        }
      }
      if (cells != (uchar *)0x0) {
        operator_delete(cells);
      }
    }
    else {
      stream = context->stream;
    }
  }
  if (local_2c == *piVar9) {
    return stream;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

