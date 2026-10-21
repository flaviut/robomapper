/* Decompiled C, NOT recovered source; need not compile.
 * Binary: rr_loader
 * SHA256: 020d6d7de7d282ecec3e845e4664113b11df82656701d42de7e901595c5f5125
 * Function VA: 0x00019da8
 */

/* WARNING: Removing unreachable block (ram,0x00019f2e) */
/* rrloader::RRConf::init() */

void __thiscall rrloader::RRConf::init(RRConf *this)

{
  bool bVar1;
  int iVar2;
  void *__ptr;
  int iVar3;
  FILE *__stream;
  size_t __size;
  size_t sVar4;
  char *pcVar5;
  int *piVar6;
  char *pcVar7;
  bool bVar8;
  char *local_20;
  
  iVar2 = __stack_chk_guard;
  RRLoader::GetInstance();
  RREnv::getConfigFilePath();
  if (*(int *)(local_20 + -0xc) == 0) {
    __ptr = (void *)rr_unpacking(json_config,json_config_len);
    if (__ptr != (void *)0x0) {
      rr_loader_debug_log(7,"D #2868\n");
LAB_00019dfc:
      iVar3 = cJSON_Parse(__ptr);
      *(int *)this = iVar3;
      if (iVar3 == 0) {
        pcVar5 = (char *)cJSON_GetErrorPtr();
        pcVar7 = "unknown parse error";
        if (pcVar5 != (char *)0x0) {
          pcVar7 = pcVar5;
        }
        rr_loader_debug_log(3,"F #2874`%s\n",pcVar7);
      }
      free(__ptr);
      bVar8 = *(int *)this != 0;
      goto LAB_00019e76;
    }
    rr_loader_debug_log(3,"E #2867\n");
  }
  else {
    __stream = fopen(local_20,"rb");
    if (__stream == (FILE *)0x0) {
      rr_loader_debug_log(3,"E #2869`%s\n",local_20);
    }
    else {
      fseek(__stream,0,2);
      __size = ftell(__stream);
      if ((int)__size < 1) {
        rr_loader_debug_log(3,"E #2870`%s\n",local_20);
      }
      else {
        rewind(__stream);
        __ptr = malloc(__size);
        if (__ptr == (void *)0x0) {
          rr_loader_debug_log(3,"E #2871`%d\n",__size);
        }
        else {
          sVar4 = fread(__ptr,1,__size,__stream);
          if (__size == sVar4) {
            rr_loader_debug_log(7,"D #2873`%s\n",local_20);
            goto LAB_00019dfc;
          }
          rr_loader_debug_log(3,"E #2872`%zu\n",sVar4);
        }
      }
      fclose(__stream);
    }
  }
  bVar8 = false;
LAB_00019e76:
  if ((allocator *)(local_20 + -0xc) != (allocator *)std::string::_Rep::_S_empty_rep_storage) {
    piVar6 = (int *)(local_20 + -4);
    DataMemoryBarrier(0x1b);
    do {
      ExclusiveAccess(piVar6);
      iVar3 = *piVar6;
      bVar1 = (bool)hasExclusiveAccess(piVar6);
    } while (!bVar1);
    *piVar6 = iVar3 + -1;
    DataMemoryBarrier(0x1b);
    if (iVar3 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_20 + -0xc));
    }
  }
  if (iVar2 == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(bVar8);
}

