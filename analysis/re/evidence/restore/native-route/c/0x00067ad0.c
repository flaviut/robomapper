/* Decompiled C, NOT recovered source; need not compile.
 * Binary: librrnavdrv.so
 * SHA256: 603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475
 * Function VA: 0x00067ad0
 */

void FUN_00067ad0(int param_1,int *param_2,undefined4 param_3)

{
  bool bVar1;
  int extraout_r1;
  int extraout_r1_00;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  pthread_mutex_t *__mutex;
  int iVar9;
  undefined4 local_34;
  int local_30;
  int local_2c;
  
  iVar7 = DAT_00067cc0 + 0x67ae4;
  iVar6 = *param_2;
  piVar3 = *(int **)(iVar7 + DAT_00067cc4);
  uVar8 = *(undefined4 *)(param_1 + 8);
  local_2c = *piVar3;
  __aeabi_uidivmod(iVar6,uVar8);
  piVar2 = *(int **)(*(int *)(param_1 + 4) + extraout_r1 * 4);
  if (piVar2 != (int *)0x0) {
    iVar9 = ((int *)*piVar2)[4];
    piVar5 = (int *)*piVar2;
    do {
      if ((iVar6 == iVar9) && (iVar6 == piVar5[1])) {
        iVar9 = *piVar2;
        if (iVar9 == 0) break;
        piVar2 = *(int **)(iVar9 + 0xc);
        __mutex = *(pthread_mutex_t **)(iVar9 + 8);
        if (piVar2 == (int *)0x0) {
          if (__mutex == (pthread_mutex_t *)0x0) break;
          iVar7 = *(int *)(iVar7 + DAT_00067cc8);
          if (iVar7 != 0) goto LAB_00067b8c;
        }
        else {
          iVar7 = *(int *)(iVar7 + DAT_00067cc8);
          if (iVar7 != 0) {
            piVar5 = piVar2 + 1;
            DataMemoryBarrier(0x1b);
            do {
              ExclusiveAccess(piVar5);
              bVar1 = (bool)hasExclusiveAccess(piVar5);
            } while (!bVar1);
            *piVar5 = *piVar5 + 1;
            DataMemoryBarrier(0x1b);
            if (__mutex == (pthread_mutex_t *)0x0) {
LAB_00067be0:
              piVar5 = piVar2 + 1;
              DataMemoryBarrier(0x1b);
              do {
                ExclusiveAccess(piVar5);
                iVar6 = *piVar5;
                bVar1 = (bool)hasExclusiveAccess(piVar5);
              } while (!bVar1);
              *piVar5 = iVar6 + -1;
              DataMemoryBarrier(0x1b);
              if (iVar6 != 1) break;
              (**(code **)(*piVar2 + 8))(piVar2);
              piVar5 = piVar2 + 2;
              DataMemoryBarrier(0x1b);
              do {
                ExclusiveAccess(piVar5);
                iVar6 = *piVar5;
                bVar1 = (bool)hasExclusiveAccess(piVar5);
              } while (!bVar1);
              *piVar5 = iVar6 + -1;
              DataMemoryBarrier(0x1b);
            }
            else {
              iVar6 = *param_2;
LAB_00067b8c:
              iVar9 = pthread_mutex_lock(__mutex);
              if (iVar9 != 0) {
                    /* WARNING: Subroutine does not return */
                std::__throw_system_error(iVar9);
              }
              piVar5 = *(int **)((int)__mutex + 0x20);
              if (piVar5 == (int *)0x0) {
LAB_00067bd0:
                pthread_mutex_unlock(__mutex);
                if (piVar2 == (int *)0x0) break;
                goto LAB_00067be0;
              }
LAB_00067b9e:
              iVar9 = piVar5[4];
              while( true ) {
                local_34 = param_3;
                local_30 = iVar6;
                if (iVar9 == 0) {
                    /* WARNING: Subroutine does not return */
                  std::__throw_bad_function_call();
                }
                (*(code *)piVar5[5])(piVar5 + 2,&local_30,&local_34);
                piVar5 = (int *)*piVar5;
                if (piVar5 == (int *)0x0) break;
                iVar9 = piVar5[4];
              }
              if (iVar7 != 0) goto LAB_00067bd0;
LAB_00067c4c:
              if (piVar2 == (int *)0x0) break;
              iVar9 = piVar2[1];
LAB_00067c58:
              piVar2[1] = iVar9 + -1;
              if (iVar9 != 1) break;
              (**(code **)(*piVar2 + 8))(piVar2);
              iVar6 = piVar2[2];
              piVar2[2] = iVar6 + -1;
            }
            if (iVar6 == 1) {
              (**(code **)(*piVar2 + 0xc))(piVar2);
            }
            break;
          }
          iVar9 = piVar2[1] + 1;
          piVar2[1] = iVar9;
          if (__mutex == (pthread_mutex_t *)0x0) goto LAB_00067c58;
        }
        piVar5 = *(int **)((int)__mutex + 0x20);
        if (piVar5 == (int *)0x0) goto LAB_00067c4c;
        goto LAB_00067b9e;
      }
      piVar4 = (int *)*piVar5;
      if (piVar4 == (int *)0x0) break;
      iVar9 = piVar4[4];
      __aeabi_uidivmod(iVar9,uVar8);
      piVar2 = piVar5;
      piVar5 = piVar4;
    } while (extraout_r1 == extraout_r1_00);
  }
  if (local_2c == *piVar3) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

