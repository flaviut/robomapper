/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrslamdrv.so
 * SHA256: b48f5f56eb1b2d22abbf727725ea558762337f8f0103229d8da6c1ab6275608a
 * Function VA: 0x0001b5c4
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Gets/creates pointer-table slot indexed directly by *index, NOT a native flag. Existing cells
   return valid=1 immediately. Missing slot: 1024x1024 allocation (0x100000 bytes), centered bounds
   via 0x21dc0, fill every cell from *fill, metadata stride36. Allocation failure sets only
   out->valid=0; other result fields are not established. No lock in this routine. ABI-level
   explicit result pointer, not invented original C++ return signature. */

GridBufferRef * GridGetBuffer(GridBufferRef *out,void *store,int *index,uchar *fill)

{
  uint uVar1;
  void *pvVar2;
  int iVar3;
  uchar *puVar4;
  uchar *puVar5;
  int *piVar6;
  int iVar7;
  int *piVar8;
  GridRect GStack_4c;
  GridRect local_3c;
  int local_2c;
  
  iVar7 = DAT_0001b6f8 + 0x1b5d6;
  iVar3 = *index;
  piVar6 = *(int **)(iVar7 + DAT_0001b6fc);
  puVar4 = *(uchar **)(*(int *)store + iVar3 * 4);
  local_2c = *piVar6;
  if (puVar4 == (uchar *)0x0) {
    local_3c.left = 0x400;
    local_3c.top = 0x400;
    GridRectSet(&GStack_4c,0,0,(GridSize *)&local_3c);
    puVar4 = (uchar *)FUN_00026a88(store,0x100000);
    if (puVar4 == (uchar *)0x0) {
      if (2 < **(uint **)(iVar7 + DAT_0001b700)) {
        (*(code *)**(undefined4 **)(iVar7 + DAT_0001b704))
                  (4,3,0xe8,DAT_0001b710 + 0x1b75e,DAT_0001b714 + 0x1b6e4);
      }
      out->valid = '\0';
    }
    else {
      if (6 < **(uint **)(iVar7 + DAT_0001b700)) {
        (*(code *)**(undefined4 **)(iVar7 + DAT_0001b704))
                  (4,7,0xec,DAT_0001b70c + 0x1b6cc,DAT_0001b708 + 0x1b64e,puVar4);
      }
      GridCenteredRect(&local_3c,&GStack_4c);
      iVar3 = *(int *)((int)store + 0xc);
      piVar8 = (int *)(*index * 0x24 + iVar3);
      *piVar8 = local_3c.left;
      piVar8[1] = local_3c.top;
      piVar8[2] = local_3c.width;
      piVar8[3] = local_3c.height;
      uVar1 = GridRectCellCount((GridRect *)(*index * 0x24 + iVar3));
      for (puVar5 = puVar4; puVar4 + uVar1 != puVar5; puVar5 = puVar5 + 1) {
        *puVar5 = *fill;
      }
      iVar3 = *index;
      pvVar2 = *(void **)(*(int *)store + iVar3 * 4);
      *(uchar **)(*(int *)store + iVar3 * 4) = puVar4;
      if (pvVar2 != (void *)0x0) {
        operator_delete__(pvVar2);
        iVar3 = *index;
      }
      iVar7 = *(int *)((int)store + 0xc);
      out->cells = puVar4;
      out->valid = '\x01';
      out->metadata = (GridCacheMeta *)(iVar3 * 0x24 + iVar7);
    }
  }
  else {
    iVar7 = *(int *)((int)store + 0xc);
    out->cells = puVar4;
    out->valid = '\x01';
    out->metadata = (GridCacheMeta *)(iVar3 * 0x24 + iVar7);
  }
  if (local_2c != *piVar6) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return out;
}

