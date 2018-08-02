// --- GPIO.c ---
// --- Created on: Jul 30, 2017 ---
// --- Author: Chirag Parikh  ---

/* DriverLib Includes */
#include "driverlib.h"
#include "GPIO.h"

// --- This function sets the direction of required peripherals ---
void set_data_directions(void)
{
  // Set the directions of LEDA, LEDB, LEDC and LEDD
  GPIO_LED_A_PORT->DIR |= GPIO_LED_A_MASK;
  GPIO_LED_B_PORT->DIR |= GPIO_LED_B_MASK;
  GPIO_LED_C_PORT->DIR |= GPIO_LED_C_MASK;
  GPIO_LED_D_PORT->DIR |= GPIO_LED_D_MASK;

  // Set the direction of BUZZER (Handled in buzzer lib)

  // Turn all LEDs OFF
  GPIO_LED_A_PORT->OUT &= ~GPIO_LED_A_MASK;
  GPIO_LED_B_PORT->OUT &= ~GPIO_LED_B_MASK;
  GPIO_LED_C_PORT->OUT &= ~GPIO_LED_C_MASK;
  GPIO_LED_D_PORT->OUT &= ~GPIO_LED_D_MASK;
}

// ---- Turns ON LEDA and LEDB ---
void on1(void)
{
  // Turns ON LEDA and LEDB
  GPIO_LED_A_PORT->OUT |= GPIO_LED_A_MASK;
  GPIO_LED_B_PORT->OUT |= GPIO_LED_B_MASK;

}

// ---- Turns ON LEDC and LEDD ---
void on2(void)
{
  // Turns ON LEDC and LEDD
  GPIO_LED_C_PORT->OUT |= GPIO_LED_C_MASK;
  GPIO_LED_D_PORT->OUT |= GPIO_LED_D_MASK;

}

// ---- Turns OFF LEDA and LEDB ---
void off1(void)
{
  // Turns OFF LEDA and LEDB
  GPIO_LED_A_PORT->OUT &= ~GPIO_LED_A_MASK;
  GPIO_LED_B_PORT->OUT &= ~GPIO_LED_B_MASK;
}

// ---- Turns OFF LEDC and LEDD ---
void off2(void)
{
  // Turns OFF LEDC and LEDD
  GPIO_LED_C_PORT->OUT &= ~GPIO_LED_C_MASK;
  GPIO_LED_D_PORT->OUT &= ~GPIO_LED_D_MASK;
}
