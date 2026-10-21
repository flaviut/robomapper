/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrslamdrv.so
 * SHA256: b48f5f56eb1b2d22abbf727725ea558762337f8f0103229d8da6c1ab6275608a
 * Function VA: 0x00003b64
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* ABI correction only, preserving surviving std::istream::read symbol. Storage callsites pass
   this=r0, buffer=r1, count=r2. Demangler-imported two-argument prototype omitted implicit this.
   Not an original C++ class declaration. */

void * std::istream::read(void *stream,void *bytes,int length)

{
  void *pvVar1;
  
  pvVar1 = (void *)(*(code *)PTR_read_000541b8)(stream);
  return pvVar1;
}

