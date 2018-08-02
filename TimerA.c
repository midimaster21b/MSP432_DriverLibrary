// --- TimerA.c ---
// --- Created on: Jul 30, 2017 ---
// --- Author: Chirag Parikh  ---

/* DriverLib Includes */
#include "driverlib.h"

/* Timer_A UpMode Configuration Parameter */
const Timer_A_UpModeConfig upConfig =
  {
    , // SMCLK Clock Source
    , // SMCLK/1 = 3 MHz
    , // Variable period
    , // Disable Timer interrupt
    , // Enable CCR0 interrupt
      // Clear value
  };

// --- Initialize Timer A ---
void TimerA_init(void)
{
  // Configuring Timer_A2 for Up Mode
  // Enable NVIC to accept Timer interrupt
  // Start Timer
  // Enable Interrupt mechanism
}


// --- TA2_0 ISR ---
void TA2_0_IRQHandler(void)
{
  // Toggle BUZZER pin

  // Clear Capture-Compare Interrupt Flag

}
