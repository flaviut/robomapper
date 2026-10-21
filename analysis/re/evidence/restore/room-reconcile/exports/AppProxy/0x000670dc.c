/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x000670dc
 */

/* WARNING: Restarted to delay deadcode elimination for space: stack */

void FUN_000670dc(int param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  char *pcVar4;
  void *__dest;
  void **__dest_00;
  undefined4 *puVar5;
  undefined4 *__dest_01;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  undefined4 extraout_r1_01;
  void *pvVar6;
  undefined4 extraout_r1_02;
  undefined4 extraout_r1_03;
  undefined4 extraout_r1_04;
  int iVar7;
  size_t sVar8;
  uint uVar9;
  uint uVar10;
  int *piVar11;
  undefined1 *puVar12;
  char *pcVar13;
  undefined4 uVar14;
  undefined1 *puVar15;
  void **local_560;
  char *local_548;
  undefined4 local_544;
  char *local_53c;
  char *local_538;
  char *local_534;
  void *local_530;
  void *local_52c;
  void *local_528;
  undefined4 local_524;
  undefined4 local_520;
  undefined4 local_51c;
  void **local_518;
  void **local_514;
  void *local_510;
  void *local_50c;
  undefined4 local_508;
  undefined4 local_504;
  undefined4 local_500;
  undefined1 local_4fc;
  int local_4f8;
  int iStack_4f4;
  undefined4 local_4f0;
  undefined4 uStack_4ec;
  undefined4 local_4e8;
  undefined4 uStack_4e4;
  undefined4 uStack_4e0;
  undefined4 uStack_4dc;
  undefined1 auStack_4d8 [20];
  undefined4 local_4c4;
  char local_498 [4];
  undefined4 local_494;
  char local_458 [100];
  undefined4 local_3f4;
  char *local_98;
  uint local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  int local_2c;
  
  local_2c = __stack_chk_guard;
  if (*(int *)(param_2 + 8) == 0x20) {
    local_4f8 = *(int *)(param_2 + 0xc);
    iStack_4f4 = *(int *)(param_2 + 0x10);
    local_4f0 = *(uint *)(param_2 + 0x14);
    uStack_4ec = *(undefined4 *)(param_2 + 0x18);
    local_4e8 = *(undefined4 *)(param_2 + 0x1c);
    uStack_4e4 = *(undefined4 *)(param_2 + 0x20);
    uStack_4e0 = *(undefined4 *)(param_2 + 0x24);
    uStack_4dc = *(undefined4 *)(param_2 + 0x28);
    FUN_00026228(0x345a,DAT_000672b4,2,6,"#10012");
    pthread_mutex_lock((pthread_mutex_t *)(param_1 + 0x390));
    for (iVar7 = *(int *)(param_1 + 0x3a8); *(int *)(param_1 + 0x3ac) != iVar7; iVar7 = iVar7 + 0x50
        ) {
      if ((*(int *)(iVar7 + 0x10) != 0 || *(int *)(iVar7 + 0x14) != 0) &&
         (*(int *)(iVar7 + 0x14) == iStack_4f4 && *(int *)(iVar7 + 0x10) == local_4f8)) {
        FUN_0006fc30(param_1 + 0x3a8);
        break;
      }
    }
    piVar11 = (int *)(param_1 + 0xa10);
    pthread_mutex_unlock((pthread_mutex_t *)(param_1 + 0x390));
    if (iStack_4f4 == *(int *)(param_1 + 0xa14) && local_4f8 == *piVar11) {
      if ((local_4f0 & 0xff) == 0) {
        FUN_0004ad88(param_1,param_1 + 0xa08,0xffffd8ea,"timer modify map failed");
        FUN_00026228(0x34d3,DAT_000679e8,2,6,"#10013");
        FUN_0003a714(param_1,0);
        *(undefined4 *)(param_1 + 0xa08) = 0;
        *piVar11 = 0;
        *(undefined4 *)(param_1 + 0xa14) = 0;
        memset((void *)(param_1 + 0xf70),0,0x400);
        memset((void *)(param_1 + 0x1370),0,0x100);
        if (local_2c == __stack_chk_guard) {
          (*(code *)PTR_memset_00120578)(param_1 + 0x1470,0,0x100);
          return;
        }
        goto LAB_00067b9a;
      }
      pcVar4 = (char *)(param_1 + 0xf70);
      uVar10 = *(byte *)(param_1 + 0x3d70) & 1;
      if ((*(byte *)(param_1 + 0x3d70) & 1) == 0) {
        rr_event_int(9,0x11,1);
        memset(&local_8c,uVar10,0x60);
        pcVar13 = (char *)((int)&local_4f0 + 1);
        uVar9 = uVar10;
        if (local_4f0._1_1_ != '\0') {
          do {
            pcVar13 = pcVar13 + 1;
            if (*pcVar13 != '\0') {
              local_94 = uVar10;
              local_90 = uVar10;
              __sprintf_chk(&local_94,1,8,&DAT_000f2c60,*pcVar13);
              __strcat_chk(&local_8c,&local_94,0x60);
            }
            uVar9 = uVar9 + 1;
          } while ((int)uVar9 < (int)(local_4f0 >> 8 & 0xff));
        }
        sVar8 = strlen((char *)&local_8c);
        *(undefined1 *)((int)&local_90 + sVar8 + 3) = 0;
        FUN_0006f0d8(auStack_4d8,0,0x400,0);
        local_53c = (char *)(param_1 + 0x1370);
        local_538 = local_53c;
        FUN_00072f88(auStack_4d8,&local_53c);
        puVar5 = (undefined4 *)FUN_0006f130(auStack_4d8,"segments");
        sVar8 = strlen((char *)&local_8c);
        if (sVar8 < 0xc) {
          puVar5[4] = 0x700005;
          *(char *)((int)puVar5 + 0xb) = '\v' - (char)sVar8;
          __dest_01 = puVar5;
        }
        else {
          puVar5[1] = sVar8;
          puVar5[4] = &DAT_00300005;
          __dest_01 = (undefined4 *)FUN_000718f4(local_4c4,sVar8 + 1);
          *puVar5 = __dest_01;
        }
        memcpy(__dest_01,&local_8c,sVar8);
        *(undefined1 *)((int)__dest_01 + sVar8) = 0;
        local_530 = (void *)0x0;
        local_52c = (void *)0x0;
        local_528 = (void *)0x0;
        local_524 = 0;
        local_520 = 0;
        local_51c = 0x100;
        local_500 = 0x100;
        local_514 = (void **)0x0;
        local_510 = (void *)0x0;
        local_50c = (void *)0x0;
        local_508 = 0;
        local_504 = 0;
        local_4fc = 0;
        local_518 = &local_530;
        FUN_00070690(auStack_4d8,&local_518);
        __strcat_chk(pcVar4,&DAT_000f3b80,0x400);
        uVar3 = FUN_0006f494(&local_530);
        sVar8 = strlen(pcVar4);
        pcVar13 = (char *)__stpcpy_chk(pcVar4 + sVar8,uVar3,0x400);
        *(undefined2 *)pcVar13 = s_array_size_less_than__d__000f9d30._24_2_;
        strncpy(local_498,pcVar4,0x3ff);
        local_98 = local_498;
        uVar3 = FUN_00086ecc();
        FUN_00087614(uVar3,local_498,1);
        free(local_50c);
        operator_delete(local_510);
        free(local_528);
        operator_delete(local_52c);
        FUN_0002ba94(auStack_4d8);
      }
      else {
        rr_event_int(9,0x11,3,1);
        local_458[0] = 'Y';
        memset(local_498,0,0x40);
        strncpy(local_498,pcVar4,0x3f);
        local_3f4 = GetSharedCurrentMapFlag();
        memset(local_458 + 1,0,0x60);
        if (local_4f0._1_1_ != '\0') {
          iVar7 = 0;
          pcVar4 = (char *)((int)&local_4f0 + 1);
          do {
            pcVar4 = pcVar4 + 1;
            if (*pcVar4 != '\0') {
              local_8c = 0;
              local_88 = 0;
              __sprintf_chk(&local_8c,1,8,&DAT_000f2c60,*pcVar4);
              __strcat_chk(local_458 + 1,&local_8c,0x60);
            }
            iVar7 = iVar7 + 1;
          } while (iVar7 < (int)(local_4f0 >> 8 & 0xff));
        }
        sVar8 = strlen(local_458 + 1);
        pcVar4 = *(char **)(param_1 + 0x3d8c);
        pcVar13 = *(char **)(param_1 + 0x3d90);
        local_458[sVar8] = '\0';
        for (; pcVar4 != pcVar13; pcVar4 = pcVar4 + 0xa8) {
          iVar7 = strcmp(pcVar4,local_498);
          if (iVar7 == 0) {
            FUN_0006fb58(param_1 + 0x3d8c,pcVar4);
            pcVar13 = *(char **)(param_1 + 0x3d90);
            break;
          }
        }
        if (pcVar13 == *(char **)(param_1 + 0x3d94)) {
          FUN_0006fb90(param_1 + 0x3d8c,local_498);
        }
        else {
          iVar7 = 0;
          if (pcVar13 != (char *)0x0) {
            memcpy(pcVar13,local_498,0xa8);
            iVar7 = *(int *)(param_1 + 0x3d90);
          }
          *(int *)(param_1 + 0x3d90) = iVar7 + 0xa8;
        }
        FUN_00039e30(param_1);
        local_514 = (void **)0x0;
        local_530 = (void *)0x0;
        local_52c = (void *)0x0;
        local_528 = (void *)0x0;
        local_524 = 0;
        local_520 = 0;
        local_510 = (void *)0x0;
        local_50c = (void *)0x0;
        local_508 = 0;
        local_504 = 0;
        local_51c = 0x100;
        local_500 = 0x100;
        local_4fc = 0;
        local_518 = &local_530;
        FUN_0006f990(&local_518);
        FUN_0007065c(&local_518,DAT_001208f8);
        iVar2 = iStack_4f4;
        iVar7 = local_4f8;
        FUN_0006f888(&local_518,6);
        FUN_0003d11c(&local_518,extraout_r1_03,iVar7,iVar2);
        FUN_0007065c(&local_518,DAT_001208fc);
        FUN_0006f904(&local_518);
        FUN_0007065c(&local_518,local_458 + 1);
        FUN_0003d218(&local_518);
        FUN_0003d244(&local_518);
        memset((char *)(param_1 + 0x1470),0,0x100);
        pcVar4 = (char *)FUN_0006f494(&local_530);
        strncpy((char *)(param_1 + 0x1470),pcVar4,0x100);
        free(local_50c);
        operator_delete(local_510);
        free(local_528);
        operator_delete(local_52c);
      }
      local_560 = &local_530;
      uVar3 = GetSharedCurrentMapFlag();
      local_498[0] = '\x01';
      local_498[1] = '\0';
      local_498[2] = '\0';
      local_498[3] = '\0';
      local_494 = uVar3;
      FUN_0006f31c(local_560,local_498,2,&local_518);
      iVar7 = *piVar11;
      uVar14 = *(undefined4 *)(param_1 + 0xa14);
      FUN_0006f234(&local_518,local_560);
      FUN_0003c6bc(param_1,extraout_r1_04,iVar7,uVar14,uVar3,&local_518);
LAB_0006729a:
      if (local_518 != (void **)0x0) {
        operator_delete(local_518);
      }
      if (local_530 != (void *)0x0) {
        operator_delete(local_530);
      }
    }
    else {
      piVar11 = (int *)(param_1 + 0xb00);
      if (iStack_4f4 == *(int *)(param_1 + 0xb04) && local_4f8 == *piVar11) {
        if ((local_4f0 & 0xff) == 0) {
          FUN_0004ad88(param_1,param_1 + 0xaf8,0xffffd8ea,"name segment modify map failed");
          FUN_00026228(0x3507,DAT_000679e8,2,6,"#10014");
          FUN_0003a714(param_1,0);
          *(undefined4 *)(param_1 + 0xaf8) = 0;
          *piVar11 = 0;
          *(undefined4 *)(param_1 + 0xb04) = 0;
        }
        else {
          rr_event_int(9,0x10,2,1);
          pvVar6 = *(void **)(param_1 + 0x3dcc);
          local_53c = (char *)0x0;
          uVar9 = *(int *)(param_1 + 0x3dd0) - (int)pvVar6;
          local_538 = (char *)0x0;
          local_534 = (char *)0x0;
          uVar10 = ((int)uVar9 >> 2) * -0x49249249;
          if (uVar10 == 0) {
            iVar7 = 0;
            pcVar4 = (char *)0x0;
            sVar8 = uVar9;
          }
          else {
            if (0x9249249 < uVar10) {
LAB_00067c04:
                    /* WARNING: Subroutine does not return */
              std::__throw_bad_alloc();
            }
            pcVar4 = operator_new(uVar9);
            pvVar6 = *(void **)(param_1 + 0x3dcc);
            sVar8 = *(int *)(param_1 + 0x3dd0) - (int)pvVar6;
            iVar7 = ((int)sVar8 >> 2) * -0x49249249;
          }
          local_534 = pcVar4 + uVar9;
          local_53c = pcVar4;
          if (iVar7 != 0) {
            local_538 = pcVar4;
            memmove(pcVar4,pvVar6,sVar8);
          }
          local_538 = pcVar4 + sVar8;
          FUN_0003c2a0(param_1,&local_53c,(int)&local_4f0 + 2);
          if (local_53c != (char *)0x0) {
            operator_delete(local_53c);
          }
          local_51c = 0x100;
          local_530 = (void *)0x0;
          local_52c = (void *)0x0;
          local_528 = (void *)0x0;
          local_524 = 0;
          local_520 = 0;
          local_514 = (void **)0x0;
          local_510 = (void *)0x0;
          local_50c = (void *)0x0;
          local_508 = 0;
          local_504 = 0;
          local_500 = 0x100;
          local_4fc = 0;
          local_518 = &local_530;
          FUN_0006f990(&local_518);
          FUN_0007065c(&local_518,DAT_001208f8);
          iVar2 = iStack_4f4;
          iVar7 = local_4f8;
          FUN_0006f888(&local_518,6);
          FUN_0003d11c(&local_518,extraout_r1_00,iVar7,iVar2);
          FUN_0007065c(&local_518,DAT_001208fc);
          FUN_0006f904(&local_518);
          if (local_4f0._1_1_ != '\0') {
            puVar12 = (undefined1 *)(param_1 + 0x3da8);
            puVar15 = (undefined1 *)((int)&local_4f0 + 1);
            iVar7 = 0;
            do {
              FUN_0006f990(&local_518);
              FUN_0007065c(&local_518,"oldId");
              puVar12 = puVar12 + 1;
              uVar1 = *puVar12;
              FUN_0006f888(&local_518,6);
              FUN_0003d180(&local_518,uVar1);
              FUN_0007065c(&local_518,"newId");
              puVar15 = puVar15 + 1;
              uVar1 = *puVar15;
              FUN_0006f888(&local_518,6);
              FUN_0003d180(&local_518,uVar1);
              FUN_0003d244(&local_518);
              iVar7 = iVar7 + 1;
            } while (iVar7 < (int)(local_4f0 >> 8 & 0xff));
          }
          FUN_0003d218(&local_518);
          FUN_0003d244(&local_518);
          memset((char *)(param_1 + 0x3df0),0,0x400);
          pcVar4 = (char *)FUN_0006f494(&local_530);
          strncpy((char *)(param_1 + 0x3df0),pcVar4,0x3ff);
          uVar3 = GetSharedCurrentMapFlag();
          local_498[0] = '\x01';
          local_498[1] = '\0';
          local_498[2] = '\0';
          local_498[3] = '\0';
          local_494 = uVar3;
          FUN_0006f31c(&local_548,local_498,2,&local_53c);
          iVar7 = *piVar11;
          uVar14 = *(undefined4 *)(param_1 + 0xb04);
          FUN_0006f234(&local_53c,&local_548);
          FUN_0003c6bc(param_1,extraout_r1_01,iVar7,uVar14,uVar3,&local_53c);
          if (local_53c != (char *)0x0) {
            operator_delete(local_53c);
          }
          if (local_548 != (char *)0x0) {
            operator_delete(local_548);
          }
          free(local_50c);
          operator_delete(local_510);
          free(local_528);
          operator_delete(local_52c);
        }
      }
      else {
        piVar11 = (int *)(param_1 + 0xc90);
        if (iStack_4f4 == *(int *)(param_1 + 0xc94) && local_4f8 == *piVar11) {
          if ((local_4f0 & 0xff) != 0) {
            rr_event_int(9,0x10,3,1);
            pvVar6 = *(void **)(param_1 + 0x3dd8);
            uVar10 = *(int *)(param_1 + 0x3ddc) - (int)pvVar6;
            local_530 = (void *)0x0;
            local_52c = (void *)0x0;
            local_528 = (void *)0x0;
            if (uVar10 * -0x55555555 == 0) {
              iVar7 = 0;
              __dest = (void *)0x0;
              sVar8 = uVar10;
            }
            else {
              if (0x55555555 < uVar10 * -0x55555555) goto LAB_00067c04;
              __dest = operator_new(uVar10);
              pvVar6 = *(void **)(param_1 + 0x3dd8);
              sVar8 = *(int *)(param_1 + 0x3ddc) - (int)pvVar6;
              iVar7 = sVar8 * -0x55555555;
            }
            local_528 = (void *)(uVar10 + (int)__dest);
            local_530 = __dest;
            if (iVar7 != 0) {
              local_52c = __dest;
              memmove(__dest,pvVar6,sVar8);
            }
            local_52c = (void *)((int)__dest + sVar8);
            FUN_0003b614(param_1,&local_530,(int)&local_4f0 + 2);
            if (local_530 != (void *)0x0) {
              operator_delete(local_530);
            }
            pvVar6 = *(void **)(param_1 + 0x3de4);
            local_518 = (void **)0x0;
            uVar10 = *(int *)(param_1 + 0x3de8) - (int)pvVar6;
            local_514 = (void **)0x0;
            local_510 = (void *)0x0;
            if ((int)uVar10 >> 3 == 0) {
              iVar7 = 0;
              __dest_00 = (void **)0x0;
              uVar9 = uVar10;
            }
            else {
              if (0x1fffffff < (uint)((int)uVar10 >> 3)) goto LAB_00067c04;
              __dest_00 = operator_new(uVar10);
              pvVar6 = *(void **)(param_1 + 0x3de4);
              uVar9 = *(int *)(param_1 + 0x3de8) - (int)pvVar6;
              iVar7 = (int)uVar9 >> 3;
            }
            local_510 = (void *)((int)__dest_00 + uVar10);
            local_518 = __dest_00;
            if (iVar7 != 0) {
              local_514 = __dest_00;
              memmove(__dest_00,pvVar6,uVar9);
            }
            local_514 = (void **)((int)__dest_00 + uVar9);
            FUN_0003b6c4(param_1,&local_518,(int)&local_4f0 + 2);
            if (local_518 != (void **)0x0) {
              operator_delete(local_518);
            }
            uVar3 = GetSharedCurrentMapFlag();
            local_548 = local_498;
            local_544 = 2;
            local_498[0] = '\x01';
            local_498[1] = '\0';
            local_498[2] = '\0';
            local_498[3] = '\0';
            local_494 = uVar3;
            FUN_0006f31c(&local_530,local_548,2,&local_518);
            iVar7 = *piVar11;
            uVar14 = *(undefined4 *)(param_1 + 0xc94);
            FUN_0006f234(&local_518,&local_530);
            FUN_0003c6bc(param_1,extraout_r1_02,iVar7,uVar14,uVar3,&local_518);
            goto LAB_0006729a;
          }
          FUN_0004ad88(param_1,param_1 + 0xc88,0xffffd8ea,"customize clean mode modify map failed");
          FUN_00026228(0x3525,DAT_000679e8,2,6,"#10015");
          FUN_0003a714(param_1,0);
          *(undefined4 *)(param_1 + 0xc88) = 0;
          *piVar11 = 0;
          *(undefined4 *)(param_1 + 0xc94) = 0;
        }
        else {
          piVar11 = (int *)(param_1 + 0xdd0);
          if (iStack_4f4 == *(int *)(param_1 + 0xdd4) && local_4f8 == *piVar11) {
            if ((local_4f0 & 0xff) != 0) {
              rr_event_int(9,0x10,4,1);
              FUN_0003ba40(param_1,local_4f0._1_1_,(int)&local_4f0 + 2);
              uVar3 = GetSharedCurrentMapFlag();
              local_53c = local_498;
              local_538 = (char *)0x2;
              local_498[0] = '\x01';
              local_498[1] = '\0';
              local_498[2] = '\0';
              local_498[3] = '\0';
              local_494 = uVar3;
              FUN_0006f31c(&local_530,local_53c,2,&local_518);
              iVar7 = *piVar11;
              uVar14 = *(undefined4 *)(param_1 + 0xdd4);
              FUN_0006f234(&local_518,&local_530);
              FUN_0003c6bc(param_1,extraout_r1,iVar7,uVar14,uVar3,&local_518);
              goto LAB_0006729a;
            }
            FUN_0004ad88(param_1,param_1 + 0xdc8,0xffffd8ea,"customize clean mode modify map failed"
                        );
            FUN_00026228(0x3542,DAT_00067c30,2,6,"#10016");
            FUN_0003a714(param_1,0);
            *(undefined4 *)(param_1 + 0xdc8) = 0;
            *piVar11 = 0;
            *(undefined4 *)(param_1 + 0xdd4) = 0;
          }
        }
      }
    }
  }
  else {
    FUN_00026228(0x344d,DAT_000672b4,2,6,"#10011");
    FUN_0003a714(param_1,0);
    *(undefined4 *)(param_1 + 0xa08) = 0;
    *(undefined4 *)(param_1 + 0xa10) = 0;
    *(undefined4 *)(param_1 + 0xa14) = 0;
    *(undefined4 *)(param_1 + 0xaf8) = 0;
    *(undefined4 *)(param_1 + 0xb00) = 0;
    *(undefined4 *)(param_1 + 0xb04) = 0;
    *(undefined4 *)(param_1 + 0xc88) = 0;
    *(undefined4 *)(param_1 + 0xc90) = 0;
    *(undefined4 *)(param_1 + 0xc94) = 0;
    *(undefined4 *)(param_1 + 0xdc8) = 0;
    *(undefined4 *)(param_1 + 0xdd0) = 0;
    *(undefined4 *)(param_1 + 0xdd4) = 0;
  }
  if (local_2c == __stack_chk_guard) {
    return;
  }
LAB_00067b9a:
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

