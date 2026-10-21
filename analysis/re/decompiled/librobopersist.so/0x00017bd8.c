/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x00017bd8
 */

/* Returns metadata pointer or null; locks its +0x14 mutex. EOWNERDEAD (0x82) invokes
   pthread_mutex_consistent. Other errors are logged; a non-null return alone is not proof of
   successful locking. */

void * LockPersistInfo(int persistence_type)

{
  void *pvVar1;
  int iVar2;
  __pid_t _Var3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  
  uVar4 = *(undefined4 *)(DAT_00017cb4 + 0x17be4);
  iVar6 = DAT_00017cb8 + 0x17bf0;
  iVar5 = DAT_00017cbc + 0x17c76;
  iVar2 = persistence_type;
  _rrlogm(0x15,6,0x70,iVar6,iVar5,DAT_00017cc0 + 0x17bfa,uVar4,persistence_type);
  pvVar1 = (void *)GetPersistInfo(persistence_type);
  if (pvVar1 == (void *)0x0) {
    _rrlogm(0x15,4,0x74,iVar6,iVar5,DAT_00017cd8 + 0x17ca8,uVar4,iVar2);
  }
  else {
    iVar2 = pthread_mutex_lock((pthread_mutex_t *)((int)pvVar1 + 0x14));
    if ((iVar2 != 0) && (rr_event_int(1,1,iVar2), iVar2 == 0x82)) {
      iVar2 = pthread_mutex_consistent((pthread_mutex_t *)((int)pvVar1 + 0x14));
      _Var3 = getpid();
      _rrlogm(0x15,6,0x7f,iVar6,iVar5,DAT_00017cd4 + 0x17c7c,_Var3,iVar2);
      if (iVar2 != 0) {
        rr_event_int(1,2,iVar2);
      }
    }
    _rrlogm(0x15,7,0x86,DAT_00017cd0 + 0x17c44,&UNK_00017cb2 + DAT_00017cc8,DAT_00017ccc + 0x17c3c,
            *(undefined4 *)(DAT_00017cc4 + 0x17c2e),persistence_type);
  }
  return pvVar1;
}

