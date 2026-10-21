/* Decompiled C, NOT recovered source; need not compile.
 * Binary: WatchDoge
 * SHA256: 3f9f2f14202434336803f975dddd6221d51ea3a14b5c5b169f50d2dc850311b6
 * Function VA: 0x00018bfc
 */

/* WARNING: Removing unreachable block (ram,0x00019098) */
/* WARNING: Removing unreachable block (ram,0x000190a4) */
/* WARNING: Removing unreachable block (ram,0x000190b0) */
/* WARNING: Removing unreachable block (ram,0x0001908c) */
/* WARNING: Removing unreachable block (ram,0x0001910a) */
/* WARNING: Removing unreachable block (ram,0x000190bc) */
/* WARNING: Heritage AFTER dead removal. Example location: r0 : 0x00018f54 */
/* WARNING: Restarted to delay deadcode elimination for space: register */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Polls opening /proc/<pid>/status, sleeping one second while present; returns 1 when fopen fails,
   0 when attempts reaches zero. Does not distinguish ENOENT from other open failures, reap zombies,
   wait for children, or flush files. Negative attempt values are not validated here. */

int WdogWaitProcGone(void *supervisor,int pid,int attempts)

{
  bool bVar1;
  undefined4 uVar2;
  char *pcVar3;
  ostream *poVar4;
  allocator *paVar5;
  FILE *__stream;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  char *local_f4;
  char *local_f0;
  char *local_ec;
  int local_e8 [2];
  int local_e0 [8];
  locale alStack_c0 [4];
  undefined4 local_bc;
  char *local_b8;
  int local_b4 [28];
  undefined4 local_44;
  undefined1 local_40;
  undefined1 local_3f;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  int local_2c;
  
  local_2c = __stack_chk_guard;
  uVar2 = std::stringstream::VTT._12_4_;
  iVar8 = std::stringstream::VTT._8_4_;
  do {
    if (attempts == 0) {
      iVar8 = 0;
LAB_000190ca:
      if (local_2c == __stack_chk_guard) {
        return iVar8;
      }
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail();
    }
    std::ios_base::ios_base((ios_base *)local_b4);
    local_40 = 0;
    local_b4[0] = DAT_00018f34;
    local_44 = 0;
    local_3f = 0;
    local_3c = 0;
    local_38 = 0;
    local_34 = 0;
    local_30 = 0;
    local_e8[0] = iVar8;
    *(undefined4 *)((int)local_e8 + *(int *)(iVar8 + -0xc)) = uVar2;
    local_e8[1] = 0;
    std::ios::init((streambuf *)((int)local_e8 + *(int *)(iVar8 + -0xc)));
    iVar8 = *(int *)(std::stringstream::VTT._16_4_ + -0xc);
    local_e0[0] = std::stringstream::VTT._16_4_;
    *(undefined4 *)((ostream *)local_e0 + iVar8) = std::stringstream::VTT._20_4_;
    std::ios::init((streambuf *)((ostream *)local_e0 + iVar8));
    pcVar3 = DAT_00018f48;
    uVar2 = DAT_00018f44;
    iVar8 = DAT_00018f38;
    *(undefined4 *)((int)local_e8 + *(int *)(std::stringstream::VTT._4_4_ + -0xc)) =
         std::stringstream::VTT._24_4_;
    local_e8[0] = DAT_00018f38 + -0x14;
    local_b4[0] = DAT_00018f38 + 0x14;
    local_e0[2] = 0;
    local_e0[3] = 0;
    local_e0[4] = 0;
    local_e0[5] = 0;
    local_e0[6] = 0;
    local_e0[7] = 0;
    local_e0[1] = DAT_00018f3c;
    local_e0[0] = DAT_00018f38;
    std::locale::locale(alStack_c0);
    local_e0[1] = uVar2;
    local_b8 = pcVar3;
    local_bc = 0x18;
    std::ios::init((streambuf *)local_b4);
    std::__ostream_insert<char,std::char_traits<char>>((ostream *)local_e0,"/proc",5);
    std::__ostream_insert<char,std::char_traits<char>>((ostream *)local_e0,"/",1);
    poVar4 = (ostream *)std::ostream::operator<<((ostream *)local_e0,pid);
    std::__ostream_insert<char,std::char_traits<char>>(poVar4,"/",1);
    std::__ostream_insert<char,std::char_traits<char>>(poVar4,"status",6);
    local_f4 = pcVar3;
    if (local_e0[6] == 0) {
      std::string::assign((string *)&local_f4);
LAB_00018d6c:
      paVar5 = (allocator *)(local_f4 + -0xc);
      if (paVar5 == (allocator *)std::string::_Rep::_S_empty_rep_storage) goto LAB_00018d78;
LAB_00018fba:
      piVar10 = (int *)(local_f4 + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar10);
        iVar6 = *piVar10;
        bVar1 = (bool)hasExclusiveAccess(piVar10);
      } while (!bVar1);
      *piVar10 = iVar6 + -1;
      DataMemoryBarrier(0x1b);
      if (0 < iVar6) goto LAB_00018d78;
      std::string::_Rep::_M_destroy(paVar5);
      if (local_e0[6] == 0) goto LAB_00018ff8;
LAB_00018d84:
      local_f0 = pcVar3;
      if ((uint)local_e0[4] < (uint)local_e0[6]) {
        local_ec = std::string::_S_construct<char*>(paVar5,local_e0[6],&local_f4,0);
        std::string::swap((string *)&local_f0);
        paVar5 = (allocator *)(local_ec + -0xc);
        if (paVar5 != (allocator *)std::string::_Rep::_S_empty_rep_storage) {
          piVar10 = (int *)(local_ec + -4);
          DataMemoryBarrier(0x1b);
          do {
            ExclusiveAccess(piVar10);
            iVar6 = *piVar10;
            bVar1 = (bool)hasExclusiveAccess(piVar10);
          } while (!bVar1);
          *piVar10 = iVar6 + -1;
LAB_00018f22:
          DataMemoryBarrier(0x1b);
          if (iVar6 < 1) {
            std::string::_Rep::_M_destroy(paVar5);
          }
        }
      }
      else {
        local_ec = std::string::_S_construct<char*>(paVar5,local_e0[4],&local_f4,0);
        std::string::swap((string *)&local_f0);
        paVar5 = (allocator *)(local_ec + -0xc);
        if (paVar5 != (allocator *)std::string::_Rep::_S_empty_rep_storage) {
          piVar10 = (int *)(local_ec + -4);
          DataMemoryBarrier(0x1b);
          do {
            ExclusiveAccess(piVar10);
            iVar6 = *piVar10;
            bVar1 = (bool)hasExclusiveAccess(piVar10);
          } while (!bVar1);
          *piVar10 = iVar6 + -1;
          goto LAB_00018f22;
        }
      }
    }
    else {
      if ((uint)local_e0[6] <= (uint)local_e0[4]) {
        local_ec = std::string::_S_construct<char*>(poVar4,local_e0[4],&local_f0,0);
        std::string::swap((string *)&local_f4);
        paVar5 = (allocator *)(local_ec + -0xc);
        if (paVar5 != (allocator *)std::string::_Rep::_S_empty_rep_storage) {
          piVar10 = (int *)(local_ec + -4);
          DataMemoryBarrier(0x1b);
          do {
            ExclusiveAccess(piVar10);
            iVar6 = *piVar10;
            bVar1 = (bool)hasExclusiveAccess(piVar10);
          } while (!bVar1);
          *piVar10 = iVar6 + -1;
          goto LAB_00018f9e;
        }
        goto LAB_00018d6c;
      }
      local_ec = std::string::_S_construct<char*>(poVar4,local_e0[6],&local_f0,0);
      std::string::swap((string *)&local_f4);
      paVar5 = (allocator *)(local_ec + -0xc);
      if (paVar5 == (allocator *)std::string::_Rep::_S_empty_rep_storage) goto LAB_00018d6c;
      piVar10 = (int *)(local_ec + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar10);
        iVar6 = *piVar10;
        bVar1 = (bool)hasExclusiveAccess(piVar10);
      } while (!bVar1);
      *piVar10 = iVar6 + -1;
LAB_00018f9e:
      DataMemoryBarrier(0x1b);
      if (0 < iVar6) goto LAB_00018d6c;
      std::string::_Rep::_M_destroy(paVar5);
      paVar5 = (allocator *)(local_f4 + -0xc);
      if (paVar5 != (allocator *)std::string::_Rep::_S_empty_rep_storage) goto LAB_00018fba;
LAB_00018d78:
      if (local_e0[6] != 0) goto LAB_00018d84;
LAB_00018ff8:
      local_f0 = pcVar3;
      std::string::assign((string *)&local_f0);
    }
    __stream = fopen(local_f0,"r");
    iVar9 = DAT_00018f40;
    iVar6 = local_e8[0];
    if ((allocator *)(local_f0 + -0xc) != (allocator *)std::string::_Rep::_S_empty_rep_storage) {
      piVar10 = (int *)(local_f0 + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar10);
        iVar7 = *piVar10;
        bVar1 = (bool)hasExclusiveAccess(piVar10);
      } while (!bVar1);
      *piVar10 = iVar7 + -1;
      DataMemoryBarrier(0x1b);
      iVar9 = DAT_00018f40;
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_f0 + -0xc));
        iVar9 = DAT_00018f40;
        iVar6 = local_e8[0];
      }
    }
    local_e8[0] = iVar9;
    DAT_00018f40 = local_e8[0];
    if (__stream == (FILE *)0x0) {
      local_e0[0] = iVar8;
      local_e0[1] = uVar2;
      local_b4[0] = local_e8[0] + 0x28;
      if ((allocator *)(local_b8 + -0xc) != (allocator *)std::string::_Rep::_S_empty_rep_storage) {
        piVar10 = (int *)(local_b8 + -4);
        DataMemoryBarrier(0x1b);
        do {
          ExclusiveAccess(piVar10);
          iVar8 = *piVar10;
          bVar1 = (bool)hasExclusiveAccess(piVar10);
        } while (!bVar1);
        *piVar10 = iVar8 + -1;
        DataMemoryBarrier(0x1b);
        if (iVar8 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_b8 + -0xc));
        }
      }
      local_e0[1] = DAT_00018f3c;
      std::locale::~locale(alStack_c0);
      iVar8 = *(int *)(std::stringstream::VTT._16_4_ + -0xc);
      iVar6 = *(int *)(std::stringstream::VTT._8_4_ + -0xc);
      *(undefined4 *)((int)local_e8 + *(int *)(std::stringstream::VTT._4_4_ + -0xc)) =
           std::stringstream::VTT._24_4_;
      *(undefined4 *)((int)local_e0 + iVar8) = std::stringstream::VTT._20_4_;
      *(undefined4 *)((int)local_e8 + iVar6) = std::stringstream::VTT._12_4_;
      local_b4[0] = DAT_00018f34;
      std::ios_base::~ios_base((ios_base *)local_b4);
      iVar8 = 1;
      goto LAB_000190ca;
    }
    local_e8[0] = iVar6;
    sleep(1);
    fclose(__stream);
    local_e0[0] = iVar8;
    local_e0[1] = uVar2;
    local_e8[0] = DAT_00018f40;
    local_b4[0] = DAT_00018f40 + 0x28;
    if ((allocator *)(local_b8 + -0xc) != (allocator *)std::string::_Rep::_S_empty_rep_storage) {
      piVar10 = (int *)(local_b8 + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar10);
        iVar8 = *piVar10;
        bVar1 = (bool)hasExclusiveAccess(piVar10);
      } while (!bVar1);
      *piVar10 = iVar8 + -1;
      DataMemoryBarrier(0x1b);
      if (iVar8 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_b8 + -0xc));
      }
    }
    local_e0[1] = DAT_00018f3c;
    std::locale::~locale(alStack_c0);
    uVar2 = std::stringstream::VTT._12_4_;
    iVar8 = std::stringstream::VTT._8_4_;
    iVar6 = *(int *)(std::stringstream::VTT._16_4_ + -0xc);
    iVar9 = *(int *)(std::stringstream::VTT._8_4_ + -0xc);
    *(undefined4 *)((int)local_e8 + *(int *)(std::stringstream::VTT._4_4_ + -0xc)) =
         std::stringstream::VTT._24_4_;
    *(undefined4 *)((int)local_e0 + iVar6) = std::stringstream::VTT._20_4_;
    *(undefined4 *)((int)local_e8 + iVar9) = std::stringstream::VTT._12_4_;
    local_b4[0] = DAT_00018f34;
    std::ios_base::~ios_base((ios_base *)local_b4);
    attempts = attempts + -1;
  } while( true );
}

