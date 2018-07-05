#include <stdint.h>
#include "msp.h"
#include "jedge_uart.h"
#include "jedge_spi.h"
#include "jedge_systick.h"
#include "jedge_adc.h"

#include "driverlib.h"

/**
 * main.c
 */
void main(void)
{
  // stop watchdog timer
  WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

  ADC_init();
  ADC_start_conversion();

  // Enable interrupts on the microcontroller
  MAP_Interrupt_enableMaster();

  while(1);
}

void ADC14_IRQHandler(void) {
  int x = 0;

  if(MAP_ADC14_getInterruptStatus() & ADC14_IFGR0_IFG0) {
    MAP_ADC14_clearInterruptFlag(ADC14_IFGR0_IFG0);
  }

  return;
}
