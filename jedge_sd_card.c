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

uint8_t sd_init(void) {
  uint8_t *retval;

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

  retval = sd_send_command(SD_GO_IDLE_STATE_CMD, 0x00, SD_RESET_CMD_CRC, SD_RESPONSE_R1);

  // Put the device into idle state (0x01 indicates success)
  if(*retval != 0x01) {
    // Free malloc'd memory
    free(retval);

    // TODO: THIS SHOULD DO SOMETHING EXCEPTIONAL/RETURN SOMETHING BAD!!!
    return SD_OP_FAILURE;
  }
  else {
    // Success! (but we still need to free that memory...)
    free(retval);
  }

  /* systick_blocking_wait_ms(5); */

  retval = sd_send_command(SD_SEND_IF_COND_CMD, 0x000001AA, SD_CMD8_INIT_CRC, SD_RESPONSE_R7);

  free(retval);

  return SD_OP_SUCCESS;
}

void sd_test(void) {
  sd_init();
}

uint8_t *sd_send_command(uint8_t command, uint32_t argument, uint8_t CRC, uint8_t response_type) {
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

  uint8_t *recv;
  uint16_t num_recv_bytes = 0;

  // Handle expected response
  switch(response_type) {
  case SD_RESPONSE_R1:
    num_recv_bytes = SD_RESPONSE_R1_NUM_BYTES;
    break;
  case SD_RESPONSE_R3:
    num_recv_bytes = SD_RESPONSE_R3_NUM_BYTES;
    break;
  case SD_RESPONSE_R7:
    num_recv_bytes = SD_RESPONSE_R7_NUM_BYTES;
    break;
  }

  // Receive the response
  recv = sd_recv_bytes(num_recv_bytes);

  // Set SD chip select pin inactive (high)
  /* SD_CS_PORT->OUT |= SD_CS_MASK; */

  // Send two bytes to ensure SD card doesn't hog MISO line
  /* sd_clock_only(2); */

  // TODO: Make this the response of the SD card
  return recv;
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

// TODO: Add timeout to function
uint8_t sd_recv_byte(void) {
  uint8_t recv = 0xFF;

  // If data is available, receive it first
  if(sd_device->IFG & UCRXIFG) {
    recv = sd_device->RXBUF;
  }

  // Otherwise, send a byte to receive a byte (well, keep the clock going at least)
  while(recv == 0xFF) {
    SPI_send_byte(sd_device, 0xFF);
    recv = SPI_recv_byte(sd_device);
  }

  return recv;
}

// TODO: Add timeout to function
uint8_t *sd_recv_bytes(uint16_t num_bytes) {
  if(num_bytes == 0) {
    return NULL;
  }

  // Initialize function variables
  uint8_t recv;
  uint16_t byte_num;

  // Allocate space for return value
  uint8_t *recv_bytes = malloc(num_bytes * sizeof(uint8_t));

  // If data is available, receive it first
  if(sd_device->IFG & UCRXIFG) {
    recv = sd_device->RXBUF;
  }
  else {
    recv = 0xFF;
  }

  // Otherwise, send a byte to receive a byte (well, keep the clock going at least)
  while(recv == 0xFF) {
    SPI_send_byte(sd_device, 0xFF);
    recv = SPI_recv_byte(sd_device);
  }

  // Store the first found byte
  *(recv_bytes) = recv;

  // Get the remaining expected bytes and load them into the return value
  for(byte_num=0; byte_num<num_bytes-1; byte_num++) {
    SPI_send_byte(sd_device, 0xFF);
    *(recv_bytes+byte_num) = SPI_recv_byte(sd_device);
  }

  return recv_bytes;
}
