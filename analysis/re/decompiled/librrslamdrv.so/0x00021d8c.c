/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrslamdrv.so
 * SHA256: b48f5f56eb1b2d22abbf727725ea558762337f8f0103229d8da6c1ab6275608a
 * Function VA: 0x00021d8c
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Returns low 32 bits of width*height; no overflow validation. */

uint GridRectCellCount(GridRect *rect)

{
  int iVar1;
  int iVar2;
  
  iVar1 = GridRectWidth(rect);
  iVar2 = GridRectHeight(rect);
  return iVar2 * iVar1;
}

