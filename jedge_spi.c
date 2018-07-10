/*
 * jedge_spi.c
 *
 *  Created on: Jun 27, 2018
 *      Author: Joshua Edgcombe
 */

#include <stdint.h>
#include "msp.h"
#include "jedge_spi.h"

// TODO: Add support for eUSCI_A
void SPI_init(EUSCI_SPI_TYPE *EUSCI_device, EUSCI_SPI_config *config) {
  // Put the peripheral in a reset state
  EUSCI_device->CTLW0 |= UCSWRST;

  // Fill the CTRLW0 register
  EUSCI_device->CTLW0 = (config->clock_phase << UCCKPH_OFS | \
			 config->clock_polarity << UCCKPL_OFS | \
			 config->msb_first << UCMSB_OFS | \
			 config->seven_bit_data << UC7BIT_OFS | \
			 config->master_mode << UCMST_OFS | \
			 (config->eusci_mode_bit_10 << 1 | config->eusci_mode_bit_9) <<  UCMODE_OFS | \
			 config->sync_mode << UCSYNC_OFS | \
			 (config->clk_sel_bit_7 << 1 | config->clk_sel_bit_6) << UCSSEL_OFS| \
			 config->ste_mode << UCSTEM_OFS) | UCSWRST;

  // Set the baud rate of the SPI device to whichever clock was used
  // TODO: Supply baud rate and determine clock divider programmatically
  EUSCI_device->BRW = config->prescaler;

  // Port & Pin mode muxing
  if(EUSCI_device == EUSCI_B0_SPI) {
    SPI_B0_PORT->SEL0 |= SPI_B0_PIN_MASK;
    SPI_B0_PORT->SEL1 &= ~SPI_B0_PIN_MASK;
  }
  else if(EUSCI_device == EUSCI_B1_SPI) {
    SPI_B1_PORT->SEL0 |= SPI_B1_PIN_MASK;
    SPI_B1_PORT->SEL1 &= ~SPI_B1_PIN_MASK;
  }
  else if(EUSCI_device == EUSCI_B2_SPI) {
    SPI_B2_PORT->SEL0 |= SPI_B2_PIN_MASK;
    SPI_B2_PORT->SEL1 &= ~SPI_B2_PIN_MASK;
  }

  // Enable the peripheral
  EUSCI_device->CTLW0 &= ~UCSWRST;
}

void SPI_send(EUSCI_SPI_TYPE *EUSCI_device, char *data) {
  unsigned address_offset = 0;

  // Iterate through supplied data
  /* while(address_offset < data_length) { */
  while(*(data+address_offset) != '\0') {
    // If transmit buffer is not empty, wait for it to be empty
    while(!(EUSCI_device->IFG & UCTXIFG));

    // Put character in buffer to be transferred
    EUSCI_device->TXBUF = *(data+address_offset);

    // Increment the address offset
    address_offset = address_offset + 1;
  }
}

void SPI_send_data(EUSCI_SPI_TYPE *EUSCI_device, uint8_t *data, uint16_t data_length) {
  unsigned address_offset = 0;

  // Iterate through supplied data
  while(address_offset < data_length) {
    // If transmit buffer is not empty, wait for it to be empty
    while(!(EUSCI_device->IFG & UCTXIFG));

    // Put character in buffer to be transferred
    EUSCI_device->TXBUF = *(data+address_offset);

    // Increment the address offset
    address_offset = address_offset + 1;
  }
}

void SPI_send_byte(EUSCI_SPI_TYPE *EUSCI_device, uint8_t data) {
  // If transmit buffer is not empty, wait for it to be empty
  while(!(EUSCI_device->IFG & UCTXIFG));

  // Put character in buffer to be transferred
  EUSCI_device->TXBUF = data;
}


uint8_t SPI_send_with_response(EUSCI_SPI_TYPE *EUSCI_device, uint8_t data) {
  // If transmit buffer is not empty, wait for it to be empty
  while(!(EUSCI_device->IFG & UCTXIFG));

  // Put character in buffer to be transferred
  EUSCI_device->TXBUF = data;

  // Wait until the receive buffer has been filled
  while(!(EUSCI_device->IFG & UCRXIFG));

  // Return the supplied byte
  return EUSCI_device->RXBUF;
}

void SPI_test(void) {
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
}
