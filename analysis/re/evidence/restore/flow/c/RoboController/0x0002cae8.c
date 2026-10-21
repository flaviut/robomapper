/* Decompiled C, NOT recovered source; need not compile.
 * Binary: RoboController
 * SHA256: bf1d43313dd8beaa0c802f9ae4c666138b3bb518f69b4909a746285f3f3947cf
 * Function VA: 0x0002cae8
 */

void FUN_0002cae8(int param_1)

{
  int iVar1;
  int in_stack_00000000;
  int in_stack_00000004;
  
  pthread_mutex_lock((pthread_mutex_t *)(param_1 + 0x36c));
  iVar1 = *(int *)(param_1 + 900);
  do {
    if (*(int *)(param_1 + 0x388) == iVar1) {
LAB_00015bec:
      (*(code *)PTR_pthread_mutex_unlock_0006a448)((pthread_mutex_t *)(param_1 + 0x36c));
      return;
    }
    if ((*(int *)(iVar1 + 8) != 0 || *(int *)(iVar1 + 0xc) != 0) &&
       (*(int *)(iVar1 + 0xc) == in_stack_00000004 && *(int *)(iVar1 + 8) == in_stack_00000000)) {
      FUN_00034d98(param_1 + 900);
      goto LAB_00015bec;
    }
    iVar1 = iVar1 + 0x18;
  } while( true );
}

