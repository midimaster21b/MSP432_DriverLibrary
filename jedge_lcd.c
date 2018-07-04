/*
 * jedge_lcd.c
 *
 *  Created on: Jun 28, 2018
 *      Author: Joshua Edgcombe
 */

#include <stdint.h>
#include "jedge_lcd.h"
#include "jedge_st7735.h"

uint8_t prev_amplitude = 0;
uint8_t num_cols = 128;
uint8_t num_rows = 160;

uint16_t background_color;
uint16_t foreground_color;

void lcd_test(void) {
  st7735_setup();

  background_color = lcd_get_color(0x00, 0x00, 0x00);
  foreground_color = lcd_get_color(0x0F, 0x0F, 0x0F);

  lcd_clear_screen(background_color);
  /* lcd_draw_rect(15, 50, 100, 100, color); */

  int x;
  // Climb higher
  for(x=0; x < 50; x++) {
    lcd_set_amplitude(x<<1);
    st7735_delay(200);
  }

  // Reduce height
  for(x=80; x > 0; x--) {
    lcd_set_amplitude(x);
    st7735_delay(200);
  }
}

void lcd_set_amplitude(uint8_t amplitude) {

  uint8_t row_start;
  uint8_t row_stop;
  uint16_t color;

  if(prev_amplitude > amplitude) {
    row_start = amplitude;
    row_stop = prev_amplitude;

    color = background_color;
  }
  else if(prev_amplitude < amplitude) {
    row_start = prev_amplitude;
    row_stop = amplitude;

    color = foreground_color;
  }
  else {
    // If they are equal, nothing needs to be drawn
    return;
  }

  // Update previous amplitude
  prev_amplitude = amplitude;

  // Draw the appropiate rectangle (delta)
  lcd_draw_rect(0, row_start, num_cols, row_stop, color);
}

void lcd_prepare_write_area(uint8_t start_col, uint8_t start_row, uint8_t end_col, uint8_t end_row) {
  // Prepare RAM for writing frame
  st7735_column_address_set(start_col, end_col);
  st7735_row_address_set(start_row, end_row);
  st7735_send_command(ST7735_RAMWR);
}

void lcd_clear_screen(uint16_t color) {
  lcd_draw_rect(0, 0, num_cols, num_rows, color);
}

void lcd_draw_rect(uint8_t start_col, uint8_t start_row, uint8_t end_col, uint8_t end_row, uint16_t color) {
  // Prepare LCD memory for writing pixel data
  lcd_prepare_write_area(start_col, start_row, end_col, end_row);

  int x, y;

  // TODO: Verify loop iteration
  for(x=start_row; x<end_row; x++) {
    for(y=start_col; y<=end_col; y++) {
      st7735_send_data(color>>8);
      st7735_send_data(color & 0x00FF);
    }
  }
}

/****************************************************************************
 * lcd_get_color
 *
 * Description: get a 16-bit packed representation of the color specified
 * using the RGB values supplied.
 ****************************************************************************/
uint16_t lcd_get_color(uint8_t red, uint8_t green, uint8_t blue) {
  // Mask out appropariate bits
  red &= 0x1F;
  green &= 0x3F;
  blue &= 0x1F;

  // Pack the bits
  return (0x8080 | (red << 12) | ((green & 0x38) << 9) | blue);
}
