/* Decompiled C, NOT recovered source; need not compile.
 * Binary: rr_loader
 * SHA256: 020d6d7de7d282ecec3e845e4664113b11df82656701d42de7e901595c5f5125
 * Function VA: 0x000170d8
 */

/* WARNING: Removing unreachable block (ram,0x00017328) */
/* rrloader::RRPluginManager::loadPlugin(unsigned char, cJSON const*) */

void __thiscall
rrloader::RRPluginManager::loadPlugin(RRPluginManager *this,uchar param_1,cJSON *param_2)

{
  void *__s2;
  RRPlugin *this_00;
  int iVar1;
  char *pcVar2;
  undefined4 uVar3;
  uint uVar4;
  RRPluginManager *pRVar5;
  RRPluginManager *pRVar6;
  RRPluginManager *pRVar7;
  RRPluginManager *pRVar8;
  uint uVar9;
  uint uVar10;
  pthread_rwlock_t *__rwlock;
  int *piVar11;
  bool bVar12;
  string *local_54;
  void *local_50;
  RRPluginManager local_41;
  allocator aaStack_40 [8];
  undefined1 auStack_38 [4];
  void *local_34;
  RRPluginManager *local_30;
  int local_2c;
  
  local_2c = __stack_chk_guard;
  local_41 = (RRPluginManager)param_1;
  this_00 = operator_new(0x1d8);
  RRPlugin::RRPlugin(this_00,(uchar)local_41,param_2);
  __rwlock = (pthread_rwlock_t *)(this + 0x30);
  pRVar8 = this + 4;
  pthread_rwlock_wrlock(__rwlock);
  pRVar5 = *(RRPluginManager **)(this + 8);
  pRVar7 = pRVar8;
  if (pRVar5 == (RRPluginManager *)0x0) {
LAB_0001713c:
    local_30 = &local_41;
    iVar1 = std::
            _Rb_tree<unsigned_char,std::pair<unsigned_char_const,rrloader::RRPlugin*>,std::_Select1st<std::pair<unsigned_char_const,rrloader::RRPlugin*>>,std::less<unsigned_char>,std::allocator<std::pair<unsigned_char_const,rrloader::RRPlugin*>>>
            ::
            _M_emplace_hint_unique<std::piecewise_construct_t_const&,std::tuple<unsigned_char_const&>,std::tuple<>>
                      (this,pRVar8,&DAT_0001d6c8,&local_30,&local_34);
    *(RRPlugin **)(iVar1 + 0x14) = this_00;
    pthread_rwlock_unlock(__rwlock);
    iVar1 = RRPlugin::init(this_00);
    if (iVar1 == 0) {
      rr_loader_debug_log(3,"E #2804\n");
      pthread_rwlock_wrlock(__rwlock);
      std::
      _Rb_tree<unsigned_char,std::pair<unsigned_char_const,rrloader::RRPlugin*>,std::_Select1st<std::pair<unsigned_char_const,rrloader::RRPlugin*>>,std::less<unsigned_char>,std::allocator<std::pair<unsigned_char_const,rrloader::RRPlugin*>>>
      ::erase((_Rb_tree<unsigned_char,std::pair<unsigned_char_const,rrloader::RRPlugin*>,std::_Select1st<std::pair<unsigned_char_const,rrloader::RRPlugin*>>,std::less<unsigned_char>,std::allocator<std::pair<unsigned_char_const,rrloader::RRPlugin*>>>
               *)this,(uchar *)&local_41);
      pthread_rwlock_unlock(__rwlock);
LAB_000171e2:
      iVar1 = 0;
      RRPlugin::~RRPlugin(this_00);
      operator_delete(this_00);
      goto LAB_000171f0;
    }
  }
  else {
    do {
      if ((byte)pRVar5[0x10] < (byte)local_41) {
        pRVar6 = *(RRPluginManager **)(pRVar5 + 0xc);
      }
      else {
        pRVar6 = *(RRPluginManager **)(pRVar5 + 8);
        pRVar7 = pRVar5;
      }
      pRVar5 = pRVar6;
    } while (pRVar6 != (RRPluginManager *)0x0);
    bVar12 = pRVar8 == pRVar7;
    pRVar8 = pRVar7;
    if ((bVar12) || ((byte)local_41 < (byte)pRVar7[0x10])) goto LAB_0001713c;
    *(RRPlugin **)(pRVar7 + 0x14) = this_00;
    pthread_rwlock_unlock(__rwlock);
    iVar1 = RRPlugin::init(this_00);
    if (iVar1 == 0) {
      rr_loader_debug_log(3,"E #2804\n");
      pthread_rwlock_wrlock(__rwlock);
      std::
      _Rb_tree<unsigned_char,std::pair<unsigned_char_const,rrloader::RRPlugin*>,std::_Select1st<std::pair<unsigned_char_const,rrloader::RRPlugin*>>,std::less<unsigned_char>,std::allocator<std::pair<unsigned_char_const,rrloader::RRPlugin*>>>
      ::erase((_Rb_tree<unsigned_char,std::pair<unsigned_char_const,rrloader::RRPlugin*>,std::_Select1st<std::pair<unsigned_char_const,rrloader::RRPlugin*>>,std::less<unsigned_char>,std::allocator<std::pair<unsigned_char_const,rrloader::RRPlugin*>>>
               *)this,(uchar *)&local_41);
      pthread_rwlock_unlock(__rwlock);
      goto LAB_000171e2;
    }
  }
  local_54 = (string *)&local_34;
  pRVar7 = this + 0x1c;
  pthread_rwlock_wrlock(__rwlock);
  pcVar2 = (char *)RRPlugin::getName(this_00);
  std::string::string(local_54,pcVar2,aaStack_40);
  __s2 = local_34;
  if (*(RRPluginManager **)(this + 0x20) == (RRPluginManager *)0x0) {
LAB_000172a2:
    local_30 = (RRPluginManager *)local_54;
    pRVar8 = (RRPluginManager *)
             std::
             _Rb_tree<std::string,std::pair<std::string_const,rrloader::RRPlugin*>,std::_Select1st<std::pair<std::string_const,rrloader::RRPlugin*>>,std::less<std::string>,std::allocator<std::pair<std::string_const,rrloader::RRPlugin*>>>
             ::
             _M_emplace_hint_unique<std::piecewise_construct_t_const&,std::tuple<std::string&&>,std::tuple<>>
                       (this + 0x18,pRVar7,&DAT_0001d6c8,&local_30,auStack_38);
    local_50 = local_34;
  }
  else {
    uVar10 = *(uint *)((int)local_34 + -0xc);
    local_50 = local_34;
    pRVar5 = *(RRPluginManager **)(this + 0x20);
    pRVar8 = pRVar7;
    do {
      uVar9 = *(uint *)((int)*(void **)(pRVar5 + 0x10) + -0xc);
      uVar4 = uVar10;
      if (uVar9 <= uVar10) {
        uVar4 = uVar9;
      }
      if ((uVar4 == 0) || (iVar1 = memcmp(*(void **)(pRVar5 + 0x10),__s2,uVar4), iVar1 == 0)) {
        iVar1 = uVar9 - uVar10;
      }
      if (iVar1 < 0) {
        pRVar6 = *(RRPluginManager **)(pRVar5 + 0xc);
      }
      else {
        pRVar6 = *(RRPluginManager **)(pRVar5 + 8);
        pRVar8 = pRVar5;
      }
      pRVar5 = pRVar6;
    } while (pRVar6 != (RRPluginManager *)0x0);
    bVar12 = pRVar8 == pRVar7;
    pRVar7 = pRVar8;
    if (bVar12) goto LAB_000172a2;
    uVar9 = *(uint *)((int)*(void **)(pRVar8 + 0x10) + -0xc);
    uVar4 = uVar10;
    if (uVar9 <= uVar10) {
      uVar4 = uVar9;
    }
    if ((uVar4 == 0) || (iVar1 = memcmp(__s2,*(void **)(pRVar8 + 0x10),uVar4), iVar1 == 0)) {
      iVar1 = uVar10 - uVar9;
    }
    if (iVar1 < 0) goto LAB_000172a2;
  }
  *(RRPlugin **)(pRVar8 + 0x14) = this_00;
  if ((allocator *)((int)local_50 + -0xc) != (allocator *)std::string::_Rep::_S_empty_rep_storage) {
    DataMemoryBarrier(0x1b);
    piVar11 = (int *)((int)local_50 + -4);
    do {
      ExclusiveAccess(piVar11);
      iVar1 = *piVar11;
      bVar12 = (bool)hasExclusiveAccess(piVar11);
    } while (!bVar12);
    *piVar11 = iVar1 + -1;
    DataMemoryBarrier(0x1b);
    if (iVar1 < 1) {
      std::string::_Rep::_M_destroy((allocator *)((int)local_50 + -0xc));
    }
  }
  pthread_rwlock_unlock(__rwlock);
  iVar1 = RRPlugin::start(this_00);
  if (iVar1 == 0) {
    uVar3 = RRPlugin::getName(this_00);
    rr_loader_debug_log(3,"F #2805`%s\n",uVar3);
  }
LAB_000171f0:
  if (local_2c != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(iVar1);
  }
  return;
}

