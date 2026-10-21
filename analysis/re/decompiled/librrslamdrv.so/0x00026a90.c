/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrslamdrv.so
 * SHA256: b48f5f56eb1b2d22abbf727725ea558762337f8f0103229d8da6c1ab6275608a
 * Function VA: 0x00026a90
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Index=*base_index+*flag; 0x26ae6-0x26af8 clears pointer-table slot and delete[]s old cells if
   non-NULL; metadata at store[3]+36*index is zeroed (36 bytes), then two empty 16-byte rectangles
   installed. Does not delete file or rebuild string. Grid file-load callers pass base=11. No bounds
   test, mutex, or wait observed here; caller serialization is not established by this helper. */

void GridDropCacheSlot(void *store,int *base_index,int *flag)

{
  void *pvVar1;
  int iVar2;
  int iVar3;
  int *__s;
  int *piVar4;
  int iVar5;
  GridRect local_3c;
  GridRect local_2c;
  int local_1c;
  
  iVar2 = DAT_00026b48 + 0x26a9e;
  piVar4 = *(int **)(iVar2 + DAT_00026b4c);
  iVar5 = *base_index;
  iVar3 = *flag;
  local_1c = *piVar4;
  if (6 < **(uint **)(iVar2 + DAT_00026b50)) {
    (*(code *)**(undefined4 **)(iVar2 + DAT_00026b54))
              (4,7,0x85,DAT_00026b5c + 0x26adc,DAT_00026b58 + 0x26aca,iVar5,iVar3);
    iVar3 = *flag;
    iVar5 = *base_index;
  }
  iVar3 = iVar3 + iVar5;
  pvVar1 = *(void **)(*(int *)store + iVar3 * 4);
  *(undefined4 *)(*(int *)store + iVar3 * 4) = 0;
  if (pvVar1 != (void *)0x0) {
    operator_delete__(pvVar1);
  }
  __s = (int *)(iVar3 * 0x24 + *(int *)((int)store + 0xc));
  GridRectClear(&local_3c);
  GridRectClear(&local_2c);
  memset(__s,0,0x24);
  iVar2 = *piVar4;
  *__s = local_3c.left;
  __s[1] = local_3c.top;
  __s[2] = local_3c.width;
  __s[3] = local_3c.height;
  __s[4] = local_2c.left;
  __s[5] = local_2c.top;
  __s[6] = local_2c.width;
  __s[7] = local_2c.height;
  if (local_1c == iVar2) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

