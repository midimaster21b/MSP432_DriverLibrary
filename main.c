#include <stdint.h>
#include "msp.h"
#include "jedge_uart.h"
#include "jedge_spi.h"
#include "jedge_systick.h"

/**
 * main.c
 */
void main(void)
{
  // stop watchdog timer
  WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

  // UART Test
  UART_test();

  // SPI Test
  SPI_test();

  // SysTick Test
  systick_test();

  while(1) {
  }
}
