/*
 * jedge_systick.h
 *
 *  Created on: Jun 27, 2018
 *      Author: Joshua Edgcombe
 */

#ifndef JEDGE_SYSTICK_H_
#define JEDGE_SYSTICK_H_

#include <stdint.h>
#include "msp.h"

#define MASTER_CLK_FREQ 3000000

void systick_setup(uint32_t max_value, uint8_t interrupt_enable);
void systick_start(void);
void systick_stop(void);
void systick_blocking_wait_ms(uint32_t delay);

// Test functions
void systick_test(void);
void SysTickISR(void);
#endif /* JEDGE_SYSTICK_H_ */
