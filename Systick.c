// --- Systick.c ---
// --- Created on: Jul 30, 2017 ---
// --- Author: Chirag Parikh  ---

/* DriverLib Includes */
#include "driverlib.h"

#include "Systick.h"
#include "jedge_systick.h"

// ----- Initialize SysTick ------
void SysTick_Init(void)
{
  // disable SysTick during setup
  // any write to current clears it
  // enable SysTick, 3MHz, no interrupts
  /* systick_setup(uint32_t max_value, uint8_t interrupt_enable); */
  systick_setup(0x03, 0);
}

// ---- Configurable Systick delay from 1 microsec
void SysTick_delay(uint16_t delay)
{
  // configure it to count from 1 microsecond count down to zero
  // any write to CVR clears it and COUNTFLAG in CSR

  // Stop systick if it is currently running
  systick_stop();

  // Set it up for the appropriate delay in ms (blocking: no interrupt)
  systick_setup(SYSTICK_MICROSECOND_MULTIPLIER * delay, 0);

  // Start the timer
  systick_start();

  // Wait for flag to be SET (Timeout happened)
  // Poll on the interrupt status flag
  while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
}
