/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x00017cdc
 */

/* Unlocks selected persistence metadata mutex; does not wait for any asynchronous map writer. */

void UnlockPersistInfo(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  
  puVar5 = (undefined4 *)(DAT_00017d88 + 0x17cee);
  iVar4 = DAT_00017d8c + 0x17cf2;
  uVar2 = *puVar5;
  iVar3 = (int)&DAT_00017d88 + DAT_00017d90;
  uVar6 = param_1;
  _rrlogm(0x15,6,0x8c,iVar4,iVar3,DAT_00017d94 + 0x17cfa,uVar2,param_1);
  iVar1 = GetPersistInfo(param_1);
  if (iVar1 != 0) {
    _rrlogm(0x15,6,0x95,iVar4,iVar3,DAT_00017d98 + 0x17d28,*puVar5,uVar6);
    pthread_mutex_unlock((pthread_mutex_t *)(iVar1 + 0x14));
    _rrlogm(0x15,7,0x97,iVar4,iVar3,DAT_00017d9c + 0x17d48,*puVar5);
    _rrlogm(0x15,7,0x99,iVar4,iVar3,DAT_00017da0 + 0x17d60,*puVar5);
    return;
  }
  _rrlogm(0x15,3,0x90,iVar4,iVar3,DAT_00017da4 + 0x17d7a,uVar2,uVar6);
  return;
}

