/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x00017a70
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Metadata backing is shared region 7, size 0x2c10: ten 0x468-byte records initialized only when
   region is absent. Legacy shared region 4 is removed if present. */

PersistInfo * InitPersistInfoGroup(void)

{
  int iVar1;
  PersistInfo *pPVar2;
  PersistInfo *pPVar3;
  
  iVar1 = ExistSharedRegion(7);
  pPVar2 = (PersistInfo *)GetSharedRegion(7,0x2c10);
  if (iVar1 == 0) {
    _rrlogm(0x15,7,0x3d,DAT_00017ae4 + 0x17abc,DAT_00017adc + 0x17b0e,DAT_00017ae0 + 0x17aba);
    iVar1 = 0;
    pPVar3 = pPVar2;
    do {
      InitPersistInfo(pPVar3);
      *(short *)pPVar3 = (short)iVar1;
      iVar1 = iVar1 + 1;
      pPVar3 = pPVar3 + 0x468;
    } while (iVar1 != 10);
  }
  iVar1 = ExistSharedRegion(4);
  if (iVar1 != 0) {
    GetSharedRegion(4,0x468);
    DestroySharedRegion(4);
  }
  return pPVar2;
}

