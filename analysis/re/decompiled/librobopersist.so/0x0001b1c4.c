/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0001b1c4
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Restart-safety/capacity repair under root mutex: trylocks task mutex; EBUSY counts task occupied.
   EOWNERDEAD makes consistent and resets state to 0. On successful trylock, foreign-owner states
   other than 0/2/6 are reset to 0 (model-version 2 may abort). Repairs semaphore count with
   post/trywait. This is not a writer completion/durability check; state 6 remains unknown. */

void CheckBlockedSaveTask(void)

{
  bool bVar1;
  int iVar2;
  __pid_t _Var3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  int iVar10;
  undefined4 uVar11;
  int *piVar12;
  undefined4 *puVar13;
  undefined *puVar14;
  pthread_mutex_t *__mutex;
  undefined4 uVar15;
  int iVar16;
  undefined4 *puVar17;
  undefined4 uVar18;
  uint uVar19;
  undefined4 uVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  uint local_30;
  int local_2c;
  
  iVar22 = DAT_0001b504 + 0x1b1d4;
  piVar9 = *(int **)(iVar22 + DAT_0001b508);
  piVar12 = (int *)(DAT_0001b50c + 0x1b1dc);
  iVar2 = *piVar12;
  local_2c = *piVar9;
  if (iVar2 != 0) {
    iVar2 = PersistLockRobust((void *)(iVar2 + 0x1b0),-1);
    iVar16 = *piVar12;
    puVar13 = (undefined4 *)(iVar16 + 8);
    puVar17 = (undefined4 *)(iVar16 + 0x1a8);
    if (puVar13 == puVar17) {
      uVar19 = 1;
    }
    else {
      iVar7 = DAT_0001b510 + 0x1b274;
      iVar6 = DAT_0001b518 + 0x1b220;
      iVar10 = DAT_0001b514 + 0x1b27e;
      iVar8 = DAT_0001b51c + 0x1b224;
      iVar16 = 0;
      do {
        while( true ) {
          __mutex = (pthread_mutex_t *)(puVar13 + 0x62);
          iVar4 = pthread_mutex_trylock(__mutex);
          if (iVar4 != 0x10) break;
          iVar16 = iVar16 + 1;
LAB_0001b2ac:
          puVar13 = puVar13 + 0x68;
          if (puVar17 == puVar13) goto LAB_0001b336;
        }
        if (iVar4 == 0x82) {
          uVar15 = puVar13[2];
          uVar11 = puVar13[3];
          iVar23 = DAT_0001b544 + 0x1b3ea;
          uVar18 = puVar13[1];
          uVar20 = *puVar13;
          iVar21 = DAT_0001b54c + 0x1b462;
          _rrlogm(0x15,7,0x232,iVar23,iVar21,DAT_0001b548 + 0x1b3f6,uVar20,uVar18,uVar15,uVar11);
          iVar4 = pthread_mutex_consistent(__mutex);
          if (iVar4 != 0) {
            _rrlogm(0x15,3,0x236,iVar23,iVar21,DAT_0001b550 + 0x1b42c,uVar20,uVar18,uVar15,uVar11);
          }
          puVar13[2] = 0;
          pthread_mutex_unlock(__mutex);
          goto LAB_0001b2ac;
        }
        if (iVar4 == 0) {
          if ((((puVar13[2] != 0) && (puVar13[2] != 2)) && (puVar13[2] != 6)) &&
             (iVar4 = puVar13[1], _Var3 = getpid(), iVar4 != _Var3)) {
            uVar11 = puVar13[1];
            uVar15 = *puVar13;
            uVar18 = puVar13[2];
            GetMapFlagsNamesFromMask((uint)&local_30);
            _rrlogm(0x15,3,0x241,DAT_0001b524 + 0x1b284,iVar10,DAT_0001b520 + 0x1b272,uVar15,uVar18,
                    uVar11,local_30);
            if ((allocator *)(local_30 - 0xc) != *(allocator **)(iVar22 + DAT_0001b528)) {
              if (*(int *)(iVar22 + DAT_0001b554) == 0) {
                iVar4 = *(int *)(local_30 - 4);
                *(int *)(local_30 - 4) = iVar4 + -1;
              }
              else {
                piVar12 = (int *)(local_30 - 4);
                DataMemoryBarrier(0x1b);
                do {
                  ExclusiveAccess(piVar12);
                  iVar4 = *piVar12;
                  bVar1 = (bool)hasExclusiveAccess(piVar12);
                } while (!bVar1);
                *piVar12 = iVar4 + -1;
                DataMemoryBarrier(0x1b);
              }
              if (iVar4 < 1) {
                std::string::_Rep::_M_destroy((allocator *)(local_30 - 0xc));
              }
            }
            iVar4 = rrlog_get_model_ver();
            if (iVar4 == 2) goto LAB_0001b4e2;
            puVar13[2] = 0;
          }
          pthread_mutex_unlock(__mutex);
          goto LAB_0001b2ac;
        }
        pcVar5 = strerror(iVar4);
        uVar15 = *puVar13;
        uVar11 = puVar13[1];
        uVar18 = puVar13[2];
        GetMapFlagsNamesFromMask((uint)&local_30);
        _rrlogm(0x15,3,0x24a,iVar6,iVar7,iVar8,pcVar5,uVar15,uVar18,uVar11,local_30);
        if ((allocator *)(local_30 - 0xc) != *(allocator **)(iVar22 + DAT_0001b528)) {
          if (*(int *)(iVar22 + DAT_0001b554) == 0) {
            iVar4 = *(int *)(local_30 - 4);
            *(int *)(local_30 - 4) = iVar4 + -1;
          }
          else {
            piVar12 = (int *)(local_30 - 4);
            DataMemoryBarrier(0x1b);
            do {
              ExclusiveAccess(piVar12);
              iVar4 = *piVar12;
              bVar1 = (bool)hasExclusiveAccess(piVar12);
            } while (!bVar1);
            *piVar12 = iVar4 + -1;
            DataMemoryBarrier(0x1b);
          }
          if (iVar4 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_30 - 0xc));
          }
        }
        iVar4 = rrlog_get_model_ver();
        if (iVar4 == 2) {
LAB_0001b4e2:
                    /* WARNING: Subroutine does not return */
          abort();
        }
        puVar13[2] = 0;
        puVar13 = puVar13 + 0x68;
      } while (puVar17 != puVar13);
LAB_0001b336:
      uVar19 = 1 - iVar16;
    }
    iVar22 = DAT_0001b52c;
    local_30 = 0;
    iVar16 = sem_getvalue(*(sem_t **)(DAT_0001b52c + 0x1b34a),(int *)&local_30);
    if (iVar16 == 0) {
      local_30 = local_30 & ~((int)local_30 >> 0x1f);
      if (uVar19 != local_30) {
        _rrlogm(0x15,3,599,DAT_0001b538 + 0x1b37e,DAT_0001b530 + 0x1b3ca,DAT_0001b534 + 0x1b376,
                local_30,uVar19);
        iVar16 = DAT_0001b53c;
        for (; DAT_0001b53c = iVar16, (int)local_30 < (int)uVar19; local_30 = local_30 + 1) {
          sem_post(*(sem_t **)(iVar22 + 0x1b34a));
          iVar16 = DAT_0001b53c;
        }
        for (; (int)uVar19 < (int)local_30; local_30 = local_30 - 1) {
          sem_trywait(*(sem_t **)(iVar16 + 0x1b3a4));
        }
      }
    }
    else {
      piVar12 = __errno_location();
      iVar22 = DAT_0001b55c + 0x1b4a4;
      puVar14 = &UNK_0001b502 + DAT_0001b558;
      pcVar5 = strerror(*piVar12);
      _rrlogm(0x15,3,0x266,DAT_0001b560 + 0x1b4b6,puVar14,iVar22,pcVar5);
    }
    if (iVar2 == 0) {
      pthread_mutex_unlock((pthread_mutex_t *)(*(int *)(DAT_0001b540 + 0x1b3b8) + 0x1b0));
    }
  }
  if (local_2c != *piVar9) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}

