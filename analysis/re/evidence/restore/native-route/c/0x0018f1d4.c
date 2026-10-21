/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x0018f1d4
 */

void FUN_0018f1d4(undefined4 *param_1,undefined4 param_2,uint param_3,uint *param_4)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  undefined1 uVar11;
  int iVar12;
  uint uVar13;
  int *piVar14;
  int iVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  int iVar18;
  int iVar19;
  uint *puVar20;
  uint local_98;
  uint uStack_94;
  uint local_90;
  uint uStack_8c;
  uint local_88;
  uint uStack_84;
  undefined1 auStack_60 [4];
  undefined4 local_5c;
  undefined4 uStack_58;
  void *local_54;
  void *local_50;
  uint local_48;
  uint local_44;
  uint local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  int local_2c;
  
  iVar18 = DAT_0018fe4c + 0x18f1ea;
  piVar14 = *(int **)(iVar18 + DAT_0018fe50);
  local_2c = *piVar14;
  memset(param_1,0,0x4c);
  if (param_3 == 1) {
    *param_1 = 0x2010001;
LAB_0018f272:
    if ((1 < param_3 - 0x21) && (param_3 != 0x59)) {
      if ((param_3 == 0x23) || (param_3 - 0x1b < 2)) goto LAB_0018fa1e;
      if (param_3 != 0x2c) {
        if (param_3 - 0x1d < 0xf) {
          if ((int)((0x4083U >> (param_3 - 0x1d & 0xff)) << 0x1f) < 0) goto LAB_0018f508;
          if (param_3 != 0x25) goto LAB_0018f2a8;
          goto LAB_0018f574;
        }
LAB_0018f2a8:
        if (param_3 == 0x3b) {
          uVar9 = *param_4;
          uVar16 = 15000;
          param_1[2] = 4;
          if (uVar9 != 0x2e) {
            uVar16 = 0;
          }
          param_1[3] = uVar16;
          goto LAB_0018f508;
        }
        if (param_3 != 0x3c) {
          if (param_3 == 0x1f) goto LAB_0018f574;
          if (param_3 != 0x1a) {
            if (param_3 == 0x26) {
              uVar9 = *param_4;
              uVar7 = param_4[1];
              uVar10 = param_4[2];
              uVar13 = param_4[3];
              param_1[2] = 0x1c;
              param_1[3] = uVar9;
              param_1[4] = uVar7;
              param_1[5] = uVar10;
              param_1[6] = uVar13;
              uVar9 = param_4[5];
              uVar7 = param_4[6];
              param_1[7] = param_4[4];
              param_1[8] = uVar9;
              param_1[9] = uVar7;
              goto LAB_0018f508;
            }
            if (param_3 == 0x27) goto LAB_0018f5b8;
            if (param_3 == 0x29 || param_3 == 0x7c) goto LAB_0018f508;
            if (param_3 == 0x41) {
LAB_0018f418:
              uVar9 = *param_4;
              param_1[2] = 4;
              param_1[3] = (uint)(uVar9 != 0);
              goto LAB_0018f508;
            }
            if (param_3 == 0x46) {
              uVar9 = *param_4;
              if (uVar9 == 0) goto switchD_0018f522_caseD_0;
              if (uVar9 == 0x32) goto switchD_0018f522_caseD_8;
              if (uVar9 == 0x44 || uVar9 == 0x33) goto switchD_0018f522_caseD_1;
              if (uVar9 < 0x4a) {
                piVar6 = (int *)FUN_00065fdc();
                iVar18 = *(int *)(*piVar6 + uVar9 * 4);
              }
              else {
                iVar18 = DAT_0018ff38 + 0x18fba6;
              }
              _rrlogmP(3,3,1,0x354,DAT_0018ff44 + 0x18fbbe,DAT_0018ff40 + 0x18fbb6,
                       DAT_0018ff3c + 0x18fbb2,iVar18);
              uVar9 = 1;
            }
            else {
              if (param_3 != 0x4d) {
                if (param_3 == 0x6b) {
                  uVar9 = *param_4;
                  uVar16 = 0;
                  if (uVar9 != 0) {
                    if (uVar9 == 0x41) {
                      uVar16 = 1;
                    }
                    else if ((uVar9 - 0x42 & 0xfffffffd) == 0) {
                      uVar16 = 2;
                    }
                    else {
                      if (uVar9 < 0x4a) {
                        piVar6 = (int *)FUN_00065fdc();
                        iVar18 = *(int *)(*piVar6 + uVar9 * 4);
                      }
                      else {
                        iVar18 = DAT_00190064 + 0x18ff84;
                      }
                      uVar16 = 1;
                      _rrlogmP(3,3,1,0x38b,DAT_00190070 + 0x18ff96,DAT_0019006c + 0x18ff94,
                               DAT_00190068 + 0x18ff90,iVar18);
                    }
                  }
                  param_1[3] = uVar16;
                  param_1[2] = 4;
                  goto LAB_0018f508;
                }
                if (((param_3 - 0x52 < 0x1f) &&
                    ((int)((0x48002201U >> (param_3 - 0x52 & 0xff)) << 0x1f) < 0)) ||
                   (param_3 - 0x50 < 2)) goto LAB_0018fa06;
                if (param_3 != 0x62) {
                  if (((param_3 & 0xfffffffd) == 100) || (param_3 == 0x68)) {
                    uVar9 = *param_4;
                    uVar7 = param_4[1];
                    uVar10 = param_4[2];
                    uVar13 = param_4[3];
                    param_1[2] = 0x20;
                    param_1[3] = uVar9;
                    param_1[4] = uVar7;
                    param_1[5] = uVar10;
                    param_1[6] = uVar13;
                    uVar9 = param_4[5];
                    uVar7 = param_4[6];
                    uVar10 = param_4[7];
                    param_1[7] = param_4[4];
                    param_1[8] = uVar9;
                    param_1[9] = uVar7;
                    param_1[10] = uVar10;
                    goto LAB_0018f508;
                  }
                  if ((param_3 != 0x5a) && (param_3 != 0x7f)) {
                    if (param_3 == 0x6f) {
                      uVar9 = *param_4;
                      param_1[2] = 1;
                      *(char *)(param_1 + 3) = (char)uVar9;
                      goto LAB_0018f508;
                    }
                    if (param_3 == 0x76) {
LAB_00190010:
                      uVar9 = *param_4;
                      param_1[2] = 2;
                      *(short *)(param_1 + 3) = (short)uVar9;
                      goto LAB_0018f508;
                    }
                    if (param_3 != 0x74) {
                      if (param_3 == 0x7d) goto LAB_0018f574;
                      if (param_3 != 0x7e) {
                        if ((param_3 - 0x80 < 7) &&
                           ((int)((0x49U >> (param_3 - 0x80 & 0xff)) << 0x1f) < 0))
                        goto LAB_0018f574;
                        if (param_3 != 0x8a) {
                          if (param_3 == 0x85) {
                            local_48 = 0;
                            local_44 = 0;
                            local_40 = 0;
                            local_3c = 0;
                            local_38 = 0;
                            local_34 = 0;
                            if ((-1 < *(int *)(DAT_0018ff48 + 0x18fc30) << 0x1f) &&
                               (iVar18 = __cxa_guard_acquire(), iVar18 != 0)) {
                              local_5c = *(undefined4 *)(DAT_0019007c + 0x19002c);
                              uStack_58 = *(undefined4 *)(DAT_0019007c + 0x190030);
                              std::
                              map<SensorType,AdBumperSource,std::less<SensorType>,std::allocator<std::pair<SensorType_const,AdBumperSource>>>
                              ::map(DAT_00190080 + 0x19003c,local_5c,uStack_58,auStack_60,&local_54)
                              ;
                              __cxa_guard_release(DAT_00190084 + 0x190044);
                    /* WARNING: Subroutine does not return */
                              __aeabi_atexit(DAT_00190090 + 0x190054,DAT_0019008c + 0x190052,
                                             DAT_00190088 + 0x190050);
                            }
                            FUN_0018e0f4(&local_54);
                            if (local_54 != local_50) {
                              bVar2 = false;
                              iVar18 = *(int *)(DAT_0018ff4c + 0x18fc72);
                              puVar20 = (uint *)((int)local_54 + -4);
                              bVar1 = false;
                              local_88 = local_48;
                              uStack_84 = local_44;
                              local_90 = local_40;
                              uStack_8c = local_3c;
                              local_98 = local_38;
                              uStack_94 = local_34;
                              bVar3 = false;
                              do {
                                puVar20 = puVar20 + 1;
                                uVar9 = *puVar20;
                                uVar7 = uVar9 >> 5;
                                uVar10 = 1 << (uVar9 & 0x1f);
                                iVar12 = DAT_0018ff50 + 0x18fc72;
                                iVar15 = iVar18;
                                if ((uVar10 & param_4[uVar7 + 4]) == 0) {
                                  uVar13 = uVar10 & param_4[uVar7 + 10];
                                  if ((uVar13 != 0) || ((uVar10 & param_4[uVar7 + 0x10]) != 0)) {
                                    uVar8 = uVar10 & param_4[uVar7 + 0x10];
                                    if (iVar18 != 0) goto LAB_0018fcea;
                                    uVar9 = 1;
                                    goto LAB_0018fd4c;
                                  }
                                }
                                else {
                                  uVar13 = uVar10 & param_4[uVar7 + 10];
                                  uVar8 = uVar10 & param_4[uVar7 + 0x10];
                                  if (iVar18 == 0) {
                                    uVar9 = 1;
                                  }
                                  else {
LAB_0018fcea:
                                    do {
                                      if (*(int *)(iVar15 + 0x10) < (int)uVar9) {
                                        iVar19 = *(int *)(iVar15 + 0xc);
                                      }
                                      else {
                                        iVar19 = *(int *)(iVar15 + 8);
                                        iVar12 = iVar15;
                                      }
                                      iVar15 = iVar19;
                                    } while (iVar19 != 0);
                                    if ((iVar12 == DAT_0018ff54 + 0x18fc7e) ||
                                       ((int)uVar9 < *(int *)(iVar12 + 0x10))) {
                                      uVar9 = 1;
                                    }
                                    else {
                                      uVar9 = *(uint *)(iVar12 + 0x14);
                                    }
                                    if ((uVar10 & param_4[uVar7 + 4]) == 0) goto LAB_0018fd4c;
                                  }
                                  local_88 = local_88 | uVar9;
                                  uStack_84 = uStack_84 | (int)uVar9 >> 0x1f;
                                  bVar1 = true;
LAB_0018fd4c:
                                  if (uVar13 != 0) {
                                    bVar2 = true;
                                    local_90 = local_90 | uVar9;
                                    uStack_8c = uStack_8c | (int)uVar9 >> 0x1f;
                                  }
                                  if (uVar8 != 0) {
                                    local_98 = local_98 | uVar9;
                                    uStack_94 = uStack_94 | (int)uVar9 >> 0x1f;
                                    bVar3 = true;
                                  }
                                }
                              } while (puVar20 != (uint *)((int)local_50 + -4));
                              if (bVar1) {
                                local_48 = local_88;
                                local_44 = uStack_84;
                              }
                              if (bVar2) {
                                local_40 = local_90;
                                local_3c = uStack_8c;
                              }
                              if (bVar3) {
                                local_38 = local_98;
                                local_34 = uStack_94;
                              }
                            }
                            if (local_54 != (void *)0x0) {
                              operator_delete(local_54);
                            }
                            param_1[2] = 0x18;
                            param_1[3] = local_48;
                            param_1[4] = local_44;
                            param_1[5] = local_40;
                            param_1[6] = local_3c;
                            param_1[7] = local_38;
                            param_1[8] = local_34;
                            goto LAB_0018f508;
                          }
                          if (1 < param_3 - 0x8b) {
                            if (param_3 == 0x8d) goto LAB_0018f508;
                            if (param_3 != 0x8e) {
                              if (param_3 == 0x8f) goto LAB_0018f508;
                              if (param_3 - 0x91 < 2) goto LAB_0018f574;
                              if (param_3 == 0x95) goto LAB_0018f508;
                              if (param_3 != 0x96) {
                                if (1 < param_3 - 0x9d) {
                                  if (param_3 == 0x9f) goto LAB_00190010;
                                  if (param_3 - 0xa1 < 3) goto LAB_0018f508;
                                  if (param_3 != 0xa5) {
                                    if (param_3 != 0xb7) {
                                      if ((param_3 & 0xfffffffd) != 0xb4) {
                                        if (param_3 != 0xba) goto LAB_0018f508;
                                        goto LAB_0018f418;
                                      }
                                      goto LAB_0018fa06;
                                    }
                                    goto LAB_0018f574;
                                  }
                                }
                                goto LAB_0018f5b8;
                              }
                            }
                            uVar9 = *param_4;
                            uVar7 = param_4[1];
                            param_1[2] = 8;
                            param_1[3] = uVar9;
                            param_1[4] = uVar7;
                            goto LAB_0018f508;
                          }
                        }
                      }
                    }
                    goto LAB_0018f5b8;
                  }
                }
LAB_0018f574:
                uVar9 = *param_4;
                param_1[2] = 1;
                *(char *)(param_1 + 3) = (char)uVar9;
                goto LAB_0018f508;
              }
              uVar9 = *param_4;
              if (uVar9 == 0x3d) {
switchD_0018f522_caseD_1:
                uVar9 = 2;
              }
              else if (uVar9 == 0x3e) {
                uVar9 = 3;
              }
              else {
                if (uVar9 == 0x3f) goto LAB_0018f62c;
                if (uVar9 == 0x40) {
                  uVar9 = 5;
                }
                else {
                  uVar9 = 1;
                }
              }
            }
LAB_0018f5d0:
            param_1[3] = uVar9;
            param_1[2] = 4;
            goto LAB_0018f508;
          }
        }
LAB_0018fa1e:
        uVar9 = *param_4;
        uVar7 = param_4[1];
        uVar10 = param_4[2];
        param_1[2] = 0xc;
        param_1[3] = uVar9;
        param_1[4] = uVar7;
        param_1[5] = uVar10;
        goto LAB_0018f508;
      }
    }
LAB_0018f5b8:
    uVar9 = *param_4;
    param_1[2] = 4;
    param_1[3] = uVar9;
    goto LAB_0018f508;
  }
  iVar12 = 1;
  uVar9 = 2;
  while (uVar9 != param_3) {
    iVar12 = iVar12 + 1;
    if (iVar12 == 0xae) {
      if (param_3 < 0xbb) {
        if ((-1 < *(int *)(DAT_0018fe94 + 0x18f61a) << 0x1f) &&
           (iVar12 = __cxa_guard_acquire(), iVar12 != 0)) {
          std::string::string((string *)&local_48,(char *)(DAT_0018fe9c + 0x18f648),
                              (allocator *)&local_54);
          FUN_0016b510(DAT_0018fea0 + 0x18f658,(string *)&local_48,0x2c);
          __cxa_guard_release(DAT_0018fea4 + 0x18f662);
                    /* WARNING: Subroutine does not return */
          __aeabi_atexit(DAT_0018feb0 + 0x18f67a,*(undefined4 *)(iVar18 + DAT_0018fea8),
                         DAT_0018feac + 0x18f674);
        }
        iVar18 = *(int *)(*(int *)(DAT_0018fe98 + 0x18f626) + param_3 * 4);
      }
      else {
        iVar18 = DAT_0018fe70 + 0x18f58c;
      }
      _rrlogmP(3,3,1,0x484,DAT_0018fe7c + 0x18f5a4,DAT_0018fe78 + 0x18f5a0,DAT_0018fe74 + 0x18f59e,
               param_3,iVar18);
      goto LAB_0018f508;
    }
    uVar9 = *(uint *)(DAT_0018fe54 + 0x18f20e + iVar12 * 8);
  }
  *param_1 = *(undefined4 *)(DAT_0018fe58 + iVar12 * 8 + 0x18f230);
  iVar5 = DAT_0018feec;
  iVar4 = DAT_0018fee0;
  iVar19 = DAT_0018fed4;
  iVar15 = DAT_0018fec8;
  iVar12 = DAT_0018febc;
  if (1 < uVar9 - 10) {
    if (uVar9 == 0xd) {
      uVar9 = *param_4;
      if (uVar9 == 0x19) {
        if ((-1 < *(int *)(DAT_0018fe5c + 0x18f4c6) << 0x1f) &&
           (iVar12 = __cxa_guard_acquire(), iVar12 != 0)) {
          std::string::string((string *)&local_48,(char *)(DAT_0018ff10 + 0x18fa6a),
                              (allocator *)&local_5c);
          FUN_0016b510(DAT_0018ff14 + 0x18fa7a,(string *)&local_48,0x2c);
          __cxa_guard_release(DAT_0018ff18 + 0x18fa84);
                    /* WARNING: Subroutine does not return */
          __aeabi_atexit(DAT_0018ff20 + 0x18fa9c,*(undefined4 *)(iVar18 + DAT_0018fea8),
                         DAT_0018ff1c + 0x18fa96);
        }
        _rrlogmP(3,7,1,0x26c,DAT_0018fe6c + 0x18f4f2,DAT_0018fe68 + 0x18f4ea,DAT_0018fe64 + 0x18f4e4
                 ,*(undefined4 *)(*(int *)(DAT_0018fe60 + 0x18f4de) + 100));
        uVar11 = 4;
      }
      else {
        *param_1 = 0;
        if (uVar9 < 0x4a) {
          if ((-1 < *(int *)(DAT_0018ff08 + 0x18fa38) << 0x1f) &&
             (iVar12 = __cxa_guard_acquire(), iVar12 != 0)) {
            std::string::string((string *)&local_48,(char *)(DAT_0018ff24 + 0x18fafa),
                                (allocator *)&local_5c);
            FUN_0016b510(DAT_0018ff28 + 0x18fb0a,(string *)&local_48,0x2c);
            __cxa_guard_release(DAT_0018ff2c + 0x18fb14);
                    /* WARNING: Subroutine does not return */
            __aeabi_atexit(DAT_0018ff34 + 0x18fb2a,*(undefined4 *)(iVar18 + DAT_0018fea8),
                           DAT_0018ff30 + 0x18fb24);
          }
          iVar18 = *(int *)(*(int *)(DAT_0018ff0c + 0x18fa44) + uVar9 * 4);
        }
        else {
          iVar18 = DAT_0018fe84 + 0x18f5e8;
        }
        _rrlogmP(3,3,1,0x270,DAT_0018fe90 + 0x18f606,DAT_0018fe8c + 0x18f5fe,DAT_0018fe88 + 0x18f5fa
                 ,iVar18);
        uVar11 = 0;
      }
      *(undefined1 *)(param_1 + 3) = uVar11;
      param_1[2] = 1;
      goto LAB_0018f508;
    }
    if (uVar9 == 0xe) goto LAB_0018f5b8;
    if (uVar9 == 0xf) {
      uVar7 = *param_4;
      uVar10 = param_4[1];
      uVar13 = param_4[2];
      uVar8 = param_4[3];
      param_1[2] = 0x19;
      uVar9 = param_4[6];
      param_1[3] = uVar7;
      param_1[4] = uVar10;
      param_1[5] = uVar13;
      param_1[6] = uVar8;
      uVar7 = param_4[5];
      param_1[7] = param_4[4];
      param_1[8] = uVar7;
      *(char *)(param_1 + 9) = (char)uVar9;
      goto LAB_0018f508;
    }
    if (uVar9 == 0x10) {
LAB_0018fa06:
      uVar9 = *param_4;
      uVar7 = param_4[1];
      uVar10 = param_4[2];
      uVar13 = param_4[3];
      param_1[2] = 0x10;
      param_1[3] = uVar9;
      param_1[4] = uVar7;
      param_1[5] = uVar10;
      param_1[6] = uVar13;
      goto LAB_0018f508;
    }
    if (uVar9 == 0x13) {
      if (*param_4 < 0x3c) {
        uVar9 = (uint)*(byte *)(DAT_0018fe80 + 0x18f5d0 + *param_4);
      }
      else {
LAB_0018f62c:
        uVar9 = 4;
      }
    }
    else {
      if (uVar9 != 0x99) {
        if (param_3 != 0x9b) {
          if (param_3 == 0x18) {
            FUN_0018e1a8(param_4,param_1);
            goto LAB_0018f508;
          }
          if (param_3 != 0x88) goto LAB_0018f272;
        }
        goto LAB_0018f5b8;
      }
      switch(*param_4) {
      case 0:
switchD_0018f522_caseD_0:
        uVar9 = 0;
        break;
      default:
        goto switchD_0018f522_caseD_1;
      case 8:
      case 9:
      case 10:
switchD_0018f522_caseD_8:
        uVar9 = 1;
      }
    }
    goto LAB_0018f5d0;
  }
  uVar9 = *param_4;
  local_48 = 0;
  local_44 = 0;
  switch(uVar9) {
  case 0xd:
    local_48 = 4;
    break;
  case 0xe:
    local_48 = 0x2000;
    break;
  case 0xf:
    local_48 = 0x10;
    break;
  case 0x10:
    local_48 = 2;
    break;
  case 0x11:
    local_48 = 8;
    break;
  case 0x12:
    local_48 = 0x200;
    piVar6 = (int *)FUN_00065fdc();
    uVar16 = 500;
    iVar18 = DAT_0018fef0 + 0x18f938;
    iVar15 = iVar5 + 0x18f93a;
    iVar12 = DAT_0018fef4 + 0x18f93c;
    uVar17 = *(undefined4 *)(*piVar6 + 0x48);
    goto LAB_0018f77c;
  case 0x13:
    local_48 = 0x40000;
    break;
  case 0x14:
    local_48 = 0x80000;
    break;
  case 0x15:
    local_48 = 0x400;
    piVar6 = (int *)FUN_00065fdc();
    uVar16 = 0x1fe;
    iVar18 = DAT_0018fed8 + 0x18f872;
    iVar15 = iVar19 + 0x18f874;
    iVar12 = DAT_0018fedc + 0x18f876;
    uVar17 = *(undefined4 *)(*piVar6 + 0x54);
    goto LAB_0018f77c;
  case 0x16:
    local_48 = 0x100000;
    break;
  case 0x17:
    local_48 = 0x200000;
    break;
  case 0x18:
    local_48 = 0x600;
    piVar6 = (int *)FUN_00065fdc();
    uVar16 = 0x209;
    iVar18 = DAT_0018fee4 + 0x18f8c0;
    iVar15 = iVar4 + 0x18f8c2;
    iVar12 = DAT_0018fee8 + 0x18f8c4;
    uVar17 = *(undefined4 *)(*piVar6 + 0x60);
    goto LAB_0018f77c;
  default:
    *param_1 = 0;
    if (uVar9 < 0x4a) {
      piVar6 = (int *)FUN_00065fdc();
      iVar18 = *(int *)(*piVar6 + uVar9 * 4);
    }
    else {
      iVar18 = DAT_0018fef8 + 0x18f9ae;
    }
    _rrlogmP(3,3,1,0x25d,DAT_0018ff04 + 0x18f9c6,DAT_0018ff00 + 0x18f9c2,DAT_0018fefc + 0x18f9c0,
             iVar18);
    break;
  case 0x1a:
    local_48 = 0x100;
    break;
  case 0x1b:
    local_48 = 0x1000000;
    break;
  case 0x1c:
    local_48 = 0x800;
    break;
  case 0x1d:
    local_48 = 0x400000;
    break;
  case 0x1e:
    local_48 = 0x40;
    break;
  case 0x1f:
    local_48 = 0x4000;
    break;
  case 0x20:
    local_48 = 0x8000;
    break;
  case 0x21:
    local_48 = 0x80;
    break;
  case 0x22:
    local_48 = 0x10000;
    break;
  case 0x23:
    local_48 = 0x20000;
    break;
  case 0x24:
    local_44 = 0x400;
    piVar6 = (int *)FUN_00065fdc();
    iVar15 = iVar12 + 0x18f76a;
    iVar18 = DAT_0018fec0 + 0x18f76c;
    uVar16 = 0x219;
    iVar12 = DAT_0018fec4 + 0x18f772;
    uVar17 = *(undefined4 *)(*piVar6 + 0x90);
    goto LAB_0018f77c;
  case 0x25:
    local_44 = 0x200;
    piVar6 = (int *)FUN_00065fdc();
    uVar16 = 0x211;
    iVar18 = DAT_0018fecc + 0x18f7b2;
    iVar15 = iVar15 + 0x18f7b4;
    iVar12 = DAT_0018fed0 + 0x18f7b6;
    uVar17 = *(undefined4 *)(*piVar6 + 0x94);
LAB_0018f77c:
    _rrlogmP(3,7,1,uVar16,iVar15,iVar12,iVar18,uVar17);
    break;
  case 0x26:
    local_48 = 0x20;
    break;
  case 0x27:
    local_48 = 0x2000000;
    break;
  case 0x28:
    local_48 = 0x4000000;
    break;
  case 0x29:
    local_48 = 0x8000000;
    break;
  case 0x2a:
    local_48 = 0x80000000;
    break;
  case 0x2b:
    local_44 = 0x10;
    break;
  case 0x2c:
    local_44 = 0x20;
    break;
  case 0x2d:
    local_48 = 1;
    break;
  case 0x30:
    local_48 = 0x10000000;
    break;
  case 0x31:
    local_48 = 0x20000000;
    break;
  case 0x45:
    local_44 = 1;
    break;
  case 0x46:
    local_44 = 8;
  }
  param_1[2] = 8;
  param_1[3] = local_48;
  param_1[4] = local_44;
LAB_0018f508:
  if (local_2c == *piVar14) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(param_1);
}

