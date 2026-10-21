/* Decompiled C, NOT recovered source; need not compile.
 * Binary: WatchDoge
 * SHA256: 3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6
 * Function VA: 0x0001779c
 */

/* WARNING: Removing unreachable block (ram,0x00017e3a) */
/* WARNING: Removing unreachable block (ram,0x00017e5e) */
/* WARNING: Removing unreachable block (ram,0x00017e52) */
/* WARNING: Removing unreachable block (ram,0x00017e16) */
/* WARNING: Removing unreachable block (ram,0x00017e46) */
/* WARNING: Removing unreachable block (ram,0x00017e0a) */
/* WARNING: Removing unreachable block (ram,0x00017e2e) */
/* WARNING: Removing unreachable block (ram,0x00017e22) */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Loads the configured process list. path_string is an ABI pointer to a C++ string object, NOT
   char*. Record stride 0x1c; observed fields PID +0, name string +4, command string +8, key flag
   +0xc, stop timeout +0x10, start delay +0x14, enabled byte +0x18. No original class/STL layout is
   asserted; other fields and padding remain unknown. */

void WdogLoadProcessList(void *supervisor,void *path_string)

{
  bool bVar1;
  char cVar2;
  int iVar3;
  istream *piVar4;
  int iVar5;
  uint uVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  uint uVar10;
  int iVar11;
  undefined4 uVar12;
  undefined4 *puVar13;
  char *pcVar14;
  int *piVar15;
  undefined4 *puVar16;
  undefined4 uVar17;
  allocator *paVar18;
  undefined8 uVar19;
  int local_184;
  int local_180;
  int local_17c;
  char *local_178;
  char *local_174;
  char *local_170;
  undefined4 local_16c;
  undefined4 local_168;
  undefined4 *local_164;
  undefined4 local_160;
  int local_15c;
  int local_158;
  long local_154;
  long local_150;
  long local_14c;
  undefined1 local_148;
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
  
  pcVar14 = *(char **)((int)supervisor + 0xc);
  uVar17 = *(undefined4 *)((int)supervisor + 0x10);
  local_2c = __stack_chk_guard;
  local_160 = *(undefined4 *)((int)supervisor + 0x1c);
  uVar12 = *(undefined4 *)((int)supervisor + 0x14);
  puVar13 = *(undefined4 **)((int)supervisor + 0x18);
  local_158 = *(int *)((int)supervisor + 0x24);
  local_15c = *(int *)((int)supervisor + 0x20);
  local_154 = *(long *)((int)supervisor + 0x28);
  local_170 = pcVar14;
  local_16c = uVar17;
  local_168 = uVar12;
  local_164 = puVar13;
  FUN_0001a610((int)supervisor + 4,&local_170,&local_160);
  iVar11 = *(int *)((int)supervisor + 0x28);
  puVar16 = puVar13;
  while (puVar16 = puVar16 + 1, puVar16 < (undefined4 *)(iVar11 + 4)) {
    operator_delete((void *)*puVar16);
  }
  *(undefined4 *)((int)supervisor + 0x24) = uVar12;
  *(char **)((int)supervisor + 0x1c) = pcVar14;
  *(undefined4 **)((int)supervisor + 0x28) = puVar13;
  *(undefined4 *)((int)supervisor + 0x20) = uVar17;
  std::ios_base::ios_base((ios_base *)local_b4);
  iVar11 = std::ifstream::VTT._4_4_;
  local_40 = 0;
  local_b4[0] = DAT_00017988;
  local_144[0] = std::ifstream::VTT._4_4_;
  local_44 = 0;
  local_3f = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  *(undefined4 *)((istream *)local_144 + *(int *)(std::ifstream::VTT._4_4_ + -0xc)) =
       std::ifstream::VTT._8_4_;
  local_144[1] = 0;
  std::ios::init((streambuf *)((istream *)local_144 + *(int *)(std::ifstream::VTT._4_4_ + -0xc)));
  local_144[0] = DAT_0001798c;
  local_b4[0] = DAT_0001798c + 0x14;
  std::filebuf::filebuf((filebuf *)local_13c);
  std::ios::init((streambuf *)local_b4);
  iVar3 = std::filebuf::open(local_13c,*(undefined4 *)path_string,8);
  if (iVar3 == 0) {
    std::ios::clear((istream *)local_144 + *(int *)(local_144[0] + -0xc),
                    *(uint *)((int)auStack_130 + *(int *)(local_144[0] + -0xc)) | 4);
  }
  else {
    std::ios::clear((istream *)local_144 + *(int *)(local_144[0] + -0xc),0);
  }
  iVar3 = DAT_00017998;
  if ((local_a0 & 5) == 0) {
    paVar18 = (allocator *)(DAT_00017998 + -0xc);
    local_184 = DAT_00017998;
LAB_000178ee:
    do {
      piVar15 = *(int **)((int)auStack_c8 + *(int *)(local_144[0] + -0xc));
      if (piVar15 == (int *)0x0) goto LAB_00017e6a;
      if ((char)piVar15[7] == '\0') {
        std::ctype<char>::_M_widen_init();
        if (*(code **)(*piVar15 + 0x18) == (code *)0x1a1ad) {
          cVar2 = '\n';
        }
        else {
          cVar2 = (**(code **)(*piVar15 + 0x18))(piVar15,10);
        }
      }
      else {
        cVar2 = *(char *)((int)piVar15 + 0x27);
      }
      piVar4 = std::getline<char,std::char_traits<char>,std::allocator<char>>
                         ((istream *)local_144,(string *)&local_184,cVar2);
      if ((*(uint *)(piVar4 + *(int *)(*(int *)piVar4 + -0xc) + 0x14) & 5) != 0) {
        if ((allocator *)(local_184 + -0xc) != paVar18) {
          piVar15 = (int *)(local_184 + -4);
          DataMemoryBarrier(0x1b);
          do {
            ExclusiveAccess(piVar15);
            iVar11 = *piVar15;
            bVar1 = (bool)hasExclusiveAccess(piVar15);
          } while (!bVar1);
          *piVar15 = iVar11 + -1;
          DataMemoryBarrier(0x1b);
          if (iVar11 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_184 + -0xc));
          }
        }
        local_13c[0] = DAT_00017990;
        local_144[0] = DAT_0001798c;
        local_b4[0] = DAT_0001798c + 0x14;
        std::filebuf::close();
        std::__basic_file<char>::~__basic_file(a_Stack_104);
        local_13c[0] = DAT_00017994;
        std::locale::~locale(alStack_120);
        *(undefined4 *)((istream *)local_144 + *(int *)(std::ifstream::VTT._4_4_ + -0xc)) =
             std::ifstream::VTT._8_4_;
        local_b4[0] = DAT_00017988;
        std::ios_base::~ios_base((ios_base *)local_b4);
        if (local_2c != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
          __stack_chk_fail();
        }
        return;
      }
      iVar5 = std::string::find((char *)&local_184,0x206c8,0);
      if (iVar5 != 0) {
        if (*(int *)((int)supervisor + 0x58) + *(int *)((int)supervisor + 0x5c) == 0) {
          uVar19 = get_cur_time_ms();
          __printf_chk(1,"%llu,wdog,#11523\n",(int)uVar19,(int)((ulonglong)uVar19 >> 0x20));
          fflush(stdout);
          iVar5 = std::string::find((char *)&local_184,0x206e0,0);
          if ((iVar5 != -1) ||
             (iVar5 = std::string::find((char *)&local_184,0x206ec,0), iVar5 != -1)) {
            uVar19 = get_cur_time_ms();
            __printf_chk(1,"%llu,wdog,#11524\n",(int)uVar19,(int)((ulonglong)uVar19 >> 0x20));
            fflush(stdout);
            goto LAB_000178ee;
          }
        }
        uVar6 = std::string::find((char *)&local_184,0x20708,0);
        std::string::string((string *)&local_180,(string *)&local_184,0,uVar6);
        uVar10 = *(uint *)(local_184 + -0xc);
        if (uVar6 + 1 <= *(uint *)(local_184 + -0xc)) {
          uVar10 = uVar6 + 1;
        }
        std::string::_M_mutate((uint)&local_184,0,uVar10);
        uVar6 = std::string::find((char *)&local_184,0x20708,0);
        std::string::string((string *)&local_17c,(string *)&local_184,0,uVar6);
        uVar10 = *(uint *)(local_184 + -0xc);
        if (uVar6 + 1 <= *(uint *)(local_184 + -0xc)) {
          uVar10 = uVar6 + 1;
        }
        std::string::_M_mutate((uint)&local_184,0,uVar10);
        uVar6 = std::string::find((char *)&local_184,0x20708,0);
        std::string::string((string *)&local_178,(string *)&local_184,0,uVar6);
        uVar10 = *(uint *)(local_184 + -0xc);
        if (uVar6 + 1 <= *(uint *)(local_184 + -0xc)) {
          uVar10 = uVar6 + 1;
        }
        std::string::_M_mutate((uint)&local_184,0,uVar10);
        uVar6 = std::string::find((char *)&local_184,0x20708,0);
        std::string::string((string *)&local_174,(string *)&local_184,0,uVar6);
        uVar10 = uVar6 + 1;
        if (*(uint *)(local_184 + -0xc) <= uVar6 + 1) {
          uVar10 = *(uint *)(local_184 + -0xc);
        }
        std::string::_M_mutate((uint)&local_184,0,uVar10);
        std::string::string((string *)&local_170,(string *)&local_184,0,uVar6);
        lVar7 = strtol(local_178,(char **)0x0,10);
        lVar8 = strtol(local_174,(char **)0x0,10);
        lVar9 = strtol(local_170,(char **)0x0,10);
        local_15c = iVar3;
        local_158 = iVar3;
        std::string::assign((string *)&local_15c);
        std::string::assign((string *)&local_158);
        local_160 = 0xffffffff;
        local_148 = 1;
        local_154 = lVar7;
        local_150 = lVar8;
        local_14c = lVar9;
        uVar19 = get_cur_time_ms();
        iVar11 = local_180;
        __printf_chk(1,"%llu,wdog,Name: %s Cmd: %s KeyProc:%d KillTimeout:%d WaitAfterStart:%d\n",
                     (int)uVar19,(int)((ulonglong)uVar19 >> 0x20),local_180,local_17c,lVar7,lVar8,
                     lVar9);
        fflush(stdout);
        puVar16 = *(undefined4 **)((int)supervisor + 0x1c);
        if (puVar16 == (undefined4 *)(*(int *)((int)supervisor + 0x24) + -0x1c)) {
          FUN_0001a384((int)supervisor + 4,&local_160);
        }
        else {
          iVar5 = 0;
          if (puVar16 != (undefined4 *)0x0) {
            *puVar16 = local_160;
            std::string::string((string *)(puVar16 + 1),(string *)&local_15c);
            std::string::string((string *)(puVar16 + 2),(string *)&local_158);
            puVar16[3] = local_154;
            puVar16[4] = local_150;
            puVar16[5] = local_14c;
            *(undefined1 *)(puVar16 + 6) = local_148;
            iVar5 = *(int *)((int)supervisor + 0x1c);
          }
          *(int *)((int)supervisor + 0x1c) = iVar5 + 0x1c;
        }
        if ((allocator *)(local_158 + -0xc) != paVar18) {
          piVar15 = (int *)(local_158 + -4);
          DataMemoryBarrier(0x1b);
          do {
            ExclusiveAccess(piVar15);
            iVar5 = *piVar15;
            bVar1 = (bool)hasExclusiveAccess(piVar15);
          } while (!bVar1);
          *piVar15 = iVar5 + -1;
          DataMemoryBarrier(0x1b);
          iVar11 = 0;
          if (iVar5 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_158 + -0xc));
          }
        }
        if ((allocator *)(local_15c + -0xc) != paVar18) {
          piVar15 = (int *)(local_15c + -4);
          DataMemoryBarrier(0x1b);
          do {
            ExclusiveAccess(piVar15);
            iVar5 = *piVar15;
            bVar1 = (bool)hasExclusiveAccess(piVar15);
          } while (!bVar1);
          *piVar15 = iVar5 + -1;
          DataMemoryBarrier(0x1b);
          iVar11 = 0;
          if (iVar5 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_15c + -0xc));
          }
        }
        if ((allocator *)(local_170 + -0xc) != paVar18) {
          piVar15 = (int *)(local_170 + -4);
          DataMemoryBarrier(0x1b);
          do {
            ExclusiveAccess(piVar15);
            iVar5 = *piVar15;
            bVar1 = (bool)hasExclusiveAccess(piVar15);
          } while (!bVar1);
          *piVar15 = iVar5 + -1;
          DataMemoryBarrier(0x1b);
          iVar11 = 0;
          if (iVar5 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_170 + -0xc));
          }
        }
        if ((allocator *)(local_174 + -0xc) != paVar18) {
          piVar15 = (int *)(local_174 + -4);
          DataMemoryBarrier(0x1b);
          do {
            ExclusiveAccess(piVar15);
            iVar5 = *piVar15;
            bVar1 = (bool)hasExclusiveAccess(piVar15);
          } while (!bVar1);
          *piVar15 = iVar5 + -1;
          DataMemoryBarrier(0x1b);
          iVar11 = 0;
          if (iVar5 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_174 + -0xc));
          }
        }
        if ((allocator *)(local_178 + -0xc) != paVar18) {
          piVar15 = (int *)(local_178 + -4);
          DataMemoryBarrier(0x1b);
          do {
            ExclusiveAccess(piVar15);
            iVar5 = *piVar15;
            bVar1 = (bool)hasExclusiveAccess(piVar15);
          } while (!bVar1);
          *piVar15 = iVar5 + -1;
          DataMemoryBarrier(0x1b);
          iVar11 = 0;
          if (iVar5 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_178 + -0xc));
            iVar11 = 0;
          }
        }
        if ((allocator *)(local_17c + -0xc) != paVar18) {
          piVar15 = (int *)(local_17c + -4);
          DataMemoryBarrier(0x1b);
          do {
            ExclusiveAccess(piVar15);
            iVar5 = *piVar15;
            bVar1 = (bool)hasExclusiveAccess(piVar15);
          } while (!bVar1);
          *piVar15 = iVar5 + -1;
          DataMemoryBarrier(0x1b);
          iVar11 = 0;
          if (iVar5 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_17c + -0xc));
          }
        }
        if ((allocator *)(local_180 + -0xc) != paVar18) {
          piVar15 = (int *)(local_180 + -4);
          DataMemoryBarrier(0x1b);
          do {
            ExclusiveAccess(piVar15);
            iVar5 = *piVar15;
            bVar1 = (bool)hasExclusiveAccess(piVar15);
          } while (!bVar1);
          *piVar15 = iVar5 + -1;
          DataMemoryBarrier(0x1b);
          iVar11 = 0;
          if (iVar5 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_180 + -0xc));
          }
        }
      }
    } while( true );
  }
LAB_00017ea2:
  uVar19 = get_cur_time_ms();
  __printf_chk(1,"%llu,wdog,#11522`%s\n",(int)uVar19,(int)((ulonglong)uVar19 >> 0x20),
               *(undefined4 *)path_string);
  fflush(stdout);
                    /* WARNING: Subroutine does not return */
  exit(0);
LAB_00017e6a:
  std::__throw_bad_cast();
  if ((allocator *)(local_184 + -0xc) != paVar18) {
    FUN_00013edc((allocator *)(local_184 + -0xc),&local_160);
  }
  std::ifstream::~ifstream((ifstream *)local_144);
  __cxa_end_cleanup();
  std::filebuf::~filebuf((filebuf *)local_13c);
  *(undefined **)((istream *)local_144 + *(int *)(iVar11 + -0xc)) = &DAT_000206c8;
  local_b4[0] = DAT_00017f64;
  std::ios_base::~ios_base((ios_base *)local_b4);
  __cxa_end_cleanup();
  path_string = (undefined4 *)0x0;
  goto LAB_00017ea2;
}

