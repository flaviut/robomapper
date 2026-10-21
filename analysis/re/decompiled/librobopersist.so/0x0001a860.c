/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0001a860
 */

/* Builds unsigned destination mask by ORing ARM register shifts 1 << (signed_flag+8). This is not
   1<<flag. Negative temporary flag -2 maps to bit 6; no range validation occurs here. Input is
   opaque ABI pointer to existing flag vector; no MapPersistFlag type owned here. */

uint ConvertMapFlagMask(void *flags_vector)

{
  uint uVar1;
  int *piVar2;
  int *piVar3;
  
  if (*(int **)flags_vector != *(int **)((int)flags_vector + 4)) {
    uVar1 = 0;
    piVar2 = *(int **)flags_vector;
    do {
      piVar3 = piVar2 + 1;
      uVar1 = uVar1 | 1 << (*piVar2 + 8U & 0xff);
      piVar2 = piVar3;
    } while (*(int **)((int)flags_vector + 4) != piVar3);
    return uVar1;
  }
  return 0;
}

