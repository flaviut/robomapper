/* Decompiled C, NOT recovered source; need not compile.
 * Binary: WatchDoge
 * SHA256: 3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6
 * Function VA: 0x0001e09c
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* DESTRUCTIVE event-9 helper: unlinks Wi-Fi/device/config files, upload flag, exclusions, endpoint
   files and invokes rm -rf on rriot directory. No result checks. Caller kills three network-client
   names before this call and falls through to exclusions reload afterward. Bounded analysis of side
   effects only; not a map-restore or safe re-enable operation. */

void WdogResetConfigFiles(void)

{
  int iVar1;
  int iVar2;
  char acStack_214 [512];
  int local_14;
  
  iVar1 = DAT_0001e214;
  iVar2 = DAT_0001e214 + -0x504;
  local_14 = __stack_chk_guard;
  memset(acStack_214,0,0x200);
  __snprintf_chk(acStack_214,0x3f,1,0x200,"%s/miio/wifi.conf",iVar1);
  unlink(acStack_214);
  __snprintf_chk(acStack_214,0x3f,1,0x200,"%s/miio/device.uid",iVar1);
  unlink(acStack_214);
  __snprintf_chk(acStack_214,0x3f,1,0x200,"%s/miio/device.token",iVar1);
  unlink(acStack_214);
  __snprintf_chk(acStack_214,0x3f,1,0x200,"%s/miio/device.country",iVar1);
  unlink(acStack_214);
  __snprintf_chk(acStack_214,0x3f,1,0x200,"%s/miio/config.db",iVar1);
  unlink(acStack_214);
  __snprintf_chk(acStack_214,0x3f,1,0x200,"rm -rf %s/rriot",iVar1);
  system(acStack_214);
  __snprintf_chk(acStack_214,0x3f,1,0x200,"%s/rockrobo/rrlog/upload_en",iVar1);
  unlink(acStack_214);
  __snprintf_chk(acStack_214,0x3f,1,0x200,"%s/rockrobo/exclude_process.conf",iVar1);
  unlink(acStack_214);
  __snprintf_chk(acStack_214,0x3f,1,0x200,"%s/endpoint.bin",iVar2);
  unlink(acStack_214);
  __snprintf_chk(acStack_214,0x3f,1,0x200,"%s/endpoint.bin.old",iVar2);
  unlink(acStack_214);
  if (local_14 == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

