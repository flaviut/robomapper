/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0001c620
 */

/* Buffer-aware load under type-0 metadata and root mutex. States 0/5 or destination mismatch select
   ForcePersistLoad(0, filename(flag)). State 1 is an error: resets state/owner/mask to zero,
   model-version 2 aborts; otherwise returns false, NOT fallback file load. Other matching states
   (including unnamed 6) use buffer: same PID uses pointer, foreign PID opens task-index shm
   O_RDONLY and mmap(PROT_READ, MAP_SHARED). For each subscribed ID found in buffered descriptors:
   region lock, callback 0, memcpy recorded length, callback 1, unlock. Can succeed with newer data
   than file and without every subscribed ID present. Foreign-owner normal success has no local fd
   close or munmap: mmap success at 0x1ca28 branches via 0x1ca32/0x1ca3e to 0x1c778; close at
   0x1ca4a is on failure path only; common restore exits at 0x1c84a..0x1c858 then 0x1c6f2..0x1c708.
   No munmap call in this function. Worker cleanup at 0x1d1e8..0x1d212 releases its own task
   mapping/fd, not the foreign loader locals. Static local-resource observation, not proven runtime
   leak rate, safe shutdown, disk freshness or durability. */

bool PersistLoadMapInfo(int flag)

{
  bool bVar1;
  int *piVar2;
  PersistBufferRootView *pPVar3;
  int iVar4;
  uint uVar5;
  __pid_t _Var6;
  void *__dest;
  undefined4 uVar7;
  char *pcVar8;
  int iVar9;
  int *piVar10;
  undefined4 uVar11;
  int iVar12;
  char *pcVar13;
  int iVar14;
  uchar *__mutex;
  int iVar15;
  undefined4 uVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  char *__name;
  char *__n;
  undefined2 *local_68;
  uint local_64;
  undefined2 *local_4c;
  int local_40;
  PersistInfoLockGuard aPStack_3c [4];
  undefined2 *local_38;
  char *local_34 [2];
  int local_2c;
  
  iVar15 = DAT_0001cb40 + 0x1c636;
  piVar2 = *(int **)(iVar15 + DAT_0001cb44);
  iVar19 = DAT_0001cb4c + 0x1c648;
  uVar11 = *(undefined4 *)(DAT_0001cb48 + 0x1c65a);
  local_2c = *piVar2;
  iVar14 = DAT_0001cb50 + 0x1c752;
  iVar4 = flag;
  _rrlogm(0x15,6,0x368,iVar19,iVar14,DAT_0001cb54 + 0x1c662,uVar11,flag);
  PersistInfoLockGuard::PersistInfoLockGuard(aPStack_3c,0);
  if (local_38 == (undefined2 *)0x0) {
    _rrlogm(0x15,3,0x36d,iVar19,iVar14,DAT_0001cb9c + 0x1c88a,uVar11,iVar4);
  }
  else {
    pPVar3 = GetBufferedMapInfoRoot();
    if ((pPVar3 == (PersistBufferRootView *)0x0) || (*(int *)(DAT_0001cb58 + 0x1c6a0) == 0)) {
      _rrlogm(0x15,3,0x373,DAT_0001cb98 + 0x1c870,DAT_0001cb90 + 0x1c95e,DAT_0001cb94 + 0x1c86c,
              uVar11,iVar4);
    }
    else {
      __mutex = pPVar3->root_mutex_storage;
      iVar4 = PersistLockRobust(__mutex,-1);
      iVar14 = *(int *)(DAT_0001cb5c + 0x1c6ba);
      if ((*(int *)(iVar14 + 0x10) == 0) || (*(int *)(iVar14 + 0x10) == 5)) {
LAB_0001c6c2:
        if (iVar4 == 0) {
          pthread_mutex_unlock((pthread_mutex_t *)__mutex);
        }
        GetMapInfoPersistFileName(local_34,flag);
        bVar1 = ForcePersistLoad(0,local_34[0]);
        uVar5 = (uint)bVar1;
        if ((allocator *)(local_34[0] + -0xc) != *(allocator **)(iVar15 + DAT_0001cb60)) {
          if (*(int *)(iVar15 + DAT_0001cba0) == 0) {
            iVar4 = *(int *)(local_34[0] + -4);
            *(int *)(local_34[0] + -4) = iVar4 + -1;
          }
          else {
            piVar10 = (int *)(local_34[0] + -4);
            DataMemoryBarrier(0x1b);
            do {
              ExclusiveAccess(piVar10);
              iVar4 = *piVar10;
              bVar1 = (bool)hasExclusiveAccess(piVar10);
            } while (!bVar1);
            *piVar10 = iVar4 + -1;
            DataMemoryBarrier(0x1b);
          }
          if (iVar4 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_34[0] + -0xc));
          }
        }
        goto LAB_0001c6f2;
      }
      if (*(int *)(iVar14 + 0x10) == 1) {
        _rrlogm(0x15,3,0x37e,DAT_0001cbbc + 0x1c984,DAT_0001cbb4 + 0x1ca60,DAT_0001cbb8 + 0x1c972,0,
                *(undefined4 *)(iVar14 + 0xc),*(undefined4 *)(iVar14 + 0x14));
        *(undefined4 *)(iVar14 + 0x10) = 0;
        *(undefined4 *)(iVar14 + 0xc) = 0;
        *(undefined4 *)(iVar14 + 0x14) = 0;
        iVar14 = rrlog_get_model_ver();
        if (iVar14 == 2) {
                    /* WARNING: Subroutine does not return */
          abort();
        }
      }
      else {
        uVar5 = CheckMapFlagMask(*(uint *)(iVar14 + 0x14),flag);
        if (uVar5 == 0) goto LAB_0001c6c2;
        pcVar8 = *(char **)(iVar14 + 0xc);
        __n = (char *)0x0;
        _rrlogm(0x15,7,0x387,DAT_0001cb6c + 0x1c758,DAT_0001cb64 + 0x1c834,DAT_0001cb68 + 0x1c74e,
                flag,0,pcVar8);
        iVar19 = *(int *)(iVar14 + 0xc);
        _Var6 = getpid();
        if (iVar19 == _Var6) {
          local_4c = *(undefined2 **)(iVar14 + 0x188);
LAB_0001c778:
          _rrlogm(0x15,6,0x3a8,DAT_0001cb78 + 0x1c79a,DAT_0001cb70 + 0x1c87e,DAT_0001cb74 + 0x1c78e,
                  *(undefined4 *)(local_38 + 0x16),__n,pcVar8);
          *local_38 = *local_4c;
          uVar16 = *(undefined4 *)(local_4c + 3);
          uVar11 = *(undefined4 *)(local_4c + 5);
          uVar7 = *(undefined4 *)(local_4c + 7);
          *(undefined4 *)(local_38 + 1) = *(undefined4 *)(local_4c + 1);
          *(undefined4 *)(local_38 + 3) = uVar16;
          *(undefined4 *)(local_38 + 5) = uVar11;
          *(undefined4 *)(local_38 + 7) = uVar7;
          local_38[9] = local_4c[9];
          if (*(int *)(local_38 + 0x16) != 0) {
            local_64 = 0;
            iVar15 = DAT_0001cb7c + 0x1c8c4;
            iVar9 = DAT_0001cb80 + 0x1c8ce;
            iVar12 = DAT_0001cb84 + 0x1c8d2;
            iVar19 = DAT_0001cb88 + 0x1c7e4;
            local_68 = local_38;
            do {
              _rrlogm(0x15,7,0x3ae,iVar19,iVar15,DAT_0001cb8c + 0x1c7fc,
                      *(undefined4 *)(local_68 + 0x18),__n);
              if (*(int *)(iVar14 + 0x180) != 0) {
                iVar20 = *(int *)(local_68 + 0x18);
                if (*(int *)(iVar14 + 0x18) == iVar20) {
                  iVar17 = 0;
                }
                else {
                  iVar17 = 0;
                  iVar18 = iVar14;
                  do {
                    iVar17 = iVar17 + 1;
                    if (iVar17 == *(int *)(iVar14 + 0x180)) goto LAB_0001c834;
                    piVar10 = (int *)(iVar18 + 0x24);
                    iVar18 = iVar18 + 0xc;
                  } while (*piVar10 != iVar20);
                }
                SharedRegionLockGuard::SharedRegionLockGuard
                          ((SharedRegionLockGuard *)local_34,0,iVar20);
                RunPersistSharedRegionCallback(local_68 + 0x18,0);
                __n = *(char **)(iVar17 * 0xc + iVar14 + 0x20);
                __dest = (void *)GetSharedRegion(iVar20);
                iVar18 = iVar17 * 0xc + iVar14;
                memcpy(__dest,(void *)(*(int *)(iVar18 + 0x1c) + (int)local_4c),(size_t)__n);
                _rrlogm(0x15,7,0x3ba,DAT_0001cba8 + 0x1c920,iVar9,DAT_0001cba4 + 0x1c912,__n,
                        *(undefined4 *)(iVar18 + 0x1c));
                RunPersistSharedRegionCallback(local_68 + 0x18,1);
                _rrlogm(0x15,7,0x3c7,DAT_0001cbb0 + 0x1c94c,iVar12,DAT_0001cbac + 0x1c93e,iVar20,__n
                       );
                SharedRegionLockGuard::~SharedRegionLockGuard((SharedRegionLockGuard *)local_34);
              }
LAB_0001c834:
              local_64 = local_64 + 1;
              local_68 = local_68 + 0x12;
            } while (local_64 < *(uint *)(local_38 + 0x16));
          }
          if (iVar4 == 0) {
            pthread_mutex_unlock((pthread_mutex_t *)__mutex);
          }
          goto LAB_0001c6f2;
        }
        __gnu_cxx::__to_xstring<std::string,char>
                  ((__gnu_cxx *)&local_40,
                   *(_func_int_char_ptr_uint_char_ptr___va_list **)(iVar15 + DAT_0001cbc0),0x10,
                   (char *)(DAT_0001cbc4 + 0x1c9d0),0);
        piVar10 = (int *)std::string::insert((uint)&local_40,(char *)0x0,DAT_0001cbc8 + 0x1c9e2);
        __name = (char *)*piVar10;
        pcVar13 = *(char **)(iVar15 + DAT_0001cb60);
        *piVar10 = (int)(pcVar13 + 0xc);
        if ((char *)(local_40 + -0xc) != pcVar13) {
          FUN_0000ddf8((char *)(local_40 + -0xc),local_34);
        }
        iVar15 = shm_open(__name,0,0x100);
        if (iVar15 < 0) {
          piVar10 = __errno_location();
          iVar19 = DAT_0001cbd8 + 0x1ca78;
          __n = strerror(*piVar10);
          flag = (int)__name;
          _rrlogm(0x15,3,0x395,DAT_0001cbe0 + 0x1ca96,DAT_0001cbdc + 0x1cb7e,iVar19,__name,__n);
          local_4c = (undefined2 *)0x0;
LAB_0001caa0:
          if (__name + -0xc != pcVar13) {
            bVar1 = true;
            goto LAB_0001ca36;
          }
        }
        else {
          bVar1 = false;
          local_4c = mmap((void *)0x0,*(size_t *)(iVar14 + 0x18c),1,1,iVar15,0);
          if (local_4c == (undefined2 *)0xffffffff) {
            piVar10 = __errno_location();
            __n = *(char **)(iVar14 + 0x18c);
            iVar19 = DAT_0001cbe4 + 0x1caca;
            pcVar8 = strerror(*piVar10);
            flag = (int)__name;
            _rrlogm(0x15,3,0x39a,DAT_0001cbec + 0x1caec,DAT_0001cbe8 + 0x1cbce,iVar19,__name,__n,
                    pcVar8);
            goto LAB_0001caa0;
          }
          if (__name + -0xc == pcVar13) goto LAB_0001c778;
LAB_0001ca36:
          FUN_0000ddf8(__name + -0xc,local_34);
          if (!bVar1) goto LAB_0001c778;
        }
        if (-1 < iVar15) {
          close(iVar15);
        }
        _rrlogm(0x15,3,0x3a4,DAT_0001cbd4 + 0x1ca64,DAT_0001cbcc + 0x1cb52,DAT_0001cbd0 + 0x1ca62,
                flag,__n,pcVar8);
      }
      if (iVar4 == 0) {
        pthread_mutex_unlock((pthread_mutex_t *)__mutex);
        uVar5 = 0;
        goto LAB_0001c6f2;
      }
    }
  }
  uVar5 = 0;
LAB_0001c6f2:
  PersistInfoLockGuard::~PersistInfoLockGuard(aPStack_3c);
  if (local_2c != *piVar2) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return SUB41(uVar5,0);
}

