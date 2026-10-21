/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0000e034
 */

/* Catalog path helper: appends /rockrobo/SharedMultiMapInfo to GetUserDataPath output; sets
   output[127]=0. Caller supplies 128-byte storage; no general arbitrary-path selection. */

void GetMultiMapFilePath(char *path_out)

{
  char cVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  size_t sVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 *puVar10;
  
  GetUserDataPath(path_out);
  iVar3 = DAT_0000e084;
  sVar5 = strlen(path_out);
  iVar4 = DAT_0000e088;
  puVar10 = (undefined4 *)(DAT_0000e088 + 0xe04c);
  uVar6 = *(undefined4 *)(iVar3 + 0xe04e);
  *(undefined4 *)(path_out + sVar5) = *(undefined4 *)(iVar3 + 0xe04a);
  *(undefined4 *)(path_out + sVar5 + 4) = uVar6;
  uVar6 = *puVar10;
  uVar7 = *(undefined4 *)(iVar4 + 0xe050);
  uVar8 = *(undefined4 *)(iVar4 + 0xe054);
  uVar9 = *(undefined4 *)(iVar4 + 0xe058);
  *(undefined2 *)(path_out + sVar5 + 8) = *(undefined2 *)(iVar3 + 0xe052);
  uVar2 = *(undefined2 *)(iVar4 + 0xe05c);
  cVar1 = *(char *)(iVar4 + 0xe05e);
  *(undefined4 *)(path_out + sVar5 + 10) = uVar6;
  *(undefined4 *)(path_out + sVar5 + 0xe) = uVar7;
  *(undefined4 *)(path_out + sVar5 + 0x12) = uVar8;
  *(undefined4 *)(path_out + sVar5 + 0x16) = uVar9;
  *(undefined2 *)(path_out + sVar5 + 0x1a) = uVar2;
  path_out[sVar5 + 0x1c] = cVar1;
  path_out[0x7f] = '\0';
  return;
}

