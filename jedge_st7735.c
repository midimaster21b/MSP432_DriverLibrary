/*
 * jedge_st7735.c
 *
 *  Created on: Jun 27, 2018
 *      Author: Joshua Edgcombe
 */

#include <stdio.h>
#include <stdint.h>

#include "jedge_st7735.h"
#include "jedge_systick.h"
#include "jedge_spi.h"

// SPI device handle
EUSCI_B_SPI_Type *EUSCI_device = NULL;

// Configuration variables
uint8_t line_period[] = {0x01, 0x01};
uint8_t front_porch[] = {0x2C, 0x2C};
uint8_t back_porch[]  = {0x2D, 0x2D};

void st7735_test(void) {
  st7735_setup();

  // Prepare RAM for writing frame
  st7735_column_address_set(50, 90);
  st7735_row_address_set(10, 50);
  st7735_send_command(ST7735_RAMWR);

  int x, y;

  // Write green rectangle to the screen
  for(x=0; x<40; x++) {
    for(y=0; y<40; y++) {
      st7735_send_data(0xF7);
      st7735_send_data(0xE0);
    }
  }
}

/******************************
 * Initializes the LCD driver.
 ******************************/
void st7735_setup(void) {
  // Setup for GPIO pins
  st7735_setup_pins();

  // Perform hard reset
  st7735_hard_reset();

  // Set up any necessary peripherals
  st7735_setup_peripherals();

  // Configure the screen settings for use
  st7735_configure_screen();
}

void st7735_configure_screen(void) {
  // Perform a software reset to get the screen in a known state
  st7735_software_reset();

  // Wake the device
  st7735_sleep_out();

  // Configure the screen's power settings
  st7735_configure_screen_power();

  // Configure the screen's display settings
  st7735_configure_screen_display_settings();

  // Set the display to normal display mode
  st7735_normal_display_mode();

  // Turn the display on
  st7735_display_on();
}

void st7735_configure_screen_power(void) {
  // Configure general power settings
  st7735_power_control_one(ST7735_PWCTR1_AVDD_5_0V, ST7735_PWCTR1_VRHP_4_6, ST7735_PWCTR1_VRHN_4_6, ST7735_PWCTR1_MODE_AUTO);
  st7735_power_control_two(ST7735_PWCTR2_VGH25_2_4, ST7735_PWCTR2_VGLSEL_10, ST7735_PWCTR2_VGHBT_EQ_1);

  // Configure normal mode power settings
  st7735_power_control_three(ST7735_PWCTR3_SAPA_SMALL, ST7735_PWCTR3_APA_MEDIUM_LOW, 0x0000);

  // Configure idle mode power settings
  st7735_power_control_four(ST7735_PWCTR4_SAPB_SMALL, ST7735_PWCTR4_APB_MEDIUM_LOW, 0x022A);

  // Configure partial mode power settings
  st7735_power_control_five(ST7735_PWCTR5_SAPC_SMALL, ST7735_PWCTR5_APC_MEDIUM_LOW, 0x02EE);

  // Configure VCOM voltage
  st7735_vcom_voltage_control(ST7735_VMCTR1_VCOM_0_775);
}

void st7735_configure_screen_display_settings(void) {
  // Configure the frame refresh rate for normal mode
  st7735_frame_control(ST7735_FRMCTR1, line_period, front_porch, back_porch);

  // Configure the frame refresh rate for idle mode
  st7735_frame_control(ST7735_FRMCTR2, line_period, front_porch, back_porch);

  // Configure the frame refresh rate for partial mode (dot and line inversion)
  st7735_frame_control(ST7735_FRMCTR3, line_period, front_porch, back_porch);

  // Configure the display for no inversion to occur
  st7735_inversion_control(ST7735_INVCTR_NLA_MASK | ST7735_INVCTR_NLB_MASK | ST7735_INVCTR_NLC_MASK);

  // Turn display inversion off
  st7735_inversion_off();

  // Control the direction pixel data is written in memory
  st7735_memory_address_control(ST7735_MADCTL_MY_MASK | ST7735_MADCTL_MX_MASK);

  // Set the display's color mode to 16 bit
  st7735_set_color_mode(ST7735_COLMOD_IFPF_16_BIT);
}

/***********************************************
 * Set up the GPIO pins, peripheral pins should
 * be setup in peripheral drivers.
 ***********************************************/
void st7735_setup_pins(void) {

  // Set the TFT light pin to GPIO
  TFT_LIGHT_PORT->SEL0 &= ~TFT_LIGHT_MASK;
  TFT_LIGHT_PORT->SEL1 &= ~TFT_LIGHT_MASK;

  // Set the data/command line to GPIO
  TFT_DC_PORT->SEL0 &= ~TFT_DC_MASK;
  TFT_DC_PORT->SEL1 &= ~TFT_DC_MASK;

  // Set the reset line to GPIO
  TFT_RESET_PORT->SEL0 &= ~TFT_RESET_MASK;
  TFT_RESET_PORT->SEL1 &= ~TFT_RESET_MASK;

  // Set the SPI chip select line to GPIO (until SPI initialization)
  TFT_SPI_CS_PORT->SEL0 &= ~TFT_SPI_CS_MASK;
  TFT_SPI_CS_PORT->SEL1 &= ~TFT_SPI_CS_MASK;

  // Set pin directions to output
  TFT_LIGHT_PORT->DIR |= TFT_LIGHT_MASK;
  TFT_DC_PORT->DIR |= TFT_DC_MASK;
  TFT_RESET_PORT->DIR |= TFT_RESET_MASK;
  TFT_SPI_CS_PORT->DIR |= TFT_SPI_CS_MASK;

  // Set reset pin high (Note: This line is active high)
  TFT_RESET_PORT->OUT |= TFT_RESET_MASK;

  // See ST7735 manual(9.4 Serial interface pg. 33) for further use.
  TFT_DC_PORT->OUT |= TFT_DC_MASK;

  // Set TFT light to high (active low?)
  TFT_LIGHT_PORT->OUT &= ~TFT_LIGHT_MASK;
}

/***********************************************
 * Initializes the LCD driver's peripherals.
 ***********************************************/
void st7735_setup_peripherals(void) {
  st7735_setup_peripherals_spi();
}

/***********************************************
 * Initializes the LCD driver's SPI peripheral.
 ***********************************************/
void st7735_setup_peripherals_spi(void) {
  // Create SPI initialization struct
  EUSCI_SPI_config lcd_config = {
    .clock_phase = 1,
    .clock_polarity = 0,
    .msb_first = 1,
    .seven_bit_data = 0,
    .master_mode = 1,
    .eusci_mode_bit_10 = 1,
    .eusci_mode_bit_9 = 0,
    .sync_mode = 1,
    .clk_sel_bit_7 = 1,
    .clk_sel_bit_6 = 0,
    .ste_mode = 1
  };

  // Assign initial value to SPI device handle
  EUSCI_device = EUSCI_B0_SPI;

  // Initialize SPI peripheral
  SPI_init(EUSCI_device, &lcd_config);
}

/*******************************************************
 * Perform a hard reset on the LCD using the reset line.
 *******************************************************/
void st7735_hard_reset(void) {
  // Pull the SPI chip select line low
  TFT_SPI_CS_PORT->OUT &= ~TFT_SPI_CS_MASK;

  // Pull reset line high (active)
  TFT_RESET_PORT->OUT |= TFT_RESET_MASK;

  // Wait for time > 200 ms
  st7735_delay(500);

  // Pull reset line low (inactive)
  TFT_RESET_PORT->OUT &= ~TFT_RESET_MASK;

  // Wait for time > 200ms
  st7735_delay(500);

  // Pull reset line high (active)
  TFT_RESET_PORT->OUT |= TFT_RESET_MASK;

  // Wait for time > 200ms
  st7735_delay(500);
}

/*******************************************
 * Delay a specified amount of milliseconds
 *******************************************/
void st7735_delay(uint16_t milliseconds) {
  systick_blocking_wait_ms(milliseconds);
}

/*************************
 * Sends data to the LCD.
 *************************/
uint8_t st7735_send_data(uint8_t data) {
  // Set the data/command line high, signifying data is being supplied
  TFT_DC_PORT->OUT |= TFT_DC_MASK;

  return SPI_send_with_response(EUSCI_device, data);
}

/******************************
 * Sends a command to the LCD.
 ******************************/
uint8_t st7735_send_command(uint8_t cmd) {
  // Set the data/command line low, signifying a command is being supplied
  TFT_DC_PORT->OUT &= ~TFT_DC_MASK;

  return SPI_send_with_response(EUSCI_device, cmd);
}

/********************
 * Command functions
 ********************/
// Software reset
void st7735_software_reset(void) {
  st7735_send_command(ST7735_SWRESET);

  // Wait for the reset to complete
  st7735_delay(150);
}

// Sleep out
void st7735_sleep_out(void) {
  st7735_send_command(ST7735_SLPOUT);

  // Wait for the device to wake from sleep
  st7735_delay(500);
}

// INVCTR: Inversion control function
void st7735_inversion_control(uint8_t inversion_flags) {
  st7735_send_command(ST7735_INVCTR);
  st7735_send_data(inversion_flags);
}

void st7735_power_control_one(uint8_t avdd, uint8_t vrhp, uint8_t vrhn, uint8_t mode) {
  // Shift params if necessary
  if(avdd < 0x08) {
    avdd = avdd << ST7735_PWCTR1_AVDD_OFS;
  }
  if(mode < 0x04) {
    mode = mode << ST7735_PWCTR1_MODE_OFS;
  }

  st7735_send_command(ST7735_PWCTR1);
  st7735_send_data((avdd & ST7735_PWCTR1_AVDD_MASK) | (vrhp & ST7735_PWCTR1_VRHP_MASK));
  st7735_send_data(vrhn & ST7735_PWCTR1_VRHN_MASK);
  st7735_send_data((mode & ST7735_PWCTR1_MODE_MASK) | 0x04);
}

void st7735_power_control_two(uint8_t vgh25, uint8_t vglsel, uint8_t vghbt) {
  // Verify params are shifted, shift if they aren't
  if(vgh25 < 0x04) {
    vgh25 = vgh25 << ST7735_PWCTR2_VGH25_OFS;
  }
  if(vglsel < 0x04) {
    vglsel = vglsel << ST7735_PWCTR2_VGLSEL_OFS;
  }

  st7735_send_command(ST7735_PWCTR2);
  st7735_send_data((vgh25 & ST7735_PWCTR2_VGH25_MASK) | \
		   (vglsel & ST7735_PWCTR2_VGLSEL_MASK) | \
		   (vghbt & ST7735_PWCTR2_VGHBT_MASK));
}

void st7735_power_control_three(uint8_t sap_amplifier_current, uint8_t ap_amplifier_current, uint16_t booster_cycles) {
  if(sap_amplifier_current < 0x08) {
    sap_amplifier_current = sap_amplifier_current << ST7735_PWCTR3_SAPA_OFS;
  }

  uint8_t param_one = ((booster_cycles & ST7735_PWCTR3_DCA_98_MASK) >> 2) | \
    (sap_amplifier_current & ST7735_PWCTR3_SAPA_MASK) | \
    (ap_amplifier_current & ST7735_PWCTR3_APA_MASK);

  st7735_send_command(ST7735_PWCTR3);
  st7735_send_data(param_one);

  // Mask out lower byte
  st7735_send_data(booster_cycles & 0xFF);
}

void st7735_power_control_four(uint8_t sap_amplifier_current, uint8_t ap_amplifier_current, uint16_t booster_cycles) {
  if(sap_amplifier_current < 0x08) {
    sap_amplifier_current = sap_amplifier_current << ST7735_PWCTR4_SAPB_OFS;
  }

  uint8_t param_one = ((booster_cycles & ST7735_PWCTR4_DCB_98_MASK) >> 2) | \
    (sap_amplifier_current & ST7735_PWCTR4_SAPB_MASK) | \
    (ap_amplifier_current & ST7735_PWCTR4_APB_MASK);

  st7735_send_command(ST7735_PWCTR4);
  st7735_send_data(param_one);

  // Mask out lower byte
  st7735_send_data(booster_cycles & 0xFF);
}

void st7735_power_control_five(uint8_t sap_amplifier_current, uint8_t ap_amplifier_current, uint16_t booster_cycles) {
  if(sap_amplifier_current < 0x08) {
    sap_amplifier_current = sap_amplifier_current << ST7735_PWCTR5_SAPC_OFS;
  }

  uint8_t param_one = ((booster_cycles & ST7735_PWCTR5_DCC_98_MASK) >> 2) | \
    (sap_amplifier_current & ST7735_PWCTR5_SAPC_MASK) | \
    (ap_amplifier_current & ST7735_PWCTR5_APC_MASK);

  st7735_send_command(ST7735_PWCTR5);
  st7735_send_data(param_one);

  // Mask out lower byte
  st7735_send_data(booster_cycles & 0xFF);
}

void st7735_vcom_voltage_control(uint8_t vcom_voltage) {
  st7735_send_command(ST7735_VMCTR1);
  st7735_send_data(vcom_voltage);
}

void st7735_inversion_off(void) {
  st7735_send_command(ST7735_INVOFF);
}

void st7735_memory_address_control(uint8_t flags) {
  st7735_send_command(ST7735_MADCTL);
  st7735_send_data(flags);
}

// IFPF: Interface pixel format command
void st7735_set_color_mode(uint8_t interface_pixel_format) {
  st7735_send_command(ST7735_COLMOD);
  st7735_send_data(interface_pixel_format);
}

void st7735_column_address_set(uint16_t start_column, uint16_t end_column) {
  st7735_send_command(ST7735_CASET);
  st7735_send_data(start_column >> 8);
  st7735_send_data(start_column & 0xFF);
  st7735_send_data(end_column >> 8);
  st7735_send_data(end_column & 0xFF);
}

void st7735_row_address_set(uint16_t start_row, uint16_t end_row) {
  st7735_send_command(ST7735_RASET);
  st7735_send_data(start_row >> 8);
  st7735_send_data(start_row & 0xFF);
  st7735_send_data(end_row >> 8);
  st7735_send_data(end_row & 0xFF);
}

void st7735_normal_display_mode(void) {
  st7735_send_command(ST7735_NORON);

  // Give the 10 ms to change modes
  st7735_delay(10);
}

void st7735_display_on(void) {
  st7735_send_command(ST7735_DISPON);

  // Give the display 100 ms to turn on
  st7735_delay(100);
}

void st7735_set_positive_gamma(uint8_t *positive_gamma_corrections) {
  st7735_send_command(ST7735_GMCTRP1);

  uint8_t correction_num;

  for(correction_num = 0; correction_num < 16; correction_num++) {
    st7735_send_data(*(positive_gamma_corrections+correction_num));
  }
}

void st7735_set_negative_gamma(uint8_t *negative_gamma_corrections) {
  st7735_send_command(ST7735_GMCTRN1);

  uint8_t correction_num;

  for(correction_num = 0; correction_num < 16; correction_num++) {
    st7735_send_data(*(negative_gamma_corrections+correction_num));
  }
}

/******************************************************
 * Command: Frame control
 *
 * frmctr_cmd: The frame control command to be executed
 * period (RTNA): The one line period
 * front_porch (FPA): The front porch
 * back_porch (BPA): The back porch
 *
 * NOTE: This function uses a pointer for the arguments
 *       to handle the FRMCTR3 command.
 ******************************************************/
void st7735_frame_control(uint16_t frmctr_cmd, uint8_t *period, uint8_t *front_porch, uint8_t *back_porch) {
  st7735_send_command(frmctr_cmd);
  st7735_send_data((*period & ST7735_FRMCTR1_RTNA_MASK) << ST7735_FRMCTR1_RTNA_OFS);
  st7735_send_data((*front_porch & ST7735_FRMCTR1_FPA_MASK) << ST7735_FRMCTR1_FPA_OFS);
  st7735_send_data((*back_porch & ST7735_FRMCTR1_BPA_MASK) << ST7735_FRMCTR1_BPA_OFS);

  if(frmctr_cmd == ST7735_FRMCTR3) {
    st7735_send_data((*(period+1) & ST7735_FRMCTR1_RTNA_MASK) << ST7735_FRMCTR1_RTNA_OFS);
    st7735_send_data((*(front_porch+1) & ST7735_FRMCTR1_FPA_MASK) << ST7735_FRMCTR1_FPA_OFS);
    st7735_send_data((*(back_porch+1) & ST7735_FRMCTR1_BPA_MASK) << ST7735_FRMCTR1_BPA_OFS);
  }
}
