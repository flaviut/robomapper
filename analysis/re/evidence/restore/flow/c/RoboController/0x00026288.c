/* Decompiled C, NOT recovered source; need not compile.
 * Binary: RoboController
 * SHA256: bf1d43313dd8beaa0c802f9ae4c666138b3bb518f69b4909a746285f3f3947cf
 * Function VA: 0x00026288
 */

void FUN_00026288(int *param_1,uint *param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined1 uVar4;
  uint uVar5;
  uint *puVar6;
  uint *puVar7;
  uint uVar8;
  uint uVar9;
  uint *puVar10;
  uint *puVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  undefined4 uVar15;
  
  iVar1 = __stack_chk_guard;
  uVar2 = (**(code **)(*param_1 + 8))();
  if (uVar2 == 0x80) {
    param_2[2] = 0x3e;
    *param_2 = 0x2010012;
    puVar6 = param_2 + 3;
    puVar10 = (uint *)(param_1 + 3);
    do {
      puVar11 = puVar10 + 4;
      uVar3 = puVar10[1];
      puVar7 = puVar6 + 4;
      uVar2 = puVar10[2];
      uVar12 = puVar10[3];
      *puVar6 = *puVar10;
      puVar6[1] = uVar3;
      puVar6[2] = uVar2;
      puVar6[3] = uVar12;
      puVar6 = puVar7;
      puVar10 = puVar11;
    } while (puVar11 != (uint *)(param_1 + 0xf));
LAB_000264d4:
    uVar15 = 0;
    uVar2 = puVar11[1];
    uVar12 = puVar11[2];
    *puVar7 = *puVar11;
    puVar7[1] = uVar2;
    puVar7[2] = uVar12;
    *(short *)(puVar7 + 3) = (short)puVar11[3];
    goto LAB_0002644c;
  }
  if (0x80 < uVar2) {
    if (uVar2 == 0xa4) {
      uVar4 = (undefined1)param_1[3];
      uVar2 = 0x1211;
LAB_00026644:
      param_2[2] = 1;
      uVar15 = 0;
      *(undefined1 *)(param_2 + 3) = uVar4;
      *param_2 = uVar2 | 0x2010000;
    }
    else {
      if (uVar2 < 0xa5) {
        if (uVar2 == 0x94) {
          uVar4 = (undefined1)param_1[3];
          uVar2 = 0x120c;
          goto LAB_00026644;
        }
        if (uVar2 < 0x95) {
          if (uVar2 == 0x8c) {
            param_2[2] = 0x28;
            *param_2 = 0x2011205;
            puVar6 = param_2 + 3;
            puVar10 = (uint *)(param_1 + 3);
            do {
              puVar11 = puVar10 + 4;
              uVar3 = puVar10[1];
              puVar7 = puVar6 + 4;
              uVar2 = puVar10[2];
              uVar12 = puVar10[3];
              *puVar6 = *puVar10;
              puVar6[1] = uVar3;
              puVar6[2] = uVar2;
              puVar6[3] = uVar12;
              puVar6 = puVar7;
              puVar10 = puVar11;
            } while (puVar11 != (uint *)(param_1 + 0xb));
          }
          else {
            if (uVar2 == 0x93) {
              uVar2 = 0x120b;
              goto LAB_00026438;
            }
            if (uVar2 != 0x8b) goto LAB_000262d0;
            param_2[2] = 0x28;
            *param_2 = 0x2011204;
            puVar6 = param_2 + 3;
            puVar10 = (uint *)(param_1 + 3);
            do {
              puVar11 = puVar10 + 4;
              uVar3 = puVar10[1];
              puVar7 = puVar6 + 4;
              uVar2 = puVar10[2];
              uVar12 = puVar10[3];
              *puVar6 = *puVar10;
              puVar6[1] = uVar3;
              puVar6[2] = uVar2;
              puVar6[3] = uVar12;
              puVar6 = puVar7;
              puVar10 = puVar11;
            } while (puVar11 != (uint *)(param_1 + 0xb));
          }
          uVar15 = 0;
          uVar2 = puVar11[1];
          *puVar7 = *puVar11;
          puVar7[1] = uVar2;
          goto LAB_0002644c;
        }
        if (uVar2 == 0x9f) {
          uVar2 = 0x1207;
          goto LAB_000263ba;
        }
        if (uVar2 == 0xa0) {
          uVar2 = 0x1208;
LAB_00026438:
          *param_2 = uVar2 | 0x2010000;
          uVar15 = 0;
          param_2[2] = 4;
          param_2[3] = param_1[3];
          goto LAB_0002644c;
        }
        if (uVar2 == 0x9b) {
          uVar2 = param_1[3];
          uVar12 = 0x39;
          goto LAB_00026348;
        }
      }
      else {
        if (uVar2 == 0x210) {
          uVar2 = param_1[4];
          uVar15 = 0;
          *param_2 = 0x2011210;
          param_2[2] = 0x20;
          param_2[3] = uVar2;
          goto LAB_0002644c;
        }
        if (uVar2 < 0x211) {
          if (uVar2 == 0xab) {
            uVar2 = param_1[3];
            uVar12 = param_1[4];
            uVar3 = param_1[5];
            *param_2 = 0x2011214;
            uVar15 = 0;
            param_2[2] = 0xc;
            param_2[3] = uVar2;
            param_2[4] = uVar12;
            param_2[5] = uVar3;
            goto LAB_0002644c;
          }
          if (uVar2 == 0x20a) {
            uVar2 = param_1[3];
            uVar12 = 0x120d;
            goto LAB_00026348;
          }
          if (uVar2 == 0xa6) {
            uVar2 = 0x1215;
            goto LAB_00026438;
          }
        }
        else {
          if (uVar2 == 0x230) {
            uVar2 = param_1[4];
            uVar3 = param_1[5];
            uVar8 = param_1[6];
            uVar13 = param_1[7];
            uVar12 = param_1[8];
            uVar5 = param_1[9];
            uVar9 = param_1[10];
            uVar14 = param_1[0xb];
            *param_2 = 0x2011222;
            uVar15 = 0;
            param_2[2] = 0x20;
            param_2[3] = uVar2;
            param_2[4] = uVar3;
            param_2[5] = uVar8;
            param_2[6] = uVar13;
            param_2[7] = uVar12;
            param_2[8] = uVar5;
            param_2[9] = uVar9;
            param_2[10] = uVar14;
            goto LAB_0002644c;
          }
          if (uVar2 == 0x7dd) {
            param_2[2] = 0xc;
            *param_2 = 0x201033a;
            uVar2 = param_1[4];
            uVar12 = param_1[5];
            uVar15 = 0;
            param_2[3] = param_1[3];
            param_2[4] = uVar2;
            param_2[5] = uVar12;
            goto LAB_0002644c;
          }
          if (uVar2 == 0x211) {
            uVar2 = param_1[3];
            uVar12 = 0x1212;
            goto LAB_00026348;
          }
        }
      }
LAB_000262d0:
      uVar15 = 0x80000002;
    }
    goto LAB_0002644c;
  }
  if (uVar2 == 0x38) {
    uVar2 = param_1[3];
    uVar12 = 4;
LAB_00026348:
    param_2[2] = 4;
    uVar15 = 0;
    param_2[3] = uVar2;
    *param_2 = uVar12 | 0x2010000;
    goto LAB_0002644c;
  }
  if (uVar2 < 0x39) {
    if (uVar2 == 0x33) {
      uVar2 = 0x6c;
LAB_000264f2:
      *param_2 = uVar2 | 0x2010000;
      uVar15 = 0;
      param_2[2] = 4;
      param_2[3] = param_1[3];
      goto LAB_0002644c;
    }
    if (uVar2 < 0x34) {
      if (uVar2 == 0xe) {
        param_2[2] = 8;
        *param_2 = 0x201032a;
        uVar15 = 0;
        uVar2 = param_1[4];
        param_2[3] = param_1[3];
        param_2[4] = uVar2;
        goto LAB_0002644c;
      }
      if (uVar2 == 0x31) {
        uVar2 = 0x66;
        goto LAB_00026438;
      }
    }
    else {
      if (uVar2 == 0x35) {
        uVar2 = param_1[3];
        uVar12 = 2;
        goto LAB_00026348;
      }
      if (uVar2 < 0x35) {
        uVar2 = 1;
        goto LAB_000264f2;
      }
      if (uVar2 == 0x36) {
        param_2[2] = 5;
        *param_2 = 0x2010003;
        uVar15 = 0;
        param_2[3] = param_1[3];
        *(char *)(param_2 + 4) = (char)param_1[4];
        goto LAB_0002644c;
      }
    }
    goto LAB_000262d0;
  }
  if (uVar2 == 0x77) {
    uVar2 = 0x75;
LAB_000262fc:
    param_2[2] = 0x10;
    *param_2 = uVar2 | 0x2010000;
    puVar6 = (uint *)(param_1 + 3);
    uVar2 = *puVar6;
  }
  else {
    if (0x77 < uVar2) {
      if (uVar2 == 0x7a) {
        uVar2 = 0xe;
        goto LAB_000264f2;
      }
      if (uVar2 == 0x7f) {
        param_2[2] = 0x3e;
        *param_2 = 0x2010010;
        puVar6 = param_2 + 3;
        puVar10 = (uint *)(param_1 + 3);
        do {
          puVar11 = puVar10 + 4;
          uVar3 = puVar10[1];
          puVar7 = puVar6 + 4;
          uVar2 = puVar10[2];
          uVar12 = puVar10[3];
          *puVar6 = *puVar10;
          puVar6[1] = uVar3;
          puVar6[2] = uVar2;
          puVar6[3] = uVar12;
          puVar6 = puVar7;
          puVar10 = puVar11;
        } while (puVar11 != (uint *)(param_1 + 0xf));
        goto LAB_000264d4;
      }
      if (uVar2 != 0x78) goto LAB_000262d0;
      uVar2 = 0x76;
      goto LAB_000262fc;
    }
    if (uVar2 == 0x3d) {
      uVar2 = 0x20;
    }
    else {
      if (uVar2 == 0x3f) {
        uVar2 = param_1[3];
        uVar12 = 0x2f;
        goto LAB_00026348;
      }
      if (uVar2 != 0x3c) goto LAB_000262d0;
      uVar2 = 0x1b;
    }
LAB_000263ba:
    param_2[2] = 0x10;
    *param_2 = uVar2 | 0x2010000;
    puVar6 = (uint *)(param_1 + 4);
    uVar2 = *puVar6;
  }
  uVar15 = 0;
  uVar12 = puVar6[1];
  uVar3 = puVar6[2];
  uVar5 = puVar6[3];
  param_2[3] = uVar2;
  param_2[4] = uVar12;
  param_2[5] = uVar3;
  param_2[6] = uVar5;
LAB_0002644c:
  if (iVar1 == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar15);
}

