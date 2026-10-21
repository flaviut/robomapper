/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0001bb20
 */

/* Boolean means snapshot/enqueue accepted, NOT file save completed. Locks type-0 metadata; no
   subscriptions returns true without a write. Converts flags to bits at flag+8 and cancels older
   destinations. Capacity loop has outer 20000 ms deadline, 50 ms semaphore timedwait probes.
   Selects state 0 or UNKNOWN 6; cleans state-6 mapping/fd before reuse, sets state 1 and owner PID.
   Copies 0x468-byte metadata; payload starts at 0x470 and each region allocation rounds to 16
   bytes. Each region has its OWN lock, callbacks 2/copy/3/unlock; not an atomic multi-region
   snapshot. Publishes fd/mapping/length, state 2; pthread_create passes root+8 task pointer and
   then pthread_detach, with no join. Allocation/thread failures reset state 0 and return false. */

bool PersistSaveMapInfo(void *flags_vector)

{
  bool bVar1;
  PersistBufferRootView *pPVar2;
  uint uVar3;
  __pid_t _Var4;
  long lVar5;
  int iVar6;
  int *piVar7;
  char *pcVar8;
  undefined4 uVar9;
  undefined4 *puVar10;
  char *pcVar11;
  char *pcVar12;
  void *__src;
  int iVar13;
  size_t __n;
  pthread_t *__newthread;
  uint uVar14;
  uint uVar15;
  int iVar16;
  int iVar17;
  size_t sVar18;
  int iVar19;
  int *piVar20;
  allocator *paVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  int iVar25;
  size_t __len;
  int iVar26;
  void *pvVar27;
  void *pvVar28;
  int iVar29;
  bool bVar30;
  longlong lVar31;
  undefined8 uVar32;
  longlong lVar33;
  undefined4 uVar34;
  int local_b8;
  uint local_a4;
  char *local_64;
  PersistInfoLockGuard aPStack_60 [4];
  void *local_5c;
  timespec local_58;
  undefined1 local_50 [4];
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 local_30;
  int local_2c;
  
  iVar19 = DAT_0001c444 + 0x1bb2c;
  piVar20 = *(int **)(iVar19 + DAT_0001c448);
  local_2c = *piVar20;
  lVar31 = get_cur_time_ms();
  PersistInfoLockGuard::PersistInfoLockGuard(aPStack_60,0);
  if (local_5c == (void *)0x0) {
    uVar9 = 0x28b;
    iVar6 = DAT_0001c530 + 0x1c214;
    iVar22 = DAT_0001c534 + 0x1c216;
    iVar19 = DAT_0001c538 + 0x1c218;
LAB_0001c090:
    _rrlogm(0x15,3,uVar9,iVar19,iVar22 + 0xcc,iVar6);
LAB_0001bc74:
    bVar30 = false;
    goto LAB_0001bc76;
  }
  if (*(int *)((int)local_5c + 0x2c) == 0) {
    _rrlogm(0x15,4,0x290,DAT_0001c478 + 0x1bcac,DAT_0001c470 + 0x1bd72,DAT_0001c474 + 0x1bca8);
    bVar30 = true;
    goto LAB_0001bc76;
  }
  pPVar2 = GetBufferedMapInfoRoot();
  if ((pPVar2 == (PersistBufferRootView *)0x0) || (*(int *)(DAT_0001c44c + 0x1bb80) == 0)) {
    uVar9 = 0x296;
    iVar6 = DAT_0001c500 + 0x1c08e;
    iVar22 = DAT_0001c504 + 0x1c090;
    iVar19 = DAT_0001c508 + 0x1c092;
    goto LAB_0001c090;
  }
  uVar3 = ConvertMapFlagMask(flags_vector);
  CancelSavingTasksForMaps(uVar3);
  _Var4 = getpid();
  lVar5 = syscall(0xe0);
  GetMapFlagsNames((vector *)&local_64);
  pcVar11 = local_64;
  _rrlogm(0x15,6,0x29d,DAT_0001c458 + 0x1bbd8,DAT_0001c450 + 0x1bc8e,DAT_0001c454 + 0x1bbcc,_Var4,
          lVar5,local_64,*(undefined4 *)((int)local_5c + 0x2c));
  paVar21 = *(allocator **)(iVar19 + DAT_0001c45c);
  if ((allocator *)(local_64 + -0xc) != paVar21) {
    if (*(int *)(iVar19 + DAT_0001c4d4) == 0) {
      iVar22 = *(int *)(local_64 + -4);
      *(int *)(local_64 + -4) = iVar22 + -1;
    }
    else {
      piVar7 = (int *)(local_64 + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar7);
        iVar22 = *piVar7;
        bVar30 = (bool)hasExclusiveAccess(piVar7);
      } while (!bVar30);
      *piVar7 = iVar22 + -1;
      DataMemoryBarrier(0x1b);
    }
    if (iVar22 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_64 + -0xc));
    }
  }
  iVar22 = DAT_0001c460;
  uVar14 = (uint)((ulonglong)(lVar31 + 20000) >> 0x20);
  local_b8 = -1;
  do {
    while( true ) {
      uVar32 = get_cur_time_ms();
      uVar15 = (uint)((ulonglong)uVar32 >> 0x20);
      bVar30 = uVar15 <= uVar14;
      if (uVar14 == uVar15) {
        bVar30 = (uint)uVar32 <= (uint)(lVar31 + 20000);
      }
      if (!bVar30) {
        lVar33 = get_cur_time_ms();
        _rrlogm(0x15,3,0x2e3,DAT_0001c46c + 0x1bc72,DAT_0001c468 + 0x1bd30,DAT_0001c464 + 0x1bc50,
                lVar33 - lVar31);
        goto LAB_0001bc74;
      }
      local_58.tv_sec = 0;
      local_58.tv_nsec = 0;
      clock_gettime(0,&local_58);
      iVar6 = local_58.tv_nsec + 50000000;
      if (999999999 < local_58.tv_nsec + 50000000) {
        local_58.tv_sec = local_58.tv_sec + 1;
        iVar6 = local_58.tv_nsec + -950000000;
      }
      local_58.tv_nsec = iVar6;
      iVar6 = sem_timedwait(*(sem_t **)(iVar22 + 0x1bc0e),&local_58);
      if (iVar6 == 0) break;
      piVar7 = __errno_location();
      iVar6 = *piVar7;
      if (iVar6 == 0x6e) {
        CheckBlockedSaveTask();
      }
      else if (iVar6 != 4) {
        pcVar8 = strerror(iVar6);
        _rrlogm(0x15,3,0x2de,DAT_0001c484 + 0x1bd18,DAT_0001c47c + 0x1bdde,DAT_0001c480 + 0x1bd16,
                pcVar8);
      }
    }
    iVar6 = PersistLockRobust((void *)(*(int *)(DAT_0001c488 + 0x1bd32) + 0x1b0),-1);
    iVar25 = *(int *)(DAT_0001c48c + 0x1bd44);
    if (*(int *)(iVar25 + 0x10) == 0 || *(int *)(iVar25 + 0x10) == 6) {
      if (*(int *)(iVar25 + 0x10) == 6) {
        if (*(void **)(iVar25 + 0x188) != (void *)0x0) {
          munmap(*(void **)(iVar25 + 0x188),*(size_t *)(iVar25 + 0x18c));
          *(undefined4 *)(iVar25 + 0x188) = 0;
          *(undefined4 *)(iVar25 + 0x18c) = 0;
        }
        if (-1 < *(int *)(iVar25 + 0x184)) {
          close(*(int *)(iVar25 + 0x184));
          *(undefined4 *)(iVar25 + 0x184) = 0xffffffff;
        }
        _rrlogm(0x15,7,0x2c4,DAT_0001c4e4 + 0x1bfde,DAT_0001c4dc + 0x1c094,DAT_0001c4e0 + 0x1bfd6,
                *(undefined4 *)(iVar25 + 0x10),0);
        *(undefined4 *)(iVar25 + 0x10) = 0;
      }
      local_b8 = PersistLockRobust((void *)(iVar25 + 400),1000);
      lVar5 = 1;
      _rrlogm(0x15,7,0x2c8,DAT_0001c4f0 + 0x1c01a,DAT_0001c4e8 + 0x1c0d0,DAT_0001c4ec + 0x1c012,
              *(undefined4 *)(iVar25 + 0x10),1);
      *(undefined4 *)(iVar25 + 0x10) = 1;
      _Var4 = getpid();
      iVar29 = 0;
      *(uint *)(iVar25 + 0x14) = uVar3;
      *(__pid_t *)(iVar25 + 0xc) = _Var4;
    }
    else {
      CheckBlockedSaveTask();
      iVar29 = -1;
    }
    if (iVar6 == 0) {
      pthread_mutex_unlock((pthread_mutex_t *)(*(int *)(DAT_0001c4d8 + 0x1bf7a) + 0x1b0));
    }
  } while (iVar29 != 0);
  _rrlogm(0x15,7,0x2e9,DAT_0001c498 + 0x1bd8e,DAT_0001c490 + 0x1be46,DAT_0001c494 + 0x1bd82,0,lVar5)
  ;
  iVar22 = *(int *)(DAT_0001c49c + 0x1bda0);
  *(undefined4 *)(iVar22 + 0x180) = *(undefined4 *)((int)local_5c + 0x2c);
  if (*(int *)((int)local_5c + 0x2c) == 0) {
    __len = 0x470;
  }
  else {
    uVar3 = 0;
    __len = 0x470;
    iVar6 = iVar22;
    pvVar27 = local_5c;
    do {
      uVar9 = *(undefined4 *)((int)pvVar27 + 0x30);
      *(size_t *)(iVar6 + 0x1c) = __len;
      *(undefined4 *)(iVar6 + 0x18) = uVar9;
      iVar25 = GetSharedRegionSize();
      *(int *)(iVar6 + 0x20) = iVar25;
      uVar3 = uVar3 + 1;
      pvVar27 = (void *)((int)pvVar27 + 0x24);
      __len = __len + (iVar25 + 0xfU & 0xfffffff0);
      iVar6 = iVar6 + 0xc;
    } while (uVar3 < *(uint *)((int)local_5c + 0x2c));
  }
  __gnu_cxx::__to_xstring<std::string,char>
            ((__gnu_cxx *)&local_58,
             *(_func_int_char_ptr_uint_char_ptr___va_list **)(iVar19 + DAT_0001c4a0),0x10,
             (char *)(DAT_0001c4a4 + 0x1bdf8),0);
  puVar10 = (undefined4 *)std::string::insert((uint)&local_58,(char *)0x0,DAT_0001c4a8 + 0x1be0c);
  pcVar8 = (char *)*puVar10;
  *puVar10 = paVar21 + 0xc;
  if ((allocator *)(local_58.tv_sec + -0xc) != paVar21) {
    if (*(int *)(iVar19 + DAT_0001c4d4) == 0) {
      iVar6 = *(int *)(local_58.tv_sec + -4);
      *(int *)(local_58.tv_sec + -4) = iVar6 + -1;
    }
    else {
      piVar7 = (int *)(local_58.tv_sec + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar7);
        iVar6 = *piVar7;
        bVar30 = (bool)hasExclusiveAccess(piVar7);
      } while (!bVar30);
      *piVar7 = iVar6 + -1;
      DataMemoryBarrier(0x1b);
    }
    if (iVar6 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_58.tv_sec + -0xc));
    }
  }
  iVar6 = shm_open(pcVar8,0x42,0x180);
  if (iVar6 < 0) {
    piVar7 = __errno_location();
    iVar25 = DAT_0001c4f4 + 0x1c04e;
    pcVar12 = strerror(*piVar7);
    _rrlogm(0x15,3,0x2fc,DAT_0001c4fc + 0x1c070,DAT_0001c4f8 + 0x1c12c,iVar25,pcVar8,pcVar12);
LAB_0001be7e:
    if (-1 < iVar6) {
LAB_0001be84:
      close(iVar6);
    }
    iVar6 = PersistLockRobust((void *)(*(int *)(DAT_0001c4b8 + 0x1be96) + 0x1b0),-1);
    uVar9 = 0;
    _rrlogm(0x15,7,0x34b,DAT_0001c4c4 + 0x1bec4,DAT_0001c4bc + 0x1bf88,DAT_0001c4c0 + 0x1bebe,
            *(undefined4 *)(iVar22 + 0x10),0,pcVar11);
    *(undefined4 *)(iVar22 + 0x10) = 0;
    if (iVar6 == 0) {
      pthread_mutex_unlock((pthread_mutex_t *)(*(int *)(DAT_0001c568 + 0x1c31a) + 0x1b0));
    }
    if (local_b8 == 0) {
      pthread_mutex_unlock((pthread_mutex_t *)(iVar22 + 400));
    }
    _Var4 = getpid();
    _rrlogm(0x15,7,0x34f,DAT_0001c4d0 + 0x1bf10,DAT_0001c4c8 + 0x1bfd6,DAT_0001c4cc + 0x1bf0e,_Var4,
            uVar9);
    bVar30 = false;
  }
  else {
    iVar25 = ftruncate(iVar6,__len);
    if (iVar25 != 0) {
      piVar7 = __errno_location();
      iVar25 = DAT_0001c4ac + 0x1be54;
      pcVar11 = strerror(*piVar7);
      _rrlogm(0x15,3,0x301,DAT_0001c4b4 + 0x1be78,DAT_0001c4b0 + 0x1bf32,iVar25,pcVar8,__len,pcVar11
             );
      goto LAB_0001be7e;
    }
    pvVar27 = mmap((void *)0x0,__len,3,1,iVar6,0);
    if (pvVar27 == (void *)0xffffffff) {
      piVar7 = __errno_location();
      iVar25 = DAT_0001c56c + 0x1c3b6;
      pcVar11 = strerror(*piVar7);
      _rrlogm(0x15,3,0x306,DAT_0001c574 + 0x1c3d6,DAT_0001c570 + 0x1c492,iVar25,pcVar8,__len,pcVar11
             );
      goto LAB_0001be7e;
    }
    memcpy(pvVar27,local_5c,0x468);
    if (*(int *)((int)local_5c + 0x2c) != 0) {
      iVar16 = DAT_0001c50c + 0x1c1aa;
      iVar23 = DAT_0001c514 + 0x1c1be;
      iVar29 = DAT_0001c510 + 0x1c0f6;
      iVar17 = DAT_0001c518 + 0x1c0f8;
      local_a4 = 0;
      iVar25 = iVar22;
      pvVar28 = local_5c;
      do {
        iVar24 = *(int *)(iVar25 + 0x18);
        iVar26 = *(int *)(iVar25 + 0x1c);
        iVar13 = *(int *)((int)pvVar28 + 0x30);
        uStack_4c = *(undefined4 *)((int)pvVar28 + 0x34);
        uStack_48 = *(undefined4 *)((int)pvVar28 + 0x38);
        uStack_44 = *(undefined4 *)((int)pvVar28 + 0x3c);
        local_40 = *(undefined4 *)((int)pvVar28 + 0x40);
        uStack_3c = *(undefined4 *)((int)pvVar28 + 0x44);
        uStack_38 = *(undefined4 *)((int)pvVar28 + 0x48);
        uStack_34 = *(undefined4 *)((int)pvVar28 + 0x4c);
        sVar18 = *(size_t *)(iVar25 + 0x20);
        local_30 = *(undefined4 *)((int)pvVar28 + 0x50);
        __n = GetSharedRegionSize(iVar13);
        if (__n != sVar18 || iVar13 != iVar24) {
          _rrlogm(0x15,3,0x315,DAT_0001c52c + 0x1c1ea,DAT_0001c524 + 0x1c2a4,DAT_0001c528 + 0x1c1e2,
                  iVar13,iVar24);
          iVar25 = rrlog_get_model_ver();
          if (iVar25 == 2) {
                    /* WARNING: Subroutine does not return */
            abort();
          }
          if ((int)pvVar27 - 1U < 0xfffffffe) goto LAB_0001c2c2;
          goto LAB_0001be7e;
        }
        SharedRegionLockGuard::SharedRegionLockGuard((SharedRegionLockGuard *)&local_58,0,iVar13);
        RunPersistSharedRegionCallback(local_50,2);
        __src = (void *)GetSharedRegion(iVar13,sVar18);
        memcpy((void *)((int)pvVar27 + iVar26),__src,__n);
        _rrlogm(0x15,7,799,iVar29,iVar16,iVar17,__n,iVar26);
        RunPersistSharedRegionCallback(local_50,3);
        _rrlogm(0x15,7,0x324,DAT_0001c520 + 0x1c168,iVar23,DAT_0001c51c + 0x1c15c,iVar13,__n);
        pvVar28 = (void *)((int)pvVar28 + 0x24);
        SharedRegionLockGuard::~SharedRegionLockGuard((SharedRegionLockGuard *)&local_58);
        iVar25 = iVar25 + 0xc;
        local_a4 = local_a4 + 1;
      } while (local_a4 < *(uint *)((int)local_5c + 0x2c));
    }
    iVar29 = DAT_0001c53c + 0x1c300;
    iVar16 = DAT_0001c540 + 0x1c23e;
    iVar25 = DAT_0001c544 + 0x1c244;
    *(int *)(iVar22 + 0x184) = iVar6;
    *(size_t *)(iVar22 + 0x18c) = __len;
    *(void **)(iVar22 + 0x188) = pvVar27;
    uVar9 = *(undefined4 *)(iVar22 + 0x10);
    uVar34 = 2;
    _rrlogm(0x15,7,0x32c,iVar25,iVar29,iVar16,uVar9,2);
    iVar29 = DAT_0001c54c;
    iVar25 = DAT_0001c548;
    __newthread = (pthread_t *)(DAT_0001c548 + 0x1c28c);
    *(undefined4 *)(iVar22 + 0x10) = 2;
    iVar29 = pthread_create(__newthread,(pthread_attr_t *)0x0,(__start_routine *)(iVar29 + 0x1c292),
                            (void *)(iVar22 + 8));
    if (iVar29 != 0) {
      _rrlogm(0x15,3,0x333,DAT_0001c558 + 0x1c2b0,DAT_0001c550 + 0x1c376,DAT_0001c554 + 0x1c2ae,
              uVar9,uVar34);
      if ((int)pvVar27 - 1U < 0xfffffffe) {
LAB_0001c2c2:
        munmap(pvVar27,__len);
        goto LAB_0001be7e;
      }
      goto LAB_0001be84;
    }
    pthread_detach(*(pthread_t *)(iVar25 + 0x1c28c));
    if (local_b8 == 0) {
      pthread_mutex_unlock((pthread_mutex_t *)(iVar22 + 400));
    }
    _Var4 = getpid();
    _rrlogm(0x15,7,0x33e,DAT_0001c564 + 0x1c2f0,DAT_0001c55c + 0x1c3b6,DAT_0001c560 + 0x1c2ee,_Var4)
    ;
    bVar30 = true;
  }
  iVar22 = get_cur_time_ms();
  rr_max_int(1,0xc,iVar22 - (int)lVar31);
  if ((allocator *)(pcVar8 + -0xc) != paVar21) {
    if (*(int *)(iVar19 + DAT_0001c4d4) == 0) {
      iVar19 = *(int *)(pcVar8 + -4);
      *(int *)(pcVar8 + -4) = iVar19 + -1;
    }
    else {
      DataMemoryBarrier(0x1b);
      piVar7 = (int *)(pcVar8 + -4);
      do {
        ExclusiveAccess(piVar7);
        iVar19 = *piVar7;
        bVar1 = (bool)hasExclusiveAccess(piVar7);
      } while (!bVar1);
      *piVar7 = iVar19 + -1;
      DataMemoryBarrier(0x1b);
    }
    if (iVar19 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(pcVar8 + -0xc));
    }
  }
LAB_0001bc76:
  PersistInfoLockGuard::~PersistInfoLockGuard(aPStack_60);
  if (local_2c != *piVar20) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return bVar30;
}

