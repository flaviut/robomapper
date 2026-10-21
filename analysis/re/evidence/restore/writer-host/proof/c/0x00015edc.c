/* Decompiled C, NOT recovered source; need not compile.
 * Binary: rr_loader
 * SHA256: 020d6d7de7d282ecec3e845e4664113b11df82656701d42de7e901595c5f5125
 * Function VA: 0x00015edc
 */

undefined4 main(int param_1,char **param_2)

{
  int iVar1;
  RREnv *this;
  
  iVar1 = rrloader::initTime();
  if (iVar1 == 0) {
    return 0xffffffff;
  }
  this = (RREnv *)rrloader::RRLoader::GetInstance();
  iVar1 = rrloader::RREnv::parseArg(this,param_1,param_2);
  if (iVar1 != 0) {
    rr_loader_debug_log(6,"I #2807\n");
    iVar1 = rrloader::RRLoader::init((RRLoader *)this);
    if (iVar1 != 0) {
      rr_loader_debug_log(6,"I #2809\n");
      rrloader::RRLoader::final((RRLoader *)this);
      rr_loader_debug_log(6,"I #2810\n");
      return 0;
    }
    rr_loader_debug_log(3,"F #2808\n");
    return 0xffffffff;
  }
  rr_loader_debug_log(3,"F #2806\n");
  return 0xffffffff;
}

