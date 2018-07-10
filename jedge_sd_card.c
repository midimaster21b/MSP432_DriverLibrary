/*
 * jedge_sd_card.c
 *
 *  Created on: July 9, 2018
 *      Author: Joshua Edgcombe
 */

#include <stdint.h>
#include <stdlib.h>

#include "jedge_spi.h"
#include "jedge_systick.h"

#include "jedge_sd_card.h"


EUSCI_B_SPI_Type *sd_device;

// Create SPI configuration struct
EUSCI_SPI_config sd_spi_config = {
  .clock_phase = 1,
  .clock_polarity = 0,
  .msb_first = 1,
  .seven_bit_data = 0,
  .master_mode = 1,
  .eusci_mode_bit_10 = 0,   // Active High CS, opposite of LCD... (Remember for circuit design)
  .eusci_mode_bit_9 = 1,
  .sync_mode = 1,
  .clk_sel_bit_7 = 1,
  .clk_sel_bit_6 = 0,
  .ste_mode = 1,
  .prescaler = 60           // Sets clock to 400 kHz
};

void sd_init(void) {
  uint8_t *clock_only = malloc(100 * sizeof(uint8_t));

  uint8_t reset_cmd[SD_BYTES_PER_CMD] = {
    (command(SD_GO_IDLE_STATE_CMD, 0x00, SD_RESET_CMD_CRC) >> 40) & 0xFF,
    (command(SD_GO_IDLE_STATE_CMD, 0x00, SD_RESET_CMD_CRC) >> 32) & 0xFF,
    (command(SD_GO_IDLE_STATE_CMD, 0x00, SD_RESET_CMD_CRC) >> 24) & 0xFF,
    (command(SD_GO_IDLE_STATE_CMD, 0x00, SD_RESET_CMD_CRC) >> 16) & 0xFF,
    (command(SD_GO_IDLE_STATE_CMD, 0x00, SD_RESET_CMD_CRC) >> 8) & 0xFF,
    (command(SD_GO_IDLE_STATE_CMD, 0x00, SD_RESET_CMD_CRC) >> 0) & 0xFF,
  };

  // Initialize SPI peripheral
  sd_device = EUSCI_B2_SPI;
  SPI_init(sd_device, &sd_spi_config);

  // Wait for at least 1 ms after power on (Before or after CS is high?)
  systick_blocking_wait_ms(5);

  // Send >74 clock cycles to allow device to initialize
  SPI_send_data(sd_device, clock_only, 80);

  // Put the device into idle state
  SPI_send_data(sd_device, reset_cmd, SD_BYTES_PER_CMD);

  // Wait for the response...
  SPI_send_data(sd_device, clock_only, 80);
}

void sd_test(void) {
  sd_init();
}
