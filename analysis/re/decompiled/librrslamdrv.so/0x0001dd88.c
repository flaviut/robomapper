/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrslamdrv.so
 * SHA256: b48f5f56eb1b2d22abbf727725ea558762337f8f0103229d8da6c1ab6275608a
 * Function VA: 0x0001dd88
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Storage cache loader: index=*flag+11. Existing pointer bypasses file read, returns GridGetBuffer
   result. Otherwise obtains 1024x1024 buffer filled 0x80, copies GridFilenameSlot string and opens
   input mode 8. Calls GridReadDispatch, accepts if stream state &5 ==0. On allocation/open/stream
   failure drops same cache slot with base11 and sets out->valid=0. Header/scale/digest mismatch
   need not set stream state: can return valid=1 with initialized unchanged cells and retain cache.
   No lock around cache lookup/load/drop observed; dmb/ldrex/strex belong to string reference count,
   not cache synchronization. Close result is ignored. ABI explicit out pointer; original C++
   class/layout unknown. */

GridBufferRef * GridGetSavedBuffer(GridBufferRef *out,void *store,int *flag)

{
  bool bVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  uint *puVar8;
  int iVar9;
  int iVar10;
  undefined4 uVar11;
  int local_188;
  void *local_180;
  void *local_168;
  undefined1 auStack_15c [4];
  int local_158;
  int local_154;
  GridBufferRef local_150;
  int local_144 [2];
  int local_13c [3];
  uint auStack_130 [4];
  locale alStack_120 [28];
  __basic_file<char> a_Stack_104 [80];
  int local_b4 [5];
  uint local_a0;
  undefined4 local_44;
  undefined2 local_40;
  undefined4 local_3c;
  undefined4 uStack_38;
  undefined4 local_34;
  undefined4 uStack_30;
  int local_2c;
  
  iVar10 = DAT_0001e158 + 0x1dd9a;
  piVar6 = *(int **)(iVar10 + DAT_0001e15c);
  local_158 = *flag + 0xb;
  local_2c = *piVar6;
  if (*(int *)(*(int *)store + local_158 * 4) != 0) {
    GridCellSet((uchar *)&local_154,0x80);
    GridGetBuffer(&local_150,store,&local_158,(uchar *)&local_154);
    out->cells = local_150.cells;
    out->metadata = local_150.metadata;
    out->valid = local_150.valid;
    out->unknown_09_0b[0] = local_150.unknown_09_0b[0];
    out->unknown_09_0b[1] = local_150.unknown_09_0b[1];
    out->unknown_09_0b[2] = local_150.unknown_09_0b[2];
    goto LAB_0001ddd6;
  }
  GridCellSet((uchar *)&local_154,0x80);
  GridGetBuffer(&local_150,store,&local_158,(uchar *)&local_154);
  if (local_150.valid == '\0') {
    local_154 = 0xb;
    GridDropCacheSlot(store,&local_154,flag);
    out->valid = '\0';
    goto LAB_0001ddd6;
  }
  local_154 = *flag;
  piVar2 = GridFilenameSlot(store,&local_154);
  local_188 = *piVar2;
  local_180 = (void *)(local_188 + -0xc);
  piVar2 = (int *)(local_188 + -4);
  if (*(int *)(local_188 + -4) < 0) {
    local_188 = FUN_0001dcdc(local_180,auStack_15c,0);
    local_180 = (void *)(local_188 + -0xc);
    local_168 = *(void **)(iVar10 + DAT_0001e160);
  }
  else {
    local_168 = *(void **)(iVar10 + DAT_0001e160);
    if (local_180 != local_168) {
      if (*(int *)(iVar10 + DAT_0001e190) == 0) {
        *(int *)(local_188 + -4) = *(int *)(local_188 + -4) + 1;
      }
      else {
        DataMemoryBarrier(0x1b);
        do {
          ExclusiveAccess(piVar2);
          bVar1 = (bool)hasExclusiveAccess(piVar2);
        } while (!bVar1);
        *piVar2 = *piVar2 + 1;
        DataMemoryBarrier(0x1b);
      }
    }
  }
  puVar8 = *(uint **)(iVar10 + DAT_0001e164);
  if (6 < *puVar8) {
    (*(code *)**(undefined4 **)(iVar10 + DAT_0001e168))
              (4,7,0xba,&UNK_0001e0da + DAT_0001e170,DAT_0001e16c + 0x1de78,local_188);
  }
  std::ios_base::ios_base((ios_base *)local_b4);
  iVar3 = *(int *)(iVar10 + DAT_0001e174);
  local_40 = 0;
  local_44 = 0;
  local_b4[0] = iVar3 + 8;
  local_3c = 0;
  uStack_38 = 0;
  local_34 = 0;
  uStack_30 = 0;
  iVar4 = *(int *)(*(int *)(iVar10 + DAT_0001e178) + 4);
  uVar11 = *(undefined4 *)(*(int *)(iVar10 + DAT_0001e178) + 8);
  local_144[0] = iVar4;
  *(undefined4 *)((int)local_144 + *(int *)(iVar4 + -0xc)) = uVar11;
  local_144[1] = 0;
  std::ios::init((streambuf *)(*(int *)(iVar4 + -0xc) + (int)local_144));
  iVar7 = *(int *)(iVar10 + DAT_0001e17c);
  local_144[0] = iVar7 + 0xc;
  local_b4[0] = iVar7 + 0x20;
  std::filebuf::filebuf((filebuf *)local_13c);
  std::ios::init((streambuf *)local_b4);
  iVar5 = std::filebuf::open((filebuf *)local_13c,local_188,8);
  iVar9 = *(int *)(local_144[0] + -0xc) + (int)local_144;
  if (iVar5 == 0) {
    std::ios::clear(iVar9,*(uint *)((int)auStack_130 + *(int *)(local_144[0] + -0xc)) | 4);
  }
  else {
    std::ios::clear(iVar9,0);
  }
  if ((local_a0 & 5) == 0) {
    if (6 < *puVar8) {
      (*(code *)**(undefined4 **)(iVar10 + DAT_0001e168))
                (4,7,0xc3,DAT_0001e198 + 0x1e29e,DAT_0001e194 + 0x1e03c);
    }
    GridReadDispatch(local_144,&local_150);
    if (6 < *puVar8) {
      (*(code *)**(undefined4 **)(iVar10 + DAT_0001e168))
                (4,7,199,DAT_0001e1a0 + 0x1e2ce,DAT_0001e19c + 0x1e06c);
    }
    if ((local_a0 & 5) != 0) goto LAB_0001df62;
    out->cells = local_150.cells;
    out->metadata = local_150.metadata;
    out->valid = local_150.valid;
    out->unknown_09_0b[0] = local_150.unknown_09_0b[0];
    out->unknown_09_0b[1] = local_150.unknown_09_0b[1];
    out->unknown_09_0b[2] = local_150.unknown_09_0b[2];
  }
  else {
    if (3 < *puVar8) {
      (*(code *)**(undefined4 **)(iVar10 + DAT_0001e168))
                (4,4,0xbe,DAT_0001e184 + 0x1e1b2,DAT_0001e180 + 0x1df50,local_188);
    }
LAB_0001df62:
    local_154 = 0xb;
    GridDropCacheSlot(store,&local_154,flag);
    out->valid = '\0';
  }
  local_b4[0] = iVar7 + 0x20;
  local_144[0] = iVar7 + 0xc;
  local_13c[0] = *(int *)(iVar10 + DAT_0001e188) + 8;
  std::filebuf::close();
  std::__basic_file<char>::~__basic_file(a_Stack_104);
  local_13c[0] = *(int *)(iVar10 + DAT_0001e18c) + 8;
  std::locale::~locale(alStack_120);
  local_144[0] = iVar4;
  *(undefined4 *)((int)local_144 + *(int *)(iVar4 + -0xc)) = uVar11;
  local_b4[0] = iVar3 + 8;
  local_144[1] = 0;
  std::ios_base::~ios_base((ios_base *)local_b4);
  if (local_180 != local_168) {
    if (*(int *)(iVar10 + DAT_0001e190) == 0) {
      iVar10 = *(int *)(local_188 + -4);
      *(int *)(local_188 + -4) = iVar10 + -1;
    }
    else {
      DataMemoryBarrier(0x1b);
      piVar2 = (int *)(local_188 + -4);
      do {
        ExclusiveAccess(piVar2);
        iVar10 = *piVar2;
        bVar1 = (bool)hasExclusiveAccess(piVar2);
      } while (!bVar1);
      *piVar2 = iVar10 + -1;
      DataMemoryBarrier(0x1b);
    }
    if (iVar10 < 1) {
      operator_delete(local_180);
    }
  }
LAB_0001ddd6:
  if (local_2c != *piVar6) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return out;
}

