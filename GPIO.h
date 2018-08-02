/// --- GPIO.h ---
// --- Created on: Jul 30, 2017 ---
// --- Author: Chirag Parikh  ---

#ifndef GPIO_H_
#define GPIO_H_

#define GPIO_LED_A_PORT P4
#define GPIO_LED_A_PIN  5
#define GPIO_LED_A_MASK 1 << GPIO_LED_A_PIN

#define GPIO_LED_B_PORT P4
#define GPIO_LED_B_PIN  7
#define GPIO_LED_B_MASK 1 << GPIO_LED_B_PIN

#define GPIO_LED_C_PORT P5
#define GPIO_LED_C_PIN  4
#define GPIO_LED_C_MASK 1 << GPIO_LED_C_PIN

/* #define GPIO_LED_D_PORT P5 */
/* #define GPIO_LED_D_PIN  5 */
#define GPIO_LED_D_PORT P6
#define GPIO_LED_D_PIN  7
#define GPIO_LED_D_MASK 1 << GPIO_LED_D_PIN

void set_data_directions(void);
void on1(void);
void on2(void);
void off1(void);
void off2(void);

#endif /* GPIO_H_ */
