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

// Pin declarations
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

void st7735_setup(void);
void st7735_setup_pins(void);
void st7735_setup_peripherals(void);
void st7735_setup_peripherals_spi(void);
void st7735_hard_reset(void);

#endif /* JEDGE_ST7735_H_ */
