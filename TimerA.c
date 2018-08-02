// --- TimerA.c ---
// --- Created on: Jul 30, 2017 ---
// --- Author: Chirag Parikh  ---

/* DriverLib Includes */
#include "driverlib.h"
#include "TimerA.h"
#include "jedge_pwm.h"

// --- Initialize Timer A ---
void TimerA_init(void)
{
  jedge_pwm_init();

  // Configuring Timer_A2 for Up Mode
  // Enable NVIC to accept Timer interrupt

  // Start Timer
  jedge_pwm_start(JEDGE_PWM_BUZZER_TIMER);

  // Enable Interrupt mechanism
}


// --- TA2_0 ISR ---
void TA0_0_IRQHandler(void)
{
  // Toggle BUZZER pin

  // Clear Capture-Compare Interrupt Flag

}
