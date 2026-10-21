/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrslamdrv.so
 * SHA256: b48f5f56eb1b2d22abbf727725ea558762337f8f0103229d8da6c1ab6275608a
 * Function VA: 0x00022030
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Assigns bounding rectangle union from helper0x21f14. V2 load merges file rectangle into cleared
   active view; not clipping to allocated bounds. No bounds enforcement here. */

GridRect * GridRectMergeInto(GridRect *rect,GridRect *other)

{
  int iVar1;
  int *piVar2;
  GridRect local_30;
  int local_1c;
  
  piVar2 = *(int **)(DAT_00022068 + 0x2203a + DAT_0002206c);
  local_1c = *piVar2;
  GridRectUnion(&local_30,rect,other);
  iVar1 = *piVar2;
  rect->left = local_30.left;
  rect->top = local_30.top;
  rect->width = local_30.width;
  rect->height = local_30.height;
  if (local_1c == iVar1) {
    return rect;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

