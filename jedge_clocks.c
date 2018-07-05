/*
 * jedge_clocks.c
 *
 *  Created on: Jun 28, 2018
 *      Author: Joshua Edgcombe
 */

#include "driverlib.h"

void init_clocks(void) {
  // Misc pin stuff
  MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ,
						  GPIO_PIN3 | GPIO_PIN2, GPIO_PRIMARY_MODULE_FUNCTION);
  MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

  // Set external (LFXT, HFXT) frequencies
  // Low frequency is 32kHz, External is SW configurable from 1-48MHz
  CS_setExternalClockSourceFrequency(32000, CS_48MHZ);

  // Set PCM to VCORE1
  MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);

  // Set effective clock speed to 1/4
  MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
  MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);

  // Start the HFXT, but don't bypass initially
  CS_startHFXT(false);

  // Set the DCO to 327680 Hz, necessary for 200ms sample window
  /* CS_setDCOFrequency(327680); */

  // Initialize master clock to high frequency external clock
  CS_initClockSignal(CS_MCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);

  // Initializes CS_HSMCLK (don't understand the necessity of this line...)
  MAP_CS_initClockSignal(CS_HSMCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_16);

  // Initializes to 327680 for sample window
  /* MAP_CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1); */

  // Initialize SMCLK to high frequency DCO clock with 1 times clock divider
  MAP_CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1 );

  // Initialize to 3MHz for LCD
  /* MAP_CS_initClockSignal(CS_SMCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_16); */
}
