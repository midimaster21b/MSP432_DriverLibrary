#include <stdint.h>
#include "msp.h"
#include "driverlib.h"
#include "jedge_uart.h"
#include "jedge_spi.h"
#include "jedge_systick.h"
#include "jedge_clocks.h"
#include "jedge_sccb.h"
#include "jedge_ov7670.h"
#include "jedge_sd_card.h"

/**
 * main.c
 */
void main(void)
{
  // stop watchdog timer
  WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

  // UART Test
  /* UART_test(); */

  // SPI Test
  /* SPI_test(); */

  // SysTick Test
  /* systick_test(); */

  init_clocks();

  // SCCB test
  sccb_test();

  // OV7670 test
  /* ov7670_test(); */

  // SD card test
  /* sd_test(); */

  // Enable interrupts on the microcontroller
  MAP_Interrupt_enableMaster();

  while(1) {
  }
}
