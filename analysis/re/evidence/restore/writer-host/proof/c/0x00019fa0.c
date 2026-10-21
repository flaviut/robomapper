/* Decompiled C, NOT recovered source; need not compile.
 * Binary: rr_loader
 * SHA256: 020d6d7de7d282ecec3e845e4664113b11df82656701d42de7e901595c5f5125
 * Function VA: 0x00019fa0
 */

/* rrloader::RRConf::getNode(char const*) const */

undefined4 rrloader::RRConf::getNode(char *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if ((*(int *)param_1 != 0) && (iVar1 = cJSON_IsObject(*(int *)param_1), iVar1 != 0)) {
    uVar2 = cJSON_GetObjectItemCaseSensitive(*(undefined4 *)param_1);
    return uVar2;
  }
  return 0;
}

