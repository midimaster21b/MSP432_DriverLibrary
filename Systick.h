// --- Systick.h ---
// --- Created on: Jul 30, 2017 ---
// --- Author: Chirag Parikh  ---

#ifndef SYSTICK_H_
#define SYSTICK_H_

// 1 us @ 3 MHz happens every 3 cycles
#define SYSTICK_MICROSECOND_MULTIPLIER 3

void SysTick_Init(void);
void SysTick_delay(uint16_t delay);

#endif /* SYSTICK_H_ */
