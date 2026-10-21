/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0001a990
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Returns cached/shared root or null. Opens named semaphore with initial count 1 and
   /BufferedMapInfo shm, resizes/maps 0x1c8 bytes read-write MAP_SHARED, then initializes root if
   needed. Semaphore is capacity gating, not successful-file-write acknowledgment. */

PersistBufferRootView * GetBufferedMapInfoRoot(void)

{
  int iVar1;
  int iVar2;
  PersistBufferRootView *root;
  sem_t *psVar3;
  int *piVar4;
  undefined4 uVar5;
  PersistBufferRootView *pPVar6;
  int *piVar7;
  bool force_init;
  char *pcVar8;
  int iVar9;
  int iVar10;
  stat sStack_80;
  int local_24;
  
  iVar2 = DAT_0001ab54;
  piVar7 = *(int **)(DAT_0001ab4c + 0x1a998 + DAT_0001ab50);
  local_24 = *piVar7;
  pPVar6 = *(PersistBufferRootView **)(DAT_0001ab54 + 0x1a9a4);
  if (pPVar6 == (PersistBufferRootView *)0x0) {
    if (*(int *)(DAT_0001ab54 + 0x1a9a8) == 0) {
      psVar3 = sem_open((char *)(DAT_0001ab6c + 0x1aa72),0x40,0x180,1);
      *(sem_t **)(iVar2 + 0x1a9a8) = psVar3;
      if (psVar3 == (sem_t *)0x0) {
        piVar4 = __errno_location();
        iVar1 = DAT_0001ab70 + 0x1aa84;
        pcVar8 = strerror(*piVar4);
        _rrlogm(0x15,3,0xed,DAT_0001ab78 + 0x1aa96,DAT_0001ab74 + 0x1aada,iVar1,pcVar8);
        *(undefined4 *)(iVar2 + 0x1a9a8) = 0;
        goto LAB_0001a9aa;
      }
    }
    pcVar8 = (char *)(DAT_0001ab58 + 0x1a9d2);
    iVar10 = DAT_0001ab5c + 0x1a9d4;
    iVar1 = shm_open(pcVar8,0x42,0x180);
    iVar9 = DAT_0001ab60 + 0x1aa2c;
    iVar2 = iVar1;
    _rrlogm(0x15,7,0xf3,iVar10,iVar9,DAT_0001ab64 + 0x1a9f6,pcVar8,iVar1);
    if (iVar1 < 0) {
      piVar4 = __errno_location();
      iVar1 = DAT_0001ab8c + 0x1ab00;
      pcVar8 = strerror(*piVar4);
      _rrlogm(0x15,3,0xf6,iVar10,iVar9,iVar1,pcVar8,iVar2);
    }
    else {
      memset(&sStack_80,0,0x58);
      iVar2 = __fxstat(3,iVar1,&sStack_80);
      if (iVar2 == 0) {
        if (sStack_80.st_size == 0x1c8) {
          force_init = false;
        }
        else {
          iVar2 = ftruncate(iVar1,0x1c8);
          if (iVar2 != 0) {
            piVar4 = __errno_location();
            pcVar8 = strerror(*piVar4);
            _rrlogm(0x15,3,0x106,iVar10,iVar9,DAT_0001ab90 + 0x1ab2c,0x1c8,pcVar8);
            close(iVar1);
            goto LAB_0001a9aa;
          }
          force_init = true;
        }
        root = mmap((void *)0x0,0x1c8,3,1,iVar1,0);
        if (root[-1].root_mutex_storage + 0x17 < (uchar *)0xfffffffe) {
          DataMemoryBarrier(0x1b);
          pPVar6 = InitBufferedMapInfoRoot(root,force_init);
          *(PersistBufferRootView **)(DAT_0001ab68 + 0x1aa5c) = pPVar6;
          goto LAB_0001a9aa;
        }
        piVar4 = __errno_location();
        iVar2 = DAT_0001ab80 + 0x1aadc;
        pcVar8 = strerror(*piVar4);
        uVar5 = 0x10e;
        iVar9 = DAT_0001ab84 + 0x1ab34;
        iVar10 = DAT_0001ab88 + 0x1aaf0;
      }
      else {
        piVar4 = __errno_location();
        pcVar8 = strerror(*piVar4);
        uVar5 = 0xfc;
        iVar2 = DAT_0001ab7c + 0x1aabe;
      }
      _rrlogm(0x15,3,uVar5,iVar10,iVar9,iVar2,pcVar8);
      close(iVar1);
    }
  }
LAB_0001a9aa:
  if (local_24 == *piVar7) {
    return pPVar6;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

