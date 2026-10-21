/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrslamdrv.so
 * SHA256: b48f5f56eb1b2d22abbf727725ea558762337f8f0103229d8da6c1ab6275608a
 * Function VA: 0x00026b60
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Observed initialization only; no original C++ class claimed. Allocates 25 pointer slots (100
   bytes at store+0..8) and 25 36-byte metadata slots (900 bytes at store+12..20); clears both.
   Constructs 25 string slots at store+24 onward. First 12 are
   mobility_test_vmap,last_vmap,user_vmap0..9. Grid strings at store+72: flag0
   /opt/rockrobo/cleaner/misc/mobility_test_map; flag1 /mnt/data/rockrobo/last_map; flags2..11
   /mnt/data/rockrobo/user_map0..9; flag12 /dev/shm/tmp_map. Absolute strings verified against
   literal pool 0x26e1c..0x26e7c and .rodata 0x3f594..0x3f8a8. Constructor alone imposes no flag
   range check. */

void GridStoreInit(void *store)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  GridRect *rect;
  GridRect *rect_00;
  undefined4 *puVar4;
  int *piVar5;
  int *piVar6;
  undefined1 auStack_20 [4];
  int local_1c;
  
  piVar6 = *(int **)(DAT_00026e14 + 0x26b68 + DAT_00026e18);
  *(undefined4 *)((int)store + 4) = 0;
  *(undefined4 *)((int)store + 8) = 0;
  local_1c = *piVar6;
  *(undefined4 *)store = 0;
  puVar2 = operator_new(100);
  puVar4 = puVar2 + 0x19;
  *(undefined4 **)store = puVar2;
  *(undefined4 **)((int)store + 8) = puVar4;
  do {
    puVar3 = puVar2 + 1;
    *puVar2 = 0;
    puVar2 = puVar3;
  } while (puVar4 != puVar3);
  *(undefined4 **)((int)store + 4) = puVar4;
  *(undefined4 *)((int)store + 0xc) = 0;
  *(undefined4 *)((int)store + 0x10) = 0;
  *(undefined4 *)((int)store + 0x14) = 0;
  rect = operator_new(900);
  piVar5 = &rect[0x38].top;
  *(GridRect **)((int)store + 0xc) = rect;
  *(GridRect **)((int)store + 0x10) = rect;
  *(int **)((int)store + 0x14) = piVar5;
  do {
    memset(rect,0,0x24);
    GridRectClear(rect);
    rect_00 = rect + 1;
    rect = (GridRect *)&rect[2].top;
    GridRectClear(rect_00);
    iVar1 = DAT_00026e1c;
  } while ((GridRect *)piVar5 != rect);
  *(int **)((int)store + 0x10) = piVar5;
  FUN_0000fb2c((int)store + 0x18,iVar1 + 0x26bde,auStack_20);
  FUN_0000fb2c((int)store + 0x1c,DAT_00026e20 + 0x26bec,auStack_20);
  FUN_0000fb2c((int)store + 0x20,DAT_00026e24 + 0x26bfa,auStack_20);
  FUN_0000fb2c((int)store + 0x24,DAT_00026e28 + 0x26c08,auStack_20);
  FUN_0000fb2c((int)store + 0x28,DAT_00026e2c + 0x26c16,auStack_20);
  FUN_0000fb2c((int)store + 0x2c,DAT_00026e30 + 0x26c24,auStack_20);
  FUN_0000fb2c((int)store + 0x30,DAT_00026e34 + 0x26c32,auStack_20);
  FUN_0000fb2c((int)store + 0x34,DAT_00026e38 + 0x26c40,auStack_20);
  FUN_0000fb2c((int)store + 0x38,DAT_00026e3c + 0x26c4e,auStack_20);
  FUN_0000fb2c((int)store + 0x3c,DAT_00026e40 + 0x26c5c,auStack_20);
  FUN_0000fb2c((int)store + 0x40,DAT_00026e44 + 0x26c6a,auStack_20);
  FUN_0000fb2c((int)store + 0x44,DAT_00026e48 + 0x26c78,auStack_20);
  FUN_0000fb2c((int)store + 0x48,DAT_00026e4c + 0x26c86,auStack_20);
  FUN_0000fb2c((int)store + 0x4c,DAT_00026e50 + 0x26c96,auStack_20);
  FUN_0000fb2c((int)store + 0x50,DAT_00026e54 + 0x26ca4,auStack_20);
  FUN_0000fb2c((int)store + 0x54,DAT_00026e58 + 0x26cb2,auStack_20);
  FUN_0000fb2c((int)store + 0x58,DAT_00026e5c + 0x26cc0,auStack_20);
  FUN_0000fb2c((int)store + 0x5c,DAT_00026e60 + 0x26cce,auStack_20);
  FUN_0000fb2c((int)store + 0x60,DAT_00026e64 + 0x26cdc,auStack_20);
  FUN_0000fb2c((int)store + 100,DAT_00026e68 + 0x26cea,auStack_20);
  FUN_0000fb2c((int)store + 0x68,DAT_00026e6c + 0x26cf8,auStack_20);
  FUN_0000fb2c((int)store + 0x6c,DAT_00026e70 + 0x26d06,auStack_20);
  FUN_0000fb2c((int)store + 0x70,DAT_00026e74 + 0x26d14,auStack_20);
  FUN_0000fb2c((int)store + 0x74,DAT_00026e78 + 0x26d22,auStack_20);
  FUN_0000fb2c((int)store + 0x78,DAT_00026e7c + 0x26d30,auStack_20);
  if (local_1c == *piVar6) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(store);
}

