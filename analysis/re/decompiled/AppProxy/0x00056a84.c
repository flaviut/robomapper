/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x00056a84
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* HandleNavLoadMapResult diagnostic. Requires message length +8==16; request low/high +0xc/+0x10,
   flag +0x14, result +0x18. Only result==1 advances queued series; other values fail it with load
   map result failed. Legacy fallback paths run only if series did not handle request. This consumes
   a result, not evidence the cross-process bridge was fully recovered. */

void MapFlowHandleLoadResult(void *proxy,void *message)

{
  uint request_lo;
  uint request_hi;
  undefined4 uVar1;
  void *series;
  int iVar2;
  time_t tVar3;
  uint reserved_r1;
  uint *puVar4;
  pthread_mutex_t *ppVar5;
  undefined8 uVar6;
  allocator aaStack_44 [4];
  undefined1 auStack_40 [4];
  int local_3c;
  uint local_38;
  uint uStack_34;
  undefined4 local_30;
  int local_2c;
  int local_24;
  
  local_24 = __stack_chk_guard;
  if (*(int *)((int)message + 8) == 0x10) {
    uVar1 = FUN_0007d574();
    FUN_0007ced8(uVar1,1);
    FUN_00026228(0x309d,"HandleNavLoadMapResult",5,6,"#9958");
    local_38 = *(uint *)((int)message + 0xc);
    local_2c = *(int *)((int)message + 0x18);
    uStack_34 = *(uint *)((int)message + 0x10);
    local_30 = *(undefined4 *)((int)message + 0x14);
    if (local_2c == 1) {
      uVar6 = FUN_0006f064();
      iVar2 = MapFlowAdvanceSeries
                        ((void *)uVar6,(uint)((ulonglong)uVar6 >> 0x20),local_38,uStack_34);
    }
    else {
      series = (void *)FUN_0006f064();
      request_hi = uStack_34;
      request_lo = local_38;
      std::string::string((string *)&local_3c,"load map result failed!",aaStack_44);
      iVar2 = MapFlowFailSeries(series,reserved_r1,request_lo,request_hi,(string *)&local_3c);
      if ((undefined1 *)(local_3c + -0xc) != std::string::_Rep::_S_empty_rep_storage) {
        FUN_00037650((undefined1 *)(local_3c + -0xc),auStack_40);
      }
    }
    if ((iVar2 == 0) && (local_38 != 0 || uStack_34 != 0)) {
      puVar4 = (uint *)((int)proxy + 0x970);
      if (uStack_34 == *(uint *)((int)proxy + 0x974) && local_38 == *puVar4) {
        ppVar5 = (pthread_mutex_t *)((int)proxy + 0x390);
        FUN_00026228(0x30ae,"HandleNavLoadMapResult",2,6,"#9959");
        pthread_mutex_lock(ppVar5);
        for (iVar2 = *(int *)((int)proxy + 0x3a8); iVar2 != *(int *)((int)proxy + 0x3ac);
            iVar2 = iVar2 + 0x50) {
          if ((*(uint *)(iVar2 + 0x10) != 0 || *(int *)(iVar2 + 0x14) != 0) &&
             (*(int *)(iVar2 + 0x14) == *(int *)((int)proxy + 0x974) &&
              *(uint *)(iVar2 + 0x10) == *puVar4)) {
            FUN_0006fc30((int)proxy + 0x3a8);
            break;
          }
        }
        pthread_mutex_unlock(ppVar5);
        pthread_mutex_lock((pthread_mutex_t *)((int)proxy + 0xf54));
        tVar3 = time((time_t *)0x0);
        *(time_t *)((int)proxy + 0xf6c) = tVar3;
        pthread_mutex_unlock((pthread_mutex_t *)((int)proxy + 0xf54));
        if (local_2c == 1) {
          FUN_00026228(0x30c1,"HandleNavLoadMapResult",2,6,"#9960");
          ClearCleanRouting();
          FUN_00026228(0x30c3,"HandleNavLoadMapResult",2,6,"#9961");
          *(undefined4 *)((int)proxy + 0xb48) = *(undefined4 *)((int)proxy + 0x968);
          *(undefined4 *)((int)proxy + 0xb4c) = *(undefined4 *)((int)proxy + 0x96c);
          *(undefined4 *)((int)proxy + 0xb50) = *(undefined4 *)((int)proxy + 0x970);
          *(undefined4 *)((int)proxy + 0xb54) = *(undefined4 *)((int)proxy + 0x974);
          *(undefined4 *)((int)proxy + 0xb58) = *(undefined4 *)((int)proxy + 0x978);
          *(undefined4 *)((int)proxy + 0xb5c) = *(undefined4 *)((int)proxy + 0x97c);
          *(undefined4 *)((int)proxy + 0xb60) = *(undefined4 *)((int)proxy + 0x980);
          *(undefined4 *)((int)proxy + 0xb64) = *(undefined4 *)((int)proxy + 0x984);
          *(undefined4 *)((int)proxy + 0xb68) = *(undefined4 *)((int)proxy + 0x988);
          *(undefined4 *)((int)proxy + 0xb6c) = *(undefined4 *)((int)proxy + 0x98c);
          *(undefined4 *)((int)proxy + 0xb70) = *(undefined4 *)((int)proxy + 0x990);
          *(undefined4 *)((int)proxy + 0xb74) = *(undefined4 *)((int)proxy + 0x994);
          *(undefined4 *)((int)proxy + 0xb78) = *(undefined4 *)((int)proxy + 0x998);
          *(undefined4 *)((int)proxy + 0xb7c) = *(undefined4 *)((int)proxy + 0x99c);
          *(undefined4 *)((int)proxy + 0xb80) = *(undefined4 *)((int)proxy + 0x9a0);
          *(undefined4 *)((int)proxy + 0xb84) = *(undefined4 *)((int)proxy + 0x9a4);
          *(undefined4 *)((int)proxy + 0xb40) = *(undefined4 *)((int)proxy + 0x960);
          pthread_mutex_lock(ppVar5);
          FUN_0006fb30((int)proxy + 0x3a8,(int)proxy + 0xb40);
          pthread_mutex_unlock(ppVar5);
          MapFlowSendSave(proxy);
          FUN_0003a664(proxy);
          FUN_0008c46c(*(undefined4 *)((int)proxy + 0x4e8));
        }
        else {
          FUN_0004ad88(proxy,(int)proxy + 0x968,0xffffd8ea,"recover bak map failed");
          FUN_00026228(0x30d4,"HandleNavLoadMapResult",2,6,"#9962");
          FUN_0003a714(proxy,0);
          *(undefined4 *)((int)proxy + 0x968) = 0;
          *puVar4 = 0;
          *(undefined4 *)((int)proxy + 0x974) = 0;
          *(undefined4 *)((int)proxy + 0xf00) = 0;
        }
      }
      else {
        puVar4 = (uint *)((int)proxy + 0xa60);
        if (uStack_34 == *(uint *)((int)proxy + 0xa64) && local_38 == *puVar4) {
          ppVar5 = (pthread_mutex_t *)((int)proxy + 0x390);
          FUN_00026228(0x30dd,"HandleNavLoadMapResult",2,6,"#9963");
          pthread_mutex_lock(ppVar5);
          for (iVar2 = *(int *)((int)proxy + 0x3a8); iVar2 != *(int *)((int)proxy + 0x3ac);
              iVar2 = iVar2 + 0x50) {
            if ((*(uint *)(iVar2 + 0x10) != 0 || *(int *)(iVar2 + 0x14) != 0) &&
               (*(int *)(iVar2 + 0x14) == *(int *)((int)proxy + 0xa64) &&
                *(uint *)(iVar2 + 0x10) == *puVar4)) {
              FUN_0006fc30((int)proxy + 0x3a8);
              break;
            }
          }
          pthread_mutex_unlock(ppVar5);
          pthread_mutex_lock((pthread_mutex_t *)((int)proxy + 0xf54));
          tVar3 = time((time_t *)0x0);
          *(time_t *)((int)proxy + 0xf6c) = tVar3;
          pthread_mutex_unlock((pthread_mutex_t *)((int)proxy + 0xf54));
          if (local_2c == 1) {
            FUN_00026228(0x30f0,"HandleNavLoadMapResult",2,6,"#9964");
            ClearCleanRouting();
            FUN_00026228(0x30f2,"HandleNavLoadMapResult",2,6,"#9965");
            *(undefined4 *)((int)proxy + 0xaa8) = *(undefined4 *)((int)proxy + 0xa58);
            *(undefined4 *)((int)proxy + 0xaac) = *(undefined4 *)((int)proxy + 0xa5c);
            *(undefined4 *)((int)proxy + 0xab0) = *(undefined4 *)((int)proxy + 0xa60);
            *(undefined4 *)((int)proxy + 0xab4) = *(undefined4 *)((int)proxy + 0xa64);
            *(undefined4 *)((int)proxy + 0xab8) = *(undefined4 *)((int)proxy + 0xa68);
            *(undefined4 *)((int)proxy + 0xabc) = *(undefined4 *)((int)proxy + 0xa6c);
            *(undefined4 *)((int)proxy + 0xac0) = *(undefined4 *)((int)proxy + 0xa70);
            *(undefined4 *)((int)proxy + 0xac4) = *(undefined4 *)((int)proxy + 0xa74);
            *(undefined4 *)((int)proxy + 0xac8) = *(undefined4 *)((int)proxy + 0xa78);
            *(undefined4 *)((int)proxy + 0xacc) = *(undefined4 *)((int)proxy + 0xa7c);
            *(undefined4 *)((int)proxy + 0xad0) = *(undefined4 *)((int)proxy + 0xa80);
            *(undefined4 *)((int)proxy + 0xad4) = *(undefined4 *)((int)proxy + 0xa84);
            *(undefined4 *)((int)proxy + 0xad8) = *(undefined4 *)((int)proxy + 0xa88);
            *(undefined4 *)((int)proxy + 0xadc) = *(undefined4 *)((int)proxy + 0xa8c);
            *(undefined4 *)((int)proxy + 0xae0) = *(undefined4 *)((int)proxy + 0xa90);
            *(undefined4 *)((int)proxy + 0xae4) = *(undefined4 *)((int)proxy + 0xa94);
            tVar3 = time((time_t *)0x0);
            *(time_t *)((int)proxy + 0xaa0) = tVar3;
            pthread_mutex_lock(ppVar5);
            FUN_0006fb30((int)proxy + 0x3a8,(int)proxy + 0xaa0);
            pthread_mutex_unlock(ppVar5);
            MapFlowSendSave(proxy);
            FUN_0008c46c(*(undefined4 *)((int)proxy + 0x4e8));
          }
          else {
            FUN_0004ad88(proxy,(int)proxy + 0xa58,0xffffd8ea,"recover user map failed");
            FUN_00026228(0x3102,"HandleNavLoadMapResult",2,6,"#9966");
          }
          *(undefined4 *)((int)proxy + 0xa58) = 0;
          *puVar4 = 0;
          *(undefined4 *)((int)proxy + 0xa64) = 0;
        }
        else {
          puVar4 = (uint *)((int)proxy + 0xce0);
          if (uStack_34 == *(uint *)((int)proxy + 0xce4) && local_38 == *puVar4) {
            ppVar5 = (pthread_mutex_t *)((int)proxy + 0x390);
            FUN_00026228(0x3108,"HandleNavLoadMapResult",2,6,"#9967");
            pthread_mutex_lock(ppVar5);
            for (iVar2 = *(int *)((int)proxy + 0x3a8); iVar2 != *(int *)((int)proxy + 0x3ac);
                iVar2 = iVar2 + 0x50) {
              if ((*(uint *)(iVar2 + 0x10) != 0 || *(int *)(iVar2 + 0x14) != 0) &&
                 (*(int *)(iVar2 + 0x14) == *(int *)((int)proxy + 0xce4) &&
                  *(uint *)(iVar2 + 0x10) == *puVar4)) {
                FUN_0006fc30((int)proxy + 0x3a8);
                break;
              }
            }
            pthread_mutex_unlock(ppVar5);
            pthread_mutex_lock((pthread_mutex_t *)((int)proxy + 0xf54));
            tVar3 = time((time_t *)0x0);
            *(time_t *)((int)proxy + 0xf6c) = tVar3;
            pthread_mutex_unlock((pthread_mutex_t *)((int)proxy + 0xf54));
            if (local_2c == 1) {
              FUN_00026228(0x311b,"HandleNavLoadMapResult",2,6,"#9968");
              ClearCleanRouting();
              FUN_00026228(0x311d,"HandleNavLoadMapResult",2,6,"#9969");
              SetSharedCurrentMapFlag(local_30);
              *(undefined4 *)((int)proxy + 0xd28) = *(undefined4 *)((int)proxy + 0xcd8);
              *(undefined4 *)((int)proxy + 0xd2c) = *(undefined4 *)((int)proxy + 0xcdc);
              *(undefined4 *)((int)proxy + 0xd30) = *(undefined4 *)((int)proxy + 0xce0);
              *(undefined4 *)((int)proxy + 0xd34) = *(undefined4 *)((int)proxy + 0xce4);
              *(undefined4 *)((int)proxy + 0xd38) = *(undefined4 *)((int)proxy + 0xce8);
              *(undefined4 *)((int)proxy + 0xd3c) = *(undefined4 *)((int)proxy + 0xcec);
              *(undefined4 *)((int)proxy + 0xd40) = *(undefined4 *)((int)proxy + 0xcf0);
              *(undefined4 *)((int)proxy + 0xd44) = *(undefined4 *)((int)proxy + 0xcf4);
              *(undefined4 *)((int)proxy + 0xd48) = *(undefined4 *)((int)proxy + 0xcf8);
              *(undefined4 *)((int)proxy + 0xd4c) = *(undefined4 *)((int)proxy + 0xcfc);
              *(undefined4 *)((int)proxy + 0xd50) = *(undefined4 *)((int)proxy + 0xd00);
              *(undefined4 *)((int)proxy + 0xd54) = *(undefined4 *)((int)proxy + 0xd04);
              *(undefined4 *)((int)proxy + 0xd58) = *(undefined4 *)((int)proxy + 0xd08);
              *(undefined4 *)((int)proxy + 0xd5c) = *(undefined4 *)((int)proxy + 0xd0c);
              *(undefined4 *)((int)proxy + 0xd60) = *(undefined4 *)((int)proxy + 0xd10);
              *(undefined4 *)((int)proxy + 0xd64) = *(undefined4 *)((int)proxy + 0xd14);
              tVar3 = time((time_t *)0x0);
              *(time_t *)((int)proxy + 0xd20) = tVar3;
              pthread_mutex_lock(ppVar5);
              FUN_0006fb30((int)proxy + 0x3a8,(int)proxy + 0xd20);
              pthread_mutex_unlock(ppVar5);
              MapFlowSendSave(proxy);
              FUN_0008c46c(*(undefined4 *)((int)proxy + 0x4e8));
            }
            else {
              FUN_0004ad88(proxy,(int)proxy + 0xcd8,0xffffd8ea,"use current map failed");
              FUN_00026228(0x312f,"HandleNavLoadMapResult",2,6,"#9970");
            }
            *(undefined4 *)((int)proxy + 0xcd8) = 0;
            *puVar4 = 0;
            *(undefined4 *)((int)proxy + 0xce4) = 0;
          }
          else {
            puVar4 = (uint *)((int)proxy + 0xe20);
            if (uStack_34 == *(uint *)((int)proxy + 0xe24) && local_38 == *puVar4) {
              ppVar5 = (pthread_mutex_t *)((int)proxy + 0x390);
              FUN_00026228(0x3135,"HandleNavLoadMapResult",2,6,"#9971");
              pthread_mutex_lock(ppVar5);
              for (iVar2 = *(int *)((int)proxy + 0x3a8); *(int *)((int)proxy + 0x3ac) != iVar2;
                  iVar2 = iVar2 + 0x50) {
                if ((*(uint *)(iVar2 + 0x10) != 0 || *(int *)(iVar2 + 0x14) != 0) &&
                   (*(int *)(iVar2 + 0x14) == *(int *)((int)proxy + 0xe24) &&
                    *(uint *)(iVar2 + 0x10) == *puVar4)) {
                  FUN_0006fc30((int)proxy + 0x3a8);
                  break;
                }
              }
              pthread_mutex_unlock(ppVar5);
              pthread_mutex_lock((pthread_mutex_t *)((int)proxy + 0xf54));
              tVar3 = time((time_t *)0x0);
              *(time_t *)((int)proxy + 0xf6c) = tVar3;
              pthread_mutex_unlock((pthread_mutex_t *)((int)proxy + 0xf54));
              if (local_2c == 1) {
                FUN_00026228(0x3148,"HandleNavLoadMapResult",2,6,"#9972");
                ClearCleanRouting();
                FUN_00026228(0x314a,"HandleNavLoadMapResult",2,6,"#9973");
                *(undefined4 *)((int)proxy + 0xe68) = *(undefined4 *)((int)proxy + 0xe18);
                *(undefined4 *)((int)proxy + 0xe6c) = *(undefined4 *)((int)proxy + 0xe1c);
                *(undefined4 *)((int)proxy + 0xe70) = *(undefined4 *)((int)proxy + 0xe20);
                *(undefined4 *)((int)proxy + 0xe74) = *(undefined4 *)((int)proxy + 0xe24);
                *(undefined4 *)((int)proxy + 0xe78) = *(undefined4 *)((int)proxy + 0xe28);
                *(undefined4 *)((int)proxy + 0xe7c) = *(undefined4 *)((int)proxy + 0xe2c);
                *(undefined4 *)((int)proxy + 0xe80) = *(undefined4 *)((int)proxy + 0xe30);
                *(undefined4 *)((int)proxy + 0xe84) = *(undefined4 *)((int)proxy + 0xe34);
                *(undefined4 *)((int)proxy + 0xe88) = *(undefined4 *)((int)proxy + 0xe38);
                *(undefined4 *)((int)proxy + 0xe8c) = *(undefined4 *)((int)proxy + 0xe3c);
                *(undefined4 *)((int)proxy + 0xe90) = *(undefined4 *)((int)proxy + 0xe40);
                *(undefined4 *)((int)proxy + 0xe94) = *(undefined4 *)((int)proxy + 0xe44);
                *(undefined4 *)((int)proxy + 0xe98) = *(undefined4 *)((int)proxy + 0xe48);
                *(undefined4 *)((int)proxy + 0xe9c) = *(undefined4 *)((int)proxy + 0xe4c);
                *(undefined4 *)((int)proxy + 0xea0) = *(undefined4 *)((int)proxy + 0xe50);
                *(undefined4 *)((int)proxy + 0xea4) = *(undefined4 *)((int)proxy + 0xe54);
                tVar3 = time((time_t *)0x0);
                *(time_t *)((int)proxy + 0xe60) = tVar3;
                pthread_mutex_lock(ppVar5);
                FUN_0006fb30((int)proxy + 0x3a8,(int)proxy + 0xe60);
                pthread_mutex_unlock(ppVar5);
                MapFlowSendSave(proxy);
                FUN_0008c46c(*(undefined4 *)((int)proxy + 0x4e8));
              }
              else {
                FUN_0004ad88(proxy,(int)proxy + 0xe18,0xffffd8ea,"load reserve map failed");
                FUN_00026228(0x315a,"HandleNavLoadMapResult",2,6,"#9974");
              }
              *(undefined4 *)((int)proxy + 0xe18) = 0;
              *puVar4 = 0;
              *(undefined4 *)((int)proxy + 0xe24) = 0;
            }
            else {
              puVar4 = (uint *)((int)proxy + 0x790);
              if (uStack_34 == *(uint *)((int)proxy + 0x794) && local_38 == *puVar4) {
                ppVar5 = (pthread_mutex_t *)((int)proxy + 0x390);
                FUN_00026228(0x3160,"HandleNavLoadMapResult",2,6,"#9975");
                pthread_mutex_lock(ppVar5);
                for (iVar2 = *(int *)((int)proxy + 0x3a8); *(int *)((int)proxy + 0x3ac) != iVar2;
                    iVar2 = iVar2 + 0x50) {
                  if ((*(uint *)(iVar2 + 0x10) != 0 || *(int *)(iVar2 + 0x14) != 0) &&
                     (*(int *)(iVar2 + 0x14) == *(int *)((int)proxy + 0x794) &&
                      *(uint *)(iVar2 + 0x10) == *puVar4)) {
                    FUN_0006fc30((int)proxy + 0x3a8);
                    break;
                  }
                }
                pthread_mutex_unlock(ppVar5);
                pthread_mutex_lock((pthread_mutex_t *)((int)proxy + 0xf54));
                tVar3 = time((time_t *)0x0);
                *(time_t *)((int)proxy + 0xf6c) = tVar3;
                pthread_mutex_unlock((pthread_mutex_t *)((int)proxy + 0xf54));
                if (local_2c == 1) {
                  FUN_00026228(0x3173,"HandleNavLoadMapResult",2,6,"#9976");
                  ClearCleanRouting();
                  FUN_00026228(0x3175,"HandleNavLoadMapResult",2,6,"#9977");
                  *(undefined4 *)((int)proxy + 0xe68) = *(undefined4 *)((int)proxy + 0x788);
                  *(undefined4 *)((int)proxy + 0xe6c) = *(undefined4 *)((int)proxy + 0x78c);
                  *(undefined4 *)((int)proxy + 0xe70) = *(undefined4 *)((int)proxy + 0x790);
                  *(undefined4 *)((int)proxy + 0xe74) = *(undefined4 *)((int)proxy + 0x794);
                  *(undefined4 *)((int)proxy + 0xe78) = *(undefined4 *)((int)proxy + 0x798);
                  *(undefined4 *)((int)proxy + 0xe7c) = *(undefined4 *)((int)proxy + 0x79c);
                  *(undefined4 *)((int)proxy + 0xe80) = *(undefined4 *)((int)proxy + 0x7a0);
                  *(undefined4 *)((int)proxy + 0xe84) = *(undefined4 *)((int)proxy + 0x7a4);
                  *(undefined4 *)((int)proxy + 0xe88) = *(undefined4 *)((int)proxy + 0x7a8);
                  *(undefined4 *)((int)proxy + 0xe8c) = *(undefined4 *)((int)proxy + 0x7ac);
                  *(undefined4 *)((int)proxy + 0xe90) = *(undefined4 *)((int)proxy + 0x7b0);
                  *(undefined4 *)((int)proxy + 0xe94) = *(undefined4 *)((int)proxy + 0x7b4);
                  *(undefined4 *)((int)proxy + 0xe98) = *(undefined4 *)((int)proxy + 0x7b8);
                  *(undefined4 *)((int)proxy + 0xe9c) = *(undefined4 *)((int)proxy + 0x7bc);
                  *(undefined4 *)((int)proxy + 0xea0) = *(undefined4 *)((int)proxy + 0x7c0);
                  *(undefined4 *)((int)proxy + 0xea4) = *(undefined4 *)((int)proxy + 0x7c4);
                  tVar3 = time((time_t *)0x0);
                  *(time_t *)((int)proxy + 0xe60) = tVar3;
                  pthread_mutex_lock(ppVar5);
                  FUN_0006fb30((int)proxy + 0x3a8,(int)proxy + 0xe60);
                  pthread_mutex_unlock(ppVar5);
                  MapFlowSendSave(proxy);
                  FUN_0008c46c(*(undefined4 *)((int)proxy + 0x4e8));
                }
                else {
                  FUN_0004ad88(proxy,(int)proxy + 0x788,0xffffd8ea,"load reserve map failed");
                  FUN_00026228(0x3185,"HandleNavLoadMapResult",2,6,"#9978");
                }
                *(undefined4 *)((int)proxy + 0x788) = 0;
                *puVar4 = 0;
                *(undefined4 *)((int)proxy + 0x794) = 0;
              }
            }
          }
        }
      }
    }
  }
  else {
    FUN_00026228(0x308f,"HandleNavLoadMapResult",2,6,"#9957");
    FUN_0003a714(proxy,0);
    *(undefined4 *)((int)proxy + 0x968) = 0;
    *(undefined4 *)((int)proxy + 0x970) = 0;
    *(undefined4 *)((int)proxy + 0x974) = 0;
    *(undefined4 *)((int)proxy + 0xf00) = 0;
    *(undefined4 *)((int)proxy + 0xa58) = 0;
    *(undefined4 *)((int)proxy + 0xa60) = 0;
    *(undefined4 *)((int)proxy + 0xa64) = 0;
    *(undefined4 *)((int)proxy + 0xcd8) = 0;
    *(undefined4 *)((int)proxy + 0xce0) = 0;
    *(undefined4 *)((int)proxy + 0xce4) = 0;
    *(undefined4 *)((int)proxy + 0xe18) = 0;
    *(undefined4 *)((int)proxy + 0xe20) = 0;
    *(undefined4 *)((int)proxy + 0xe24) = 0;
    *(undefined4 *)((int)proxy + 0x788) = 0;
    *(undefined4 *)((int)proxy + 0x790) = 0;
    *(undefined4 *)((int)proxy + 0x794) = 0;
  }
  if (local_24 == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

