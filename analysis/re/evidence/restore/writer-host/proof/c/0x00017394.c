/* Decompiled C, NOT recovered source; need not compile.
 * Binary: rr_loader
 * SHA256: 020d6d7de7d282ecec3e845e4664113b11df82656701d42de7e901595c5f5125
 * Function VA: 0x00017394
 */

/* rrloader::RRPluginManager::init() */

undefined4 __thiscall rrloader::RRPluginManager::init(RRPluginManager *this)

{
  int iVar1;
  int iVar2;
  cJSON *pcVar3;
  int iVar4;
  
  iVar1 = RRLoader::GetInstance();
  iVar1 = RRConf::getNode((char *)(iVar1 + 0x14));
  if (iVar1 == 0) {
    rr_loader_debug_log(3,"E #2800\n");
    return 0;
  }
  iVar2 = cJSON_IsArray();
  iVar4 = 0;
  if (iVar2 == 0) {
    rr_loader_debug_log(3,"E #2801\n");
    return 0;
  }
  while( true ) {
    iVar2 = cJSON_GetArraySize(iVar1);
    if (iVar2 <= iVar4) {
      return 1;
    }
    pcVar3 = (cJSON *)cJSON_GetArrayItem(iVar1,iVar4);
    iVar2 = cJSON_IsObject();
    if (iVar2 == 0) break;
    iVar2 = loadPlugin(this,(uchar)iVar4,pcVar3);
    if (iVar2 == 0) {
      rr_loader_debug_log(3,"E #2803`%d\n",iVar4);
      return 0;
    }
    iVar4 = iVar4 + 1;
  }
  rr_loader_debug_log(3,"E #2802\n");
  return 0;
}

