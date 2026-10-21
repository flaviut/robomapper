/* Decompiled C, NOT recovered source; need not compile.
 * Binary: rr_loader
 * SHA256: 020d6d7de7d282ecec3e845e4664113b11df82656701d42de7e901595c5f5125
 * Function VA: 0x00018c28
 */

/* WARNING: Removing unreachable block (ram,0x00018e88) */
/* rrloader::RRPlugin::init() */

void __thiscall rrloader::RRPlugin::init(RRPlugin *this)

{
  bool bVar1;
  RREnv *this_00;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  string *psVar6;
  char *__s;
  code *pcVar7;
  int *piVar8;
  int local_28;
  int local_24;
  
  local_24 = __stack_chk_guard;
  this_00 = (RREnv *)RRLoader::GetInstance();
  iVar2 = cJSON_GetObjectItem(*(undefined4 *)(this + 0x8c),"common");
  if ((iVar2 == 0) || (iVar3 = cJSON_IsObject(), iVar3 == 0)) {
    iVar2 = 0;
    rr_loader_debug_log(3,"E #2851\n");
    goto LAB_00018c6c;
  }
  iVar3 = cJSON_GetObjectItem(iVar2,&DAT_0001df8c);
  if ((iVar3 == 0) || (iVar4 = cJSON_IsString(), iVar4 == 0)) {
    iVar2 = 0;
    rr_loader_debug_log(3,"E #2852\n");
    goto LAB_00018c6c;
  }
  uVar5 = cJSON_GetStringValue(iVar3);
  *(undefined4 *)(this + 0x88) = uVar5;
  iVar3 = cJSON_GetObjectItem(iVar2,"plugin");
  if ((iVar3 == 0) || (iVar4 = cJSON_IsString(), iVar4 == 0)) {
    iVar2 = 0;
    rr_loader_debug_log(3,"E #2853\n");
    goto LAB_00018c6c;
  }
  iVar2 = cJSON_GetObjectItem(iVar2,"maxQueueCapacity");
  if (iVar2 != 0) {
    iVar4 = cJSON_IsNumber();
    if (iVar4 == 0) {
      rr_loader_debug_log(3,"E #2854\n");
      iVar2 = 0;
      goto LAB_00018c6c;
    }
    if (*(int *)(iVar2 + 0x14) < 1) {
      iVar2 = 0;
      rr_loader_debug_log(3,"E #2855\n");
      goto LAB_00018c6c;
    }
    rrMsgQueue::setMaxCapacity((rrMsgQueue *)this,*(int *)(iVar2 + 0x14));
  }
  psVar6 = (string *)RREnv::getPluginsPath(this_00);
  __s = (char *)cJSON_GetStringValue(iVar3);
  std::string::string((string *)&local_28,psVar6);
  strlen(__s);
  std::string::append((char *)&local_28,(uint)__s);
  iVar3 = dlopen(local_28,0x102);
  iVar2 = local_28;
  *(int *)(this + 0x90) = iVar3;
  if (iVar3 == 0) {
    uVar5 = dlerror();
    rr_loader_debug_log(3,"F #2856`%s`%s\n",iVar2,uVar5);
LAB_00018dfa:
    iVar2 = 0;
  }
  else {
    pcVar7 = (code *)dlsym(iVar3,"rr_load_plugin");
    if (pcVar7 == (code *)0x0) {
      dlclose(*(undefined4 *)(this + 0x90));
      rr_loader_debug_log(3,"F #2857`%s\n",local_28);
      goto LAB_00018dfa;
    }
    iVar2 = (*pcVar7)();
    *(int *)(this + 0x80) = iVar2;
    if (iVar2 == 0) {
      dlclose(*(undefined4 *)(this + 0x90));
      rr_loader_debug_log(3,"F #2858`%s\n",local_28);
      goto LAB_00018dfa;
    }
    if (((*(code **)(iVar2 + 4) == (code *)0x0) || (*(int *)(iVar2 + 8) == 0)) ||
       (*(int *)(iVar2 + 0x14) == 0)) {
      dlclose(*(undefined4 *)(this + 0x90));
      rr_loader_debug_log(3,"F #2859`%s\n",local_28);
      goto LAB_00018dfa;
    }
    iVar2 = (**(code **)(iVar2 + 4))(this + 0x9c);
    if (iVar2 == 0) {
      dlclose(*(undefined4 *)(this + 0x90));
      rr_loader_debug_log(3,"F #2860`%s\n",local_28);
      goto LAB_00018dfa;
    }
    rr_subscribe_msg(this + 0x9c,4);
    rr_loader_debug_log(6,"I #2861`%s`%u\n",local_28,**(undefined4 **)(this + 0x80));
  }
  if ((allocator *)(local_28 + -0xc) != (allocator *)std::string::_Rep::_S_empty_rep_storage) {
    piVar8 = (int *)(local_28 + -4);
    DataMemoryBarrier(0x1b);
    do {
      ExclusiveAccess(piVar8);
      iVar3 = *piVar8;
      bVar1 = (bool)hasExclusiveAccess(piVar8);
    } while (!bVar1);
    *piVar8 = iVar3 + -1;
    DataMemoryBarrier(0x1b);
    if (iVar3 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_28 + -0xc));
    }
  }
LAB_00018c6c:
  if (local_24 != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(iVar2);
  }
  return;
}

