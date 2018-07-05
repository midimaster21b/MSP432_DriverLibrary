#include <math.h>
#include <stdint.h>
#include "msp.h"
#include "jedge_spi.h"
#include "jedge_adc.h"
#include "jedge_clocks.h"
#include "jedge_lcd.h"
#include "jedge_timer32.h"

#include "driverlib.h"

#include "main.h"

// Initialize buffers
uint16_t buffer_a[NUM_SAMPLES] = {0};
uint16_t buffer_b[NUM_SAMPLES] = {0};

// Initialize
uint8_t full_buffer_flag = BUFFER_A_FULL;
float average_value = 50.0;
uint8_t average_percentage = 50;

/**
 * main.c
 */
void main(void)
{
  // stop watchdog timer
  WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

  // Initialize the clocks
  init_clocks();

  // Initialize the sample timer
  init_sample_timer();

  // Initialize the lcd
  lcd_init();

  // Initialize the ADC
  ADC_init();

  // Enable interrupts on the microcontroller
  MAP_Interrupt_enableMaster();

  // Start the sample timer
  start_sample_timer();

  while(1) {

    if(full_buffer_flag == BUFFER_A_FULL) {
      // Signify that the buffer has been handled
      full_buffer_flag = BUFFER_HANDLED;

      // Calculate average
      average_value = calculate_average(buffer_a);

      // Calculate average percentage
      /* average_percentage = round((average_value / 16384) * 100); */

      // Display updated average
      /* lcd_set_amplitude(average_percentage); */
      lcd_set_amplitude(round(average_value));
    }
    else if(full_buffer_flag == BUFFER_B_FULL) {
      // Signify that the buffer has been handled
      full_buffer_flag = BUFFER_HANDLED;

      // Calculate average
      average_value = calculate_average(buffer_b);

      /* average_percentage = round((average_value / 16384) * 100); */

      // Display updated average
      /* lcd_set_amplitude(average_percentage); */
      lcd_set_amplitude(round(average_value));
    }
  }
}

float calculate_average(uint16_t *buffer) {
  uint16_t x;
  uint32_t total=0;

  for(x=0; x<NUM_SAMPLES; x++) {
    total += *(buffer+x);
  }

  return (1.0 * total) / NUM_SAMPLES;
}

void ADC14_IRQHandler(void) {
  static uint16_t offset = 0;
  static uint16_t *buffer = buffer_a;

  // Clear interrupt flag
  if(MAP_ADC14_getInterruptStatus() & ADC14_IFGR0_IFG0) {
    MAP_ADC14_clearInterruptFlag(ADC14_IFGR0_IFG0);
  }

  buffer[offset++] = ADC14->MEM[0] & 0xFFFF;

  if(offset >= NUM_SAMPLES) {
    // Set offset back to zero
    offset = 0;

    // Switch buffer being used
    if(buffer == buffer_a) {
      buffer = buffer_b;

      // Set flag indicating a buffer has been filled
      full_buffer_flag = BUFFER_A_FULL;
    } else {
      buffer = buffer_a;

      // Set flag indicating a buffer has been filled
      full_buffer_flag = BUFFER_B_FULL;
    }
  }
}

void T32_INT1_IRQHandler(void) {
  // Clear the interrupt flag
  Timer32_clearInterruptFlag(TIMER32_0_BASE);

  // Potential issue caused if a conversion is in progress..
  ADC_start_conversion();
}
