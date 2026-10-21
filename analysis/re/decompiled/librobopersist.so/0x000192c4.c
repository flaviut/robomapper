/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x000192c4
 */

/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* File-only persistence loader: locks selected metadata, parses protobuf from filename and restores
   subscribed regions under individual locks/callback stages 0/1. compress controls inflation;
   encrypt is not tested. Return primarily reflects ParseFromIstream, not validation of every
   restored region. Multipart compressed load requires value count == rawDataPartSize count and
   prefix-sum total == rawDataSize; uses independent uncompress streams at prefix offsets and joins
   min(part_count,get_nprocs()) workers. Single compressed value uses rawDataSize and offset zero.
   Count/total/zlib errors only log/events; they do NOT clear parse-success result. Unexpected raw
   branch: with exactly one uncompressed value, memcpy length is value COUNT (1), not
   rawDataSize/string length (0x19692->0x19756); do not assume raw regions fully restore. Full
   protobuf/C++ layouts intentionally remain opaque. */

bool ForcePersistLoad(int persistence_type,char *filename)

{
  bool bVar1;
  int iVar2;
  void *pvVar3;
  bool bVar4;
  undefined2 *puVar5;
  _Sp_counted_ptr_inplace<std::thread::_Impl<std::_Bind_simple<void(*(std::reference_wrapper<robopersist::PersistRegionInfo_const>,void*,std::reference_wrapper<std::vector<int,std::allocator<int>>>,int,int))(robopersist::PersistRegionInfo_const&,void*,std::vector<int,std::allocator<int>>const&,int,int)>>,std::allocator<std::thread::_Impl<std::_Bind_simple<void(*(std::reference_wrapper<robopersist::PersistRegionInfo_const>,void*,std::reference_wrapper<std::vector<int,std::allocator<int>>>,int,int))(robopersist::PersistRegionInfo_const&,void*,std::vector<int,std::allocator<int>>const&,int,int)>>>,(__gnu_cxx::_Lock_policy)2>
  *p_Var6;
  int iVar7;
  undefined4 *puVar8;
  int iVar9;
  int iVar10;
  int *piVar11;
  _func_void_PersistRegionInfo_ptr_void_ptr_vector_ptr_int_int *p_Var12;
  int iVar13;
  int iVar14;
  undefined4 uVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  char *pcVar19;
  uint uVar20;
  char *pcVar21;
  _Sp_counted_ptr_inplace<std::thread::_Impl<std::_Bind_simple<void(*(std::reference_wrapper<robopersist::PersistRegionInfo_const>,void*,std::reference_wrapper<std::vector<int,std::allocator<int>>>,int,int))(robopersist::PersistRegionInfo_const&,void*,std::vector<int,std::allocator<int>>const&,int,int)>>,std::allocator<std::thread::_Impl<std::_Bind_simple<void(*(std::reference_wrapper<robopersist::PersistRegionInfo_const>,void*,std::reference_wrapper<std::vector<int,std::allocator<int>>>,int,int))(robopersist::PersistRegionInfo_const&,void*,std::vector<int,std::allocator<int>>const&,int,int)>>>,(__gnu_cxx::_Lock_policy)2>
  *p_Var22;
  int *piVar23;
  int iVar24;
  void *region_message;
  int *piVar25;
  int iVar26;
  int iVar27;
  size_t __n;
  uint uVar28;
  undefined2 *puVar29;
  int iVar30;
  uint uVar31;
  void *local_1e0;
  uint local_1dc;
  int local_1d8;
  void *local_1d4;
  undefined4 **local_1d0;
  SharedRegionLockGuard aSStack_1cc [8];
  undefined4 local_1c4;
  _Sp_counted_ptr_inplace<std::thread::_Impl<std::_Bind_simple<void(*(std::reference_wrapper<robopersist::PersistRegionInfo_const>,void*,std::reference_wrapper<std::vector<int,std::allocator<int>>>,int,int))(robopersist::PersistRegionInfo_const&,void*,std::vector<int,std::allocator<int>>const&,int,int)>>,std::allocator<std::thread::_Impl<std::_Bind_simple<void(*(std::reference_wrapper<robopersist::PersistRegionInfo_const>,void*,std::reference_wrapper<std::vector<int,std::allocator<int>>>,int,int))(robopersist::PersistRegionInfo_const&,void*,std::vector<int,std::allocator<int>>const&,int,int)>>>,(__gnu_cxx::_Lock_policy)2>
  *local_1c0;
  undefined4 *local_1bc;
  undefined4 *local_1b8;
  undefined4 *local_1b4;
  int *local_1b0;
  int *local_1ac;
  int *local_1a8;
  undefined4 *local_1a4;
  undefined4 **local_1a0;
  undefined4 **local_19c;
  void *local_194;
  PersistData aPStack_18c [12];
  int local_180;
  int local_178;
  int local_174;
  int local_16c;
  undefined4 uStack_168;
  undefined4 uStack_164;
  undefined4 uStack_160;
  undefined4 local_15c;
  undefined4 uStack_158;
  undefined4 uStack_154;
  undefined4 uStack_150;
  undefined4 local_14c;
  int local_148 [2];
  int local_140;
  int local_13c [2];
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
  
  iVar30 = DAT_00019af0 + 0x192de;
  piVar23 = *(int **)(iVar30 + DAT_00019af4);
  iVar26 = DAT_00019afc + 0x19300;
  uVar15 = *(undefined4 *)(DAT_00019af8 + 0x192f2);
  local_2c = *piVar23;
  iVar24 = DAT_00019b04 + 0x19456;
  pcVar19 = filename;
  _rrlogm(0x15,6,0x207,iVar26,iVar24,DAT_00019b00 + 0x19306,uVar15,filename);
  puVar5 = LockPersistInfo(persistence_type);
  if (puVar5 == (undefined2 *)0x0) {
    _rrlogm(0x15,3,0x20c,iVar26,iVar24,DAT_00019b9c + 0x19a32,uVar15,pcVar19);
    bVar4 = false;
  }
  else {
    CheckPersistInfoOwner(persistence_type);
    robopersist::PersistData::PersistData(aPStack_18c);
    std::ios_base::ios_base((ios_base *)local_b4);
    iVar24 = *(int *)(iVar30 + DAT_00019b08);
    local_44 = 0;
    local_40 = 0;
    local_3f = 0;
    local_3c = 0;
    local_38 = 0;
    local_34 = 0;
    local_30 = 0;
    local_b4[0] = iVar24 + 8;
    iVar9 = *(int *)(iVar30 + DAT_00019b0c);
    iVar26 = *(int *)(iVar9 + 8);
    local_148[0] = iVar26;
    *(undefined4 *)((int)local_148 + *(int *)(iVar26 + -0xc)) = *(undefined4 *)(iVar9 + 0xc);
    local_148[1] = 0;
    std::ios::init((streambuf *)((int)local_148 + *(int *)(iVar26 + -0xc)));
    local_140 = *(int *)(iVar9 + 0x10);
    iVar26 = *(int *)(local_140 + -0xc);
    *(undefined4 *)((int)local_13c + iVar26 + -4) = *(undefined4 *)(iVar9 + 0x14);
    std::ios::init((streambuf *)((int)local_13c + iVar26 + -4));
    *(undefined4 *)((int)local_148 + *(int *)(*(int *)(iVar9 + 4) + -0xc)) =
         *(undefined4 *)(iVar9 + 0x18);
    iVar16 = *(int *)(iVar30 + DAT_00019b10);
    local_148[0] = iVar16 + 0xc;
    local_b4[0] = iVar16 + 0x34;
    local_140 = iVar16 + 0x20;
    std::filebuf::filebuf((filebuf *)local_13c);
    std::ios::init((streambuf *)local_b4);
    iVar26 = std::filebuf::open((filebuf *)local_13c,filename,0xc);
    if (iVar26 == 0) {
      std::ios::clear((int)local_148 + *(int *)(local_148[0] + -0xc),
                      *(uint *)((int)auStack_134 + *(int *)(local_148[0] + -0xc)) | 4);
    }
    else {
      std::ios::clear((int)local_148 + *(int *)(local_148[0] + -0xc),0);
    }
    iVar26 = google::protobuf::Message::ParseFromIstream((istream *)aPStack_18c);
    if (iVar26 == 0) {
      _rrlogm(0x15,4,0x219,DAT_00019b54 + 0x19666,DAT_00019b4c + 0x19796,DAT_00019b50 + 0x19658,
              filename);
      rr_stat_int(1,7);
    }
    bVar4 = iVar26 != 0;
    iVar26 = std::filebuf::close();
    if (iVar26 == 0) {
      std::ios::clear((int)local_148 + *(int *)(local_148[0] + -0xc),
                      *(uint *)((int)auStack_134 + *(int *)(local_148[0] + -0xc)) | 4);
    }
    if (bVar4) {
      _rrlogm(0x15,6,0x231,DAT_00019b1c + 0x19490,DAT_00019b18 + 0x195c2,DAT_00019b14 + 0x19478,
              *(undefined4 *)(puVar5 + 0x16));
      if (local_174 == 0) {
        local_174 = *(int *)(iVar30 + DAT_00019ba0);
      }
      *puVar5 = (short)*(undefined4 *)(local_174 + 0xc);
      *(undefined4 *)(puVar5 + 1) = 0;
      *(undefined4 *)(puVar5 + 3) = 0;
      *(undefined4 *)(puVar5 + 5) = 0;
      *(undefined4 *)(puVar5 + 7) = 0;
      puVar5[9] = 0;
      memcpy(puVar5 + 1,(void *)**(undefined4 **)(local_174 + 8),
             *(size_t *)((int)**(undefined4 **)(local_174 + 8) + -0xc));
      if (*(int *)(puVar5 + 0x16) != 0) {
        uVar31 = 0;
        iVar26 = DAT_00019b20 + 0x1961e;
        iVar7 = DAT_00019b2c + 0x194f0;
        iVar10 = DAT_00019b24 + 0x1962e;
        iVar17 = DAT_00019b28 + 0x19630;
        puVar29 = puVar5;
        do {
          local_16c = *(int *)(puVar29 + 0x18);
          uStack_168 = *(undefined4 *)(puVar29 + 0x1a);
          uStack_164 = *(undefined4 *)(puVar29 + 0x1c);
          uStack_160 = *(undefined4 *)(puVar29 + 0x1e);
          local_15c = *(undefined4 *)(puVar29 + 0x20);
          uStack_158 = *(undefined4 *)(puVar29 + 0x22);
          uStack_154 = *(undefined4 *)(puVar29 + 0x24);
          uStack_150 = *(undefined4 *)(puVar29 + 0x26);
          local_14c = *(undefined4 *)(puVar29 + 0x28);
          _rrlogm(0x15,7,0x23a,iVar7,iVar26,DAT_00019b30 + 0x1950c,local_16c,pcVar19);
          iVar13 = local_16c;
          if (0 < local_180) {
            region_message = *(void **)(local_178 + 4);
            iVar27 = *(int *)((int)region_message + 0x2c);
            if (iVar27 != local_16c) {
              piVar11 = (int *)(local_178 + 4);
              iVar18 = 0;
              do {
                iVar18 = iVar18 + 1;
                if (iVar18 == local_180) goto LAB_00019560;
                piVar11 = piVar11 + 1;
                region_message = (void *)*piVar11;
                iVar27 = *(int *)((int)region_message + 0x2c);
              } while (iVar27 != local_16c);
            }
            SharedRegionLockGuard::SharedRegionLockGuard(aSStack_1cc,persistence_type,local_16c);
            RunPersistSharedRegionCallback(&local_16c,0);
            pcVar19 = *(char **)((int)region_message + 0x28);
            __n = *(size_t *)((int)region_message + 0xc);
            local_1e0 = (void *)GetSharedRegion(iVar13,pcVar19);
            uVar28 = *(uint *)((int)region_message + 0xc);
            if (*(char *)((int)region_message + 0x30) == '\0') {
              if (uVar28 == 1) {
                memcpy(local_1e0,(void *)**(undefined4 **)(*(int *)((int)region_message + 0x14) + 4)
                       ,__n);
              }
              else {
                _rrlogm(0x15,4,0x283,DAT_00019b70 + 0x19744,iVar17,DAT_00019b6c + 0x19736,uVar28);
                rr_event_int(1,6,0x66);
              }
            }
            else {
              if (uVar28 == 1) {
                local_1a4 = (undefined4 *)0x0;
                local_1a0 = (undefined4 **)0x0;
                local_19c = (undefined4 **)0x0;
                local_1a4 = operator_new(4);
                local_1a0 = (undefined4 **)(local_1a4 + 1);
                *local_1a4 = 0;
                local_19c = local_1a0;
                PersistInflateParts(region_message,local_1e0,&local_1a4,0,1);
                puVar8 = local_1a4;
                goto joined_r0x0001982e;
              }
              if (uVar28 != *(uint *)((int)region_message + 0x18)) {
                _rrlogm(0x15,4,0x255,DAT_00019b60 + 0x196e0,DAT_00019b58 + 0x1980c,
                        DAT_00019b5c + 0x196d6,uVar28,*(uint *)((int)region_message + 0x18));
                rr_event_int(1,6,100);
                goto LAB_000196ee;
              }
              local_1bc = (undefined4 *)0x0;
              local_1b8 = (undefined4 *)0x0;
              local_1b4 = (undefined4 *)0x0;
              if (uVar28 == 0) {
                local_1b4 = (undefined4 *)0x0;
              }
              else {
                if (0x3fffffff < uVar28) {
                  std::__throw_bad_alloc();
                  goto LAB_00019aa4;
                }
                local_1bc = operator_new(uVar28 * 4);
                local_1b4 = local_1bc + uVar28;
                puVar8 = local_1bc;
                uVar20 = uVar28;
                do {
                  uVar20 = uVar20 - 1;
                  *puVar8 = 0;
                  puVar8 = puVar8 + 1;
                } while (uVar20 != 0);
              }
              if ((int)uVar28 < 1) {
                pcVar21 = (char *)0x0;
              }
              else {
                piVar11 = *(int **)((int)region_message + 0x20);
                puVar8 = local_1bc + -1;
                pcVar21 = (char *)0x0;
                piVar25 = piVar11 + uVar28;
                do {
                  puVar8 = puVar8 + 1;
                  *puVar8 = pcVar21;
                  piVar11 = piVar11 + 1;
                  pcVar21 = pcVar21 + *piVar11;
                } while (piVar25 != piVar11);
              }
              local_1b8 = local_1b4;
              if (pcVar19 == pcVar21) {
                uVar20 = get_nprocs();
                local_1b0 = (int *)0x0;
                local_1ac = (int *)0x0;
                local_1d8 = 0;
                local_1a8 = (int *)0x0;
                local_1dc = uVar28;
                if ((int)uVar20 <= (int)uVar28) {
                  local_1dc = uVar20;
                }
                puVar8 = local_1bc;
                if (0 < (int)local_1dc) {
                  p_Var12 = (_func_void_PersistRegionInfo_ptr_void_ptr_vector_ptr_int_int *)
                            (DAT_00019b80 + 0x1986c);
                  iVar13 = DAT_00019b84 + 0x19872;
                  do {
                    piVar11 = local_1ac;
                    iVar18 = local_1d8;
                    uVar28 = local_1dc;
                    pvVar3 = local_1e0;
                    local_1d4 = region_message;
                    local_1d0 = &local_1bc;
                    if (local_1a8 == local_1ac) {
                      std::vector<std::thread,std::allocator<std::thread>>::
                      _M_emplace_back_aux<void(&)(robopersist::PersistRegionInfo_const&,void*,std::vector<int,std::allocator<int>>const&,int,int),std::reference_wrapper<robopersist::PersistRegionInfo_const>,void*&,std::reference_wrapper<std::vector<int,std::allocator<int>>>,int&,int&>
                                ((vector<std::thread,std::allocator<std::thread>> *)&local_1b0,
                                 p_Var12,(reference_wrapper *)&local_1d4,&local_1e0,
                                 (reference_wrapper *)&local_1d0,&local_1d8,(int *)&local_1dc);
                    }
                    else {
                      piVar25 = (int *)0x0;
                      if (local_1ac != (int *)0x0) {
                        *local_1ac = 0;
                        local_19c = &local_1bc;
                        local_194 = region_message;
                        p_Var6 = operator_new(0x30);
                        iVar14 = DAT_00019b88;
                        *(undefined4 *)(p_Var6 + 4) = 1;
                        *(undefined4 *)(p_Var6 + 8) = 1;
                        iVar2 = DAT_00019b8c;
                        *(int *)p_Var6 = *(int *)(iVar30 + iVar14) + 8;
                        *(undefined4 *)(p_Var6 + 0x10) = 0;
                        *(undefined4 *)(p_Var6 + 0x14) = 0;
                        iVar14 = *(int *)(iVar30 + iVar2);
                        *(void **)(p_Var6 + 0x28) = local_194;
                        *(undefined4 ***)(p_Var6 + 0x20) = local_19c;
                        *(int *)(p_Var6 + 0x1c) = iVar18;
                        *(uint *)(p_Var6 + 0x18) = uVar28;
                        iVar18 = DAT_00019b90;
                        *(void **)(p_Var6 + 0x24) = pvVar3;
                        *(int *)(p_Var6 + 0xc) = iVar14 + 8;
                        *(int *)(p_Var6 + 0x2c) = iVar13;
                        local_1c4 = std::
                                    _Sp_counted_ptr_inplace<std::thread::_Impl<std::_Bind_simple<void(*(std::reference_wrapper<robopersist::PersistRegionInfo_const>,void*,std::reference_wrapper<std::vector<int,std::allocator<int>>>,int,int))(robopersist::PersistRegionInfo_const&,void*,std::vector<int,std::allocator<int>>const&,int,int)>>,std::allocator<std::thread::_Impl<std::_Bind_simple<void(*(std::reference_wrapper<robopersist::PersistRegionInfo_const>,void*,std::reference_wrapper<std::vector<int,std::allocator<int>>>,int,int))(robopersist::PersistRegionInfo_const&,void*,std::vector<int,std::allocator<int>>const&,int,int)>>>,(__gnu_cxx::_Lock_policy)2>
                                    ::_M_get_deleter(p_Var6,*(type_info **)(iVar30 + iVar18));
                        local_1c0 = p_Var6;
                        std::thread::_M_start_thread
                                  (piVar11,&local_1c4,*(undefined4 *)(iVar30 + DAT_00019b94));
                        p_Var6 = local_1c0;
                        piVar25 = local_1ac;
                        if (local_1c0 !=
                            (_Sp_counted_ptr_inplace<std::thread::_Impl<std::_Bind_simple<void(*(std::reference_wrapper<robopersist::PersistRegionInfo_const>,void*,std::reference_wrapper<std::vector<int,std::allocator<int>>>,int,int))(robopersist::PersistRegionInfo_const&,void*,std::vector<int,std::allocator<int>>const&,int,int)>>,std::allocator<std::thread::_Impl<std::_Bind_simple<void(*(std::reference_wrapper<robopersist::PersistRegionInfo_const>,void*,std::reference_wrapper<std::vector<int,std::allocator<int>>>,int,int))(robopersist::PersistRegionInfo_const&,void*,std::vector<int,std::allocator<int>>const&,int,int)>>>,(__gnu_cxx::_Lock_policy)2>
                             *)0x0) {
                          if (*(int *)(iVar30 + DAT_00019b98) == 0) {
                            iVar18 = *(int *)(local_1c0 + 4);
                            *(int *)(local_1c0 + 4) = iVar18 + -1;
                            if (iVar18 == 1) {
                              (**(code **)(*(int *)local_1c0 + 8))(local_1c0);
                              iVar18 = *(int *)(p_Var6 + 8);
                              *(int *)(p_Var6 + 8) = iVar18 + -1;
LAB_00019972:
                              piVar25 = local_1ac;
                              if (iVar18 == 1) {
                                (**(code **)(*(int *)p_Var6 + 0xc))(p_Var6);
                                piVar25 = local_1ac;
                              }
                            }
                          }
                          else {
                            p_Var22 = local_1c0 + 4;
                            DataMemoryBarrier(0x1b);
                            do {
                              ExclusiveAccess(p_Var22);
                              iVar18 = *(int *)p_Var22;
                              bVar1 = (bool)hasExclusiveAccess(p_Var22);
                            } while (!bVar1);
                            *(int *)p_Var22 = iVar18 + -1;
                            DataMemoryBarrier(0x1b);
                            if (iVar18 == 1) {
                              (**(code **)(*(int *)local_1c0 + 8))(local_1c0);
                              p_Var22 = p_Var6 + 8;
                              DataMemoryBarrier(0x1b);
                              do {
                                ExclusiveAccess(p_Var22);
                                iVar18 = *(int *)p_Var22;
                                bVar1 = (bool)hasExclusiveAccess(p_Var22);
                              } while (!bVar1);
                              *(int *)p_Var22 = iVar18 + -1;
                              DataMemoryBarrier(0x1b);
                              goto LAB_00019972;
                            }
                          }
                        }
                      }
                      local_1ac = piVar25 + 1;
                    }
                    piVar11 = local_1ac;
                    local_1d8 = local_1d8 + 1;
                  } while (local_1d8 < (int)local_1dc);
                  piVar25 = local_1b0;
                  if (local_1ac == local_1b0) {
LAB_00019a58:
                    puVar8 = local_1bc;
                    if (piVar11 == (int *)0x0) goto joined_r0x0001982e;
                  }
                  else {
                    do {
                      std::thread::join();
                      piVar25 = piVar25 + 1;
                    } while (piVar11 != piVar25);
                    piVar11 = local_1b0;
                    if (local_1b0 == local_1ac) goto LAB_00019a58;
                    iVar13 = *local_1b0;
                    piVar25 = local_1b0;
                    while( true ) {
                      if (iVar13 != 0) {
                    /* WARNING: Subroutine does not return */
                        std::terminate();
                      }
                      piVar25 = piVar25 + 1;
                      if (piVar25 == local_1ac) break;
                      iVar13 = *piVar25;
                    }
                  }
                  operator_delete(piVar11);
                  puVar8 = local_1bc;
                }
              }
              else {
                _rrlogm(0x15,4,0x270,DAT_00019b7c + 0x197ea,DAT_00019b74 + 0x1991a,
                        DAT_00019b78 + 0x197dc,pcVar19,pcVar21);
                puVar8 = local_1bc;
              }
joined_r0x0001982e:
              if (puVar8 != (undefined4 *)0x0) {
                operator_delete(puVar8);
              }
            }
LAB_000196ee:
            RunPersistSharedRegionCallback(&local_16c,1);
            _rrlogm(0x15,7,0x289,DAT_00019b68 + 0x19716,iVar10,DAT_00019b64 + 0x19708,iVar27,pcVar19
                   );
            SharedRegionLockGuard::~SharedRegionLockGuard(aSStack_1cc);
          }
LAB_00019560:
          uVar31 = uVar31 + 1;
          puVar29 = puVar29 + 0x12;
        } while (uVar31 < *(uint *)(puVar5 + 0x16));
      }
    }
    UnlockPersistInfo(persistence_type);
    _rrlogm(0x15,7,0x294,DAT_00019b40 + 0x195a8,DAT_00019b3c + 0x196e0,DAT_00019b38 + 0x1958e,
            *(undefined4 *)(DAT_00019b34 + 0x19586),filename);
    local_b4[0] = iVar16 + 0x34;
    local_148[0] = iVar16 + 0xc;
    local_140 = iVar16 + 0x20;
    local_13c[0] = *(int *)(iVar30 + DAT_00019b44) + 8;
    std::filebuf::close();
    std::__basic_file<char>::~__basic_file(a_Stack_104);
    local_13c[0] = *(int *)(iVar30 + DAT_00019b48) + 8;
    std::locale::~locale(alStack_120);
    iVar30 = *(int *)(*(int *)(iVar9 + 8) + -0xc);
    iVar26 = *(int *)(*(int *)(iVar9 + 0x10) + -0xc);
    *(undefined4 *)((int)local_148 + *(int *)(*(int *)(iVar9 + 4) + -0xc)) =
         *(undefined4 *)(iVar9 + 0x18);
    uVar15 = *(undefined4 *)(iVar9 + 0xc);
    *(undefined4 *)((int)local_13c + iVar26 + -4) = *(undefined4 *)(iVar9 + 0x14);
    *(undefined4 *)((int)local_148 + iVar30) = uVar15;
    local_b4[0] = iVar24 + 8;
    std::ios_base::~ios_base((ios_base *)local_b4);
    robopersist::PersistData::~PersistData(aPStack_18c);
  }
  if (local_2c == *piVar23) {
    return bVar4;
  }
LAB_00019aa4:
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

