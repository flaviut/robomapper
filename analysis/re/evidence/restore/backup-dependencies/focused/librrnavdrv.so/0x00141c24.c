/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x00141c24
 */

undefined4 FUN_00141c24(int param_1)

{
  int iVar1;
  char *__new;
  char *__old;
  
  __old = (char *)(param_1 + 0x81);
  libconfig::Config::writeFile(*(char **)(param_1 + 0x104));
  _rrlogmP(3,7,1,0x5e,DAT_00141d00 + 0x141c4c,DAT_00141cfc + 0x141c48,DAT_00141cf8 + 0x141c46,__old)
  ;
  __new = (char *)(param_1 + 1);
  iVar1 = rename(__old,__new);
  if (iVar1 != 0) {
    _rrlogmP(3,3,1,0x6d,DAT_00141d0c + 0x141c7a,DAT_00141d08 + 0x141c76,DAT_00141d04 + 0x141c74,
             __old,__new);
    return 0;
  }
  _rrlogmP(3,7,1,0x68,DAT_00141d18 + 0x141ca6,DAT_00141d14 + 0x141ca2,DAT_00141d10 + 0x141ca0,__old,
           __new);
  return 1;
}

