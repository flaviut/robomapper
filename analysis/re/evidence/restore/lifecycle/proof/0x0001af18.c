/* Decompiled C, NOT recovered source; need not compile.
 * Binary: WatchDoge
 * SHA256: 3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6
 * Function VA: 0x0001af18
 */

undefined4 FUN_0001af18(void)

{
  undefined4 in_r3;
  undefined8 uVar1;
  
  uVar1 = get_cur_time_ms();
  __printf_chk(1,&UNK_00020a7c,(int)uVar1,(int)((ulonglong)uVar1 >> 0x20),in_r3);
  fflush(stdout);
  FUN_0001abd8();
  FUN_0001ad68();
  DAT_000345ec = 1;
  do {
    FUN_0001aec8();
    sleep(8);
  } while (DAT_000345ec != 0);
  FUN_0001ac20();
  return 0;
}

