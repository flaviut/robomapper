/* Decompiled C, NOT recovered source; need not compile.
 * Binary: WatchDoge
 * SHA256: 3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6
 * Function VA: 0x0001ec38
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Builds packet and calls SendPacket, logging failures but returning no delivery status. Event-8
   dispatcher calls with message_id 0x03070343, payload NULL, size 0 after exclusions reload.
   Existence of this send is confirmed; delivery, correlation and writer-exit guarantees are not. */

void WdogSendIpcPacket(uint message_id,void *payload,uint payload_size)

{
  int iVar1;
  int *piVar2;
  undefined8 uVar3;
  undefined4 local_74;
  uint local_70 [2];
  uint local_68;
  undefined1 auStack_64 [64];
  int local_24;
  
  local_24 = __stack_chk_guard;
  local_74 = 1;
  memset(local_70,0,0x4c);
  local_70[0] = message_id;
  local_68 = payload_size;
  if (payload != (void *)0x0) {
    __memcpy_chk(auStack_64,payload,payload_size,0x40);
  }
  iVar1 = SendPacket(local_70,&local_74);
  if (iVar1 < 0) {
    uVar3 = get_cur_time_ms();
    piVar2 = __errno_location();
    __printf_chk(1,"%llu,wdog,#11798`%d`%d\n",(int)uVar3,(int)((ulonglong)uVar3 >> 0x20),iVar1,
                 *piVar2);
    fflush(stdout);
  }
  else {
    uVar3 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11799`%d\n",(int)uVar3,(int)((ulonglong)uVar3 >> 0x20),message_id);
    fflush(stdout);
  }
  if (local_24 == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

