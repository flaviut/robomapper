/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrslamdrv.so
 * SHA256: b48f5f56eb1b2d22abbf727725ea558762337f8f0103229d8da6c1ab6275608a
 * Function VA: 0x00021d0c
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Stores left/top at0/4 and two size words at8/12; returns rect. In-memory aligned rectangle,
   distinct from file header offsets. */

GridRect * GridRectSet(GridRect *rect,int left,int top,GridSize *size)

{
  int iVar1;
  int iVar2;
  
  rect->left = left;
  iVar1 = size->width;
  iVar2 = size->height;
  rect->top = top;
  rect->width = iVar1;
  rect->height = iVar2;
  return rect;
}

