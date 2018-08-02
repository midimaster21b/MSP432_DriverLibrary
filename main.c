/* DriverLib Includes */
#include "driverlib.h"

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
/* #include <math.h> */

/* Custom Includes */
#include "Systick.h"
#include "GPIO.h"
#include "jedge_pwm.h"
#include "TimerA.h"

#define ONE_KHZ_PERIOD (750-1)
#define FIVE_HUNDRED_HZ_PERIOD (375-1)

// --- This function imitates police siren and light show ----
void light_show(int bright)
{
  int wait = 1000-bright;

  // Compare value should range from 500 Hz to 1 KHz
  // Compute compare value using the value of "bright" that first ranges from 1 to 998 and then from 999 to 2
  // After you devise a formula to compute the compare value, assign it to Timer A Compare register
  // Use 50% DC
  
  // Compute the period (Max - (proportion * delta))
  uint32_t period = ONE_KHZ_PERIOD - ((wait * ONE_KHZ_PERIOD) - (wait * FIVE_HUNDRED_HZ_PERIOD)) / 999;
  /* uint16_t period = 1000; */

  jedge_pwm_set_frequency(period, period / 2);

  // Turn ON LEDA and LEDB
  on1();

  // Turn OFF LEDA and LEDB
  off2();

  // Delay for "bright" time
  SysTick_delay(2 * bright);

  // Turn ON LEDC and LEDD
  on2();

  // Delay for "wait" time
  /* SysTick_delay(wait); */

  // Turn OFF LEDC and LEDD
  off1();

  // Delay for "wait" time
  SysTick_delay(2 * wait);
}


int main(void)
{
  volatile int i;

  // Stop Watchdog
  WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

  // Sets the direction of peripherals
  set_data_directions();

  // Initialize Systick peripheral
  SysTick_Init();

  // Initialize Timer A peripheral
  TimerA_init();

  while(1) {
    for(i=1; i<999; i++)
      light_show(i);

    for(i=999; i>1; i--)
      light_show(i);
  }
}
