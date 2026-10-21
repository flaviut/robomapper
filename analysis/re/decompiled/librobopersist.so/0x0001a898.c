/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librobopersist.so
 * SHA256: 8a1b4fb47407a3e95c96e240e1326e4dbad46f1729d0ad534aa659ac106b542c
 * Function VA: 0x0001a898
 */

/* Returns supplied root pointer. Reinitializes if forced or magic!=0x20210415 or format_version!=2.
   One 0x1a0-byte task at root+8; root mutex at +0x1b0 and task mutex at +0x190 use
   type=1/pshared=1/robust=1. State 6 remains UNKNOWN, not assigned a semantic name. View types
   describe observed storage offsets, not recovered C++ declarations. */

PersistBufferRootView * InitBufferedMapInfoRoot(PersistBufferRootView *root,bool force_init)

{
  int *piVar1;
  undefined8 uVar2;
  pthread_mutexattr_t pStack_18;
  int local_14;
  
  piVar1 = *(int **)(DAT_0001a970 + 0x1a8a0 + DAT_0001a974);
  local_14 = *piVar1;
  if (root == (PersistBufferRootView *)0x0) {
    _rrlogm(0x15,3,0xc1,DAT_0001a98c + 0x1a966,DAT_0001a984 + 0x1a986,DAT_0001a988 + 0x1a95a,0);
  }
  else if (((force_init) || (root->magic != 0x20210415)) || (root->format_version != 2)) {
    pthread_mutexattr_init(&pStack_18);
    pthread_mutexattr_settype(&pStack_18,1);
    pthread_mutexattr_setpshared(&pStack_18,1);
    pthread_mutexattr_setrobust(&pStack_18,1);
    pthread_mutex_init((pthread_mutex_t *)root->root_mutex_storage,&pStack_18);
    (root->task).task_index = 0;
    (root->task).owner_pid = 0;
    (root->task).state = PersistTaskIdle;
    (root->task).destination_mask = 0;
    pthread_mutex_init((pthread_mutex_t *)(root->task).task_mutex_storage,&pStack_18);
    uVar2 = get_cur_time_ms();
    *(undefined8 *)root->unknown_time_ms_storage = uVar2;
    root->magic = 0x20210415;
    root->format_version = 2;
  }
  else {
    _rrlogm(0x15,7,0xc6,DAT_0001a980 + 0x1a946,DAT_0001a978 + 0x1a966,DAT_0001a97c + 0x1a93a,root);
  }
  if (local_14 == *piVar1) {
    return root;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

