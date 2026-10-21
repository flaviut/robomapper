/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0001d10c
 */

/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Detached pthread entry; argument is root+8 task, NOT root. Locks task then root; state 2->3
   encodes buffered regions (compress flag selects zlib; encrypt recorded only), joins multipart
   compressors, then state 3->4. Loops signed destination flags -7 through 11, separately. Temp name
   is filename + .tmp + DECIMAL TASK INDEX at task+0, NOT owner PID at task+4. SerializeToOstream
   return ignored; open/close failure only sets stream fail state. Under root mutex rechecks
   destination bit and renames, or unlinks temp if canceled. Rename failures log only. Cleanup
   unmaps/closes, sets state 0, releases task mutex and posts semaphore even after
   failures/cancellation. No fsync/fdatasync/directory-sync call in this entry. Return is null
   pthread result, no result to enqueue caller. Lock-error paths may continue when not model-version
   2. */

void * PersistMapWriteWorker(PersistMapTaskView *task)

{
  PersistRegionInfo PVar1;
  bool bVar2;
  uint uVar3;
  uint uVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  string *psVar9;
  PersistRegionInfo *this;
  uint uVar10;
  int *piVar11;
  char *pcVar12;
  undefined4 *puVar13;
  int iVar14;
  char *pcVar15;
  PersistInfo *pPVar16;
  void *pvVar17;
  uint uVar18;
  int *piVar19;
  int iVar20;
  undefined4 uVar21;
  undefined4 uVar22;
  uint uVar23;
  _func_bool_void_ptr_uint_uint_string_ptr_BufferedMapInfoSavStatus_ptr *p_Var24;
  PersistTaskState *pPVar25;
  allocator *paVar26;
  int *piVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  undefined4 uVar31;
  BufferedMapInfoSavStatus *pBVar32;
  int iVar33;
  int iVar34;
  uint uVar35;
  type_info *ptVar36;
  int iVar37;
  PersistRegionInfo PVar38;
  uint uVar39;
  int iVar40;
  uint local_218;
  int *local_214;
  uint local_208;
  allocator *local_1e0;
  PersistData *local_1dc;
  int *local_1d8;
  PersistMapTaskView *local_1d4;
  int local_1cc;
  ushort *local_1c8;
  int *local_1c4;
  int *local_1b8;
  void *local_1a8;
  uint local_1a4;
  uint local_1a0;
  int *local_19c;
  BufferedMapInfoSavStatus *local_198;
  int *local_194;
  int *local_190;
  allocator *local_18c;
  allocator *local_188;
  allocator *local_184;
  allocator *local_180;
  int *local_17c;
  PersistData aPStack_168 [8];
  type_info *local_160;
  int local_15c;
  int local_158;
  int *local_154;
  PersistInfo *local_150;
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
  
  iVar40 = DAT_0001db70 + 0x1d126;
  piVar5 = *(int **)(iVar40 + DAT_0001db74);
  local_2c = *piVar5;
  iVar34 = DAT_0001db7c + 0x1d14a;
  iVar33 = DAT_0001db80 + 0x1d290;
  _rrlogm(0x15,6,0x168,iVar34,iVar33,DAT_0001db78 + 0x1d146,task->task_index);
  iVar8 = DAT_0001db84;
  iVar6 = PersistLockRobust(task->task_mutex_storage,1000);
  iVar7 = PersistLockRobust((void *)(*(int *)(iVar8 + 0x1d178) + 0x1b0),-1);
  if (task->state == PersistTaskReady) {
    _rrlogm(0x15,7,0x17a,iVar34,iVar33,DAT_0001dbac + 0x1d2dc,task->state,3);
    task->state = PersistTaskEncoding;
    if (iVar7 == 0) {
      pthread_mutex_unlock((pthread_mutex_t *)(*(int *)(iVar8 + 0x1d178) + 0x1b0));
      local_1c8 = task->buffer_mapping;
      robopersist::PersistData::PersistData(aPStack_168);
    }
    else {
      local_1c8 = task->buffer_mapping;
      robopersist::PersistData::PersistData(aPStack_168);
    }
    local_1dc = aPStack_168;
    if (local_150 == (PersistInfo *)0x0) {
      pPVar16 = operator_new(0x14);
      robopersist::PersistInfo::PersistInfo(pPVar16);
      local_150 = pPVar16;
    }
    pPVar16 = local_150;
    *(uint *)(local_150 + 0xc) = (uint)*local_1c8;
    std::string::string((string *)&local_18c,(char *)(local_1c8 + 1),(allocator *)&local_19c);
    psVar9 = *(string **)(pPVar16 + 8);
    if (psVar9 == *(string **)(iVar40 + DAT_0001dbb0)) {
      puVar13 = operator_new(4);
      iVar8 = DAT_0001e2c8;
      *puVar13 = local_18c;
      local_1e0 = *(allocator **)(iVar40 + iVar8);
      local_18c = local_1e0 + 0xc;
      *(undefined4 **)(pPVar16 + 8) = puVar13;
    }
    else {
      std::string::swap(psVar9);
      local_1e0 = *(allocator **)(iVar40 + DAT_0001dbb4);
    }
    if (local_18c + -0xc != local_1e0) {
      if (*(int *)(iVar40 + DAT_0001e2b8) == 0) {
        iVar8 = *(int *)(local_18c + -4);
        *(int *)(local_18c + -4) = iVar8 + -1;
      }
      else {
        paVar26 = local_18c + -4;
        DataMemoryBarrier(0x1b);
        do {
          ExclusiveAccess(paVar26);
          iVar8 = *(int *)paVar26;
          bVar2 = (bool)hasExclusiveAccess(paVar26);
        } while (!bVar2);
        *(int *)paVar26 = iVar8 + -1;
        DataMemoryBarrier(0x1b);
      }
      if (iVar8 < 1) {
        std::string::_Rep::_M_destroy(local_18c + -0xc);
      }
    }
    uVar23 = task->region_count;
    if (uVar23 == *(uint *)(local_1c8 + 0x16)) {
      if ((int)uVar23 < 1) {
LAB_0001d992:
        iVar8 = PersistLockRobust((void *)(*(int *)(DAT_0001dbf0 + 0x1d99c) + 0x1b0),-1);
        if (task->state == PersistTaskEncoding) {
          _rrlogm(0x15,7,0x1e0,DAT_0001dc24 + 0x1daf4,DAT_0001dc1c + 0x1dc1a,DAT_0001dc20 + 0x1daec,
                  task->state,4);
          task->state = PersistTaskWriting;
          if (iVar8 == 0) {
            pthread_mutex_unlock((pthread_mutex_t *)(*(int *)(DAT_0001dc28 + 0x1db06) + 0x1b0));
          }
          iVar33 = -7;
          iVar8 = DAT_0001dc2c + 0x1dc54;
          piVar11 = (int *)(DAT_0001dc30 + 0x1db24);
          iVar7 = DAT_0001dc34 + 0x1dc60;
          piVar19 = (int *)(DAT_0001dc38 + 0x1db32);
          do {
            iVar34 = PersistLockRobust((void *)(*piVar11 + 0x1b0),-1);
            uVar23 = CheckMapFlagMask(task->destination_mask,iVar33);
            if ((uVar23 == 0) || (task->state != PersistTaskWriting)) {
              if (iVar34 == 0) {
                pthread_mutex_unlock((pthread_mutex_t *)(*piVar19 + 0x1b0));
              }
            }
            else {
              if (iVar34 == 0) {
                pthread_mutex_unlock((pthread_mutex_t *)(*(int *)(DAT_0001e2d0 + 0x1e1cc) + 0x1b0));
              }
              GetMapInfoPersistFileName((string *)&local_180,iVar33);
              std::string::string((string *)&local_198,(string *)&local_180);
              std::string::append((char *)&local_198,DAT_0001e28c + 0x1dc66);
              __gnu_cxx::__to_xstring<std::string,char>
                        ((__gnu_cxx *)&local_194,
                         *(_func_int_char_ptr_uint_char_ptr___va_list **)(iVar40 + DAT_0001e290),
                         0x10,(char *)(DAT_0001e294 + 0x1dc84),task->task_index);
              if ((((PersistMapTaskView *)(local_198 + -8))->task_index <
                   (uint)(local_194[-3] + *(int *)(local_198 + -0xc))) &&
                 ((uint)(local_194[-3] + *(int *)(local_198 + -0xc)) <= (uint)local_194[-2])) {
                puVar13 = (undefined4 *)
                          std::string::insert((uint)&local_194,(char *)0x0,(uint)local_198);
              }
              else {
                puVar13 = (undefined4 *)std::string::append((string *)&local_198);
              }
              pcVar12 = (char *)*puVar13;
              *puVar13 = local_1e0 + 0xc;
              if ((allocator *)(local_194 + -3) != local_1e0) {
                if (*(int *)(iVar40 + DAT_0001e2b8) == 0) {
                  iVar34 = local_194[-1];
                  local_194[-1] = iVar34 + -1;
                }
                else {
                  piVar27 = local_194 + -1;
                  DataMemoryBarrier(0x1b);
                  do {
                    ExclusiveAccess(piVar27);
                    iVar34 = *piVar27;
                    bVar2 = (bool)hasExclusiveAccess(piVar27);
                  } while (!bVar2);
                  *piVar27 = iVar34 + -1;
                  DataMemoryBarrier(0x1b);
                }
                if (iVar34 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_194 + -3));
                }
              }
              if ((allocator *)(local_198 + -0xc) != local_1e0) {
                if (*(int *)(iVar40 + DAT_0001e2b8) == 0) {
                  iVar34 = *(int *)(local_198 + -4);
                  *(int *)(local_198 + -4) = iVar34 + -1;
                }
                else {
                  pBVar32 = local_198 + -4;
                  DataMemoryBarrier(0x1b);
                  do {
                    ExclusiveAccess(pBVar32);
                    iVar34 = *(int *)pBVar32;
                    bVar2 = (bool)hasExclusiveAccess(pBVar32);
                  } while (!bVar2);
                  *(int *)pBVar32 = iVar34 + -1;
                  DataMemoryBarrier(0x1b);
                }
                if (iVar34 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_198 + -0xc));
                }
              }
              std::ios_base::ios_base((ios_base *)local_b4);
              iVar34 = *(int *)(iVar40 + DAT_0001e298);
              local_40 = 0;
              local_44 = 0;
              local_b4[0] = iVar34 + 8;
              local_3f = 0;
              local_3c = 0;
              local_38 = 0;
              local_34 = 0;
              local_30 = 0;
              iVar37 = *(int *)(iVar40 + DAT_0001e29c);
              iVar20 = *(int *)(iVar37 + 8);
              uVar21 = *(undefined4 *)(iVar37 + 0xc);
              local_148[0] = iVar20;
              *(undefined4 *)((int)local_148 + *(int *)(iVar20 + -0xc)) = uVar21;
              local_148[1] = 0;
              std::ios::init((streambuf *)((int)local_148 + *(int *)(iVar20 + -0xc)));
              iVar28 = *(int *)(iVar37 + 0x10);
              uVar22 = *(undefined4 *)(iVar37 + 0x14);
              iVar29 = *(int *)(iVar28 + -0xc);
              local_140 = iVar28;
              *(undefined4 *)((int)local_13c + iVar29 + -4) = uVar22;
              std::ios::init((streambuf *)((int)local_13c + iVar29 + -4));
              iVar30 = *(int *)(iVar37 + 4);
              uVar31 = *(undefined4 *)(iVar37 + 0x18);
              *(undefined4 *)((int)local_148 + *(int *)(iVar30 + -0xc)) = uVar31;
              iVar37 = *(int *)(iVar40 + DAT_0001e2a0);
              local_148[0] = iVar37 + 0xc;
              local_b4[0] = iVar37 + 0x34;
              local_140 = iVar37 + 0x20;
              std::filebuf::filebuf((filebuf *)local_13c);
              std::ios::init((streambuf *)local_b4);
              iVar29 = std::filebuf::open((filebuf *)local_13c,pcVar12,0x14);
              if (iVar29 == 0) {
                std::ios::clear((int)local_148 + *(int *)(local_148[0] + -0xc),
                                *(uint *)((int)auStack_134 + *(int *)(local_148[0] + -0xc)) | 4);
              }
              else {
                std::ios::clear((int)local_148 + *(int *)(local_148[0] + -0xc),0);
              }
              google::protobuf::Message::SerializeToOstream((ostream *)local_1dc);
              iVar29 = std::filebuf::close();
              if (iVar29 == 0) {
                std::ios::clear((int)local_148 + *(int *)(local_148[0] + -0xc),
                                *(uint *)((int)auStack_134 + *(int *)(local_148[0] + -0xc)) | 4);
              }
              iVar29 = PersistLockRobust((void *)(*(int *)(DAT_0001e2a4 + 0x1dde2) + 0x1b0),-1);
              uVar23 = CheckMapFlagMask(task->destination_mask,iVar33);
              if (uVar23 == 0) {
                unlink(pcVar12);
              }
              else {
                iVar14 = rename(pcVar12,(char *)local_180);
                if (iVar14 == 0) {
                  _rrlogm(0x15,7,0x1ff,DAT_0001e2ac + 0x1de2e,iVar7,DAT_0001e2a8 + 0x1de1e,local_180
                         );
                }
                else {
                  piVar27 = __errno_location();
                  paVar26 = local_180;
                  pcVar15 = strerror(*piVar27);
                  _rrlogm(0x15,3,0x203,DAT_0001e2c4 + 0x1df3c,iVar8,DAT_0001e2c0 + 0x1df2e,paVar26,
                          pcVar15);
                }
              }
              if (iVar29 == 0) {
                pthread_mutex_unlock((pthread_mutex_t *)(*(int *)(DAT_0001e2bc + 0x1df0a) + 0x1b0));
              }
              local_148[0] = iVar37 + 0xc;
              local_b4[0] = iVar37 + 0x34;
              local_140 = iVar37 + 0x20;
              local_13c[0] = *(int *)(iVar40 + DAT_0001e2b0) + 8;
              std::filebuf::close();
              std::__basic_file<char>::~__basic_file(a_Stack_104);
              local_13c[0] = *(int *)(iVar40 + DAT_0001e2b4) + 8;
              std::locale::~locale(alStack_120);
              iVar29 = *(int *)(iVar28 + -0xc);
              iVar20 = *(int *)(iVar20 + -0xc);
              *(undefined4 *)((int)local_148 + *(int *)(iVar30 + -0xc)) = uVar31;
              *(undefined4 *)((int)local_13c + iVar29 + -4) = uVar22;
              *(undefined4 *)((int)local_148 + iVar20) = uVar21;
              local_b4[0] = iVar34 + 8;
              std::ios_base::~ios_base((ios_base *)local_b4);
              if ((allocator *)(pcVar12 + -0xc) != local_1e0) {
                if (*(int *)(iVar40 + DAT_0001e2b8) == 0) {
                  iVar34 = *(int *)(pcVar12 + -4);
                  *(int *)(pcVar12 + -4) = iVar34 + -1;
                }
                else {
                  DataMemoryBarrier(0x1b);
                  piVar27 = (int *)(pcVar12 + -4);
                  do {
                    ExclusiveAccess(piVar27);
                    iVar34 = *piVar27;
                    bVar2 = (bool)hasExclusiveAccess(piVar27);
                  } while (!bVar2);
                  *piVar27 = iVar34 + -1;
                  DataMemoryBarrier(0x1b);
                }
                if (iVar34 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(pcVar12 + -0xc));
                }
              }
              if (local_180 + -0xc != local_1e0) {
                if (*(int *)(iVar40 + DAT_0001e2b8) == 0) {
                  iVar34 = *(int *)(local_180 + -4);
                  *(int *)(local_180 + -4) = iVar34 + -1;
                }
                else {
                  paVar26 = local_180 + -4;
                  DataMemoryBarrier(0x1b);
                  do {
                    ExclusiveAccess(paVar26);
                    iVar34 = *(int *)paVar26;
                    bVar2 = (bool)hasExclusiveAccess(paVar26);
                  } while (!bVar2);
                  *(int *)paVar26 = iVar34 + -1;
                  DataMemoryBarrier(0x1b);
                }
                if (iVar34 < 1) {
                  std::string::_Rep::_M_destroy(local_180 + -0xc);
                }
              }
            }
            iVar33 = iVar33 + 1;
          } while (iVar33 != 0xc);
        }
        else {
          if (task->state == PersistTaskCanceled) {
            _rrlogm(0x15,7,0x1d5,DAT_0001dc18 + 0x1dacc,(int)&DAT_0001dbf4 + DAT_0001dc14,
                    DAT_0001dc10 + 0x1dab8,task->task_index);
          }
          else {
            _rrlogm(0x15,3,0x1d9,DAT_0001dbfc + 0x1d9e0,DAT_0001dbf4 + 0x1db00,
                    DAT_0001dbf8 + 0x1d9d0,task->state,task->task_index);
            iVar7 = rrlog_get_model_ver();
            if (iVar7 == 2) goto LAB_0001d756;
          }
          if (iVar8 == 0) {
            pthread_mutex_unlock((pthread_mutex_t *)(*(int *)(DAT_0001dc00 + 0x1d9f8) + 0x1b0));
          }
        }
        goto LAB_0001d1d0;
      }
      iVar8 = *(int *)(local_1c8 + 0x18);
      PVar1 = *(PersistRegionInfo *)(local_1c8 + 0x1a);
      iVar7 = task->regions[0].region_id;
      PVar38 = *(PersistRegionInfo *)((int)local_1c8 + 0x35);
      if (iVar7 == iVar8) {
        p_Var24 = (_func_bool_void_ptr_uint_uint_string_ptr_BufferedMapInfoSavStatus_ptr *)
                  (DAT_0001dbb8 + 0x1d38e);
        iVar33 = DAT_0001dbbc + 0x1d39a;
        local_1cc = 0;
        local_1d4 = task;
        do {
          local_1a8 = (void *)(local_1d4->regions[0].buffer_offset + (int)task->buffer_mapping);
          local_218 = local_1d4->regions[0].byte_length;
          if (local_154 == (int *)0x0) {
LAB_0001d8a6:
            google::protobuf::internal::RepeatedPtrFieldBase::Reserve((int)&local_160);
            iVar8 = *local_154;
LAB_0001d3d4:
            ptVar36 = local_160;
            *local_154 = iVar8 + 1;
            if (local_160 == (type_info *)0x0) {
              this = operator_new(0x38);
              robopersist::PersistRegionInfo::PersistRegionInfo(this);
            }
            else {
              if (*(int *)(local_160 + 0x40) != 0) {
                google::protobuf::Arena::OnArenaAllocation
                          (local_160,*(uint *)(iVar40 + DAT_0001dbec));
              }
              this = (PersistRegionInfo *)
                     google::protobuf::internal::ArenaImpl::AllocateAlignedAndAddCleanup
                               ((uint)ptVar36,
                                (_func_void_void_ptr *)&Elf32_Phdr_ARRAY_00000034[0].p_offset);
              if (this != (PersistRegionInfo *)0x0) {
                robopersist::PersistRegionInfo::PersistRegionInfo(this);
              }
            }
            local_154[local_15c + 1] = (int)this;
          }
          else {
            iVar8 = *local_154;
            if (iVar8 <= local_15c) {
              if (iVar8 == local_158) goto LAB_0001d8a6;
              goto LAB_0001d3d4;
            }
            this = (PersistRegionInfo *)local_154[local_15c + 1];
          }
          pvVar17 = local_1a8;
          local_15c = local_15c + 1;
          *(int *)(this + 0x2c) = iVar7;
          this[0x30] = PVar1;
          this[0x31] = PVar38;
          *(uint *)(this + 0x28) = local_218;
          if (PVar1 == (PersistRegionInfo)0x0) {
            piVar19 = *(int **)(this + 0x14);
            if (piVar19 == (int *)0x0) {
LAB_0001d940:
              google::protobuf::internal::RepeatedPtrFieldBase::Reserve((int)(this + 8));
              ptVar36 = *(type_info **)(this + 8);
              **(int **)(this + 0x14) = **(int **)(this + 0x14) + 1;
              if (ptVar36 == (type_info *)0x0) {
LAB_0001d95a:
                pcVar12 = operator_new(4);
LAB_0001d6c0:
                *(allocator **)pcVar12 = local_1e0 + 0xc;
              }
              else {
LAB_0001d6a6:
                if (*(int *)(ptVar36 + 0x40) != 0) {
                  google::protobuf::Arena::OnArenaAllocation
                            (ptVar36,*(uint *)(iVar40 + DAT_0001dbe8));
                }
                pcVar12 = (char *)google::protobuf::internal::ArenaImpl::
                                  AllocateAlignedAndAddCleanup
                                            ((uint)ptVar36,
                                             (_func_void_void_ptr *)
                                             &Elf32_Ehdr_00000000.e_ident_abiversion);
                if (pcVar12 != (char *)0x0) goto LAB_0001d6c0;
              }
              iVar8 = *(int *)(this + 0xc);
              *(int *)(this + 0xc) = iVar8 + 1;
              *(char **)(*(int *)(this + 0x14) + iVar8 * 4 + 4) = pcVar12;
            }
            else {
              iVar8 = *(int *)(this + 0xc);
              iVar7 = *piVar19;
              if (iVar7 <= iVar8) {
                if (iVar7 == *(int *)(this + 0x10)) goto LAB_0001d940;
                ptVar36 = *(type_info **)(this + 8);
                *piVar19 = iVar7 + 1;
                if (ptVar36 == (type_info *)0x0) goto LAB_0001d95a;
                goto LAB_0001d6a6;
              }
              *(int *)(this + 0xc) = iVar8 + 1;
              pcVar12 = (char *)piVar19[iVar8 + 1];
            }
            std::string::assign(pcVar12,(uint)pvVar17);
          }
          else {
            uVar10 = get_nprocs();
            uVar18 = local_218 >> 0x14;
            if ((int)uVar10 <= (int)(local_218 >> 0x14)) {
              uVar18 = uVar10;
            }
            if ((int)uVar18 < 1) {
              uVar18 = 1;
            }
            uVar18 = __aeabi_uidiv((local_218 - 1) + uVar18);
            if ((uVar18 & 7) != 0) {
              uVar18 = (uVar18 & 0xfffffff8) + 8;
            }
            uVar10 = __aeabi_uidiv((local_218 - 1) + uVar18,uVar18);
            if (uVar10 != 1) {
              if (uVar10 == 0) {
                local_1d8 = (int *)0x0;
                local_1c4 = (int *)0x0;
              }
              else {
                if (0x3fffffff < uVar10) {
                  pvVar17 = (void *)std::__throw_bad_alloc();
                  piVar5 = local_1d8;
                  if (pvVar17 != (void *)0x0) {
                    operator_delete(pvVar17);
                  }
                  while (piVar5 != local_1c4) {
                    piVar5 = local_1b8 + 1;
                    iVar8 = *local_1b8;
                    local_1b8 = piVar5;
                    if ((allocator *)(iVar8 + -0xc) != local_1e0) {
                      piVar19 = (int *)(iVar8 + -4);
                      if (*(int *)(iVar40 + DAT_0001e2b8) == 0) {
                        iVar6 = *(int *)(iVar8 + -4);
                        *(int *)(iVar8 + -4) = iVar6 + -1;
                      }
                      else {
                        DataMemoryBarrier(0x1b);
                        do {
                          ExclusiveAccess(piVar19);
                          iVar6 = *piVar19;
                          bVar2 = (bool)hasExclusiveAccess(piVar19);
                        } while (!bVar2);
                        *piVar19 = iVar6 + -1;
                        DataMemoryBarrier(0x1b);
                      }
                      if (iVar6 < 1) {
                        std::string::_Rep::_M_destroy((allocator *)(iVar8 + -0xc));
                      }
                    }
                  }
                  if (local_1d8 != (int *)0x0) {
                    operator_delete(local_1d8);
                  }
                  robopersist::PersistData::~PersistData(local_1dc);
                    /* WARNING: Subroutine does not return */
                  __cxa_end_cleanup();
                }
                local_1d8 = operator_new(uVar10 * 4);
                local_1c4 = local_1d8 + uVar10;
                piVar19 = local_1d8;
                do {
                  if (piVar19 != (int *)0x0) {
                    *piVar19 = (int)(local_1e0 + 0xc);
                  }
                  piVar19 = piVar19 + 1;
                } while (piVar19 != local_1c4);
              }
              uVar35 = 0;
              local_18c = (allocator *)0x0;
              local_188 = (allocator *)0x0;
              local_184 = (allocator *)0x0;
              piVar19 = local_1d8;
              if (0 < (int)uVar10) {
                pPVar25 = &task->state;
                local_208 = 0;
                local_1b8 = local_1d8;
                local_214 = local_1d8;
                do {
                  iVar8 = *(int *)(this + 0x18);
                  uVar39 = uVar18;
                  if (local_218 <= uVar18) {
                    uVar39 = local_218;
                  }
                  local_1a4 = uVar35;
                  local_1a0 = uVar39;
                  if (iVar8 == *(int *)(this + 0x1c)) {
                    google::protobuf::RepeatedField<unsigned_int>::Reserve
                              ((RepeatedField<unsigned_int> *)(this + 0x18),iVar8 + 1);
                    iVar8 = *(int *)(this + 0x18);
                  }
                  paVar26 = local_188;
                  uVar4 = local_1a0;
                  uVar3 = local_1a4;
                  pvVar17 = local_1a8;
                  *(int *)(this + 0x18) = iVar8 + 1;
                  *(uint *)(*(int *)(this + 0x20) + iVar8 * 4 + 4) = uVar39;
                  local_19c = local_214;
                  local_198 = (BufferedMapInfoSavStatus *)pPVar25;
                  if (local_188 == local_184) {
                    std::vector<std::thread,std::allocator<std::thread>>::
                    _M_emplace_back_aux<bool(&)(void_const*,unsigned_int,unsigned_int,std::string&,BufferedMapInfoSavStatus_const_volatile*),void_const*&,unsigned_int&,unsigned_int&,std::reference_wrapper<std::string>,BufferedMapInfoSavStatus_volatile*>
                              ((vector<std::thread,std::allocator<std::thread>> *)&local_18c,p_Var24
                               ,&local_1a8,&local_1a4,&local_1a0,(reference_wrapper *)&local_19c,
                               &local_198);
                  }
                  else {
                    if (local_188 != (allocator *)0x0) {
                      local_17c = local_214;
                      *(int *)local_188 = 0;
                      piVar11 = operator_new(0x30);
                      iVar8 = DAT_0001dbc4;
                      piVar11[1] = 1;
                      piVar11[2] = 1;
                      iVar7 = DAT_0001dbc8;
                      iVar8 = *(int *)(iVar40 + iVar8);
                      piVar11[4] = 0;
                      piVar11[5] = 0;
                      *piVar11 = iVar8 + 8;
                      piVar11[3] = *(int *)(iVar40 + iVar7) + 8;
                      iVar8 = DAT_0001dbcc;
                      piVar11[8] = uVar4;
                      piVar11[7] = (int)local_17c;
                      piVar11[6] = (int)pPVar25;
                      piVar11[9] = uVar3;
                      piVar11[10] = (int)pvVar17;
                      piVar11[0xb] = iVar33;
                      iVar8 = std::type_info::operator==
                                        (*(type_info **)(iVar40 + iVar8),
                                         *(type_info **)(iVar40 + iVar8));
                      if (iVar8 == 0) {
                        local_194 = (int *)0x0;
                      }
                      else {
                        local_194 = piVar11 + 3;
                      }
                      local_190 = piVar11;
                      std::thread::_M_start_thread
                                (paVar26,&local_194,*(undefined4 *)(iVar40 + DAT_0001dbd0));
                      piVar11 = local_190;
                      if (local_190 != (int *)0x0) {
                        if (*(int *)(iVar40 + DAT_0001dbd4) == 0) {
                          iVar8 = local_190[1];
                          local_190[1] = iVar8 + -1;
                          if (iVar8 == 1) {
                            (**(code **)(*local_190 + 8))(local_190);
                            iVar8 = piVar11[2];
                            piVar11[2] = iVar8 + -1;
                            goto LAB_0001d62e;
                          }
                        }
                        else {
                          piVar27 = local_190 + 1;
                          DataMemoryBarrier(0x1b);
                          do {
                            ExclusiveAccess(piVar27);
                            iVar8 = *piVar27;
                            bVar2 = (bool)hasExclusiveAccess(piVar27);
                          } while (!bVar2);
                          *piVar27 = iVar8 + -1;
                          DataMemoryBarrier(0x1b);
                          if (iVar8 == 1) {
                            (**(code **)(*local_190 + 8))(local_190);
                            piVar27 = piVar11 + 2;
                            DataMemoryBarrier(0x1b);
                            do {
                              ExclusiveAccess(piVar27);
                              iVar8 = *piVar27;
                              bVar2 = (bool)hasExclusiveAccess(piVar27);
                            } while (!bVar2);
                            *piVar27 = iVar8 + -1;
                            DataMemoryBarrier(0x1b);
LAB_0001d62e:
                            if (iVar8 == 1) {
                              (**(code **)(*piVar11 + 0xc))(piVar11);
                            }
                          }
                        }
                      }
                    }
                    local_188 = local_188 + 4;
                  }
                  uVar35 = uVar35 + uVar18;
                  local_218 = local_218 - uVar18;
                  local_208 = local_208 + 1;
                  local_214 = local_214 + 1;
                } while (uVar10 != local_208);
                uVar18 = 0;
                do {
                  std::thread::join();
                  if (task->state == PersistTaskEncoding) {
                    uVar35 = local_1d8[uVar18];
                    piVar11 = *(int **)(this + 0x14);
                    if (piVar11 == (int *)0x0) {
LAB_0001d874:
                      google::protobuf::internal::RepeatedPtrFieldBase::Reserve((int)(this + 8));
                      ptVar36 = *(type_info **)(this + 8);
                      **(int **)(this + 0x14) = **(int **)(this + 0x14) + 1;
                      if (ptVar36 == (type_info *)0x0) {
LAB_0001d88c:
                        pcVar12 = operator_new(4);
LAB_0001d84a:
                        *(allocator **)pcVar12 = local_1e0 + 0xc;
                      }
                      else {
LAB_0001d834:
                        if (*(int *)(ptVar36 + 0x40) != 0) {
                          google::protobuf::Arena::OnArenaAllocation
                                    (ptVar36,*(uint *)(iVar40 + DAT_0001dbe8));
                        }
                        pcVar12 = (char *)google::protobuf::internal::ArenaImpl::
                                          AllocateAlignedAndAddCleanup
                                                    ((uint)ptVar36,
                                                     (_func_void_void_ptr *)
                                                     &Elf32_Ehdr_00000000.e_ident_abiversion);
                        if (pcVar12 != (char *)0x0) goto LAB_0001d84a;
                      }
                      iVar8 = *(int *)(this + 0xc);
                      *(int *)(this + 0xc) = iVar8 + 1;
                      *(char **)(*(int *)(this + 0x14) + iVar8 * 4 + 4) = pcVar12;
                    }
                    else {
                      iVar8 = *(int *)(this + 0xc);
                      iVar7 = *piVar11;
                      if (iVar7 <= iVar8) {
                        if (iVar7 == *(int *)(this + 0x10)) goto LAB_0001d874;
                        ptVar36 = *(type_info **)(this + 8);
                        *piVar11 = iVar7 + 1;
                        if (ptVar36 == (type_info *)0x0) goto LAB_0001d88c;
                        goto LAB_0001d834;
                      }
                      *(int *)(this + 0xc) = iVar8 + 1;
                      pcVar12 = (char *)piVar11[iVar8 + 1];
                    }
                    std::string::assign(pcVar12,uVar35);
                  }
                  uVar18 = uVar18 + 1;
                } while (uVar10 != uVar18);
                if (local_188 == local_18c) {
                  if (local_18c == (allocator *)0x0) goto joined_r0x0001d788;
                }
                else {
                  iVar8 = *(int *)local_18c;
                  paVar26 = local_18c;
                  while( true ) {
                    if (iVar8 != 0) {
                    /* WARNING: Subroutine does not return */
                      std::terminate();
                    }
                    paVar26 = paVar26 + 4;
                    if (local_188 == paVar26) break;
                    iVar8 = *(int *)paVar26;
                  }
                }
                operator_delete(local_18c);
              }
joined_r0x0001d788:
              if (piVar19 != local_1c4) {
                do {
                  piVar11 = piVar19 + 1;
                  iVar8 = *piVar19;
                  piVar19 = piVar11;
                  if ((allocator *)(iVar8 + -0xc) != local_1e0) {
                    if (*(int *)(iVar40 + DAT_0001dbd4) == 0) {
                      iVar7 = *(int *)(iVar8 + -4);
                      *(int *)(iVar8 + -4) = iVar7 + -1;
                    }
                    else {
                      piVar27 = (int *)(iVar8 + -4);
                      DataMemoryBarrier(0x1b);
                      do {
                        ExclusiveAccess(piVar27);
                        iVar7 = *piVar27;
                        bVar2 = (bool)hasExclusiveAccess(piVar27);
                      } while (!bVar2);
                      *piVar27 = iVar7 + -1;
                      DataMemoryBarrier(0x1b);
                    }
                    if (iVar7 < 1) goto code_r0x0001d7d0;
                  }
                  if (local_1c4 == piVar11) break;
                } while( true );
              }
              if (local_1d8 != (int *)0x0) {
                operator_delete(local_1d8);
              }
              goto LAB_0001d6dc;
            }
            local_180 = local_1e0 + 0xc;
            PersistDeflateCancellable(local_1a8,0,local_218,&local_180,&task->state);
            paVar26 = local_180;
            if (task->state == PersistTaskEncoding) {
              piVar19 = *(int **)(this + 0x14);
              if (piVar19 == (int *)0x0) {
LAB_0001e0b6:
                google::protobuf::internal::RepeatedPtrFieldBase::Reserve((int)(this + 8));
                piVar19 = *(int **)(this + 0x14);
                iVar7 = *piVar19;
LAB_0001da66:
                ptVar36 = *(type_info **)(this + 8);
                *piVar19 = iVar7 + 1;
                if (ptVar36 == (type_info *)0x0) {
                  pcVar12 = operator_new(4);
LAB_0001da8a:
                  *(allocator **)pcVar12 = local_1e0 + 0xc;
                }
                else {
                  if (*(int *)(ptVar36 + 0x40) != 0) {
                    google::protobuf::Arena::OnArenaAllocation
                              (ptVar36,*(uint *)(iVar40 + DAT_0001e2cc));
                  }
                  pcVar12 = (char *)google::protobuf::internal::ArenaImpl::
                                    AllocateAlignedAndAddCleanup
                                              ((uint)ptVar36,
                                               (_func_void_void_ptr *)
                                               &Elf32_Ehdr_00000000.e_ident_abiversion);
                  if (pcVar12 != (char *)0x0) goto LAB_0001da8a;
                }
                iVar8 = *(int *)(this + 0xc);
                *(int *)(this + 0xc) = iVar8 + 1;
                *(char **)(*(int *)(this + 0x14) + iVar8 * 4 + 4) = pcVar12;
              }
              else {
                iVar8 = *(int *)(this + 0xc);
                iVar7 = *piVar19;
                if (iVar7 <= iVar8) {
                  if (iVar7 == *(int *)(this + 0x10)) goto LAB_0001e0b6;
                  goto LAB_0001da66;
                }
                *(int *)(this + 0xc) = iVar8 + 1;
                pcVar12 = (char *)piVar19[iVar8 + 1];
              }
              std::string::assign(pcVar12,(uint)paVar26);
            }
            if (local_180 + -0xc != local_1e0) {
              if (*(int *)(iVar40 + DAT_0001dbd4) == 0) {
                iVar8 = *(int *)(local_180 + -4);
                *(int *)(local_180 + -4) = iVar8 + -1;
              }
              else {
                paVar26 = local_180 + -4;
                DataMemoryBarrier(0x1b);
                do {
                  ExclusiveAccess(paVar26);
                  iVar8 = *(int *)paVar26;
                  bVar2 = (bool)hasExclusiveAccess(paVar26);
                } while (!bVar2);
                *(int *)paVar26 = iVar8 + -1;
                DataMemoryBarrier(0x1b);
              }
              if (iVar8 < 1) {
                std::string::_Rep::_M_destroy(local_180 + -0xc);
              }
            }
          }
LAB_0001d6dc:
          local_1cc = local_1cc + 1;
          if ((int)uVar23 <= local_1cc || task->state != PersistTaskEncoding) {
            if (task->state != PersistTaskEncoding) goto LAB_0001d1d0;
            goto LAB_0001d992;
          }
          iVar8 = *(int *)(local_1c8 + 0x2a);
          iVar7 = local_1d4->regions[1].region_id;
          PVar1 = *(PersistRegionInfo *)(local_1c8 + 0x2c);
          local_1d4 = (PersistMapTaskView *)&local_1d4->destination_mask;
          PVar38 = *(PersistRegionInfo *)((int)local_1c8 + 0x59);
          local_1c8 = local_1c8 + 0x12;
        } while (iVar7 == iVar8);
      }
      else {
        local_1cc = 0;
      }
      _rrlogm(0x15,3,0x195,DAT_0001dbe4 + 0x1d74a,DAT_0001dbe0 + 0x1d876,DAT_0001dbdc + 0x1d736,
              local_1cc,iVar8,iVar7);
    }
    else {
      _rrlogm(0x15,3,0x189,DAT_0001dc0c + 0x1da3c,DAT_0001dc04 + 0x1db60,DAT_0001dc08 + 0x1da34,
              uVar23,*(uint *)(local_1c8 + 0x16));
    }
    iVar8 = rrlog_get_model_ver();
    if (iVar8 == 2) {
LAB_0001d756:
                    /* WARNING: Subroutine does not return */
      abort();
    }
  }
  else {
    if (task->state == PersistTaskCanceled) {
      _rrlogm(0x15,7,0x16f,iVar34,iVar33,DAT_0001dba8 + 0x1d2c2,task->task_index);
    }
    else {
      _rrlogm(0x15,3,0x173,iVar34,iVar33,DAT_0001db88 + 0x1d1a4,task->state,task->task_index);
      iVar8 = rrlog_get_model_ver();
      if (iVar8 == 2) goto LAB_0001d756;
    }
    if (iVar7 == 0) {
      pthread_mutex_unlock((pthread_mutex_t *)(*(int *)(DAT_0001dba4 + 0x1d29c) + 0x1b0));
      robopersist::PersistData::PersistData(aPStack_168);
    }
    else {
      robopersist::PersistData::PersistData(aPStack_168);
    }
  }
LAB_0001d1d0:
  local_1dc = aPStack_168;
  iVar8 = PersistLockRobust((void *)(*(int *)(DAT_0001db8c + 0x1d1dc) + 0x1b0),-1);
  if (task->buffer_mapping != (void *)0x0) {
    munmap(task->buffer_mapping,task->buffer_length);
    task->buffer_mapping = (void *)0x0;
    task->buffer_length = 0;
  }
  if (-1 < task->buffer_fd) {
    close(task->buffer_fd);
    task->buffer_fd = -1;
  }
  _rrlogm(0x15,7,0x21a,DAT_0001db98 + 0x1d240,DAT_0001db90 + 0x1d364,DAT_0001db94 + 0x1d238,
          task->state,0);
  task->state = PersistTaskIdle;
  if (iVar8 == 0) {
    pthread_mutex_unlock((pthread_mutex_t *)(*(int *)(DAT_0001dba0 + 0x1d286) + 0x1b0));
  }
  if (iVar6 == 0) {
    pthread_mutex_unlock((pthread_mutex_t *)task->task_mutex_storage);
  }
  sem_post(*(sem_t **)(DAT_0001db9c + 0x1d262));
  robopersist::PersistData::~PersistData(local_1dc);
  if (local_2c != *piVar5) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return (void *)0x0;
code_r0x0001d7d0:
  std::string::_Rep::_M_destroy((allocator *)(iVar8 + -0xc));
  goto joined_r0x0001d788;
}

