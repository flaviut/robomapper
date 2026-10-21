/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0001cbf0
 */

/* First buffer-aware loads source flag. If successful, cancels destination tasks then opens SOURCE
   FILE and copies through binary input/output streams directly to destination files. Does not
   serialize the possibly newer source buffer; no tmp/rename transaction. Returns initial load
   result; stream-copy failures do not replace it. */

bool PersistLoadMapInfoAndSave(int source_flag,void *destination_flags_vector)

{
  bool bVar1;
  bool bVar2;
  uint destination_mask;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  undefined4 uVar8;
  int *piVar9;
  int iVar10;
  int iVar11;
  undefined4 uVar12;
  int iVar13;
  int *piVar14;
  int *piVar15;
  int iVar16;
  int iVar17;
  int *local_2b8;
  allocator *local_2ac;
  int local_26c;
  int local_268;
  int local_264;
  PersistInfoLockGuard aPStack_260 [8];
  int local_258;
  int local_254 [4];
  uint auStack_244 [3];
  locale alStack_238 [28];
  __basic_file<char> a_Stack_21c [80];
  int local_1cc [28];
  undefined4 local_15c;
  undefined1 local_158;
  undefined1 local_157;
  undefined4 local_154;
  undefined4 local_150;
  undefined4 local_14c;
  undefined4 local_148;
  int local_144 [2];
  int local_13c [3];
  uint auStack_130 [4];
  locale alStack_120 [28];
  __basic_file<char> a_Stack_104 [80];
  int local_b4 [28];
  undefined4 local_44;
  undefined1 local_40;
  undefined1 local_3f;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  int local_2c;
  
  iVar17 = DAT_0001d074 + 0x1cc0c;
  piVar9 = *(int **)(iVar17 + DAT_0001d078);
  local_2c = *piVar9;
  PersistInfoLockGuard::PersistInfoLockGuard(aPStack_260,0);
  bVar2 = PersistLoadMapInfo(source_flag);
  if (bVar2) {
    destination_mask = ConvertMapFlagMask(destination_flags_vector);
    CancelSavingTasksForMaps(destination_mask);
    GetMapInfoPersistFileName(&local_26c,source_flag);
    piVar7 = *(int **)((int)destination_flags_vector + 4);
    if (*(int **)destination_flags_vector == piVar7) {
      local_2ac = *(allocator **)(iVar17 + DAT_0001d088);
    }
    else {
      iVar6 = DAT_0001d08c + 0x1cc98;
      local_2ac = *(allocator **)(iVar17 + DAT_0001d088);
      iVar10 = DAT_0001d090 + 0x1cda8;
      local_2b8 = *(int **)destination_flags_vector;
      do {
        piVar14 = local_2b8 + 1;
        iVar16 = *local_2b8;
        if (source_flag == iVar16) {
          _rrlogm(0x15,3,0x3fa,iVar6,iVar10,DAT_0001d0b0 + 0x1ced6,source_flag);
        }
        GetMapInfoPersistFileName(&local_268,source_flag);
        std::ios_base::ios_base((ios_base *)local_b4);
        iVar3 = *(int *)(iVar17 + DAT_0001d094);
        local_40 = 0;
        local_44 = 0;
        local_b4[0] = iVar3 + 8;
        local_3f = 0;
        local_3c = 0;
        local_38 = 0;
        local_34 = 0;
        local_30 = 0;
        iVar4 = *(int *)(*(int *)(iVar17 + DAT_0001d098) + 4);
        uVar8 = *(undefined4 *)(*(int *)(iVar17 + DAT_0001d098) + 8);
        local_144[0] = iVar4;
        *(undefined4 *)((int)local_144 + *(int *)(iVar4 + -0xc)) = uVar8;
        local_144[1] = 0;
        std::ios::init((streambuf *)((int)local_144 + *(int *)(iVar4 + -0xc)));
        iVar11 = *(int *)(iVar17 + DAT_0001d09c);
        local_144[0] = iVar11 + 0xc;
        local_b4[0] = iVar11 + 0x20;
        std::filebuf::filebuf((filebuf *)local_13c);
        std::ios::init((streambuf *)local_b4);
        iVar5 = std::filebuf::open((filebuf *)local_13c,local_268,0xc);
        if (iVar5 == 0) {
          std::ios::clear((int)local_144 + *(int *)(local_144[0] + -0xc),
                          *(uint *)((int)auStack_130 + *(int *)(local_144[0] + -0xc)) | 4);
        }
        else {
          std::ios::clear((int)local_144 + *(int *)(local_144[0] + -0xc),0);
        }
        if ((allocator *)(local_268 + -0xc) != local_2ac) {
          if (*(int *)(iVar17 + DAT_0001d0b4) == 0) {
            iVar5 = *(int *)(local_268 + -4);
            *(int *)(local_268 + -4) = iVar5 + -1;
          }
          else {
            piVar15 = (int *)(local_268 + -4);
            DataMemoryBarrier(0x1b);
            do {
              ExclusiveAccess(piVar15);
              iVar5 = *piVar15;
              bVar1 = (bool)hasExclusiveAccess(piVar15);
            } while (!bVar1);
            *piVar15 = iVar5 + -1;
            DataMemoryBarrier(0x1b);
          }
          if (iVar5 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_268 + -0xc));
          }
        }
        GetMapInfoPersistFileName(&local_264,iVar16);
        std::ios_base::ios_base((ios_base *)local_1cc);
        local_1cc[0] = iVar3 + 8;
        local_158 = 0;
        local_15c = 0;
        local_157 = 0;
        local_154 = 0;
        local_150 = 0;
        local_14c = 0;
        local_148 = 0;
        iVar5 = *(int *)(*(int *)(iVar17 + DAT_0001d0a0) + 4);
        uVar12 = *(undefined4 *)(*(int *)(iVar17 + DAT_0001d0a0) + 8);
        iVar16 = *(int *)(iVar5 + -0xc);
        local_258 = iVar5;
        *(undefined4 *)((ostream *)&local_258 + iVar16) = uVar12;
        std::ios::init((streambuf *)((ostream *)&local_258 + iVar16));
        iVar13 = *(int *)(iVar17 + DAT_0001d0a4);
        local_258 = iVar13 + 0xc;
        local_1cc[0] = iVar13 + 0x20;
        std::filebuf::filebuf((filebuf *)local_254);
        std::ios::init((streambuf *)local_1cc);
        iVar16 = std::filebuf::open((filebuf *)local_254,local_264,0x14);
        if (iVar16 == 0) {
          std::ios::clear((ostream *)&local_258 + *(int *)(local_258 + -0xc),
                          *(uint *)((int)auStack_244 + *(int *)(local_258 + -0xc)) | 4);
        }
        else {
          std::ios::clear((ostream *)&local_258 + *(int *)(local_258 + -0xc),0);
        }
        if ((allocator *)(local_264 + -0xc) != local_2ac) {
          if (*(int *)(iVar17 + DAT_0001d0b4) == 0) {
            iVar16 = *(int *)(local_264 + -4);
            *(int *)(local_264 + -4) = iVar16 + -1;
          }
          else {
            piVar15 = (int *)(local_264 + -4);
            DataMemoryBarrier(0x1b);
            do {
              ExclusiveAccess(piVar15);
              iVar16 = *piVar15;
              bVar1 = (bool)hasExclusiveAccess(piVar15);
            } while (!bVar1);
            *piVar15 = iVar16 + -1;
            DataMemoryBarrier(0x1b);
          }
          if (iVar16 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_264 + -0xc));
          }
        }
        std::ostream::operator<<((ostream *)&local_258,(streambuf *)local_13c);
        local_1cc[0] = iVar13 + 0x20;
        local_258 = iVar13 + 0xc;
        iVar13 = *(int *)(iVar17 + DAT_0001d0a8) + 8;
        local_254[0] = iVar13;
        std::filebuf::close();
        std::__basic_file<char>::~__basic_file(a_Stack_21c);
        iVar16 = *(int *)(iVar17 + DAT_0001d0ac) + 8;
        local_254[0] = iVar16;
        std::locale::~locale(alStack_238);
        *(undefined4 *)((ostream *)&local_258 + *(int *)(iVar5 + -0xc)) = uVar12;
        local_1cc[0] = iVar3 + 8;
        std::ios_base::~ios_base((ios_base *)local_1cc);
        local_144[0] = iVar11 + 0xc;
        local_b4[0] = iVar11 + 0x20;
        local_13c[0] = iVar13;
        std::filebuf::close();
        std::__basic_file<char>::~__basic_file(a_Stack_104);
        local_13c[0] = iVar16;
        std::locale::~locale(alStack_120);
        *(undefined4 *)((int)local_144 + *(int *)(iVar4 + -0xc)) = uVar8;
        local_b4[0] = iVar3 + 8;
        std::ios_base::~ios_base((ios_base *)local_b4);
        local_2b8 = piVar14;
      } while (piVar7 != piVar14);
    }
    if ((allocator *)(local_26c + -0xc) != local_2ac) {
      if (*(int *)(iVar17 + DAT_0001d0b4) == 0) {
        iVar17 = *(int *)(local_26c + -4);
        *(int *)(local_26c + -4) = iVar17 + -1;
      }
      else {
        piVar7 = (int *)(local_26c + -4);
        DataMemoryBarrier(0x1b);
        do {
          ExclusiveAccess(piVar7);
          iVar17 = *piVar7;
          bVar1 = (bool)hasExclusiveAccess(piVar7);
        } while (!bVar1);
        *piVar7 = iVar17 + -1;
        DataMemoryBarrier(0x1b);
      }
      if (iVar17 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_26c + -0xc));
      }
    }
  }
  else {
    _rrlogm(0x15,3,0x3ec,DAT_0001d084 + 0x1cc4e,DAT_0001d07c + 0x1cd42,DAT_0001d080 + 0x1cc42,
            source_flag);
  }
  PersistInfoLockGuard::~PersistInfoLockGuard(aPStack_260);
  if (local_2c != *piVar9) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return bVar2;
}

