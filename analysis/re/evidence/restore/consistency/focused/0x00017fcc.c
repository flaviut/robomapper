/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x00017fcc
 */

/* PersistInfoLockGuard::~PersistInfoLockGuard() */

PersistInfoLockGuard * __thiscall
PersistInfoLockGuard::~PersistInfoLockGuard(PersistInfoLockGuard *this)

{
  UnlockPersistInfo(*(undefined4 *)this);
  return this;
}

