/* Decompiled C, NOT recovered source; need not compile.
 * Binary: rr_loader
 * SHA256: 020d6d7de7d282ecec3e845e4664113b11df82656701d42de7e901595c5f5125
 * Function VA: 0x000188f8
 */

/* rrloader::RRLoader::init() */

int __thiscall rrloader::RRLoader::init(RRLoader *this)

{
  int iVar1;
  
  iVar1 = RREnv::checkDaemon((RREnv *)this);
  if (iVar1 != 0) {
    rr_loader_debug_log(6,"I #2821\n");
    iVar1 = daemonInit(this);
    if (iVar1 == 0) {
      rr_loader_debug_log(3,"F #2822\n");
      return 0;
    }
  }
  rr_loader_debug_log(6,"I #2823\n");
  iVar1 = initSigaction();
  if (iVar1 != 0) {
    rr_loader_debug_log(6,"I #2825\n");
    iVar1 = RRConf::init((RRConf *)(this + 0x14));
    if (iVar1 == 0) {
      rr_loader_debug_log(3,"F #2826\n");
      iVar1 = 0;
    }
    else {
      iVar1 = RREnv::checkDaemon((RREnv *)this);
      if (((iVar1 != 0) && (iVar1 = RRConf::getNode((char *)(this + 0x14)), iVar1 != 0)) &&
         (iVar1 = cJSON_IsString(), iVar1 != 0)) {
        redirectFds((char *)this);
      }
      rr_loader_debug_log(6,"I #2827\n");
      iVar1 = RREnv::init((RREnv *)this);
      if (iVar1 == 0) {
        rr_loader_debug_log(3,"F #2828\n");
        return 0;
      }
      rr_loader_debug_log(6,"I #2829\n");
      iVar1 = RRTimerManager::init((RRTimerManager *)(this + 0x94));
      if (iVar1 == 0) {
        rr_loader_debug_log(3,"F #2830\n");
        iVar1 = 0;
      }
      else {
        iVar1 = pthread_create((pthread_t *)(this + 0xa0),(pthread_attr_t *)0x0,
                               (__start_routine *)&LAB_00018314_1,(void *)0x0);
        if (iVar1 == 0) {
          rr_loader_debug_log(6,"I #2832\n");
          iVar1 = RRPluginManager::init((RRPluginManager *)(this + 0x18));
          if (iVar1 == 0) {
            rr_loader_debug_log(3,"F #2833\n");
          }
        }
        else {
          iVar1 = 0;
          rr_loader_debug_log(3,"F #2831\n");
        }
      }
    }
    return iVar1;
  }
  rr_loader_debug_log(3,"F #2824\n");
  return 0;
}

