/* Decompiled C, NOT recovered source; need not compile.
 * Binary: rr_loader
 * SHA256: 020d6d7de7d282ecec3e845e4664113b11df82656701d42de7e901595c5f5125
 * Function VA: 0x00018ad4
 */

void FUN_00018ad4(siginfo_t *param_1)

{
  int iVar1;
  
  iVar1 = rrloader::RRLoader::GetInstance();
  rrloader::RRLoader::dealSignal(iVar1,param_1);
  return;
}

