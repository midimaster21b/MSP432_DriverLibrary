/*
 * jedge_sd_card.h
 *
 *  Created on: July 9, 2018
 *      Author: Joshua Edgcombe
 */

#ifndef JEDGE_SD_CARD_H_
#define JEDGE_SD_CARD_H_

/**********************
 * Pin definitions
 **********************/
#define SD_CS_PORT P5
#define SD_CS_PIN  2
#define SD_CS_MASK 1 << SD_CS_PIN

/**********************
 * Command definitions
 **********************/
#define SD_BYTES_PER_CMD 6
#define SD_RESET_CMD_CRC 0x4A

// Commands
#define SD_GO_IDLE_STATE_CMD            0x00 // Software reset
#define SD_SEND_OP_COND_CMD             0x01 // Initiate initialization process
#define SD_SEND_IF_COND_CMD             0x08 // Initiate initialization process (SDC only)
#define SD_SEND_CSD_CMD                 0x09 // Read CSD register
#define SD_SEND_CID_CMD                 0x0A // Read CID register
#define SD_STOP_TRANSMISSION_CMD        0x0C // Stop reading data (For multiple read command)
#define SD_SET_BLOCKLEN_CMD             0x10 // Change R/W block size
#define SD_READ_SINGLE_BLOCK_CMD        0x11 // Read a single block
#define SD_READ_MULTIPLE_BLOCK_CMD      0x12 // Read multiple blocks
#define SD_SET_BLOCK_COUNT_CMD          0x17 // Set number of blocks to transfer in next multi-block read/write (MMC only)
#define SD_WRITE_BLOCK_CMD              0x18 // Write a single block
#define SD_WRITE_MULTIPLE_BLOCK_CMD     0x19 // Write multiple blocks
#define SD_APP_CMD_CMD                  0x37 // Leading command of ACMD's
#define SD_READ_OCR_CMD                 0x3A // Read OCR

// ACMD's (Requires issuing of SD_APP_CMD_CMD immediately prior to issuing these commands)
#define SD_SET_WR_BLOCK_ERASE_COUNT_CMD 0x17
#define SD_APP_SEND_OP_COND_CMD         0x29 // Check voltage range (SDC v2 only)

// SD card functions
void sd_init(void);
void sd_test(void);
uint8_t sd_send_command(uint8_t command, uint32_t argument, uint8_t CRC);
void sd_clock_only(uint32_t num_bytes);
void sd_clock_only_time(uint32_t milliseconds);

#endif /* JEDGE_SD_CARD_H_ */
