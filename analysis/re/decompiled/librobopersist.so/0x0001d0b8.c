/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0001d0b8
 */

/* String is log label only; forwards integer flag to buffer-aware PersistLoadMapInfo. It does not
   import an arbitrary pathname. */

bool PersistLoadMapInfo(char *log_label,int flag)

{
  undefined1 uVar1;
  
  if (log_label == (char *)0x0) {
    log_label = &UNK_0001d0fa + DAT_0001d108;
  }
  _rrlogm(0x15,7,0x451,DAT_0001d104 + 0x1d0e6,DAT_0001d100 + 0x1d1f8,DAT_0001d0fc + 0x1d0d0,
          log_label,flag);
  uVar1 = (*(code *)PTR_PersistLoadMapInfo_00033488)(flag);
  return (bool)uVar1;
}

