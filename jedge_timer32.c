/*
 * jedge_timer32.c
 *
 *  Created on: July 5, 2018
 *      Author: Joshua Edgcombe
 */

#include "driverlib.h"

void init_sample_timer(void) {
  MAP_Timer32_initModule(TIMER32_0_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT, TIMER32_PERIODIC_MODE);
  MAP_Timer32_setCount(TIMER32_0_BASE, 2400);
  MAP_Timer32_enableInterrupt(TIMER32_0_BASE);
  MAP_Interrupt_enableInterrupt(INT_T32_INT1);
}

void start_sample_timer(void) {
  MAP_Timer32_startTimer(TIMER32_0_BASE, false);
}
