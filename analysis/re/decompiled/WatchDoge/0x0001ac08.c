/* Decompiled C, NOT recovered source; need not compile.
 * Binary: WatchDoge
 * SHA256: 3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6
 * Function VA: 0x0001ac08
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Tail-calls pthread_create(&thread_id_at_0x345e4,NULL,(start_routine)0x1af19,NULL). Actual Thumb
   candidate entry is EVEN 0x1af18, first bytes 38b503f00dfc, but no baseline function/instructions
   exist there. No function was guessed/created. See discovery-run/instructions.txt and
   evidence.json. pthread_create result is not checked by startup. */

int WdogHwStartFeeder(void)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_pthread_create_00034290)(&DAT_000345e4,0,0x1af19);
  return iVar1;
}

