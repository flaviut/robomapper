/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrslamdrv.so
 * SHA256: b48f5f56eb1b2d22abbf727725ea558762337f8f0103229d8da6c1ab6275608a
 * Function VA: 0x0002bc4c
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Stores low byte only (strb r1,[r0]); storage initializes unknown cells with0x80. Exact
   occupancy-to-probability mapping remains unknown. */

void GridCellSet(uchar *cell,uint value)

{
  *cell = (uchar)value;
  return;
}

