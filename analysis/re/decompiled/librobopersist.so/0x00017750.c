/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x00017750
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Independent zlib-stream loader, not concatenated-stream inflation. Opaque protobuf region message
   and prefix-offset vector. For indices first_part, first_part+stride,...:
   uncompress(destination+offset[index], &capacity, value[index], value_size). capacity is
   rawDataSize for a single value, rawDataPartSize[index] otherwise. Signed index/count/stride
   comparisons; no task cancellation check. Zlib errors log and emit event, but return void and do
   not aggregate failure. Successful output length is logged, not compared to declared capacity.
   Workers are joined by ForcePersistLoad before callback stage 1/unlock. */

void PersistInflateParts(void *region_message,void *destination,void *offsets_vector,int first_part,
                        int stride)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 local_30;
  int local_2c;
  
  iVar8 = *(int *)((int)region_message + 0xc);
  piVar5 = *(int **)(DAT_00017878 + 0x17762 + DAT_0001787c);
  local_2c = *piVar5;
  if (first_part < iVar8) {
    iVar7 = first_part << 2;
    iVar2 = DAT_00017880 + 0x1779e;
    iVar6 = DAT_00017884 + 0x177a8;
    iVar1 = DAT_00017888 + 0x1779a;
    iVar3 = DAT_0001788c + 0x1779e;
    iVar9 = iVar7;
    while( true ) {
      if (iVar8 == 1) {
        local_30 = *(undefined4 *)((int)region_message + 0x28);
      }
      else {
        local_30 = *(undefined4 *)(*(int *)((int)region_message + 0x20) + iVar7 + 4);
      }
      iVar4 = **(int **)(*(int *)((int)region_message + 0x14) + iVar7 + 4);
      iVar4 = uncompress(*(int *)(*(int *)offsets_vector + iVar9) + (int)destination,&local_30,iVar4
                         ,*(undefined4 *)(iVar4 + -0xc));
      if (iVar4 == 0) {
        _rrlogm(0x15,7,0x200,iVar1,iVar2,iVar3,0,local_30,
                *(undefined4 *)(**(int **)(iVar7 + *(int *)((int)region_message + 0x14) + 4) + -0xc)
                ,first_part,iVar8);
      }
      else {
        _rrlogm(0x15,4,0x1fa,DAT_00017894 + 0x177d4,iVar6,DAT_00017890 + 0x177be,iVar4,local_30,
                *(undefined4 *)(**(int **)(iVar7 + *(int *)((int)region_message + 0x14) + 4) + -0xc)
                ,first_part,iVar8);
        rr_event_int(1,6,iVar4);
      }
      if (iVar8 <= first_part + stride) break;
      first_part = first_part + stride;
      iVar9 = iVar9 + stride * 4;
      iVar7 = first_part * 4;
    }
  }
  if (local_2c == *piVar5) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

