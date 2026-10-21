/* Decompiled C, NOT recovered source; need not compile.
 * Binary: rr_loader
 * SHA256: 020d6d7de7d282ecec3e845e4664113b11df82656701d42de7e901595c5f5125
 * Function VA: 0x00017038
 */

/* rrloader::RRPluginManager::final() */

void __thiscall rrloader::RRPluginManager::final(RRPluginManager *this)

{
  int iVar1;
  RRPluginManager *pRVar2;
  RRPluginManager *pRVar3;
  RRPluginManager *pRVar4;
  RRPlugin *this_00;
  RRPluginManager *pRVar5;
  
  pRVar5 = this + 4;
  pRVar2 = pRVar5;
  if (pRVar5 != *(RRPluginManager **)(this + 0xc)) {
    do {
      iVar1 = std::_Rb_tree_decrement((_Rb_tree_node_base *)pRVar2);
      RRPlugin::final(*(RRPlugin **)(iVar1 + 0x14));
      pRVar2 = (RRPluginManager *)std::_Rb_tree_decrement((_Rb_tree_node_base *)pRVar2);
      pRVar4 = *(RRPluginManager **)(this + 0xc);
    } while (pRVar4 != pRVar2);
    pRVar3 = pRVar5;
    if (pRVar5 != pRVar2) {
      do {
        while( true ) {
          pRVar2 = (RRPluginManager *)std::_Rb_tree_decrement((_Rb_tree_node_base *)pRVar3);
          this_00 = *(RRPlugin **)(pRVar2 + 0x14);
          if (this_00 != (RRPlugin *)0x0) break;
          pRVar3 = pRVar2;
          if (pRVar4 == pRVar2) goto LAB_0001709e;
        }
        RRPlugin::~RRPlugin(this_00);
        operator_delete(this_00);
        pRVar3 = (RRPluginManager *)std::_Rb_tree_decrement((_Rb_tree_node_base *)pRVar3);
        pRVar4 = *(RRPluginManager **)(this + 0xc);
      } while (pRVar4 != pRVar3);
    }
  }
LAB_0001709e:
  std::
  _Rb_tree<unsigned_char,std::pair<unsigned_char_const,rrloader::RRPlugin*>,std::_Select1st<std::pair<unsigned_char_const,rrloader::RRPlugin*>>,std::less<unsigned_char>,std::allocator<std::pair<unsigned_char_const,rrloader::RRPlugin*>>>
  ::_M_erase((_Rb_tree<unsigned_char,std::pair<unsigned_char_const,rrloader::RRPlugin*>,std::_Select1st<std::pair<unsigned_char_const,rrloader::RRPlugin*>>,std::less<unsigned_char>,std::allocator<std::pair<unsigned_char_const,rrloader::RRPlugin*>>>
              *)this,*(_Rb_tree_node **)(this + 8));
  *(RRPluginManager **)(this + 0xc) = pRVar5;
  *(RRPluginManager **)(this + 0x10) = pRVar5;
  *(undefined4 *)(this + 8) = 0;
  *(undefined4 *)(this + 0x14) = 0;
  return;
}

