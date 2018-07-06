/*
 * jedge_sccb.h
 *
 *  Created on: July 6, 2018
 *      Author: Joshua Edgcombe
 */

#include <stdint.h>
#include "msp.h"

#ifndef JEDGE_SCCB_H_
#define JEDGE_SCCB_H_

#define SCCB_EUSCI_DEVICE EUSCI_B1_BASE
#define SCCB_TEST_ADDRESS 22

#define SCCB_SDA_PORT P6
#define SCCB_SDA_PIN  4
#define SCCB_SDA_MASK (1 << SCCB_SDA_PIN)

#define SCCB_SCL_PORT P6
#define SCCB_SCL_PIN  5
#define SCCB_SCL_MASK (1 << SCCB_SCL_PIN)

#define SCCB_REG_WRITE 0
#define SCCB_REG_READ  1

// TODO: implement interrupt driven messaging
typedef struct SCCB_Message {
  uint8_t message_type;
  uint8_t register_address;
  uint8_t data;
  struct SCCB_Message *next;
} SCCB_Message;

void sccb_test(void);
void sccb_init(EUSCI_B_Type *EUSCI_device);
void sccb_write_register(EUSCI_B_Type *EUSCI_device, uint8_t slave_address, uint8_t reg_address, uint8_t data);
uint8_t sccb_read_register(EUSCI_B_Type *EUSCI_device, uint8_t slave_address);

#endif /* JEDGE_SCCB_H_ */
