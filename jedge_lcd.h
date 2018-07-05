/*
 * jedge_lcd.h
 *
 *  Created on: Jun 28, 2018
 *      Author: Joshua Edgcombe
 */

#include <stdint.h>

#ifndef JEDGE_LCD_H_
#define JEDGE_LCD_H_

// Application specific functions
void lcd_init(void);
void lcd_test(void);
void lcd_set_amplitude(uint8_t amplitude);
void lcd_set_amplitude_multi(uint8_t *amplitude, uint8_t num_bands);

// General LCD functions
void lcd_prepare_write_area(uint8_t start_col, uint8_t start_row, uint8_t end_col, uint8_t end_row);
void lcd_clear_screen(uint16_t color);
void lcd_draw_rect(uint8_t start_col, uint8_t start_row, uint8_t end_col, uint8_t end_row, uint16_t color);
uint16_t lcd_get_color(uint8_t red, uint8_t green, uint8_t blue);

#endif /* JEDGE_LCD_H_ */
