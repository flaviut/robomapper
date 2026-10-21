/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x0013223c
 */

/* WARNING: Restarted to delay deadcode elimination for space: stack */

void FUN_0013223c(int param_1,int *param_2,int *param_3,int param_4,undefined4 param_5,byte param_6,
                 char param_7)

{
  _Rb_tree_node _Var1;
  float fVar2;
  byte bVar3;
  int *piVar4;
  int iVar5;
  _Rb_tree_node *p_Var6;
  int iVar7;
  uint uVar8;
  _Reuse_or_alloc_node _Var9;
  int *piVar10;
  _Rb_tree_node *p_Var11;
  _Rb_tree_node *p_Var12;
  undefined4 uVar13;
  int iVar14;
  int iVar15;
  _Reuse_or_alloc_node *p_Var16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  double dVar21;
  float fVar22;
  double dVar23;
  undefined4 uVar24;
  double dVar25;
  double dVar26;
  uint local_224;
  undefined1 auStack_1f8 [4];
  undefined1 auStack_1f4 [4];
  undefined1 auStack_1f0 [4];
  undefined1 auStack_1ec [4];
  undefined1 auStack_1e8 [4];
  undefined4 local_1e4;
  int *local_1e0;
  int *local_1dc;
  int *local_1d8;
  int *local_1d4;
  int *local_1d0;
  uchar auStack_1cc [8];
  int local_1c4;
  int local_1c0;
  int local_1bc;
  int local_1b8;
  int local_1b4;
  int local_1b0;
  int local_1ac;
  int local_1a8;
  _Rb_tree_node *local_1a4;
  _Rb_tree_node *local_1a0;
  _Rb_tree<int,std::pair<int_const,int>,std::_Select1st<std::pair<int_const,int>>,std::less<int>,std::allocator<std::pair<int_const,int>>>
  *local_19c;
  _Rb_tree<int,std::pair<int_const,int>,std::_Select1st<std::pair<int_const,int>>,std::less<int>,std::allocator<std::pair<int_const,int>>>
  a_Stack_198 [4];
  undefined4 local_194;
  _Rb_tree_node *local_190;
  _Rb_tree_node *local_18c;
  _Rb_tree_node *local_188;
  int local_184;
  _Rb_tree<int,std::pair<int_const,int>,std::_Select1st<std::pair<int_const,int>>,std::less<int>,std::allocator<std::pair<int_const,int>>>
  a_Stack_180 [4];
  undefined4 local_17c;
  _Rb_tree_node *local_178;
  _Rb_tree_node *local_174;
  _Rb_tree_node *local_170;
  int local_16c;
  map<int,std::set<int,std::less<int>,std::allocator<int>>,std::less<int>,std::allocator<std::pair<int_const,std::set<int,std::less<int>,std::allocator<int>>>>>
  amStack_168 [4];
  undefined4 local_164;
  _Rb_tree_node *local_160;
  undefined4 *local_15c;
  undefined4 *local_158;
  undefined4 local_154;
  _Rb_tree<int,std::pair<int_const,unsigned_char>,std::_Select1st<std::pair<int_const,unsigned_char>>,std::less<int>,std::allocator<std::pair<int_const,unsigned_char>>>
  a_Stack_150 [4];
  undefined4 local_14c;
  _Rb_tree_node *local_148;
  _Rb_tree_node *local_144;
  _Rb_tree_node *local_140;
  undefined4 local_13c;
  undefined4 local_138;
  undefined4 local_134;
  int *local_130;
  undefined4 local_12c;
  int local_128;
  int local_124;
  int local_120;
  int local_11c;
  undefined4 local_118;
  int local_114;
  int local_110;
  undefined4 local_10c;
  int *local_108;
  undefined4 local_104;
  int local_100;
  int local_fc;
  int local_f8;
  int local_f4;
  undefined4 local_f0;
  int local_ec;
  int local_e8;
  int local_e4;
  int local_e0;
  int local_dc;
  int local_d8;
  int local_d4;
  int local_d0;
  undefined1 auStack_cc [36];
  undefined4 *local_a8;
  int *local_a4;
  map<int,std::set<int,std::less<int>,std::allocator<int>>,std::less<int>,std::allocator<std::pair<int_const,std::set<int,std::less<int>,std::allocator<int>>>>>
  *local_a0;
  int local_98;
  int local_94;
  int local_90;
  int local_8c;
  int local_88;
  int local_84;
  int local_80;
  undefined1 auStack_7c [36];
  int local_58;
  undefined4 *local_54;
  int *local_50;
  _Rb_tree<int,std::pair<int_const,unsigned_char>,std::_Select1st<std::pair<int_const,unsigned_char>>,std::less<int>,std::allocator<std::pair<int_const,unsigned_char>>>
  *local_4c;
  int local_44;
  
  piVar10 = *(int **)(DAT_0013245c + 0x132252 + DAT_00132460);
  local_44 = *piVar10;
  local_1e4 = FUN_0014d1dc();
  piVar4 = (int *)FUN_00205d68();
  iVar14 = 0;
  (**(code **)(*piVar4 + 0x30))();
  local_184 = 0;
  local_194 = 0;
  local_190 = (_Rb_tree_node *)0x0;
  local_17c = 0;
  local_178 = (_Rb_tree_node *)0x0;
  local_16c = 0;
  local_18c = (_Rb_tree_node *)&local_194;
  local_188 = (_Rb_tree_node *)&local_194;
  local_174 = (_Rb_tree_node *)&local_17c;
  local_170 = (_Rb_tree_node *)&local_17c;
  if (0 < param_4) {
    iVar15 = DAT_00132464 + 0x1322cc;
    iVar17 = DAT_00132468 + 0x1322ce;
    do {
      while (local_110 = *(int *)(param_3[2] + iVar14 * 4), local_110 < 1) {
LAB_001322ce:
        iVar14 = iVar14 + 1;
        if (param_4 == iVar14) goto LAB_0013235e;
      }
      FUN_00148b5c(local_1e4,iVar14,&local_e8,&local_98);
      iVar5 = FUN_00127518(param_1,local_e8,local_98);
      if (iVar5 == -1) {
        p_Var6 = (_Rb_tree_node *)&local_194;
        p_Var12 = local_190;
        if (local_190 == (_Rb_tree_node *)0x0) {
LAB_00132850:
          local_1e0 = &local_110;
          p_Var6 = (_Rb_tree_node *)
                   std::
                   _Rb_tree<int,std::pair<int_const,int>,std::_Select1st<std::pair<int_const,int>>,std::less<int>,std::allocator<std::pair<int_const,int>>>
                   ::
                   _M_emplace_hint_unique<std::piecewise_construct_t_const&,std::tuple<int_const&>,std::tuple<>>
                             (a_Stack_198,p_Var6,iVar17,&local_1e0,auStack_1f8);
        }
        else {
          do {
            if (*(int *)(p_Var12 + 0x10) < local_110) {
              p_Var11 = *(_Rb_tree_node **)(p_Var12 + 0xc);
            }
            else {
              p_Var11 = *(_Rb_tree_node **)(p_Var12 + 8);
              p_Var6 = p_Var12;
            }
            p_Var12 = p_Var11;
          } while (p_Var11 != (_Rb_tree_node *)0x0);
          if ((p_Var6 == (_Rb_tree_node *)&local_194) || (local_110 < *(int *)(p_Var6 + 0x10)))
          goto LAB_00132850;
        }
        *(int *)(p_Var6 + 0x14) = *(int *)(p_Var6 + 0x14) + 1;
      }
      iVar5 = FUN_00127804(param_1,local_e8,local_98);
      if (iVar5 == 0) goto LAB_001322ce;
      p_Var6 = (_Rb_tree_node *)&local_17c;
      p_Var12 = local_178;
      if (local_178 == (_Rb_tree_node *)0x0) {
LAB_00132336:
        local_1dc = &local_110;
        p_Var6 = (_Rb_tree_node *)
                 std::
                 _Rb_tree<int,std::pair<int_const,int>,std::_Select1st<std::pair<int_const,int>>,std::less<int>,std::allocator<std::pair<int_const,int>>>
                 ::
                 _M_emplace_hint_unique<std::piecewise_construct_t_const&,std::tuple<int_const&>,std::tuple<>>
                           (a_Stack_180,p_Var6,iVar15,&local_1dc,auStack_1f4);
      }
      else {
        do {
          if (*(int *)(p_Var12 + 0x10) < local_110) {
            p_Var11 = *(_Rb_tree_node **)(p_Var12 + 0xc);
          }
          else {
            p_Var11 = *(_Rb_tree_node **)(p_Var12 + 8);
            p_Var6 = p_Var12;
          }
          p_Var12 = p_Var11;
        } while (p_Var11 != (_Rb_tree_node *)0x0);
        if ((p_Var6 == (_Rb_tree_node *)&local_17c) || (local_110 < *(int *)(p_Var6 + 0x10)))
        goto LAB_00132336;
      }
      iVar14 = iVar14 + 1;
      *(int *)(p_Var6 + 0x14) = *(int *)(p_Var6 + 0x14) + 1;
    } while (param_4 != iVar14);
LAB_0013235e:
    if (local_16c != 0) goto LAB_00132368;
  }
  _rrlogmP(3,6,1,0x189,DAT_00132c20 + 0x13299c,DAT_00132c1c + 0x132998,DAT_00132c18 + 0x132996);
  local_1a4 = local_178;
  if (local_178 == (_Rb_tree_node *)0x0) {
    local_1a0 = (_Rb_tree_node *)0x0;
  }
  else {
    p_Var6 = *(_Rb_tree_node **)(local_170 + 8);
    *(undefined4 *)(local_178 + 4) = 0;
    local_1a0 = local_170;
    if (p_Var6 != (_Rb_tree_node *)0x0) {
      local_1a0 = p_Var6;
    }
  }
  local_178 = (_Rb_tree_node *)0x0;
  local_16c = 0;
  local_19c = a_Stack_180;
  local_174 = (_Rb_tree_node *)&local_17c;
  local_170 = (_Rb_tree_node *)&local_17c;
  if (local_190 != (_Rb_tree_node *)0x0) {
    local_178 = std::
                _Rb_tree<int,std::pair<int_const,int>,std::_Select1st<std::pair<int_const,int>>,std::less<int>,std::allocator<std::pair<int_const,int>>>
                ::
                _M_copy<std::_Rb_tree<int,std::pair<int_const,int>,std::_Select1st<std::pair<int_const,int>>,std::less<int>,std::allocator<std::pair<int_const,int>>>::_Reuse_or_alloc_node>
                          (a_Stack_180,local_190,(_Rb_tree_node *)&local_17c,
                           (_Reuse_or_alloc_node *)&local_1a4);
    p_Var6 = local_178;
    do {
      local_174 = p_Var6;
      p_Var6 = *(_Rb_tree_node **)(local_174 + 8);
      p_Var12 = local_178;
    } while (p_Var6 != (_Rb_tree_node *)0x0);
    do {
      local_170 = p_Var12;
      p_Var12 = *(_Rb_tree_node **)(local_170 + 0xc);
    } while (p_Var12 != (_Rb_tree_node *)0x0);
    local_16c = local_184;
  }
  std::
  _Rb_tree<int,std::pair<int_const,int>,std::_Select1st<std::pair<int_const,int>>,std::less<int>,std::allocator<std::pair<int_const,int>>>
  ::_M_erase(local_19c,local_1a4);
LAB_00132368:
  piVar4 = (int *)(&DAT_00100010 + param_1);
  local_154 = 0;
  local_15c = &local_164;
  local_164 = 0;
  local_160 = (_Rb_tree_node *)0x0;
  local_158 = local_15c;
  FUN_001b2214(&local_e8);
  local_e4 = *piVar4;
  local_e0 = *(int *)(&DAT_00100014 + param_1);
  local_dc = *(int *)(&DAT_00100018 + param_1);
  local_d8 = *(int *)(&DAT_0010001c + param_1);
  if (local_dc - local_e4 < 0) {
    local_d4 = 0;
  }
  else {
    local_d4 = (local_dc - local_e4) + 1;
  }
  local_e8 = DAT_0013246c + 0x1323c4;
  if (local_d8 - local_e0 < 0) {
    local_d0 = 0;
  }
  else {
    local_d0 = (local_d8 - local_e0) + 1;
  }
  FUN_00126344(auStack_cc,piVar4);
  local_a8 = &local_1e4;
  local_a4 = param_3;
  local_a0 = amStack_168;
  FUN_001250d4(auStack_cc);
  iVar14 = *param_2;
  if (((local_e4 <= iVar14) && (iVar14 <= local_dc)) &&
     (iVar15 = FUN_00124fe4(&local_e4,param_2 + 1), iVar15 != 0)) {
    local_1c4 = 0;
    local_1c0 = 0;
    local_138 = 0;
    local_134 = 0;
    local_130 = (int *)0x0;
    local_12c = 0;
    local_128 = 0;
    local_124 = 0;
    local_120 = 0;
    local_11c = 0;
    local_118 = 0;
    local_114 = 0;
    local_1bc = 0;
    local_1b8 = 0;
    FUN_000e66f8(&local_138,0);
    FUN_0012ba24(&local_138,param_2);
LAB_00132a66:
    if ((local_120 - local_11c >> 3) + ((local_114 - local_124 >> 2) + -1) * 0x40 +
        (local_128 - (int)local_130 >> 3) != 0) {
      local_1c4 = *local_130;
      local_1c0 = local_130[1];
      if (local_130 == (int *)(local_128 + -8)) {
        FUN_00124ffc(&local_138);
      }
      else {
        local_130 = local_130 + 2;
      }
      iVar14 = -1;
      iVar15 = 0;
      do {
        if (iVar14 != 0) {
          local_1bc = local_1c4 + iVar14;
          local_1b8 = local_1c0;
          iVar17 = FUN_00132148(&local_e8,&local_1c4,&local_1bc,&local_138);
          if (iVar17 != 0) break;
          local_1b8 = local_1c0 + iVar14;
          local_1bc = local_1c4;
          iVar17 = FUN_00132148(&local_e8,&local_1c4,&local_1bc,&local_138);
          if (iVar17 != 0) break;
          if (iVar15 == 2) goto LAB_00132a66;
        }
        iVar15 = iVar15 + 1;
        iVar14 = iVar14 + 1;
      } while( true );
    }
    FUN_000d0198(&local_138);
    iVar14 = *param_2;
  }
  local_14c = 0;
  local_148 = (_Rb_tree_node *)0x0;
  local_13c = 0;
  local_144 = (_Rb_tree_node *)&local_14c;
  local_140 = (_Rb_tree_node *)&local_14c;
  iVar14 = FUN_00148b94(local_1e4,iVar14,param_2[1]);
  fVar2 = DAT_00132458;
  if (0 < param_4) {
    iVar15 = DAT_00132470 + 0x132440;
    iVar5 = 0;
    iVar17 = DAT_00132474 + 0x13244c;
    local_224 = 1;
    p_Var16 = (_Reuse_or_alloc_node *)(param_1 + 0x10);
    do {
      while( true ) {
        local_1a4 = (_Rb_tree_node *)((uint)local_1a4 & 0xffffff00);
        FUN_00148b5c(local_1e4,iVar5,&local_138,&local_110);
        if ((*(int *)(param_1 + 0x10003c) < 1) || (0xf < ((byte)*p_Var16 & 0x3f) - 0x10)) break;
        local_1a4 = (_Rb_tree_node *)CONCAT31(local_1a4._1_3_,(char)((byte)*p_Var16 & 0x3f));
LAB_00132478:
        std::
        _Rb_tree<unsigned_char,unsigned_char,std::_Identity<unsigned_char>,std::less<unsigned_char>,std::allocator<unsigned_char>>
        ::_M_insert_unique<unsigned_char_const&>(auStack_1cc);
        iVar20 = FUN_00127804(param_1,local_138,local_110);
        _Var9 = local_1a4._0_1_;
        if (iVar20 == 0) {
          _Var9 = (_Reuse_or_alloc_node)((byte)local_1a4._0_1_ | 0x40);
        }
LAB_00132494:
        iVar5 = iVar5 + 1;
        *p_Var16 = _Var9;
        p_Var16 = p_Var16 + 1;
        if (param_4 == iVar5) goto LAB_001326cc;
      }
      if (local_1a4._0_1_ != (_Reuse_or_alloc_node)0x0) goto LAB_00132478;
      local_98 = *(int *)(param_3[2] + iVar5 * 4);
      _Var9 = (_Reuse_or_alloc_node)0x0;
      if (local_98 < 1) goto LAB_00132494;
      p_Var6 = (_Rb_tree_node *)&local_14c;
      p_Var12 = local_148;
      if (local_148 == (_Rb_tree_node *)0x0) {
LAB_00132512:
        bVar3 = param_6;
        if (*(int *)(param_3[2] + iVar14 * 4) != local_98) {
          bVar3 = param_6 | 1;
        }
        p_Var6 = (_Rb_tree_node *)&local_194;
        p_Var12 = local_190;
        if (local_190 == (_Rb_tree_node *)0x0) {
LAB_00132546:
          local_1d8 = &local_98;
          p_Var6 = (_Rb_tree_node *)
                   std::
                   _Rb_tree<int,std::pair<int_const,int>,std::_Select1st<std::pair<int_const,int>>,std::less<int>,std::allocator<std::pair<int_const,int>>>
                   ::
                   _M_emplace_hint_unique<std::piecewise_construct_t_const&,std::tuple<int_const&>,std::tuple<>>
                             (a_Stack_198,p_Var6,iVar15,&local_1d8,auStack_1f0);
        }
        else {
          do {
            if (*(int *)(p_Var12 + 0x10) < local_98) {
              p_Var11 = *(_Rb_tree_node **)(p_Var12 + 0xc);
            }
            else {
              p_Var11 = *(_Rb_tree_node **)(p_Var12 + 8);
              p_Var6 = p_Var12;
            }
            p_Var12 = p_Var11;
          } while (p_Var11 != (_Rb_tree_node *)0x0);
          if ((p_Var6 == (_Rb_tree_node *)&local_194) || (local_98 < *(int *)(p_Var6 + 0x10)))
          goto LAB_00132546;
        }
        iVar20 = *(int *)(p_Var6 + 0x14);
        p_Var6 = (_Rb_tree_node *)&local_17c;
        p_Var12 = local_178;
        if (local_178 == (_Rb_tree_node *)0x0) {
LAB_00132596:
          local_1d4 = &local_98;
          p_Var6 = (_Rb_tree_node *)
                   std::
                   _Rb_tree<int,std::pair<int_const,int>,std::_Select1st<std::pair<int_const,int>>,std::less<int>,std::allocator<std::pair<int_const,int>>>
                   ::
                   _M_emplace_hint_unique<std::piecewise_construct_t_const&,std::tuple<int_const&>,std::tuple<>>
                             (a_Stack_180,p_Var6,iVar17,&local_1d4,auStack_1ec);
        }
        else {
          do {
            if (*(int *)(p_Var12 + 0x10) < local_98) {
              p_Var11 = *(_Rb_tree_node **)(p_Var12 + 0xc);
            }
            else {
              p_Var11 = *(_Rb_tree_node **)(p_Var12 + 8);
              p_Var6 = p_Var12;
            }
            p_Var12 = p_Var11;
          } while (p_Var11 != (_Rb_tree_node *)0x0);
          if ((p_Var6 == (_Rb_tree_node *)&local_17c) || (local_98 < *(int *)(p_Var6 + 0x10)))
          goto LAB_00132596;
        }
        dVar21 = (double)((float)(longlong)iVar20 * fVar2);
        fVar22 = (float)(longlong)*(int *)(p_Var6 + 0x14) * fVar2;
        dVar23 = (double)fVar22;
        uVar24 = local_138;
        iVar20 = local_110;
        dVar25 = dVar21;
        dVar26 = dVar23;
        _rrlogmP(3,7,1,0x1c0,DAT_00132bdc + 0x1325e4,DAT_00132bd8 + 0x1325dc,DAT_00132bd4 + 0x1325ce
                 ,local_98,local_138,local_110,dVar21,dVar23);
        p_Var6 = (_Rb_tree_node *)&local_14c;
        if (bVar3 == 0) {
LAB_00132620:
          if (local_224 < 0x10) {
            local_1a4 = (_Rb_tree_node *)CONCAT31(local_1a4._1_3_,(char)local_224);
            uVar8 = local_224;
            local_224 = local_224 + 1 & 0xff;
          }
          else {
            local_1a4 = (_Rb_tree_node *)CONCAT31(local_1a4._1_3_,0xf);
            _rrlogmP(3,6,1,0x1d4,DAT_00132c14 + 0x13296e,DAT_00132c10 + 0x13296a,
                     DAT_00132c0c + 0x132968,0xf,uVar24,iVar20,dVar25,dVar26);
            uVar8 = (uint)local_1a4 & 0xff;
          }
          _rrlogmP(3,6,1,0x1d9,DAT_00132be4 + 0x13265a,DAT_00132be8 + 0x13265e,
                   DAT_00132be0 + 0x13264e,local_138,local_110,local_98,uVar8,
                   (int)((ulonglong)dVar25 >> 0x20),dVar26);
          p_Var12 = local_148;
          if (local_148 != (_Rb_tree_node *)0x0) goto LAB_0013267c;
LAB_00132698:
          local_1d0 = &local_98;
          p_Var6 = (_Rb_tree_node *)
                   std::
                   _Rb_tree<int,std::pair<int_const,unsigned_char>,std::_Select1st<std::pair<int_const,unsigned_char>>,std::less<int>,std::allocator<std::pair<int_const,unsigned_char>>>
                   ::
                   _M_emplace_hint_unique<std::piecewise_construct_t_const&,std::tuple<int_const&>,std::tuple<>>
                             (a_Stack_150,p_Var6,DAT_00132bec + 0x1326a6,&local_1d0,auStack_1e8);
        }
        else {
          if (param_7 == '\0') {
            if ((0.0 < fVar22) &&
               (((-1 < (int)((uint)(dVar21 < *(double *)((int)&DAT_001000a0 + param_1)) << 0x1f) ||
                 (-1 < (int)((uint)(dVar23 < *(double *)((int)&DAT_001000b0 + param_1)) << 0x1f)))
                || (iVar7 = std::
                            map<int,std::set<int,std::less<int>,std::allocator<int>>,std::less<int>,std::allocator<std::pair<int_const,std::set<int,std::less<int>,std::allocator<int>>>>>
                            ::operator[](amStack_168,&local_98), 1 < *(uint *)(iVar7 + 0x14)))))
            goto LAB_00132620;
            uVar13 = 0x1cc;
            iVar18 = DAT_00132c00 + 0x13294a;
            iVar7 = DAT_00132c04 + 0x13294c;
            iVar19 = DAT_00132c08 + 0x13294e;
          }
          else {
            if ((-1 < (int)((uint)(dVar21 < *(double *)((int)&DAT_001000a8 + param_1)) << 0x1f)) ||
               (iVar7 = std::
                        map<int,std::set<int,std::less<int>,std::allocator<int>>,std::less<int>,std::allocator<std::pair<int_const,std::set<int,std::less<int>,std::allocator<int>>>>>
                        ::operator[](amStack_168,&local_98), 1 < *(uint *)(iVar7 + 0x14)))
            goto LAB_00132620;
            uVar13 = 0x1c6;
            iVar18 = DAT_00132c24 + 0x132b18;
            iVar7 = DAT_00132c28 + 0x132b1a;
            iVar19 = DAT_00132c2c + 0x132b1c;
          }
          _rrlogmP(3,6,1,uVar13,iVar19,iVar7,iVar18,local_98,uVar24,iVar20,dVar25,dVar26);
          p_Var12 = local_148;
          if (local_148 == (_Rb_tree_node *)0x0) goto LAB_00132698;
LAB_0013267c:
          do {
            if (*(int *)(p_Var12 + 0x10) < local_98) {
              p_Var11 = *(_Rb_tree_node **)(p_Var12 + 0xc);
            }
            else {
              p_Var11 = *(_Rb_tree_node **)(p_Var12 + 8);
              p_Var6 = p_Var12;
            }
            p_Var12 = p_Var11;
          } while (p_Var11 != (_Rb_tree_node *)0x0);
          if ((p_Var6 == (_Rb_tree_node *)&local_14c) || (local_98 < *(int *)(p_Var6 + 0x10)))
          goto LAB_00132698;
        }
        p_Var6[0x14] = (_Rb_tree_node)local_1a4._0_1_;
        _Var1 = (_Rb_tree_node)local_1a4._0_1_;
      }
      else {
        do {
          if (*(int *)(p_Var12 + 0x10) < local_98) {
            p_Var11 = *(_Rb_tree_node **)(p_Var12 + 0xc);
          }
          else {
            p_Var11 = *(_Rb_tree_node **)(p_Var12 + 8);
            p_Var6 = p_Var12;
          }
          p_Var12 = p_Var11;
        } while (p_Var11 != (_Rb_tree_node *)0x0);
        if ((p_Var6 == (_Rb_tree_node *)&local_14c) || (local_98 < *(int *)(p_Var6 + 0x10)))
        goto LAB_00132512;
        _Var1 = p_Var6[0x14];
        local_1a4 = (_Rb_tree_node *)CONCAT31(local_1a4._1_3_,_Var1);
      }
      if (_Var1 != (_Rb_tree_node)0x0) goto LAB_00132478;
      iVar5 = iVar5 + 1;
      *p_Var16 = (_Reuse_or_alloc_node)0x0;
      p_Var16 = p_Var16 + 1;
    } while (param_4 != iVar5);
  }
LAB_001326cc:
  iVar15 = *param_3;
  iVar14 = param_3[1];
  *(int *)(param_1 + 8) = iVar15;
  *(int *)(param_1 + 0xc) = iVar14;
  *(int *)(param_1 + 0x10003c) = iVar14 * iVar15;
  FUN_001b2214(&local_98);
  local_94 = *piVar4;
  local_90 = *(int *)(&DAT_00100014 + param_1);
  local_8c = *(int *)(&DAT_00100018 + param_1);
  local_88 = *(int *)(&DAT_0010001c + param_1);
  if (local_8c - local_94 < 0) {
    local_84 = 0;
  }
  else {
    local_84 = (local_8c - local_94) + 1;
  }
  local_98 = DAT_00132bf0 + 0x132722;
  if (local_88 - local_90 < 0) {
    local_80 = 0;
  }
  else {
    local_80 = (local_88 - local_90) + 1;
  }
  FUN_00126344(auStack_7c,piVar4);
  local_58 = param_1;
  local_54 = &local_1e4;
  local_50 = param_3;
  local_4c = a_Stack_150;
  FUN_001250d4(auStack_7c);
  iVar14 = *param_2;
  if (((local_94 <= iVar14) && (iVar14 <= local_8c)) &&
     (iVar15 = FUN_00124fe4(&local_94,param_2 + 1), iVar15 != 0)) {
    local_1b4 = 0;
    local_1b0 = 0;
    local_110 = 0;
    local_10c = 0;
    local_108 = (int *)0x0;
    local_104 = 0;
    local_100 = 0;
    local_fc = 0;
    local_f8 = 0;
    local_f4 = 0;
    local_f0 = 0;
    local_ec = 0;
    local_1ac = 0;
    local_1a8 = 0;
    FUN_000e66f8(&local_110,0);
    FUN_0012ba24(&local_110,param_2);
LAB_0013279c:
    if ((local_f8 - local_f4 >> 3) + ((local_ec - local_fc >> 2) + -1) * 0x40 +
        (local_100 - (int)local_108 >> 3) != 0) {
      local_1b4 = *local_108;
      local_1b0 = local_108[1];
      if (local_108 == (int *)(local_100 + -8)) {
        FUN_00124ffc(&local_110);
      }
      else {
        local_108 = local_108 + 2;
      }
      iVar14 = -1;
      iVar15 = 0;
      do {
        if (iVar14 != 0) {
          local_1ac = local_1b4 + iVar14;
          local_1a8 = local_1b0;
          iVar17 = FUN_0012d22c(&local_98,&local_1b4,&local_1ac,&local_110);
          if (iVar17 != 0) break;
          local_1a8 = local_1b0 + iVar14;
          local_1ac = local_1b4;
          iVar17 = FUN_0012d22c(&local_98,&local_1b4,&local_1ac,&local_110);
          if (iVar17 != 0) break;
          if (iVar15 == 2) goto LAB_0013279c;
        }
        iVar15 = iVar15 + 1;
        iVar14 = iVar14 + 1;
      } while( true );
    }
    FUN_000d0198(&local_110);
    iVar14 = *param_2;
  }
  _rrlogmP(3,6,1,0x20d,DAT_00132bf8 + 0x1328a6,DAT_00132bfc + 0x1328aa,DAT_00132bf4 + 0x13289a,
           local_13c,iVar14,param_2[1]);
  FUN_00124a74(&local_98);
  std::
  _Rb_tree<int,std::pair<int_const,unsigned_char>,std::_Select1st<std::pair<int_const,unsigned_char>>,std::less<int>,std::allocator<std::pair<int_const,unsigned_char>>>
  ::_M_erase(a_Stack_150,local_148);
  FUN_00124abc(&local_e8);
  std::
  _Rb_tree<int,std::pair<int_const,std::set<int,std::less<int>,std::allocator<int>>>,std::_Select1st<std::pair<int_const,std::set<int,std::less<int>,std::allocator<int>>>>,std::less<int>,std::allocator<std::pair<int_const,std::set<int,std::less<int>,std::allocator<int>>>>>
  ::_M_erase((_Rb_tree<int,std::pair<int_const,std::set<int,std::less<int>,std::allocator<int>>>,std::_Select1st<std::pair<int_const,std::set<int,std::less<int>,std::allocator<int>>>>,std::less<int>,std::allocator<std::pair<int_const,std::set<int,std::less<int>,std::allocator<int>>>>>
              *)amStack_168,local_160);
  std::
  _Rb_tree<int,std::pair<int_const,int>,std::_Select1st<std::pair<int_const,int>>,std::less<int>,std::allocator<std::pair<int_const,int>>>
  ::_M_erase(a_Stack_180,local_178);
  std::
  _Rb_tree<int,std::pair<int_const,int>,std::_Select1st<std::pair<int_const,int>>,std::less<int>,std::allocator<std::pair<int_const,int>>>
  ::_M_erase(a_Stack_198,local_190);
  if (local_44 == *piVar10) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(1);
}

