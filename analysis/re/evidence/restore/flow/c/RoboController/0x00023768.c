/* Decompiled C, NOT recovered source; need not compile.
 * Binary: RoboController
 * SHA256: bf1d43313dd8beaa0c802f9ae4c666138b3bb518f69b4909a746285f3f3947cf
 * Function VA: 0x00023768
 */

void FUN_00023768(ushort *param_1,undefined4 *param_2)

{
  ushort uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 uVar8;
  char *pcVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  char cVar12;
  undefined4 uVar13;
  undefined4 local_38;
  
  iVar2 = __stack_chk_guard;
  uVar1 = *param_1;
  if (uVar1 == 0x2104) {
    if (*(int *)(param_1 + 4) == 4) {
      local_38 = *(undefined4 *)(param_1 + 6);
      puVar3 = operator_new(0x10);
      uVar6 = 0x8d;
      uVar4 = DAT_00024434;
      goto LAB_0002403e;
    }
    __printf_chk(1,"%s,%d: ",DAT_00023e88,0x4d4);
    pcVar9 = "((Packet->MessageSize == sizeof(Robot_SegmentCleanResult)) > 0)";
LAB_0002390c:
    __printf_chk(1,"Verify \'%s\' failed\n",pcVar9);
    _IO_putc(10,stdout);
    uVar4 = 0x80000002;
LAB_0002392c:
    *param_2 = 0;
  }
  else {
    if (uVar1 < 0x2105) {
      if (uVar1 == 0x65) {
        puVar3 = operator_new(0xc);
        uVar4 = DAT_00023e84;
        puVar3[1] = 0x25;
        puVar3[2] = 0;
        *puVar3 = uVar4;
      }
      else if (uVar1 < 0x66) {
        if (uVar1 == 0x16) {
          if (*(int *)(param_1 + 4) != 1) {
            uVar4 = 0x3df;
LAB_000239f4:
            __printf_chk(1,"%s,%d: ",DAT_00023b44,uVar4);
            pcVar9 = "((Packet->MessageSize == sizeof(unsigned char)) > 0)";
            goto LAB_0002390c;
          }
          cVar12 = (char)param_1[6];
          if (cVar12 != '\0') {
            puVar3 = operator_new(0x10);
            uVar6 = 0xe7;
            uVar4 = DAT_00024450;
LAB_00024022:
            *(char *)(puVar3 + 3) = cVar12;
            puVar3[1] = uVar6;
            puVar3[2] = 0;
            *puVar3 = uVar4;
            goto LAB_000239b8;
          }
          __printf_chk(1,"%s,%d: ",DAT_00023e88,0x3e6);
          pcVar9 = "EscapeSucceeded.Value";
LAB_00023c1c:
          __printf_chk(1,"%s failed\n",pcVar9);
          _IO_putc(10,stdout);
          uVar4 = 0x80000000;
          goto LAB_0002392c;
        }
        if (0x16 < uVar1) {
          if (uVar1 == 0x1a) {
            if (*(int *)(param_1 + 4) != 4) {
              __printf_chk(1,"%s,%d: ",DAT_00023e88,0x496);
              pcVar9 = "((Packet->MessageSize == sizeof(Robot_ZonedCleanResult)) > 0)";
              goto LAB_0002390c;
            }
            local_38 = *(undefined4 *)(param_1 + 6);
            puVar3 = operator_new(0x10);
            uVar6 = 0x82;
            uVar4 = DAT_000241a0;
LAB_0002403e:
            puVar3[1] = uVar6;
            puVar3[2] = 0;
            *puVar3 = uVar4;
            puVar3[3] = local_38;
          }
          else if (uVar1 < 0x1b) {
            if (uVar1 == 0x17) goto LAB_00023e90;
            if (uVar1 != 0x18) goto LAB_00023f56;
            puVar3 = operator_new(0xc);
            uVar4 = DAT_00023e84;
            puVar3[1] = 0x2b;
            puVar3[2] = 0;
            *puVar3 = uVar4;
          }
          else if (uVar1 == 0x1c) {
            if (*(int *)(param_1 + 4) != 4) {
              __printf_chk(1,"%s,%d: ",DAT_00024190,0x412);
              pcVar9 = "((Packet->MessageSize == sizeof (Robot_DockingState)) > 0)";
              goto LAB_0002390c;
            }
            switch(*(undefined4 *)(param_1 + 6)) {
            case 1:
              puVar3 = operator_new(0xc);
              uVar4 = DAT_00024424;
              puVar3[1] = 0x11;
              puVar3[2] = 0;
              *puVar3 = uVar4;
              break;
            case 2:
              puVar3 = operator_new(0xc);
              uVar4 = DAT_00024424;
              puVar3[1] = 0x12;
              puVar3[2] = 0;
              *puVar3 = uVar4;
              break;
            default:
              puVar3 = (undefined4 *)0x0;
              __printf_chk(1,"%s,%d: ",DAT_00024428,0x439);
              __printf_chk(1,"<FATAL> Unrecognized docking state type");
              _IO_putc(10,stdout);
              break;
            case 4:
              puVar3 = operator_new(0xc);
              uVar4 = DAT_00024424;
              puVar3[1] = 0x12d;
              puVar3[2] = 0;
              *puVar3 = uVar4;
              break;
            case 8:
              puVar3 = operator_new(0xc);
              uVar4 = DAT_00024424;
              puVar3[1] = 300;
              puVar3[2] = 0;
              *puVar3 = uVar4;
              break;
            case 0x10:
              puVar3 = operator_new(0xc);
              uVar4 = DAT_00024424;
              puVar3[1] = 0x12e;
              puVar3[2] = 0;
              *puVar3 = uVar4;
            }
          }
          else {
            if (uVar1 != 0x3d) goto LAB_00023f56;
            puVar3 = operator_new(0xc);
            uVar4 = DAT_00023b40;
            puVar3[1] = 0x5c;
            puVar3[2] = 0;
            *puVar3 = uVar4;
          }
          goto LAB_000239b8;
        }
        if (uVar1 == 0xf) {
          if (*(int *)(param_1 + 4) == 4) {
            local_38 = *(undefined4 *)(param_1 + 6);
            puVar3 = operator_new(0x10);
            uVar6 = 0x7b;
            uVar4 = DAT_000241b0;
            goto LAB_0002403e;
          }
          __printf_chk(1,"%s,%d: ",DAT_00023e88,0x48b);
          pcVar9 = "((Packet->MessageSize == sizeof(Robot_GotoTargetResult)) > 0)";
          goto LAB_0002390c;
        }
        if (uVar1 < 0x10) {
          if (uVar1 != 9) goto LAB_00023f56;
          puVar3 = operator_new(0xc);
          uVar4 = DAT_00023e84;
          puVar3[1] = 0x24;
          puVar3[2] = 0;
          *puVar3 = uVar4;
        }
        else {
          if (uVar1 != 0x14) {
            if (uVar1 == 0x15) {
              if (*(int *)(param_1 + 4) == 1) {
                cVar12 = (char)param_1[6];
                if (cVar12 == '\0') {
                  __printf_chk(1,"%s,%d: ",DAT_00024190,0x3d4);
                  pcVar9 = "EscapeFailed.Value";
                  goto LAB_00023c1c;
                }
                puVar3 = operator_new(0x10);
                uVar6 = 0xe6;
                uVar4 = DAT_00024450;
                goto LAB_00024022;
              }
              uVar4 = 0x3cd;
              goto LAB_000239f4;
            }
LAB_00023f56:
            uVar4 = 0x80000002;
            goto LAB_0002392c;
          }
          puVar3 = operator_new(0xc);
          uVar4 = DAT_0002418c;
          puVar3[1] = 0x2a;
          puVar3[2] = 0;
          *puVar3 = uVar4;
        }
      }
      else if (uVar1 == 400) {
        if (*(int *)(param_1 + 4) != 8) {
          __printf_chk(1,"%s,%d: ",DAT_00023e88,0x3a9);
          pcVar9 = "((Packet->MessageSize == sizeof(MotionStatus.Value)) > 0)";
          goto LAB_0002390c;
        }
        iVar5 = *(int *)(param_1 + 6);
        iVar7 = *(int *)(param_1 + 8);
        if (iVar5 == 0 && iVar7 == 0) {
          __printf_chk(1,"%s,%d: ",DAT_00024190,0x3b0);
          pcVar9 = "MotionStatus.Value";
          goto LAB_00023c1c;
        }
        puVar3 = operator_new(0x18);
        uVar4 = 0x400;
LAB_000243e2:
        uVar6 = DAT_0002444c;
        puVar3[4] = iVar5;
        puVar3[5] = iVar7;
        puVar3[1] = uVar4;
        puVar3[2] = 0;
        *puVar3 = uVar6;
      }
      else if (uVar1 < 0x191) {
        if (uVar1 == 0xcb) {
          puVar3 = operator_new(0xc);
          uVar4 = DAT_00023e84;
          puVar3[1] = 0xd2;
          puVar3[2] = 0;
          *puVar3 = uVar4;
        }
        else {
          if (0xcb < uVar1) {
            if (uVar1 == 0xcc) {
              if (*(int *)(param_1 + 4) == 4) {
                uVar6 = *(undefined4 *)(param_1 + 6);
                puVar3 = operator_new(0x10);
                uVar8 = 0xd3;
                uVar4 = DAT_00024194;
                goto LAB_00023fec;
              }
              __printf_chk(1,"%s,%d: ",DAT_00023e88,0x447);
              pcVar9 = "((Packet->MessageSize == sizeof (Robot_BackState)) > 0)";
            }
            else {
              if (uVar1 != 0xcd) goto LAB_00023f56;
              if (*(int *)(param_1 + 4) == 4) {
                local_38 = *(undefined4 *)(param_1 + 6);
                puVar3 = operator_new(0x10);
                uVar6 = 0xd4;
                uVar4 = DAT_000241a8;
                goto LAB_0002403e;
              }
              __printf_chk(1,"%s,%d: ",DAT_00023b44,0x453);
              pcVar9 = "((Packet->MessageSize == sizeof (Robot_RubResult)) > 0)";
            }
            goto LAB_0002390c;
          }
          if (uVar1 == 0x6b) {
            puVar3 = operator_new(0xc);
            uVar4 = DAT_0002418c;
            puVar3[1] = 0xb8;
            puVar3[2] = 0;
            *puVar3 = uVar4;
          }
          else {
            if (uVar1 != 0x83) goto LAB_00023f56;
            if (*(int *)(param_1 + 4) != 4) {
              __printf_chk(1,"%s,%d: ",DAT_00023b44,0x480);
              pcVar9 = "((Packet->MessageSize == sizeof(int)) > 0)";
              goto LAB_0002390c;
            }
            local_38 = *(undefined4 *)(param_1 + 6);
            puVar3 = operator_new(0x10);
            uVar6 = 0xe9;
            uVar4 = DAT_000241ac;
LAB_00024008:
            puVar3[2] = 0;
            puVar3[1] = uVar6;
            *puVar3 = uVar4;
            puVar3[3] = local_38;
          }
        }
      }
      else {
        if (uVar1 != 0x2101) {
          if (uVar1 < 0x2102) {
            if (uVar1 == 0x191) {
              if (*(int *)(param_1 + 4) == 8) {
                iVar5 = *(int *)(param_1 + 6);
                iVar7 = *(int *)(param_1 + 8);
                if (iVar5 != 0 || iVar7 != 0) {
                  puVar3 = operator_new(0x18);
                  uVar4 = 0x401;
                  goto LAB_000243e2;
                }
                __printf_chk(1,"%s,%d: ",DAT_00024190,0x3c2);
                pcVar9 = "MotionRecovery.Value";
                goto LAB_00023c1c;
              }
              __printf_chk(1,"%s,%d: ",DAT_00023e88,0x3bb);
              pcVar9 = "((Packet->MessageSize == sizeof(MotionRecovery.Value)) > 0)";
            }
            else {
              if (uVar1 != 0x328) goto LAB_00023f56;
              if (*(int *)(param_1 + 4) == 4) {
                local_38 = *(undefined4 *)(param_1 + 6);
                puVar3 = operator_new(0x10);
                uVar6 = 0x40;
                uVar4 = DAT_00024198;
                goto LAB_00024008;
              }
              __printf_chk(1,"%s,%d: ",DAT_00023b44,0x460);
              pcVar9 = "((Packet->MessageSize == sizeof(unsigned int)) > 0)";
            }
          }
          else {
            if (uVar1 == 0x2102) {
              puVar3 = operator_new(0xc);
              uVar4 = DAT_00023e84;
              puVar3[1] = 0xeb;
              puVar3[2] = 0;
              *puVar3 = uVar4;
              goto LAB_000239b8;
            }
            if (uVar1 != 0x2103) goto LAB_00023f56;
            if (*(int *)(param_1 + 4) == 1) {
              cVar12 = (char)param_1[6];
              puVar3 = operator_new(0x10);
              uVar6 = 0x834;
              uVar4 = DAT_000241b4;
              goto LAB_00024022;
            }
            __printf_chk(1,"%s,%d: ",DAT_00023b44,0x4c9);
            pcVar9 = "((Packet->MessageSize == sizeof(bool)) > 0)";
          }
          goto LAB_0002390c;
        }
LAB_00023e90:
        puVar3 = operator_new(0xc);
        uVar4 = DAT_0002418c;
        puVar3[1] = 0xe8;
        puVar3[2] = 0;
        *puVar3 = uVar4;
      }
    }
    else {
      if (uVar1 == 0x2111) {
        if (*(int *)(param_1 + 4) == 4) {
          local_38 = *(undefined4 *)(param_1 + 6);
          puVar3 = operator_new(0x10);
          uVar6 = 0x859;
          uVar4 = DAT_000241a4;
          goto LAB_00023ddc;
        }
        __printf_chk(1,"%s,%d: ",DAT_00023e88,0x527);
        pcVar9 = "((Packet->MessageSize == sizeof(TestVoiceType)) > 0)";
        goto LAB_0002390c;
      }
      if (uVar1 < 0x2112) {
        if (uVar1 == 0x210a) {
          if (*(int *)(param_1 + 4) == 4) {
            local_38 = *(undefined4 *)(param_1 + 6);
            puVar3 = operator_new(0x10);
            uVar6 = 0x843;
            uVar4 = DAT_000241b8;
            goto LAB_00024008;
          }
          __printf_chk(1,"%s,%d: ",DAT_00023e88,0x4af);
          pcVar9 = "((Packet->MessageSize == sizeof(Robot_GlobalLocationResult)) > 0)";
          goto LAB_0002390c;
        }
        if (uVar1 < 0x210b) {
          if (uVar1 == 0x2106) {
            if (*(int *)(param_1 + 4) != 0x10) {
              uVar4 = 0x4ea;
LAB_00023b98:
              __printf_chk(1,"%s,%d: ",DAT_00023e88,uVar4);
              pcVar9 = "((Packet->MessageSize == sizeof(MapHandleResult)) > 0)";
              goto LAB_0002390c;
            }
            uVar6 = *(undefined4 *)(param_1 + 6);
            uVar8 = *(undefined4 *)(param_1 + 8);
            uVar10 = *(undefined4 *)(param_1 + 10);
            uVar11 = *(undefined4 *)(param_1 + 0xc);
            puVar3 = operator_new(0x20);
            uVar13 = 0x837;
            uVar4 = DAT_000241bc;
          }
          else {
            if (0x2105 < uVar1) {
              if (uVar1 == 0x2108) {
                if (*(int *)(param_1 + 4) != 8) {
                  __printf_chk(1,"%s,%d: ",DAT_00024190,0x4f5);
                  pcVar9 = "((Packet->MessageSize == sizeof(Robot_WakeUpResult)) > 0)";
                  goto LAB_0002390c;
                }
                uVar6 = *(undefined4 *)(param_1 + 6);
                uVar8 = *(undefined4 *)(param_1 + 8);
                puVar3 = operator_new(0x14);
                uVar4 = DAT_00024430;
                puVar3[1] = 0x91;
                puVar3[2] = 0;
                *puVar3 = uVar4;
                puVar3[3] = uVar6;
                puVar3[4] = uVar8;
              }
              else {
                if (uVar1 != 0x2109) goto LAB_00023f56;
                puVar3 = operator_new(0xc);
                uVar4 = DAT_00023b40;
                puVar3[1] = 0x842;
                puVar3[2] = 0;
                *puVar3 = uVar4;
              }
              goto LAB_000239b8;
            }
            if (*(int *)(param_1 + 4) != 0x10) {
              uVar4 = 0x4df;
              goto LAB_00023b98;
            }
            uVar6 = *(undefined4 *)(param_1 + 6);
            uVar8 = *(undefined4 *)(param_1 + 8);
            uVar10 = *(undefined4 *)(param_1 + 10);
            uVar11 = *(undefined4 *)(param_1 + 0xc);
            puVar3 = operator_new(0x20);
            uVar13 = 0x836;
            uVar4 = DAT_000241c0;
          }
          puVar3[1] = uVar13;
          puVar3[2] = 0;
          *puVar3 = uVar4;
          puVar3[4] = uVar6;
          puVar3[5] = uVar8;
          puVar3[6] = uVar10;
          puVar3[7] = uVar11;
        }
        else if (uVar1 == 0x210d) {
          puVar3 = operator_new(0xc);
          uVar4 = DAT_00023e84;
          puVar3[1] = 0x84d;
          puVar3[2] = 0;
          *puVar3 = uVar4;
        }
        else if (uVar1 < 0x210e) {
          if (uVar1 == 0x210b) {
            if (*(int *)(param_1 + 4) != 4) {
              __printf_chk(1,"%s,%d: ",DAT_00023e88,0x500);
              pcVar9 = "((Packet->MessageSize == sizeof(IPC_Slam_MapFlag)) > 0)";
              goto LAB_0002390c;
            }
            local_38 = *(undefined4 *)(param_1 + 6);
            puVar3 = operator_new(0x10);
            uVar6 = 0x847;
            uVar4 = DAT_0002442c;
            goto LAB_00023ddc;
          }
          if (uVar1 != 0x210c) goto LAB_00023f56;
          puVar3 = operator_new(0xc);
          uVar4 = DAT_00023b40;
          puVar3[1] = 0x95;
          puVar3[2] = 0;
          *puVar3 = uVar4;
        }
        else {
          if (uVar1 != 0x210e) {
            if (uVar1 != 0x210f) goto LAB_00023f56;
            if (*(int *)(param_1 + 4) != 4) {
              uVar4 = 0x511;
              goto LAB_00023b24;
            }
            local_38 = *(undefined4 *)(param_1 + 6);
            puVar3 = operator_new(0x10);
            uVar6 = 0x857;
            uVar4 = DAT_00024448;
            goto LAB_00023ddc;
          }
          puVar3 = operator_new(0xc);
          uVar4 = DAT_0002418c;
          puVar3[1] = 0x84c;
          puVar3[2] = 0;
          *puVar3 = uVar4;
        }
      }
      else if (uVar1 == 0x2117) {
        puVar3 = operator_new(0xc);
        uVar4 = DAT_00023e84;
        puVar3[1] = 0xf3;
        puVar3[2] = 0;
        *puVar3 = uVar4;
      }
      else if (uVar1 < 0x2118) {
        if (uVar1 == 0x2114) {
          puVar3 = operator_new(0xc);
          uVar4 = DAT_00023e84;
          puVar3[1] = 0xec;
          puVar3[2] = 0;
          *puVar3 = uVar4;
        }
        else if (uVar1 < 0x2115) {
          if (uVar1 == 0x2112) {
            puVar3 = operator_new(0xc);
            uVar4 = DAT_0002418c;
            puVar3[1] = 0x85d;
            puVar3[2] = 0;
            *puVar3 = uVar4;
          }
          else {
            if (uVar1 != 0x2113) goto LAB_00023f56;
            if (*(int *)(param_1 + 4) != 8) {
              __printf_chk(1,"%s,%d: ",DAT_00023b44,0x532);
              pcVar9 = "((Packet->MessageSize == sizeof(WaterBoxWorkingTime)) > 0)";
              goto LAB_0002390c;
            }
            uVar6 = *(undefined4 *)(param_1 + 6);
            uVar8 = *(undefined4 *)(param_1 + 8);
            puVar3 = operator_new(0x14);
            uVar4 = DAT_00024444;
            puVar3[1] = 0x85b;
            puVar3[2] = 0;
            *puVar3 = uVar4;
            puVar3[3] = uVar6;
            puVar3[4] = uVar8;
          }
        }
        else {
          if (uVar1 != 0x2115) {
            if (uVar1 == 0x2116) {
              if (*(int *)(param_1 + 4) == 1) {
                cVar12 = (char)param_1[6];
                puVar3 = operator_new(0x10);
                uVar6 = 0xee;
                uVar4 = DAT_0002419c;
                goto LAB_00024022;
              }
              __printf_chk(1,"%s,%d: ",DAT_00023b44,0x552);
              pcVar9 = "((Packet->MessageSize == sizeof(mopMotorStatus)) > 0)";
              goto LAB_0002390c;
            }
            goto LAB_00023f56;
          }
          puVar3 = operator_new(0xc);
          uVar4 = DAT_00023e84;
          puVar3[1] = 0xed;
          puVar3[2] = 0;
          *puVar3 = uVar4;
        }
      }
      else {
        if (uVar1 == 0x211c) {
          if (*(int *)(param_1 + 4) != 4) {
            uVar4 = 0x51c;
LAB_00023b24:
            __printf_chk(1,"%s,%d: ",DAT_00023b44,uVar4);
            pcVar9 = "((Packet->MessageSize == sizeof(Robot_MopMotorState)) > 0)";
            goto LAB_0002390c;
          }
          local_38 = *(undefined4 *)(param_1 + 6);
          puVar3 = operator_new(0x10);
          uVar6 = 0x868;
          uVar4 = DAT_00023e8c;
        }
        else {
          if (0x211c < uVar1) {
            if (uVar1 == 0x2120) {
              if (*(int *)(param_1 + 4) != 4) {
                __printf_chk(1,"%s,%d: ",DAT_00024190,0x59e);
                pcVar9 = "((Packet->MessageSize == sizeof(DockType_e)) > 0)";
                goto LAB_0002390c;
              }
              uVar6 = *(undefined4 *)(param_1 + 6);
              FUN_00020728(0x5a0,DAT_00024428,DAT_0006a690 & 0x2000,"#12361`%d",uVar6);
              puVar3 = operator_new(0x10);
              uVar8 = 0x22a;
              uVar4 = DAT_00024440;
LAB_00023fec:
              puVar3[3] = uVar6;
              puVar3[1] = uVar8;
              puVar3[2] = 0;
              *puVar3 = uVar4;
            }
            else {
              if (uVar1 != 0x2128) goto LAB_00023f56;
              if (*(int *)(param_1 + 4) != 0x10) {
                __printf_chk(1,"%s,%d: ",DAT_00023b44,0x5ab);
                pcVar9 = "((Packet->MessageSize == sizeof(MapsHandleResult)) > 0)";
                goto LAB_0002390c;
              }
              uVar6 = *(undefined4 *)(param_1 + 6);
              uVar8 = *(undefined4 *)(param_1 + 8);
              uVar10 = *(undefined4 *)(param_1 + 10);
              uVar11 = *(undefined4 *)(param_1 + 0xc);
              puVar3 = operator_new(0x20);
              uVar4 = DAT_00024454;
              puVar3[1] = 0x873;
              puVar3[2] = 0;
              *puVar3 = uVar4;
              puVar3[4] = uVar6;
              puVar3[5] = uVar8;
              puVar3[6] = uVar10;
              puVar3[7] = uVar11;
            }
            goto LAB_000239b8;
          }
          if (uVar1 == 0x211a) {
            if (*(int *)(param_1 + 4) != 4) {
              __printf_chk(1,"%s,%d: ",DAT_00023e88,0x588);
              pcVar9 = "((Packet->MessageSize == sizeof(Robot_WaterBoxModeStatus)) > 0)";
              goto LAB_0002390c;
            }
            local_38 = *(undefined4 *)(param_1 + 6);
            puVar3 = operator_new(0x10);
            uVar6 = 0x865;
            uVar4 = DAT_0002443c;
          }
          else {
            if (uVar1 != 0x211b) goto LAB_00023f56;
            if (*(int *)(param_1 + 4) != 4) {
              __printf_chk(1,"%s,%d: ",DAT_00023b44,0x593);
              pcVar9 = "((Packet->MessageSize == sizeof(Robot_VacModeStatus)) > 0)";
              goto LAB_0002390c;
            }
            local_38 = *(undefined4 *)(param_1 + 6);
            puVar3 = operator_new(0x10);
            uVar6 = 0x866;
            uVar4 = DAT_00024438;
          }
        }
LAB_00023ddc:
        puVar3[1] = uVar6;
        puVar3[2] = 0;
        *puVar3 = uVar4;
        puVar3[3] = local_38;
      }
    }
LAB_000239b8:
    uVar4 = 0;
    *param_2 = puVar3;
  }
  if (iVar2 != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(uVar4);
  }
  return;
}

