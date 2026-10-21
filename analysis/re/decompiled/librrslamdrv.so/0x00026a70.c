/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrslamdrv.so
 * SHA256: b48f5f56eb1b2d22abbf727725ea558762337f8f0103229d8da6c1ab6275608a
 * Function VA: 0x00026a70
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Returns address of one-word string slot store + 4*(*flag+18), NOT raw char*. No flag validation.
   Constructor binds flag0 mobility_test_map, 1 last_map, 2..11 user_map(flag-2), 12
   /dev/shm/tmp_map. Cache index is separately flag+11; do not conflate string and pointer-table
   indexes. */

void * GridFilenameSlot(void *store,int *flag)

{
  return (void *)((int)store + (*flag + 0x12) * 4);
}

