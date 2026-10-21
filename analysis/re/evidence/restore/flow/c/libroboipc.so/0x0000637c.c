/* Decompiled C, NOT recovered source; need not compile.
 * Binary: libroboipc.so
 * SHA256: a7a693c8edd37aa9367f680d2f742ef81f4b8007c97a7720fc02f35ded57a832
 * Function VA: 0x0000637c
 */

/* pDoSendPacket(Packet_t*, SendOptions_t*) */

undefined4 pDoSendPacket(Packet_t *param_1,SendOptions_t *param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = DAT_000063d8 + 0x6390;
  if (((byte)*param_2 & 1) == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = 0x800;
  }
  uVar1 = pChannelWrite(*(void **)(*(int *)(iVar3 + DAT_000063dc) +
                                  (((*(uint *)param_1 << 8) >> 0x18) * 0x11 +
                                  (*(uint *)param_1 >> 0x18)) * 4),param_1,0x4c,iVar2);
  pLogPrint(0x2b3,DAT_000063e4 + 0x641c,*(uint *)(*(int *)(iVar3 + DAT_000063e0) + 0x220) & 0x10,
            DAT_000063e8 + 0x63be,uVar1);
  return uVar1;
}

