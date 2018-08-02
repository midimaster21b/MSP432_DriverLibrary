/* DriverLib Includes */
#include "driverlib.h"

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

/* Custom Includes */


// --- This function imitates police siren and light show ----
void light_show(int bright)
{
  int wait = 1000-bright;

  // Compare value should range from 500 Hz to 1 KHz
  // Compute compare value using the value of "bright" that first ranges from 1 to 998 and then from 999 to 2
  // After you devise a formula to compute the compare value, assign it to Timer A Compare register
  // Use 50% DC


  // Turn ON LEDA and LEDB
  // Delay for "bright" time
  // Turn OFF LEDA and LEDB
  // Delay for "bright" time

  // Turn ON LEDC and LEDD
  // Delay for "wait" time
  // Turn OFF LEDC and LEDD
  // Delay for "wait" time
}


int main(void)
{
  volatile int i;

  // Stop Watchdog

  // Sets the direction of peripherals
  // Initialize Systick peripheral
  // Initialize Timer A peripheral


  while(1)
    {
      for(i=1; i<999; i++)
	light_show(i);

      for(i=999; i>1; i--)
	light_show(i);
    }
}
