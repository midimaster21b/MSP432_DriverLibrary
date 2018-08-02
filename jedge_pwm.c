/*
 * jedge_pwm.h
 *
 *  Created on: July 28, 2018
 *      Author: Joshua Edgcombe
 */

#include <stdint.h>
#include <math.h>
#include "jedge_pwm.h"
#include "msp.h"

void jedge_pwm_init(void) {
  //////////////////////////
  // Configure timers
  //////////////////////////
  // Clear any previous timer configuration
  /* JEDGE_PWM_MOTOR_TIMER->CTL |= TIMER_A_CTL_CLR; */

  // Use SMClk
  JEDGE_PWM_MOTOR_TIMER->CTL |= TIMER_A_CTL_SSEL__SMCLK;

  // Set to output mode 7 (reset/set)
  // See Figure 17-12 in MSP432P4xx Family Rev. C datasheet for more info.
  JEDGE_PWM_MOTOR_TIMER->CCTL[JEDGE_PWM_LEFT_MOTOR_CCR]  = TIMER_A_CCTLN_OUTMOD_7;
  JEDGE_PWM_MOTOR_TIMER->CCTL[JEDGE_PWM_RIGHT_MOTOR_CCR] = TIMER_A_CCTLN_OUTMOD_7;

  // Set output period of the PWM
  JEDGE_PWM_MOTOR_TIMER->CCR[0] = JEDGE_PWM_MOTOR_TIMER_PERIOD;

  // Set initial duty cycle of PWM
  JEDGE_PWM_MOTOR_TIMER->CCR[JEDGE_PWM_LEFT_MOTOR_CCR]  = JEDGE_PWM_MOTOR_INIT_DUTY_CYCLE;
  JEDGE_PWM_MOTOR_TIMER->CCR[JEDGE_PWM_RIGHT_MOTOR_CCR] = JEDGE_PWM_MOTOR_INIT_DUTY_CYCLE;

  // Divide the clock signal by 8 (down to 3 MHz)
  JEDGE_PWM_MOTOR_TIMER->EX0 = TIMER_A_EX0_IDEX__8;

  ////////////////////////////////////////////////////////////////
  // Configure pins (Output direction, PWM peripheral controlled)
  ////////////////////////////////////////////////////////////////
  JEDGE_PWM_LEFT_MOTOR_PORT->DIR  |= JEDGE_PWM_LEFT_MOTOR_MASK;
  JEDGE_PWM_LEFT_MOTOR_PORT->SEL0 |= JEDGE_PWM_LEFT_MOTOR_MASK;
  JEDGE_PWM_LEFT_MOTOR_PORT->SEL1 &= ~JEDGE_PWM_LEFT_MOTOR_MASK;

  JEDGE_PWM_RIGHT_MOTOR_PORT->DIR  |= JEDGE_PWM_RIGHT_MOTOR_MASK;
  JEDGE_PWM_RIGHT_MOTOR_PORT->SEL0 |= JEDGE_PWM_RIGHT_MOTOR_MASK;
  JEDGE_PWM_RIGHT_MOTOR_PORT->SEL1 &= ~JEDGE_PWM_RIGHT_MOTOR_MASK;
}

void jedge_pwm_start(Timer_A_Type *motor_timer) {
  // Set to up mode (need control over signal period)
  motor_timer->CTL |= TIMER_A_CTL_MC__UP;
}

uint16_t jedge_pwm_calculate_duty_cycle(float receiver_duty_cycle) {
  // TODO: Determine the input to output relationship between duty cycle in to duty cycle out
  return floor(receiver_duty_cycle * JEDGE_PWM_MOTOR_TIMER_PERIOD);
}

void jedge_pwm_set_duty_cycle(uint16_t duty_cycle) {
  // Set duty cycle for appropriate timer
  JEDGE_PWM_MOTOR_TIMER->CCR[JEDGE_PWM_LEFT_MOTOR_CCR] = duty_cycle;
}

void jedge_pwm_set_period(uint16_t period) {
  // Set period for appropriate timer
  JEDGE_PWM_MOTOR_TIMER->CCR[0] = period;
}
