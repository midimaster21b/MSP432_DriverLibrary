#include "msp.h"
#include "jedge_uart.h"

/**
 * main.c
 */
void main(void)
{
  // stop watchdog timer
  WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

  EUSCI_A_Type *EUSCI_device = EUSCI_A0;

  UART_init(EUSCI_device);

  UART_send(EUSCI_device, 'H');

  while(1);
}
