/*
 * jedge_pwm.h
 *
 *  Created on: July 28, 2018
 *      Author: Joshua Edgcombe
 */

#include <stdint.h>
#include "msp.h"

#ifndef JEDGE_PWM_H_
#define JEDGE_PWM_H_

// General motor definitions
#define JEDGE_PWM_BUZZER_INIT_DUTY_CYCLE (3000)

// 500 Hz @ 3 MHz clock (6000)
// 1 kHz @ 3 MHz clock (12000)
#define JEDGE_PWM_BUZZER_TIMER_PERIOD    (6000)
#define JEDGE_PWM_BUZZER_TIMER           TIMER_A0

// Buzzer definitions (P2.7, TA0.4)
#define JEDGE_PWM_BUZZER_PORT   P2
#define JEDGE_PWM_BUZZER_PIN    7
#define JEDGE_PWM_BUZZER_MASK   1 << JEDGE_PWM_BUZZER_PIN
#define JEDGE_PWM_BUZZER_CCR    4

void jedge_pwm_init(void);
void jedge_pwm_timer_init(Timer_A_Type *motor_timer);
void jedge_pwm_start(Timer_A_Type *motor_timer);
uint16_t jedge_pwm_calculate_duty_cycle(float receiver_duty_cycle);
void jedge_pwm_set_duty_cycle(uint16_t duty_cycle);
void jedge_pwm_set_frequency(uint16_t period, uint16_t duty_cycle);

#endif /* JEDGE_PWM_H_ */
