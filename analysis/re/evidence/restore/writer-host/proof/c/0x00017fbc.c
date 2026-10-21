/* Decompiled C, NOT recovered source; need not compile.
 * Binary: rr_loader
 * SHA256: 020d6d7de7d282ecec3e845e4664113b11df82656701d42de7e901595c5f5125
 * Function VA: 0x00017fbc
 */

/* rrloader::RREnv::parseArg(int, char**) */

undefined4 __thiscall rrloader::RREnv::parseArg(RREnv *this,int param_1,char **param_2)

{
  int iVar1;
  char *__s1;
  int iVar2;
  
  if (param_1 < 2) {
    return 1;
  }
  iVar2 = 1;
  do {
    __s1 = param_2[iVar2];
    iVar1 = strcmp(__s1,"-d");
    if (iVar1 == 0) {
      *this = (RREnv)0x1;
    }
    else {
      iVar1 = strcmp(__s1,"-s");
      if (iVar1 == 0) {
        rrlog_factory_mode = 1;
      }
      else {
        iVar1 = strcmp(__s1,"-c");
        if (iVar1 == 0) {
          if (param_1 <= iVar2 + 1) {
            rr_loader_debug_log(3,"F #2817\n");
            return 0;
          }
          __s1 = param_2[iVar2 + 1];
          iVar2 = iVar2 + 1;
        }
        else {
          iVar1 = strcmp(__s1,"-h");
          if ((iVar1 == 0) || (iVar1 = strcmp(__s1,"--help"), iVar1 == 0)) {
            puts(
                "Copyright (c) 2016 Roborock. All rights reserved.\nUsage: rr_loader [OPTION...] [FILE]...\noptions:\n-d set daemon\n-s set rrlog factory mode\n-c [FILE] set configFile\n-h print this"
                );
                    /* WARNING: Subroutine does not return */
            exit(0);
          }
          if ((*__s1 == '-') || (*(int *)(*(int *)(this + 8) + -0xc) != 0)) {
            rr_loader_debug_log(3,"F #2818`%s\n",__s1);
            puts(
                "Copyright (c) 2016 Roborock. All rights reserved.\nUsage: rr_loader [OPTION...] [FILE]...\noptions:\n-d set daemon\n-s set rrlog factory mode\n-c [FILE] set configFile\n-h print this"
                );
            return 0;
          }
        }
        strlen(__s1);
        std::string::assign((char *)(this + 8),(uint)__s1);
      }
    }
    iVar2 = iVar2 + 1;
    if (param_1 <= iVar2) {
      return 1;
    }
  } while( true );
}

