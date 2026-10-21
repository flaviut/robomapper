/* Decompiled C, NOT recovered source; need not compile.
 * Binary: rr_loader
 * SHA256: 020d6d7de7d282ecec3e845e4664113b11df82656701d42de7e901595c5f5125
 * Function VA: 0x000187fc
 */

/* rrloader::RRLoader::final() */

undefined4 __thiscall rrloader::RRLoader::final(RRLoader *this)

{
  RRTimerManager::final((RRTimerManager *)(this + 0x94));
  rr_loader_debug_log(6,"I #2835\n");
  RRPluginManager::final((RRPluginManager *)(this + 0x18));
  daemonExit();
  rr_loader_debug_log(6,"I #2836\n");
  return 1;
}

