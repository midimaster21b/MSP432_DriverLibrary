// --- Systick.c ---
// --- Created on: Jul 30, 2017 ---
// --- Author: Chirag Parikh  ---

/* DriverLib Includes */
#include "driverlib.h"

// ----- Initialize SysTick ------
void SysTick_Init(void)
{
  // disable SysTick during setup
  // any write to current clears it
  // enable SysTick, 3MHz, no interrupts
}

// ---- Configurable Systick delay from 1 microsec
void SysTick_delay(uint16_t delay)
{
  // configure it to count from 1 microsecond count down to zero
  // any write to CVR clears it and COUNTFLAG in CSR

  // Wait for flag to be SET (Timeout happened)
}
