/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x001a6018
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Returns word at manager+0x28; constructor initializes it to -1. Read during flag-1 load
   reconciliation. */

int MapFlowGetStoredFlag(void *manager)

{
  return *(int *)((int)manager + 0x28);
}

