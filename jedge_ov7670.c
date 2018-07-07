/*
 * jedge_ov7670.c
 *
 *  Created on: July 6, 2018
 *      Author: Joshua Edgcombe
 */

#include "msp.h"
#include "jedge_sccb.h"
#include "jedge_ov7670.h"

EUSCI_B_Type *ov7670_eusci_device;

void ov7670_test(void) {
  /* EUSCI_B_Type *test_dev = OV7670_EUSCI_INTERFACE; */
  /* ov7670_init(test_dev); */

  ov7670_init_clock_signal();
}

void ov7670_init(EUSCI_B_Type *device) {
  // Assign supplied device to driver device
  ov7670_eusci_device = device;

  // Setup pins (Data)
  OV7670_DATA_PORT->DIR &= ~OV7670_DATA_MASK;

  // Setup pins (Peripherals) (Pixel clock)
  ov7670_init_clock_signal();

  // Initialize SCCB communication interface
  sccb_init(ov7670_eusci_device);

  // Setup interrupts (HS, VS, & Pixel Clk?)
}

void ov7670_init_clock_signal(void) {
  Timer_A_Type *clk = OV7670_CLK_TIMER;

  // Disable timer if running
  clk->CTL &= ~TIMER_A_CTL_MC_MASK;

  // Reset this timer A peripheral
  clk->CTL |= TIMER_A_CTL_CLR;

  // Set to SMCLK
  clk->CTL &= ~TIMER_A_CTL_SSEL_MASK;
  clk->CTL |= TIMER_A_CTL_SSEL__SMCLK;

  // Set to toggle output
  clk->CCTL[0] &= ~TIMER_A_CCTLN_OUTMOD_MASK;
  clk->CCTL[0] |= TIMER_A_CCTLN_OUTMOD_4;

  // Divide clock signal by 2
  // 2 -> 4 MHz
  // 1 -> 6 MHz
  clk->CCR[0] = 1;

  // Configure clock output pin
  OV7670_CLK_PORT->DIR |= OV7670_CLK_MASK;

  OV7670_CLK_PORT->SEL0 |= OV7670_CLK_MASK;
  OV7670_CLK_PORT->SEL1 &= ~OV7670_CLK_MASK;

  // Set to up mode (Enable timer)
  clk->CTL |= TIMER_A_CTL_MC__UP;
}

// TODO: Write GPIO interrupt handler
// QUESTION: Can a small window be read? Ex. (col: 50 - 150, row 50 - 150)
