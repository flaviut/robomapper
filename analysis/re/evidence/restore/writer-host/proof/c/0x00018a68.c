/* Decompiled C, NOT recovered source; need not compile.
 * Binary: rr_loader
 * SHA256: 020d6d7de7d282ecec3e845e4664113b11df82656701d42de7e901595c5f5125
 * Function VA: 0x00018a68
 */

/* rrloader::RRLoader::dealSignal(int, siginfo_t*) */

void rrloader::RRLoader::dealSignal(int param_1,siginfo_t *param_2)

{
  long lVar1;
  uint uVar2;
  
  if ((siginfo_t *)0xf < param_2) {
    return;
  }
  uVar2 = 1 << ((uint)param_2 & 0xff);
  if ((uVar2 & 0x9d0) == 0) {
    if (((uVar2 & 0x800c) == 0) && (-1 < (int)(uVar2 << 0x1e))) {
      return;
    }
    *(undefined1 *)(param_1 + 0x9c) = 1;
    return;
  }
  lVar1 = syscall(0xe0);
  __printf_chk(1,"rrloader catch signal %d T%ld\n",param_2,lVar1);
  print_trace();
  fflush(stdout);
  signal((int)param_2,(__sighandler_t)0x0);
  raise((int)param_2);
  *(undefined1 *)(param_1 + 0x9c) = 1;
  return;
}

