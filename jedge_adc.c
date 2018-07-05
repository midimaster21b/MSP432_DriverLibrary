/*
 * jedge_adc.c
 *
 *  Created on: Jun 28, 2018
 *      Author: Joshua Edgcombe
 */

#include "driverlib.h"
#include "jedge_adc.h"

/**
 * @brief Initialize the ADC peripheral and pins.
 *
 * Initialize the ADC peripheral and pins for analog pin 9 on ADC channel zero and ADC storage zero.
 * The ADC is set to sample using the master clock currently. An interrupt is enabled for completion of
 * sampling for ADC channel 0.
 */
void ADC_init(void) {
  // Handle PIN muxing to analog line SEL0 = SEL1 = 1
  ADC_PORT->SEL0 |= ADC_MASK;
  ADC_PORT->SEL1 |= ADC_MASK;

  /************************
   * Ctrl 0 register setup
   ************************/
  // Power ADC14 core (Necessary?)(Correct order?)
  ADC14->CTL0 |= ADC14_CTL0_ON;

  // Disable conversions
  ADC14->CTL0 &= ~ADC14_CTL0_ENC;

  // Enable multiple sample conversions (continuous sampling)
  /* ADC14->CTL0 |= ADC14_CTL0_MSC; */

  // ADC14SHTXX (Setting sample and hold time for register sets, not necessary)

  // ADC14CONSEQx (Conversion mode, single channel, single conversion by default)
  /* ADC14_CTL0_CONSEQ_0; // Single channel, single conversion */
  /* ADC14_CTL0_CONSEQ_2; // Single channel, repeat conversion */

  // ADC14SSELx Clock select
  // Clear bits
  ADC14->CTL0 &= ~ADC14_CTL0_SSEL_MASK;
  // Set to master clock
  ADC14->CTL0 |= ADC14_CTL0_SSEL__MCLK;

  // Set to pulse mode
  ADC14->CTL0 |= ADC14_CTL0_SHP;

  // ADC14DIVx
  // Defaults to no clock division. *thumbs up emoji*

  /****************************
   * ADC14MCTL0 register setup
   ****************************/
  ADC14->MCTL[0] = ADC14_MCTLN_INCH_9; // Assign input channel 9 (A9) to this memory

  /****************************
   * ADC14IER0 register setup
   ****************************/
  ADC14->IER0 |= ADC14_IER0_IE0; // Interrupt enable register

  // Enable the interrupt to be triggered
  MAP_Interrupt_enableInterrupt(INT_ADC14);

  // Enable conversions
  ADC14->CTL0 |= ADC14_CTL0_ENC;
}

/**
 * @brief Start ADC conversion(s) depending on configuration
 *
 * This is a blocking call that waits for the ADC14_CTL0_BUSY flag to be cleared before starting the conversion(s).
 */
void ADC_start_conversion(void) {
  // Wait for any previous samples to finish
  while(ADC14->CTL0 & ADC14_CTL0_BUSY);

  // Set start conversion bit (software trigger)
  ADC14->CTL0 |= ADC14_CTL0_SC;
}

/**
 * @brief Stops ADC conversions
 *
 * This function will stop any currently running ADC conversions and the values stored in the
 * ADC memory corresponding to ADC conversions running at the time of stopping the conversions
 * will contain invalid results.
 */
void ADC_stop_conversions(void) {
  // Clear enable conversion bit (NOTE: DOESN'T WORK FOR ALL CASES!!!)
  ADC14->CTL0 &= ~ADC14_CTL0_ENC;
}

/**
 * @brief Perform an ADC conversion and return the resulting value as a 16 bit value.
 *
 * This is a blocking call that waits for the ADC14_CTL0_BUSY flag to be cleared before starting the first conversion.
 * The function then waits for the ADC14_CTL0_BUSY flag to be cleared again and returns the result stored in ADC memory.
 */
uint16_t ADC_get_result(void) {
  ADC_start_conversion();

  // This is the wrong way to do this...?
  while(ADC14->CTL0 & ADC14_CTL0_BUSY);
  /* while(!(ADC14->IFGR0 & ADC14_IFGR0_IFG0)); */

  return (ADC14->MEM[0] & 0xFFFF);
}
