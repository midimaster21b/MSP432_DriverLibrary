/*
 * jedge_uart.h
 *
 *  Created on: Jun 19, 2018
 *      Author: midimaster21b
 */

#ifndef JEDGE_UART_H_
#define JEDGE_UART_H_

#include "msp.h"

void UART_init(EUSCI_A_Type *EUSCI_device);
void UART_send(EUSCI_A_Type *EUSCI_device, char c);

#endif /* JEDGE_UART_H_ */
