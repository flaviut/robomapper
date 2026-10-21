/* Decompiled C, NOT recovered source; need not compile.
 * Binary: rr_loader
 * SHA256: 020d6d7de7d282ecec3e845e4664113b11df82656701d42de7e901595c5f5125
 * Function VA: 0x00019058
 */

/* rrloader::RRPlugin::final() */

void __thiscall rrloader::RRPlugin::final(RRPlugin *this)

{
  showStatus(this);
  pthread_mutex_lock((pthread_mutex_t *)(this + 0xf0));
  this[0x184] = (RRPlugin)0x1;
  pthread_cond_broadcast((pthread_cond_t *)(this + 0x108));
  pthread_mutex_unlock((pthread_mutex_t *)(this + 0xf0));
  pthread_cond_signal((pthread_cond_t *)(this + 0xc0));
  rrMsgQueue::quit((rrMsgQueue *)this);
  if (*(code **)(*(int *)(this + 0x80) + 0x10) != (code *)0x0) {
    (**(code **)(*(int *)(this + 0x80) + 0x10))(this + 0x9c);
  }
  if (*(pthread_t *)(this + 0x94) != 0) {
    pthread_join(*(pthread_t *)(this + 0x94),(void **)0x0);
  }
  if (*(code **)(*(int *)(this + 0x80) + 0x14) != (code *)0x0) {
    (**(code **)(*(int *)(this + 0x80) + 0x14))(this + 0x9c);
  }
  if (*(int *)(this + 0x90) != 0) {
    *(undefined4 *)(this + 0x90) = 0;
  }
  return;
}

