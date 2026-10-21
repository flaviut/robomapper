/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x0012cb14
 */

/* WARNING: Restarted to delay deadcode elimination for space: stack */

void FUN_0012cb14(int param_1,int *param_2,int *param_3)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int **ppiVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  uint uVar9;
  uint uVar10;
  char cVar11;
  bool bVar12;
  float fVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  undefined1 local_1f7;
  undefined1 local_1f6;
  char local_1f5;
  undefined4 local_1f4;
  int local_1f0;
  int local_1ec [11];
  int *local_1c0;
  int *piStack_1bc;
  undefined4 *local_1b8;
  int **local_1b4;
  int *local_1b0;
  undefined4 local_1ac;
  int *local_1a8;
  uint local_1a4;
  int *local_1a0;
  int local_19c;
  int local_198;
  int local_194;
  int local_190;
  int local_18c;
  int local_188;
  int local_184;
  int local_180;
  int local_17c;
  int local_178;
  int local_174;
  int local_170;
  uint local_16c;
  uint local_168;
  uint local_164;
  uint local_160;
  int local_15c;
  int local_158;
  int *local_154;
  int *local_150;
  undefined4 *local_14c;
  int local_148;
  undefined1 *local_144;
  undefined1 *local_140;
  undefined4 local_13c;
  undefined4 local_138;
  int *local_134;
  undefined4 local_130;
  int local_12c;
  int local_128;
  int local_124;
  int local_120;
  undefined4 local_11c;
  int local_118;
  undefined4 local_114;
  undefined4 local_110;
  int *local_10c;
  undefined4 local_108;
  int local_104;
  int local_100;
  int local_fc;
  int local_f8;
  undefined4 local_f4;
  int local_f0;
  int local_ec;
  int local_e8;
  int local_e4;
  int local_e0;
  int local_dc;
  int local_d8;
  int local_d4;
  undefined1 auStack_d0 [36];
  undefined4 *local_ac;
  int **local_a8;
  int local_a4;
  char *local_a0;
  int local_98;
  int local_94;
  int local_90;
  int local_8c;
  int local_88;
  int local_84;
  int local_80;
  undefined1 auStack_7c [36];
  undefined4 *local_58;
  int local_54;
  undefined1 *local_50;
  undefined1 *local_4c;
  int *local_48;
  int *local_44;
  int **local_40;
  int **local_3c;
  int **local_38;
  uint *local_34;
  int local_2c;
  
  piVar3 = *(int **)(DAT_0012cd18 + 0x12cb28 + DAT_0012cd1c);
  local_2c = *piVar3;
  _rrlogmP(3,7,1,0x2a5,DAT_0012cd28 + 0x12cb4e,DAT_0012cd24 + 0x12cb46,DAT_0012cd20 + 0x12cb42);
  local_1f4 = FUN_0014d1dc();
  local_1b0 = (int *)0x0;
  local_1ac = 0;
  uVar9 = *(int *)(param_1 + 0x100024) * *(int *)(param_1 + 0x100020);
  local_1a8 = (int *)0x0;
  local_1a4 = 0;
  local_1a0 = (int *)0x0;
  uVar7 = uVar9 + 0x1f >> 5;
  cVar11 = '\0';
  local_1b0 = operator_new(uVar7 * 4);
  uVar10 = uVar9 + 0x1f & (int)uVar9 >> 0x20;
  if (cVar11 == '\0') {
    uVar10 = uVar9;
  }
  local_1a4 = uVar9 & 0x1f;
  if (-1 < (int)-uVar9) {
    local_1a4 = -(-uVar9 & 0x1f);
  }
  local_1a0 = local_1b0 + uVar7;
  local_1a8 = local_1b0 + ((int)uVar10 >> 5);
  if ((int)local_1a4 < 0) {
    local_1a4 = local_1a4 + 0x20;
    local_1a8 = local_1a8 + -1;
  }
  bVar12 = local_1b0 != local_1a0;
  local_1ac = 0;
  piVar1 = local_1b0;
  ppiVar5 = &local_1b0;
  if (bVar12) {
    ppiVar5 = (int **)0x0;
  }
  while (bVar12) {
    *piVar1 = (int)ppiVar5;
    bVar12 = piVar1 + 1 != local_1a0;
    piVar1 = piVar1 + 1;
  }
  fVar13 = roundf((float)(longlong)*(int *)((int)&DAT_001000b8 + param_1) * DAT_0012cd14);
  local_164 = (uint)fVar13;
  local_190 = local_164 + 2;
  local_19c = *param_3 - local_190;
  local_194 = param_3[2] + local_190;
  local_198 = param_3[1] - local_190;
  local_190 = local_190 + param_3[3];
  if (local_194 - local_19c < 0) {
    local_18c = 0;
  }
  else {
    local_18c = (local_194 - local_19c) + 1;
  }
  if (local_190 - local_198 < 0) {
    local_188 = 0;
  }
  else {
    local_188 = (local_190 - local_198) + 1;
  }
  FUN_0012883c(&local_98,&local_19c,&DAT_00100010 + param_1);
  local_19c = local_98;
  local_198 = local_94;
  local_194 = local_90;
  local_190 = local_8c;
  local_1ec[0] = (param_3[3] + param_3[1]) / 2;
  iVar4 = *param_3;
  local_18c = local_88;
  local_188 = local_84;
  local_184 = -local_164;
  local_1f0 = iVar4 + -1;
  local_17c = local_164 - 1;
  if ((int)(local_17c + local_164) < 0) {
    local_15c = 0;
  }
  else {
    local_15c = local_17c + local_164 + 1;
  }
  local_174 = local_15c;
  local_16c = ~local_164;
  if ((int)(local_164 - local_16c) < 0) {
    local_15c = 0;
  }
  else {
    local_15c = (local_164 - local_16c) + 1;
  }
  local_180 = local_184;
  local_178 = local_17c;
  local_170 = local_174;
  local_168 = local_16c;
  local_160 = local_164;
  local_158 = local_15c;
  if (iVar4 <= param_3[2]) {
    iVar6 = (*(int *)(param_1 + 8) * (local_1ec[0] - *(int *)(&DAT_00100014 + param_1)) + iVar4) -
            *(int *)(&DAT_00100010 + param_1);
    do {
      if (((-1 < iVar6) && (iVar6 < *(int *)(param_1 + 0x10003c))) &&
         ((*(byte *)(param_1 + iVar6 + 0x10) & 0x3f) != 0)) {
        piVar1 = local_1ec + 1;
        local_1f0 = iVar4 + -1;
        local_1f7 = 0;
        local_1f6 = 0;
        local_1ec[1] = 0;
        local_1ec[2] = 0;
        local_1c0 = piVar1;
        piStack_1bc = &local_19c;
        local_1b8 = &local_1f4;
        local_1b4 = &local_1b0;
        local_154 = piVar1;
        local_150 = &local_19c;
        local_14c = &local_1f4;
        local_148 = param_1;
        local_144 = &local_1f7;
        local_140 = &local_1f6;
        FUN_001b2214(&local_98);
        local_94 = local_19c;
        local_90 = local_198;
        local_98 = DAT_0012d1f4 + 0x12cdb8;
        local_8c = local_194;
        local_88 = local_190;
        if (local_194 - local_19c < 0) {
          local_84 = 0;
        }
        else {
          local_84 = (local_194 - local_19c) + 1;
        }
        if (local_190 - local_198 < 0) {
          local_80 = 0;
        }
        else {
          local_80 = (local_190 - local_198) + 1;
        }
        FUN_00126344(auStack_7c,&local_19c);
        local_58 = &local_1f4;
        local_54 = param_1;
        local_50 = &local_1f7;
        local_4c = &local_1f6;
        local_48 = piVar1;
        local_44 = &local_184;
        local_40 = &local_154;
        local_3c = &local_1c0;
        local_38 = &local_1b0;
        local_34 = &local_16c;
        FUN_001250d4(auStack_7c);
        if (((local_94 <= local_1f0) && (local_1f0 <= local_8c)) &&
           (iVar4 = FUN_00124fe4(&local_94,local_1ec), iVar4 != 0)) {
          local_13c = 0;
          local_138 = 0;
          local_134 = (int *)0x0;
          local_130 = 0;
          local_12c = 0;
          local_128 = 0;
          local_124 = 0;
          local_120 = 0;
          local_11c = 0;
          local_118 = 0;
          local_1ec[3] = 0;
          local_1ec[4] = 0;
          local_1ec[5] = 0;
          local_1ec[6] = 0;
          FUN_000e66f8(&local_13c,0);
          FUN_0012ba24(&local_13c,&local_1f0);
LAB_0012d0da:
          if ((local_124 - local_120 >> 3) + ((local_118 - local_128 >> 2) + -1) * 0x40 +
              (local_12c - (int)local_134 >> 3) != 0) {
            local_1ec[3] = *local_134;
            local_1ec[4] = local_134[1];
            if (local_134 == (int *)(local_12c + -8)) {
              FUN_00124ffc(&local_13c);
            }
            else {
              local_134 = local_134 + 2;
            }
            iVar4 = -1;
            iVar6 = 0;
            do {
              if (iVar4 != 0) {
                local_1ec[5] = local_1ec[3] + iVar4;
                local_1ec[6] = local_1ec[4];
                iVar2 = FUN_0012c860(&local_98,local_1ec + 3,local_1ec + 5,&local_13c);
                if (iVar2 != 0) break;
                local_1ec[6] = local_1ec[4] + iVar4;
                local_1ec[5] = local_1ec[3];
                iVar2 = FUN_0012c860(&local_98,local_1ec + 3,local_1ec + 5,&local_13c);
                if (iVar2 != 0) break;
                if (iVar6 == 2) goto LAB_0012d0da;
              }
              iVar6 = iVar6 + 1;
              iVar4 = iVar4 + 1;
            } while( true );
          }
          FUN_000d0198(&local_13c);
        }
        _rrlogmP(3,6,1,0x300,DAT_0012d200 + 0x12ce2c,DAT_0012d1fc + 0x12ce28,DAT_0012d1f8 + 0x12ce26
                );
        local_1f5 = '\0';
        FUN_001b2214(&local_ec);
        local_e8 = local_19c;
        local_e4 = local_198;
        local_e0 = local_194;
        local_dc = local_190;
        local_ec = DAT_0012d204 + 0x12ce68;
        if (local_194 - local_19c < 0) {
          local_d8 = 0;
        }
        else {
          local_d8 = (local_194 - local_19c) + 1;
        }
        if (local_190 - local_198 < 0) {
          local_d4 = 0;
        }
        else {
          local_d4 = (local_190 - local_198) + 1;
        }
        FUN_00126344(auStack_d0,&local_19c);
        local_ac = &local_1f4;
        local_a8 = &local_1b0;
        local_a4 = param_1;
        local_a0 = &local_1f5;
        FUN_001250d4(auStack_d0);
        iVar4 = *param_2;
        if (((local_e8 <= iVar4) && (iVar4 <= local_e0)) &&
           (iVar6 = FUN_00124fe4(&local_e8,param_2 + 1), iVar6 != 0)) {
          local_1ec[7] = 0;
          local_1ec[8] = 0;
          local_114 = 0;
          local_110 = 0;
          local_10c = (int *)0x0;
          local_108 = 0;
          local_104 = 0;
          local_100 = 0;
          local_fc = 0;
          local_f8 = 0;
          local_f4 = 0;
          local_f0 = 0;
          local_1ec[9] = 0;
          local_1ec[10] = 0;
          FUN_000e66f8(&local_114,0);
          FUN_0012ba24(&local_114,param_2);
LAB_0012cfea:
          if ((local_fc - local_f8 >> 3) + ((local_f0 - local_100 >> 2) + -1) * 0x40 +
              (local_104 - (int)local_10c >> 3) != 0) {
            local_1ec[7] = *local_10c;
            local_1ec[8] = local_10c[1];
            if (local_10c == (int *)(local_104 + -8)) {
              FUN_00124ffc(&local_114);
            }
            else {
              local_10c = local_10c + 2;
            }
            iVar4 = -1;
            iVar6 = 0;
            do {
              if (iVar4 != 0) {
                local_1ec[9] = local_1ec[7] + iVar4;
                local_1ec[10] = local_1ec[8];
                iVar2 = FUN_0012ca58(&local_ec,local_1ec + 7,local_1ec + 9,&local_114);
                if (iVar2 != 0) break;
                local_1ec[10] = local_1ec[8] + iVar4;
                local_1ec[9] = local_1ec[7];
                iVar2 = FUN_0012ca58(&local_ec,local_1ec + 7,local_1ec + 9,&local_114);
                if (iVar2 != 0) break;
                if (iVar6 == 2) goto LAB_0012cfea;
              }
              iVar6 = iVar6 + 1;
              iVar4 = iVar4 + 1;
            } while( true );
          }
          FUN_000d0198(&local_114);
          iVar4 = *param_2;
        }
        iVar6 = local_1f0;
        iVar2 = local_1ec[0];
        iVar14 = local_19c;
        iVar15 = local_198;
        iVar16 = local_194;
        iVar17 = local_190;
        _rrlogmP(3,6,1,0x318,DAT_0012d210 + 0x12ceea,DAT_0012d20c + 0x12cee4,DAT_0012d208 + 0x12cee0
                 ,iVar4,param_2[1],local_1f0,local_1ec[0],local_19c,local_198,local_194,local_190);
        if (local_1f5 == '\0') {
          _rrlogmP(3,6,1,0x31a,DAT_0012d228 + 0x12cf90,DAT_0012d224 + 0x12cf8a,
                   DAT_0012d220 + 0x12cf86,*(undefined4 *)(param_1 + 0x100020),
                   *(undefined4 *)(param_1 + 0x100024),iVar6,iVar2,iVar14,iVar15,iVar16,iVar17);
        }
        uVar8 = 1;
        FUN_00124bdc(&local_ec);
        FUN_00124c24(&local_98);
        goto LAB_0012cf10;
      }
      iVar4 = iVar4 + 1;
      iVar6 = iVar6 + 1;
    } while (iVar4 <= param_3[2]);
  }
  _rrlogmP(3,6,1,0x2ba,DAT_0012d21c + 0x12cf5a,DAT_0012d214 + 0x12cf48,DAT_0012d218 + 0x12cf54,
           local_98,local_94,local_90,local_8c);
  uVar8 = 0;
LAB_0012cf10:
  if (local_1b0 != (int *)0x0) {
    operator_delete(local_1b0);
  }
  if (local_2c == *piVar3) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar8);
}

