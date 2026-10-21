/* Decompiled C, NOT recovered source; need not compile.
 * Binary: RoboController
 * SHA256: bf1d43313dd8beaa0c802f9ae4c666138b3bb518f69b4909a746285f3f3947cf
 * Function VA: 0x000367ac
 */

void FUN_000367ac(int param_1,int *param_2)

{
  int *piVar1;
  byte bVar2;
  undefined1 uVar3;
  char cVar4;
  undefined4 uVar5;
  uint uVar6;
  void *pvVar7;
  CustomizeCleanMode *pCVar8;
  uchar *puVar9;
  int *piVar10;
  time_t tVar11;
  uint uVar12;
  byte *pbVar13;
  uint uVar14;
  int ****ppppiVar15;
  int *****pppppiVar16;
  int iVar17;
  undefined4 uVar18;
  undefined4 uVar19;
  int iVar20;
  int *****pppppiVar21;
  int *****pppppiVar22;
  int iVar23;
  int iVar24;
  uint uVar25;
  bool bVar26;
  float fVar27;
  int ****local_84;
  int ****local_80;
  int ****local_7c;
  int ****local_78;
  int ****local_74;
  int ****local_70;
  undefined4 local_6c;
  int ****local_68;
  int ****local_64;
  int ****local_60;
  int local_5c;
  int ****local_58;
  int ****ppppiStack_54;
  int ****ppppiStack_50;
  int iStack_4c;
  int ***local_48;
  int ****local_44;
  int local_40;
  int ***local_3c;
  int ****local_38;
  int local_34;
  int iStack_30;
  int local_2c;
  
  local_2c = __stack_chk_guard;
  if (param_2 == (int *)0x0) {
    __printf_chk(1,"%s,%d: ",DAT_000372d8,0x26d);
    __printf_chk(1,"Verify \'%s\' failed\n","((pRoboEvent) != NULL)");
    _IO_putc(10,stdout);
    uVar19 = 0;
    goto LAB_0003688e;
  }
  uVar6 = (**(code **)(*param_2 + 8))(param_2);
  uVar25 = DAT_0006a690;
  uVar5 = DAT_00037d48;
  uVar18 = DAT_0003765c;
  if (uVar6 == 0x848) {
    local_78 = (int ****)param_2[3];
    local_74 = (int ****)param_2[4];
    local_70 = (int ****)param_2[5];
    local_68 = local_78;
    local_64 = local_74;
    local_60 = local_70;
    uVar19 = FUN_00036668(param_1,local_78,local_74,local_70);
LAB_0003706a:
    FUN_0002d24c();
    FUN_0002df8c(&DAT_00055258,0x5a,0);
    goto LAB_0003688e;
  }
  if (uVar6 < 0x849) {
    if (uVar6 == 0x835) {
      uVar12 = param_2[3];
      bVar2 = *(byte *)(param_1 + 0x2b7);
      uVar14 = uVar12 & 1;
      uVar6 = DAT_0006a690 & 0x2000;
      *(char *)(param_1 + 0x2b7) = (char)uVar14;
      uVar25 = uVar14;
      FUN_00020728(0x2e5,DAT_0003765c,uVar6,"#13106`%d",uVar14);
      if (uVar14 != bVar2) {
        if ((0 < DAT_0006cf80) &&
           (pppppiVar16 = (int *****)access(&DAT_0006d3b8,0), pppppiVar16 == (int *****)0x0)) {
          iVar17 = rr_get_multimap_flag_available((uVar12 << 0x1e) >> 0x1f);
          if (iVar17 == 0) {
            FUN_00020728(0x2ed,DAT_0003765c,DAT_0006a690 & 0x2000,"#13107",uVar25);
            goto LAB_00036ece;
          }
          iVar17 = FUN_0002d24c();
          iVar20 = GetSharedSegmentMap();
          *(bool *)(iVar17 + 0x2d9) = iVar20 != 0;
          iVar17 = rand();
          pppppiVar22 = (int *****)time((time_t *)0x0);
          pppppiVar21 = (int *****)(iVar17 % 0x10e91959 + 0x4380b);
          iVar17 = (int)pppppiVar21 >> 0x1f;
          iVar20 = FUN_0002d24c();
          *(int ******)(iVar20 + 0x3e0) = pppppiVar22;
          *(int ******)(iVar20 + 1000) = pppppiVar21;
          *(int *)(iVar20 + 0x3ec) = iVar17;
          *(undefined4 *)(iVar20 + 0x3f0) = 0x1e;
          uVar19 = FUN_0002d24c();
          local_58 = (int ****)0x1e;
          local_68 = (int ****)pppppiVar22;
          local_60 = (int ****)pppppiVar21;
          local_5c = iVar17;
          FUN_0002ca90(uVar19,iVar17,pppppiVar22,local_64,pppppiVar21,iVar17,0x1e,ppppiStack_54);
          local_74 = (int ****)0x9e;
          local_78 = (int ****)DAT_00038090;
          local_6c = (uint)CONCAT21(local_6c._2_2_,DAT_0006cf80 == 2) << 8;
          local_70 = (int ****)pppppiVar16;
          uVar19 = FUN_0002d24c();
          FUN_00028678(uVar19,2,&local_78,0);
          FUN_00020728(0x300,DAT_00038094,DAT_0006a690 & 0x2000,"#13108");
          uVar19 = FUN_0002d24c();
          FUN_00030b00(uVar19,1);
        }
        FUN_0001cfe0(&DAT_0006cd78,0);
      }
      goto LAB_00036ece;
    }
    if (0x835 < uVar6) {
      if (uVar6 == 0x840) {
        iVar17 = param_2[3];
        *(undefined1 *)(param_1 + 0x218) = 1;
        uVar19 = 1;
        *(int *)(param_1 + 0x21c) = iVar17;
        iVar17 = FUN_0002d24c();
        iVar20 = GetSharedSegmentMap();
        *(bool *)(iVar17 + 0x2d9) = iVar20 != 0;
        iVar17 = rand();
        pppppiVar16 = (int *****)time((time_t *)0x0);
        pppppiVar22 = (int *****)(iVar17 % 0x10e91959 + 0x4380b);
        iVar17 = (int)pppppiVar22 >> 0x1f;
        iVar20 = FUN_0002d24c();
        *(int ******)(iVar20 + 0x3e0) = pppppiVar16;
        *(int ******)(iVar20 + 1000) = pppppiVar22;
        *(int *)(iVar20 + 0x3ec) = iVar17;
        *(undefined4 *)(iVar20 + 0x3f0) = 0x1e;
        uVar18 = FUN_0002d24c();
        local_58 = (int ****)0x1e;
        local_68 = (int ****)pppppiVar16;
        local_60 = (int ****)pppppiVar22;
        local_5c = iVar17;
        FUN_0002ca90(uVar18,iVar17,pppppiVar16,local_64,pppppiVar22,iVar17,0x1e,ppppiStack_54);
        local_74 = (int ****)0x9e;
        local_78 = (int ****)DAT_000379dc;
        local_70 = (int ****)0x0;
        local_6c = CONCAT22(local_6c._2_2_,1);
        uVar18 = FUN_0002d24c();
        FUN_00028678(uVar18,2,&local_78,0);
        FUN_00020728(0x49d,DAT_000379d4,DAT_0006a690 & 0x2000,"#13143");
        uVar18 = FUN_0002d24c();
        FUN_00030b00(uVar18,1);
        goto LAB_0003688e;
      }
      if (uVar6 < 0x841) {
        if (uVar6 == 0x838) {
          uVar19 = 1;
          FUN_00020728(0x453,DAT_000379d4,DAT_0006a690 & 0x2000,"#13137");
          local_68 = (int ****)DAT_000379d8;
          local_60 = (int ****)0x0;
          local_5c = DAT_0006cf78;
          local_64 = (int ****)0x839;
          FUN_00028678(param_1,3,&local_68,0);
          FUN_00020728(0x458,DAT_000379d4,DAT_0006a690 & 0x2000,"#13138`%d",local_5c);
          goto LAB_0003688e;
        }
        if (uVar6 < 0x839) {
          if (uVar6 == 0x836) {
            iVar17 = param_2[4];
            iVar20 = param_2[5];
            if (iVar17 != 0 || iVar20 != 0) {
              piVar10 = (int *)(param_1 + 0x3b8);
              if (iVar20 == *(int *)(param_1 + 0x3bc) && iVar17 == *piVar10) {
                FUN_00020728(0x3a1,DAT_00038410,DAT_0006a690 & 0x2000,"#13122");
                uVar19 = FUN_0002d24c();
                FUN_0002cae8(uVar19,*(undefined4 *)(param_1 + 0x3bc),
                             *(undefined4 *)(param_1 + 0x3b0),*(undefined4 *)(param_1 + 0x3b4),
                             *piVar10,*(undefined4 *)(param_1 + 0x3bc),
                             *(undefined4 *)(param_1 + 0x3c0),*(undefined4 *)(param_1 + 0x3c4));
                if (param_2[7] == 1) {
                  FUN_00020728(0x3a6,DAT_00038714,DAT_0006a690 & 0x2000,"#13123");
                  if ((*(char *)(param_1 + 0x218) == '\0') || (*(int *)(param_1 + 0x21c) == -1)) {
                    iVar17 = GetSharedCurrentMapFlag();
                    if (iVar17 == -1) {
                      iVar17 = InsertMultiMap(param_2[6]);
                      if (iVar17 == 0) {
                        FUN_00020728(0x3ae,DAT_00038714,DAT_0006a690 & 0x2000,"#13124");
                        uVar19 = 1;
                        goto LAB_0003688e;
                      }
                      FUN_0002c014(param_1);
                    }
                  }
                  else {
                    SetSharedCurrentMapFlag();
                  }
                  local_78 = (int ****)*piVar10;
                  local_74 = *(int *****)(param_1 + 0x3bc);
                  iVar17 = param_2[6];
                  piVar1 = (int *)(param_1 + 0x3d0);
                  *piVar1 = (int)local_78;
                  *(int *****)(param_1 + 0x3d4) = local_74;
                  *(undefined4 *)(param_1 + 0x3d8) = *(undefined4 *)(param_1 + 0x3c0);
                  *(undefined4 *)(param_1 + 0x3c8) = *(undefined4 *)(param_1 + 0x3b0);
                  *(int *)(param_1 + 0x410) = iVar17;
                  local_70 = (int ****)0x0;
                  local_6c = 0;
                  iVar17 = rr_check_has_bak_map(iVar17);
                  if ((iVar17 == 0) || (*(char *)(param_1 + 0x218) != '\0')) {
                    pppppiVar16 = (int *****)rr_get_available_bak_map_flag_for_multimap(param_2[6]);
                    if (pppppiVar16 == (int *****)0xffffffff) {
                      FUN_00020728(0x3e2,DAT_00038714,DAT_0006a690 & 0x2000,"#13129");
                      goto LAB_00038292;
                    }
                    local_60 = (int ****)0x0;
                    local_58 = local_78;
                    ppppiStack_54 = local_74;
                    iStack_4c = local_6c;
                    local_68 = (int ****)DAT_00038718;
                    local_64 = (int ****)0x3c;
                    local_70 = (int ****)pppppiVar16;
                    ppppiStack_50 = (int ****)pppppiVar16;
                    uVar19 = FUN_0002d24c();
                    FUN_00028678(uVar19,2,&local_68,0);
                    FUN_00020728(0x3ec,DAT_00038714,DAT_0006a690 & 0x2000,"#13130`%d",pppppiVar16);
                    uVar19 = FUN_0002d24c();
                    FUN_0002ca90(uVar19,*(undefined4 *)(param_1 + 0x3d4),
                                 *(undefined4 *)(param_1 + 0x3c8),*(undefined4 *)(param_1 + 0x3cc),
                                 *piVar1,*(undefined4 *)(param_1 + 0x3d4),
                                 *(undefined4 *)(param_1 + 0x3d8),*(undefined4 *)(param_1 + 0x3dc));
                  }
                  else {
                    uVar19 = FUN_0002d24c();
                    FUN_00030958(uVar19,param_2[6],*piVar1,*(undefined4 *)(param_1 + 0x3d4),
                                 param_2[6],*(undefined4 *)(param_1 + 0x3d8));
                    *piVar1 = 0;
                    *(undefined4 *)(param_1 + 0x3d4) = 0;
                  }
                }
                else {
LAB_00038292:
                  uVar19 = FUN_0002d24c();
                  FUN_00030b00(uVar19,0);
                  if (*(char *)(param_1 + 0x218) != '\0') {
                    FUN_000365ec(param_1,0);
                  }
                }
                uVar19 = 1;
                *piVar10 = 0;
                *(undefined4 *)(param_1 + 0x3bc) = 0;
                goto LAB_0003688e;
              }
              piVar10 = (int *)(param_1 + 0x3d0);
              if (iVar20 == *(int *)(param_1 + 0x3d4) && iVar17 == *piVar10) {
                FUN_00020728(0x3fe,DAT_00038410,DAT_0006a690 & 0x2000,"#13131");
                uVar19 = FUN_0002d24c();
                FUN_0002cae8(uVar19,*(undefined4 *)(param_1 + 0x3d4),
                             *(undefined4 *)(param_1 + 0x3c8),*(undefined4 *)(param_1 + 0x3cc),
                             *piVar10,*(undefined4 *)(param_1 + 0x3d4),
                             *(undefined4 *)(param_1 + 0x3d8),*(undefined4 *)(param_1 + 0x3dc));
                UpdateBakMapForMultiMap(*(int *)(param_1 + 0x410),param_2[6]);
                if (param_2[7] == 1) {
                  FUN_00020728(0x406,DAT_00038714,DAT_0006a690 & 0x2000,"#13132");
                  uVar19 = FUN_0002d24c();
                  FUN_00030958(uVar19,param_2[6],*piVar10,*(undefined4 *)(param_1 + 0x3d4),
                               param_2[6],*(undefined4 *)(param_1 + 0x3d8));
                }
                else {
                  uVar19 = FUN_0002d24c();
                  FUN_00030b00(uVar19,0);
                  if (*(char *)(param_1 + 0x218) != '\0') {
                    FUN_000365ec(param_1,0);
                  }
                }
                uVar19 = 1;
                *piVar10 = 0;
                *(undefined4 *)(param_1 + 0x3d4) = 0;
                goto LAB_0003688e;
              }
              piVar10 = (int *)(param_1 + 0x3a0);
              if (iVar20 == *(int *)(param_1 + 0x3a4) && iVar17 == *piVar10) {
                FUN_00020728(0x411,DAT_0003765c,DAT_0006a690 & 0x2000,"#13133");
                uVar19 = FUN_0002d24c();
                FUN_00030b00(uVar19,0);
                uVar19 = FUN_0002d24c();
                FUN_0002cae8(uVar19,*(undefined4 *)(param_1 + 0x3a4),
                             *(undefined4 *)(param_1 + 0x398),*(undefined4 *)(param_1 + 0x39c),
                             *piVar10,*(undefined4 *)(param_1 + 0x3a4),
                             *(undefined4 *)(param_1 + 0x3a8),*(undefined4 *)(param_1 + 0x3ac));
                cVar4 = *(char *)(param_1 + 0x218);
                if (param_2[7] == 1) {
                  FUN_00020728(0x418,DAT_00038714,DAT_0006a690 & 0x2000,"#13134");
                  if (*(char *)(param_1 + 0x218) != '\0') {
                    FUN_000365ec(param_1,1);
                  }
                  *piVar10 = 0;
                  *(undefined4 *)(param_1 + 0x3a4) = 0;
                  if (cVar4 != '\0') goto LAB_00036ece;
                }
                else {
                  if (cVar4 != '\0') {
                    FUN_000365ec(param_1,0);
                    uVar19 = 1;
                    *piVar10 = 0;
                    *(undefined4 *)(param_1 + 0x3a4) = 0;
                    goto LAB_0003688e;
                  }
                  *piVar10 = 0;
                  *(undefined4 *)(param_1 + 0x3a4) = 0;
                }
                FUN_00020728(0x426,DAT_0003765c,DAT_0006a690 & 0x2000,"#13135`%d",
                             *(undefined4 *)(param_1 + 0x4b0));
                iVar17 = FUN_00030508(param_1);
                if ((iVar17 == 8) && (*(int *)(param_1 + 0x4b0) != -1)) {
                  iVar17 = FUN_0002d24c();
                  iVar17 = *(int *)(iVar17 + 0x1a4);
                  if (iVar17 != 0) {
                    if (*(char *)(iVar17 + 8) != '\0') {
                      FUN_000356f0(iVar17);
                    }
                    FUN_00035868(iVar17,1000);
                    uVar19 = 1;
                    goto LAB_0003688e;
                  }
                }
                iVar17 = FUN_0002d24c();
                if ((0 < DAT_0006cf80) && (*(char *)(iVar17 + 0x2b7) != '\0')) {
                  uVar18 = FUN_0002d24c();
                  uVar19 = 1;
                  FUN_00031848(uVar18,DAT_0006cf80 == 2);
                  goto LAB_0003688e;
                }
              }
            }
          }
          else {
            if (uVar6 != 0x837) goto LAB_000370e6;
            FUN_00020728(0x443,DAT_000372d8,DAT_0006a690 & 0x2000,"#13136");
            if (param_2[7] == 1) {
              iVar17 = FUN_0002d24c();
              *(undefined1 *)(iVar17 + 0x414) = 1;
              uVar19 = FUN_0002d24c();
              FUN_0002eeec(uVar19,3,0x291,0);
              uVar19 = 1;
              goto LAB_0003688e;
            }
          }
          goto LAB_00036ece;
        }
        if (uVar6 == 0x83d) {
          uVar19 = FUN_00036404(param_1,param_2[3]);
          goto LAB_0003706a;
        }
        if (uVar6 == 0x83e) {
          FUN_00020728(0x483,DAT_00037d48,DAT_0006a690 & 0x2000,"#13142");
          uVar19 = FUN_00036470(param_1);
          goto LAB_0003688e;
        }
        if (uVar6 == 0x83a) {
          uVar19 = 1;
          FUN_00020728(0x46b,DAT_00036b4c,DAT_0006a690 & 0x2000,"#13140");
          local_68 = (int ****)DAT_00036b58;
          local_60 = (int ****)0x0;
          local_5c = DAT_0006cf7c;
          local_64 = (int ****)0x83b;
          FUN_00028678(param_1,3,&local_68,0);
          FUN_00020728(0x470,DAT_00036b4c,DAT_0006a690 & 0x2000,"#13141`%d",local_5c);
          goto LAB_0003688e;
        }
      }
      else {
        if (uVar6 == 0x844) {
          FUN_00020728(0x4df,DAT_0003765c,DAT_0006a690 & 0x2000,"#13148");
          local_3c = (int ***)param_2[3];
          local_38 = (int ****)param_2[4];
          local_34 = param_2[5];
          iStack_30 = param_2[6];
          uVar19 = 1;
          FUN_0001b940(&local_3c);
          goto LAB_0003688e;
        }
        if (0x844 < uVar6) {
          if (uVar6 == 0x846) {
            uVar19 = 1;
            FUN_00020728(0x4fc,DAT_000372d8,DAT_0006a690 & 0x2000,"#13151");
            SetSharedUseNewMap(true);
            FUN_0001cfe0(&DAT_0006cd78,0);
          }
          else if (uVar6 < 0x847) {
            uVar19 = 1;
            FUN_00020728(0x4ec,DAT_000372d8,DAT_0006a690 & 0x2000,"#13149");
            iVar24 = param_2[3];
            iVar23 = param_2[4];
            iVar20 = param_2[5];
            iVar17 = param_2[6];
            FUN_00020728(0x4f2,DAT_000372d8,DAT_0006a690 & 0x2000,&DAT_000553e4,iVar24,iVar23,iVar20
                         ,iVar17);
            *(int *)(param_1 + 0x424) = iVar24;
            *(int *)(param_1 + 0x428) = iVar23;
            *(int *)(param_1 + 0x42c) = iVar20;
            *(int *)(param_1 + 0x430) = iVar17;
          }
          else {
            iVar17 = param_2[3];
            FUN_00020728(0x509,DAT_00036f24,DAT_0006a690 & 0x2000,"#13152`%d",iVar17);
            SetSharedCurrentMapFlag(iVar17);
            uVar19 = 1;
          }
          goto LAB_0003688e;
        }
        if (uVar6 == 0x842) {
          FUN_00020728(0x4a4,DAT_000372d8,DAT_0006a690 & 0x2000,"#13144");
          piVar10 = (int *)FUN_0002d940(param_1);
          iVar17 = (**(code **)(*piVar10 + 0x14))();
          if ((iVar17 != 0xf) || (iVar17 = FUN_00030508(param_1), iVar17 != 6)) {
            FUN_0002d24c();
            FUN_0002df8c("positioning",0x5a,0);
          }
          if (((*(byte *)(param_1 + 0x114) & 0xf) != 0) &&
             (iVar17 = FUN_00030508(param_1), iVar17 == 6)) {
            FUN_00033af0(param_1,0x40);
          }
          iVar17 = FUN_00030508(param_1);
          if (iVar17 == 0x1d) {
            FUN_0003d828();
            uVar19 = 1;
            goto LAB_0003688e;
          }
          goto LAB_00036ece;
        }
        if (uVar6 == 0x843) {
          FUN_00020728(0x4c4,DAT_000372d8,DAT_0006a690 & 0x2000,"#13146");
          uVar19 = FUN_0002d24c();
          FUN_0002eeec(uVar19,3,0x291,0);
          piVar10 = (int *)FUN_0002d940(param_1);
          iVar17 = (**(code **)(*piVar10 + 0x14))();
          if ((iVar17 != 0xf) || (iVar17 = FUN_00030508(param_1), iVar17 != 6)) {
            if (param_2[3] == 0) {
              FUN_0002d24c();
              FUN_0002df8c("positioning_success",0x5a,0);
              uVar19 = 0;
              goto LAB_0003688e;
            }
            if (param_2[3] == 1) {
              FUN_0002d24c();
              uVar19 = 0;
              FUN_0002df8c("positioning_map_changed",0x5a);
              goto LAB_0003688e;
            }
          }
        }
      }
LAB_000370e6:
      uVar19 = 0;
      goto LAB_0003688e;
    }
    if (uVar6 == 0x7da) {
      uVar3 = (undefined1)param_2[3];
      piVar10 = param_2 + 4;
      iVar17 = *piVar10;
      local_44 = (int ****)*piVar10;
      piVar1 = param_2 + 5;
      iVar20 = *piVar1;
      local_40 = *piVar1;
      local_3c = (int ***)CONCAT31((int3)((uint)param_2[3] >> 8),uVar3);
      local_48 = local_3c;
      local_38 = local_44;
      local_34 = local_40;
      FUN_00020728(0x2bd,DAT_000379d4,DAT_0006a690 & 0x2000,"#13104`%d`%d`%d`%d`%d",uVar3,
                   (short)*piVar10,*(undefined2 *)((int)param_2 + 0x12),(short)*piVar1,
                   *(undefined2 *)((int)param_2 + 0x16));
      local_48 = (int ***)CONCAT31(local_48._1_3_,uVar3);
      local_44 = (int ****)iVar17;
      local_40 = iVar20;
      uVar19 = FUN_00036068(param_1,local_48,iVar17,iVar20);
      goto LAB_0003688e;
    }
    if (uVar6 < 0x7db) {
      if (uVar6 == 0x7d3) {
        uVar19 = FUN_0002094c(param_2);
        FUN_00020728(0x287,DAT_000379d4,uVar25 & 0x2000,"#13098`%s",uVar19);
        *(int *)(param_1 + 0x33c) = param_2[3];
        uVar19 = FUN_00035ce8(param_1);
        goto LAB_0003688e;
      }
      if (uVar6 < 0x7d4) {
        if (uVar6 == 0x237) {
          FUN_00020728(0x689,DAT_000372d8,DAT_0006a690 & 0x2000,"#13173`%d",param_2[3]);
          uVar19 = 1;
          goto LAB_0003688e;
        }
        if (uVar6 == 0x7d2) {
          uVar19 = FUN_00018b2c(param_2[3]);
          FUN_00020728(0x27d,DAT_000372d8,uVar25 & 0x2000,"#13097`%s",uVar19);
          uVar19 = FUN_00035b50(param_1,param_2);
          goto LAB_0003688e;
        }
      }
      else {
        if (uVar6 == 0x7d7) {
          iVar17 = param_2[3];
          FUN_00020728(0x2a7,DAT_000379d4,DAT_0006a690 & 0x2000,"#13101`%d",(char)iVar17);
          uVar19 = FUN_00035d38(param_1,(char)iVar17);
          goto LAB_0003688e;
        }
        if (uVar6 == 0x7d8) {
          FUN_00020728(0x2ad,DAT_000379d4,DAT_0006a690 & 0x2000,"#13102");
          uVar19 = FUN_00035d78(param_1);
          goto LAB_0003688e;
        }
        if (uVar6 == 0x7d6) {
          FUN_00020728(0x292,DAT_00036b4c,DAT_0006a690 & 0x2000,"#13099");
          uVar19 = FUN_00035998(param_1,param_2);
          goto LAB_0003688e;
        }
      }
      goto LAB_000370e6;
    }
    if (uVar6 == 0x7e0) {
      FUN_00020728(0x2b3,DAT_00037d48,DAT_0006a690 & 0x2000,"#13103");
      uVar19 = FUN_00035df4(param_1);
      goto LAB_0003688e;
    }
    if (uVar6 < 0x7e1) {
      if (uVar6 == 0x7db) {
        FUN_00020728(0x2c3,DAT_00037d48,DAT_0006a690 & 0x2000,"#13105");
        uVar19 = FUN_000361dc(param_1);
        goto LAB_0003688e;
      }
      if (uVar6 == 0x7df) {
        uVar19 = FUN_0003629c(param_1,param_2[3]);
        goto LAB_0003706a;
      }
      goto LAB_000370e6;
    }
    if (uVar6 == 0x7e2) {
      FUN_00020728(0x397,DAT_0003765c,DAT_0006a690 & 0x2000,"#13121");
      uVar19 = FUN_00036344(param_1);
      goto LAB_0003688e;
    }
    if (uVar6 < 0x7e2) {
      DAT_0006a784 = param_2[3];
      uVar19 = 1;
      FUN_00020728(0x1d4,DAT_00037658,DAT_0006a690 & 0x2000,"#13089`%d",DAT_0006a784);
      goto LAB_0003688e;
    }
    if (uVar6 != 0x834) goto LAB_000370e6;
    iVar17 = FUN_0002d24c();
    if (*(char *)(iVar17 + 0x2da) == '\0') goto LAB_00036ece;
    iVar17 = param_2[3];
    FUN_00020728(0x311,DAT_00036f24,DAT_0006a690 & 0x2000,"#13109`%d",(char)iVar17);
    *(undefined4 *)(param_1 + 0x504) = 0xffffffff;
    if ((char)iVar17 == '\0') {
      uVar19 = FUN_0002d24c();
      FUN_00030b00(uVar19,0);
      ppppiVar15 = (int ****)(uint)*(byte *)(param_1 + 0x218);
      if (ppppiVar15 == (int ****)0x0) {
        local_68 = ppppiVar15;
        local_64 = ppppiVar15;
        local_60 = ppppiVar15;
        local_68 = operator_new(4);
        local_64 = local_68 + 1;
        *local_68 = (int ***)DAT_0005500c;
        local_60 = local_64;
        uVar19 = FUN_0002d24c();
        iVar17 = rand();
        tVar11 = time((time_t *)0x0);
        iVar17 = iVar17 % 0x10e91959 + 0x4380b;
        FUN_00031a2c(uVar19,&local_68,iVar17,iVar17 >> 0x1f,0xffffffff,&local_68,tVar11,3,0xffffffff
                    );
        pppppiVar16 = (int *****)local_68;
        goto joined_r0x00037fac;
      }
      FUN_000365ec(param_1,0);
    }
    else {
      uVar19 = FUN_0002d24c();
      FUN_0002eeec(uVar19,3,0x291,0);
      uVar19 = FUN_0002d24c();
      FUN_0002ae7c(uVar19,0x28,0);
      local_68 = *(int *****)(param_1 + 1000);
      local_64 = *(int *****)(param_1 + 0x3ec);
      *(int *)(param_1 + 0x3b8) = (int)local_68;
      *(int *****)(param_1 + 0x3bc) = local_64;
      *(undefined4 *)(param_1 + 0x3b0) = *(undefined4 *)(param_1 + 0x3e0);
      *(undefined4 *)(param_1 + 0x3c0) = *(undefined4 *)(param_1 + 0x3f0);
      local_60 = (int ****)0x0;
      local_5c = 0;
      if ((*(char *)(param_1 + 0x218) == '\0') ||
         (pppppiVar22 = *(int ******)(param_1 + 0x21c), pppppiVar16 = pppppiVar22,
         pppppiVar22 == (int *****)0xffffffff)) {
        pppppiVar22 = (int *****)GetSharedCurrentMapFlag();
        pppppiVar16 = pppppiVar22;
        FUN_00020728(0x329,DAT_00038094,DAT_0006a690 & 0x2000,"#13110`%d",pppppiVar22);
        if ((pppppiVar22 == (int *****)0xffffffff) &&
           (pppppiVar22 = (int *****)rr_get_unused_persist_map_flag(false),
           pppppiVar22 == (int *****)0xffffffff)) {
          FUN_00020728(0x337,DAT_00038714,DAT_0006a690 & 0x2000,"#13111",pppppiVar16);
          uVar19 = FUN_0002d24c();
          FUN_00030b00(uVar19,0);
          uVar19 = 1;
          uVar18 = FUN_0002d24c();
          FUN_0002cae8(uVar18,*(undefined4 *)(param_1 + 0x3ec),*(undefined4 *)(param_1 + 0x3e0),
                       *(undefined4 *)(param_1 + 0x3e4),*(int *)(param_1 + 1000),
                       *(undefined4 *)(param_1 + 0x3ec),*(undefined4 *)(param_1 + 0x3f0),
                       *(undefined4 *)(param_1 + 0x3f4));
          goto LAB_0003688e;
        }
        local_60 = (int ****)pppppiVar22;
        FUN_00020728(0x33f,DAT_00038094,DAT_0006a690 & 0x2000,"#13112`%d",pppppiVar22);
        pppppiVar16 = (int *****)local_60;
        if (*(char *)(param_1 + 0x218) != '\0') goto LAB_00036c24;
      }
      else {
LAB_00036c24:
        local_60 = (int ****)pppppiVar16;
        pvVar7 = operator_new__(0x380);
        SetRoomIdMapping(0,pvVar7);
        SetRoomIdMapping(1,pvVar7,0);
        pCVar8 = operator_new__(0x30);
        SetCustomizeCleanMode(pCVar8,0);
        operator_delete__(pCVar8);
        puVar9 = operator_new__(0x10);
        SetCleanSequence(puVar9,0);
        operator_delete__(pvVar7);
        operator_delete__(puVar9);
      }
      local_3c = (int ***)0x1;
      local_84 = (int ****)0x0;
      local_80 = (int ****)0x0;
      local_7c = (int ****)0x0;
      local_38 = (int ****)pppppiVar22;
      local_84 = operator_new(8);
      local_80 = local_84 + 2;
      *local_84 = local_3c;
      local_84[1] = (int ***)local_38;
      local_7c = local_80;
      pbVar13 = (byte *)GetBakMapList((int)pppppiVar22);
      if (pbVar13 == (byte *)0x0) {
        pppppiVar16 = (int *****)0xffffffff;
      }
      else {
        pppppiVar16 = (int *****)(uint)*pbVar13;
      }
      iVar17 = GetBakMapFlagStartPos();
      bVar26 = (int)pppppiVar16 < iVar17;
      if (bVar26) {
        FUN_00020728(0x361,DAT_00036f24,DAT_0006a690 & 0x2000,"#13114");
        pppppiVar16 = (int *****)rr_get_available_bak_map_flag_for_multimap((int)pppppiVar22);
      }
      pppppiVar21 = pppppiVar16;
      FUN_00020728(0x365,DAT_00036f24,DAT_0006a690 & 0x2000,"#13115`%d",pppppiVar16);
      iVar17 = GetBakMapFlagStartPos();
      if ((int)pppppiVar16 < iVar17) {
        FUN_00020728(0x376,DAT_00038410,DAT_0006a690 & 0x2000,"#13119",pppppiVar21);
      }
      else {
        if (bVar26) {
          iVar17 = 0;
        }
        else {
          iVar17 = FUN_0001d4c4(&DAT_0006cd78,(int)pppppiVar22 + -2);
        }
        iVar20 = iVar17;
        FUN_00020728(0x36a,DAT_00036f24,DAT_0006a690 & 0x2000,"#13116`%d",iVar17);
        if ((iVar17 < 0) || (iVar17 % 5 != 0)) {
          FUN_00020728(0x36c,DAT_00036f24,DAT_0006a690 & 0x2000,"#13117",iVar20);
          if (iVar17 < 0) goto LAB_00036d86;
        }
        else {
          local_78 = (int ****)pppppiVar16;
          if (local_80 == local_7c) {
            FUN_0003876c(&local_84,&local_78);
          }
          else {
            if ((int *****)local_80 != (int *****)0x0) {
              *local_80 = (int ***)pppppiVar16;
            }
            local_80 = local_80 + 1;
          }
          uVar25 = DAT_0006a690;
          *(int ******)(param_1 + 0x504) = pppppiVar16;
          FUN_00020728(0x370,DAT_00038410,uVar25 & 0x2000,"#13118",iVar20);
        }
        FUN_0001d4d4(&DAT_0006cd78,(int)pppppiVar22 + -2,iVar17 + 1);
      }
LAB_00036d86:
      FUN_00031a2c(param_1,&local_84,*(int *)(param_1 + 0x3b8),*(undefined4 *)(param_1 + 0x3bc),
                   local_60,&local_84,*(undefined4 *)(param_1 + 0x3b0),
                   *(undefined4 *)(param_1 + 0x3c0),*(undefined4 *)(param_1 + 0x504));
      iVar17 = FUN_0002d24c();
      if (*(char *)(iVar17 + 0x2d9) == '\0') {
        FUN_00020728(0x37c,DAT_00036f24,DAT_0006a690 & 0x2000,"#13120");
        local_74 = (int ****)0x125;
        local_70 = (int ****)0x0;
        local_78 = (int ****)DAT_00036f28;
        uVar19 = FUN_0002d24c();
        FUN_00028678(uVar19,3,&local_78,0);
      }
      FUN_0002d24c();
      FUN_0002c7ac();
      pppppiVar16 = (int *****)local_84;
joined_r0x00037fac:
      if (pppppiVar16 != (int *****)0x0) {
        operator_delete(pppppiVar16);
      }
    }
    uVar18 = FUN_0002d24c();
    uVar19 = 1;
    FUN_0002cae8(uVar18,*(undefined4 *)(param_1 + 0x3ec),*(undefined4 *)(param_1 + 0x3e0),
                 *(undefined4 *)(param_1 + 0x3e4),*(undefined4 *)(param_1 + 1000),
                 *(undefined4 *)(param_1 + 0x3ec),*(undefined4 *)(param_1 + 0x3f0),
                 *(undefined4 *)(param_1 + 0x3f4));
    goto LAB_0003688e;
  }
  if (uVar6 == 0x85d) {
    uVar19 = 1;
    *(undefined1 *)(param_1 + 0x4ce) = 1;
    FUN_00030540(param_1);
    goto LAB_0003688e;
  }
  if (0x85d < uVar6) {
    if (uVar6 == 0x869) {
      local_60 = (int ****)0x0;
      uVar19 = 1;
      local_5c = CONCAT31(local_5c._1_3_,*(undefined1 *)(param_1 + 0x4d8));
      local_68 = (int ****)DAT_00037d4c;
      local_64 = (int ****)0x85e;
      uVar18 = FUN_0002d24c();
      FUN_00028678(uVar18,4,&local_68,0);
      goto LAB_0003688e;
    }
    if (0x869 < uVar6) {
      if (uVar6 == 0x876) {
        if (param_2[3] == DAT_0006d124) {
          uVar19 = 1;
          FUN_0001d418(&DAT_0006cd78,0);
          FUN_00030508(param_1);
          FUN_0002d744();
          goto LAB_0003688e;
        }
      }
      else {
        if (uVar6 < 0x877) {
          if (uVar6 == 0x86c) {
            iVar17 = param_2[3];
            *(int *)(param_1 + 0x4b4) = iVar17;
            uVar19 = 1;
            FUN_00020728(0x667,uVar5,uVar25 & 0x2000,"#13170`%d",iVar17);
            goto LAB_0003688e;
          }
          if (uVar6 != 0x873) {
            if (uVar6 == 0x86a) {
              uVar19 = 1;
              FUN_00020728(0x67a,DAT_00036b4c,DAT_0006a690 & 0x2000,"#13171");
              local_68 = (int ****)DAT_00036b50;
              local_60 = (int ****)0x0;
              local_5c = DAT_0006d120;
              local_64 = (int ****)0x86b;
              FUN_00028678(param_1,3,&local_68,0);
              FUN_00020728(0x67f,DAT_00036b4c,DAT_0006a690 & 0x2000,"#13172`%d",local_5c);
              goto LAB_0003688e;
            }
            goto LAB_000370e6;
          }
          iVar24 = param_2[4];
          iVar20 = param_2[5];
          iVar23 = param_2[6];
          iVar17 = param_2[7];
          uVar19 = FUN_0002d24c();
          FUN_0002cae8(uVar19,*(undefined4 *)(param_1 + 0x3bc),*(undefined4 *)(param_1 + 0x3b0),
                       *(undefined4 *)(param_1 + 0x3b4),*(undefined4 *)(param_1 + 0x3b8),
                       *(undefined4 *)(param_1 + 0x3bc),*(undefined4 *)(param_1 + 0x3c0),
                       *(undefined4 *)(param_1 + 0x3c4));
          if (iVar24 == 0 && iVar20 == 0 || iVar17 != 1) {
            if (*(char *)(param_1 + 0x218) != '\0') {
              FUN_000365ec(param_1);
            }
          }
          else {
            FUN_00020728(0x6a3,DAT_00038410,DAT_0006a690 & 0x2000,"#13174");
            cVar4 = *(char *)(param_1 + 0x218);
            if (iVar23 != -1) {
              if ((cVar4 == '\0') || (*(int *)(param_1 + 0x21c) == -1)) {
                iVar17 = GetSharedCurrentMapFlag();
                if (iVar17 == -1) {
                  iVar17 = InsertMultiMap(iVar23);
                  if (iVar17 == 0) {
                    FUN_00020728(0x6ab,DAT_00038714,DAT_0006a690 & 0x2000,"#13175");
                    uVar19 = 1;
                    uVar18 = FUN_0002d24c();
                    FUN_00030b00(uVar18,0);
                    goto LAB_0003688e;
                  }
                  FUN_0002c014(param_1);
                }
              }
              else {
                SetSharedCurrentMapFlag();
              }
              local_68 = (int ****)DAT_00038418;
              local_64 = (int ****)0x116;
              local_60 = (int ****)0x0;
              local_5c = iVar23;
              FUN_00028678(param_1,3,&local_68,0);
              uVar19 = FUN_0002d24c();
              FUN_00030b00(uVar19,0);
              if (*(char *)(param_1 + 0x218) != '\0') {
                FUN_000365ec(param_1,1);
              }
            }
            uVar25 = DAT_0006a690 & 0x2000;
            uVar19 = GetBakMapFlagStartPos();
            uVar18 = *(undefined4 *)(param_1 + 0x504);
            FUN_00020728(0x6bf,DAT_00038410,uVar25,"#13176`%d`%d`%d",iVar23,uVar19,uVar18);
            pbVar13 = (byte *)GetBakMapList(iVar23);
            if (pbVar13 == (byte *)0x0) {
              uVar25 = 0xffffffff;
            }
            else {
              uVar25 = (uint)*pbVar13;
            }
            iVar17 = GetBakMapFlagStartPos();
            if (((int)uVar25 < iVar17) &&
               (iVar20 = *(int *)(param_1 + 0x504), iVar17 = GetBakMapFlagStartPos(),
               iVar17 <= iVar20)) {
              UpdateBakMapForMultiMap(iVar23,*(int *)(param_1 + 0x504));
              uVar19 = *(undefined4 *)(param_1 + 0x504);
              FUN_00020728(0x6c4,DAT_00038410,DAT_0006a690 & 0x2000,"#13177`%d`%d",iVar23,uVar19);
            }
            else {
              FUN_00020728(0x6c6,DAT_00038410,DAT_0006a690 & 0x2000,"#13178`%d",uVar25,uVar19,uVar18
                          );
            }
            FUN_0002c014(param_1);
            if (cVar4 == '\0') {
              FUN_00020728(0x6cd,DAT_00038410,DAT_0006a690 & 0x2000,"#13179`%d",
                           *(undefined4 *)(param_1 + 0x4b0),uVar19);
              iVar17 = FUN_00030508(param_1);
              if (iVar17 == 8) {
                iVar17 = FUN_0002d24c();
                iVar17 = *(int *)(iVar17 + 0x1a4);
                if (iVar17 != 0) {
                  if (*(char *)(iVar17 + 8) != '\0') {
                    FUN_000356f0(iVar17);
                  }
                  FUN_00035868(iVar17,1000);
                  goto LAB_00037c8e;
                }
              }
              bVar26 = DAT_0006cf80 == 1;
              iVar17 = FUN_0002d24c();
              if ((*(char *)(iVar17 + 0x2b7) != '\0') && (bVar26)) {
                uVar19 = FUN_0002d24c();
                FUN_00031848(uVar19,0);
              }
            }
          }
LAB_00037c8e:
          FUN_00030b00(param_1,0);
          uVar19 = 1;
          *(undefined4 *)(param_1 + 0x3b8) = 0;
          *(undefined4 *)(param_1 + 0x3bc) = 0;
          goto LAB_0003688e;
        }
        if (uVar6 == 0x883) {
          uVar6 = (**(code **)(**(int **)(param_1 + 0xf0) + 0x14))();
          uVar12 = ((uint)*(byte *)(param_1 + 0x114) << 0x1a) >> 0x1f;
          uVar14 = *(byte *)(param_1 + 0x114) & 0xf;
          uVar25 = uVar6;
          FUN_00020728(0x700,DAT_00037d48,DAT_0006a690 & 0x2000,"#13181`%d`%d`%d",uVar14,uVar12,
                       uVar6);
          if (((((*(byte *)(param_1 + 0x114) & 0xf) == 0) &&
               (-1 < (int)((uint)*(byte *)(param_1 + 0x114) << 0x1a))) && (uVar6 < 0x10)) &&
             (uVar6 = 0x850cU >> (uVar6 & 0xff) & 1, uVar6 != 0)) {
            uVar19 = FUN_0002d24c();
            FUN_00031848(uVar19,uVar6 ^ 1);
            uVar19 = 1;
            FUN_00020728(0x703,DAT_00037d48,DAT_0006a690 & 0x2000,"#13182",uVar14,uVar12,uVar25);
            FUN_0002d24c();
            FUN_0002c7ac();
            FUN_0002d24c();
            FUN_0002ab68();
          }
          else {
            FUN_00020728(0x707,DAT_00037d48,DAT_0006a690 & 0x2000,"#13183",uVar14,uVar12,uVar25);
            uVar19 = 1;
          }
          goto LAB_0003688e;
        }
        if (uVar6 == 0x884) {
          iVar20 = param_2[4];
          iVar17 = param_2[3];
          uVar19 = 1;
          FUN_00020728(0x711,DAT_00037d48,DAT_0006a690 & 0x2000,"#13184`%d`%d",iVar17 + -2,iVar20);
          FUN_0001d4d4(&DAT_0006cd78,iVar17 + -2,iVar20);
          goto LAB_0003688e;
        }
        if (uVar6 != 0x882) goto LAB_000370e6;
        iVar17 = param_2[3];
        uVar25 = DAT_0006a690 & 0x2000;
        uVar19 = (**(code **)(**(int **)(param_1 + 0xf0) + 0x10))();
        FUN_00020728(0x6f4,DAT_00036f24,uVar25,"#13180`%s`%d",uVar19,iVar17);
        (**(code **)(**(int **)(param_1 + 0xf0) + 0x14))();
        if (iVar17 == 0 || iVar17 - 2U < 2) {
          FUN_0002d24c();
          uVar19 = 1;
          FUN_0002c7ac();
          FUN_0002d24c();
          FUN_0002ab68();
          goto LAB_0003688e;
        }
      }
      goto LAB_00036ece;
    }
    if (uVar6 == 0x865) {
      iVar17 = param_2[3];
      *(int *)(param_1 + 0x4d0) = iVar17;
      uVar19 = 1;
      FUN_00020728(0x634,uVar18,uVar25 & 0x2000,"#13167`%d",iVar17);
      FUN_00030540(param_1);
      goto LAB_0003688e;
    }
    if (uVar6 < 0x866) {
      if (uVar6 == 0x85f) {
        uVar19 = FUN_000364f0(param_1,param_2[3]);
        goto LAB_0003706a;
      }
      if (uVar6 == 0x860) {
        FUN_00020728(0x619,DAT_000372d8,DAT_0006a690 & 0x2000,"#13163");
        uVar19 = FUN_0003656c(param_1);
        goto LAB_0003688e;
      }
      goto LAB_000370e6;
    }
    if (uVar6 == 0x867) {
      iVar17 = param_2[3];
      *(int *)(param_1 + 0x4a8) = iVar17;
      uVar19 = 1;
      FUN_00020728(0x65e,uVar5,uVar25 & 0x2000,"#13169`%d",iVar17);
      goto LAB_0003688e;
    }
    if (0x867 < uVar6) {
      uVar25 = param_2[3];
      FUN_00020728(0x596,DAT_00036b4c,DAT_0006a690 & 0x2000,"#13159`%d",uVar25);
      if (uVar25 < 2) {
        *(uint *)(param_1 + 0x464) = uVar25;
        FUN_00030540(param_1);
      }
      uVar19 = 1;
      *(byte *)(param_1 + 0x305) = *(byte *)(param_1 + 0x305) & 0xf1;
      goto LAB_0003688e;
    }
    iVar17 = param_2[3];
    *(int *)(param_1 + 0x4d4) = iVar17;
    FUN_00020728(0x641,uVar5,uVar25 & 0x2000,"#13168`%d",iVar17);
    pthread_mutex_lock((pthread_mutex_t *)(param_1 + 0x4e8));
    if (*(int *)(param_1 + 0x4e4) == 0) {
      if (*(int *)(param_1 + 0x4d4) != 0x69) {
LAB_00037adc:
        tVar11 = time((time_t *)0x0);
        *(time_t *)(param_1 + 0x4e4) = tVar11;
      }
    }
    else {
      uVar19 = FUN_0002d24c();
      uVar18 = *(undefined4 *)(param_1 + 0x4e4);
      tVar11 = time((time_t *)0x0);
      uVar18 = FUN_0002c7f0(param_1,uVar18,tVar11);
      FUN_0002af94(uVar19,uVar18);
      if (*(int *)(param_1 + 0x4d4) != 0x69) goto LAB_00037adc;
      *(undefined4 *)(param_1 + 0x4e4) = 0;
    }
    uVar19 = 1;
    pthread_mutex_unlock((pthread_mutex_t *)(param_1 + 0x4e8));
    FUN_00030540(param_1);
    goto LAB_0003688e;
  }
  if (uVar6 == 0x855) {
    iVar17 = param_2[3];
    FUN_00020728(0x557,DAT_00037d48,DAT_0006a690 & 0x2000,"#13157`%d",iVar17);
    if (iVar17 == 0x2a) {
      FUN_0002df8c("visual_aid_id",0x5a,0);
      uVar19 = 1;
      goto LAB_0003688e;
    }
    if (iVar17 == 0x2b) {
      FUN_0002df8c("visual_aid_pose",0x5a,0);
      uVar19 = 1;
      goto LAB_0003688e;
    }
    if (iVar17 == 0x29) {
      FUN_0002df8c("visual_aid_no",0x5a,0);
      uVar19 = 1;
      goto LAB_0003688e;
    }
  }
  else {
    if (0x855 < uVar6) {
      if (uVar6 == 0x858) {
        iVar17 = param_2[3];
        FUN_00020728(0x5ac,DAT_0003765c,DAT_0006a690 & 0x2000,"#13160`%d",(char)iVar17);
        if ((char)iVar17 == '\x01') {
          tVar11 = time((time_t *)0x0);
          *(time_t *)(param_1 + 0x460) = tVar11;
          uVar19 = 1;
        }
        else {
          tVar11 = time((time_t *)0x0);
          iVar20 = *(int *)(param_1 + 0x460);
          bVar26 = tVar11 == iVar20;
          iVar17 = tVar11 - iVar20;
          if (tVar11 > iVar20) {
            bVar26 = iVar20 == 0;
            iVar17 = iVar20;
          }
          if (!bVar26 && iVar17 < 0 == (tVar11 <= iVar20 && SBORROW4(tVar11,iVar20))) {
            iVar20 = tVar11 - iVar20;
            FUN_0002aef4(param_1,0x4d,iVar20,iVar20 >> 0x1f);
            rr_stat_int(2,0x12,iVar20);
          }
          uVar19 = 1;
          *(undefined4 *)(param_1 + 0x460) = 0;
        }
        goto LAB_0003688e;
      }
      if (0x858 < uVar6) {
        if (uVar6 == 0x85a) {
          FUN_0002df8c(&DAT_00049630,0x5a,0);
          uVar19 = 1;
          goto LAB_0003688e;
        }
        if (uVar6 < 0x85a) {
          iVar17 = param_2[3];
          FUN_00020728(0x5c3,DAT_000379d4,DAT_0006a690 & 0x2000,"#13161`%d",iVar17);
          if (iVar17 == 0) {
            if (DAT_0006cf90 != 0) {
              FUN_0002df8c("carpet_found",0x5a,0);
              uVar19 = 1;
              goto LAB_0003688e;
            }
          }
          else if ((iVar17 == 1) && (DAT_0006cf90 != 0)) {
            FUN_0002df8c("carpet_left",0x5a,0);
            uVar19 = 1;
            goto LAB_0003688e;
          }
        }
        else {
          if (uVar6 != 0x85b) goto LAB_000370e6;
          iVar20 = param_2[3];
          iVar17 = param_2[4];
          uVar19 = FUN_0002d24c();
          FUN_0002b704(uVar19,iVar20,iVar17);
          uVar19 = FUN_0002d24c();
          FUN_0002b710(uVar19,iVar17);
          if ((DAT_0006d0ec == '\0') && (fVar27 = (float)FUN_0001ea8c(&DAT_0006cd78), 1.0 <= fVar27)
             ) {
            FUN_00030508(param_1);
            FUN_0002d744();
            uVar19 = FUN_0002d24c();
            FUN_0002ae7c(uVar19,0x38,0);
            FUN_0002df8c("water_shortage_remind",0x5a,0);
            uVar19 = 1;
            FUN_0001d094(&DAT_0006cd78,1);
            FUN_00030540(param_1);
            FUN_00020728(0x5f8,DAT_00036b4c,DAT_0006a690 & 0x2000,"#13162");
            local_64 = (int ****)0x94;
            local_5c = 1;
            local_68 = (int ****)DAT_00036b5c;
            goto LAB_00036b36;
          }
        }
        goto LAB_00036ece;
      }
      if (uVar6 == 0x856) {
        uVar19 = FUN_00036734(param_1,param_2[3]);
        goto LAB_0003688e;
      }
      if (uVar6 != 0x857) goto LAB_000370e6;
      pppppiVar16 = (int *****)param_2[3];
      FUN_00020728(0x57c,DAT_000372d8,DAT_0006a690 & 0x2000,"#13158`%d",pppppiVar16);
      if (pppppiVar16 < (int *****)0x2) {
        FUN_0002aef4(param_1,0x4c,1,0);
      }
      iVar20 = *(int *)(param_1 + 0x470);
      iVar23 = param_1 + 0x46c;
      iVar17 = iVar23;
      if (iVar20 != 0) {
        do {
          if (*(int ******)(iVar20 + 0x10) < pppppiVar16) {
            iVar24 = *(int *)(iVar20 + 0xc);
          }
          else {
            iVar24 = *(int *)(iVar20 + 8);
            iVar17 = iVar20;
          }
          iVar20 = iVar24;
        } while (iVar24 != 0);
        if ((iVar23 != iVar17) && (*(int ******)(iVar17 + 0x10) <= pppppiVar16)) {
          uVar25 = *(uint *)(iVar17 + 0x20);
          uVar19 = 1;
          *(uint *)(iVar17 + 0x20) = uVar25 + 1;
          *(uint *)(iVar17 + 0x24) = *(int *)(iVar17 + 0x24) + (uint)(0xfffffffe < uVar25);
          goto LAB_0003688e;
        }
      }
      uVar18 = FUN_0002b800(param_1);
      iVar17 = iVar23;
      iVar20 = *(int *)(param_1 + 0x470);
      local_78 = (int ****)pppppiVar16;
      if (*(int *)(param_1 + 0x470) == 0) {
LAB_000382e4:
        local_68 = (int ****)&local_78;
        iVar17 = FUN_00038840(param_1 + 0x468,local_68,iVar17,DAT_00038414,&local_68,&local_84);
      }
      else {
        do {
          if (*(int ******)(iVar20 + 0x10) < pppppiVar16) {
            iVar24 = *(int *)(iVar20 + 0xc);
          }
          else {
            iVar24 = *(int *)(iVar20 + 8);
            iVar17 = iVar20;
          }
          iVar20 = iVar24;
        } while (iVar24 != 0);
        if ((iVar17 == iVar23) || (pppppiVar16 < *(int ******)(iVar17 + 0x10))) goto LAB_000382e4;
      }
      *(int ******)(iVar17 + 0x18) = pppppiVar16;
      uVar19 = 1;
      *(undefined4 *)(iVar17 + 0x1c) = uVar18;
      *(undefined4 *)(iVar17 + 0x20) = 1;
      *(undefined4 *)(iVar17 + 0x24) = 0;
      goto LAB_0003688e;
    }
    if (uVar6 != 0x84d) {
      if (0x84d < uVar6) {
        if (uVar6 == 0x852) {
          FUN_00031404(param_1,0);
          FUN_0002862c(param_1);
          local_64 = (int ****)0x20e;
          uVar19 = 1;
          local_68 = (int ****)DAT_00037660;
        }
        else {
          if (uVar6 == 0x854) {
            FUN_00020728(0x542,DAT_0003765c,DAT_0006a690 & 0x2000,"#13156");
            uVar25 = param_2[3];
            rr_set_child_lock_status(uVar25);
            *(uint *)(param_1 + 0x448) = uVar25;
            if (uVar25 == 0) {
              FUN_0002d24c();
              uVar19 = 1;
              FUN_0002df8c("child_lock_off",0x5a,0);
            }
            else {
              FUN_0002d24c();
              uVar19 = 1;
              FUN_0002df8c("child_lock_on",0x5a,0);
            }
            goto LAB_0003688e;
          }
          if (uVar6 != 0x850) goto LAB_000370e6;
          FUN_00031404(param_1,1);
          uVar19 = 0;
          FUN_00028630(param_1);
          local_64 = (int ****)0x20d;
          local_68 = (int ****)DAT_00036b54;
        }
LAB_00036b36:
        local_60 = (int ****)0x0;
        uVar18 = FUN_0002d24c();
        FUN_00028678(uVar18,2,&local_68,0);
        goto LAB_0003688e;
      }
      if (uVar6 == 0x849) {
        FUN_00020728(0x51d,DAT_000372d8,DAT_0006a690 & 0x2000,"#13153");
        uVar19 = FUN_000366a0(param_1);
        goto LAB_0003688e;
      }
      if (uVar6 == 0x84c) {
        FUN_00020728(0x4d7,DAT_00036f24,DAT_0006a690 & 0x2000,"#13147");
        FUN_0001cfe0(&DAT_0006cd78,0);
        iVar17 = FUN_0002d24c();
        uVar19 = 1;
        *(undefined1 *)(iVar17 + 0x435) = 1;
        goto LAB_0003688e;
      }
      goto LAB_000370e6;
    }
    FUN_00020728(0x4b6,DAT_000379d4,DAT_0006a690 & 0x2000,"#13145");
    piVar10 = (int *)FUN_0002d940(param_1);
    iVar17 = (**(code **)(*piVar10 + 0x14))();
    if ((iVar17 != 0xf) || (iVar17 = FUN_00030508(param_1), iVar17 != 6)) {
      FUN_0002d24c();
      FUN_0002df8c("positioning_still",0x5a,0);
    }
    if (((*(byte *)(param_1 + 0x114) & 0xf) != 0) && (iVar17 = FUN_00030508(param_1), iVar17 == 6))
    {
      FUN_00033af0(param_1,0x40);
      uVar19 = 1;
      goto LAB_0003688e;
    }
  }
LAB_00036ece:
  uVar19 = 1;
LAB_0003688e:
  if (local_2c != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(uVar19);
  }
  return;
}

