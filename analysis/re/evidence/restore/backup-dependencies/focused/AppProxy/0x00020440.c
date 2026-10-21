/* Decompiled C, NOT recovered source; need not compile.
 * Binary: AppProxy
 * SHA256: 24b52f58fb96303225b9b9e2d2d8ff0b85792afe9f76d8255fb813381308c457
 * Function VA: 0x00020440
 */

void FUN_00020440(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined2 uVar3;
  char cVar4;
  undefined4 uVar5;
  undefined *puVar6;
  char *pcVar7;
  int iVar8;
  size_t sVar9;
  undefined4 uVar10;
  int iVar11;
  undefined4 local_28;
  int local_24;
  
  local_24 = __stack_chk_guard;
  pcVar7 = (char *)__stpcpy_chk(param_1,&DAT_0035367c,0x40);
  cVar4 = s__rockrobo_robot_db_000eb754[0x12];
  uVar3 = s__rockrobo_robot_db_000eb754._16_2_;
  uVar2 = s__rockrobo_robot_db_000eb754._12_4_;
  uVar1 = s__rockrobo_robot_db_000eb754._8_4_;
  uVar10 = s__rockrobo_robot_db_000eb754._4_4_;
  *(undefined4 *)pcVar7 = s__rockrobo_robot_db_000eb754._0_4_;
  *(undefined4 *)(pcVar7 + 4) = uVar10;
  *(undefined4 *)(pcVar7 + 8) = uVar1;
  *(undefined4 *)(pcVar7 + 0xc) = uVar2;
  *(undefined2 *)(pcVar7 + 0x10) = uVar3;
  pcVar7[0x12] = cVar4;
  iVar8 = thunk_FUN_000e06e0(param_1,param_1 + 0x40,6,0);
  if (iVar8 == 0) {
    iVar11 = param_1 + 0x44;
    pcVar7 = (char *)__stpcpy_chk(iVar11,&DAT_0035377c,0x40);
    cVar4 = s__blackbox_db_000eb774[0xc];
    uVar1 = s__blackbox_db_000eb774._8_4_;
    uVar10 = s__blackbox_db_000eb774._4_4_;
    *(undefined4 *)pcVar7 = s__blackbox_db_000eb774._0_4_;
    *(undefined4 *)(pcVar7 + 4) = uVar10;
    *(undefined4 *)(pcVar7 + 8) = uVar1;
    pcVar7[0xc] = cVar4;
    iVar8 = thunk_FUN_000e06e0(iVar11,param_1 + 0x84,6,0);
    if (iVar8 == 0) {
      iVar11 = param_1 + 0x88;
      pcVar7 = (char *)__stpcpy_chk(iVar11,&DAT_0035367c,0x40);
      uVar2 = s__rockrobo_robot_status_db_000eb790._12_4_;
      uVar1 = s__rockrobo_robot_status_db_000eb790._8_4_;
      uVar10 = s__rockrobo_robot_status_db_000eb790._4_4_;
      *(undefined4 *)pcVar7 = s__rockrobo_robot_status_db_000eb790._0_4_;
      *(undefined4 *)(pcVar7 + 4) = uVar10;
      uVar5 = s__rockrobo_robot_status_db_000eb790._20_4_;
      uVar10 = s__rockrobo_robot_status_db_000eb790._16_4_;
      *(undefined4 *)(pcVar7 + 8) = uVar1;
      *(undefined4 *)(pcVar7 + 0xc) = uVar2;
      uVar3 = s__rockrobo_robot_status_db_000eb790._24_2_;
      *(undefined4 *)(pcVar7 + 0x10) = uVar10;
      *(undefined4 *)(pcVar7 + 0x14) = uVar5;
      *(undefined2 *)(pcVar7 + 0x18) = uVar3;
      iVar8 = thunk_FUN_000e06e0(iVar11,param_1 + 200,6,0);
      if (iVar8 == 0) {
        iVar8 = FUN_000cfa24(*(undefined4 *)(param_1 + 0x40),DAT_001207c0,0,0,&local_28);
        if (iVar8 == 0) {
          iVar8 = FUN_000cfa24(*(undefined4 *)(param_1 + 0x84),DAT_001207c4,0,0,&local_28);
          if (iVar8 == 0) {
            iVar8 = FUN_000cfa24(*(undefined4 *)(param_1 + 200),DAT_001207c8,0,0,&local_28);
            if (iVar8 == 0) {
              FUN_000cfa24(*(undefined4 *)(param_1 + 0x40),DAT_001207cc,0,0,&local_28);
              FUN_000cfa24(*(undefined4 *)(param_1 + 0x40),DAT_001207d0,0,0,&local_28);
              FUN_000cfa24(*(undefined4 *)(param_1 + 0x40),DAT_001207d4,0,0,&local_28);
              FUN_000cfa24(*(undefined4 *)(param_1 + 0x40),DAT_001207d8,0,0,&local_28);
              FUN_000cfa24(*(undefined4 *)(param_1 + 0x40),DAT_001207dc,0,0,&local_28);
              FUN_000cfa24(*(undefined4 *)(param_1 + 0x40),DAT_001207e0,0,0,&local_28);
              FUN_000cfa24(*(undefined4 *)(param_1 + 0x40),DAT_001207e4,0,0,&local_28);
              FUN_000cfa24(*(undefined4 *)(param_1 + 0x40),DAT_001207e8,0,0,&local_28);
              FUN_000cfa24(*(undefined4 *)(param_1 + 0x40),DAT_001207ec,0,0,&local_28);
              pcVar7 = DAT_001207f0;
              sVar9 = strlen(DAT_001207f0);
              iVar8 = FUN_000dcf28(*(undefined4 *)(param_1 + 0x40),pcVar7,sVar9 + 1,param_1 + 0xe0,0
                                  );
              pcVar7 = DAT_001207f4;
              if (iVar8 == 0) {
                sVar9 = strlen(DAT_001207f4);
                iVar8 = FUN_000dcf28(*(undefined4 *)(param_1 + 0x40),pcVar7,sVar9 + 1,param_1 + 0xe4
                                     ,0);
                pcVar7 = DAT_001207f8;
                if (iVar8 == 0) {
                  sVar9 = strlen(DAT_001207f8);
                  iVar8 = FUN_000dcf28(*(undefined4 *)(param_1 + 0x40),pcVar7,sVar9 + 1,
                                       param_1 + 0xe8,0);
                  pcVar7 = DAT_001207fc;
                  if (iVar8 == 0) {
                    sVar9 = strlen(DAT_001207fc);
                    iVar8 = FUN_000dcf28(*(undefined4 *)(param_1 + 0x40),pcVar7,sVar9 + 1,
                                         param_1 + 0xec,0);
                    pcVar7 = DAT_00120800;
                    if (iVar8 == 0) {
                      sVar9 = strlen(DAT_00120800);
                      iVar8 = FUN_000dcf28(*(undefined4 *)(param_1 + 0x40),pcVar7,sVar9 + 1,
                                           param_1 + 0xf4,0);
                      pcVar7 = DAT_00120804;
                      if (iVar8 == 0) {
                        sVar9 = strlen(DAT_00120804);
                        iVar8 = FUN_000dcf28(*(undefined4 *)(param_1 + 0x40),pcVar7,sVar9 + 1,
                                             param_1 + 0xf0,0);
                        pcVar7 = DAT_00120808;
                        if (iVar8 == 0) {
                          sVar9 = strlen(DAT_00120808);
                          iVar8 = FUN_000dcf28(*(undefined4 *)(param_1 + 0x40),pcVar7,sVar9 + 1,
                                               param_1 + 0xfc,0);
                          pcVar7 = DAT_0012080c;
                          if (iVar8 == 0) {
                            sVar9 = strlen(DAT_0012080c);
                            iVar8 = FUN_000dcf28(*(undefined4 *)(param_1 + 0x40),pcVar7,sVar9 + 1,
                                                 param_1 + 0xf8,0);
                            pcVar7 = DAT_00120810;
                            if (iVar8 == 0) {
                              sVar9 = strlen(DAT_00120810);
                              iVar8 = FUN_000dcf28(*(undefined4 *)(param_1 + 0x40),pcVar7,sVar9 + 1,
                                                   param_1 + 0x11c,0);
                              pcVar7 = DAT_00120814;
                              if (iVar8 == 0) {
                                sVar9 = strlen(DAT_00120814);
                                iVar8 = FUN_000dcf28(*(undefined4 *)(param_1 + 0x40),pcVar7,
                                                     sVar9 + 1,param_1 + 0x118,0);
                                pcVar7 = DAT_00120818;
                                if (iVar8 == 0) {
                                  sVar9 = strlen(DAT_00120818);
                                  iVar8 = FUN_000dcf28(*(undefined4 *)(param_1 + 0x40),pcVar7,
                                                       sVar9 + 1,param_1 + 0x124,0);
                                  pcVar7 = DAT_0012081c;
                                  if (iVar8 == 0) {
                                    sVar9 = strlen(DAT_0012081c);
                                    iVar8 = FUN_000dcf28(*(undefined4 *)(param_1 + 0x40),pcVar7,
                                                         sVar9 + 1,param_1 + 0x120,0);
                                    pcVar7 = DAT_00120820;
                                    if (iVar8 == 0) {
                                      sVar9 = strlen(DAT_00120820);
                                      iVar8 = FUN_000dcf28(*(undefined4 *)(param_1 + 0x40),pcVar7,
                                                           sVar9 + 1,param_1 + 0x128,0);
                                      pcVar7 = DAT_00120824;
                                      if (iVar8 == 0) {
                                        sVar9 = strlen(DAT_00120824);
                                        iVar8 = FUN_000dcf28(*(undefined4 *)(param_1 + 0x40),pcVar7,
                                                             sVar9 + 1,param_1 + 300,0);
                                        pcVar7 = DAT_00120828;
                                        if (iVar8 == 0) {
                                          sVar9 = strlen(DAT_00120828);
                                          iVar8 = FUN_000dcf28(*(undefined4 *)(param_1 + 0x40),
                                                               pcVar7,sVar9 + 1,param_1 + 0x130,0);
                                          pcVar7 = DAT_0012082c;
                                          if (iVar8 == 0) {
                                            sVar9 = strlen(DAT_0012082c);
                                            iVar8 = FUN_000dcf28(*(undefined4 *)(param_1 + 0x40),
                                                                 pcVar7,sVar9 + 1,param_1 + 0x138,0)
                                            ;
                                            pcVar7 = DAT_00120830;
                                            if (iVar8 == 0) {
                                              sVar9 = strlen(DAT_00120830);
                                              iVar8 = FUN_000dcf28(*(undefined4 *)(param_1 + 0x40),
                                                                   pcVar7,sVar9 + 1,param_1 + 0x134,
                                                                   0);
                                              pcVar7 = DAT_00120834;
                                              if (iVar8 == 0) {
                                                sVar9 = strlen(DAT_00120834);
                                                iVar8 = FUN_000dcf28(*(undefined4 *)(param_1 + 0x40)
                                                                     ,pcVar7,sVar9 + 1,
                                                                     param_1 + 0x13c,0);
                                                pcVar7 = DAT_00120838;
                                                if (iVar8 == 0) {
                                                  sVar9 = strlen(DAT_00120838);
                                                  iVar8 = FUN_000dcf28(*(undefined4 *)
                                                                        (param_1 + 0x40),pcVar7,
                                                                       sVar9 + 1,param_1 + 0x140,0);
                                                  pcVar7 = DAT_0012083c;
                                                  if (iVar8 == 0) {
                                                    sVar9 = strlen(DAT_0012083c);
                                                    iVar8 = FUN_000dcf28(*(undefined4 *)
                                                                          (param_1 + 0x84),pcVar7,
                                                                         sVar9 + 1,param_1 + 0xcc,0)
                                                    ;
                                                    pcVar7 = DAT_00120840;
                                                    if (iVar8 == 0) {
                                                      sVar9 = strlen(DAT_00120840);
                                                      iVar8 = FUN_000dcf28(*(undefined4 *)
                                                                            (param_1 + 0x84),pcVar7,
                                                                           sVar9 + 1,param_1 + 0xd0,
                                                                           0);
                                                      pcVar7 = DAT_00120844;
                                                      if (iVar8 == 0) {
                                                        sVar9 = strlen(DAT_00120844);
                                                        iVar8 = FUN_000dcf28(*(undefined4 *)
                                                                              (param_1 + 0x84),
                                                                             pcVar7,sVar9 + 1,
                                                                             param_1 + 0xd4,0);
                                                        pcVar7 = DAT_00120848;
                                                        if (iVar8 == 0) {
                                                          sVar9 = strlen(DAT_00120848);
                                                          iVar8 = FUN_000dcf28(*(undefined4 *)
                                                                                (param_1 + 0x84),
                                                                               pcVar7,sVar9 + 1,
                                                                               param_1 + 0xd8,0);
                                                          pcVar7 = DAT_0012084c;
                                                          if (iVar8 == 0) {
                                                            sVar9 = strlen(DAT_0012084c);
                                                            iVar8 = FUN_000dcf28(*(undefined4 *)
                                                                                  (param_1 + 0x84),
                                                                                 pcVar7,sVar9 + 1,
                                                                                 param_1 + 0xdc,0);
                                                            pcVar7 = DAT_00120850;
                                                            if (iVar8 == 0) {
                                                              sVar9 = strlen(DAT_00120850);
                                                              iVar8 = FUN_000dcf28(*(undefined4 *)
                                                                                    (param_1 + 0x84)
                                                                                   ,pcVar7,sVar9 + 1
                                                                                   ,param_1 + 0x100,
                                                                                   0);
                                                              pcVar7 = DAT_00120854;
                                                              if (iVar8 == 0) {
                                                                sVar9 = strlen(DAT_00120854);
                                                                iVar8 = FUN_000dcf28(*(undefined4 *)
                                                                                      (param_1 +
                                                                                      0x84),pcVar7,
                                                                                     sVar9 + 1,
                                                                                     param_1 + 0x104
                                                                                     ,0);
                                                                pcVar7 = DAT_00120858;
                                                                if (iVar8 == 0) {
                                                                  sVar9 = strlen(DAT_00120858);
                                                                  iVar8 = FUN_000dcf28(*(undefined4
                                                                                         *)(param_1 
                                                  + 0x84),pcVar7,sVar9 + 1,param_1 + 0x108,0);
                                                  pcVar7 = DAT_0012085c;
                                                  if (iVar8 == 0) {
                                                    sVar9 = strlen(DAT_0012085c);
                                                    iVar8 = FUN_000dcf28(*(undefined4 *)
                                                                          (param_1 + 0x84),pcVar7,
                                                                         sVar9 + 1,param_1 + 0x10c,0
                                                                        );
                                                    pcVar7 = DAT_00120860;
                                                    if (iVar8 == 0) {
                                                      sVar9 = strlen(DAT_00120860);
                                                      iVar8 = FUN_000dcf28(*(undefined4 *)
                                                                            (param_1 + 0x84),pcVar7,
                                                                           sVar9 + 1,param_1 + 0x110
                                                                           ,0);
                                                      pcVar7 = DAT_00120864;
                                                      if (iVar8 == 0) {
                                                        sVar9 = strlen(DAT_00120864);
                                                        iVar8 = FUN_000dcf28(*(undefined4 *)
                                                                              (param_1 + 0x84),
                                                                             pcVar7,sVar9 + 1,
                                                                             param_1 + 0x114,0);
                                                        pcVar7 = DAT_00120868;
                                                        if (iVar8 == 0) {
                                                          sVar9 = strlen(DAT_00120868);
                                                          iVar8 = FUN_000dcf28(*(undefined4 *)
                                                                                (param_1 + 200),
                                                                               pcVar7,sVar9 + 1,
                                                                               param_1 + 0x144,0);
                                                          pcVar7 = DAT_0012086c;
                                                          if (iVar8 == 0) {
                                                            sVar9 = strlen(DAT_0012086c);
                                                            iVar8 = FUN_000dcf28(*(undefined4 *)
                                                                                  (param_1 + 200),
                                                                                 pcVar7,sVar9 + 1,
                                                                                 param_1 + 0x148,0);
                                                            pcVar7 = DAT_00120870;
                                                            if (iVar8 == 0) {
                                                              sVar9 = strlen(DAT_00120870);
                                                              iVar8 = FUN_000dcf28(*(undefined4 *)
                                                                                    (param_1 + 200),
                                                                                   pcVar7,sVar9 + 1,
                                                                                   param_1 + 0x14c,0
                                                                                  );
                                                              pcVar7 = DAT_00120874;
                                                              if (iVar8 == 0) {
                                                                sVar9 = strlen(DAT_00120874);
                                                                iVar8 = FUN_000dcf28(*(undefined4 *)
                                                                                      (param_1 + 200
                                                                                      ),pcVar7,
                                                                                     sVar9 + 1,
                                                                                     param_1 + 0x150
                                                                                     ,0);
                                                                pcVar7 = DAT_00120878;
                                                                if (iVar8 == 0) {
                                                                  sVar9 = strlen(DAT_00120878);
                                                                  iVar8 = FUN_000dcf28(*(undefined4
                                                                                         *)(param_1 
                                                  + 200),pcVar7,sVar9 + 1,param_1 + 0x154,0);
                                                  pcVar7 = DAT_0012087c;
                                                  if (iVar8 == 0) {
                                                    sVar9 = strlen(DAT_0012087c);
                                                    iVar8 = FUN_000dcf28(*(undefined4 *)
                                                                          (param_1 + 200),pcVar7,
                                                                         sVar9 + 1,param_1 + 0x158,0
                                                                        );
                                                    puVar6 = 
                                                  PTR_s_update_cleanrecords_set_reserve2_00120880;
                                                  if (iVar8 == 0) {
                                                    sVar9 = strlen(
                                                  PTR_s_update_cleanrecords_set_reserve2_00120880);
                                                  iVar8 = FUN_000dcf28(*(undefined4 *)
                                                                        (param_1 + 0x40),puVar6,
                                                                       sVar9 + 1,param_1 + 0x15c,0);
                                                  uVar10 = 0;
                                                  if (iVar8 != 0) {
                                                    FUN_00026228(0x237,"init_db",4,3,"#8943`%s",
                                                                                                                                  
                                                  PTR_s_update_cleanrecords_set_reserve2_00120880);
                                                  *(undefined4 *)(param_1 + 0x15c) = 0;
                                                  uVar10 = 0xffffffff;
                                                  }
                                                  }
                                                  else {
                                                    FUN_00026228(0x230,"init_db",4,3,"#8942`%s",
                                                                 DAT_0012087c);
                                                    *(undefined4 *)(param_1 + 0x158) = 0;
                                                    uVar10 = 0xffffffff;
                                                  }
                                                  }
                                                  else {
                                                    FUN_00026228(0x229,"init_db",4,3,"#8941`%s",
                                                                 DAT_00120878);
                                                    *(undefined4 *)(param_1 + 0x154) = 0;
                                                    uVar10 = 0xffffffff;
                                                  }
                                                  }
                                                  else {
                                                    FUN_00026228(0x222,"init_db",4,3,"#8940`%s",
                                                                 DAT_00120874);
                                                    uVar10 = 0xffffffff;
                                                    *(undefined4 *)(param_1 + 0x150) = 0;
                                                  }
                                                  }
                                                  else {
                                                    FUN_00026228(0x21b,"init_db",4,3,"#8939`%s",
                                                                 DAT_00120870);
                                                    *(undefined4 *)(param_1 + 0x14c) = 0;
                                                    uVar10 = 0xffffffff;
                                                  }
                                                  }
                                                  else {
                                                    FUN_00026228(0x214,"init_db",4,3,"#8938`%s",
                                                                 DAT_0012086c);
                                                    *(undefined4 *)(param_1 + 0x148) = 0;
                                                    uVar10 = 0xffffffff;
                                                  }
                                                  }
                                                  else {
                                                    FUN_00026228(0x20d,"init_db",4,3,"#8937`%s",
                                                                 DAT_00120868);
                                                    *(undefined4 *)(param_1 + 0x144) = 0;
                                                    uVar10 = 0xffffffff;
                                                  }
                                                  }
                                                  else {
                                                    FUN_00026228(0x205,"init_db",4,3,"#8936`%s",
                                                                 DAT_00120864);
                                                    *(undefined4 *)(param_1 + 0x114) = 0;
                                                    uVar10 = 0xffffffff;
                                                  }
                                                  }
                                                  else {
                                                    FUN_00026228(0x1fe,"init_db",4,3,"#8935`%s",
                                                                 DAT_00120860);
                                                    *(undefined4 *)(param_1 + 0x110) = 0;
                                                    uVar10 = 0xffffffff;
                                                  }
                                                  }
                                                  else {
                                                    FUN_00026228(0x1f7,"init_db",4,3,"#8934`%s",
                                                                 DAT_0012085c);
                                                    *(undefined4 *)(param_1 + 0x10c) = 0;
                                                    uVar10 = 0xffffffff;
                                                  }
                                                  }
                                                  else {
                                                    FUN_00026228(0x1ef,"init_db",4,3,"#8933`%s",
                                                                 DAT_00120858);
                                                    *(undefined4 *)(param_1 + 0x108) = 0;
                                                    uVar10 = 0xffffffff;
                                                  }
                                                  }
                                                  else {
                                                    FUN_00026228(0x1e8,"init_db",4,3,"#8932`%s",
                                                                 DAT_00120854);
                                                    *(undefined4 *)(param_1 + 0x104) = 0;
                                                    uVar10 = 0xffffffff;
                                                  }
                                                  }
                                                  else {
                                                    FUN_00026228(0x1e1,"init_db",4,3,"#8931`%s",
                                                                 DAT_00120850);
                                                    *(undefined4 *)(param_1 + 0x100) = 0;
                                                    uVar10 = 0xffffffff;
                                                  }
                                                  }
                                                  else {
                                                    FUN_00026228(0x1d9,"init_db",4,3,"#8930`%s",
                                                                 DAT_0012084c);
                                                    uVar10 = 0xffffffff;
                                                    *(undefined4 *)(param_1 + 0xdc) = 0;
                                                  }
                                                  }
                                                  else {
                                                    FUN_00026228(0x1d2,"init_db",4,3,"#8929`%s",
                                                                 DAT_00120848);
                                                    *(undefined4 *)(param_1 + 0xd8) = 0;
                                                    uVar10 = 0xffffffff;
                                                  }
                                                  }
                                                  else {
                                                    FUN_00026228(0x1ca,"init_db",4,3,"#8928`%s",
                                                                 DAT_00120844);
                                                    *(undefined4 *)(param_1 + 0xd4) = 0;
                                                    uVar10 = 0xffffffff;
                                                  }
                                                  }
                                                  else {
                                                    FUN_00026228(0x1c3,"init_db",4,3,"#8927`%s",
                                                                 DAT_00120840);
                                                    *(undefined4 *)(param_1 + 0xd0) = 0;
                                                    uVar10 = 0xffffffff;
                                                  }
                                                  }
                                                  else {
                                                    FUN_00026228(0x1bc,"init_db",4,3,"#8926`%s",
                                                                 DAT_0012083c);
                                                    *(undefined4 *)(param_1 + 0xcc) = 0;
                                                    uVar10 = 0xffffffff;
                                                  }
                                                  }
                                                  else {
                                                    FUN_00026228(0x1b4,"init_db",4,3,"#8925`%s",
                                                                 DAT_00120838);
                                                    *(undefined4 *)(param_1 + 0x140) = 0;
                                                    uVar10 = 0xffffffff;
                                                  }
                                                }
                                                else {
                                                  FUN_00026228(0x1ae,"init_db",4,3,"#8924`%s",
                                                               DAT_00120834);
                                                  *(undefined4 *)(param_1 + 0x13c) = 0;
                                                  uVar10 = 0xffffffff;
                                                }
                                              }
                                              else {
                                                FUN_00026228(0x1a8,"init_db",4,3,"#8923`%s",
                                                             DAT_00120830);
                                                *(undefined4 *)(param_1 + 0x134) = 0;
                                                uVar10 = 0xffffffff;
                                              }
                                            }
                                            else {
                                              FUN_00026228(0x1a2,"init_db",4,3,"#8922`%s",
                                                           DAT_0012082c);
                                              *(undefined4 *)(param_1 + 0x138) = 0;
                                              uVar10 = 0xffffffff;
                                            }
                                          }
                                          else {
                                            FUN_00026228(0x19a,"init_db",4,3,"#8921`%s",DAT_00120828
                                                        );
                                            *(undefined4 *)(param_1 + 0x130) = 0;
                                            uVar10 = 0xffffffff;
                                          }
                                        }
                                        else {
                                          FUN_00026228(0x194,"init_db",4,3,"#8920`%s",DAT_00120824);
                                          uVar10 = 0xffffffff;
                                          *(undefined4 *)(param_1 + 300) = 0;
                                        }
                                      }
                                      else {
                                        FUN_00026228(0x18e,"init_db",4,3,"#8919`%s",DAT_00120820);
                                        *(undefined4 *)(param_1 + 0x128) = 0;
                                        uVar10 = 0xffffffff;
                                      }
                                    }
                                    else {
                                      FUN_00026228(0x186,"init_db",4,3,"#8918`%s",DAT_0012081c);
                                      *(undefined4 *)(param_1 + 0x120) = 0;
                                      uVar10 = 0xffffffff;
                                    }
                                  }
                                  else {
                                    FUN_00026228(0x180,"init_db",4,3,"#8917`%s",DAT_00120818);
                                    *(undefined4 *)(param_1 + 0x124) = 0;
                                    uVar10 = 0xffffffff;
                                  }
                                }
                                else {
                                  FUN_00026228(0x17a,"init_db",4,3,"#8916`%s",DAT_00120814);
                                  *(undefined4 *)(param_1 + 0x118) = 0;
                                  uVar10 = 0xffffffff;
                                }
                              }
                              else {
                                FUN_00026228(0x174,"init_db",4,3,"#8915`%s",DAT_00120810);
                                *(undefined4 *)(param_1 + 0x11c) = 0;
                                uVar10 = 0xffffffff;
                              }
                            }
                            else {
                              FUN_00026228(0x16b,"init_db",4,3,"#8914`%s",DAT_0012080c);
                              *(undefined4 *)(param_1 + 0xf8) = 0;
                              uVar10 = 0xffffffff;
                            }
                          }
                          else {
                            FUN_00026228(0x164,"init_db",4,3,"#8913`%s",DAT_00120808);
                            *(undefined4 *)(param_1 + 0xfc) = 0;
                            uVar10 = 0xffffffff;
                          }
                        }
                        else {
                          FUN_00026228(0x15c,"init_db",4,3,"#8912`%s",DAT_00120804);
                          *(undefined4 *)(param_1 + 0xf0) = 0;
                          uVar10 = 0xffffffff;
                        }
                      }
                      else {
                        FUN_00026228(0x155,"init_db",4,3,"#8911`%s",DAT_00120800);
                        *(undefined4 *)(param_1 + 0xf4) = 0;
                        uVar10 = 0xffffffff;
                      }
                    }
                    else {
                      FUN_00026228(0x14e,"init_db",4,3,"#8910`%s",DAT_001207fc);
                      uVar10 = 0xffffffff;
                      *(undefined4 *)(param_1 + 0xec) = 0;
                    }
                  }
                  else {
                    FUN_00026228(0x147,"init_db",4,3,"#8909`%s",DAT_001207f8);
                    *(undefined4 *)(param_1 + 0xe8) = 0;
                    uVar10 = 0xffffffff;
                  }
                }
                else {
                  FUN_00026228(0x140,"init_db",4,3,"#8908`%s",DAT_001207f4);
                  *(undefined4 *)(param_1 + 0xe4) = 0;
                  uVar10 = 0xffffffff;
                }
              }
              else {
                FUN_00026228(0x139,"init_db",4,3,"#8907`%s",DAT_001207f0);
                *(undefined4 *)(param_1 + 0xe0) = 0;
                uVar10 = 0xffffffff;
              }
            }
            else {
              FUN_000c6858(*(undefined4 *)(param_1 + 200));
              FUN_00026228(0x124,"init_db",4,3,"#8906`%s",local_28);
              FUN_000946f4(local_28);
              uVar10 = 0xffffffff;
            }
          }
          else {
            FUN_000c6858(*(undefined4 *)(param_1 + 0x84));
            FUN_00026228(0x11d,"init_db",4,3,"#8905`%s",local_28);
            FUN_000946f4(local_28);
            uVar10 = 0xffffffff;
          }
        }
        else {
          FUN_000c6858(*(undefined4 *)(param_1 + 0x40));
          FUN_00026228(0x116,"init_db",4,3,"#8904`%s",local_28);
          FUN_000946f4(local_28);
          uVar10 = 0xffffffff;
        }
      }
      else {
        FUN_00026228(0x10c,"init_db",4,3,"#8903`%s",iVar11);
        *(undefined4 *)(param_1 + 0x40) = 0;
        uVar10 = 0xffffffff;
      }
    }
    else {
      FUN_00026228(0x102,"init_db",4,3,"#8902`%s",iVar11);
      *(undefined4 *)(param_1 + 0x40) = 0;
      uVar10 = 0xffffffff;
    }
  }
  else {
    FUN_00026228(0xf8,"init_db",4,3,"#8901`%s",param_1);
    uVar10 = 0xffffffff;
    *(undefined4 *)(param_1 + 0x40) = 0;
  }
  if (local_24 == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar10);
}

