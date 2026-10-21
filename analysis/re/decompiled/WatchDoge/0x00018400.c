/* Decompiled C, NOT recovered source; need not compile.
 * Binary: WatchDoge
 * SHA256: 3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6
 * Function VA: 0x00018400
 */

/* WARNING: Removing unreachable block (ram,0x000187b0) */
/* WARNING: Removing unreachable block (ram,0x00018b92) */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Reads exclusions from the path held by a C++ string ABI object. At most three parser iterations
   per line; comma prefixes are accepted even empty, but a final no-comma remainder is added only
   when length >3. No whitespace trimming observed. Each process is initially enabled (+0x18=1);
   std::string::find(name,+4,token) disables matches (+0x18=0). Positive signed tracked PID triggers
   kill(pid,9) at 0x18aaa and PID=-1 at 0x18aee regardless of kill result. No wait, writer flush,
   MCU heartbeat adjustment or descendant accounting. Open failure enables all records. Reload alone
   does not launch processes. */

void WdogReloadExclusions(void *supervisor,void *path_string)

{
  bool bVar1;
  char cVar2;
  int iVar3;
  istream *piVar4;
  string *psVar5;
  uint *puVar6;
  int iVar7;
  uint uVar8;
  __pid_t *p_Var9;
  int iVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  undefined4 *puVar14;
  int iVar15;
  int *piVar16;
  undefined4 *puVar17;
  undefined4 uVar18;
  int iVar19;
  undefined4 uVar20;
  undefined4 uVar21;
  int iVar22;
  uint uVar23;
  int iVar24;
  uint uVar25;
  undefined8 uVar26;
  int local_184;
  int local_180;
  int local_17c;
  int local_178;
  int local_168;
  undefined4 local_164;
  undefined4 local_160;
  undefined4 local_15c;
  undefined4 *local_158;
  int local_154;
  undefined4 local_150;
  undefined4 local_14c;
  undefined4 local_148;
  int local_144 [2];
  undefined4 local_13c [3];
  uint auStack_130 [4];
  locale alStack_120 [28];
  __basic_file<char> a_Stack_104 [60];
  undefined4 auStack_c8 [5];
  int local_b4 [5];
  uint local_a0;
  undefined4 local_44;
  undefined1 local_40;
  undefined1 local_3f;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  int local_2c;
  
  local_2c = __stack_chk_guard;
  std::ios_base::ios_base((ios_base *)local_b4);
  uVar18 = std::ifstream::VTT._8_4_;
  iVar12 = std::ifstream::VTT._4_4_;
  local_40 = 0;
  local_b4[0] = DAT_000186f4;
  local_144[0] = std::ifstream::VTT._4_4_;
  local_44 = 0;
  local_3f = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  *(undefined4 *)((int)local_144 + *(int *)(std::ifstream::VTT._4_4_ + -0xc)) =
       std::ifstream::VTT._8_4_;
  local_144[1] = 0;
  std::ios::init((streambuf *)((int)local_144 + *(int *)(std::ifstream::VTT._4_4_ + -0xc)));
  local_144[0] = DAT_000186f8;
  local_b4[0] = DAT_000186f8 + 0x14;
  std::filebuf::filebuf((filebuf *)local_13c);
  std::ios::init((streambuf *)local_b4);
  iVar3 = std::filebuf::open(local_13c,*(undefined4 *)path_string,8);
  if (iVar3 == 0) {
    std::ios::clear((int)local_144 + *(int *)(local_144[0] + -0xc),
                    *(uint *)((int)auStack_130 + *(int *)(local_144[0] + -0xc)) | 4);
  }
  else {
    std::ios::clear((int)local_144 + *(int *)(local_144[0] + -0xc),0);
  }
  if ((local_a0 & 5) == 0) {
    iVar12 = (int)supervisor + 0x2c;
    local_150 = *(undefined4 *)((int)supervisor + 0x48);
    local_154 = *(int *)((int)supervisor + 0x44);
    puVar17 = *(undefined4 **)((int)supervisor + 0x40);
    uVar21 = *(undefined4 *)((int)supervisor + 0x34);
    uVar20 = *(undefined4 *)((int)supervisor + 0x38);
    uVar18 = *(undefined4 *)((int)supervisor + 0x3c);
    local_14c = *(undefined4 *)((int)supervisor + 0x4c);
    local_148 = *(undefined4 *)((int)supervisor + 0x50);
    local_168 = DAT_00018704;
    local_164 = uVar21;
    local_160 = uVar20;
    local_15c = uVar18;
    local_158 = puVar17;
    FUN_0001a988(iVar12,&local_164,&local_154);
    iVar3 = *(int *)((int)supervisor + 0x50);
    puVar14 = puVar17;
    while (puVar14 = puVar14 + 1, puVar14 < (undefined4 *)(iVar3 + 4)) {
      operator_delete((void *)*puVar14);
    }
    *(undefined4 *)((int)supervisor + 0x44) = uVar21;
    *(undefined4 *)((int)supervisor + 0x48) = uVar20;
    *(undefined4 *)((int)supervisor + 0x4c) = uVar18;
    *(undefined4 **)((int)supervisor + 0x50) = puVar17;
    while( true ) {
      piVar16 = *(int **)((int)auStack_c8 + *(int *)(local_144[0] + -0xc));
      if (piVar16 == (int *)0x0) {
        std::__throw_bad_cast();
        if ((undefined1 *)(local_168 + -0xc) != std::string::_Rep::_S_empty_rep_storage) {
          FUN_00013edc((undefined1 *)(local_168 + -0xc),&local_154);
        }
        std::ifstream::~ifstream((ifstream *)local_144);
        __cxa_end_cleanup();
        std::filebuf::~filebuf((filebuf *)local_13c);
        do {
          *(undefined4 *)((int)local_144 + s_g__11567_00020788._0_4_) = 0x1a1ad;
          local_b4[0] = DAT_00018bf8;
          std::ios_base::~ios_base((ios_base *)local_b4);
          __cxa_end_cleanup();
        } while( true );
      }
      if ((char)piVar16[7] == '\0') {
        std::ctype<char>::_M_widen_init();
        if (*(code **)(*piVar16 + 0x18) == (code *)0x1a1ad) {
          cVar2 = '\n';
        }
        else {
          cVar2 = (**(code **)(*piVar16 + 0x18))(piVar16,10);
        }
      }
      else {
        cVar2 = *(char *)((int)piVar16 + 0x27);
      }
      piVar4 = std::getline<char,std::char_traits<char>,std::allocator<char>>
                         ((istream *)local_144,(string *)&local_168,cVar2);
      if ((*(uint *)(piVar4 + *(int *)(*(int *)piVar4 + -0xc) + 0x14) & 5) != 0) break;
      uVar26 = get_cur_time_ms();
      __printf_chk(1,"%llu,wdog,#11525`%s\n",(int)uVar26,(int)((ulonglong)uVar26 >> 0x20),local_168)
      ;
      fflush(stdout);
      iVar3 = 3;
      do {
        uVar11 = std::string::find((char *)&local_168,0x20708,0);
        if (uVar11 == 0xffffffff) {
          if (3 < *(uint *)(local_168 + -0xc)) {
            psVar5 = *(string **)((int)supervisor + 0x44);
            if (psVar5 == (string *)(*(int *)((int)supervisor + 0x4c) + -4)) {
              FUN_0001a500(iVar12,&local_168);
            }
            else {
              iVar15 = 0;
              if (psVar5 != (string *)0x0) {
                std::string::string(psVar5,(string *)&local_168);
                iVar15 = *(int *)((int)supervisor + 0x44);
              }
              *(int *)((int)supervisor + 0x44) = iVar15 + 4;
            }
            uVar26 = get_cur_time_ms();
            __printf_chk(1,"%llu,wdog,#11527`%s\n",(int)uVar26,(int)((ulonglong)uVar26 >> 0x20),
                         local_168);
            fflush(stdout);
            std::string::_M_mutate((uint)&local_168,0,*(uint *)(local_168 + -0xc));
          }
        }
        else {
          std::string::string((string *)&local_154,(string *)&local_168,0,uVar11);
          uVar23 = *(uint *)(local_168 + -0xc);
          if (uVar11 + 1 <= *(uint *)(local_168 + -0xc)) {
            uVar23 = uVar11 + 1;
          }
          std::string::_M_mutate((uint)&local_168,0,uVar23);
          psVar5 = *(string **)((int)supervisor + 0x44);
          if (psVar5 == (string *)(*(int *)((int)supervisor + 0x4c) + -4)) {
            FUN_0001a500(iVar12,&local_154);
          }
          else {
            iVar15 = 0;
            if (psVar5 != (string *)0x0) {
              std::string::string(psVar5,(string *)&local_154);
              iVar15 = *(int *)((int)supervisor + 0x44);
            }
            *(int *)((int)supervisor + 0x44) = iVar15 + 4;
          }
          uVar26 = get_cur_time_ms();
          __printf_chk(1,"%llu,wdog,#11526`%s\n",(int)uVar26,(int)((ulonglong)uVar26 >> 0x20),
                       local_154);
          fflush(stdout);
          if ((allocator *)(local_154 + -0xc) !=
              (allocator *)std::string::_Rep::_S_empty_rep_storage) {
            piVar16 = (int *)(local_154 + -4);
            DataMemoryBarrier(0x1b);
            do {
              ExclusiveAccess(piVar16);
              iVar15 = *piVar16;
              bVar1 = (bool)hasExclusiveAccess(piVar16);
            } while (!bVar1);
            *piVar16 = iVar15 + -1;
            DataMemoryBarrier(0x1b);
            if (iVar15 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_154 + -0xc));
            }
          }
        }
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    local_180 = *(int *)((int)supervisor + 0x1c);
    local_178 = *(int *)((int)supervisor + 0x28);
    iVar15 = *(int *)((int)supervisor + 0x18);
    local_17c = *(int *)((int)supervisor + 0x20);
    iVar3 = 0;
    iVar12 = *(int *)((int)supervisor + 0xc);
    local_184 = *(int *)((int)supervisor + 0x14);
    uVar11 = 0;
    if ((local_184 - iVar12 >> 2) * -0x49249249 +
        ((local_178 - iVar15 >> 2) + -1) * 0x12 + (local_180 - local_17c >> 2) * -0x49249249 != 0) {
LAB_00018820:
      iVar22 = *(int *)((int)supervisor + 0x10);
      uVar23 = (iVar12 - iVar22 >> 2) * -0x49249249 + uVar11;
      if (uVar23 < 0x12) {
        iVar7 = iVar12 + iVar3;
      }
      else {
        if ((int)uVar23 < 1) {
          uVar8 = ~(~uVar23 / 0x12);
        }
        else {
          uVar8 = (int)uVar23 / 0x12;
        }
        iVar7 = (uVar23 + uVar8 * -0x12) * 0x1c + *(int *)(iVar15 + uVar8 * 4);
      }
      iVar24 = *(int *)((int)supervisor + 0x40);
      iVar13 = *(int *)((int)supervisor + 0x50);
      iVar10 = *(int *)((int)supervisor + 0x48);
      iVar19 = *(int *)((int)supervisor + 0x44);
      *(undefined1 *)(iVar7 + 0x18) = 1;
      iVar7 = *(int *)((int)supervisor + 0x34);
      if ((iVar19 - iVar10 >> 2) + ((iVar13 - iVar24 >> 2) + -1) * 0x80 +
          (*(int *)((int)supervisor + 0x3c) - iVar7 >> 2) != 0) {
        uVar23 = 0;
        do {
          uVar8 = (iVar12 - iVar22 >> 2) * -0x49249249 + uVar11;
          if (uVar8 < 0x12) {
            iVar12 = iVar12 + iVar3;
          }
          else {
            if ((int)uVar8 < 1) {
              uVar25 = ~(~uVar8 / 0x12);
            }
            else {
              uVar25 = (int)uVar8 / 0x12;
            }
            iVar12 = (uVar8 + uVar25 * -0x12) * 0x1c + *(int *)(iVar15 + uVar25 * 4);
          }
          uVar8 = uVar23 + (iVar7 - *(int *)((int)supervisor + 0x38) >> 2);
          if (uVar8 < 0x80) {
            puVar6 = (uint *)(iVar7 + uVar23 * 4);
          }
          else {
            if ((int)uVar8 < 1) {
              uVar25 = ~(~uVar8 >> 7);
            }
            else {
              uVar25 = (int)uVar8 >> 7;
            }
            puVar6 = (uint *)(*(int *)(iVar24 + uVar25 * 4) + (uVar8 + uVar25 * -0x80) * 4);
          }
          iVar12 = std::string::find((char *)(iVar12 + 4),*puVar6,0);
          if (iVar12 != -1) {
            iVar12 = *(int *)((int)supervisor + 0xc);
            uVar23 = (iVar12 - *(int *)((int)supervisor + 0x10) >> 2) * -0x49249249 + uVar11;
            if (uVar23 < 0x12) {
              *(undefined1 *)((int *)(iVar12 + iVar3) + 6) = 0;
              if (0 < *(int *)(iVar12 + iVar3)) goto LAB_00018a12;
LAB_00018958:
              local_178 = *(int *)((int)supervisor + 0x28);
              iVar15 = *(int *)((int)supervisor + 0x18);
            }
            else {
              if ((int)uVar23 < 1) {
                iVar15 = *(int *)((int)supervisor + 0x18);
                uVar8 = ~(~uVar23 / 0x12);
                *(undefined1 *)
                 ((uVar23 + uVar8 * -0x12) * 0x1c + *(int *)(iVar15 + uVar8 * 4) + 0x18) = 0;
              }
              else {
                iVar15 = *(int *)((int)supervisor + 0x18);
                uVar8 = (int)uVar23 / 0x12;
                *(undefined1 *)(((int)uVar23 % 0x12) * 0x1c + *(int *)(iVar15 + uVar8 * 4) + 0x18) =
                     0;
              }
              if (*(int *)((uVar23 + uVar8 * -0x12) * 0x1c + *(int *)(iVar15 + uVar8 * 4)) < 1)
              goto LAB_00018958;
LAB_00018a12:
              uVar26 = get_cur_time_ms();
              uVar23 = (*(int *)((int)supervisor + 0xc) - *(int *)((int)supervisor + 0x10) >> 2) *
                       -0x49249249 + uVar11;
              if (uVar23 < 0x12) {
                iVar12 = *(int *)((int)supervisor + 0xc) + iVar3;
              }
              else {
                if ((int)uVar23 < 1) {
                  uVar8 = ~(~uVar23 / 0x12);
                }
                else {
                  uVar8 = (int)uVar23 / 0x12;
                }
                iVar12 = (uVar23 + uVar8 * -0x12) * 0x1c +
                         *(int *)(*(int *)((int)supervisor + 0x18) + uVar8 * 4);
              }
              __printf_chk(1,"%llu,wdog,#11528`%s\n",(int)uVar26,(int)((ulonglong)uVar26 >> 0x20),
                           *(undefined4 *)(iVar12 + 4));
              fflush(stdout);
              uVar23 = (*(int *)((int)supervisor + 0xc) - *(int *)((int)supervisor + 0x10) >> 2) *
                       -0x49249249 + uVar11;
              if (uVar23 < 0x12) {
                p_Var9 = (__pid_t *)(*(int *)((int)supervisor + 0xc) + iVar3);
              }
              else {
                if ((int)uVar23 < 1) {
                  uVar8 = ~(~uVar23 / 0x12);
                }
                else {
                  uVar8 = (int)uVar23 / 0x12;
                }
                p_Var9 = (__pid_t *)
                         ((uVar23 + uVar8 * -0x12) * 0x1c +
                         *(int *)(*(int *)((int)supervisor + 0x18) + uVar8 * 4));
              }
              kill(*p_Var9,9);
              iVar12 = *(int *)((int)supervisor + 0xc);
              iVar15 = *(int *)((int)supervisor + 0x18);
              uVar23 = (iVar12 - *(int *)((int)supervisor + 0x10) >> 2) * -0x49249249 + uVar11;
              if (uVar23 < 0x12) {
                puVar14 = (undefined4 *)(iVar12 + iVar3);
              }
              else {
                if ((int)uVar23 < 1) {
                  uVar8 = ~(~uVar23 / 0x12);
                }
                else {
                  uVar8 = (int)uVar23 / 0x12;
                }
                puVar14 = (undefined4 *)
                          ((uVar23 + uVar8 * -0x12) * 0x1c + *(int *)(iVar15 + uVar8 * 4));
              }
              local_178 = *(int *)((int)supervisor + 0x28);
              *puVar14 = 0xffffffff;
            }
            local_180 = *(int *)((int)supervisor + 0x1c);
            local_17c = *(int *)((int)supervisor + 0x20);
            local_184 = *(int *)((int)supervisor + 0x14);
            break;
          }
          uVar23 = uVar23 + 1;
          iVar24 = *(int *)((int)supervisor + 0x40);
          iVar7 = *(int *)((int)supervisor + 0x34);
          if ((uint)((*(int *)((int)supervisor + 0x44) - *(int *)((int)supervisor + 0x48) >> 2) +
                     ((*(int *)((int)supervisor + 0x50) - iVar24 >> 2) + -1) * 0x80 +
                    (*(int *)((int)supervisor + 0x3c) - iVar7 >> 2)) <= uVar23) goto LAB_000189b6;
          iVar12 = *(int *)((int)supervisor + 0xc);
          iVar22 = *(int *)((int)supervisor + 0x10);
          iVar15 = *(int *)((int)supervisor + 0x18);
        } while( true );
      }
      goto LAB_0001896e;
    }
LAB_000189a0:
    uVar18 = std::ifstream::VTT._8_4_;
    iVar12 = std::ifstream::VTT._4_4_;
    if ((allocator *)(local_168 + -0xc) != (allocator *)std::string::_Rep::_S_empty_rep_storage) {
      piVar16 = (int *)(local_168 + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar16);
        iVar3 = *piVar16;
        bVar1 = (bool)hasExclusiveAccess(piVar16);
      } while (!bVar1);
      *piVar16 = iVar3 + -1;
      DataMemoryBarrier(0x1b);
      uVar18 = std::ifstream::VTT._8_4_;
      iVar12 = std::ifstream::VTT._4_4_;
      if (iVar3 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_168 + -0xc));
        uVar18 = std::ifstream::VTT._8_4_;
        iVar12 = std::ifstream::VTT._4_4_;
      }
    }
  }
  else {
    iVar22 = *(int *)((int)supervisor + 0x18);
    iVar15 = *(int *)((int)supervisor + 0xc);
    iVar3 = (*(int *)((int)supervisor + 0x14) - iVar15 >> 2) * -0x49249249 +
            ((*(int *)((int)supervisor + 0x28) - iVar22 >> 2) + -1) * 0x12 +
            (*(int *)((int)supervisor + 0x1c) - *(int *)((int)supervisor + 0x20) >> 2) * -0x49249249
    ;
    if (iVar3 != 0) {
      iVar10 = iVar15 - *(int *)((int)supervisor + 0x10);
      iVar7 = 0;
      do {
        uVar11 = iVar7 + (iVar10 >> 2) * -0x49249249;
        iVar13 = iVar15;
        if (0x11 < uVar11) {
          if ((int)uVar11 < 1) {
            uVar23 = ~(~uVar11 / 0x12);
          }
          else {
            uVar23 = (int)uVar11 / 0x12;
          }
          iVar13 = (uVar11 + uVar23 * -0x12) * 0x1c + *(int *)(iVar22 + uVar23 * 4);
        }
        iVar7 = iVar7 + 1;
        *(undefined1 *)(iVar13 + 0x18) = 1;
        iVar15 = iVar15 + 0x1c;
      } while (iVar7 != iVar3);
    }
  }
  local_13c[0] = DAT_000186fc;
  local_144[0] = DAT_000186f8;
  local_b4[0] = DAT_000186f8 + 0x14;
  std::filebuf::close();
  std::__basic_file<char>::~__basic_file(a_Stack_104);
  local_13c[0] = DAT_00018700;
  std::locale::~locale(alStack_120);
  *(undefined4 *)((int)local_144 + *(int *)(iVar12 + -0xc)) = uVar18;
  local_b4[0] = DAT_000186f4;
  std::ios_base::~ios_base((ios_base *)local_b4);
  if (local_2c != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
LAB_000189b6:
  local_178 = *(int *)((int)supervisor + 0x28);
  iVar12 = *(int *)((int)supervisor + 0xc);
  iVar15 = *(int *)((int)supervisor + 0x18);
  local_180 = *(int *)((int)supervisor + 0x1c);
  local_17c = *(int *)((int)supervisor + 0x20);
  local_184 = *(int *)((int)supervisor + 0x14);
LAB_0001896e:
  uVar11 = uVar11 + 1;
  iVar3 = iVar3 + 0x1c;
  if ((uint)((local_184 - iVar12 >> 2) * -0x49249249 +
            ((local_178 - iVar15 >> 2) + -1) * 0x12 + (local_180 - local_17c >> 2) * -0x49249249) <=
      uVar11) goto LAB_000189a0;
  goto LAB_00018820;
}

