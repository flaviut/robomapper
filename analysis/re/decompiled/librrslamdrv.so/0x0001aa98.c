/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrslamdrv.so
 * SHA256: b48f5f56eb1b2d22abbf727725ea558762337f8f0103229d8da6c1ab6275608a
 * Function VA: 0x0001aa98
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Re-centers full bounds preserving dimensions via 0x21dc0; zeroes active view at metadata+0x10;
   fills bounds.width*bounds.height target bytes with *fill. Invoked only after v2 digest comparison
   passes. No allocation/resize/bounds check here. */

void GridResetCells(GridBufferRef *grid,uchar *fill)

{
  uint uVar1;
  uchar *puVar2;
  uchar *puVar3;
  GridCacheMeta *pGVar4;
  int *piVar5;
  GridRect local_40;
  GridRect local_2c;
  int local_1c;
  
  piVar5 = *(int **)(DAT_0001ab04 + 0x1aaa0 + DAT_0001ab08);
  pGVar4 = grid->metadata;
  local_1c = *piVar5;
  GridCenteredRect(&local_40,&pGVar4->bounds);
  (pGVar4->bounds).left = local_40.left;
  (pGVar4->bounds).top = local_40.top;
  (pGVar4->bounds).width = local_40.width;
  (pGVar4->bounds).height = local_40.height;
  GridRectClear(&local_2c);
  puVar3 = grid->cells;
  pGVar4 = grid->metadata;
  (pGVar4->view).left = local_2c.left;
  (pGVar4->view).top = local_2c.top;
  (pGVar4->view).width = local_2c.width;
  (pGVar4->view).height = local_2c.height;
  uVar1 = GridRectCellCount(&pGVar4->bounds);
  puVar2 = puVar3 + uVar1;
  for (; puVar3 != puVar2; puVar3 = puVar3 + 1) {
    *puVar3 = *fill;
  }
  if (local_1c != *piVar5) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}

