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
  uint8_t card_type;

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

  /************************
   * Enter idle mode/state
   ************************/
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

  /***************************************************
   * Check which kind of card is plugged in.
   * NOTE: Only handles high capacity cards currently
   ***************************************************/
  retval = sd_send_command(SD_SEND_IF_COND_CMD, 0x000001AA, SD_CMD8_INIT_CRC, SD_RESPONSE_R7);

  if(*retval == 0x01 && *(retval+3) == 0x01 && *(retval+4) == 0xAA) {
    // This is good! (High capacity card detected)
    free(retval);

    card_type = SD_HIGH_CAP_CARD;
  }
  else {
    return SD_OP_FAILURE;
  }

  switch(card_type) {
  case SD_HIGH_CAP_CARD:
    sd_initialize_high_capacity();
    break;
  }

  // Reinitialize SPI connection to 12 MHz
  /* sd_spi_config.prescaler = 2; */
  /* SPI_init(sd_device, &sd_spi_config); */

  return SD_OP_SUCCESS;
}

void sd_test(void) {
  uint8_t replacement_data[SD_BLOCK_SIZE] = { 0 };
  uint8_t replacement_CRC[2] = { 0 };

  uint16_t temp;

  // Initialize replacement data to 0x0F
  for(temp=0; temp<SD_BLOCK_SIZE; temp++) {
    replacement_data[temp] = 0x0F;
  }

  // Initialize the SD card
  sd_init();

  systick_blocking_wait_ms(1);

  // Read the data at location zero
  free(sd_read_block(0));

  systick_blocking_wait_ms(1);

  // Read the initial data into original data
  free(sd_read_block(1));

  systick_blocking_wait_ms(1);

  // Write replacement data onto the block
  sd_write_block(0, replacement_data, replacement_CRC);

  systick_blocking_wait_ms(1);

  // Verify the replacement data was written
  sd_read_block(0);

  systick_blocking_wait_ms(1);

  sd_read_block(1);

  systick_blocking_wait_ms(1);
}

uint8_t *sd_send_command(uint8_t command, uint32_t argument, uint8_t CRC, uint8_t response_type) {
  uint8_t cmd[SD_BYTES_PER_CMD];

  // Set SD chip select pin low(active)
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
uint8_t sd_recv_byte(uint8_t exclude_byte) {
  uint8_t recv = exclude_byte;

  // If data is available, receive it first
  if(sd_device->IFG & UCRXIFG) {
    recv = sd_device->RXBUF;
  }

  // Otherwise, send a byte to receive a byte (well, keep the clock going at least)
  while(recv == exclude_byte) {
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
  for(byte_num=1; byte_num<num_bytes; byte_num++) {
    SPI_send_byte(sd_device, 0xFF);
    *(recv_bytes+byte_num) = SPI_recv_byte(sd_device);
  }

  return recv_bytes;
}

void sd_initialize_high_capacity(void) {
  uint8_t *retval;

  free(sd_send_command(SD_APP_CMD_CMD, 0x00000000, 0x00, SD_RESPONSE_R1));
  retval = sd_send_command(SD_APP_SEND_OP_COND_CMD, 0x40000000, 0x00, SD_RESPONSE_R1);

  while(*retval == 0x01) {
    free(retval);
    free(sd_send_command(SD_APP_CMD_CMD, 0x00000000, 0x00, SD_RESPONSE_R1));
    retval = sd_send_command(SD_APP_SEND_OP_COND_CMD, 0x40000000, 0x00, SD_RESPONSE_R1);
  }

  free(retval);

  retval = sd_send_command(SD_READ_OCR_CMD, 0x00000000, 0x00, SD_RESPONSE_R3);

  if(*(retval+1) & 0x40) {
    // SD Ver. 2+ (Block address)
    free(retval);
  }
  else {
    // SD Ver. 2+ (Byte address)
    free(retval);

    // Set the block size to 512 bytes
    free(sd_send_command(SD_SET_BLOCKLEN_CMD, 0x00000200, 0x00, SD_RESPONSE_R1));
  }
}

// NOTE: address is the block number, not the byte address
uint8_t *sd_read_block(uint32_t address) {
  free(sd_send_command(SD_READ_SINGLE_BLOCK_CMD, address, 0x00, SD_RESPONSE_R1));

  // For some reason I had it in my mind that the data size was going to be 513 bytes initially
  // so I tested receiving 520 and 513 appears appropriate unless 2-byte CRC is 0xFF...
  // Why is this either 513 or 515? According to description Data token(1 byte), Data block(512 bytes), CRC(2 bytes)
  // this should definitely be 515...
  return sd_recv_bytes(515);
}

// NOTE: CRC must be 2-bytes, but doesn't need to be correct unless explicitly enabled
// NOTE: address is the block number, not the byte address
uint8_t sd_write_block(uint32_t address, uint8_t *data, uint8_t *CRC) {
  uint8_t data_token[1] = {0xFE};

  // Send initial write command expecting R1 response
  free(sd_send_command(SD_WRITE_SINGLE_BLOCK_CMD, address, 0x00, SD_RESPONSE_R1));

  // Send data packet (data token)
  SPI_send_data(sd_device, data_token, 1);

  // Send actual data to be written
  SPI_send_data(sd_device, data, SD_BLOCK_SIZE);

  // Send CRC bytes (2 bytes)
  SPI_send_data(sd_device, CRC, 2);

  // Get data response packet
  uint8_t *response = sd_recv_bytes(1);

  if((*response & 0x1F) != 0x05) {
    // Either failure due to rejected CRC error(0x0B) or a write error(0x0D)
    return SD_OP_FAILURE;
  }

  // Wait until something other than 0x00 is returned.
  // The SD card is busy while the line is low.
  while(sd_recv_byte(0x00) == 0x00);

  return SD_OP_SUCCESS;
}
