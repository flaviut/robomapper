/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x00055500
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Save-maps result handler: length must equal 16; result word +0x18==1 advances pending series,
   otherwise fails series. Legacy catalog/DB handling only when no pending series handled request.
   Persistence acceptance is not background writer completion. */

void MapFlowHandleSaveSetResult(void *proxy,void *message)

{
  undefined4 uVar1;
  uint uVar2;
  void *series;
  int iVar3;
  time_t tVar4;
  uint uVar5;
  uint reserved_r1;
  int iVar6;
  undefined8 uVar7;
  allocator aaStack_84 [4];
  undefined1 auStack_80 [4];
  int local_7c;
  uint local_78;
  uint uStack_74;
  int local_70;
  int local_6c;
  undefined1 auStack_68 [8];
  int local_60;
  int iStack_5c;
  int local_24;
  
  local_24 = __stack_chk_guard;
  if (*(int *)((int)message + 8) == 0x10) {
    uVar1 = FUN_0007d574();
    FUN_0007ced8(uVar1,1);
    FUN_00026228(0x5457,DAT_00055818,5,6,"#10577");
    uVar2 = *(uint *)((int)message + 0xc);
    uVar5 = *(uint *)((int)message + 0x10);
    local_70 = *(int *)((int)message + 0x14);
    iVar6 = *(int *)((int)message + 0x18);
    local_78 = uVar2;
    uStack_74 = uVar5;
    local_6c = iVar6;
    FUN_00026228(0x545c,DAT_00055818,2,6,"#10578`%llu`%d");
    if (iVar6 == 1) {
      uVar7 = FUN_0006f064();
      iVar6 = MapFlowAdvanceSeries((void *)uVar7,(uint)((ulonglong)uVar7 >> 0x20),uVar2,uVar5);
      uVar2 = local_78;
      uVar5 = uStack_74;
    }
    else {
      series = (void *)FUN_0006f064();
      std::string::string((string *)&local_7c,"save maps result failed!",aaStack_84);
      iVar6 = MapFlowFailSeries(series,reserved_r1,uVar2,uVar5,(string *)&local_7c);
      uVar2 = local_78;
      uVar5 = uStack_74;
      if ((undefined1 *)(local_7c + -0xc) != std::string::_Rep::_S_empty_rep_storage) {
        FUN_00037650((undefined1 *)(local_7c + -0xc),auStack_80);
        uVar2 = local_78;
        uVar5 = uStack_74;
      }
    }
    local_78 = uVar2;
    uStack_74 = uVar5;
    if (iVar6 == 0) {
      FUN_0003e668(proxy);
      FUN_0003c470(auStack_68,proxy,uVar2,uVar5);
      if ((uVar2 == 0 && uVar5 == 0) || (local_6c != 1)) {
        if (iStack_5c != 0 || local_60 != 0) {
          FUN_0004ad88(proxy,auStack_68,0xffffd8ea,"Save map failed");
        }
      }
      else {
        if (*(int *)((int)proxy + 0xf0c) != -1) {
          SetSharedCurrentMapFlag();
        }
        iVar6 = local_70;
        iVar3 = rr_check_mapflag_is_multimap(local_70);
        if (((iVar3 == 0) && (iVar3 = InsertMultiMap(iVar6), iVar3 == 0)) &&
           (iStack_5c != 0 || local_60 != 0)) {
          FUN_0004ad88(proxy,auStack_68,0xffffd8ea,"Save map failed");
        }
        MapFlowWriteBackupDb(proxy,iVar6);
        if (uVar5 == *(uint *)((int)proxy + 0xb04) && uVar2 == *(uint *)((int)proxy + 0xb00)) {
          FUN_0003f70c(proxy,(int)proxy + 0xaf8,(int)proxy + 0x3df0);
        }
        else if ((uVar5 == *(uint *)((int)proxy + 0xa14) && uVar2 == *(uint *)((int)proxy + 0xa10))
                && (*(char *)((int)proxy + 0x1470) != '\0')) {
          FUN_0003f70c(proxy,(int)proxy + 0xa08,(int)proxy + 0x1470);
        }
        else if (iStack_5c != 0 || local_60 != 0) {
          MapFlowReplyOk(proxy,auStack_68,&DAT_000f3398);
        }
      }
      *(undefined4 *)((int)proxy + 0xc38) = 0;
      *(undefined4 *)((int)proxy + 0xc40) = 0;
      *(undefined4 *)((int)proxy + 0xc44) = 0;
      *(undefined4 *)((int)proxy + 0x8c8) = 0;
      *(undefined4 *)((int)proxy + 0x8d0) = 0;
      *(undefined4 *)((int)proxy + 0x8d4) = 0;
      *(undefined4 *)((int)proxy + 0x918) = 0;
      *(undefined4 *)((int)proxy + 0x920) = 0;
      *(undefined4 *)((int)proxy + 0x924) = 0;
      *(undefined4 *)((int)proxy + 0xa08) = 0;
      *(undefined4 *)((int)proxy + 0xa10) = 0;
      *(undefined4 *)((int)proxy + 0xa14) = 0;
      *(undefined4 *)((int)proxy + 0xaf8) = 0;
      *(undefined4 *)((int)proxy + 0xb00) = 0;
      *(undefined4 *)((int)proxy + 0xb04) = 0;
      *(undefined4 *)((int)proxy + 0xc88) = 0;
      *(undefined4 *)((int)proxy + 0xc90) = 0;
      *(undefined4 *)((int)proxy + 0xc94) = 0;
      *(undefined4 *)((int)proxy + 0xdc8) = 0;
      *(undefined4 *)((int)proxy + 0xdd0) = 0;
      *(undefined4 *)((int)proxy + 0xdd4) = 0;
      FUN_0003a714(proxy,0);
      *(undefined4 *)((int)proxy + 0xf0c) = 0xffffffff;
      pthread_mutex_lock((pthread_mutex_t *)((int)proxy + 0xf54));
      tVar4 = time((time_t *)0x0);
      *(time_t *)((int)proxy + 0xf6c) = tVar4;
      pthread_mutex_unlock((pthread_mutex_t *)((int)proxy + 0xf54));
    }
  }
  else {
    FUN_00026228(0x544d,DAT_00055818,2,6,"#10576");
    *(undefined4 *)((int)proxy + 0xc38) = 0;
    *(undefined4 *)((int)proxy + 0xc40) = 0;
    *(undefined4 *)((int)proxy + 0xc44) = 0;
    *(undefined4 *)((int)proxy + 0x8c8) = 0;
    *(undefined4 *)((int)proxy + 0x8d0) = 0;
    *(undefined4 *)((int)proxy + 0x8d4) = 0;
    *(undefined4 *)((int)proxy + 0x918) = 0;
    *(undefined4 *)((int)proxy + 0x920) = 0;
    *(undefined4 *)((int)proxy + 0x924) = 0;
    *(undefined4 *)((int)proxy + 0xa08) = 0;
    *(undefined4 *)((int)proxy + 0xa10) = 0;
    *(undefined4 *)((int)proxy + 0xa14) = 0;
    *(undefined4 *)((int)proxy + 0xaf8) = 0;
    *(undefined4 *)((int)proxy + 0xb00) = 0;
    *(undefined4 *)((int)proxy + 0xb04) = 0;
    *(undefined4 *)((int)proxy + 0xc88) = 0;
    *(undefined4 *)((int)proxy + 0xc90) = 0;
    *(undefined4 *)((int)proxy + 0xc94) = 0;
    *(undefined4 *)((int)proxy + 0xdc8) = 0;
    *(undefined4 *)((int)proxy + 0xdd0) = 0;
    *(undefined4 *)((int)proxy + 0xdd4) = 0;
    FUN_0003a714(proxy,0);
    *(undefined4 *)((int)proxy + 0xf0c) = 0xffffffff;
  }
  if (local_24 == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

