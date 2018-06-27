/*
 * jedge_uart.c
 *
 *  Created on: Jun 19, 2018
 *      Author: midimaster21b
 */

#include "jedge_uart.h"

void UART_init(EUSCI_A_Type *EUSCI_device) {
  // Put the peripheral in a reset state
  EUSCI_device->CTLW0 |= UCSWRST;

  // Disable oversampling mode
  EUSCI_device->MCTLW &= ~UCOS16;

  // Set clock prescaler (3 MHz / 9600 Baud rate)
  EUSCI_device->BRW = 312;

  // Disable parity bit
  EUSCI_device->CTLW0 &= ~UCPEN;

  // Set to 8-bit data
  EUSCI_device->CTLW0 &= ~UC7BIT;

  // One stop bit
  EUSCI_device->CTLW0 &= ~UCSPB;

  // Select SMClk
  EUSCI_device->CTLW0 |= UCSSEL__SMCLK;

  // Select correct pin muxing
  P1SEL0 |= 1 << 2 | 1 << 3;
  P1SEL1 &= ~(1 << 2 | 1 << 3);

  // Put the peripheral in a reset state
  EUSCI_device->CTLW0 &= ~UCSWRST;
}

void UART_send(EUSCI_A_Type *EUSCI_device, char *c) {
  // If transmit buffer is not empty, wait for it to be empty
  while(!(EUSCI_device->IFG & UCTXIFG));

  // Put character in buffer to be transferred
  EUSCI_device->TXBUF = c;

  // Wait until the transmit has been moved to the shift register before returning
  while(!(EUSCI_device->IFG & UCTXCPTIFG));
}


