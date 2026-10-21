/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0001b564
 */

/* Under root mutex removes matching destination bits from task mask, skipping states 0 and 6
   (UNKNOWN). Empty mask sets state 5. Does not acquire/join writer task mutex, wait for
   compression, flush files or undo prior renames. Partial cancellation preserves other
   destinations. */

void CancelSavingTasksForMaps(uint destination_mask)

{
  bool bVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  allocator *paVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int *piVar9;
  undefined4 *puVar10;
  int iVar11;
  undefined4 *puVar12;
  int iVar13;
  undefined4 uVar14;
  int iVar15;
  int iVar16;
  int local_30;
  int local_2c;
  
  iVar15 = DAT_0001b748 + 0x1b57a;
  piVar4 = *(int **)(iVar15 + DAT_0001b74c);
  iVar8 = DAT_0001b750 + 0x1b586;
  local_2c = *piVar4;
  GetMapFlagsNamesFromMask((uint)&local_30);
  _rrlogm(0x15,7,0x26d,DAT_0001b758 + 0x1b5aa,DAT_0001b754 + 0x1b614,iVar8,local_30);
  paVar5 = *(allocator **)(iVar15 + DAT_0001b75c);
  if ((allocator *)(local_30 + -0xc) != paVar5) {
    if (*(int *)(iVar15 + DAT_0001b780) == 0) {
      iVar8 = *(int *)(local_30 + -4);
      *(int *)(local_30 + -4) = iVar8 + -1;
    }
    else {
      piVar9 = (int *)(local_30 + -4);
      DataMemoryBarrier(0x1b);
      do {
        ExclusiveAccess(piVar9);
        iVar8 = *piVar9;
        bVar1 = (bool)hasExclusiveAccess(piVar9);
      } while (!bVar1);
      *piVar9 = iVar8 + -1;
      DataMemoryBarrier(0x1b);
    }
    if (iVar8 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_30 + -0xc));
    }
  }
  piVar9 = (int *)(DAT_0001b760 + 0x1b5ca);
  iVar8 = PersistLockRobust((void *)(*piVar9 + 0x1b0),-1);
  iVar11 = *piVar9;
  puVar10 = (undefined4 *)(iVar11 + 8);
  puVar12 = (undefined4 *)(iVar11 + 0x1a8);
  if (puVar10 != puVar12) {
    iVar13 = DAT_0001b764 + 0x1b662;
    iVar11 = DAT_0001b770 + 0x1b5fa;
    iVar6 = DAT_0001b768 + 0x1b66c;
    iVar16 = DAT_0001b76c + 0x1b5fe;
    do {
      while (((puVar10[2] == 0 || (puVar10[2] == 6)) || ((destination_mask & puVar10[3]) == 0))) {
LAB_0001b608:
        puVar10 = puVar10 + 0x68;
        if (puVar12 == puVar10) goto LAB_0001b68c;
      }
      uVar14 = *puVar10;
      GetMapFlagsNamesFromMask((uint)&local_30);
      uVar2 = puVar10[2];
      _rrlogm(0x15,7,0x275,iVar16,iVar13,iVar11,uVar14,local_30,uVar2);
      if ((allocator *)(local_30 + -0xc) != paVar5) {
        if (*(int *)(iVar15 + DAT_0001b780) == 0) {
          iVar3 = *(int *)(local_30 + -4);
          *(int *)(local_30 + -4) = iVar3 + -1;
        }
        else {
          piVar9 = (int *)(local_30 + -4);
          DataMemoryBarrier(0x1b);
          do {
            ExclusiveAccess(piVar9);
            iVar3 = *piVar9;
            bVar1 = (bool)hasExclusiveAccess(piVar9);
          } while (!bVar1);
          *piVar9 = iVar3 + -1;
          DataMemoryBarrier(0x1b);
        }
        if (iVar3 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_30 + -0xc));
        }
      }
      uVar7 = puVar10[3];
      puVar10[3] = uVar7 & ~destination_mask;
      if ((uVar7 & ~destination_mask) != 0) goto LAB_0001b608;
      _rrlogm(0x15,7,0x279,DAT_0001b778 + 0x1b67c,iVar6,DAT_0001b774 + 0x1b670,puVar10[2],5,uVar2);
      puVar10[2] = 5;
      puVar10 = puVar10 + 0x68;
    } while (puVar12 != puVar10);
  }
LAB_0001b68c:
  if (iVar8 == 0) {
    pthread_mutex_unlock((pthread_mutex_t *)(*(int *)(DAT_0001b77c + 0x1b696) + 0x1b0));
  }
  if (local_2c != *piVar4) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}

