/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrslamdrv.so
 * SHA256: b48f5f56eb1b2d22abbf727725ea558762337f8f0103229d8da6c1ab6275608a
 * Function VA: 0x0001718c
 */

/* Storage boundary only; surviving unknown name/signature retained. Reset branch calls
   GridDropSavedCaches at0x172f2. A distinct saved-grid branch drops flags1..11 at0x175b8, reads
   selected flag from unknown owner state+0x15b0 then record+4, calls GridGetSavedBuffer at0x175cc,
   copies selected grid or fallback, and drops caches again at0x17646. This branch forces fresh
   saved-grid read; not proof all load paths do. No mutex call observed in this boundary.
   State/transform/algorithm semantics and unknown owner offsets intentionally not recovered.
   Decompiler aliases to imported string/symbol storage in owner-relative expressions are analysis
   artifacts, not literal accesses. */

void FUN_0001718c(int param_1,int param_2)

{
  undefined8 uVar1;
  void *pvVar2;
  char *pcVar3;
  float *pfVar4;
  char *pcVar5;
  int *piVar6;
  uint *puVar7;
  uint uVar8;
  uchar *puVar9;
  uchar *puVar10;
  uchar *puVar11;
  uint uVar12;
  GridCacheMeta *pGVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  GridBufferRef *pGVar17;
  bool bVar18;
  float fVar19;
  GridBufferRef local_68;
  GridBufferRef local_5c;
  float local_50;
  float local_4c;
  float local_48;
  GridBufferRef local_44;
  int local_34;
  
  iVar16 = DAT_000176b0 + 0x171a4;
  piVar6 = *(int **)(iVar16 + DAT_000176b4);
  local_34 = *piVar6;
  if (param_2 == 0) {
    iVar14 = DAT_000176b8 + 0x171bc;
  }
  else {
    iVar14 = DAT_000176dc + 0x1736c;
  }
  puVar7 = *(uint **)(iVar16 + DAT_000176bc);
  if (6 < *puVar7) {
    (*(code *)**(undefined4 **)(iVar16 + DAT_000176c0))
              (4,7,0x35c,DAT_000176c4 + 0x1748c,DAT_000176c8 + 0x171e6,iVar14);
  }
  pvVar2 = (void *)FUN_00026e80();
  GridCellSet((uchar *)&local_50,0x80);
  local_44.cells = Elf32_Ehdr_00000000.e_ident_pad;
  GridGetBuffer(&local_68,pvVar2,(int *)&local_44,(uchar *)&local_50);
  pvVar2 = (void *)FUN_00026e80();
  GridCellSet((uchar *)&local_50,0x80);
  local_44.cells = Elf32_Ehdr_00000000.e_ident_pad + 2;
  GridGetBuffer(&local_5c,pvVar2,(int *)&local_44,(uchar *)&local_50);
  pcVar5 = *(char **)("_ZSt17current_exceptionv" + param_1 + 4);
  iVar14 = *(int *)("_ZSt17current_exceptionv" + param_1);
  uVar12 = ((int)pcVar5 - iVar14 >> 2) * -0x11111111;
  if (param_2 == 0) {
    "_ZNSt15__exception_ptr13exception_ptr4swapERS0_"[param_1 + 0x2b] = '\0';
    if (uVar12 == 0) {
      if (5 < *puVar7) {
        (*(code *)**(undefined4 **)(iVar16 + DAT_000176c0))
                  (4,6,0x366,DAT_000176d0 + 0x17542,DAT_000176cc + 0x17292,0);
      }
      iVar16 = FUN_000221c4(local_5c.metadata,local_68.metadata);
      if (iVar16 == 0) {
        GridRectMergeInto(&(local_5c.metadata)->view,&(local_68.metadata)->view);
        uVar12 = GridRectCellCount(&(local_5c.metadata)->bounds);
        if (0 < (int)uVar12) {
          local_5c.cells = local_5c.cells + -1;
          puVar9 = local_68.cells;
          do {
            puVar11 = puVar9 + 1;
            local_5c.cells = local_5c.cells + 1;
            *local_5c.cells = *puVar9;
            puVar9 = puVar11;
          } while (local_68.cells + uVar12 != puVar11);
        }
      }
      iVar15 = *(int *)("_ZNSt18condition_variable4waitERSt11unique_lockISt5mutexE" + param_1 + 1);
      iVar14 = *(int *)("_ZNSt18condition_variable4waitERSt11unique_lockISt5mutexE" + param_1 + 5);
      "__cxa_guard_abort"[param_1 + 0xb] = '\0';
      pcVar5 = "__cxa_guard_abort" + param_1 + 0xf;
      pcVar5[0] = '\0';
      pcVar5[1] = '\0';
      pcVar5[2] = '\0';
      pcVar5[3] = '\0';
      iVar16 = iVar15;
      if (iVar15 != iVar14) {
        do {
          if (*(void **)(iVar16 + 0x28) != (void *)0x0) {
            operator_delete(*(void **)(iVar16 + 0x28));
          }
          if (*(void **)(iVar16 + 0x14) != (void *)0x0) {
            operator_delete(*(void **)(iVar16 + 0x14));
          }
          iVar16 = iVar16 + 0x38;
        } while (iVar14 != iVar16);
        *(int *)("_ZNSt18condition_variable4waitERSt11unique_lockISt5mutexE" + param_1 + 5) = iVar15
        ;
      }
      GridDropSavedCaches();
    }
    else {
      if (1 < uVar12) {
        uVar8 = *puVar7;
        if (5 < uVar8) {
          (*(code *)**(undefined4 **)(iVar16 + DAT_000176c0))
                    (4,6,0x36f,DAT_000176e0 + 0x17634,DAT_000176e4 + 0x1738e,uVar12);
          pcVar5 = *(char **)("_ZSt17current_exceptionv" + param_1 + 4);
          iVar14 = *(int *)("_ZSt17current_exceptionv" + param_1);
          uVar8 = *puVar7;
        }
        pcVar3 = (char *)(iVar14 + 0x3c);
        bVar18 = pcVar3 != pcVar5;
        "_ZNSt15__exception_ptr13exception_ptr4swapERS0_"[param_1 + 0x2d] = '\x01';
        if (bVar18) {
          pcVar5 = "17current_exceptionv";
        }
        if (bVar18) {
          *(char **)(pcVar5 + param_1) = pcVar3;
        }
        if (6 < uVar8) {
          (*(code *)**(undefined4 **)(iVar16 + DAT_000176c0))
                    (4,7,0x372,DAT_000176e8 + 0x1767e,DAT_000176ec + 0x173d8,1);
          iVar14 = *(int *)("_ZSt17current_exceptionv" + param_1);
        }
      }
      pfVar4 = (float *)FUN_00023824("_ZSt19__throw_logic_errorPKc" + param_1 + 9);
      FUN_0000eee0(*(undefined4 *)(iVar14 + 0x38),&local_44,0);
      uVar1 = *(undefined8 *)(pfVar4 + 1);
      fVar19 = (float)((ulonglong)uVar1 >> 0x20) + *(float *)(iVar14 + 0x38);
      local_50 = (*pfVar4 * (float)local_44.metadata - pfVar4[1] * (float)local_44.cells) +
                 (float)*(undefined8 *)(iVar14 + 0x30);
      local_4c = (float)local_44.metadata * (float)uVar1 + *pfVar4 * (float)local_44.cells +
                 (float)((ulonglong)*(undefined8 *)(iVar14 + 0x30) >> 0x20);
      local_48 = DAT_000176ac;
      if (!NAN(fVar19)) {
        for (; DAT_000176a0 <= fVar19; fVar19 = fVar19 - DAT_000176a4) {
        }
        for (; local_48 = fVar19, (int)((uint)(fVar19 < DAT_000176a8) << 0x1f) < 0;
            fVar19 = fVar19 + DAT_000176a4) {
        }
      }
      FUN_00023828(*(int *)("_ZSt17current_exceptionv" + param_1) + 8);
      FUN_00023814(&local_44,&local_50);
      FUN_00023854(*(int *)("_ZSt17current_exceptionv" + param_1) + 8,&local_44);
      FUN_00023824(*(int *)("_ZSt17current_exceptionv" + param_1) + 8);
      FUN_00023824(*(int *)("_ZSt17current_exceptionv" + param_1) + 8);
      FUN_00023824(*(int *)("_ZSt17current_exceptionv" + param_1) + 8);
      if (3 < *puVar7) {
        (*(code *)**(undefined4 **)(iVar16 + DAT_000176c0))
                  (4,4,0x379,DAT_000176f4 + 0x177b8,DAT_000176f0 + 0x17502);
      }
      if ("__cxa_guard_abort"[param_1 + 0xb] == '\0') {
        iVar16 = FUN_000221c4(local_5c.metadata,local_68.metadata);
        if (iVar16 == 0) {
          GridRectMergeInto(&(local_5c.metadata)->view,&(local_68.metadata)->view);
          uVar12 = GridRectCellCount(&(local_5c.metadata)->bounds);
          if (0 < (int)uVar12) {
            local_5c.cells = local_5c.cells + -1;
            puVar9 = local_68.cells;
            do {
              puVar11 = puVar9 + 1;
              local_5c.cells = local_5c.cells + 1;
              *local_5c.cells = *puVar9;
              puVar9 = puVar11;
            } while (local_68.cells + uVar12 != puVar11);
          }
        }
      }
      else {
        GridDropSavedCaches();
        pvVar2 = (void *)FUN_00026e80();
        local_50 = *(float *)(*(int *)("_ZSt17current_exceptionv" + param_1) + 4);
        GridGetSavedBuffer(&local_44,pvVar2,(int *)&local_50);
        pGVar17 = &local_44;
        if ((local_44.valid == '\0') && (pGVar17 = &local_68, 3 < *puVar7)) {
          (*(code *)**(undefined4 **)(iVar16 + DAT_000176c0))
                    (4,4,0x381,DAT_000176fc + 0x178a6,DAT_000176f8 + 0x175ee,
                     *(undefined4 *)(*(int *)("_ZSt17current_exceptionv" + param_1) + 4));
        }
        pGVar13 = pGVar17->metadata;
        iVar16 = FUN_000221c4(local_5c.metadata,pGVar13);
        if (iVar16 == 0) {
          GridRectMergeInto(&(local_5c.metadata)->view,&pGVar13->view);
          uVar12 = GridRectCellCount(&(local_5c.metadata)->bounds);
          puVar9 = pGVar17->cells;
          if (0 < (int)uVar12) {
            local_5c.cells = local_5c.cells + -1;
            puVar11 = puVar9;
            do {
              puVar10 = puVar11 + 1;
              local_5c.cells = local_5c.cells + 1;
              *local_5c.cells = *puVar11;
              puVar11 = puVar10;
            } while (puVar9 + uVar12 != puVar10);
          }
        }
        GridDropSavedCaches();
      }
      iVar15 = *(int *)("_ZNSt18condition_variable4waitERSt11unique_lockISt5mutexE" + param_1 + 1);
      iVar14 = *(int *)("_ZNSt18condition_variable4waitERSt11unique_lockISt5mutexE" + param_1 + 5);
      "__cxa_guard_abort"[param_1 + 0xb] = '\0';
      pcVar5 = "__cxa_guard_abort" + param_1 + 0xf;
      pcVar5[0] = '\0';
      pcVar5[1] = '\0';
      pcVar5[2] = '\0';
      pcVar5[3] = '\0';
      iVar16 = iVar15;
      if (iVar15 != iVar14) {
        do {
          if (*(void **)(iVar16 + 0x28) != (void *)0x0) {
            operator_delete(*(void **)(iVar16 + 0x28));
          }
          if (*(void **)(iVar16 + 0x14) != (void *)0x0) {
            operator_delete(*(void **)(iVar16 + 0x14));
          }
          iVar16 = iVar16 + 0x38;
        } while (iVar14 != iVar16);
        *(int *)("_ZNSt18condition_variable4waitERSt11unique_lockISt5mutexE" + param_1 + 5) = iVar15
        ;
      }
    }
  }
  else {
    pcVar5 = "_ZNSt18condition_variable4waitERSt11unique_lockISt5mutexE" + param_1 + 0xd;
    pcVar5[0] = '\0';
    pcVar5[1] = '\0';
    pcVar5[2] = '\0';
    pcVar5[3] = '\0';
    "_ZNSt15__exception_ptr13exception_ptr4swapERS0_"[param_1 + 0x2d] = '\0';
    ("_ZNSt15__exception_ptr13exception_ptr4swapERS0_" + param_1 + 0x2b)[0] = '\x01';
    ("_ZNSt15__exception_ptr13exception_ptr4swapERS0_" + param_1 + 0x2b)[1] = '\0';
    if (uVar12 < 2) {
      if (5 < *puVar7) {
        (*(code *)**(undefined4 **)(iVar16 + DAT_000176c0))
                  (4,6,0x391,DAT_000176d4 + 0x175ea,DAT_000176d8 + 0x17344,uVar12);
      }
      "_ZNSt15__exception_ptr13exception_ptr4swapERS0_"[param_1 + 0x2c] = '\x01';
      "_ZNSt15__exception_ptr13exception_ptr4swapERS0_"[param_1 + 0x2d] = (byte)uVar12 & 1;
    }
  }
  if (local_34 == *piVar6) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

