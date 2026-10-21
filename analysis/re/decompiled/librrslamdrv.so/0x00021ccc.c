/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrslamdrv.so
 * SHA256: b48f5f56eb1b2d22abbf727725ea558762337f8f0103229d8da6c1ab6275608a
 * Function VA: 0x00021ccc
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Zeros four 32-bit words; r0 remains rect. In-memory rectangle only, not packed file header. */

GridRect * GridRectClear(GridRect *rect)

{
  rect->left = 0;
  rect->top = 0;
  rect->width = 0;
  rect->height = 0;
  return rect;
}

