/*
 * jedge_sccb.c
 *
 *  Created on: July 6, 2018
 *      Author: Joshua Edgcombe
 */

#include <stdint.h>
#include "msp.h"
#include "jedge_sccb.h"

void sccb_test(void) {
  EUSCI_B_Type *test_dev = SCCB_EUSCI_DEVICE;

  sccb_init(test_dev);

  sccb_write_register(test_dev, SCCB_TEST_ADDRESS, 0x08, 0x38);
}

void sccb_init(EUSCI_B_Type *EUSCI_device) {
  // Put the peripheral in a reset state
  EUSCI_device->CTLW0 |= EUSCI_B_CTLW0_SWRST;

  // Initialize all eUSCI_B registers
  // Set clock bits (SMCLK)
  EUSCI_device->CTLW0 &= ~EUSCI_B_CTLW0_SSEL_MASK;
  EUSCI_device->CTLW0 |= EUSCI_B_CTLW0_SSEL__SMCLK;

  // Enable synchronous mode (USYNC = 1)
  EUSCI_device->CTLW0 |= EUSCI_B_CTLW0_SYNC;

  // Set mode to I2C (UCMODEx=11b)
  /* EUSCI_device->CTLW0 &= ~EUSCI_B_CTLW0_MODE_MASK; */
  EUSCI_device->CTLW0 |= EUSCI_B_CTLW0_MODE_3;

  // Set to master mode (UCMST = 1)
  EUSCI_device->CTLW0 |= EUSCI_B_CTLW0_MST;

  // Master acknowledges last byte in master receiver mode
  EUSCI_device->CTLW1 |= EUSCI_B_CTLW1_STPNACK;

  // Enable SW ack using UCTXACK
  EUSCI_device->CTLW1 |= EUSCI_B_CTLW1_SWACK;

  // Set divider to achieve
  EUSCI_device->BRW = 60;

  // Configure ports
  // TODO: Configure ports programmatically
  SCCB_SDA_PORT->SEL0 |= SCCB_SDA_MASK;
  SCCB_SDA_PORT->SEL1 &= ~SCCB_SDA_MASK;

  SCCB_SCL_PORT->SEL0 |= SCCB_SCL_MASK;
  SCCB_SCL_PORT->SEL1 &= ~SCCB_SCL_MASK;

  // Clear UCSWRST (Enable peripheral)
  EUSCI_device->CTLW0 &= ~EUSCI_B_CTLW0_SWRST;

  // Enable interrupts (if desired)
}

void sccb_write_register(EUSCI_B_Type *EUSCI_device, uint8_t slave_address, uint8_t reg_address, uint8_t data) {
  // Wait while bus is busy
  /* while(EUSCI_device->STATW & EUSCI_B_STATW_BBUSY); */

  // Set slave address (UCBxI2CSA = slave_address)
  EUSCI_device->I2CSA = slave_address;

  // Set transmit mode (UCTR = 1)
  EUSCI_device->CTLW0 |= EUSCI_B_CTLW0_TR;

  // Start a transmission
  EUSCI_device->CTLW0 |= EUSCI_B_CTLW0_TXSTT;

  // Wait for Tx buffer to clear (TXIFG = 1)
  while((EUSCI_device->IFG & EUSCI_B_IFG_TXIFG0) == 0);

  // Set register address to be written (UCBxTXBUF = reg_address)
  EUSCI_device->TXBUF = reg_address;

  // Wait for Tx buffer to clear (TXIFG = 1)
  while((EUSCI_device->IFG & EUSCI_B_IFG_TXIFG0) == 0);

  // Set data to be sent
  EUSCI_device->TXBUF = data;

  // Set stop bit (UCTXSTP = 1)
  EUSCI_device->CTLW0 |= EUSCI_B_CTLW0_TXSTP;
}

uint8_t sccb_read_register(EUSCI_B_Type *EUSCI_device, uint8_t slave_address, uint8_t reg_address) {
  uint8_t retval;

  /**********************************************************
   * Write register address to be read from. (2 phase write)
   **********************************************************/
  // Set slave address (UCBxI2CSA = slave_address)
  /* EUSCI_device->I2CSA = slave_address; */
  EUSCI_device->I2CSA = slave_address;

  // Set transmit mode (UCTR = 1)
  EUSCI_device->CTLW0 |= EUSCI_B_CTLW0_TR;

  // Start a transmission
  EUSCI_device->CTLW0 |= EUSCI_B_CTLW0_TXSTT;

  // Wait for Tx buffer to clear (TXIFG = 1)
  while((EUSCI_device->IFG & EUSCI_B_IFG_TXIFG0) == 0);

  EUSCI_device->CTLW0 |= EUSCI_B_CTLW0_TXACK;

  // Wait for nack flag to be set
  while((EUSCI_device->IFG & EUSCI_B_IFG_NACKIFG) == 0);

  // Set register address to be written (UCBxTXBUF = reg_address)
  EUSCI_device->TXBUF = reg_address;

  // Force second transmission start (Necessary due to SCCB "not caring" about ninth bit)
  EUSCI_device->CTLW0 |= EUSCI_B_CTLW0_TXSTT;

  // Wait for Tx buffer to clear (TXIFG = 1)
  while((EUSCI_device->IFG & EUSCI_B_IFG_TXIFG0) == 0);

  // Set stop bit (UCTXSTP = 1)
  EUSCI_device->CTLW0 |= EUSCI_B_CTLW0_TXSTP;

  /**********************************************************
   * Read register value. (2 phase read)
   **********************************************************/
  // Wait while bus is busy
  while(EUSCI_device->STATW & EUSCI_B_STATW_BBUSY);

  // Set slave address (UCBxI2CSA = slave_address)
  EUSCI_device->I2CSA = slave_address;

  // Set receiver mode (UCTR = 0)
  EUSCI_device->CTLW0 &= ~EUSCI_B_CTLW0_TR;

  // Start a transmission
  EUSCI_device->CTLW0 |= EUSCI_B_CTLW0_TXSTT;

  // Wait for Rx buffer to fill (RXIFG = 1)
  while((EUSCI_device->IFG & EUSCI_B_IFG_RXIFG0) == 0);

  // Get read byte from buffer
  retval = EUSCI_device->RXBUF;

  // Set stop bit (UCTXSTP = 1)
  EUSCI_device->CTLW0 |= EUSCI_B_CTLW0_TXSTP;

  return retval;
}
