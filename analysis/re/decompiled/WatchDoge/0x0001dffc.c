/* Decompiled C, NOT recovered source; need not compile.
 * Binary: WatchDoge
 * SHA256: 3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6
 * Function VA: 0x0001dffc
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* fopen(exclusions path,"w") truncates existing file, fprintf("%s",payload), fclose. Open or
   empty/failed write only logs; no status reaches caller and no fsync/atomic rename. Packet length
   is not passed. Do not confuse this path with map-file persistence. */

void WdogWriteExclusions(char *payload)

{
  FILE *pFVar1;
  int iVar2;
  undefined8 uVar3;
  
  pFVar1 = fopen("/mnt/data/rockrobo/exclude_process.conf","w");
  if (pFVar1 == (FILE *)0x0) {
    uVar3 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11698`%s\n",(int)uVar3,(int)((ulonglong)uVar3 >> 0x20),
                 "/mnt/data/rockrobo/exclude_process.conf");
    (*(code *)PTR_fflush_00034214)(stdout);
    return;
  }
  iVar2 = __fprintf_chk(pFVar1,1,"%s",payload);
  if (iVar2 < 1) {
    uVar3 = get_cur_time_ms();
    __printf_chk(1,"%llu,wdog,#11697`%s`%d\n",(int)uVar3,(int)((ulonglong)uVar3 >> 0x20),
                 "/mnt/data/rockrobo/exclude_process.conf",iVar2);
    fflush(stdout);
  }
  (*(code *)PTR_fclose_0003407c)(pFVar1);
  return;
}

