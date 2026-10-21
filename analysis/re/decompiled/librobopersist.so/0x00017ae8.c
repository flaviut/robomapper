/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x00017ae8
 */

/* Selects persistence metadata by integer persistence type. Do not confuse type 0 with a
   filename/map destination flag. */

int GetPersistInfo(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  
  puVar4 = (undefined4 *)(DAT_00017ba8 + 0x17afe);
  iVar3 = DAT_00017bac + 0x17b02;
  iVar2 = DAT_00017bb0 + 0x17b7a;
  iVar5 = param_1;
  _rrlogm(0x15,6,0x57,iVar3,iVar2,DAT_00017bb4 + 0x17b0c,*puVar4,param_1);
  iVar1 = TryOpenSharedRegion(7);
  if (iVar1 == 0) {
    _rrlogm(0x15,7,0x5c,iVar3,iVar2,DAT_00017bc8 + 0x17b74,*puVar4,iVar5);
    iVar1 = InitPersistInfoGroup();
  }
  if (param_1 < 10) {
    iVar1 = param_1 * 0x468 + iVar1;
  }
  else {
    iVar1 = 0;
    _rrlogm(0x15,3,0x62,DAT_00017bd4 + 0x17ba0,DAT_00017bcc + 0x17bfe,DAT_00017bd0 + 0x17b98,param_1
            ,10);
  }
  _rrlogm(0x15,7,0x6a,DAT_00017bc4 + 0x17b56,(int)&DAT_00017bb4 + DAT_00017bbc,
          DAT_00017bc0 + 0x17b4c,*(undefined4 *)(DAT_00017bb8 + 0x17b40),param_1);
  return iVar1;
}

