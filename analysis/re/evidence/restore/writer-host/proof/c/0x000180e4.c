/* Decompiled C, NOT recovered source; need not compile.
 * Binary: rr_loader
 * SHA256: 020d6d7de7d282ecec3e845e4664113b11df82656701d42de7e901595c5f5125
 * Function VA: 0x000180e4
 */

/* rrloader::RREnv::init() */

undefined4 __thiscall rrloader::RREnv::init(RREnv *this)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *__s;
  
  iVar1 = RRLoader::GetInstance();
  iVar2 = RRConf::getNode((char *)(iVar1 + 0x14));
  if ((iVar2 == 0) || (iVar3 = cJSON_IsNumber(), iVar3 == 0)) {
    rr_loader_debug_log(3,"E #2819\n");
    return 0;
  }
  *(undefined4 *)(this + 4) = *(undefined4 *)(iVar2 + 0x14);
  iVar1 = RRConf::getNode((char *)(iVar1 + 0x14));
  if ((iVar1 != 0) && (iVar2 = cJSON_IsString(), iVar2 != 0)) {
    __s = *(char **)(iVar1 + 0x10);
    strlen(__s);
    std::string::assign((char *)(this + 0x10),(uint)__s);
    std::string::append((char *)(this + 0x10),0x1d8e4);
    return 1;
  }
  rr_loader_debug_log(3,"E #2820\n");
  return 0;
}

