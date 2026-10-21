/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrslamdrv.so
 * SHA256: b48f5f56eb1b2d22abbf727725ea558762337f8f0103229d8da6c1ab6275608a
 * Function VA: 0x00021d28
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Returns in-memory rectangle left word at +0; geometry/copy callers use signed comparisons. File
   dimensions are raw LE uint32 words, not a cast of this type. */

int GridRectLeft(GridRect *rect)

{
  return rect->left;
}

