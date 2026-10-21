/* Decompiled C, NOT recovered source; need not compile.
 * Binary: libuart_api.so.4.0.2
 * SHA256: 914317e600a73255cb6523e987ab3ab99b5168c47026503fcb3fe797f9961529
 * Function VA: 0x00011690
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Surviving symbol preserved. Tail-calls rua_keep_mcu_heartbeat(-1), transmitting command 0xd3 with
   four bytes ff ff ff ff if send succeeds. Name does not prove MCU/kernel behavior or safe
   indefinite map-writer stop. Returns callee result. */

int disable_mcu_heartbeat(void)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00005480. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR_rua_keep_mcu_heartbeat_000352b0)(0xffffffff);
  return iVar1;
}

