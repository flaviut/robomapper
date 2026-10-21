/* Decompiled C, NOT recovered source; need not compile.
 * Binary: libuart_api.so.4.0.2
 * SHA256: 914317e600a73255cb6523e987ab3ab99b5168c47026503fcb3fe797f9961529
 * Function VA: 0x00011564
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Command encoding only: int value==0 becomes 60, otherwise preserve all 32 bits;
   sent_cmd_sigle_thread(0xd3,4,&value,1), up to three attempts with 20ms sleeps after failures.
   Returns 0 on nonnegative sender result, negative init/send error otherwise. If UART was not
   already initialized, initializes and closes it locally. Target is little-endian ARM32, so
   four-byte -1 is ff ff ff ff. No periodic heartbeat production is established here; MCU meaning of
   60/120/-1, sender completion semantics, reset safety and active producer remain unresolved. */

int rua_keep_mcu_heartbeat(int value)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  pthread_t pVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  int iVar8;
  int local_28;
  int local_24;
  
  iVar5 = DAT_00011670 + 0x11574;
  piVar6 = *(int **)(iVar5 + DAT_00011674);
  local_24 = *piVar6;
  iVar2 = is_mcu_tty_inited();
  if (iVar2 == 0) {
    piVar7 = *(int **)(iVar5 + DAT_00011678);
    if (*piVar7 < 5) {
      iVar2 = init_uart();
    }
    else {
      uVar3 = rua_ms_now();
      pVar4 = pthread_self();
      __printf_chk(1,DAT_00011680 + 0x115fe,uVar3,pVar4,DAT_0001167c + 0x116f8);
      iVar2 = init_uart();
    }
    if (iVar2 < 0) {
      if (2 < *piVar7) {
        uVar3 = rua_ms_now();
        pVar4 = pthread_self();
        __printf_chk(1,DAT_00011684 + 0x11632,uVar3,pVar4,iVar2);
      }
      goto LAB_000115cc;
    }
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  local_28 = value;
  if (value == 0) {
    local_28 = 0x3c;
  }
  iVar8 = 3;
  do {
    iVar2 = sent_cmd_sigle_thread(0xd3,4,&local_28,1);
    if (-1 < iVar2) {
      iVar2 = 0;
      break;
    }
    usleep(20000);
    iVar8 = iVar8 + -1;
  } while (iVar8 != 0);
  if (bVar1) {
    if (4 < **(int **)(iVar5 + DAT_00011678)) {
      uVar3 = rua_ms_now();
      pVar4 = pthread_self();
      __printf_chk(1,DAT_0001168c + 0x11652,uVar3,pVar4,DAT_00011688 + 0x1174a);
    }
    close_uart();
  }
LAB_000115cc:
  if (local_24 == *piVar6) {
    return iVar2;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

