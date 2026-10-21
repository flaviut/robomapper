/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrslamdrv.so
 * SHA256: b48f5f56eb1b2d22abbf727725ea558762337f8f0103229d8da6c1ab6275608a
 * Function VA: 0x00021f14
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Storage-relevant rectangle union: empty operands copied from other; otherwise min left/top and
   max extents. Does not validate against allocation dimensions. Geometry helper boundary only. */

GridRect * GridRectUnion(GridRect *out,GridRect *a,GridRect *b)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  
  piVar4 = *(int **)(DAT_00021fcc + 0x21f22 + DAT_00021fd0);
  local_1c = *piVar4;
  iVar1 = FUN_00021da4(a);
  if (iVar1 == 0) {
    iVar1 = FUN_00021da4(b);
    if (iVar1 == 0) {
      iVar1 = GridRectLeft(a);
      iVar2 = GridRectLeft(b);
      local_2c = iVar1;
      if (iVar2 <= iVar1) {
        local_2c = iVar2;
      }
      iVar1 = GridRectTop(a);
      iVar2 = GridRectTop(b);
      local_28 = iVar1;
      if (iVar2 <= iVar1) {
        local_28 = iVar2;
      }
      iVar1 = FUN_00021d30(a);
      iVar2 = FUN_00021d30(b);
      local_24 = iVar1;
      if (iVar1 < iVar2) {
        local_24 = iVar2;
      }
      iVar1 = FUN_00021d40(a);
      iVar2 = FUN_00021d40(b);
      local_20 = iVar1;
      if (iVar1 < iVar2) {
        local_20 = iVar2;
      }
      FUN_00021cec(out,&local_2c,&local_24);
    }
    else {
      iVar1 = a->top;
      iVar2 = a->width;
      iVar3 = a->height;
      out->left = a->left;
      out->top = iVar1;
      out->width = iVar2;
      out->height = iVar3;
    }
  }
  else {
    iVar1 = b->top;
    iVar2 = b->width;
    iVar3 = b->height;
    out->left = b->left;
    out->top = iVar1;
    out->width = iVar2;
    out->height = iVar3;
  }
  if (local_1c == *piVar4) {
    return out;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

