/*
 * jedge_systick.c
 *
 *  Created on: Jun 27, 2018
 *      Author: Joshua Edgcombe
 */

#include <stdint.h>
#include "jedge_systick.h"

void systick_setup(uint32_t max_value, uint8_t interrupt_enable) {
  // Set max value
  SysTick->LOAD = max_value;

  // Enable interrupt (if expected)
  if(interrupt_enable) {
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
  } else {
    SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
  }
}

void systick_start(void) {
  // Clear count count flag (necessary?)
  SysTick->CTRL &= ~SysTick_CTRL_COUNTFLAG_Msk;

  // Start the SysTick timer
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

void systick_stop(void) {
  // Stop the SysTick timer
  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void systick_blocking_wait_ms(uint32_t delay) {
  // Stop systick if it is currently running
  systick_stop();

  // Set it up for the appropriate delay in ms (blocking: no interrupt)
  systick_setup(delay * MASTER_CLK_FREQ / 1000, 0);

  // Start the timer
  systick_start();

  // Poll on the interrupt status flag
  while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
}

void systick_test(void) {
  P1->DIR |= 1;
  P1->OUT |= 1;

  // Setup the systick timer with max value of 12,000,000 and enable interrupt
  systick_setup(12000000, 1);

  // Enable all interrupts
  /* Interrupt_enableMaster(); */

  // Start the timer
  systick_start();
}

void SysTickISR(void) {
  P1->OUT ^= 1;
}
