/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrslamdrv.so
 * SHA256: b48f5f56eb1b2d22abbf727725ea558762337f8f0103229d8da6c1ab6275608a
 * Function VA: 0x0000c410
 */

/* WARNING: Restarted to delay deadcode elimination for space: stack */

void FUN_0000c410(int param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  undefined4 uVar5;
  float fVar6;
  uint uVar7;
  undefined4 uVar8;
  uint *puVar9;
  undefined4 uVar10;
  undefined4 *puVar11;
  int *piVar12;
  int *piVar13;
  void *pvVar14;
  int iVar15;
  undefined4 *puVar16;
  int iVar17;
  int iVar18;
  float fVar19;
  void *local_88;
  int iStack_84;
  float local_80;
  int iStack_7c;
  int local_78;
  int iStack_74;
  int iStack_70;
  int iStack_6c;
  int local_68;
  int iStack_64;
  int iStack_60;
  int iStack_5c;
  int local_58;
  int iStack_54;
  int local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  int local_34;
  
  iVar15 = DAT_0000cc30 + 0xc426;
  piVar13 = *(int **)(iVar15 + DAT_0000cc34);
  local_34 = *piVar13;
  iVar2 = FUN_0001f274(param_3);
  switch(*(undefined4 *)(iVar2 + 4)) {
  case 1:
    iVar2 = FUN_0001f274(param_3);
    *(float *)(param_1 + 0x1f0) = ABS(*(float *)(iVar2 + 0x4c));
    *(float *)(param_1 + 500) = ABS(*(float *)(iVar2 + 0x50));
    break;
  case 4:
    puVar9 = *(uint **)(iVar15 + DAT_0000cc38);
    if (*puVar9 < 7) {
      if (*(char *)(param_1 + 0xf8) != '\0') break;
    }
    else {
      iVar2 = DAT_0000cc64 + 0xc6b0;
      FUN_00007360(7,iVar2,0x599,DAT_0000cc68 + 0xc620);
      if (*(char *)(param_1 + 0xf8) != '\0') {
        if (6 < *puVar9) {
          FUN_00007360(7,iVar2,0x59b,DAT_0000cc6c + 0xc648);
        }
        break;
      }
    }
    iVar2 = FUN_0001f274(param_3);
    iVar15 = FUN_0001f274(param_3);
    local_88 = *(void **)(iVar2 + 0xc);
    iStack_84 = *(int *)(iVar2 + 0x10);
    local_80 = *(float *)(iVar2 + 0x14);
    fVar6 = *(float *)(iVar2 + 0x14);
    fVar19 = DAT_0000cc2c;
    if (!NAN(fVar6)) {
      for (; DAT_0000cc20 <= fVar6; fVar6 = fVar6 - DAT_0000cc24) {
      }
      for (; fVar19 = fVar6, (int)((uint)(fVar6 < DAT_0000cc28) << 0x1f) < 0;
          fVar6 = fVar6 + DAT_0000cc24) {
      }
    }
    piVar3 = (int *)FUN_00020040(param_2);
    piVar3[2] = (int)fVar19;
    *piVar3 = (int)local_88;
    piVar3[1] = iStack_84;
    FUN_00020748(param_2,iVar15 + 0x18,param_1 + 0x1f0);
    break;
  case 5:
    iVar2 = FUN_0001f274(param_3);
    pvVar14 = *(void **)(iVar2 + 0xc);
    if (6 < **(uint **)(iVar15 + DAT_0000cc38)) {
      (*(code *)**(undefined4 **)(iVar15 + DAT_0000cc3c))
                (4,7,0x5b6,DAT_0000cc74 + 0xc70e,DAT_0000cc70 + 0xc678,pvVar14);
    }
    if (0 < (int)pvVar14) {
      uVar5 = FUN_00026e80();
      local_88 = pvVar14;
      uVar5 = FUN_00026a7c(uVar5,&local_88);
      FUN_00020ad0(param_2,uVar5);
    }
    break;
  case 6:
    iVar2 = FUN_0001f274(param_3);
    pvVar14 = *(void **)(iVar2 + 0xc);
    if (6 < **(uint **)(iVar15 + DAT_0000cc38)) {
      (*(code *)**(undefined4 **)(iVar15 + DAT_0000cc3c))
                (4,7,0x5c0,DAT_0000cc7c + 0xc764,DAT_0000cc78 + 0xc6ce,pvVar14);
    }
    if (0 < (int)pvVar14) {
      uVar5 = FUN_00026e80();
      local_88 = pvVar14;
      uVar5 = FUN_00026a7c(uVar5,&local_88);
      FUN_00020c24(param_2,uVar5);
    }
    break;
  case 7:
    if (6 < **(uint **)(iVar15 + DAT_0000cc38)) {
      FUN_00007360(7,DAT_0000cc98 + 0xc8be,0x5ca,DAT_0000cc9c + 0xc82c);
    }
    FUN_0001feb4(param_2);
    break;
  case 8:
    iVar2 = FUN_0001f274(param_3);
    local_88 = *(void **)(iVar2 + 0xc);
    if (6 < **(uint **)(iVar15 + DAT_0000cc38)) {
      (*(code *)**(undefined4 **)(iVar15 + DAT_0000cc3c))
                (4,7,0x5d1,DAT_0000cc8c + 0xc80c,DAT_0000cc88 + 0xc76c,local_88);
    }
    if (0 < (int)local_88) {
      FUN_00020190(param_2,&local_88);
    }
    break;
  case 9:
    puVar9 = *(uint **)(iVar15 + DAT_0000cc38);
    if (6 < *puVar9) {
      FUN_00007360(7,DAT_0000ccac + 0xc934,0x5da,DAT_0000ccb0 + 0xc8a2);
    }
    iVar2 = FUN_0001f274(param_3);
    if (6 < *puVar9) {
      (*(code *)**(undefined4 **)(iVar15 + DAT_0000cc3c))
                (4,7,0x5de,DAT_0000ccb8 + 0xc96e,DAT_0000ccb4 + 0xc8d4);
    }
    local_88 = *(void **)(iVar2 + 0xc);
    iStack_84 = *(int *)(iVar2 + 0x10);
    fVar6 = *(float *)(iVar2 + 0x14);
    local_80 = DAT_0000cc2c;
    if (!NAN(fVar6)) {
      for (; DAT_0000cc20 <= fVar6; fVar6 = fVar6 - DAT_0000cc24) {
      }
      for (; local_80 = fVar6, (int)((uint)(fVar6 < DAT_0000cc28) << 0x1f) < 0;
          fVar6 = fVar6 + DAT_0000cc24) {
      }
    }
    FUN_00020018(param_2,&local_88);
    break;
  case 0xb:
    iVar2 = FUN_0001f274(param_3);
    cVar1 = *(char *)(iVar2 + 0xc);
    if (6 < **(uint **)(iVar15 + DAT_0000cc38)) {
      (*(code *)**(undefined4 **)(iVar15 + DAT_0000cc3c))
                (4,7,0x5a9,DAT_0000cc84 + 0xc7ba,DAT_0000cc80 + 0xc724,cVar1);
    }
    FUN_00020044(param_2,cVar1);
    if (cVar1 == '\0') break;
    goto LAB_0000c5c2;
  case 0x22:
    iVar2 = FUN_0001f274(param_3);
    if (*(char *)(iVar2 + 0xc) != '\0') {
      if (6 < **(uint **)(iVar15 + DAT_0000cc38)) {
        (*(code *)**(undefined4 **)(iVar15 + DAT_0000cc3c))
                  (4,7,0x617,DAT_0000cca8 + 0xc908,DAT_0000cca4 + 0xc86a,DAT_0000cca0 + 0xc866);
      }
      FUN_000202c0(param_2,1);
      break;
    }
    if (6 < **(uint **)(iVar15 + DAT_0000cc38)) {
      (*(code *)**(undefined4 **)(iVar15 + DAT_0000cc3c))
                (4,7,0x617,DAT_0000ccd4 + 0xcb94,DAT_0000ccd0 + 0xcaf8,DAT_0000cccc + 0xcaf4);
    }
    goto LAB_0000c5cc;
  case 0x26:
    if (6 < **(uint **)(iVar15 + DAT_0000cc38)) {
      FUN_00007360(7,DAT_0000cc90 + 0xc840,0x601,DAT_0000cc94 + 0xc7ae);
    }
    iVar2 = FUN_0001f274(param_3);
    iVar15 = 0;
    local_50 = *(int *)(iVar2 + 0xc);
    uStack_4c = *(undefined4 *)(iVar2 + 0x10);
    uStack_48 = *(undefined4 *)(iVar2 + 0x14);
    uStack_44 = *(undefined4 *)(iVar2 + 0x18);
    local_40 = *(undefined4 *)(iVar2 + 0x1c);
    uStack_3c = *(undefined4 *)(iVar2 + 0x20);
    uStack_38 = *(undefined4 *)(iVar2 + 0x24);
    local_88 = (void *)0x0;
    iStack_84 = 0;
    local_80 = 0.0;
    puVar11 = &uStack_4c;
    if (0 < local_50) {
      do {
        FUN_0000f120(&local_88,puVar11);
        iVar15 = iVar15 + 1;
        puVar11 = puVar11 + 1;
      } while (iVar15 < local_50);
    }
    FUN_00020160(param_2,&local_88);
    if (local_88 != (void *)0x0) {
      operator_delete(local_88);
    }
    break;
  case 0x2d:
    iVar2 = FUN_0001f274(param_3);
    if (*(char *)(iVar2 + 0xc) != '\0') {
      if (6 < **(uint **)(iVar15 + DAT_0000cc38)) {
        (*(code *)**(undefined4 **)(iVar15 + DAT_0000cc3c))
                  (4,7,0x5e7,DAT_0000cc48 + 0xc57e,DAT_0000cc44 + 0xc4e2,DAT_0000cc40 + 0xc4dc);
      }
      FUN_000208bc(param_2,1);
      iVar2 = *(int *)(iVar15 + DAT_0000cc4c);
      if ((iVar2 != 0) &&
         (iVar15 = pthread_mutex_lock((pthread_mutex_t *)(param_1 + 0x1cc)), iVar15 != 0))
      goto LAB_0000cbf8;
      if (*(int *)(param_1 + 0x1e4) != *(int *)(param_1 + 0x1e8)) {
        *(int *)(param_1 + 0x1e8) = *(int *)(param_1 + 0x1e4);
      }
      if (iVar2 != 0) {
        pthread_mutex_unlock((pthread_mutex_t *)(param_1 + 0x1cc));
      }
      break;
    }
    puVar9 = *(uint **)(iVar15 + DAT_0000cc38);
    if (6 < *puVar9) {
      (*(code *)**(undefined4 **)(iVar15 + DAT_0000cc3c))
                (4,7,0x5e7,DAT_0000ccc4 + 0xca32,DAT_0000ccc0 + 0xc996,DAT_0000ccbc + 0xc990);
    }
    thunk_FUN_000205b4(param_2);
    iVar2 = *(int *)(iVar15 + DAT_0000cc4c);
    if ((iVar2 != 0) &&
       (iVar15 = pthread_mutex_lock((pthread_mutex_t *)(param_1 + 0x1cc)), iVar15 != 0)) {
LAB_0000cbf8:
                    /* WARNING: Subroutine does not return */
      std::__throw_system_error(iVar15);
    }
    piVar3 = (int *)FUN_0002015c(param_2);
    iVar18 = *piVar3;
    iVar15 = piVar3[1];
    uVar7 = (iVar15 - iVar18 >> 3) * -0x49249249;
    if (uVar7 == 0) {
      if (iVar18 != iVar15) {
        piVar4 = (int *)0x0;
        goto LAB_0000ca10;
      }
    }
    else {
      if (0x4924924 < uVar7) {
                    /* WARNING: Subroutine does not return */
        std::__throw_bad_alloc();
      }
      piVar4 = operator_new(iVar15 - iVar18);
      iVar18 = *piVar3;
      iVar15 = piVar3[1];
      if (iVar18 != iVar15) {
LAB_0000ca10:
        iVar17 = 0;
        do {
          puVar16 = (undefined4 *)(iVar18 + iVar17);
          puVar11 = (undefined4 *)((int)piVar4 + iVar17);
          iVar17 = iVar17 + 0x38;
          uVar5 = puVar16[1];
          uVar8 = puVar16[2];
          uVar10 = puVar16[3];
          *puVar11 = *puVar16;
          puVar11[1] = uVar5;
          puVar11[2] = uVar8;
          puVar11[3] = uVar10;
          uVar5 = puVar16[5];
          uVar8 = puVar16[6];
          uVar10 = puVar16[7];
          puVar11[4] = puVar16[4];
          puVar11[5] = uVar5;
          puVar11[6] = uVar8;
          puVar11[7] = uVar10;
          uVar5 = puVar16[9];
          uVar8 = puVar16[10];
          uVar10 = puVar16[0xb];
          puVar11[8] = puVar16[8];
          puVar11[9] = uVar5;
          puVar11[10] = uVar8;
          puVar11[0xb] = uVar10;
          uVar5 = puVar16[0xd];
          puVar11[0xc] = puVar16[0xc];
          puVar11[0xd] = uVar5;
        } while (iVar17 != (((uint)((iVar15 + -0x38) - iVar18) >> 3) * 0x16db6db7 & 0x1fffffff) *
                           0x38 + 0x38);
        if ((int *)(iVar17 + (int)piVar4) != piVar4) {
          piVar3 = piVar4;
          do {
            local_88 = (void *)*piVar3;
            iStack_84 = piVar3[1];
            local_80 = (float)piVar3[2];
            iStack_7c = piVar3[3];
            piVar12 = *(int **)(param_1 + 0x1e8);
            local_78 = piVar3[4];
            iStack_74 = piVar3[5];
            iStack_70 = piVar3[6];
            iStack_6c = piVar3[7];
            local_68 = piVar3[8];
            iStack_64 = piVar3[9];
            iStack_60 = piVar3[10];
            iStack_5c = piVar3[0xb];
            local_58 = piVar3[0xc];
            iStack_54 = piVar3[0xd];
            if (piVar12 == *(int **)(param_1 + 0x1ec)) {
              FUN_0000f14c(param_1 + 0x1e4,piVar12,&local_88);
            }
            else {
              *piVar12 = (int)local_88;
              piVar12[1] = iStack_84;
              piVar12[2] = (int)local_80;
              piVar12[3] = iStack_7c;
              piVar12[4] = local_78;
              piVar12[5] = iStack_74;
              piVar12[6] = iStack_70;
              piVar12[7] = iStack_6c;
              piVar12[8] = local_68;
              piVar12[9] = iStack_64;
              piVar12[10] = iStack_60;
              piVar12[0xb] = iStack_5c;
              piVar12[0xc] = local_58;
              piVar12[0xd] = iStack_54;
              *(int **)(param_1 + 0x1e8) = piVar12 + 0xe;
            }
            piVar3 = piVar3 + 0xe;
          } while (piVar3 != (int *)(iVar17 + (int)piVar4));
        }
      }
      operator_delete(piVar4);
    }
    if (iVar2 != 0) {
      pthread_mutex_unlock((pthread_mutex_t *)(param_1 + 0x1cc));
    }
    if (6 < *puVar9) {
      FUN_00007360(7,DAT_0000ccd8 + 0xcc5e,0x5f4,DAT_0000ccdc + 0xcbcc);
    }
    break;
  case 0x30:
    iVar2 = FUN_0001f274(param_3);
    iVar2 = *(int *)(iVar2 + 0xc);
    if (iVar2 == 0) {
      iVar18 = DAT_0000cc50 + 0xc55c;
    }
    else {
      iVar18 = DAT_0000ccc8 + 0xcad6;
    }
    if (6 < **(uint **)(iVar15 + DAT_0000cc38)) {
      (*(code *)**(undefined4 **)(iVar15 + DAT_0000cc3c))
                (4,7,0x610,DAT_0000cc58 + 0xc61a,DAT_0000cc54 + 0xc57c,iVar18);
    }
    FUN_000200d4(param_2,iVar2 != 0);
    break;
  case 0x32:
    if (6 < **(uint **)(iVar15 + DAT_0000cc38)) {
      FUN_00007360(7,DAT_0000cc5c + 0xc650,0x622,DAT_0000cc60 + 0xc5be);
    }
LAB_0000c5c2:
    iVar2 = FUN_00020208(param_2);
    if (iVar2 != 0) {
LAB_0000c5cc:
      FUN_000208bc(param_2,0);
    }
  }
  if (local_34 == *piVar13) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

