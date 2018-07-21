/*
 * jedge_sccb.c
 *
 *  Created on: July 6, 2018
 *      Author: Joshua Edgcombe
 */

#include <stdint.h>
#include "msp.h"
#include "driverlib.h"
#include "jedge_sccb.h"
#include "jedge_timer_a.h"

Timer_A_Type *sccb_timer;

void sccb_test(void) {
  Timer_A_Type *test_timer = TIMER_A0;

  sccb_init(test_timer);
  sccb_start_timer();

  /* sccb_write_register(test_dev, SCCB_TEST_ADDRESS, 0x08, 0x38); */
}

void sccb_init(Timer_A_Type *timer_a) {
  sccb_init_pins();
  sccb_init_timer(timer_a);
}

void sccb_init_pins(void) {
  // Configure pins (GPIO, Output, High)
  SCCB_SDA_PORT->SEL0 &= ~SCCB_SDA_MASK;
  SCCB_SDA_PORT->SEL1 &= ~SCCB_SDA_MASK;
  SCCB_SDA_PORT->DIR  |= SCCB_SDA_MASK;
  SCCB_SDA_PORT->OUT  |= SCCB_SDA_MASK;

  SCCB_SCL_PORT->SEL0 &= ~SCCB_SCL_MASK;
  SCCB_SCL_PORT->SEL1 &= ~SCCB_SCL_MASK;
  SCCB_SCL_PORT->DIR |= SCCB_SCL_MASK;
  SCCB_SCL_PORT->OUT |= SCCB_SCL_MASK;
}

void sccb_init_timer(Timer_A_Type *timer_a) {
  sccb_timer = timer_a;

  // Reset the timer setup
  sccb_timer->CTL |= TIMER_A_CTL_CLR;

  // Set timer a clock
  sccb_timer->CTL |= TIMER_A_CTL_SSEL__SMCLK;

  // Set clock divider
  sccb_timer->CTL |= TIMER_A_CTL_ID__1;

  // Sets the peak value
  sccb_timer->CCR[0] = 30;

  // Enable interrupts (if desired)
  sccb_timer->CTL |= TIMER_A_CTL_IE;

  MAP_Timer_A_registerInterrupt(TIMER_A0_BASE, TIMER_A_CCR0_INTERRUPT, sccb_timer_handler);

  MAP_Timer_A_enableInterrupt(TIMER_A0_BASE);
  MAP_Interrupt_enableInterrupt(INT_TA0_0);
}

void sccb_init_timer_driverlib(Timer_A_Type *timer_a) {

  MAP_Timer_A_registerInterrupt(TIMER_A0_BASE, TIMER_A_CCR0_INTERRUPT, sccb_timer_handler);

  MAP_Timer_A_enableInterrupt(TIMER_A0_BASE);
  MAP_Interrupt_enableInterrupt(INT_TA0_0);
}


static void sccb_start_timer(void) {
  // Start the timer
  sccb_timer->CTL |= TIMER_A_CTL_MC__UP;
}

void sccb_timer_handler(void) {
  MAP_Timer_A_clearInterruptFlag(TIMER_A0_BASE);
  SCCB_SCL_PORT->OUT ^= SCCB_SCL_MASK;
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
