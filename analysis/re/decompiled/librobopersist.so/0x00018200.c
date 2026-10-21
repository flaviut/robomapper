/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x00018200
 */

/* Invokes subscribed callback if present. Observed stage integers: 0 before restore, 1 after
   restore, 2 before snapshot copy, 3 after snapshot copy. Callback semantics beyond these
   boundaries are unknown. */

void RunPersistSharedRegionCallback(undefined4 *param_1,undefined4 param_2)

{
  longlong lVar1;
  longlong lVar2;
  
  if (param_1[8] == 0) {
    return;
  }
  lVar1 = get_cur_time_ms();
  (*(code *)param_1[8])(param_2);
  lVar2 = get_cur_time_ms();
  lVar2 = lVar2 - lVar1;
  if ((int)((ulonglong)lVar2 >> 0x20) == 0 && (uint)lVar2 < 500) {
    return;
  }
  _rrlogm(0x15,4,0x134,DAT_00018268 + 0x18254,DAT_00018260 + 0x1832c,DAT_00018264 + 0x1824a,*param_1
          ,param_2,lVar2);
  return;
}

