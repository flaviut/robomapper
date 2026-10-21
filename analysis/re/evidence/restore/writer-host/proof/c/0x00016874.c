/* Decompiled C, NOT recovered source; need not compile.
 * Binary: rr_loader
 * SHA256: 020d6d7de7d282ecec3e845e4664113b11df82656701d42de7e901595c5f5125
 * Function VA: 0x00016874
 */

/* rrloader::RRTimerManager::final() */

void __thiscall rrloader::RRTimerManager::final(RRTimerManager *this)

{
  if (*(pthread_t *)(this + 4) == 0) {
    return;
  }
  pthread_join(*(pthread_t *)(this + 4),(void **)0x0);
  *(undefined4 *)(this + 4) = 0;
  return;
}

