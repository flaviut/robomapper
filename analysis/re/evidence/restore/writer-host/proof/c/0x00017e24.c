/* Decompiled C, NOT recovered source; need not compile.
 * Binary: rr_loader
 * SHA256: 020d6d7de7d282ecec3e845e4664113b11df82656701d42de7e901595c5f5125
 * Function VA: 0x00017e24
 */

/* rrloader::RREnv::RREnv() */

void __thiscall rrloader::RREnv::RREnv(RREnv *this)

{
  undefined4 uVar1;
  int iVar2;
  allocator aaStack_18 [4];
  int local_14;
  
  local_14 = __stack_chk_guard;
  uVar1 = DAT_00017eb8;
  *this = (RREnv)0x0;
  *(undefined4 *)(this + 4) = 7;
  *(undefined4 *)(this + 8) = uVar1;
  std::string::string((string *)(this + 0xc),"arm",aaStack_18);
  iVar2 = __stack_chk_guard;
  *(undefined4 *)(this + 0x10) = uVar1;
  if (local_14 == iVar2) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(this);
}

