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
  // Set SD chip select pin to output
  SD_CS_PORT->DIR |= SD_CS_MASK;

  // Set chip select pin high for initialization
  SD_CS_PORT->OUT |= SD_CS_MASK;

  // Initialize SPI peripheral
  sd_device = EUSCI_B2_SPI;
  SPI_init(sd_device, &sd_spi_config);

  // Wait for at least 1 ms after power on
  systick_blocking_wait_ms(5);

  // Send >74 clock cycles(supplying 80*8) to allow device to initialize
  sd_clock_only(80);

  // THIS LINE IS LITERALLY ONLY HERE TO ENSURE I CAN APPROPRIATELY SEE/TRANSLATE THE SPI
  // USING MY SALEAE ANALYZER.
  systick_blocking_wait_ms(50);

  // Put the device into idle state
  sd_send_command(SD_GO_IDLE_STATE_CMD, 0x00, SD_RESET_CMD_CRC);
}

void sd_test(void) {
  sd_init();
}

uint8_t sd_send_command(uint8_t command, uint32_t argument, uint8_t CRC) {
  uint8_t cmd[SD_BYTES_PER_CMD];

  // Set SD chip select pin low(active?)
  SD_CS_PORT->OUT &= ~SD_CS_MASK;

  // Leading 01b followed by command number
  cmd[0] = (0x01 << 6) | (command & 0x3F);
  cmd[1] = (argument >> 24) & 0xFF;
  cmd[2] = (argument >> 16) & 0xFF;
  cmd[3] = (argument >> 8) & 0xFF;
  cmd[4] = argument & 0xFF;
  cmd[5] = ((CRC & 0x7F) << 1) | 0x01; // 7-bit CRC + stop bit

  SPI_send_data(sd_device, cmd, sizeof(cmd));

  // Wait for a response from the SD card
  /* sd_clock_only_time(200); */
  sd_clock_only(50000);

  // Set SD chip select pin inactive (high)
  SD_CS_PORT->OUT |= SD_CS_MASK;

  // Send two bytes to ensure SD card doesn't hog MISO line
  sd_clock_only(2);

  // TODO: Make this the response of the SD card
  return 0x00;
}

void sd_clock_only(uint32_t num_bytes) {

  int count;

  // Set all locations to 0xFF (all high)
  for(count=0; count<num_bytes; count++) {
    SPI_send_byte(sd_device, 0xFF);
  }
}

void sd_clock_only_time(uint32_t milliseconds) {
  systick_stop();
  systick_setup(systick_ms_to_cycles(milliseconds), 0x00);
  systick_start();

  while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)) {
    // Send 0xFF
    SPI_send_byte(sd_device, 0xFF);
  }
}
