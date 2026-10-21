/* Decompiled C, NOT recovered source; need not compile.
 * Binary: rr_loader
 * SHA256: 020d6d7de7d282ecec3e845e4664113b11df82656701d42de7e901595c5f5125
 * Function VA: 0x0001d364
 */

void rr_unpacking(int param_1,size_t param_2)

{
  int iVar1;
  byte bVar2;
  void *pvVar3;
  int iVar4;
  byte bVar5;
  byte *pbVar6;
  int iVar7;
  undefined1 *puVar8;
  byte *pbVar9;
  byte bStack_35;
  byte local_34 [16];
  int local_24;
  
  puVar8 = key1;
  pbVar9 = &key2;
  pbVar6 = &bStack_35;
  bVar5 = 0x36;
  bVar2 = 0x4d;
  local_24 = __stack_chk_guard;
  while( true ) {
    pbVar6 = pbVar6 + 1;
    *pbVar6 = bVar5 ^ bVar2;
    if (pbVar6 == local_34 + 0xf) break;
    puVar8 = puVar8 + 1;
    bVar2 = *puVar8;
    pbVar9 = pbVar9 + 1;
    bVar5 = *pbVar9;
  }
  iVar7 = param_2 - 4;
  CCMInit(local_34);
  pvVar3 = malloc(param_2);
  iVar4 = CCMDecrypt(DAT_0001d410 + -8,8,param_1,iVar7,param_1 + iVar7,4,DAT_0001d410,0xd,0,pvVar3);
  iVar1 = __stack_chk_guard;
  if (iVar4 == 0) {
    *(undefined1 *)((int)pvVar3 + iVar7) = 0;
    if (local_24 == iVar1) {
      return;
    }
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(pvVar3);
  }
  puts("exit -4");
                    /* WARNING: Subroutine does not return */
  exit(-4);
}

