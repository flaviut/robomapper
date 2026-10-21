/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0001c578
 */

/* String is a log label, NOT an arbitrary output pathname. Constructs one-element destination-flag
   vector and forwards to vector PersistSaveMapInfo. Boolean return is enqueue/no-op result, not
   file completion. */

bool PersistSaveMapInfo(char *log_label,int flag)

{
  bool bVar1;
  int *piVar2;
  int *local_2c;
  int *local_28;
  int *local_24;
  int local_20;
  int local_1c;
  
  piVar2 = *(int **)(DAT_0001c608 + 0x1c580 + DAT_0001c60c);
  local_1c = *piVar2;
  if (log_label == (char *)0x0) {
    log_label = (char *)(DAT_0001c61c + 0x1c5f6);
  }
  _rrlogm(0x15,7,1099,DAT_0001c618 + 0x1c5b2,DAT_0001c614 + 0x1c682,DAT_0001c610 + 0x1c59e,log_label
          ,flag);
  local_2c = (int *)0x0;
  local_28 = (int *)0x0;
  local_24 = (int *)0x0;
  local_20 = flag;
  local_2c = operator_new(4);
  local_28 = local_2c + 1;
  *local_2c = local_20;
  local_24 = local_28;
  bVar1 = PersistSaveMapInfo(&local_2c);
  if (local_2c != (int *)0x0) {
    operator_delete(local_2c);
  }
  if (local_1c == *piVar2) {
    return bVar1;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

