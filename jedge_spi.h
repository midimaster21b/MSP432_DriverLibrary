/*
 * jedge_spi.h
 *
 *  Created on: Jun 27, 2018
 *      Author: Joshua Edgcombe
 */

#ifndef JEDGE_SPI_H_
#define JEDGE_SPI_H_

#include <stdint.h>
#include "msp.h"

// Define which SPI eUSCI type to use
#ifndef EUSCI_SPI_TYPE
// Defaults to eUSCI_B0
#define EUSCI_SPI_TYPE EUSCI_B_SPI_Type

// Define ports and pins to be used
#define SPI_PORT P1
#define SPI_STE_PIN  4
#define SPI_CLK_PIN  5
#define SPI_MOSI_PIN 6
#define SPI_MISO_PIN 7

// Define pin masks
#define SPI_STE_MASK  1 << SPI_STE_PIN
#define SPI_CLK_MASK  1 << SPI_CLK_PIN
#define SPI_MOSI_MASK 1 << SPI_MOSI_PIN
#define SPI_MISO_MASK 1 << SPI_MISO_PIN

#define SPI_PIN_MASK (SPI_STE_MASK|SPI_CLK_MASK|SPI_MOSI_MASK|SPI_MISO_MASK)
#endif

typedef struct EUSCI_SPI_config_struct {
  uint8_t clock_phase;
  uint8_t clock_polarity;
  uint8_t msb_first;
  uint8_t seven_bit_data;
  uint8_t master_mode;
  uint8_t eusci_mode_bit_10;
  uint8_t eusci_mode_bit_9;
  uint8_t sync_mode;
  uint8_t clk_sel_bit_7;
  uint8_t clk_sel_bit_6;
  uint8_t ste_mode;
} EUSCI_SPI_config;

void SPI_init(EUSCI_SPI_TYPE *EUSCI_device, EUSCI_SPI_config *config);
void SPI_send(EUSCI_SPI_TYPE *EUSCI_device, char *data);
uint8_t SPI_send_with_response(EUSCI_SPI_TYPE *EUSCI_device, uint8_t data);

#endif /* JEDGE_SPI_H_ */
