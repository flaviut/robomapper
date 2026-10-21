/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x000185c0
 */

/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* ABI boolean result is not a durability/completion acknowledgment. type==0 parses a flag from
   filename and delegates to asynchronous PersistSaveMapInfo. Nonzero types use synchronous protobuf
   encoding, join compression workers and write DIRECTLY to filename (binary output, no tmp/rename
   here). No subscriptions returns true without a write. SerializeToOstream result is ignored;
   open/close failure only changes stream state and can still return true. compress controls zlib;
   encrypt is recorded, not acted upon in this path. */

bool PersistSave(int persistence_type,char *filename)

{
  bool bVar1;
  void *pvVar2;
  uint uVar3;
  uint uVar4;
  allocator *paVar5;
  bool bVar6;
  ushort *puVar7;
  int iVar8;
  undefined4 uVar9;
  uint length;
  PersistRegionInfo *this;
  uint uVar10;
  _Sp_counted_ptr_inplace<std::thread::_Impl<std::_Bind_simple<void(*(void_const*,unsigned_int,unsigned_int,std::reference_wrapper<std::string>))(void_const*,unsigned_int,unsigned_int,std::string&)>>,std::allocator<std::thread::_Impl<std::_Bind_simple<void(*(void_const*,unsigned_int,unsigned_int,std::reference_wrapper<std::string>))(void_const*,unsigned_int,unsigned_int,std::string&)>>>,(__gnu_cxx::_Lock_policy)2>
  *p_Var11;
  undefined4 uVar12;
  char *pcVar13;
  undefined4 *puVar14;
  PersistInfo *this_00;
  int iVar15;
  uint uVar16;
  int iVar17;
  int *piVar18;
  int iVar19;
  _Sp_counted_ptr_inplace<std::thread::_Impl<std::_Bind_simple<void(*(void_const*,unsigned_int,unsigned_int,std::reference_wrapper<std::string>))(void_const*,unsigned_int,unsigned_int,std::string&)>>,std::allocator<std::thread::_Impl<std::_Bind_simple<void(*(void_const*,unsigned_int,unsigned_int,std::reference_wrapper<std::string>))(void_const*,unsigned_int,unsigned_int,std::string&)>>>,(__gnu_cxx::_Lock_policy)2>
  *p_Var20;
  uint uVar21;
  undefined4 uVar22;
  int *piVar23;
  allocator *paVar24;
  int extraout_r3;
  int iVar25;
  uint uVar26;
  allocator *paVar27;
  type_info *ptVar28;
  int iVar29;
  int iVar30;
  int iVar31;
  byte bStack0000008c;
  uint local_228;
  uint local_21c;
  ushort *local_1e8;
  allocator *local_1dc;
  uint local_1d4;
  allocator *local_1d0;
  allocator *local_1c4;
  allocator *local_1b8;
  void *local_1a8;
  uint local_1a4;
  uint local_1a0;
  allocator *local_19c;
  SharedRegionLockGuard aSStack_198 [8];
  undefined4 local_190;
  _Sp_counted_ptr_inplace<std::thread::_Impl<std::_Bind_simple<void(*(void_const*,unsigned_int,unsigned_int,std::reference_wrapper<std::string>))(void_const*,unsigned_int,unsigned_int,std::string&)>>,std::allocator<std::thread::_Impl<std::_Bind_simple<void(*(void_const*,unsigned_int,unsigned_int,std::reference_wrapper<std::string>))(void_const*,unsigned_int,unsigned_int,std::string&)>>>,(__gnu_cxx::_Lock_policy)2>
  *local_18c;
  allocator *local_188;
  allocator *local_184;
  allocator *local_180;
  allocator *local_17c [5];
  int *local_168;
  type_info *local_164;
  type_info *local_160;
  int local_15c;
  uint local_158;
  uint *local_154;
  PersistInfo *local_150;
  int local_148;
  undefined4 local_144;
  int local_140;
  int local_13c;
  undefined4 local_138;
  uint auStack_134 [5];
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
  
  iVar31 = iRam00019190 + 0x185d4;
  piVar18 = *(int **)(iVar31 + iRam00019194);
  local_2c = *piVar18;
  if (persistence_type == 0) {
    _rrlogm(0x15,3,0x176,iRam000191a0 + 0x18600,iRam00019198 + 0x18730,iRam0001919c + 0x185fa);
    std::string::string((string *)local_17c,filename,(allocator *)&local_190);
    local_148 = FUN_00017898((string *)local_17c);
    local_168 = (int *)0x0;
    local_164 = (type_info *)0x0;
    local_160 = (type_info *)0x0;
    local_168 = operator_new(4);
    local_164 = (type_info *)(local_168 + 1);
    *local_168 = local_148;
    local_160 = local_164;
    bVar6 = PersistSaveMapInfo(&local_168);
    if (local_168 != (int *)0x0) {
      operator_delete(local_168);
    }
    if (local_17c[0] + -0xc != *(allocator **)(iVar31 + iRam000191a4)) {
      if (*(int *)(iVar31 + iRam000191dc) == 0) {
        iVar31 = *(int *)(local_17c[0] + -4);
        *(int *)(local_17c[0] + -4) = iVar31 + -1;
      }
      else {
        paVar24 = local_17c[0] + -4;
        DataMemoryBarrier(0x1b);
        do {
          ExclusiveAccess(paVar24);
          iVar31 = *(int *)paVar24;
          bVar1 = (bool)hasExclusiveAccess(paVar24);
        } while (!bVar1);
        *(int *)paVar24 = iVar31 + -1;
        DataMemoryBarrier(0x1b);
      }
      if (iVar31 < 1) {
        std::string::_Rep::_M_destroy(local_17c[0] + -0xc);
      }
    }
  }
  else {
    puVar7 = LockPersistInfo(persistence_type);
    if (puVar7 == (ushort *)0x0) {
      _rrlogm(0x15,3,0x17e,iRam00019228 + 0x19024,&UNK_00019154 + iRam00019220,
              iRam00019224 + 0x1901e);
      bVar6 = false;
    }
    else if (*(int *)(puVar7 + 0x16) == 0) {
      bVar6 = true;
      _rrlogm(0x15,4,0x183,iRam0001921c + 0x18fce,&UNK_000190fe + iRam00019214,
              iRam00019218 + 0x18fc8);
    }
    else {
      iVar8 = get_cur_time_ms();
      _rrlogm(0x15,6,0x189,iRam000191b4 + 0x186dc,iRam000191b0 + 0x18806,iRam000191a8 + 0x186b2,
              *(undefined4 *)(iRam000191ac + 0x186ba),filename,*(undefined4 *)(puVar7 + 0x16));
      CheckPersistInfoOwner(persistence_type);
      robopersist::PersistData::PersistData((PersistData *)&local_168);
      this_00 = local_150;
      if (local_150 == (PersistInfo *)0x0) {
        this_00 = operator_new(0x14);
        robopersist::PersistInfo::PersistInfo(this_00);
      }
      *(uint *)(this_00 + 0xc) = (uint)*puVar7;
      std::string::string((string *)&local_188,(char *)(puVar7 + 1),(allocator *)&local_190);
      if (*(string **)(this_00 + 8) == *(string **)(iVar31 + iRam000191b8)) {
        puVar14 = operator_new(4);
        iVar15 = iRam000191a4;
        *puVar14 = local_188;
        local_1d0 = *(allocator **)(iVar31 + iVar15);
        local_188 = local_1d0 + 0xc;
        *(undefined4 **)(this_00 + 8) = puVar14;
      }
      else {
        std::string::swap(*(string **)(this_00 + 8));
        local_1d0 = *(allocator **)(iVar31 + iRam000191a4);
      }
      if (local_188 + -0xc != local_1d0) {
        paVar24 = local_188 + -4;
        if (*(int *)(iVar31 + iRam000191dc) == 0) {
          iVar15 = *(int *)(local_188 + -4);
          *(int *)(local_188 + -4) = iVar15 + -1;
        }
        else {
          DataMemoryBarrier(0x1b);
          do {
            ExclusiveAccess(paVar24);
            iVar15 = *(int *)paVar24;
            bVar6 = (bool)hasExclusiveAccess(paVar24);
          } while (!bVar6);
          *(int *)paVar24 = iVar15 + -1;
          DataMemoryBarrier(0x1b);
        }
        if (iVar15 < 1) {
          std::string::_Rep::_M_destroy(local_188 + -0xc);
        }
      }
      if (*(int *)(puVar7 + 0x16) != 0) {
        iVar19 = iRam000191bc + 0x18888;
        iVar15 = iRam000191c0 + 0x1875e;
        local_1d4 = 0;
        local_1e8 = puVar7;
        do {
          uVar9 = *(undefined4 *)(local_1e8 + 0x18);
          local_144 = *(undefined4 *)(local_1e8 + 0x1a);
          local_140 = *(int *)(local_1e8 + 0x1c);
          local_13c = *(int *)(local_1e8 + 0x1e);
          local_138 = *(undefined4 *)(local_1e8 + 0x20);
          auStack_134[0] = *(uint *)(local_1e8 + 0x22);
          auStack_134[1] = *(uint *)(local_1e8 + 0x24);
          auStack_134[2] = *(uint *)(local_1e8 + 0x26);
          auStack_134[3] = *(uint *)(local_1e8 + 0x28);
          SharedRegionLockGuard::SharedRegionLockGuard(aSStack_198,persistence_type,uVar9);
          RunPersistSharedRegionCallback(&local_148,2);
          length = GetSharedRegionSize(uVar9);
          local_1a8 = (void *)GetSharedRegion(uVar9,length);
          if (local_154 == (uint *)0x0) {
LAB_00018e34:
            google::protobuf::internal::RepeatedPtrFieldBase::Reserve((int)&local_160);
            uVar16 = *local_154;
LAB_000187ca:
            ptVar28 = local_160;
            *local_154 = uVar16 + 1;
            if (local_160 == (type_info *)0x0) {
              this = operator_new(0x38);
              robopersist::PersistRegionInfo::PersistRegionInfo(this);
            }
            else {
              if (*(int *)(local_160 + 0x40) != 0) {
                google::protobuf::Arena::OnArenaAllocation
                          (local_160,*(uint *)(iVar31 + iRam00019210));
              }
              this = (PersistRegionInfo *)
                     google::protobuf::internal::ArenaImpl::AllocateAlignedAndAddCleanup
                               ((uint)ptVar28,
                                (_func_void_void_ptr *)&Elf32_Phdr_ARRAY_00000034[0].p_offset);
              if (this != (PersistRegionInfo *)0x0) {
                robopersist::PersistRegionInfo::PersistRegionInfo(this);
              }
            }
            local_154[local_15c + 1] = (uint)this;
          }
          else {
            uVar16 = *local_154;
            if ((int)uVar16 <= local_15c) {
              if (uVar16 == local_158) goto LAB_00018e34;
              goto LAB_000187ca;
            }
            this = (PersistRegionInfo *)local_154[local_15c + 1];
          }
          pvVar2 = local_1a8;
          local_15c = local_15c + 1;
          *(undefined4 *)(this + 0x2c) = uVar9;
          this[0x30] = local_144._0_1_;
          *(uint *)(this + 0x28) = length;
          this[0x31] = local_144._1_1_;
          if (local_144._0_1_ == (PersistRegionInfo)0x0) {
            piVar23 = *(int **)(this + 0x14);
            if (piVar23 == (int *)0x0) {
LAB_00018f02:
              google::protobuf::internal::RepeatedPtrFieldBase::Reserve((int)(this + 8));
              ptVar28 = *(type_info **)(this + 8);
              **(int **)(this + 0x14) = **(int **)(this + 0x14) + 1;
              if (ptVar28 == (type_info *)0x0) {
LAB_00018f1c:
                pcVar13 = operator_new(4);
LAB_00018aaa:
                *(allocator **)pcVar13 = local_1d0 + 0xc;
              }
              else {
LAB_00018a90:
                if (*(int *)(ptVar28 + 0x40) != 0) {
                  google::protobuf::Arena::OnArenaAllocation
                            (ptVar28,*(uint *)(iVar31 + iRam0001920c));
                }
                pcVar13 = (char *)google::protobuf::internal::ArenaImpl::
                                  AllocateAlignedAndAddCleanup
                                            ((uint)ptVar28,
                                             (_func_void_void_ptr *)
                                             &Elf32_Ehdr_00000000.e_ident_abiversion);
                if (pcVar13 != (char *)0x0) goto LAB_00018aaa;
              }
              iVar25 = *(int *)(this + 0xc);
              *(int *)(this + 0xc) = iVar25 + 1;
              *(char **)(*(int *)(this + 0x14) + iVar25 * 4 + 4) = pcVar13;
            }
            else {
              iVar25 = *(int *)(this + 0xc);
              iVar17 = *piVar23;
              if (iVar17 <= iVar25) {
                if (iVar17 == *(int *)(this + 0x10)) goto LAB_00018f02;
                ptVar28 = *(type_info **)(this + 8);
                *piVar23 = iVar17 + 1;
                if (ptVar28 == (type_info *)0x0) goto LAB_00018f1c;
                goto LAB_00018a90;
              }
              *(int *)(this + 0xc) = iVar25 + 1;
              pcVar13 = (char *)piVar23[iVar25 + 1];
            }
            std::string::assign(pcVar13,(uint)pvVar2);
          }
          else {
            uVar10 = get_nprocs();
            iVar25 = length - 1;
            uVar16 = length >> 0x14;
            if ((int)uVar10 <= (int)(length >> 0x14)) {
              uVar16 = uVar10;
            }
            if ((int)uVar16 < 1) {
              uVar16 = 1;
            }
            local_21c = __aeabi_uidiv(iVar25 + uVar16);
            if ((local_21c & 7) != 0) {
              local_21c = (local_21c & 0xfffffff8) + 8;
            }
            uVar16 = __aeabi_uidiv(iVar25 + local_21c,local_21c);
            if (uVar16 != 1) {
              if (uVar16 == 0) {
                local_1dc = (allocator *)0x0;
                local_1c4 = (allocator *)0x0;
              }
              else {
                if (0x3fffffff < uVar16) {
                  std::__throw_bad_alloc();
                  bStack0000008c =
                       *(byte *)(*(byte *)((uint)*(byte *)(extraout_r3 + 0xc) * 0x80000 + 9) + 0xc);
                  local_158 = local_158 & 0xffffff;
                  Elf32_Ehdr_00000000.e_entry._0_1_ = 0;
                  *(char *)((int)&stack0x00000078 * 0x40000 + 5) = (char)&stack0x000000b4 + -0x1c;
                  *(undefined1 *)(extraout_r3 + 0x16) = 0;
                  *(byte *)(iVar25 * 0x100000 + 10) = bStack0000008c;
                  *(undefined1 *)(bStack0000008c + 3) = 0;
                  local_160._0_2_ = (ushort)(byte)local_160;
                  std::vector<std::thread,std::allocator<std::thread>>::~vector
                            ((vector<std::thread,std::allocator<std::thread>> *)&local_188);
                  paVar24 = local_1dc;
                  while (local_1c4 != paVar24) {
                    paVar24 = local_1b8 + 4;
                    iVar8 = *(int *)local_1b8;
                    local_1b8 = paVar24;
                    if ((allocator *)(iVar8 + -0xc) != local_1d0) {
                      piVar18 = (int *)(iVar8 + -4);
                      if (*(int *)(iVar31 + DAT_000192c0) == 0) {
                        iVar15 = *(int *)(iVar8 + -4);
                        *(int *)(iVar8 + -4) = iVar15 + -1;
                      }
                      else {
                        DataMemoryBarrier(0x1b);
                        do {
                          ExclusiveAccess(piVar18);
                          iVar15 = *piVar18;
                          bVar6 = (bool)hasExclusiveAccess(piVar18);
                        } while (!bVar6);
                        *piVar18 = iVar15 + -1;
                        DataMemoryBarrier(0x1b);
                      }
                      if (iVar15 < 1) {
                        std::string::_Rep::_M_destroy((allocator *)(iVar8 + -0xc));
                      }
                    }
                  }
                  if (local_1dc != (allocator *)0x0) {
                    operator_delete(local_1dc);
                  }
                  SharedRegionLockGuard::~SharedRegionLockGuard(aSStack_198);
                  robopersist::PersistData::~PersistData((PersistData *)&local_168);
                    /* WARNING: Subroutine does not return */
                  __cxa_end_cleanup();
                }
                local_1dc = operator_new(uVar16 * 4);
                local_1c4 = local_1dc + uVar16 * 4;
                paVar24 = local_1dc;
                do {
                  if (paVar24 != (allocator *)0x0) {
                    *(allocator **)paVar24 = local_1d0 + 0xc;
                  }
                  paVar24 = paVar24 + 4;
                } while (paVar24 != local_1c4);
              }
              local_188 = (allocator *)0x0;
              local_184 = (allocator *)0x0;
              local_180 = (allocator *)0x0;
              paVar24 = local_1dc;
              if (0 < (int)uVar16) {
                local_228 = 0;
                uVar26 = 0;
                local_1b8 = local_1dc;
                paVar27 = local_1dc;
                uVar10 = length;
                do {
                  iVar25 = *(int *)(this + 0x18);
                  uVar21 = local_21c;
                  if (uVar10 <= local_21c) {
                    uVar21 = uVar10;
                  }
                  local_1a4 = local_228;
                  local_1a0 = uVar21;
                  if (iVar25 == *(int *)(this + 0x1c)) {
                    google::protobuf::RepeatedField<unsigned_int>::Reserve
                              ((RepeatedField<unsigned_int> *)(this + 0x18),iVar25 + 1);
                    iVar25 = *(int *)(this + 0x18);
                  }
                  paVar5 = local_184;
                  uVar4 = local_1a0;
                  uVar3 = local_1a4;
                  pvVar2 = local_1a8;
                  *(int *)(this + 0x18) = iVar25 + 1;
                  *(uint *)(*(int *)(this + 0x20) + iVar25 * 4 + 4) = uVar21;
                  local_19c = paVar27;
                  if (local_184 == local_180) {
                    std::vector<std::thread,std::allocator<std::thread>>::
                    _M_emplace_back_aux<void(&)(void_const*,unsigned_int,unsigned_int,std::string&),void_const*&,unsigned_int&,unsigned_int&,std::reference_wrapper<std::string>>
                              ((vector<std::thread,std::allocator<std::thread>> *)&local_188,
                               *(_func_void_void_ptr_uint_uint_string_ptr **)(iVar31 + iRam000191d0)
                               ,&local_1a8,&local_1a4,&local_1a0,(reference_wrapper *)&local_19c);
                  }
                  else {
                    if (local_184 != (allocator *)0x0) {
                      *(int *)local_184 = 0;
                      local_17c[0] = paVar27;
                      p_Var11 = operator_new(0x2c);
                      iVar25 = iRam000191c8;
                      *(undefined4 *)(p_Var11 + 4) = 1;
                      *(undefined4 *)(p_Var11 + 8) = 1;
                      iVar17 = iRam000191cc;
                      iVar25 = *(int *)(iVar31 + iVar25);
                      *(undefined4 *)(p_Var11 + 0x10) = 0;
                      *(undefined4 *)(p_Var11 + 0x14) = 0;
                      *(int *)p_Var11 = iVar25 + 8;
                      iVar17 = *(int *)(iVar31 + iVar17);
                      *(uint *)(p_Var11 + 0x1c) = uVar4;
                      iVar25 = iRam000191d0;
                      *(int *)(p_Var11 + 0xc) = iVar17 + 8;
                      *(uint *)(p_Var11 + 0x20) = uVar3;
                      iVar17 = iRam000191d4;
                      *(void **)(p_Var11 + 0x24) = pvVar2;
                      *(allocator **)(p_Var11 + 0x18) = local_17c[0];
                      *(undefined4 *)(p_Var11 + 0x28) = *(undefined4 *)(iVar31 + iVar25);
                      local_190 = std::
                                  _Sp_counted_ptr_inplace<std::thread::_Impl<std::_Bind_simple<void(*(void_const*,unsigned_int,unsigned_int,std::reference_wrapper<std::string>))(void_const*,unsigned_int,unsigned_int,std::string&)>>,std::allocator<std::thread::_Impl<std::_Bind_simple<void(*(void_const*,unsigned_int,unsigned_int,std::reference_wrapper<std::string>))(void_const*,unsigned_int,unsigned_int,std::string&)>>>,(__gnu_cxx::_Lock_policy)2>
                                  ::_M_get_deleter(p_Var11,*(type_info **)(iVar31 + iVar17));
                      local_18c = p_Var11;
                      std::thread::_M_start_thread
                                (paVar5,(allocator *)&local_190,
                                 *(undefined4 *)(iVar31 + iRam000191d8));
                      p_Var11 = local_18c;
                      if (local_18c !=
                          (_Sp_counted_ptr_inplace<std::thread::_Impl<std::_Bind_simple<void(*(void_const*,unsigned_int,unsigned_int,std::reference_wrapper<std::string>))(void_const*,unsigned_int,unsigned_int,std::string&)>>,std::allocator<std::thread::_Impl<std::_Bind_simple<void(*(void_const*,unsigned_int,unsigned_int,std::reference_wrapper<std::string>))(void_const*,unsigned_int,unsigned_int,std::string&)>>>,(__gnu_cxx::_Lock_policy)2>
                           *)0x0) {
                        if (*(int *)(iVar31 + iRam000191dc) == 0) {
                          iVar25 = *(int *)(local_18c + 4);
                          *(int *)(local_18c + 4) = iVar25 + -1;
                          if (iVar25 == 1) {
                            (**(code **)(*(int *)local_18c + 8))(local_18c);
                            iVar25 = *(int *)(p_Var11 + 8);
                            *(int *)(p_Var11 + 8) = iVar25 + -1;
                            goto LAB_00018a18;
                          }
                        }
                        else {
                          p_Var20 = local_18c + 4;
                          DataMemoryBarrier(0x1b);
                          do {
                            ExclusiveAccess(p_Var20);
                            iVar25 = *(int *)p_Var20;
                            bVar6 = (bool)hasExclusiveAccess(p_Var20);
                          } while (!bVar6);
                          *(int *)p_Var20 = iVar25 + -1;
                          DataMemoryBarrier(0x1b);
                          if (iVar25 == 1) {
                            (**(code **)(*(int *)local_18c + 8))(local_18c);
                            p_Var20 = p_Var11 + 8;
                            DataMemoryBarrier(0x1b);
                            do {
                              ExclusiveAccess(p_Var20);
                              iVar25 = *(int *)p_Var20;
                              bVar6 = (bool)hasExclusiveAccess(p_Var20);
                            } while (!bVar6);
                            *(int *)p_Var20 = iVar25 + -1;
                            DataMemoryBarrier(0x1b);
LAB_00018a18:
                            if (iVar25 == 1) {
                              (**(code **)(*(int *)p_Var11 + 0xc))(p_Var11);
                            }
                          }
                        }
                      }
                    }
                    local_184 = local_184 + 4;
                  }
                  uVar26 = uVar26 + 1;
                  paVar27 = paVar27 + 4;
                  local_228 = local_228 + local_21c;
                  uVar10 = uVar10 - local_21c;
                } while (uVar16 != uVar26);
                uVar10 = 0;
                paVar27 = local_1dc + -4;
                do {
                  std::thread::join();
                  paVar27 = paVar27 + 4;
                  uVar26 = *(uint *)paVar27;
                  piVar23 = *(int **)(this + 0x14);
                  if (piVar23 == (int *)0x0) {
LAB_00018df2:
                    google::protobuf::internal::RepeatedPtrFieldBase::Reserve((int)(this + 8));
                    ptVar28 = *(type_info **)(this + 8);
                    **(int **)(this + 0x14) = **(int **)(this + 0x14) + 1;
                    if (ptVar28 == (type_info *)0x0) {
LAB_00018e0a:
                      pcVar13 = operator_new(4);
LAB_00018da2:
                      *(allocator **)pcVar13 = local_1d0 + 0xc;
                    }
                    else {
LAB_00018d8a:
                      if (*(int *)(ptVar28 + 0x40) != 0) {
                        google::protobuf::Arena::OnArenaAllocation
                                  (ptVar28,*(uint *)(iVar31 + iRam0001920c));
                      }
                      pcVar13 = (char *)google::protobuf::internal::ArenaImpl::
                                        AllocateAlignedAndAddCleanup
                                                  ((uint)ptVar28,
                                                   (_func_void_void_ptr *)
                                                   &Elf32_Ehdr_00000000.e_ident_abiversion);
                      if (pcVar13 != (char *)0x0) goto LAB_00018da2;
                    }
                    iVar25 = *(int *)(this + 0xc);
                    *(int *)(this + 0xc) = iVar25 + 1;
                    *(char **)(*(int *)(this + 0x14) + iVar25 * 4 + 4) = pcVar13;
                  }
                  else {
                    iVar25 = *(int *)(this + 0xc);
                    iVar17 = *piVar23;
                    if (iVar17 <= iVar25) {
                      if (iVar17 == *(int *)(this + 0x10)) goto LAB_00018df2;
                      ptVar28 = *(type_info **)(this + 8);
                      *piVar23 = iVar17 + 1;
                      if (ptVar28 == (type_info *)0x0) goto LAB_00018e0a;
                      goto LAB_00018d8a;
                    }
                    *(int *)(this + 0xc) = iVar25 + 1;
                    pcVar13 = (char *)piVar23[iVar25 + 1];
                  }
                  std::string::assign(pcVar13,uVar26);
                  uVar10 = uVar10 + 1;
                } while (uVar16 != uVar10);
                if (local_184 == local_188) {
                  if (local_188 == (allocator *)0x0) goto joined_r0x00018d08;
                }
                else {
                  iVar25 = *(int *)local_188;
                  paVar27 = local_188;
                  while( true ) {
                    if (iVar25 != 0) {
                    /* WARNING: Subroutine does not return */
                      std::terminate();
                    }
                    paVar27 = paVar27 + 4;
                    if (local_184 == paVar27) break;
                    iVar25 = *(int *)paVar27;
                  }
                }
                operator_delete(local_188);
              }
joined_r0x00018d08:
              if (local_1c4 != paVar24) {
                do {
                  paVar27 = paVar24 + 4;
                  iVar25 = *(int *)paVar24;
                  paVar24 = paVar27;
                  if ((allocator *)(iVar25 + -0xc) != local_1d0) {
                    if (*(int *)(iVar31 + iRam000191dc) == 0) {
                      iVar17 = *(int *)(iVar25 + -4);
                      *(int *)(iVar25 + -4) = iVar17 + -1;
                    }
                    else {
                      piVar23 = (int *)(iVar25 + -4);
                      DataMemoryBarrier(0x1b);
                      do {
                        ExclusiveAccess(piVar23);
                        iVar17 = *piVar23;
                        bVar6 = (bool)hasExclusiveAccess(piVar23);
                      } while (!bVar6);
                      *piVar23 = iVar17 + -1;
                      DataMemoryBarrier(0x1b);
                    }
                    if (iVar17 < 1) goto code_r0x00018d50;
                  }
                  if (local_1c4 == paVar27) break;
                } while( true );
              }
              if (local_1dc != (allocator *)0x0) {
                operator_delete(local_1dc);
              }
              goto LAB_00018ac6;
            }
            local_17c[0] = local_1d0 + 0xc;
            CompressRegionWorker(local_1a8,0,length,local_17c);
            paVar24 = local_17c[0];
            piVar23 = *(int **)(this + 0x14);
            if (piVar23 == (int *)0x0) {
LAB_00018f74:
              google::protobuf::internal::RepeatedPtrFieldBase::Reserve((int)(this + 8));
              piVar23 = *(int **)(this + 0x14);
              iVar17 = *piVar23;
LAB_00018e80:
              ptVar28 = *(type_info **)(this + 8);
              *piVar23 = iVar17 + 1;
              if (ptVar28 == (type_info *)0x0) {
                pcVar13 = operator_new(4);
LAB_00018ea4:
                *(allocator **)pcVar13 = local_1d0 + 0xc;
              }
              else {
                if (*(int *)(ptVar28 + 0x40) != 0) {
                  google::protobuf::Arena::OnArenaAllocation
                            (ptVar28,*(uint *)(iVar31 + iRam0001920c));
                }
                pcVar13 = (char *)google::protobuf::internal::ArenaImpl::
                                  AllocateAlignedAndAddCleanup
                                            ((uint)ptVar28,
                                             (_func_void_void_ptr *)
                                             &Elf32_Ehdr_00000000.e_ident_abiversion);
                if (pcVar13 != (char *)0x0) goto LAB_00018ea4;
              }
              iVar25 = *(int *)(this + 0xc);
              *(int *)(this + 0xc) = iVar25 + 1;
              *(char **)(*(int *)(this + 0x14) + iVar25 * 4 + 4) = pcVar13;
            }
            else {
              iVar25 = *(int *)(this + 0xc);
              iVar17 = *piVar23;
              if (iVar17 <= iVar25) {
                if (iVar17 == *(int *)(this + 0x10)) goto LAB_00018f74;
                goto LAB_00018e80;
              }
              *(int *)(this + 0xc) = iVar25 + 1;
              pcVar13 = (char *)piVar23[iVar25 + 1];
            }
            std::string::assign(pcVar13,(uint)paVar24);
            if (local_17c[0] + -0xc != local_1d0) {
              if (*(int *)(iVar31 + iRam000191dc) == 0) {
                iVar25 = *(int *)(local_17c[0] + -4);
                *(int *)(local_17c[0] + -4) = iVar25 + -1;
              }
              else {
                paVar24 = local_17c[0] + -4;
                DataMemoryBarrier(0x1b);
                do {
                  ExclusiveAccess(paVar24);
                  iVar25 = *(int *)paVar24;
                  bVar6 = (bool)hasExclusiveAccess(paVar24);
                } while (!bVar6);
                *(int *)paVar24 = iVar25 + -1;
                DataMemoryBarrier(0x1b);
              }
              if (iVar25 < 1) {
                std::string::_Rep::_M_destroy(local_17c[0] + -0xc);
              }
            }
          }
LAB_00018ac6:
          RunPersistSharedRegionCallback(&local_148,3);
          uVar12 = crc32(0x80000000,local_1a8,length);
          _rrlogm(0x15,7,0x1cc,iVar15,iVar19,iRam000191e4 + 0x18af8,uVar9,length,uVar12);
          SharedRegionLockGuard::~SharedRegionLockGuard(aSStack_198);
          local_1d4 = local_1d4 + 1;
          local_1e8 = local_1e8 + 0x12;
        } while (local_1d4 < *(uint *)(puVar7 + 0x16));
      }
      std::ios_base::ios_base((ios_base *)local_b4);
      iVar15 = *(int *)(iVar31 + iRam000191e8);
      local_40 = 0;
      local_44 = 0;
      local_3f = 0;
      local_3c = 0;
      local_38 = 0;
      local_34 = 0;
      local_30 = 0;
      local_b4[0] = iVar15 + 8;
      iVar25 = *(int *)(iVar31 + iRam000191ec);
      uVar9 = *(undefined4 *)(iVar25 + 0xc);
      iVar17 = *(int *)(iVar25 + 8);
      *(undefined4 *)((int)&local_148 + *(int *)(iVar17 + -0xc)) = uVar9;
      local_144 = 0;
      std::ios::init((streambuf *)((int)&local_148 + *(int *)(iVar17 + -0xc)));
      uVar12 = *(undefined4 *)(iVar25 + 0x14);
      iVar30 = *(int *)(iVar25 + 0x10);
      iVar19 = *(int *)(iVar30 + -0xc);
      local_140 = iVar30;
      *(undefined4 *)((int)&local_140 + iVar19) = uVar12;
      std::ios::init((streambuf *)((int)&local_140 + iVar19));
      uVar22 = *(undefined4 *)(iVar25 + 0x18);
      iVar29 = *(int *)(iVar25 + 4);
      *(undefined4 *)((int)&local_148 + *(int *)(iVar29 + -0xc)) = uVar22;
      iVar25 = *(int *)(iVar31 + iRam000191f0);
      local_148 = iVar25 + 0xc;
      local_b4[0] = iVar25 + 0x34;
      local_140 = iVar25 + 0x20;
      std::filebuf::filebuf((filebuf *)&local_13c);
      std::ios::init((streambuf *)local_b4);
      iVar19 = std::filebuf::open((filebuf *)&local_13c,filename,0x14);
      if (iVar19 == 0) {
        std::ios::clear((int)&local_148 + *(int *)(local_148 + -0xc),
                        *(uint *)((int)auStack_134 + *(int *)(local_148 + -0xc)) | 4);
      }
      else {
        std::ios::clear((int)&local_148 + *(int *)(local_148 + -0xc),0);
      }
      google::protobuf::Message::SerializeToOstream((ostream *)&local_168);
      iVar19 = std::filebuf::close();
      if (iVar19 == 0) {
        std::ios::clear((int)&local_148 + *(int *)(local_148 + -0xc),
                        *(uint *)((int)auStack_134 + *(int *)(local_148 + -0xc)) | 4);
      }
      UnlockPersistInfo(persistence_type);
      _rrlogm(0x15,7,0x1dd,iRam00019200 + 0x18c50,iRam000191fc + 0x18d74,iRam000191f8 + 0x18c38,
              *(undefined4 *)(iRam000191f4 + 0x18c32));
      iVar19 = get_cur_time_ms();
      rr_max_int(1,0xc,iVar19 - iVar8);
      local_148 = iVar25 + 0xc;
      local_b4[0] = iVar25 + 0x34;
      local_140 = iVar25 + 0x20;
      bVar6 = true;
      local_13c = *(int *)(iVar31 + iRam00019204) + 8;
      std::filebuf::close();
      std::__basic_file<char>::~__basic_file(a_Stack_104);
      local_13c = *(int *)(iVar31 + iRam00019208) + 8;
      std::locale::~locale(alStack_120);
      iVar8 = *(int *)(iVar17 + -0xc);
      iVar31 = *(int *)(iVar30 + -0xc);
      *(undefined4 *)((int)&local_148 + *(int *)(iVar29 + -0xc)) = uVar22;
      *(undefined4 *)((int)&local_140 + iVar31) = uVar12;
      *(undefined4 *)((int)&local_148 + iVar8) = uVar9;
      local_b4[0] = iVar15 + 8;
      std::ios_base::~ios_base((ios_base *)local_b4);
      robopersist::PersistData::~PersistData((PersistData *)&local_168);
    }
  }
  if (local_2c == *piVar18) {
    return bVar6;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
code_r0x00018d50:
  std::string::_Rep::_M_destroy((allocator *)(iVar25 + -0xc));
  goto joined_r0x00018d08;
}

