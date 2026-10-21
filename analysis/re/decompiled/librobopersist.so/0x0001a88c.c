/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0001a88c
 */

/* Tests bit (flag+8) using ARM register logical shift; no range validation. Returns exactly 0 or 1.
    */

uint CheckMapFlagMask(uint destination_mask,int flag)

{
  return destination_mask >> (flag + 8U & 0xff) & 1;
}

