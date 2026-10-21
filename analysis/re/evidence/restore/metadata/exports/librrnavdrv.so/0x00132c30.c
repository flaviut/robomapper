/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x00132c30
 */

/* WARNING: Restarted to delay deadcode elimination for space: stack */

void FUN_00132c30(int param_1,int param_2,undefined4 param_3)

{
  _Rb_tree<unsigned_char,unsigned_char,std::_Identity<unsigned_char>,std::less<unsigned_char>,std::allocator<unsigned_char>>
  *p_Var1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  SharedSegmentMapData *__s;
  int *piVar6;
  int *piVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  double dVar13;
  double dVar14;
  _Rb_tree<unsigned_char,unsigned_char,std::_Identity<unsigned_char>,std::less<unsigned_char>,std::allocator<unsigned_char>>
  *p_Var15;
  undefined4 uVar16;
  void *local_11c;
  int local_108;
  int local_104;
  void *local_100;
  void *local_fc;
  undefined4 local_f8;
  void *local_f4;
  int local_f0;
  int local_e8;
  _Rb_tree<unsigned_char,unsigned_char,std::_Identity<unsigned_char>,std::less<unsigned_char>,std::allocator<unsigned_char>>
  *local_e4;
  void *local_e0;
  int local_dc;
  _Rb_tree<unsigned_char,unsigned_char,std::_Identity<unsigned_char>,std::less<unsigned_char>,std::allocator<unsigned_char>>
  *local_d8;
  void *local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  int local_c0;
  _Rb_tree<unsigned_char,unsigned_char,std::_Identity<unsigned_char>,std::less<unsigned_char>,std::allocator<unsigned_char>>
  *local_bc;
  int local_b8;
  int local_b4;
  int local_b0;
  int local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined1 auStack_a0 [8];
  undefined4 local_98;
  undefined4 local_8c;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  _Rb_tree<unsigned_char,unsigned_char,std::_Identity<unsigned_char>,std::less<unsigned_char>,std::allocator<unsigned_char>>
  a_Stack_70 [4];
  undefined4 local_6c;
  _Rb_tree_node *local_68;
  undefined4 *local_64;
  undefined4 *local_60;
  undefined4 local_5c;
  undefined1 auStack_58 [36];
  int local_34;
  
  piVar7 = *(int **)(DAT_00133330 + 0x132c4c + DAT_00133334);
  local_34 = *piVar7;
  _rrlogmP(3,6,1,0x34f,DAT_00133340 + 0x132c7e,DAT_0013333c + 0x132c70,DAT_00133338 + 0x132c60,
           *(undefined4 *)(param_1 + 0x10003c),*(undefined4 *)(param_1 + 0x100078),param_2);
  iVar2 = FUN_00168498();
  local_d0 = 0;
  local_cc = 0;
  local_c8 = 0;
  local_c4 = 0;
  local_c0 = 0;
  local_bc = (_Rb_tree<unsigned_char,unsigned_char,std::_Identity<unsigned_char>,std::less<unsigned_char>,std::allocator<unsigned_char>>
              *)0x0;
  FUN_000d5808(&local_d0);
  local_100 = (void *)0x0;
  local_fc = (void *)0x0;
  local_f8 = 0;
  local_b8 = 0;
  local_b4 = 0;
  local_a8 = 0;
  local_a4 = 0;
  local_b0 = -1;
  local_ac = -1;
  uVar3 = FUN_0014d1dc();
  FUN_0014b56c(uVar3,&local_d0,&local_100);
  iVar4 = rrlog_get_model_ver();
  if (iVar4 != 1) {
    FUN_00128358(param_1,iVar2 + -2,&local_b8,&local_100,0,0);
  }
  local_108 = 0;
  local_104 = 0;
  local_11c = (void *)FUN_00127618(param_1,&local_d0,&local_100);
  if (local_11c == (void *)0x0) {
    _rrlogmP(3,3,1,0x35b,DAT_0013339c + 0x133176,DAT_00133398 + 0x133172,DAT_00133394 + 0x133170);
    goto LAB_00133182;
  }
  if (param_2 == 0) {
    FUN_0012a35c(param_1,0);
  }
  else {
    *(undefined4 *)(param_1 + 0x10003c) = 0;
  }
  p_Var1 = local_bc;
  iVar4 = local_c0;
  FUN_0012d4ac(param_1,&local_100,&local_b8,&local_108);
  uVar3 = FUN_00138980();
  FUN_001384c0(&local_f4,uVar3);
  FUN_0012afc8(auStack_a0,param_1,&local_f4);
  iVar11 = (local_f0 - (int)local_f4 >> 2) * -0x33333333;
  _rrlogmP(3,6,1,0x368,DAT_0013334c + 0x132d7c,DAT_00133344 + 0x132d6e,DAT_00133348 + 0x132d6c,
           iVar11,local_8c);
  if ((0 < *(int *)(param_1 + 0x10003c)) && (local_b8 < local_b0)) {
    iVar10 = local_b8;
    do {
      if (local_b4 < local_ac) {
        iVar8 = (*(int *)(param_1 + 8) * (local_b4 - *(int *)(&DAT_00100014 + param_1)) + iVar10) -
                *(int *)(&DAT_00100010 + param_1);
        iVar5 = local_b4;
        do {
          if ((iVar8 < *(int *)(param_1 + 0x10003c) && -1 < iVar8) &&
             ((*(byte *)(param_1 + iVar8 + 0x10) & 0x3f) - 0x10 < 0x10)) {
            iVar10 = 1;
            goto LAB_00132e04;
          }
          iVar5 = iVar5 + 1;
          iVar8 = iVar8 + *(int *)(param_1 + 8);
        } while (iVar5 != local_ac);
      }
      iVar10 = iVar10 + 1;
    } while (iVar10 != local_b0);
  }
  iVar10 = 0;
LAB_00132e04:
  iVar5 = rrlog_get_model_ver();
  uVar3 = local_8c;
  if (iVar5 != 1) {
    piVar6 = (int *)(&DAT_00100010 + param_1);
    if (iVar10 == 0) {
      piVar6 = &local_b8;
    }
    FUN_00128358(param_1,iVar2 + -1,piVar6,&local_100,&local_f4,auStack_a0);
    uVar3 = local_8c;
  }
  if (iVar10 != 0) {
    FUN_00126858(param_1,&local_100);
  }
  if (local_100 == local_fc) {
LAB_001331a2:
    _rrlogmP(3,6,1,0x38c,DAT_001333a8 + 0x1331b8,DAT_001333a4 + 0x1331b4,DAT_001333a0 + 0x1331b2,
             iVar11,uVar3);
  }
  else {
    uVar9 = 0;
    uVar12 = uVar9;
    do {
      if (*(char *)((int)local_100 + uVar9) == -1) {
        uVar12 = 1;
      }
      else {
        *(undefined1 *)((int)local_100 + uVar9) = 0;
      }
      uVar9 = uVar9 + 1;
    } while (uVar9 < (uint)((int)local_fc - (int)local_100));
    if (uVar12 == 0) goto LAB_001331a2;
    local_e0 = local_100;
    local_88 = local_b8;
    local_84 = local_b4;
    local_e4 = local_bc;
    local_d8 = local_bc;
    local_80 = local_b0;
    local_7c = local_ac;
    if (local_b0 - local_b8 < 0) {
      local_78 = 0;
    }
    else {
      local_78 = (local_b0 - local_b8) + 1;
    }
    if (local_ac - local_b4 < 0) {
      local_74 = 0;
    }
    else {
      local_74 = (local_ac - local_b4) + 1;
    }
    local_e8 = local_c0;
    local_dc = local_c0;
    _rrlogmP(3,6,1,0x398,DAT_00133354 + 0x132ecc,DAT_00133358 + 0x132ed0,DAT_00133350 + 0x132eba,
             (int)local_fc - (int)local_100,local_bc,local_c0,iVar10);
    if (0x1fc00000 < (uint)((int)local_fc - (int)local_100)) {
                    /* WARNING: Subroutine does not return */
      __cxa_throw_bad_array_new_length();
    }
    local_d4 = operator_new__(((int)local_fc - (int)local_100) * 4);
    FUN_00128358(param_1,iVar2,&DAT_00100010 + param_1,&local_100,0,0);
    FUN_00127b78(param_1,local_e0,local_e8,local_e4,1);
    FUN_00127d80(param_1,auStack_58);
    iVar11 = rs::segment_gridmap(&local_e8,(vector *)0x0,(vector *)0x0,1,auStack_58,
                                 (SegmentMap_t *)&local_dc);
    FUN_00127b78(param_1,local_d4,local_dc,local_d8,4);
    if (iVar11 == 0) {
      uVar3 = *(undefined4 *)(param_1 + 0x100078);
      _rrlogmP(3,6,1,0x3d1,DAT_00133364 + 0x132f78,DAT_00133360 + 0x132f74,DAT_0013335c + 0x132f72,
               uVar3);
      if (*(int *)(param_1 + 0x10003c) != 0) {
        memset(local_d4,0,((int)local_fc - (int)local_100) * 4);
        goto LAB_00132fe0;
      }
      _rrlogmP(3,6,1,0x3d3,DAT_00133370 + 0x132fa0,DAT_0013336c + 0x132f9c,DAT_00133368 + 0x132f9a,
               uVar3);
      local_11c = local_d4;
      if (local_d4 != (void *)0x0) {
        local_11c = (void *)0x0;
        operator_delete__(local_d4);
      }
    }
    else {
LAB_00132fe0:
      iVar8 = DAT_00133374 + 0x132fec;
      dVar13 = round((double)(longlong)-(local_c0 / 2));
      dVar14 = round((double)(longlong)-((int)local_bc / 2));
      uVar3 = (undefined4)(longlong)dVar13;
      uVar16 = (undefined4)(longlong)dVar14;
      p_Var15 = local_e4;
      iVar5 = local_e8;
      _rrlogmP(3,6,1,0x3dc,DAT_0013337c + 0x133034,DAT_00133378 + 0x13302c,iVar8,local_e4,local_e8,
               uVar3,uVar16);
      local_64 = &local_6c;
      local_68 = (_Rb_tree_node *)0x0;
      local_6c = 0;
      local_5c = 0;
      local_60 = local_64;
      if (iVar11 != 0) {
        if ((0 < *(int *)(param_1 + 0x10003c)) && (iVar11 = rrlog_get_model_ver(), iVar11 != 1)) {
          FUN_001280c4(auStack_58,&local_b8);
          FUN_001264f0(param_1,DAT_001333ac + 0x133218,auStack_58,iVar2 + -3,0);
        }
        FUN_00128178(param_1,DAT_001333b0 + 0x133230,&local_b8,local_d4,iVar2 + -2);
        p_Var15 = a_Stack_70;
        FUN_0013223c(param_1,&local_108,&local_dc,(int)p_Var1 * iVar4,&local_b8,iVar10,param_3,
                     p_Var15);
      }
      iVar4 = (*(int *)(param_1 + 8) * (local_104 - *(int *)(&DAT_00100014 + param_1)) + local_108)
              - *(int *)(&DAT_00100010 + param_1);
      if (((iVar4 < 0) || (*(int *)(param_1 + 0x10003c) <= iVar4)) ||
         ((*(byte *)(iVar4 + param_1 + 0x10) & 0x3f) == 0)) {
        iVar4 = FUN_00130f1c(param_1,&local_108,&local_88);
        if (iVar4 == 0) {
          _rrlogmP(3,6,1,0x3f0,DAT_001333c8 + 0x1332a0,DAT_001333c4 + 0x13329c,
                   DAT_001333c0 + 0x13329a,p_Var15,iVar5,uVar3,uVar16);
        }
        else {
          _rrlogmP(3,6,1,0x3ed,DAT_001333bc + 0x13327e,DAT_001333b8 + 0x133276,
                   DAT_001333b4 + 0x133272,local_108,local_104,uVar3,uVar16);
        }
      }
      FUN_0012e95c(param_1,&local_108,&local_88);
      FUN_0012e12c(param_1,&local_108,&local_88);
      FUN_0012cb14(param_1,&local_108,&local_88);
      iVar4 = rrlog_get_model_ver();
      if (iVar4 != 1) {
        FUN_001280c4(auStack_58,&local_88);
        FUN_001264f0(param_1,DAT_00133380 + 0x1330ce,auStack_58,iVar2 + -1,1);
      }
      FUN_001280c4(auStack_58,&local_88);
      FUN_001264f0(param_1,DAT_00133384 + 0x1330e4,auStack_58,iVar2,0);
      __s = operator_new(0x1001a4);
      memset(__s,0,0x1001a4);
      memcpy(__s + 4,(void *)(param_1 + 4),0x10000c);
      *__s = (SharedSegmentMapData)0x1;
      SetSharedSegmentMap(__s);
      _rrlogmP(3,6,1,0x402,DAT_00133390 + 0x13313a,DAT_0013338c + 0x133134,DAT_00133388 + 0x133130,
               __s[0x100010]);
      if (local_d4 != (void *)0x0) {
        operator_delete__(local_d4);
      }
      local_d4 = (void *)0x0;
      operator_delete(__s);
      std::
      _Rb_tree<unsigned_char,unsigned_char,std::_Identity<unsigned_char>,std::less<unsigned_char>,std::allocator<unsigned_char>>
      ::_M_erase(a_Stack_70,local_68);
    }
  }
  FUN_001294f4(auStack_a0,local_98);
  if (local_f4 != (void *)0x0) {
    operator_delete(local_f4);
  }
LAB_00133182:
  if (local_100 != (void *)0x0) {
    operator_delete(local_100);
  }
  if (local_34 != *piVar7) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(local_11c);
  }
  return;
}

