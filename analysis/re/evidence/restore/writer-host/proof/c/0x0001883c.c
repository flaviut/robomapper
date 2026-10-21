/* Decompiled C, NOT recovered source; need not compile.
 * Binary: rr_loader
 * SHA256: 020d6d7de7d282ecec3e845e4664113b11df82656701d42de7e901595c5f5125
 * Function VA: 0x0001883c
 */

/* rrloader::RRLoader::initSigaction() */

void rrloader::RRLoader::initSigaction(void)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  sigaltstack local_ac;
  _union_1051 local_a0;
  sigset_t sStack_9c;
  undefined4 local_1c;
  int local_14;
  
  local_14 = __stack_chk_guard;
  local_ac.ss_sp = malloc(0x2000);
  if (local_ac.ss_sp == (void *)0x0) {
    perror("malloc");
                    /* WARNING: Subroutine does not return */
    exit(-1);
  }
  local_ac.ss_flags = 0;
  local_ac.ss_size = 0x2000;
  iVar1 = sigaltstack(&local_ac,(sigaltstack *)0x0);
  if (iVar1 == -1) {
    perror("sigaltstack");
                    /* WARNING: Subroutine does not return */
    exit(-1);
  }
  piVar3 = &DAT_0002f1c8;
  iVar1 = DAT_0002f1c8;
  do {
    if (iVar1 == 0) {
      uVar2 = 1;
LAB_000188bc:
      if (local_14 == __stack_chk_guard) {
        return;
      }
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(uVar2);
    }
    memset(&local_a0,0,0x8c);
    local_a0 = (_union_1051)((_union_1051 *)(piVar3 + 3))->sa_handler;
    if (local_a0.sa_handler == (__sighandler_t)0x0) {
      local_a0 = (_union_1051)0x1;
    }
    else {
      local_1c = 0x8000004;
    }
    sigemptyset(&sStack_9c);
    iVar1 = sigaction(*piVar3,(sigaction *)&local_a0,(sigaction *)0x0);
    if (iVar1 == -1) {
      uVar2 = 0;
      goto LAB_000188bc;
    }
    piVar3 = piVar3 + 4;
    iVar1 = *piVar3;
  } while( true );
}

