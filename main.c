#include <stdint.h>
#include "msp.h"
#include "jedge_uart.h"
#include "jedge_spi.h"

/**
 * main.c
 */
void main(void)
{
  // stop watchdog timer
  WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

  // UART Test
  EUSCI_A_Type *EUSCI_UART_device = EUSCI_A0;
  UART_init(EUSCI_UART_device);
  UART_send(EUSCI_UART_device, "Hello, UART!");

  // SPI Test
  // Create SPI configuration struct
  EUSCI_SPI_config SPI_config = {
    .clock_phase = 1,
    .clock_polarity = 0,
    .msb_first = 1,
    .seven_bit_data = 0,
    .master_mode = 1,
    .eusci_mode_bit_10 = 1,
    .eusci_mode_bit_9 = 0,
    .sync_mode = 1,
    .clk_sel_bit_7 = 1,
    .clk_sel_bit_6 = 0,
    .ste_mode = 1
  };

  EUSCI_B_SPI_Type *EUSCI_SPI_device = EUSCI_B0_SPI;
  SPI_init(EUSCI_SPI_device, &SPI_config);
  SPI_send(EUSCI_SPI_device, "Hello, SPI!");

  while(1);
}
