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
  // Initialize SPI peripheral
  sd_device = EUSCI_B2_SPI;
  SPI_init(sd_device, &sd_spi_config);

  // Wait for at least 1 ms after power on (Before or after CS is high?)
  systick_blocking_wait_ms(5);

  // Send >74 clock cycles to allow device to initialize
  sd_clock_only(80);

  // Put the device into idle state
  sd_send_command(SD_GO_IDLE_STATE_CMD, 0x00, SD_RESET_CMD_CRC);

  // Wait for the response...
  sd_clock_only(80);
}

void sd_test(void) {
  sd_init();
}

uint8_t sd_send_command(uint8_t command, uint32_t argument, uint8_t CRC) {
  uint8_t cmd[SD_BYTES_PER_CMD];

  // Leading 01b followed by command number
  cmd[0] = (0x01 << 6) | (command & 0x3F);
  cmd[1] = (argument >> 24) & 0xFF;
  cmd[2] = (argument >> 16) & 0xFF;
  cmd[3] = (argument >> 8) & 0xFF;
  cmd[4] = argument & 0xFF;
  cmd[5] = ((CRC & 0x7F) << 1) | 0x01; // 7-bit CRC + stop bit

  SPI_send_data(sd_device, cmd, sizeof(cmd));

  // Make this the response of the SD card
  return 0x00;
}

void sd_clock_only(uint8_t num_bytes) {
  // Initialize all 0xFF's for clock signal
  uint8_t *clock_only = malloc(num_bytes * sizeof(uint8_t));

  int offset;

  // Set all locations to 0xFF (all high)
  for(offset=0; offset<num_bytes; offset++) {
    *(clock_only+offset) = 0xFF;
  }

  SPI_send_data(sd_device, clock_only, num_bytes);

  free(clock_only);
}
