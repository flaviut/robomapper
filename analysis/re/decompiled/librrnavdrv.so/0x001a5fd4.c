/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x001a5fd4
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Returns unsigned byte at manager+0x22. Constructor 0x1a6374 clears it; MapFlowSetStoredFlag sets
   it. This is an in-process initialized/stored-flag predicate, not a catalog lookup or a proven
   persisted-file flag. */

uint MapFlowHasStoredFlag(void *manager)

{
  return (uint)*(byte *)((int)manager + 0x22);
}

