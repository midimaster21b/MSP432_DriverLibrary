/*
 * jedge_st7735.c
 *
 *  Created on: Jun 27, 2018
 *      Author: Joshua Edgcombe
 */

#include "jedge_st7735.h"
#include "jedge_spi.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

// SPI device handle
EUSCI_B_SPI_Type *EUSCI_device = NULL;

/******************************
 * Initializes the LCD driver.
 ******************************/
void st7735_setup(void) {
  // Setup for GPIO pins
  st7735_setup_pins();

  // Perform hard reset
  st7735_hard_reset();

  // Set up any necessary peripherals
  st7735_setup_peripherals();
}

/***********************************************
 * Set up the GPIO pins, peripheral pins should
 * be setup in peripheral drivers.
 ***********************************************/
void st7735_setup_pins(void) {
  // Set TFT light to output
  TFT_LIGHT_PORT->DIR |= TFT_LIGHT_MASK;
  TFT_LIGHT_PORT->OUT |= TFT_LIGHT_MASK;

  // Set chip select port to output and start low
  TFT_SPI_CS_PORT->DIR |= TFT_SPI_CS_MASK;
  TFT_SPI_CS_PORT->OUT &= TFT_SPI_CS_MASK;

  // Set the Data/Command line port to output
  // See ST7735 manual(9.4 Serial interface pg. 33) for further use.
  TFT_DC_PORT->DIR |= TFT_DC_MASK;
  TFT_DC_PORT->OUT |= TFT_DC_MASK;

  // Set the reset port to output
  // This line is active high
  TFT_RESET_PORT->DIR |= TFT_RESET_MASK;
  TFT_RESET_PORT->OUT |= TFT_RESET_MASK;
}

/***********************************************
 * Initializes the LCD driver's peripherals.
 ***********************************************/
void st7735_setup_peripherals(void) {
  st7735_setup_peripherals_spi();
}

/***********************************************
 * Initializes the LCD driver's SPI peripheral.
 ***********************************************/
void st7735_setup_peripherals_spi(void) {
  // Create SPI initialization struct
  EUSCI_SPI_config lcd_config = {
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

  // Assign initial value to SPI device handle
  EUSCI_B_SPI_Type *EUSCI_device = EUSCI_B0_SPI;

  // Initialize SPI peripheral
  SPI_init(EUSCI_device, &lcd_config);
}

/*******************************************************
 * Perform a hard reset on the LCD using the reset line.
 *******************************************************/
void st7735_hard_reset(void) {
  // Pull reset line low
  TFT_RESET_PORT->OUT &= ~TFT_RESET_MASK;

  // Wait for time > 200ms
  int x;
  for(x=0; x<200000; x++);

  // Pull reset line high
  TFT_RESET_PORT->OUT |= TFT_RESET_MASK;
}
