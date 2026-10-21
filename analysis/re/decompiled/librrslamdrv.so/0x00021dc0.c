/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrslamdrv.so
 * SHA256: b48f5f56eb1b2d22abbf727725ea558762337f8f0103229d8da6c1ab6275608a
 * Function VA: 0x00021dc0
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Preserves dimensions; left=-trunc(width/2), top=-trunc(height/2). Used by storage buffer
   initialization/reset. Does not copy prior origin. */

GridRect * GridCenteredRect(GridRect *out,GridRect *bounds)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  GridSize local_24;
  int local_1c;
  
  piVar3 = *(int **)(DAT_00021e24 + 0x21dc8 + DAT_00021e28);
  local_1c = *piVar3;
  iVar1 = GridRectWidth(bounds);
  iVar2 = GridRectHeight(bounds);
  local_24.width = GridRectWidth(bounds);
  local_24.height = GridRectHeight(bounds);
  GridRectSet(out,-(iVar1 / 2),-(iVar2 / 2),&local_24);
  if (local_1c == *piVar3) {
    return out;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

