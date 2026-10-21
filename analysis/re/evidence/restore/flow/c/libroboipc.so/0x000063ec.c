/* Decompiled C, NOT recovered source; need not compile.
 * Binary: libroboipc.so
 * SHA256: a7a693c8edd37aa9367f680d2f742ef81f4b8007c97a7720fc02f35ded57a832
 * Function VA: 0x000063ec
 */

undefined4 SendPacket(Packet_t *param_1,byte *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar4 = DAT_0000648c + 0x63f6;
  if (param_1 == (Packet_t *)0x0) {
    __printf_chk(1,DAT_000064a4 + 0x6466,DAT_000064a0 + 0x64d4,0x2d9);
    __printf_chk(1,DAT_000064ac + 0x6476,DAT_000064a8 + 0x6474);
    _IO_putc(10,(_IO_FILE *)**(undefined4 **)(iVar4 + DAT_000064b0));
  }
  else if (*(int *)(*(int *)(iVar4 + DAT_00006490) +
                   (((*(uint *)param_1 << 8) >> 0x18) * 0x11 + (*(uint *)param_1 >> 0x18)) * 4) != 0
          ) {
    GetNextSequenceNumber(param_1);
    iVar2 = DAT_00006498;
    iVar1 = DAT_00006494;
    *param_2 = *param_2 | 1;
    pLogPrint(0x2ea,iVar2 + 0x649e,*(uint *)(*(int *)(iVar4 + iVar1) + 0x220) & 0x10,
              DAT_0000649c + 0x6444,*(undefined4 *)param_1,*(undefined4 *)(param_1 + 4),1);
    uVar3 = (*(code *)PTR_pDoSendPacket_0001c144)(param_1,param_2);
    return uVar3;
  }
  return 0xffffffff;
}

