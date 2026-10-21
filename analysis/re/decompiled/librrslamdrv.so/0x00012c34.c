/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrslamdrv.so
 * SHA256: b48f5f56eb1b2d22abbf727725ea558762337f8f0103229d8da6c1ab6275608a
 * Function VA: 0x00012c34
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Saves manager slot index11 (runtime grid) to caller-supplied one-word string slot. Opens output
   mode0x10 and calls GridWriteV2. 0x12dd2-0x12de0 captures success from stream state &5 BEFORE
   std::filebuf::close; 0x12dbc returns captured bool in r0. Close return ignored. No temporary
   rename/fsync in this function, unlike separate persistence writer. Does not select a native flag
   or invalidate saved caches; caller is boundary 0x92e0, not recovered wholesale. */

int GridSaveRuntime(void *unknown_context,void *filename_slot)

{
  void *store;
  int iVar1;
  int *piVar2;
  uint *puVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  uchar auStack_154 [4];
  int local_150;
  GridBufferRef GStack_14c;
  int local_140;
  int local_13c [4];
  uint auStack_12c [3];
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
  
  iVar7 = DAT_00012e28 + 0x12c44;
  piVar2 = *(int **)(iVar7 + DAT_00012e2c);
  local_2c = *piVar2;
  puVar3 = *(uint **)(iVar7 + DAT_00012e30);
  if (6 < *puVar3) {
    unknown_context =
         (void *)(*(code *)**(undefined4 **)(iVar7 + DAT_00012e34))
                           (4,7,0x588,DAT_00012e3c + 0x12dce,DAT_00012e38 + 0x12c6a,
                            *(undefined4 *)filename_slot);
  }
  store = (void *)FUN_00026e80(unknown_context);
  GridCellSet(auStack_154,0x80);
  local_150 = 0xb;
  GridGetBuffer(&GStack_14c,store,&local_150,auStack_154);
  std::ios_base::ios_base((ios_base *)local_b4);
  iVar1 = *(int *)(iVar7 + DAT_00012e40);
  local_40 = 0;
  local_44 = 0;
  local_b4[0] = iVar1 + 8;
  local_3c = 0;
  uStack_38 = 0;
  local_34 = 0;
  uStack_30 = 0;
  iVar8 = *(int *)(*(int *)(iVar7 + DAT_00012e44) + 4);
  uVar4 = *(undefined4 *)(*(int *)(iVar7 + DAT_00012e44) + 8);
  iVar5 = *(int *)(iVar8 + -0xc);
  local_140 = iVar8;
  *(undefined4 *)((int)&local_140 + iVar5) = uVar4;
  std::ios::init((streambuf *)((int)&local_140 + iVar5));
  iVar10 = *(int *)(iVar7 + DAT_00012e48);
  local_140 = iVar10 + 0xc;
  local_b4[0] = iVar10 + 0x20;
  std::filebuf::filebuf((filebuf *)local_13c);
  std::ios::init((streambuf *)local_b4);
  iVar5 = std::filebuf::open((filebuf *)local_13c,*(undefined4 *)filename_slot,0x10);
  iVar6 = *(int *)(local_140 + -0xc) + (int)&local_140;
  if (iVar5 == 0) {
    std::ios::clear(iVar6,*(uint *)((int)auStack_12c + *(int *)(local_140 + -0xc)) | 4);
  }
  else {
    std::ios::clear(iVar6,0);
  }
  if ((local_a0 & 5) == 0) {
    GridWriteV2(&local_140,&GStack_14c);
    uVar9 = (uint)((local_a0 & 5) == 0);
  }
  else {
    if (3 < *puVar3) {
      (*(code *)**(undefined4 **)(iVar7 + DAT_00012e34))
                (4,4,0x58e,DAT_00012e50 + 0x12ebc,DAT_00012e4c + 0x12d5a,
                 *(undefined4 *)filename_slot);
    }
    uVar9 = 0;
  }
  local_140 = iVar10 + 0xc;
  local_b4[0] = iVar10 + 0x20;
  local_13c[0] = *(int *)(iVar7 + DAT_00012e54) + 8;
  std::filebuf::close();
  std::__basic_file<char>::~__basic_file(a_Stack_104);
  local_13c[0] = *(int *)(iVar7 + DAT_00012e58) + 8;
  std::locale::~locale(alStack_120);
  local_140 = iVar8;
  *(undefined4 *)((int)&local_140 + *(int *)(iVar8 + -0xc)) = uVar4;
  local_b4[0] = iVar1 + 8;
  std::ios_base::~ios_base((ios_base *)local_b4);
  if (local_2c != *piVar2) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar9;
}

