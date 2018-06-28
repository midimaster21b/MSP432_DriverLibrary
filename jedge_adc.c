/*
 * jedge_adc.c
 *
 *  Created on: Jun 28, 2018
 *      Author: Joshua Edgcombe
 */

#include "jedge_adc.h"

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

  // ADC14SSELx
  // Clear bits
  ADC14->CTL0 &= ~ADC14_CTL0_SSEL_MASK;
  // Set to master clock
  ADC14->CTL0 |= ADC14_CTL0_SSEL__MCLK << ADC14_CTL0_SSEL__MCLK;

  // ADC14DIVx
  // Defaults to no clock division. *thumbs up emoji*

  // ADC14SHP <!-- Not sure if this needs to be modified. Deals with SAMPCON signal

  /****************************
   * ADC14MCTL0 register setup
   ****************************/
  ADC14->MCTL[0] = ADC14_MCTLN_INCH_9; // Assign input channel 9 (A9) to this memory


  /****************************
   * ADC14IER0 register setup
   ****************************/
  ADC14->IER0 |= ADC14_IER0_IE0; // Enable register (necessary for interrupt flag to be set?)

  // Enable conversions
  ADC14->CTL0 &= ~ADC14_CTL0_ENC;
}

void ADC_start_conversion(void) {
  // Wait for any previous samples to finish
  while(ADC14->CTL0 & ADC14_CTL0_BUSY);

  // Set start conversion bit (software trigger)
  ADC14->CTL0 |= ADC14_CTL0_SC;
}

void ADC_stop_conversions(void) {
  // Clear enable conversion bit (NOTE: DOESN'T WORK FOR ALL CASES!!!)
  ADC14->CTL0 &= ~ADC14_CTL0_ENC;
}

uint16_t ADC_get_result(void) {
  ADC_start_conversion();

  // Wait for any previous sample to finish

  // This is the wrong way to do this...?
  while(ADC14->CTL0 & ADC14_CTL0_BUSY);
  /* while(!(ADC14->IFGR0 & ADC14_IFGR0_IFG0)); */

  return (ADC14->MEM[0] & 0xFFFF);
}
