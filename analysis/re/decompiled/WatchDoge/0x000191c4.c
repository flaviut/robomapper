/* Decompiled C, NOT recovered source; need not compile.
 * Binary: WatchDoge
 * SHA256: 3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6
 * Function VA: 0x000191c4
 */

/* WARNING: Removing unreachable block (ram,0x00019804) */
/* WARNING: Removing unreachable block (ram,0x00019978) */
/* WARNING: Removing unreachable block (ram,0x00019824) */
/* WARNING: Removing unreachable block (ram,0x000198b0) */
/* WARNING: Removing unreachable block (ram,0x00019984) */
/* WARNING: Removing unreachable block (ram,0x0001983c) */
/* WARNING: Removing unreachable block (ram,0x00019830) */
/* WARNING: Removing unreachable block (ram,0x000196b6) */
/* WARNING: Heritage AFTER dead removal. Example location: r0 : 0x0001941e */
/* WARNING: Restarted to delay deadcode elimination for space: register */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* For mode 0, reads /proc/<pid>/status, parses State and PPid; non-zombie -> kill(pid,1), zombie Z
   -> kill(parsed_parent,9). Nonzero mode bypasses that signal path. Missing status/negative PID
   returns success-like result. This helper does not prove graceful writer shutdown; its boolean
   result is ignored by WdogStopProcesses. */

int WdogSignalTrackedPid(void *supervisor,int pid,int mode)

{
  char cVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  ostream *poVar8;
  allocator *paVar9;
  FILE *__stream;
  char *pcVar10;
  size_t sVar11;
  istream *piVar12;
  undefined4 uVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int *piVar17;
  uint uVar18;
  int iVar19;
  undefined8 uVar20;
  __pid_t local_5d0;
  char *local_5bc;
  char *local_5b8;
  char *local_5b4;
  char *local_5b0;
  int local_5ac;
  char *local_5a8;
  int local_5a4 [2];
  int local_59c [8];
  locale alStack_57c [4];
  undefined4 local_578;
  char *local_574;
  int local_570 [28];
  undefined4 local_500;
  undefined1 local_4fc;
  undefined1 local_4fb;
  undefined4 local_4f8;
  undefined4 local_4f4;
  undefined4 local_4f0;
  undefined4 local_4ec;
  int local_4e8 [2];
  undefined4 local_4e0;
  undefined4 local_4dc;
  undefined4 local_4d8;
  undefined4 local_4d4;
  undefined4 local_4d0;
  undefined4 local_4cc;
  undefined4 local_4c8;
  undefined4 local_4c4;
  locale alStack_4c0 [4];
  undefined4 local_4bc;
  int local_4b8;
  int local_4b4 [28];
  undefined4 local_444;
  undefined1 local_440;
  undefined1 local_43f;
  undefined4 local_43c;
  undefined4 local_438;
  undefined4 local_434;
  undefined4 local_430;
  char acStack_42c [1024];
  int local_2c;
  
  local_2c = __stack_chk_guard;
  memset(acStack_42c,0,0x400);
  if (pid < 0) {
    uVar18 = 1;
    goto LAB_000193fa;
  }
  std::ios_base::ios_base((ios_base *)local_570);
  local_4fc = 0;
  local_5a4[0] = std::stringstream::VTT._8_4_;
  local_500 = 0;
  local_4fb = 0;
  local_4f8 = 0;
  local_4f4 = 0;
  local_4f0 = 0;
  local_4ec = 0;
  local_570[0] = DAT_0001950c;
  *(undefined4 *)((int)local_5a4 + *(int *)(std::stringstream::VTT._8_4_ + -0xc)) =
       std::stringstream::VTT._12_4_;
  local_5a4[1] = 0;
  std::ios::init((streambuf *)((int)local_5a4 + *(int *)(std::stringstream::VTT._8_4_ + -0xc)));
  iVar15 = *(int *)(std::stringstream::VTT._16_4_ + -0xc);
  local_59c[0] = std::stringstream::VTT._16_4_;
  *(undefined4 *)((int)local_59c + iVar15) = std::stringstream::VTT._20_4_;
  std::ios::init((streambuf *)((int)local_59c + iVar15));
  iVar15 = DAT_00019520;
  iVar19 = DAT_00019520 + 0x28;
  *(undefined4 *)((int)local_5a4 + *(int *)(std::stringstream::VTT._4_4_ + -0xc)) =
       std::stringstream::VTT._24_4_;
  local_59c[0] = DAT_00019520 + 0x14;
  local_59c[2] = 0;
  local_59c[3] = 0;
  local_59c[1] = DAT_00019510;
  local_59c[4] = 0;
  local_59c[5] = 0;
  local_59c[6] = 0;
  local_59c[7] = 0;
  local_5a4[0] = DAT_00019520;
  local_570[0] = iVar19;
  std::locale::locale(alStack_57c);
  local_59c[1] = DAT_00019514;
  local_574 = DAT_00019518;
  local_578 = 0x18;
  std::ios::init((streambuf *)local_570);
  std::__ostream_insert<char,std::char_traits<char>>((ostream *)local_59c,"/proc",5);
  std::__ostream_insert<char,std::char_traits<char>>((ostream *)local_59c,"/",1);
  poVar8 = (ostream *)std::ostream::operator<<((ostream *)local_59c,pid);
  std::__ostream_insert<char,std::char_traits<char>>(poVar8,"/",1);
  std::__ostream_insert<char,std::char_traits<char>>(poVar8,"status",6);
  local_5bc = DAT_00019518;
  if (local_59c[6] == 0) {
    std::string::assign((string *)&local_5bc);
  }
  else if ((uint)local_59c[4] < (uint)local_59c[6]) {
    local_5a8 = std::string::_S_construct<char*>(poVar8,local_59c[6],&local_5ac,0);
    std::string::swap((string *)&local_5bc);
    paVar9 = (allocator *)(local_5a8 + -0xc);
    if (paVar9 != (allocator *)std::string::_Rep::_S_empty_rep_storage) {
      piVar17 = (int *)(local_5a8 + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar17);
        iVar14 = *piVar17;
        bVar2 = (bool)hasExclusiveAccess(piVar17);
      } while (!bVar2);
      *piVar17 = iVar14 + -1;
      goto LAB_00019464;
    }
  }
  else {
    local_5a8 = std::string::_S_construct<char*>(poVar8,local_59c[4],&local_5ac,0);
    std::string::swap((string *)&local_5bc);
    paVar9 = (allocator *)(local_5a8 + -0xc);
    if (paVar9 != (allocator *)std::string::_Rep::_S_empty_rep_storage) {
      piVar17 = (int *)(local_5a8 + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar17);
        iVar14 = *piVar17;
        bVar2 = (bool)hasExclusiveAccess(piVar17);
      } while (!bVar2);
      *piVar17 = iVar14 + -1;
LAB_00019464:
      DataMemoryBarrier(0x1b);
      if (iVar14 < 1) {
        std::string::_Rep::_M_destroy(paVar9);
      }
    }
  }
  paVar9 = (allocator *)(local_5bc + -0xc);
  if (paVar9 != (allocator *)std::string::_Rep::_S_empty_rep_storage) {
    piVar17 = (int *)(local_5bc + -4);
    DataMemoryBarrier(0x1b);
    do {
      ExclusiveAccess(piVar17);
      iVar14 = *piVar17;
      bVar2 = (bool)hasExclusiveAccess(piVar17);
    } while (!bVar2);
    *piVar17 = iVar14 + -1;
    DataMemoryBarrier(0x1b);
    if (iVar14 < 1) {
      std::string::_Rep::_M_destroy(paVar9);
    }
  }
  uVar18 = 1;
  local_5b8 = DAT_00019518;
  local_5b4 = DAT_00019518;
  if (mode == 0) {
    local_5b0 = DAT_00019518;
    if (local_59c[6] == 0) {
      std::string::assign((string *)&local_5b0);
    }
    else if ((uint)local_59c[4] < (uint)local_59c[6]) {
      local_5a8 = std::string::_S_construct<char*>(paVar9,local_59c[6],&local_5ac,0);
      std::string::swap((string *)&local_5b0);
      paVar9 = (allocator *)(local_5a8 + -0xc);
      if (paVar9 != (allocator *)std::string::_Rep::_S_empty_rep_storage) {
        piVar17 = (int *)(local_5a8 + -4);
        DataMemoryBarrier(0x1b);
        do {
          ExclusiveAccess(piVar17);
          iVar14 = *piVar17;
          bVar2 = (bool)hasExclusiveAccess(piVar17);
        } while (!bVar2);
        *piVar17 = iVar14 + -1;
LAB_0001972e:
        DataMemoryBarrier(0x1b);
        if (iVar14 < 1) {
          std::string::_Rep::_M_destroy(paVar9);
        }
      }
    }
    else {
      local_5a8 = std::string::_S_construct<char*>(paVar9,local_59c[4],&local_5ac,0);
      std::string::swap((string *)&local_5b0);
      paVar9 = (allocator *)(local_5a8 + -0xc);
      if (paVar9 != (allocator *)std::string::_Rep::_S_empty_rep_storage) {
        piVar17 = (int *)(local_5a8 + -4);
        DataMemoryBarrier(0x1b);
        do {
          ExclusiveAccess(piVar17);
          iVar14 = *piVar17;
          bVar2 = (bool)hasExclusiveAccess(piVar17);
        } while (!bVar2);
        *piVar17 = iVar14 + -1;
        goto LAB_0001972e;
      }
    }
    __stream = fopen(local_5b0,"r");
    if ((allocator *)(local_5b0 + -0xc) != (allocator *)std::string::_Rep::_S_empty_rep_storage) {
      piVar17 = (int *)(local_5b0 + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar17);
        iVar14 = *piVar17;
        bVar2 = (bool)hasExclusiveAccess(piVar17);
      } while (!bVar2);
      *piVar17 = iVar14 + -1;
      DataMemoryBarrier(0x1b);
      if (iVar14 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_5b0 + -0xc));
      }
    }
    if (__stream == (FILE *)0x0) {
      uVar20 = get_cur_time_ms();
      uVar13 = (undefined4)uVar20;
      local_5ac = DAT_00019ad8;
      if (local_59c[6] == 0) {
        std::string::assign((string *)&local_5ac);
      }
      else {
        if ((uint)local_59c[4] < (uint)local_59c[6]) {
          local_5a8 = std::string::_S_construct<char*>(uVar13,local_59c[6],&local_5b0,0);
          std::string::swap((string *)&local_5ac);
        }
        else {
          local_5a8 = std::string::_S_construct<char*>(uVar13,local_59c[4],&local_5b0,0);
          std::string::swap((string *)&local_5ac);
        }
        if (local_5a8 + -0xc != std::string::_Rep::_S_empty_rep_storage) {
          FUN_00013edc(local_5a8 + -0xc,&local_5bc);
        }
      }
      __printf_chk(1,"%llu,wdog,#11531`%s\n",uVar13,(int)((ulonglong)uVar20 >> 0x20));
      if ((undefined1 *)(local_5ac + -0xc) != std::string::_Rep::_S_empty_rep_storage) {
        FUN_00013edc((undefined1 *)(local_5ac + -0xc),&local_5a8);
      }
      fflush(stdout);
      uVar18 = 1;
    }
    else {
      local_5d0 = -1;
      cVar1 = 'R';
      while (pcVar10 = fgets(acStack_42c,0x400,__stream), pcVar10 != (char *)0x0) {
        std::ios_base::ios_base((ios_base *)local_4b4);
        uVar4 = std::stringstream::VTT._12_4_;
        uVar3 = std::stringstream::VTT._8_4_;
        local_440 = 0;
        local_4b4[0] = DAT_0001981c;
        local_444 = 0;
        local_43f = 0;
        local_43c = 0;
        local_438 = 0;
        local_434 = 0;
        local_430 = 0;
        local_4e8[0] = std::stringstream::VTT._8_4_;
        *(undefined4 *)((istream *)local_4e8 + *(int *)(std::stringstream::VTT._8_4_ + -0xc)) =
             std::stringstream::VTT._12_4_;
        local_4e8[1] = 0;
        std::ios::init((streambuf *)
                       ((istream *)local_4e8 + *(int *)(std::stringstream::VTT._8_4_ + -0xc)));
        uVar6 = std::stringstream::VTT._20_4_;
        uVar5 = std::stringstream::VTT._16_4_;
        iVar14 = *(int *)(std::stringstream::VTT._16_4_ + -0xc);
        local_4e0 = std::stringstream::VTT._16_4_;
        *(undefined4 *)((ostream *)&local_4e0 + iVar14) = std::stringstream::VTT._20_4_;
        std::ios::init((streambuf *)((ostream *)&local_4e0 + iVar14));
        uVar7 = std::stringstream::VTT._24_4_;
        uVar13 = std::stringstream::VTT._4_4_;
        *(undefined4 *)((istream *)local_4e8 + *(int *)(std::stringstream::VTT._4_4_ + -0xc)) =
             std::stringstream::VTT._24_4_;
        local_4d8 = 0;
        local_4d4 = 0;
        local_4e0 = DAT_00019810;
        local_4d0 = 0;
        local_4cc = 0;
        local_4dc = DAT_00019818;
        local_4c8 = 0;
        local_4c4 = 0;
        local_4e8[0] = iVar15;
        local_4b4[0] = iVar19;
        std::locale::locale(alStack_4c0);
        local_4dc = DAT_00019814;
        local_4b8 = DAT_00019820;
        local_4bc = 0x18;
        std::ios::init((streambuf *)local_4b4);
        sVar11 = strlen(acStack_42c);
        std::__ostream_insert<char,std::char_traits<char>>((ostream *)&local_4e0,acStack_42c,sVar11)
        ;
        piVar12 = std::operator>>((istream *)local_4e8,(string *)&local_5b8);
        std::operator>>(piVar12,(string *)&local_5b4);
        iVar14 = std::string::compare((char *)&local_5b8);
        if (iVar14 == 0) {
          if (-1 < *(int *)(local_5b4 + -4)) {
            std::string::_M_leak_hard();
          }
          cVar1 = *local_5b4;
        }
        iVar14 = std::string::compare((char *)&local_5b8);
        if (iVar14 == 0) {
          local_5d0 = strtol(local_5b4,(char **)0x0,10);
        }
        local_4e8[0] = iVar15;
        local_4e0 = DAT_00019810;
        local_4dc = DAT_00019814;
        local_4b4[0] = iVar19;
        if ((allocator *)(local_4b8 + -0xc) != (allocator *)std::string::_Rep::_S_empty_rep_storage)
        {
          piVar17 = (int *)(local_4b8 + -4);
          DataMemoryBarrier(0x1b);
          do {
            ExclusiveAccess(piVar17);
            iVar14 = *piVar17;
            bVar2 = (bool)hasExclusiveAccess(piVar17);
          } while (!bVar2);
          *piVar17 = iVar14 + -1;
          DataMemoryBarrier(0x1b);
          if (iVar14 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_4b8 + -0xc));
          }
        }
        local_4dc = DAT_00019818;
        std::locale::~locale(alStack_4c0);
        iVar14 = *(int *)(uVar5 + -0xc);
        iVar16 = *(int *)(uVar3 + -0xc);
        *(undefined4 *)((istream *)local_4e8 + *(int *)(uVar13 + -0xc)) = uVar7;
        *(undefined4 *)((ostream *)&local_4e0 + iVar14) = uVar6;
        *(undefined4 *)((istream *)local_4e8 + iVar16) = uVar4;
        local_4b4[0] = DAT_0001981c;
        std::ios_base::~ios_base((ios_base *)local_4b4);
      }
      fclose(__stream);
      if (cVar1 == 'Z') {
        iVar14 = 9;
      }
      else {
        iVar14 = 1;
        local_5d0 = pid;
      }
      iVar14 = kill(local_5d0,iVar14);
      uVar18 = (uint)(iVar14 == 0);
    }
  }
  if ((allocator *)(local_5b4 + -0xc) != (allocator *)std::string::_Rep::_S_empty_rep_storage) {
    piVar17 = (int *)(local_5b4 + -4);
    DataMemoryBarrier(0x1b);
    do {
      ExclusiveAccess(piVar17);
      iVar14 = *piVar17;
      bVar2 = (bool)hasExclusiveAccess(piVar17);
    } while (!bVar2);
    *piVar17 = iVar14 + -1;
    DataMemoryBarrier(0x1b);
    if (iVar14 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_5b4 + -0xc));
    }
  }
  if ((allocator *)(local_5b8 + -0xc) != (allocator *)std::string::_Rep::_S_empty_rep_storage) {
    piVar17 = (int *)(local_5b8 + -4);
    DataMemoryBarrier(0x1b);
    do {
      ExclusiveAccess(piVar17);
      iVar14 = *piVar17;
      bVar2 = (bool)hasExclusiveAccess(piVar17);
    } while (!bVar2);
    *piVar17 = iVar14 + -1;
    DataMemoryBarrier(0x1b);
    if (iVar14 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_5b8 + -0xc));
    }
  }
  local_5a4[0] = iVar15;
  local_59c[0] = DAT_0001951c;
  local_59c[1] = DAT_00019514;
  local_570[0] = iVar19;
  if ((allocator *)(local_574 + -0xc) != (allocator *)std::string::_Rep::_S_empty_rep_storage) {
    piVar17 = (int *)(local_574 + -4);
    DataMemoryBarrier(0x1b);
    do {
      ExclusiveAccess(piVar17);
      iVar15 = *piVar17;
      bVar2 = (bool)hasExclusiveAccess(piVar17);
    } while (!bVar2);
    *piVar17 = iVar15 + -1;
    DataMemoryBarrier(0x1b);
    if (iVar15 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_574 + -0xc));
    }
  }
  local_59c[1] = DAT_00019510;
  std::locale::~locale(alStack_57c);
  iVar19 = *(int *)(std::stringstream::VTT._16_4_ + -0xc);
  iVar15 = *(int *)(std::stringstream::VTT._8_4_ + -0xc);
  *(undefined4 *)((int)local_5a4 + *(int *)(std::stringstream::VTT._4_4_ + -0xc)) =
       std::stringstream::VTT._24_4_;
  *(undefined4 *)((int)local_59c + iVar19) = std::stringstream::VTT._20_4_;
  *(undefined4 *)((int)local_5a4 + iVar15) = std::stringstream::VTT._12_4_;
  local_570[0] = DAT_0001950c;
  std::ios_base::~ios_base((ios_base *)local_570);
LAB_000193fa:
  if (local_2c != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar18;
}

