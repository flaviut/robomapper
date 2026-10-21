/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x00069c88
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Single-map result handler used for series continuation: length 16 and result +0x18==1 advances
   series, else fails it. Diagnostic strings confusingly say load map result failed; do not identify
   operation solely from those strings. Legacy paths are distinct from queued load/recovery path. */

void MapFlowHandleSaveResult(void *proxy,void *message)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  void *pvVar4;
  int iVar5;
  time_t tVar6;
  FILE *__stream;
  int iVar7;
  uint reserved_r1;
  uint uVar8;
  undefined4 *puVar9;
  undefined8 uVar10;
  allocator aaStack_ac [4];
  void *local_a8;
  void *local_a4;
  void *local_a0;
  void *local_9c [3];
  uint local_90;
  uint uStack_8c;
  int local_88;
  int local_84;
  undefined4 local_7c [2];
  undefined4 local_74;
  undefined4 local_70;
  undefined1 local_30 [4];
  int local_2c;
  
  local_2c = __stack_chk_guard;
  if (*(int *)((int)message + 8) != 0x10) {
    FUN_00026228(0x318f,DAT_00069f28,2,6,"#9979");
    FUN_0003a714(proxy,0);
    *(undefined4 *)((int)proxy + 0xc38) = 0;
    *(undefined4 *)((int)proxy + 0xc40) = 0;
    *(undefined4 *)((int)proxy + 0xc44) = 0;
    *(undefined4 *)((int)proxy + 0x8c8) = 0;
    *(undefined4 *)((int)proxy + 0x8d0) = 0;
    *(undefined4 *)((int)proxy + 0x8d4) = 0;
    *(undefined4 *)((int)proxy + 0x918) = 0;
    *(undefined4 *)((int)proxy + 0x920) = 0;
    *(undefined4 *)((int)proxy + 0x924) = 0;
    *(undefined4 *)((int)proxy + 0xaf8) = 0;
    *(undefined4 *)((int)proxy + 0xb00) = 0;
    *(undefined4 *)((int)proxy + 0xb04) = 0;
    *(undefined4 *)((int)proxy + 0xa08) = 0;
    *(undefined4 *)((int)proxy + 0xa10) = 0;
    *(undefined4 *)((int)proxy + 0xa14) = 0;
    *(undefined4 *)((int)proxy + 0x968) = 0;
    *(undefined4 *)((int)proxy + 0x970) = 0;
    *(undefined4 *)((int)proxy + 0x974) = 0;
    *(undefined4 *)((int)proxy + 0xf00) = 0;
    *(undefined4 *)((int)proxy + 0xc88) = 0;
    *(undefined4 *)((int)proxy + 0xc90) = 0;
    *(undefined4 *)((int)proxy + 0xc94) = 0;
    *(undefined4 *)((int)proxy + 0xd78) = 0;
    *(undefined4 *)((int)proxy + 0xd80) = 0;
    *(undefined4 *)((int)proxy + 0xd84) = 0;
    *(undefined4 *)((int)proxy + 0xdc8) = 0;
    *(undefined4 *)((int)proxy + 0xdd0) = 0;
    *(undefined4 *)((int)proxy + 0xdd4) = 0;
    *(undefined4 *)((int)proxy + 0xe68) = 0;
    *(undefined4 *)((int)proxy + 0xe70) = 0;
    *(undefined4 *)((int)proxy + 0xe74) = 0;
    goto LAB_00069d44;
  }
  uVar3 = FUN_0007d574();
  FUN_0007ced8(uVar3,1);
  FUN_00026228(0x31a3,DAT_00069f28,5,6,"#9980");
  local_90 = *(uint *)((int)message + 0xc);
  local_84 = *(int *)((int)message + 0x18);
  uStack_8c = *(uint *)((int)message + 0x10);
  local_88 = *(int *)((int)message + 0x14);
  if (local_84 == 1) {
    uVar10 = FUN_0006f064();
    iVar5 = MapFlowAdvanceSeries
                      ((void *)uVar10,(uint)((ulonglong)uVar10 >> 0x20),local_90,uStack_8c);
    uVar1 = local_90;
    uVar2 = uStack_8c;
  }
  else {
    pvVar4 = (void *)FUN_0006f064();
    uVar2 = uStack_8c;
    uVar1 = local_90;
    std::string::string((string *)local_9c,"load map result failed!",aaStack_ac);
    iVar5 = MapFlowFailSeries(pvVar4,reserved_r1,uVar1,uVar2,(string *)local_9c);
    uVar1 = local_90;
    uVar2 = uStack_8c;
    if ((undefined1 *)((int)local_9c[0] + -0xc) != std::string::_Rep::_S_empty_rep_storage) {
      FUN_00037650((undefined1 *)((int)local_9c[0] + -0xc),&local_a8);
      uVar1 = local_90;
      uVar2 = uStack_8c;
    }
  }
  local_90 = uVar1;
  uStack_8c = uVar2;
  if (iVar5 != 0) goto LAB_00069d44;
  if ((uVar1 == 0 && uVar2 == 0) || (local_84 != 1)) {
    FUN_00026228(0x3310,DAT_00069f28,2,6,"#9994");
    FUN_0003a714(proxy,0);
    if (uVar2 == *(uint *)((int)proxy + 0xc44) && uVar1 == *(uint *)((int)proxy + 0xc40)) {
      FUN_0004ad88(proxy,(int)proxy + 0xc38,0xffffd8ea,"Save map failed");
      *(undefined4 *)((int)proxy + 0xc38) = 0;
      *(uint *)((int)proxy + 0xc40) = 0;
      *(undefined4 *)((int)proxy + 0xc44) = 0;
    }
    else if (uVar2 == *(uint *)((int)proxy + 0x8d4) && uVar1 == *(uint *)((int)proxy + 0x8d0)) {
      FUN_0004ad88(proxy,(int)proxy + 0x8c8,0xffffd8ea,"Save map failed");
      *(undefined4 *)((int)proxy + 0x8c8) = 0;
      *(uint *)((int)proxy + 0x8d0) = 0;
      *(undefined4 *)((int)proxy + 0x8d4) = 0;
    }
    else if (uVar2 == *(uint *)((int)proxy + 0x924) && uVar1 == *(uint *)((int)proxy + 0x920)) {
      FUN_0004ad88(proxy,(int)proxy + 0x918,0xffffd8ea,"Save map failed");
      *(undefined4 *)((int)proxy + 0x918) = 0;
      *(uint *)((int)proxy + 0x920) = 0;
      *(undefined4 *)((int)proxy + 0x924) = 0;
    }
    else if (uVar2 == *(uint *)((int)proxy + 0xb04) && uVar1 == *(uint *)((int)proxy + 0xb00)) {
      FUN_0004ad88(proxy,(int)proxy + 0xaf8,0xffffd8ea,"Save map failed");
      *(undefined4 *)((int)proxy + 0xaf8) = 0;
      *(uint *)((int)proxy + 0xb00) = 0;
      *(undefined4 *)((int)proxy + 0xb04) = 0;
    }
    else if (uVar2 == *(uint *)((int)proxy + 0xa14) && uVar1 == *(uint *)((int)proxy + 0xa10)) {
      FUN_0004ad88(proxy,(int)proxy + 0xa08,0xffffd8ea,"Save map failed");
      *(undefined4 *)((int)proxy + 0xa08) = 0;
      *(uint *)((int)proxy + 0xa10) = 0;
      *(undefined4 *)((int)proxy + 0xa14) = 0;
    }
    else if (uVar2 == *(uint *)((int)proxy + 0x974) && uVar1 == *(uint *)((int)proxy + 0x970)) {
      FUN_0004ad88(proxy,(int)proxy + 0x968,0xffffd8ea,"Save map failed");
      *(undefined4 *)((int)proxy + 0x968) = 0;
      *(uint *)((int)proxy + 0x970) = 0;
      *(undefined4 *)((int)proxy + 0x974) = 0;
      *(undefined4 *)((int)proxy + 0xf00) = 0;
    }
    else if (uVar2 == *(uint *)((int)proxy + 0xc94) && uVar1 == *(uint *)((int)proxy + 0xc90)) {
      FUN_0004ad88(proxy,(int)proxy + 0xc88,0xffffd8ea,"CustomizeCleanMode failed");
      *(undefined4 *)((int)proxy + 0xc88) = 0;
      *(uint *)((int)proxy + 0xc90) = 0;
      *(undefined4 *)((int)proxy + 0xc94) = 0;
    }
    else if (uVar2 == *(uint *)((int)proxy + 0xd84) && uVar1 == *(uint *)((int)proxy + 0xd80)) {
      FUN_0004ad88(proxy,(int)proxy + 0xd78,0xffffd8ea,"Save as multi map failed");
      *(undefined4 *)((int)proxy + 0xd78) = 0;
      *(uint *)((int)proxy + 0xd80) = 0;
      *(undefined4 *)((int)proxy + 0xd84) = 0;
    }
    else if (uVar2 == *(uint *)((int)proxy + 0xdd4) && uVar1 == *(uint *)((int)proxy + 0xdd0)) {
      FUN_0004ad88(proxy,(int)proxy + 0xdc8,0xffffd8ea,"Save map failed");
      *(undefined4 *)((int)proxy + 0xdc8) = 0;
      *(uint *)((int)proxy + 0xdd0) = 0;
      *(undefined4 *)((int)proxy + 0xdd4) = 0;
    }
    else if (uVar2 == *(uint *)((int)proxy + 0xe74) && uVar1 == *(uint *)((int)proxy + 0xe70)) {
      FUN_0004ad88(proxy,(int)proxy + 0xe68,0xffffd8ea,"Save map failed");
      *(undefined4 *)((int)proxy + 0xe68) = 0;
      *(uint *)((int)proxy + 0xe70) = 0;
      *(undefined4 *)((int)proxy + 0xe74) = 0;
    }
    *(undefined4 *)((int)proxy + 0xf0c) = 0xffffffff;
  }
  else if (uVar2 == *(uint *)((int)proxy + 0x884) && uVar1 == *(uint *)((int)proxy + 0x880)) {
    FUN_00026228(0x31b6,DAT_0006a4fc,2,6,"#9981");
    pthread_mutex_lock((pthread_mutex_t *)((int)proxy + 0x390));
    iVar5 = *(int *)((int)proxy + 0x3a8);
    if (*(int *)((int)proxy + 0x3ac) != iVar5) {
      uVar8 = *(uint *)(iVar5 + 0x14);
      iVar7 = iVar5;
      if ((uVar8 != uVar2 || *(uint *)(iVar5 + 0x10) != uVar1) ||
          *(uint *)(iVar5 + 0x10) == 0 && uVar8 == 0) {
        do {
          iVar5 = iVar7 + 0x50;
          if (*(int *)((int)proxy + 0x3ac) == iVar5) goto LAB_0006a320;
          uVar8 = (uint)(uVar2 == *(uint *)(iVar7 + 100) && uVar1 == *(uint *)(iVar7 + 0x60));
          if (*(uint *)(iVar7 + 100) == 0 && *(uint *)(iVar7 + 0x60) == 0) {
            uVar8 = 0;
          }
          iVar7 = iVar5;
        } while (uVar8 == 0);
      }
      FUN_0006fc30((int)proxy + 0x3a8,uVar8,iVar5);
    }
LAB_0006a320:
    *(undefined4 *)((int)proxy + 0x828) = *(undefined4 *)((int)proxy + 0x878);
    *(undefined4 *)((int)proxy + 0x82c) = *(undefined4 *)((int)proxy + 0x87c);
    *(undefined4 *)((int)proxy + 0x830) = *(undefined4 *)((int)proxy + 0x880);
    *(undefined4 *)((int)proxy + 0x834) = *(undefined4 *)((int)proxy + 0x884);
    *(undefined4 *)((int)proxy + 0x838) = *(undefined4 *)((int)proxy + 0x888);
    *(undefined4 *)((int)proxy + 0x83c) = *(undefined4 *)((int)proxy + 0x88c);
    *(undefined4 *)((int)proxy + 0x840) = *(undefined4 *)((int)proxy + 0x890);
    *(undefined4 *)((int)proxy + 0x844) = *(undefined4 *)((int)proxy + 0x894);
    *(undefined4 *)((int)proxy + 0x848) = *(undefined4 *)((int)proxy + 0x898);
    *(undefined4 *)((int)proxy + 0x84c) = *(undefined4 *)((int)proxy + 0x89c);
    *(undefined4 *)((int)proxy + 0x850) = *(undefined4 *)((int)proxy + 0x8a0);
    *(undefined4 *)((int)proxy + 0x854) = *(undefined4 *)((int)proxy + 0x8a4);
    *(undefined4 *)((int)proxy + 0x858) = *(undefined4 *)((int)proxy + 0x8a8);
    *(undefined4 *)((int)proxy + 0x85c) = *(undefined4 *)((int)proxy + 0x8ac);
    *(undefined4 *)((int)proxy + 0x860) = *(undefined4 *)((int)proxy + 0x8b0);
    *(undefined4 *)((int)proxy + 0x864) = *(undefined4 *)((int)proxy + 0x8b4);
    *(undefined4 *)((int)proxy + 0x820) = *(undefined4 *)((int)proxy + 0x870);
    FUN_0006fb30((int)proxy + 0x3a8,(int)proxy + 0x820);
    pthread_mutex_unlock((pthread_mutex_t *)((int)proxy + 0x390));
    if (*(int *)((int)proxy + 0xf0c) == -1) {
      iVar5 = GetSharedCurrentMapFlag();
      if (iVar5 + 1 == 0) {
        FUN_00026228(0x31cd,DAT_0006ad08,2,6,"#9982");
        FUN_0004ad88(proxy,(undefined4 *)((int)proxy + 0x828),0xffffd8ea,"Save map failed");
        FUN_0003a714(proxy,0);
        goto LAB_00069d44;
      }
      MapFlowSendSave(proxy,iVar5 + 1,*(undefined4 *)((int)proxy + 0x830),
                      *(undefined4 *)((int)proxy + 0x834),iVar5);
    }
    else {
      MapFlowSendSave(proxy);
    }
    *(undefined4 *)((int)proxy + 0x878) = 0;
    *(uint *)((int)proxy + 0x880) = 0;
    *(undefined4 *)((int)proxy + 0x884) = 0;
  }
  else if (uVar2 == *(uint *)((int)proxy + 0xab4) && uVar1 == *(uint *)((int)proxy + 0xab0)) {
    FUN_00026228(0x31d8,DAT_0006a4fc,2,6,"#9983");
    pthread_mutex_lock((pthread_mutex_t *)((int)proxy + 0x390));
    iVar5 = *(int *)((int)proxy + 0x3a8);
    if (*(int *)((int)proxy + 0x3ac) != iVar5) {
      uVar8 = *(uint *)(iVar5 + 0x14);
      iVar7 = iVar5;
      if ((uVar2 != uVar8 || uVar1 != *(uint *)(iVar5 + 0x10)) ||
          *(uint *)(iVar5 + 0x10) == 0 && uVar8 == 0) {
        do {
          iVar5 = iVar7 + 0x50;
          if (*(int *)((int)proxy + 0x3ac) == iVar5) goto LAB_0006a400;
          uVar8 = (uint)(*(uint *)(iVar7 + 0x60) != 0 || *(uint *)(iVar7 + 100) != 0);
          if (uVar2 != *(uint *)(iVar7 + 100) || uVar1 != *(uint *)(iVar7 + 0x60)) {
            uVar8 = 0;
          }
          iVar7 = iVar5;
        } while (uVar8 == 0);
      }
      FUN_0006fc30((int)proxy + 0x3a8,uVar8,iVar5);
    }
LAB_0006a400:
    pthread_mutex_unlock((pthread_mutex_t *)((int)proxy + 0x390));
    *(undefined4 *)((int)proxy + 0xaa8) = 0;
    *(uint *)((int)proxy + 0xab0) = 0;
    *(undefined4 *)((int)proxy + 0xab4) = 0;
  }
  else if (uVar2 == *(uint *)((int)proxy + 0xb54) && uVar1 == *(uint *)((int)proxy + 0xb50)) {
    FUN_00026228(0x31e5,DAT_0006a4fc,2,6,"#9984");
    pthread_mutex_lock((pthread_mutex_t *)((int)proxy + 0x390));
    iVar5 = *(int *)((int)proxy + 0x3a8);
    if (iVar5 != *(int *)((int)proxy + 0x3ac)) {
      uVar8 = *(uint *)(iVar5 + 0x14);
      iVar7 = iVar5;
      if ((uVar2 != uVar8 || uVar1 != *(uint *)(iVar5 + 0x10)) ||
          *(uint *)(iVar5 + 0x10) == 0 && uVar8 == 0) {
        do {
          iVar5 = iVar7 + 0x50;
          if (iVar5 == *(int *)((int)proxy + 0x3ac)) goto LAB_0006a49a;
          uVar8 = (uint)(uVar2 == *(uint *)(iVar7 + 100) && uVar1 == *(uint *)(iVar7 + 0x60));
          if (*(uint *)(iVar7 + 100) == 0 && *(uint *)(iVar7 + 0x60) == 0) {
            uVar8 = 0;
          }
          iVar7 = iVar5;
        } while (uVar8 == 0);
      }
      FUN_0006fc30((int)proxy + 0x3a8,uVar8,iVar5);
    }
LAB_0006a49a:
    *(undefined4 *)((int)proxy + 0xb98) = *(undefined4 *)((int)proxy + 0xb48);
    *(undefined4 *)((int)proxy + 0xb9c) = *(undefined4 *)((int)proxy + 0xb4c);
    *(undefined4 *)((int)proxy + 0xba0) = *(undefined4 *)((int)proxy + 0xb50);
    *(undefined4 *)((int)proxy + 0xba4) = *(undefined4 *)((int)proxy + 0xb54);
    *(undefined4 *)((int)proxy + 0xba8) = *(undefined4 *)((int)proxy + 0xb58);
    *(undefined4 *)((int)proxy + 0xbac) = *(undefined4 *)((int)proxy + 0xb5c);
    *(undefined4 *)((int)proxy + 0xbb0) = *(undefined4 *)((int)proxy + 0xb60);
    *(undefined4 *)((int)proxy + 0xbb4) = *(undefined4 *)((int)proxy + 0xb64);
    *(undefined4 *)((int)proxy + 3000) = *(undefined4 *)((int)proxy + 0xb68);
    *(undefined4 *)((int)proxy + 0xbbc) = *(undefined4 *)((int)proxy + 0xb6c);
    *(undefined4 *)((int)proxy + 0xbc0) = *(undefined4 *)((int)proxy + 0xb70);
    *(undefined4 *)((int)proxy + 0xbc4) = *(undefined4 *)((int)proxy + 0xb74);
    *(undefined4 *)((int)proxy + 0xbc8) = *(undefined4 *)((int)proxy + 0xb78);
    *(undefined4 *)((int)proxy + 0xbcc) = *(undefined4 *)((int)proxy + 0xb7c);
    *(undefined4 *)((int)proxy + 0xbd0) = *(undefined4 *)((int)proxy + 0xb80);
    *(undefined4 *)((int)proxy + 0xbd4) = *(undefined4 *)((int)proxy + 0xb84);
    *(undefined4 *)((int)proxy + 0xb90) = *(undefined4 *)((int)proxy + 0xb40);
    FUN_0006fb30((int)proxy + 0x3a8,(int)proxy + 0xb90);
    pthread_mutex_unlock((pthread_mutex_t *)((int)proxy + 0x390));
    if (*(int *)((int)proxy + 0xf00) == 0) {
      MapFlowSendSave(proxy);
    }
    else {
      MapFlowSendSave(proxy);
    }
    *(undefined4 *)((int)proxy + 0xb48) = 0;
    *(uint *)((int)proxy + 0xb50) = 0;
    *(undefined4 *)((int)proxy + 0xb54) = 0;
  }
  else if (uVar2 == *(uint *)((int)proxy + 0x834) && uVar1 == *(uint *)((int)proxy + 0x830)) {
    FUN_00026228(0x31ff,DAT_0006a7cc,2,6,"#9985");
    FUN_0003a664(proxy);
    pthread_mutex_lock((pthread_mutex_t *)((int)proxy + 0x390));
    iVar5 = *(int *)((int)proxy + 0x3a8);
    if (iVar5 != *(int *)((int)proxy + 0x3ac)) {
      uVar8 = *(uint *)(iVar5 + 0x14);
      iVar7 = iVar5;
      if ((uVar2 != uVar8 || uVar1 != *(uint *)(iVar5 + 0x10)) ||
          *(uint *)(iVar5 + 0x10) == 0 && uVar8 == 0) {
        do {
          iVar5 = iVar7 + 0x50;
          if (iVar5 == *(int *)((int)proxy + 0x3ac)) goto LAB_0006a58a;
          uVar8 = (uint)(uVar2 == *(uint *)(iVar7 + 100) && uVar1 == *(uint *)(iVar7 + 0x60));
          if (*(uint *)(iVar7 + 100) == 0 && *(uint *)(iVar7 + 0x60) == 0) {
            uVar8 = 0;
          }
          iVar7 = iVar5;
        } while (uVar8 == 0);
      }
      FUN_0006fc30((int)proxy + 0x3a8,uVar8,iVar5);
    }
LAB_0006a58a:
    puVar9 = (undefined4 *)((int)proxy + 0x9b8);
    *puVar9 = *(undefined4 *)((int)proxy + 0x828);
    *(undefined4 *)((int)proxy + 0x9bc) = *(undefined4 *)((int)proxy + 0x82c);
    *(undefined4 *)((int)proxy + 0x9c0) = *(undefined4 *)((int)proxy + 0x830);
    *(undefined4 *)((int)proxy + 0x9c4) = *(undefined4 *)((int)proxy + 0x834);
    *(undefined4 *)((int)proxy + 0x9c8) = *(undefined4 *)((int)proxy + 0x838);
    *(undefined4 *)((int)proxy + 0x9cc) = *(undefined4 *)((int)proxy + 0x83c);
    *(undefined4 *)((int)proxy + 0x9d0) = *(undefined4 *)((int)proxy + 0x840);
    *(undefined4 *)((int)proxy + 0x9d4) = *(undefined4 *)((int)proxy + 0x844);
    *(undefined4 *)((int)proxy + 0x9d8) = *(undefined4 *)((int)proxy + 0x848);
    *(undefined4 *)((int)proxy + 0x9dc) = *(undefined4 *)((int)proxy + 0x84c);
    *(undefined4 *)((int)proxy + 0x9e0) = *(undefined4 *)((int)proxy + 0x850);
    *(undefined4 *)((int)proxy + 0x9e4) = *(undefined4 *)((int)proxy + 0x854);
    *(undefined4 *)((int)proxy + 0x9e8) = *(undefined4 *)((int)proxy + 0x858);
    *(undefined4 *)((int)proxy + 0x9ec) = *(undefined4 *)((int)proxy + 0x85c);
    *(undefined4 *)((int)proxy + 0x9f0) = *(undefined4 *)((int)proxy + 0x860);
    *(undefined4 *)((int)proxy + 0x9f4) = *(undefined4 *)((int)proxy + 0x864);
    *(undefined4 *)((int)proxy + 0x9b0) = *(undefined4 *)((int)proxy + 0x820);
    if (*(int *)((int)proxy + 0xf0c) != -1) {
      SetSharedCurrentMapFlag();
      *(undefined4 *)((int)proxy + 0xf0c) = 0xffffffff;
    }
    FUN_0006fb30((int)proxy + 0x3a8,(int)proxy + 0x9b0);
    pthread_mutex_unlock((pthread_mutex_t *)((int)proxy + 0x390));
    *(undefined4 *)((int)proxy + 0x828) = 0;
    *(uint *)((int)proxy + 0x830) = 0;
    *(undefined4 *)((int)proxy + 0x834) = 0;
    if ((*(char *)((int)proxy + 0x3d98) == '\0') &&
       (pvVar4 = (void *)GetSharedSegmentMap(), pvVar4 == (void *)0x0)) {
      FUN_00026228(0x321c,DAT_0006ab60,2,6,"#9986");
      local_30[0] = 0;
      local_a8 = pvVar4;
      local_a4 = pvVar4;
      local_a0 = pvVar4;
      local_9c[0] = (void *)GetSharedCurrentMapFlag();
      FUN_00071c64(&local_a8,local_9c);
      FUN_0006f234(local_9c,&local_a8);
      FUN_00069300(proxy,1,local_30,local_9c);
      if (local_9c[0] != (void *)0x0) {
        operator_delete(local_9c[0]);
      }
      *(undefined1 *)((int)proxy + 0x3d98) = 0;
      if (local_a8 != (void *)0x0) {
        operator_delete(local_a8);
      }
    }
    iVar5 = local_88;
    *(int *)((int)proxy + 0xf10) = local_88;
    iVar7 = rr_check_mapflag_is_multimap(local_88);
    if ((iVar7 == 0) && (iVar7 = InsertMultiMap(iVar5), iVar7 == 0)) {
      FUN_00026228(0x322e,DAT_0006ab60,2,6,"#9987");
      FUN_0003a714(proxy,0);
      FUN_0004ad88(proxy,puVar9,0xffffd8ea,"Save as multi map failed");
      *(undefined4 *)((int)proxy + 0x9b8) = 0;
      *(undefined4 *)((int)proxy + 0x9c0) = 0;
      *(undefined4 *)((int)proxy + 0x9c4) = 0;
      if (uVar2 == *(uint *)((int)proxy + 0xc44) && uVar1 == *(uint *)((int)proxy + 0xc40)) {
        *(undefined4 *)((int)proxy + 0xc38) = 0;
        *(uint *)((int)proxy + 0xc40) = 0;
        *(undefined4 *)((int)proxy + 0xc44) = 0;
      }
      else if (uVar2 == *(uint *)((int)proxy + 0x8d4) && uVar1 == *(uint *)((int)proxy + 0x8d0)) {
        *(undefined4 *)((int)proxy + 0x8c8) = 0;
        *(uint *)((int)proxy + 0x8d0) = 0;
        *(undefined4 *)((int)proxy + 0x8d4) = 0;
      }
      else if (uVar2 == *(uint *)((int)proxy + 0x924) && uVar1 == *(uint *)((int)proxy + 0x920)) {
        *(undefined4 *)((int)proxy + 0x918) = 0;
        *(uint *)((int)proxy + 0x920) = 0;
        *(undefined4 *)((int)proxy + 0x924) = 0;
      }
      else if (uVar2 == *(uint *)((int)proxy + 0xb04) && uVar1 == *(uint *)((int)proxy + 0xb00)) {
        *(undefined4 *)((int)proxy + 0xaf8) = 0;
        *(uint *)((int)proxy + 0xb00) = 0;
        *(undefined4 *)((int)proxy + 0xb04) = 0;
      }
      else if (uVar2 == *(uint *)((int)proxy + 0xa14) && uVar1 == *(uint *)((int)proxy + 0xa10)) {
        *(undefined4 *)((int)proxy + 0xa08) = 0;
        *(uint *)((int)proxy + 0xa10) = 0;
        *(undefined4 *)((int)proxy + 0xa14) = 0;
      }
      else if (uVar2 == *(uint *)((int)proxy + 0xc94) && uVar1 == *(uint *)((int)proxy + 0xc90)) {
        *(undefined4 *)((int)proxy + 0xc88) = 0;
        *(uint *)((int)proxy + 0xc90) = 0;
        *(undefined4 *)((int)proxy + 0xc94) = 0;
      }
      else {
        if (uVar2 != *(uint *)((int)proxy + 0xd84) || uVar1 != *(uint *)((int)proxy + 0xd80))
        goto LAB_0006a7a0;
        *(undefined4 *)((int)proxy + 0xd78) = 0;
        *(uint *)((int)proxy + 0xd80) = 0;
        *(undefined4 *)((int)proxy + 0xd84) = 0;
      }
    }
    else {
      MapFlowWriteBackupDb(proxy,iVar5);
      uVar10 = rr_get_available_bak_map_flag_for_multimap(iVar5);
      if ((int)uVar10 == -1) {
        FUN_00026228(0x326c,DAT_0006ad08,2,6,"#9988");
        FUN_0003a714(proxy,0);
        FUN_0004ad88(proxy,puVar9,0xffffd8ea,"Save as multi map failed");
        *(undefined4 *)((int)proxy + 0x9b8) = 0;
        *(undefined4 *)((int)proxy + 0x9c0) = 0;
        *(undefined4 *)((int)proxy + 0x9c4) = 0;
        if (uVar2 != *(uint *)((int)proxy + 0xc44) || uVar1 != *(uint *)((int)proxy + 0xc40)) {
          if (uVar2 != *(uint *)((int)proxy + 0x8d4) || uVar1 != *(uint *)((int)proxy + 0x8d0)) {
            if (uVar2 == *(uint *)((int)proxy + 0x924) && uVar1 == *(uint *)((int)proxy + 0x920))
            goto LAB_0006aba0;
            goto LAB_0006a75c;
          }
          goto LAB_0006ab02;
        }
        goto LAB_0006a996;
      }
      MapFlowSendSave(proxy,(int)((ulonglong)uVar10 >> 0x20),*(undefined4 *)((int)proxy + 0x9c0),
                      *(undefined4 *)((int)proxy + 0x9c4),(int)uVar10);
    }
  }
  else if (uVar2 == *(uint *)((int)proxy + 0x9c4) && uVar1 == *(uint *)((int)proxy + 0x9c0)) {
    FUN_00026228(0x3287,DAT_0006a7cc,2,6,"#9989");
    pthread_mutex_lock((pthread_mutex_t *)((int)proxy + 0x390));
    iVar5 = *(int *)((int)proxy + 0x3a8);
    if (iVar5 != *(int *)((int)proxy + 0x3ac)) {
      uVar8 = *(uint *)(iVar5 + 0x14);
      iVar7 = iVar5;
      if ((uVar2 != uVar8 || uVar1 != *(uint *)(iVar5 + 0x10)) ||
          *(uint *)(iVar5 + 0x10) == 0 && uVar8 == 0) {
        do {
          iVar5 = iVar7 + 0x50;
          if (iVar5 == *(int *)((int)proxy + 0x3ac)) goto LAB_0006a6b4;
          uVar8 = (uint)(*(uint *)(iVar7 + 0x60) != 0 || *(uint *)(iVar7 + 100) != 0);
          if (uVar2 != *(uint *)(iVar7 + 100) || uVar1 != *(uint *)(iVar7 + 0x60)) {
            uVar8 = 0;
          }
          iVar7 = iVar5;
        } while (uVar8 == 0);
      }
      FUN_0006fc30((int)proxy + 0x3a8,uVar8,iVar5);
    }
LAB_0006a6b4:
    pthread_mutex_unlock((pthread_mutex_t *)((int)proxy + 0x390));
    iVar5 = local_88;
    MapFlowWriteBackupDb(proxy,local_88);
    UpdateBakMapForMultiMap(*(int *)((int)proxy + 0xf10),iVar5);
    if (uVar2 == *(uint *)((int)proxy + 0xb04) && uVar1 == *(uint *)((int)proxy + 0xb00)) {
      FUN_0003f70c(proxy,(int)proxy + 0xaf8,(int)proxy + 0x3df0);
    }
    else if ((uVar2 == *(uint *)((int)proxy + 0xa14) && uVar1 == *(uint *)((int)proxy + 0xa10)) &&
            (*(char *)((int)proxy + 0x1470) != '\0')) {
      FUN_0003f70c(proxy,(int)proxy + 0xa08,(int)proxy + 0x1470);
    }
    else {
      MapFlowReplyOk(proxy,(int)proxy + 0x9b8,&DAT_000f3398);
    }
    *(undefined4 *)((int)proxy + 0x9b8) = 0;
    *(uint *)((int)proxy + 0x9c0) = 0;
    *(undefined4 *)((int)proxy + 0x9c4) = 0;
    FUN_0003a714(proxy);
    if (uVar2 == *(uint *)((int)proxy + 0xc44) && uVar1 == *(uint *)((int)proxy + 0xc40)) {
LAB_0006a996:
      *(undefined4 *)((int)proxy + 0xc38) = 0;
      *(undefined4 *)((int)proxy + 0xc40) = 0;
      *(undefined4 *)((int)proxy + 0xc44) = 0;
    }
    else if (uVar2 == *(uint *)((int)proxy + 0x8d4) && uVar1 == *(uint *)((int)proxy + 0x8d0)) {
LAB_0006ab02:
      *(undefined4 *)((int)proxy + 0x8c8) = 0;
      *(undefined4 *)((int)proxy + 0x8d0) = 0;
      *(undefined4 *)((int)proxy + 0x8d4) = 0;
    }
    else if (uVar2 == *(uint *)((int)proxy + 0x924) && uVar1 == *(uint *)((int)proxy + 0x920)) {
LAB_0006aba0:
      *(undefined4 *)((int)proxy + 0x918) = 0;
      *(undefined4 *)((int)proxy + 0x920) = 0;
      *(undefined4 *)((int)proxy + 0x924) = 0;
    }
    else {
LAB_0006a75c:
      if (uVar2 == *(uint *)((int)proxy + 0xb04) && uVar1 == *(uint *)((int)proxy + 0xb00)) {
        *(undefined4 *)((int)proxy + 0xaf8) = 0;
        *(uint *)((int)proxy + 0xb00) = 0;
        *(undefined4 *)((int)proxy + 0xb04) = 0;
      }
      else if (uVar2 == *(uint *)((int)proxy + 0xa14) && uVar1 == *(uint *)((int)proxy + 0xa10)) {
        *(undefined4 *)((int)proxy + 0xa08) = 0;
        *(uint *)((int)proxy + 0xa10) = 0;
        *(undefined4 *)((int)proxy + 0xa14) = 0;
      }
      else if (uVar2 == *(uint *)((int)proxy + 0xc94) && uVar1 == *(uint *)((int)proxy + 0xc90)) {
        *(undefined4 *)((int)proxy + 0xc88) = 0;
        *(uint *)((int)proxy + 0xc90) = 0;
        *(undefined4 *)((int)proxy + 0xc94) = 0;
      }
      else if (uVar2 == *(uint *)((int)proxy + 0xd84) && uVar1 == *(uint *)((int)proxy + 0xd80)) {
        *(undefined4 *)((int)proxy + 0xd78) = 0;
        *(uint *)((int)proxy + 0xd80) = 0;
        *(undefined4 *)((int)proxy + 0xd84) = 0;
      }
      else {
LAB_0006a7a0:
        if (uVar2 == *(uint *)((int)proxy + 0xdd4) && uVar1 == *(uint *)((int)proxy + 0xdd0)) {
          *(undefined4 *)((int)proxy + 0xdc8) = 0;
          *(uint *)((int)proxy + 0xdd0) = 0;
          *(undefined4 *)((int)proxy + 0xdd4) = 0;
        }
      }
    }
  }
  else if (uVar2 == *(uint *)((int)proxy + 0xba4) && uVar1 == *(uint *)((int)proxy + 0xba0)) {
    FUN_00026228(0x32b5,DAT_0006ab60,2,6,"#9990");
    pthread_mutex_lock((pthread_mutex_t *)((int)proxy + 0x390));
    iVar5 = *(int *)((int)proxy + 0x3a8);
    if (iVar5 != *(int *)((int)proxy + 0x3ac)) {
      uVar8 = *(uint *)(iVar5 + 0x14) | *(uint *)(iVar5 + 0x10);
      iVar7 = iVar5;
      if (uVar8 == 0 || (uVar2 != *(uint *)(iVar5 + 0x14) || uVar1 != *(uint *)(iVar5 + 0x10))) {
        do {
          iVar5 = iVar7 + 0x50;
          if (iVar5 == *(int *)((int)proxy + 0x3ac)) goto LAB_0006a84c;
          uVar8 = (uint)(uVar2 == *(uint *)(iVar7 + 100) && uVar1 == *(uint *)(iVar7 + 0x60));
          if (*(uint *)(iVar7 + 100) == 0 && *(uint *)(iVar7 + 0x60) == 0) {
            uVar8 = 0;
          }
          iVar7 = iVar5;
        } while (uVar8 == 0);
      }
      FUN_0006fc30((int)proxy + 0x3a8,uVar8,iVar5);
    }
LAB_0006a84c:
    pthread_mutex_unlock((pthread_mutex_t *)((int)proxy + 0x390));
    if (*(int *)((int)proxy + 0xf00) == 0) {
      MapFlowWriteBackupDb(proxy,2);
    }
    else {
      MapFlowWriteBackupDb(proxy,*(int *)((int)proxy + 0xf00));
    }
    *(undefined4 *)((int)proxy + 0xb98) = 0;
    *(uint *)((int)proxy + 0xba0) = 0;
    *(undefined4 *)((int)proxy + 0xba4) = 0;
    MapFlowReplyOk(proxy,(int)proxy + 0x968,&DAT_000f3398);
    *(undefined4 *)((int)proxy + 0x968) = 0;
    *(undefined4 *)((int)proxy + 0x970) = 0;
    *(undefined4 *)((int)proxy + 0x974) = 0;
    FUN_0003a714(proxy,0);
    *(undefined4 *)((int)proxy + 0xf00) = 0;
  }
  else if (uVar2 == *(uint *)((int)proxy + 0xd34) && uVar1 == *(uint *)((int)proxy + 0xd30)) {
    FUN_00026228(0x32d0,DAT_0006ab60,2,6,"#9991");
    pthread_mutex_lock((pthread_mutex_t *)((int)proxy + 0x390));
    iVar5 = *(int *)((int)proxy + 0x3a8);
    if (iVar5 != *(int *)((int)proxy + 0x3ac)) {
      uVar8 = *(uint *)(iVar5 + 0x14);
      iVar7 = iVar5;
      if ((uVar2 != uVar8 || uVar1 != *(uint *)(iVar5 + 0x10)) ||
          *(uint *)(iVar5 + 0x10) == 0 && uVar8 == 0) {
        do {
          iVar5 = iVar7 + 0x50;
          if (iVar5 == *(int *)((int)proxy + 0x3ac)) goto LAB_0006a922;
          uVar8 = (uint)(*(uint *)(iVar7 + 0x60) != 0 || *(uint *)(iVar7 + 100) != 0);
          if (uVar2 != *(uint *)(iVar7 + 100) || uVar1 != *(uint *)(iVar7 + 0x60)) {
            uVar8 = 0;
          }
          iVar7 = iVar5;
        } while (uVar8 == 0);
      }
      FUN_0006fc30((int)proxy + 0x3a8,uVar8,iVar5);
    }
LAB_0006a922:
    pthread_mutex_unlock((pthread_mutex_t *)((int)proxy + 0x390));
    MapFlowReplyOk(proxy,(int)proxy + 0xd28,&DAT_000f3398);
    FUN_0003a714(proxy,0);
    *(undefined4 *)((int)proxy + 0xd28) = 0;
    *(uint *)((int)proxy + 0xd30) = 0;
    *(undefined4 *)((int)proxy + 0xd34) = 0;
  }
  else if (uVar2 == *(uint *)((int)proxy + 0xe74) && uVar1 == *(uint *)((int)proxy + 0xe70)) {
    FUN_00026228(0x32e0,DAT_0006a298,2,6,"#9992");
    pthread_mutex_lock((pthread_mutex_t *)((int)proxy + 0x390));
    iVar5 = *(int *)((int)proxy + 0x3a8);
    if (iVar5 != *(int *)((int)proxy + 0x3ac)) {
      uVar8 = *(uint *)(iVar5 + 0x14) | *(uint *)(iVar5 + 0x10);
      iVar7 = iVar5;
      if (uVar8 == 0 || (uVar2 != *(uint *)(iVar5 + 0x14) || uVar1 != *(uint *)(iVar5 + 0x10))) {
        do {
          iVar5 = iVar7 + 0x50;
          if (iVar5 == *(int *)((int)proxy + 0x3ac)) goto LAB_0006a03a;
          uVar8 = (uint)(*(uint *)(iVar7 + 0x60) != 0 || *(uint *)(iVar7 + 100) != 0);
          if (uVar2 != *(uint *)(iVar7 + 100) || uVar1 != *(uint *)(iVar7 + 0x60)) {
            uVar8 = 0;
          }
          iVar7 = iVar5;
        } while (uVar8 == 0);
      }
      FUN_0006fc30((int)proxy + 0x3a8,uVar8,iVar5);
    }
LAB_0006a03a:
    pthread_mutex_unlock((pthread_mutex_t *)((int)proxy + 0x390));
    __stream = fopen((char *)((int)proxy + 0x6a8),"w");
    if (__stream == (FILE *)0x0) {
      FUN_00026228(0x32f2,DAT_0006ab60,2,6,"#9993");
      FUN_0004ad88(proxy,(int)proxy + 0xe68,0xffffd8ea,"add lab info file failed");
      goto LAB_00069d44;
    }
    __fprintf_chk(__stream,1,"%d",*(undefined4 *)((int)proxy + 0xf4c));
    fclose(__stream);
    ClearMultiMapExcept(*(int *)((int)proxy + 0xf04));
    memset(local_7c,0,0x4c);
    local_70 = *(undefined4 *)((int)proxy + 0xf4c);
    local_7c[0] = 0x2033201;
    local_74 = 4;
    FUN_00037b78(proxy,local_7c,1,0);
    memset(local_7c,0,0x4c);
    local_70 = *(undefined4 *)((int)proxy + 0xf4c);
    local_74 = 4;
    local_7c[0] = 0x1033103;
    FUN_00037b78(proxy,local_7c,1,0);
    *(uint *)((int)proxy + 0xf44) = *(byte *)((int)proxy + 0xf4c) & 1;
    *(uint *)((int)proxy + 0xf48) = ((uint)*(byte *)((int)proxy + 0xf4c) << 0x1e) >> 0x1f;
    *(undefined4 *)((int)proxy + 0x308) = *(undefined4 *)((int)proxy + 0xf4c);
    rr_event_int(9,0xb,*(undefined4 *)((int)proxy + 0xf4c));
    MapFlowReplyOk(proxy,(int)proxy + 0xe68,&DAT_000f3398);
    FUN_0003a714(proxy,0);
    *(undefined4 *)((int)proxy + 0xe68) = 0;
    *(uint *)((int)proxy + 0xe70) = 0;
    *(undefined4 *)((int)proxy + 0xe74) = 0;
  }
  pthread_mutex_lock((pthread_mutex_t *)((int)proxy + 0xf54));
  tVar6 = time((time_t *)0x0);
  *(time_t *)((int)proxy + 0xf6c) = tVar6;
  pthread_mutex_unlock((pthread_mutex_t *)((int)proxy + 0xf54));
LAB_00069d44:
  if (local_2c != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}

