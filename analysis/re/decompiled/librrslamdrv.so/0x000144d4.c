/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrslamdrv.so
 * SHA256: b48f5f56eb1b2d22abbf727725ea558762337f8f0103229d8da6c1ab6275608a
 * Function VA: 0x000144d4
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Opens caller-selected string filename in mode8, invokes GridReadDispatch, returns bool captured
   from stream state &5 before closing; close result ignored. Header/scale/MD5 mismatch may leave
   stream good, so return !=0 is not proof of format acceptance. Does not select a native flag. No
   original std::string type inferred. */

int GridLoadFile(void *filename_slot,GridBufferRef *target)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint *puVar9;
  int iVar10;
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
  
  iVar6 = DAT_000146f0 + 0x144e4;
  piVar3 = *(int **)(iVar6 + DAT_000146f4);
  local_2c = *piVar3;
  puVar9 = *(uint **)(iVar6 + DAT_000146f8);
  if (5 < *puVar9) {
    (*(code *)**(undefined4 **)(iVar6 + DAT_000146fc))
              (4,6,0x2a,(int)&DAT_000146f8 + DAT_00014704,DAT_00014700 + 0x1450c,
               *(undefined4 *)filename_slot);
  }
  std::ios_base::ios_base((ios_base *)local_b4);
  iVar1 = *(int *)(iVar6 + DAT_00014708);
  local_40 = 0;
  local_44 = 0;
  local_b4[0] = iVar1 + 8;
  local_3c = 0;
  uStack_38 = 0;
  local_34 = 0;
  uStack_30 = 0;
  iVar7 = *(int *)(*(int *)(iVar6 + DAT_0001470c) + 4);
  uVar4 = *(undefined4 *)(*(int *)(iVar6 + DAT_0001470c) + 8);
  local_144[0] = iVar7;
  *(undefined4 *)((int)local_144 + *(int *)(iVar7 + -0xc)) = uVar4;
  local_144[1] = 0;
  std::ios::init((streambuf *)(*(int *)(iVar7 + -0xc) + (int)local_144));
  iVar10 = *(int *)(iVar6 + DAT_00014710);
  local_144[0] = iVar10 + 0xc;
  local_b4[0] = iVar10 + 0x20;
  std::filebuf::filebuf((filebuf *)local_13c);
  std::ios::init((streambuf *)local_b4);
  iVar2 = std::filebuf::open((filebuf *)local_13c,*(undefined4 *)filename_slot,8);
  iVar5 = *(int *)(local_144[0] + -0xc) + (int)local_144;
  if (iVar2 == 0) {
    std::ios::clear(iVar5,*(uint *)((int)auStack_130 + *(int *)(local_144[0] + -0xc)) | 4);
  }
  else {
    std::ios::clear(iVar5,0);
  }
  if ((local_a0 & 5) == 0) {
    if (6 < *puVar9) {
      (*(code *)**(undefined4 **)(iVar6 + DAT_000146fc))
                (4,7,0x32,DAT_00014728 + 0x14844,DAT_00014724 + 0x1465e);
    }
    GridReadDispatch(local_144,target);
    if (6 < *puVar9) {
      (*(code *)**(undefined4 **)(iVar6 + DAT_000146fc))
                (4,7,0x36,DAT_00014730 + 0x14874,DAT_0001472c + 0x1468e);
    }
    uVar8 = (uint)((local_a0 & 5) == 0);
  }
  else {
    if (3 < *puVar9) {
      (*(code *)**(undefined4 **)(iVar6 + DAT_000146fc))
                (4,4,0x2e,DAT_00014718 + 0x147c2,DAT_00014714 + 0x145d6,*(undefined4 *)filename_slot
                );
    }
    uVar8 = 0;
  }
  local_144[0] = iVar10 + 0xc;
  local_b4[0] = iVar10 + 0x20;
  local_13c[0] = *(int *)(iVar6 + DAT_0001471c) + 8;
  std::filebuf::close();
  std::__basic_file<char>::~__basic_file(a_Stack_104);
  local_13c[0] = *(int *)(iVar6 + DAT_00014720) + 8;
  std::locale::~locale(alStack_120);
  local_144[0] = iVar7;
  *(undefined4 *)((int)local_144 + *(int *)(iVar7 + -0xc)) = uVar4;
  local_144[1] = 0;
  local_b4[0] = iVar1 + 8;
  std::ios_base::~ios_base((ios_base *)local_b4);
  if (local_2c != *piVar3) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar8;
}

