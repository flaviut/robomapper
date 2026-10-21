/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x0004fbf8
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Command load_multi_map registered by 0x625e8 at 0x637ba..0x637d4 with Thumb handler 0x4fbf9.
   Validates params and external flag through catalog-owned wrapper 0x3b908, converts external+2,
   then queues load step 0x3cc74 and save-last step 0x39b84. Initial series advance sends load and
   waits. On load-result success it sends save-last, then the now-empty queue forces an ok reply
   without waiting for that final save result. */

void MapFlowLoadMultiCmd(void *proxy,void *request,void *json)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  void *pvVar4;
  undefined8 uVar5;
  int local_6c;
  void *local_68;
  undefined4 uStack_64;
  code *local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  int local_24;
  
  local_24 = __stack_chk_guard;
  FUN_00026228(0x3f0f,DAT_0004fe6c,1,7,"#10189");
  FUN_0003cb84(proxy);
  iVar2 = FUN_0004fa68(proxy,request);
  if (iVar2 != 0) {
    FUN_0007047c(&local_6c,json,"params");
    if (local_6c == *(int *)((int)json + 4) * 0x30 + *(int *)json) {
      FUN_00026228(0x3f16,DAT_0004fe6c,1,6,"#10190");
    }
    else {
      piVar3 = (int *)FUN_0006f130(json,"params");
      if (piVar3[4] == 4) {
        if (piVar3[1] == 0) {
          FUN_0004ad88(proxy,request,0xffffd8eb,"param does not contain any element");
          FUN_00026228(0x3f21,DAT_0004fe6c,1,6,"#10192");
        }
        else if (((int *)*piVar3)[4] << 0x16 < 0) {
          iVar2 = *(int *)*piVar3;
          bVar1 = CatalogExternalMapExists(proxy,iVar2,0);
          if (bVar1) {
            local_68 = *(void **)request;
            uStack_64 = *(undefined4 *)((int)request + 4);
            local_60 = *(code **)((int)request + 8);
            local_5c = *(undefined4 *)((int)request + 0xc);
            local_58 = *(undefined4 *)((int)request + 0x10);
            uStack_54 = *(undefined4 *)((int)request + 0x14);
            local_50 = *(undefined4 *)((int)request + 0x18);
            uStack_4c = *(undefined4 *)((int)request + 0x1c);
            local_48 = *(undefined4 *)((int)request + 0x20);
            uStack_44 = *(undefined4 *)((int)request + 0x24);
            local_40 = *(undefined4 *)((int)request + 0x28);
            uStack_3c = *(undefined4 *)((int)request + 0x2c);
            local_38 = *(undefined4 *)((int)request + 0x30);
            uStack_34 = *(undefined4 *)((int)request + 0x34);
            local_30 = *(undefined4 *)((int)request + 0x38);
            uStack_2c = *(undefined4 *)((int)request + 0x3c);
            pvVar4 = operator_new(0x80);
            FUN_0002410c(pvVar4,uStack_2c,local_68,uStack_64,local_60,local_5c,local_58,uStack_54,
                         local_50,uStack_4c,local_48,uStack_44,local_40,uStack_3c,local_38,uStack_34
                         ,local_30,uStack_2c,iVar2 + 2);
            local_5c = 0x3cc75;
            local_60 = (code *)0x36f5d;
            local_68 = proxy;
            FUN_00024288(pvVar4,&local_68);
            if (local_60 != (code *)0x0) {
              (*local_60)(&local_68,&local_68,3);
            }
            local_5c = 0x39b85;
            local_60 = (code *)0x36f81;
            local_68 = proxy;
            FUN_00024288(pvVar4,&local_68);
            if (local_60 != (code *)0x0) {
              (*local_60)(&local_68,&local_68,3);
            }
            uVar5 = FUN_0006f064();
            FUN_000242ac((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),
                         *(undefined4 *)((int)request + 8),*(undefined4 *)((int)request + 0xc),
                         pvVar4);
            uVar5 = FUN_0006f064();
            MapFlowAdvanceSeries
                      ((void *)uVar5,(uint)((ulonglong)uVar5 >> 0x20),*(uint *)((int)request + 8),
                       *(uint *)((int)request + 0xc));
          }
          else {
            FUN_00026228(0x3f2e,DAT_0004fe6c,1,6,"#10194`%d",iVar2);
            FUN_0004ad88(proxy,request,0xffffd8eb,"mapFlag error");
          }
        }
        else {
          FUN_00026228(0x3f27,DAT_0004fe6c,1,6,"#10193");
          FUN_0004ad88(proxy,request,0xffffd8eb,"First element in array is not an Number");
        }
      }
      else {
        FUN_00026228(0x3f1c,DAT_0004fe6c,1,6,"#10191");
      }
    }
  }
  if (local_24 == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

