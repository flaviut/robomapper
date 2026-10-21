/* Decompiled C, NOT recovered source; need not compile.
 * Binary: WatchDoge
 * SHA256: 3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6
 * Function VA: 0x0001e75c
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Internal SysV queue key 0x80001000; message type 1, four-byte event payload, msgsnd flags 0x800
   (nonblocking). Returns send-success boolean; IPC receiver ignores it. Queueing does not imply
   event completion or writer quiescence. */

int WdogQueueEvent(uint event_code)

{
  int iVar1;
  undefined4 local_14;
  uint local_10;
  int local_c;
  
  local_14 = 1;
  local_c = __stack_chk_guard;
  local_10 = event_code;
  iVar1 = msgget(-0x7ffff000,0x3b6);
  iVar1 = msgsnd(iVar1,&local_14,4,0x800);
  if (local_c == __stack_chk_guard) {
    return (uint)(iVar1 != -1);
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

