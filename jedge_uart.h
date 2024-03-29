/*
 * jedge_uart.h
 *
 *  Created on: Jun 19, 2018
 *      Author: Joshua Edgcombe
 */

#ifndef JEDGE_UART_H_
#define JEDGE_UART_H_

#include "msp.h"

void UART_init(EUSCI_A_Type *EUSCI_device);
void UART_send(EUSCI_A_Type *EUSCI_device, char *str);
char UART_recv(EUSCI_A_Type *EUSCI_device);

void UART_test(void);
void UART_learning_activity(void);

#endif /* JEDGE_UART_H_ */
