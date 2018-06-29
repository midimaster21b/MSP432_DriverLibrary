/*
 * jedge_st7735.h
 *
 *  Created on: Jun 27, 2018
 *      Author: Joshua Edgcombe
 */

#ifndef JEDGE_ST7735_H_
#define JEDGE_ST7735_H_

#include "msp.h"
#include "jedge_spi.h"

/*******************
 * Pin declarations
 *******************/
#define TFT_LIGHT_PORT P6
#define TFT_LIGHT_PIN  6
#define TFT_LIGHT_MASK 1 << TFT_LIGHT_PIN

#define TFT_DC_PORT P5
#define TFT_DC_PIN  2
#define TFT_DC_MASK 1 << TFT_DC_PIN

#define TFT_RESET_PORT P3
#define TFT_RESET_PIN  6
#define TFT_RESET_MASK 1 << TFT_RESET_PIN

#define TFT_SPI_MOSI_PORT P1
#define TFT_SPI_MOSI_PIN  6
#define TFT_SPI_MOSI_MASK 1 << TFT_SPI_MOSI_PIN

#define TFT_SPI_CS_PORT P5
#define TFT_SPI_CS_PIN  0
#define TFT_SPI_CS_MASK 1 << TFT_SPI_CS_PIN

#define TFT_SPI_CLK_PORT P1
#define TFT_SPI_CLK_PIN  5
#define TFT_SPI_CLK_MASK 1 << TFT_SPI_CLK_PIN

#define TFT_SPI_MISO_PORT P1
#define TFT_SPI_MISO_PIN  7
#define TFT_SPI_MISO_MASK 1 << TFT_SPI_MISO_PIN

/***********************
 * Command declarations
 ***********************/
// System function commands
#define ST7735_NOP        0x00 // No operation
#define ST7735_SWRESET    0x01 // Software reset
#define ST7735_RDDID      0x04 // Read display ID
#define ST7735_RDDST      0x09 // Read display status
#define ST7735_RDDPM      0x0A // Read display power
#define ST7735_RDD_MADCTL 0x0B // Read display
#define ST7735_RDD_COLMOD 0x0C // Read display pixel
#define ST7735_RDDIM      0x0D // Read display image
#define ST7735_RDDSM      0x0E // Read display signal
#define ST7735_SLPIN      0x10 // Sleep in & booster off?
#define ST7735_SLPOUT     0x11 // Sleep out & booster on?
#define ST7735_PTLON      0x12 // Partial mode on
#define ST7735_NORON      0x13 // Partial mode off (Normal)
#define ST7735_INVOFF     0x20 // Display inverion off
#define ST7735_INVON      0x21 // Display inverion on
#define ST7735_GAMSET     0x26 // Gamm curve select
#define ST7735_DISPOFF    0x28 // Display off
#define ST7735_DISPON     0x29 // Display on
#define ST7735_CASET      0x2A // Column address set
#define ST7735_RASET      0x2B // Row address set
#define ST7735_RAMWR      0x2C // Memory write
#define ST7735_RGBSET     0x2D // LUT for 4k, 65k, 262k color
#define ST7735_RAMRD      0x2E // Memory read
#define ST7735_PTLAR      0x30 // Partial start/end address set
#define ST7735_TEOFF      0x34 // Tearing effect line off
#define ST7735_TEON       0x35 // Tearing effect mode set & on
#define ST7735_MADCTL     0x36 // Memory data access control
#define ST7735_IDMOFF     0x38 // Idle mode off
#define ST7735_IDMON      0x39 // Idle mode on
#define ST7735_COLMOD     0x3A // Interface pixel format
#define ST7735_RDID1      0xDA // Read ID1
#define ST7735_RDID2      0xDB // Read ID2
#define ST7735_RDID3      0xDC // Read ID3

// Panel function command list
#define ST7735_FRMCTR1    0xB1 // In normal mode (Full colors)
#define ST7735_FRMCTR2    0xB2 // In idle mode (8-colors)
#define ST7735_FRMCTR3    0xB3 // In partial mode + full colors
#define ST7735_INVCTR     0xB4 // Display inversion control
#define ST7735_PWCTR1     0xC0 // Power control setting
#define ST7735_PWCTR2     0xC1 // Power control setting
#define ST7735_PWCTR3     0xC2 // Power control setting (In normal mode (Full colors))
#define ST7735_PWCTR4     0xC3 // Power control setting (In idle mode (8-colors))
#define ST7735_PWCTR5     0xC4 // Power control setting (In partial mode + full colors)
#define ST7735_VMCTR1     0xC5 // VCOM control 1
#define ST7735_VMOFCTR    0xC7 // Set VCOM offset control
#define ST7735_WRID2      0xD1 // Set LCM version code
#define ST7735_WRID3      0xD2 // Set customer project code
#define ST7735_NVCTR1     0xD9 // NVM control status
#define ST7735_NVCTR2     0xDE // NVM read command
#define ST7735_NVCTR3     0xDF // NVM write command

/**********************************
 * ST7735 library functions
 **********************************/
// st7735 initialization functions
void st7735_setup(void);
void st7735_setup_pins(void);
void st7735_setup_peripherals(void);
void st7735_setup_peripherals_spi(void);
void st7735_hard_reset(void);

// st7735 communication functions
uint8_t st7735_send_data(uint8_t data);
uint8_t st7735_send_command(uint8_t cmd);

#endif /* JEDGE_ST7735_H_ */
