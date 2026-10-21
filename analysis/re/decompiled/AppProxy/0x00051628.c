/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x00051628
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Command recover_multi_map registered at 0x6383a..0x63852. Selects backup via catalog-owned
   0x3c568. If selection==requested and current==requested+2: immediate ok reply, no storage work.
   Otherwise selection==requested queues ordinary load/save-last. If backup differs queues
   load-selected-backup, save [1,requested+2], then backup DB step; unlike ordinary load the
   remaining DB callback makes it wait for save-set result before final success. Selection and
   current comparisons precede work; no original C++ layouts inferred. */

void MapFlowRecoverMultiCmd(void *proxy,void *request,void *json)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  void *pvVar5;
  int iVar6;
  int primary_flag;
  undefined8 uVar7;
  MapPersistFlag local_bc;
  void *local_b8;
  undefined4 uStack_b4;
  code *local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 uStack_a4;
  undefined4 local_a0;
  undefined4 uStack_9c;
  undefined4 local_98;
  undefined4 uStack_94;
  undefined4 local_90;
  undefined4 uStack_8c;
  undefined4 local_88;
  undefined4 uStack_84;
  undefined4 local_80;
  undefined4 uStack_7c;
  undefined1 auStack_78 [84];
  int local_24;
  
  local_24 = __stack_chk_guard;
  FUN_00026228(0x54ca,DAT_00051990,1,7,"#10582");
  FUN_0003cb84(proxy);
  iVar2 = FUN_0004fa68(proxy,request);
  if (iVar2 == 0) goto LAB_00051668;
  memcpy(auStack_78,
         "{\"params\":{\"force\":\"Y\",\"type\":\"O\",\"value\":{\"map_flag\":{\"force\":\"Y\",\"type\":\"N\"}}}}"
         ,0x52);
  iVar2 = FUN_000833ac(json,auStack_78);
  if (iVar2 == 0) {
    FUN_00026228(0x54d1,DAT_00051990,1,6,"#10583`%s",auStack_78);
    FUN_0004ad88(proxy,request,0xffffd8e9,"invalid params");
    FUN_00026228(0x54d3,DAT_00051990,1,6,"#10584");
    goto LAB_00051668;
  }
  uVar3 = FUN_0006f130(json,"params");
  piVar4 = (int *)FUN_0006f130(uVar3,"map_flag");
  iVar2 = *piVar4;
  bVar1 = CatalogExternalMapExists(proxy,iVar2,0);
  if (bVar1) {
    primary_flag = iVar2 + 2;
    local_bc = -1;
    CatalogSelectBackup(proxy,primary_flag,&local_bc);
    iVar6 = local_bc + -2;
    if (iVar2 == iVar6) {
      iVar6 = GetSharedCurrentMapFlag();
      if (iVar6 == primary_flag) {
        FUN_00026228(0x54e0,DAT_00051a1c,1,6,"#10586");
        MapFlowReplyOk(proxy,request,&DAT_000f3398);
      }
      else {
        local_b8 = *(void **)request;
        uStack_b4 = *(undefined4 *)((int)request + 4);
        local_b0 = *(code **)((int)request + 8);
        local_ac = *(undefined4 *)((int)request + 0xc);
        local_a8 = *(undefined4 *)((int)request + 0x10);
        uStack_a4 = *(undefined4 *)((int)request + 0x14);
        local_a0 = *(undefined4 *)((int)request + 0x18);
        uStack_9c = *(undefined4 *)((int)request + 0x1c);
        local_98 = *(undefined4 *)((int)request + 0x20);
        uStack_94 = *(undefined4 *)((int)request + 0x24);
        local_90 = *(undefined4 *)((int)request + 0x28);
        uStack_8c = *(undefined4 *)((int)request + 0x2c);
        local_88 = *(undefined4 *)((int)request + 0x30);
        uStack_84 = *(undefined4 *)((int)request + 0x34);
        local_80 = *(undefined4 *)((int)request + 0x38);
        uStack_7c = *(undefined4 *)((int)request + 0x3c);
        pvVar5 = operator_new(0x80);
        FUN_0002410c(pvVar5,uStack_7c,local_b8,uStack_b4,local_b0,local_ac,local_a8,uStack_a4,
                     local_a0,uStack_9c,local_98,uStack_94,local_90,uStack_8c,local_88,uStack_84,
                     local_80,uStack_7c,primary_flag);
        local_ac = 0x3cc75;
        local_b0 = (code *)0x36f5d;
        local_b8 = proxy;
        FUN_00024288(pvVar5,&local_b8);
        if (local_b0 != (code *)0x0) {
          (*local_b0)(&local_b8,&local_b8,3);
        }
        local_ac = 0x39b85;
        local_b0 = (code *)0x36f81;
        local_b8 = proxy;
        FUN_00024288(pvVar5,&local_b8);
        if (local_b0 != (code *)0x0) {
          (*local_b0)(&local_b8,&local_b8,3);
        }
        uVar7 = FUN_0006f064();
        FUN_000242ac((int)uVar7,(int)((ulonglong)uVar7 >> 0x20),*(undefined4 *)((int)request + 8),
                     *(undefined4 *)((int)request + 0xc),pvVar5);
        uVar7 = FUN_0006f064();
        MapFlowAdvanceSeries
                  ((void *)uVar7,(uint)((ulonglong)uVar7 >> 0x20),*(uint *)((int)request + 8),
                   *(uint *)((int)request + 0xc));
      }
      FUN_00026228(0x54e9,DAT_00051990,1,6,"#10587`%d",iVar2);
    }
    else {
      bVar1 = CatalogExternalMapExists(proxy,iVar2,0);
      if ((!bVar1) || (bVar1 = CatalogExternalMapExists(proxy,iVar6,1), !bVar1)) {
        FUN_00026228(0x54ef,DAT_00051990,1,6,"#10588`%d`%d",iVar2,iVar6);
        goto LAB_000516d6;
      }
      local_b8 = *(void **)request;
      uStack_b4 = *(undefined4 *)((int)request + 4);
      local_b0 = *(code **)((int)request + 8);
      local_ac = *(undefined4 *)((int)request + 0xc);
      local_a8 = *(undefined4 *)((int)request + 0x10);
      uStack_a4 = *(undefined4 *)((int)request + 0x14);
      local_a0 = *(undefined4 *)((int)request + 0x18);
      uStack_9c = *(undefined4 *)((int)request + 0x1c);
      local_98 = *(undefined4 *)((int)request + 0x20);
      uStack_94 = *(undefined4 *)((int)request + 0x24);
      local_90 = *(undefined4 *)((int)request + 0x28);
      uStack_8c = *(undefined4 *)((int)request + 0x2c);
      local_88 = *(undefined4 *)((int)request + 0x30);
      uStack_84 = *(undefined4 *)((int)request + 0x34);
      local_80 = *(undefined4 *)((int)request + 0x38);
      uStack_7c = *(undefined4 *)((int)request + 0x3c);
      pvVar5 = operator_new(0x80);
      FUN_0002410c(pvVar5,uStack_7c,local_b8,uStack_b4,local_b0,local_ac,local_a8,uStack_a4,local_a0
                   ,uStack_9c,local_98,uStack_94,local_90,uStack_8c,local_88,uStack_84,local_80,
                   uStack_7c,primary_flag);
      local_ac = 0x68c15;
      local_b0 = (code *)0x36f15;
      local_b8 = proxy;
      FUN_00024288(pvVar5,&local_b8);
      if (local_b0 != (code *)0x0) {
        (*local_b0)(&local_b8,&local_b8,3);
      }
      local_ac = 0x3c7a1;
      local_b0 = (code *)0x36ea9;
      local_b8 = proxy;
      FUN_00024288(pvVar5,&local_b8);
      if (local_b0 != (code *)0x0) {
        (*local_b0)(&local_b8,&local_b8,3);
      }
      local_ac = 0x3a5c1;
      local_b0 = (code *)0x36fa5;
      local_b8 = proxy;
      FUN_00024288(pvVar5,&local_b8);
      if (local_b0 != (code *)0x0) {
        (*local_b0)(&local_b8,&local_b8,3);
      }
      uVar7 = FUN_0006f064();
      FUN_000242ac((int)uVar7,(int)((ulonglong)uVar7 >> 0x20),*(undefined4 *)((int)request + 8),
                   *(undefined4 *)((int)request + 0xc),pvVar5);
      uVar7 = FUN_0006f064();
      MapFlowAdvanceSeries
                ((void *)uVar7,(uint)((ulonglong)uVar7 >> 0x20),*(uint *)((int)request + 8),
                 *(uint *)((int)request + 0xc));
    }
    rr_event_int(9,0x30,1);
  }
  else {
    FUN_00026228(0x54d8,DAT_00051990,1,6,"#10585`%d",iVar2);
LAB_000516d6:
    FUN_0004ad88(proxy,request,0xffffd8eb,"mapFlag error");
  }
LAB_00051668:
  if (local_24 == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

