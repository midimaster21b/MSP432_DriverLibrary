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
#define JEDGE_PWM_MOTOR_INIT_DUTY_CYCLE (1500)
#define JEDGE_PWM_MOTOR_TIMER_PERIOD    (15000)
#define JEDGE_PWM_MOTOR_TIMER           TIMER_A0

// Left motor definitions (P2.4, TA0.1)
#define JEDGE_PWM_LEFT_MOTOR_PORT   P2
#define JEDGE_PWM_LEFT_MOTOR_PIN    4
#define JEDGE_PWM_LEFT_MOTOR_MASK   1 << JEDGE_PWM_LEFT_MOTOR_PIN
#define JEDGE_PWM_LEFT_MOTOR_CCR    1

// Right motor definitions (P2.5, TA0.2)
#define JEDGE_PWM_RIGHT_MOTOR_PORT  P2
#define JEDGE_PWM_RIGHT_MOTOR_PIN   5
#define JEDGE_PWM_RIGHT_MOTOR_MASK  1 << JEDGE_PWM_RIGHT_MOTOR_PIN
#define JEDGE_PWM_RIGHT_MOTOR_CCR   2

void jedge_pwm_init(void);
void jedge_pwm_timer_init(Timer_A_Type *motor_timer);
void jedge_pwm_start(Timer_A_Type *motor_timer);
uint16_t jedge_pwm_calculate_duty_cycle(float receiver_duty_cycle);
void jedge_pwm_set_duty_cycle(uint16_t duty_cycle);

#endif /* JEDGE_PWM_H_ */
