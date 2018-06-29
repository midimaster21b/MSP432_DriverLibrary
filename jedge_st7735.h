/*
 * jedge_st7735.h
 *
 *  Created on: Jun 27, 2018
 *      Author: Joshua Edgcombe
 */

#ifndef JEDGE_ST7735_H_
#define JEDGE_ST7735_H_

#include "msp.h"
#include "jedge_spi.h"

/*******************
 * Pin declarations
 *******************/
#define TFT_LIGHT_PORT P6
#define TFT_LIGHT_PIN  6
#define TFT_LIGHT_MASK 1 << TFT_LIGHT_PIN

#define TFT_DC_PORT P5
#define TFT_DC_PIN  2
#define TFT_DC_MASK 1 << TFT_DC_PIN

#define TFT_RESET_PORT P3
#define TFT_RESET_PIN  6
#define TFT_RESET_MASK 1 << TFT_RESET_PIN

#define TFT_SPI_MOSI_PORT P1
#define TFT_SPI_MOSI_PIN  6
#define TFT_SPI_MOSI_MASK 1 << TFT_SPI_MOSI_PIN

#define TFT_SPI_CS_PORT P5
#define TFT_SPI_CS_PIN  0
#define TFT_SPI_CS_MASK 1 << TFT_SPI_CS_PIN

#define TFT_SPI_CLK_PORT P1
#define TFT_SPI_CLK_PIN  5
#define TFT_SPI_CLK_MASK 1 << TFT_SPI_CLK_PIN

#define TFT_SPI_MISO_PORT P1
#define TFT_SPI_MISO_PIN  7
#define TFT_SPI_MISO_MASK 1 << TFT_SPI_MISO_PIN

/*************************************************
 * Command declarations: System function commands
 *************************************************/
// System function commands
#define ST7735_NOP        0x00 // No operation
#define ST7735_SWRESET    0x01 // Software reset
#define ST7735_RDDID      0x04 // Read display ID
#define ST7735_RDDST      0x09 // Read display status
#define ST7735_RDDPM      0x0A // Read display power
#define ST7735_RDD_MADCTL 0x0B // Read display
#define ST7735_RDD_COLMOD 0x0C // Read display pixel
#define ST7735_RDDIM      0x0D // Read display image
#define ST7735_RDDSM      0x0E // Read display signal
#define ST7735_SLPIN      0x10 // Sleep in & booster off?
#define ST7735_SLPOUT     0x11 // Sleep out & booster on?
#define ST7735_PTLON      0x12 // Partial mode on
#define ST7735_NORON      0x13 // Partial mode off (Normal)
#define ST7735_INVOFF     0x20 // Display inverion off
#define ST7735_INVON      0x21 // Display inverion on
#define ST7735_GAMSET     0x26 // Gamm curve select
#define ST7735_DISPOFF    0x28 // Display off
#define ST7735_DISPON     0x29 // Display on
#define ST7735_CASET      0x2A // Column address set
#define ST7735_RASET      0x2B // Row address set
#define ST7735_RAMWR      0x2C // Memory write
#define ST7735_RGBSET     0x2D // LUT for 4k, 65k, 262k color
#define ST7735_RAMRD      0x2E // Memory read
#define ST7735_PTLAR      0x30 // Partial start/end address set
#define ST7735_TEOFF      0x34 // Tearing effect line off
#define ST7735_TEON       0x35 // Tearing effect mode set & on
#define ST7735_MADCTL     0x36 // Memory data access control
#define ST7735_IDMOFF     0x38 // Idle mode off
#define ST7735_IDMON      0x39 // Idle mode on
#define ST7735_COLMOD     0x3A // Interface pixel format
#define ST7735_RDID1      0xDA // Read ID1
#define ST7735_RDID2      0xDB // Read ID2
#define ST7735_RDID3      0xDC // Read ID3

// System function argument definitions
// NOP: No operation (No params/args) (pg. 82)
// SWRESET: Software reset (No params/args) (pg. 83)

////////////////////////////////////////
// RDDID (pg. 84)
////////////////////////////////////////
// LCD module's manufacturer ID
#define ST7735_RDDID_ID1_MASK 0xFF

// LCD module module/driver version ID
#define ST7735_RDDID_ID2_MASK 0x7F

// LCD module module/driver ID
#define ST7735_RDDID_ID3_MASK 0xFF

////////////////////////////////////////
// RDDST: Read display status (pg. 85)
////////////////////////////////////////
// 1st parameter (none/dummy)
// 2nd parameter
// Booster voltage status
#define ST7735_RDDST_BSTON_OFS  7
#define ST7735_RDDST_BSTON_MASK (1 << ST7735_RDDST_BSTON_OFS)

// Row address order
#define ST7735_RDDST_MY_OFS  6
#define ST7735_RDDST_MY_MASK (1 << ST7735_RDDST_MY_OFS)

// Column address order
#define ST7735_RDDST_MX_OFS  5
#define ST7735_RDDST_MX_MASK (1 << ST7735_RDDST_MX_OFS)

// Row/Column exchange
#define ST7735_RDDST_MV_OFS  4
#define ST7735_RDDST_MV_MASK (1 << ST7735_RDDST_MV_OFS)

// Scan address order
#define ST7735_RDDST_ML_OFS  3
#define ST7735_RDDST_ML_MASK (1 << ST7735_RDDST_ML_OFS)

// RGB/BGR order
#define ST7735_RDDST_RGB_OFS  2
#define ST7735_RDDST_RGB_MASK (1 << ST7735_RDDST_RGB_OFS)

// Horizontal order
#define ST7735_RDDST_MH_OFS  1
#define ST7735_RDDST_MH_MASK (1 << ST7735_RDDST_MH_OFS)

// 3rd paramter
// Interface color pixel format definition (InterFace Pixel Format)
#define ST7735_RDDST_IFPF_OFS  4
#define ST7735_RDDST_IFPF_MASK (7 << ST7735_RDDST_IFPF_OFS)
#define ST7735_RDDST_IFPF_12_BIT (3 << ST7735_RDDST_IFPF_OFS)
#define ST7735_RDDST_IFPF_16_BIT (5 << ST7735_RDDST_IFPF_OFS)
#define ST7735_RDDST_IFPF_18_BIT (6 << ST7735_RDDST_IFPF_OFS)

// Idle mode on/off
#define ST7735_RDDST_IDMON_OFS  3
#define ST7735_RDDST_IDMON_MASK (1 << ST7735_RDDST_IDMON_OFS)

// Partial mode on/off
#define ST7735_RDDST_PTLON_OFS  2
#define ST7735_RDDST_PTLON_MASK (1 << ST7735_RDDST_PTLON_OFS)

// Sleep in/out
#define ST7735_RDDST_SLPOUT_OFS  1
#define ST7735_RDDST_SLPOUT_MASK (1 << ST7735_RDDST_SLPOUT_OFS)

// Normal mode on/off
#define ST7735_RDDST_NORON_OFS  0
#define ST7735_RDDST_NORON_MASK (1 << ST7735_RDDST_NORON_OFS)

// 4th Parameter
// Vertical scrolling status
#define ST7735_RDDST_ST15_OFS  7
#define ST7735_RDDST_ST15_MASK (1 << ST7735_RDDST_ST15_OFS)

// Vertical scrolling status
#define ST7735_RDDST_INVON_OFS  5
#define ST7735_RDDST_INVON_MASK (1 << ST7735_RDDST_INVON_OFS)

// Display on/off
#define ST7735_RDDST_DISON_OFS  2
#define ST7735_RDDST_DISON_MASK (1 << ST7735_RDDST_DISON_OFS)

// Tearing effect line on/off
#define ST7735_RDDST_TEON_OFS  1
#define ST7735_RDDST_TEON_MASK (1 << ST7735_RDDST_TEON_OFS)

// Gamma curve selection (bit 2)
#define ST7735_RDDST_GCSEL2_OFS  0
#define ST7735_RDDST_GCSEL2_MASK (1 << ST7735_RDDST_GCSEL2_OFS)

// 5th Paramter
// Gamma curve selection (bit 1)
#define ST7735_RDDST_GCSEL1_OFS  7
#define ST7735_RDDST_GCSEL1_MASK (1 << ST7735_RDDST_GCSEL1_OFS)

// Gamma curve selection (bit 0)
#define ST7735_RDDST_GCSEL0_OFS  6
#define ST7735_RDDST_GCSEL0_MASK (1 << ST7735_RDDST_GCSEL0_OFS)

// Tearing effect line mode
#define ST7735_RDDST_TEM_OFS  5
#define ST7735_RDDST_TEM_MASK (1 << ST7735_RDDST_TEM_OFS)

///////////////////////////////////////////
// RDDPM: Read display power mode (pg. 87)
///////////////////////////////////////////
// 1st parameter (none/dummy)
// 2nd parameter
// Booster voltage status
#define ST7735_RDDPM_BSTON_OFS  7
#define ST7735_RDDPM_BSTON_MASK (1 << ST7735_RDDPM_BSTON_OFS)

// Idle mode on/off
#define ST7735_RDDPM_IDMON_OFS  6
#define ST7735_RDDPM_IDMON_MASK (1 << ST7735_RDDPM_IDMON_OFS)

// Partial mode on/off
#define ST7735_RDDPM_PTLON_OFS  5
#define ST7735_RDDPM_PTLON_MASK (1 << ST7735_RDDPM_PTLON_OFS)

// Sleep in/out
#define ST7735_RDDPM_SLPON_OFS  4
#define ST7735_RDDPM_SLPON_MASK (1 << ST7735_RDDPM_SLPON_OFS)

// Display normal mode on/off
#define ST7735_RDDPM_NORON_OFS  3
#define ST7735_RDDPM_NORON_MASK (1 << ST7735_RDDPM_NORON_OFS)

// Display on/off
#define ST7735_RDDPM_DISON_OFS  2
#define ST7735_RDDPM_DISON_MASK (1 << ST7735_RDDPM_DISON_OFS)

///////////////////////////////////////////
// RDDMADCTL: Read display MADCTL (pg. 88)
///////////////////////////////////////////
// 1st parameter (none/dummy)
// 2nd parameter
// Column address order
#define ST7735_RDDMADCTL_MX_OFS  7
#define ST7735_RDDMADCTL_MX_MASK (1 << ST7735_RDDMADCTL_MX_OFS)

// Row address order
#define ST7735_RDDMADCTL_MY_OFS  6
#define ST7735_RDDMADCTL_MY_MASK (1 << ST7735_RDDMADCTL_MY_OFS)

// Row/column order
#define ST7735_RDDMADCTL_MV_OFS  5
#define ST7735_RDDMADCTL_MV_MASK (1 << ST7735_RDDMADCTL_MV_OFS)

// Vertical refresh order
#define ST7735_RDDMADCTL_ML_OFS  4
#define ST7735_RDDMADCTL_ML_MASK (1 << ST7735_RDDMADCTL_ML_OFS)

// RGB/BGR order
#define ST7735_RDDMADCTL_RGB_OFS  3
#define ST7735_RDDMADCTL_RGB_MASK (1 << ST7735_RDDMADCTL_RGB_OFS)

// Horizontal refresh order
#define ST7735_RDDMADCTL_MH_OFS  2
#define ST7735_RDDMADCTL_MH_MASK (1 << ST7735_RDDMADCTL_MH_OFS)

/////////////////////////////////////////////////
// RDDCOLMOD: Read display pixel format (pg. 89)
/////////////////////////////////////////////////
// 1st parameter (none/dummy)
// 2nd parameter
// Interface pixel format
#define ST7735_RDDCOLMOD_IFPF_OFS    0
#define ST7735_RDDCOLMOD_IFPF_MASK   (7 << ST7735_RDDCOLMOD_IFPF_OFS)
#define ST7735_RDDCOLMOD_IFPF_12_BIT (3 << ST7735_RDDCOLMOD_IFPF_OFS)
#define ST7735_RDDCOLMOD_IFPF_16_BIT (5 << ST7735_RDDCOLMOD_IFPF_OFS)
#define ST7735_RDDCOLMOD_IFPF_18_BIT (6 << ST7735_RDDCOLMOD_IFPF_OFS)
#define ST7735_RDDCOLMOD_IFPF_NA     (7 << ST7735_RDDCOLMOD_IFPF_OFS)

///////////////////////////////////////////
// RDDIM: Read display image mode (pg. 90)
///////////////////////////////////////////
// 1st parameter (none/dummy)
// 2nd parameter
// Inversion on/off
#define ST7735_RDDIM_INVON_OFS  5
#define ST7735_RDDIM_INVON_MASK (1 << ST7735_RDDIM_INVON_OFS)

// Gamma curve selection
#define ST7735_RDDIM_GCS_OFS  0
#define ST7735_RDDIM_GCS_MASK (7 << ST7735_RDDIM_GCS_OFS)
#define ST7735_RDDIM_GCS_GC0 (0 << ST7735_RDDIM_GCS_OFS)
#define ST7735_RDDIM_GCS_GC1 (1 << ST7735_RDDIM_GCS_OFS)
#define ST7735_RDDIM_GCS_GC2 (2 << ST7735_RDDIM_GCS_OFS)
#define ST7735_RDDIM_GCS_GC3 (3 << ST7735_RDDIM_GCS_OFS)

////////////////////////////////////////////
// RDDSM: Read display signal mode (pg. 91)
////////////////////////////////////////////
// 1st parameter (none/dummy)
// 2nd parameter
// Tearing effect line on/off
#define ST7735_RDDSM_TEON_OFS  7
#define ST7735_RDDSM_TEON_MASK (1 << ST7735_RDDSM_TEON_OFS)

// Tearing effect line mode
#define ST7735_RDDSM_TEM_OFS  6
#define ST7735_RDDSM_TEM_MASK (1 << ST7735_RDDSM_TEM_OFS)

////////////////////////////////////////////////////////////
// SLPIN: Sleep in (No params/args) (pg. 93)
// SLPOUT: Sleep out (No params/args) (pg. 94)
// PTLON: Partial display mode on (No params/args) (pg. 95)
// NORON: Normal display mode on (No params/args) (pg. 96)
// INVOFF: Display inversion off (No params/args) (pg. 97)
// INVON: Display inversion on (No params/args) (pg. 98)
////////////////////////////////////////////////////////////

///////////////////////////////////////////
// GAMSET: Gamma set (pg. 99)
///////////////////////////////////////////
// 1st parameter
// Gamma curve selection (GS=0, GS=1?)
#define ST7735_GAMSET_GC_OFS  0
#define ST7735_GAMSET_GC_MASK (0x0F << ST7735_RDDIM_INVON_OFS)
#define ST7735_GAMSET_GC0     (0x01 << ST7735_RDDIM_INVON_OFS)
#define ST7735_GAMSET_GC1     (0x02 << ST7735_RDDIM_INVON_OFS)
#define ST7735_GAMSET_GC2     (0x04 << ST7735_RDDIM_INVON_OFS)
#define ST7735_GAMSET_GC3     (0x08 << ST7735_RDDIM_INVON_OFS)

////////////////////////////////////////////////////////////////////////////////
// DISPOFF: Display off (No params/args) (pg. 100)
// DISPON: Display on (No params/args) (pg. 101)
// CASET: Column address set (Param/arg def's not necessary) (pg. 102)
// RASET: Row address set (Param/arg def's not necessary) (pg. 104)
// RAMWR: Memory write (Param/arg def's not necessary) (pg. 106)
// RGBSET: Color setting for 4k, 65k, and 262k (Param/arg def's not necessary) (pg. 107)
// RAMRD: Memory read (Param/arg def's not necessary) (pg. 108)
// PTLAR: Partial area (Param/arg def's not necessary) (pg. 109)
// TEOFF: Tearing effect line off (No params/args) (pg. 111)
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////
// TEON: Tearing effect line on (pg. 112)
///////////////////////////////////////////
// 1st parameter
// When TEM ='0': The Tearing Effect output line consists of V-Blanking information only
#define ST7735_TEON_TEM_OFS  0
#define ST7735_TEON_TEM_MASK  (1 << ST7735_TEON_TEM_OFS)

////////////////////////////////////////////////
// MADCTL: Memory data access control (pg. 113)
////////////////////////////////////////////////
// 1st parameter
// Row address order
#define ST7735_MADCTL_MY_OFS  7
#define ST7735_MADCTL_MY_MASK (1 << ST7735_MADCTL_MY_OFS)

// Column address order
#define ST7735_MADCTL_MX_OFS  6
#define ST7735_MADCTL_MX_MASK (1 << ST7735_MADCTL_MX_OFS)

// Row/Column exchange
#define ST7735_MADCTL_MV_OFS  5
#define ST7735_MADCTL_MV_MASK (1 << ST7735_MADCTL_MV_OFS)

// Vertical refresh order
#define ST7735_MADCTL_ML_OFS  4
#define ST7735_MADCTL_ML_MASK (1 << ST7735_MADCTL_ML_OFS)

// RGB-BGR Order
#define ST7735_MADCTL_RGB_OFS  3
#define ST7735_MADCTL_RGB_MASK (1 << ST7735_MADCTL_RGB_OFS)

// Horizontal refresh order
#define ST7735_MADCTL_MH_OFS  2
#define ST7735_MADCTL_MH_MASK (1 << ST7735_MADCTL_MH_OFS)

////////////////////////////////////////////////////
// IDMOFF: Idle mode off (No params/args) (pg. 115)
// IDMON: Idle mode on (No params/args) (pg. 116)
////////////////////////////////////////////////////

////////////////////////////////////////////
// COLMOD: Interface pixel format (pg. 118)
////////////////////////////////////////////
// 1st parameter
// Interface pixel format
#define ST7735_COLMOD_IFPF_OFS  7
#define ST7735_COLMOD_IFPF_MASK (1 << ST7735_COLMOD_IFPF_OFS)

#define ST7735_COLMOD_IFPF_12_BIT (3 << ST7735_COLMOD_IFPF_OFS)
#define ST7735_COLMOD_IFPF_16_BIT (5 << ST7735_COLMOD_IFPF_OFS)
#define ST7735_COLMOD_IFPF_18_BIT (6 << ST7735_COLMOD_IFPF_OFS)
#define ST7735_COLMOD_IFPF_NA     (7 << ST7735_COLMOD_IFPF_OFS)

//////////////////////////////////////////////////////////////////////////////////////////////////
// RDID1: Read ID1 value (LCD module's manufacturer ID) (Param/arg def's not necessary) (pg. 119)
// RDID2: Read ID2 value (LCD module/driver version ID) (Param/arg def's not necessary) (pg. 120)
// RDID3: Read ID3 value (LCD module/driver ID) (Param/arg def's not necessary) (pg. 121)
//////////////////////////////////////////////////////////////////////////////////////////////////

/************************************************
 * Command declarations: Panel function commands
 ************************************************/
#define ST7735_FRMCTR1    0xB1 // In normal mode (Full colors)
#define ST7735_FRMCTR2    0xB2 // In idle mode (8-colors)
#define ST7735_FRMCTR3    0xB3 // In partial mode + full colors
#define ST7735_INVCTR     0xB4 // Display inversion control
#define ST7735_PWCTR1     0xC0 // Power control setting
#define ST7735_PWCTR2     0xC1 // Power control setting
#define ST7735_PWCTR3     0xC2 // Power control setting (In normal mode (Full colors))
#define ST7735_PWCTR4     0xC3 // Power control setting (In idle mode (8-colors))
#define ST7735_PWCTR5     0xC4 // Power control setting (In partial mode + full colors)
#define ST7735_VMCTR1     0xC5 // VCOM control 1
#define ST7735_VMOFCTR    0xC7 // Set VCOM offset control
#define ST7735_WRID2      0xD1 // Set LCM version code
#define ST7735_WRID3      0xD2 // Set customer project code
#define ST7735_NVCTR1     0xD9 // NVM control status
#define ST7735_NVCTR2     0xDE // NVM read command
#define ST7735_NVCTR3     0xDF // NVM write command

// Panel function argument definitions

//////////////////////////////////////////////////////////////////////
// FRMCTR1: Frame rate control (In normal mode/full colors) (pg. 126)
//////////////////////////////////////////////////////////////////////
/**********************************************************************
 * Description: Set the frame frequency of the full colors normal mode.
 * Frame_rate= fosc / ((RTNA x 2 + 40) x (LINE + FPA + BPA))
 * fosc = 625kHz
 **********************************************************************/
// 1st parameter
// Set one line period A(Normal mode)
#define ST7735_FRMCTR1_RTNA_OFS  0
#define ST7735_FRMCTR1_RTNA_MASK (0x0F << ST7735_FRMCTR1_RTNA_OFS)

// 2nd parameter
// Front porch A(Normal mode)
#define ST7735_FRMCTR1_FPA_OFS  0
#define ST7735_FRMCTR1_FPA_MASK (0x0F << ST7735_FRMCTR1_FPA_OFS)

// 3rd parameter
// Back porch A(Normal mode)
#define ST7735_FRMCTR1_BPA_OFS  0
#define ST7735_FRMCTR1_BPA_MASK (0x0F << ST7735_FRMCTR1_BPA_OFS)

/////////////////////////////////////////////////////////////////
// FRMCTR2: Frame rate control (In idle mode/8 colors) (pg. 127)
/////////////////////////////////////////////////////////////////
/**********************************************************************
 * Description: Set the frame frequency of the idle mode.
 * Frame_rate= fosc / ((RTNB x 2 + 40) x (LINE + FPB + BPB))
 * fosc = 625kHz
 **********************************************************************/
// 1st parameter
// Set one line period B(Idle mode)
#define ST7735_FRMCTR1_RTNB_OFS  0
#define ST7735_FRMCTR1_RTNB_MASK (0x0F << ST7735_FRMCTR1_RTNB_OFS)

// 2nd parameter
// Front porch B(Idle mode)
#define ST7735_FRMCTR1_FPB_OFS  0
#define ST7735_FRMCTR1_FPB_MASK (0x0F << ST7735_FRMCTR1_FPB_OFS)

// 3rd parameter
// Back porch B(Idle mode)
#define ST7735_FRMCTR1_BPB_OFS  0
#define ST7735_FRMCTR1_BPB_MASK (0x0F << ST7735_FRMCTR1_BPB_OFS)

///////////////////////////////////////////////////////////////////////
// FRMCTR3: Frame rate control (In partial mode/full colors) (pg. 128)
///////////////////////////////////////////////////////////////////////
/**********************************************************************
 * Description: Set the frame frequency of partial mode with full colors.
 * Frame_rate= fosc / ((RTNC x 2 + 40) x (LINE + FPC + BPC))
 * fosc = 625kHz
 * NOTES:
 *  - The 1st through 3rd parameters are used in dot inversion mode.
 *  - The 4th through 6th parameters are used in line inversion mode.
 **********************************************************************/
// 1st parameter
// Set one line period C(Partial mode)
#define ST7735_FRMCTR1_RTNC_OFS  0
#define ST7735_FRMCTR1_RTNC_MASK (0x0F << ST7735_FRMCTR1_RTNC_OFS)

// 2nd parameter
// Front porch C(Partial mode)
#define ST7735_FRMCTR1_FPC_OFS  0
#define ST7735_FRMCTR1_FPC_MASK (0x0F << ST7735_FRMCTR1_FPC_OFS)

// 3rd parameter
// Back porch C(Partial mode)
#define ST7735_FRMCTR1_BPC_OFS  0
#define ST7735_FRMCTR1_BPC_MASK (0x0F << ST7735_FRMCTR1_BPC_OFS)

// 4th parameter
// Set one line period D(Partial mode)
#define ST7735_FRMCTR1_RTND_OFS  0
#define ST7735_FRMCTR1_RTND_MASK (0x0F << ST7735_FRMCTR1_RTND_OFS)

// 5th parameter
// Front porch D(Partial mode)
#define ST7735_FRMCTR1_FPD_OFS  0
#define ST7735_FRMCTR1_FPD_MASK (0x0F << ST7735_FRMCTR1_FPD_OFS)

// 6th parameter
// Back porch D(Partial mode)
#define ST7735_FRMCTR1_BPD_OFS  0
#define ST7735_FRMCTR1_BPD_MASK (0x0F << ST7735_FRMCTR1_BPD_OFS)

///////////////////////////////////////////////
// INVCTR: Display inversion control (pg. 129)
///////////////////////////////////////////////
// 1st parameter
// Inversion setting in full color normal mode (Normal mode on)
#define ST7735_INVCTR_NLA_OFS  2
#define ST7735_INVCTR_NLA_MASK (1 << ST7735_INVCTR_NLA_OFS)

// Inversion setting in idle mode (Idle mode on)
#define ST7735_INVCTR_NLB_OFS  1
#define ST7735_INVCTR_NLB_MASK (1 << ST7735_INVCTR_NLB_OFS)

// Inversion setting in full color partial mode (Partial mode on / Idle mode off)
#define ST7735_INVCTR_NLC_OFS  0
#define ST7735_INVCTR_NLC_MASK (1 << ST7735_INVCTR_NLC_OFS)

/////////////////////////////////////
// PWCTR1: Power control 1 (pg. 130)
/////////////////////////////////////
// 1st parameter
// AVDD Voltage (Voltages 4.5V to 5.1V available)
#define ST7735_PWCTR1_AVDD_OFS  5
#define ST7735_PWCTR1_AVDD_MASK (0x07 << ST7735_PWCTR1_AVDD_OFS)

#define ST7735_PWCTR1_AVDD_4_5V (0x00 << ST7735_PWCTR1_AVDD_OFS)
#define ST7735_PWCTR1_AVDD_4_6V (0x01 << ST7735_PWCTR1_AVDD_OFS)
#define ST7735_PWCTR1_AVDD_4_7V (0x02 << ST7735_PWCTR1_AVDD_OFS)
#define ST7735_PWCTR1_AVDD_4_8V (0x03 << ST7735_PWCTR1_AVDD_OFS)
#define ST7735_PWCTR1_AVDD_4_9V (0x04 << ST7735_PWCTR1_AVDD_OFS)
#define ST7735_PWCTR1_AVDD_5_0V (0x05 << ST7735_PWCTR1_AVDD_OFS)
#define ST7735_PWCTR1_AVDD_5_1V (0x06 << ST7735_PWCTR1_AVDD_OFS)

// VRHP: GVDD Voltages (Voltages 4.7V to 3.15V)
#define ST7735_PWCTR1_VRHP_OFS  0
#define ST7735_PWCTR1_VRHP_MASK (0x1F << ST7735_PWCTR1_VHRP_OFS)

#define ST7735_PWCTR1_VRHP_4_7  (0x00 << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_4_65 (0x01 << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_4_6  (0x02 << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_4_55 (0x03 << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_4_5  (0x04 << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_4_45 (0x05 << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_4_4  (0x06 << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_4_35 (0x07 << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_4_3  (0x08 << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_4_25 (0x09 << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_4_2  (0x0A << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_4_15 (0x0B << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_4_1  (0x0C << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_4_05 (0x0D << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_4_0  (0x0E << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_3_95 (0x0F << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_3_9  (0x10 << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_3_85 (0x11 << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_3_8  (0x12 << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_3_75 (0x13 << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_3_7  (0x14 << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_3_65 (0x15 << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_3_6  (0x16 << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_3_55 (0x17 << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_3_5  (0x18 << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_3_45 (0x19 << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_3_4  (0x1A << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_3_35 (0x1B << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_3_3  (0x1C << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_3_25 (0x1D << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_3_2  (0x1E << ST7735_PWCTR1_VRHP_OFS)
#define ST7735_PWCTR1_VRHP_3_15 (0x1F << ST7735_PWCTR1_VRHP_OFS)

// 2nd parameter
// VRHN: GVCL Voltages (Voltages -4.7V to -3.15V available)
#define ST7735_PWCTR1_VRHN_OFS  0
#define ST7735_PWCTR1_VRHN_MASK (0x1F << ST7735_PWCTR1_VHRN_OFS)

#define ST7735_PWCTR1_VRHN_4_7  (0x00 << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_4_65 (0x01 << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_4_6  (0x02 << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_4_55 (0x03 << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_4_5  (0x04 << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_4_45 (0x05 << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_4_4  (0x06 << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_4_35 (0x07 << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_4_3  (0x08 << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_4_25 (0x09 << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_4_2  (0x0A << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_4_15 (0x0B << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_4_1  (0x0C << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_4_05 (0x0D << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_4_0  (0x0E << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_3_95 (0x0F << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_3_9  (0x10 << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_3_85 (0x11 << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_3_8  (0x12 << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_3_75 (0x13 << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_3_7  (0x14 << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_3_65 (0x15 << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_3_6  (0x16 << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_3_55 (0x17 << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_3_5  (0x18 << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_3_45 (0x19 << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_3_4  (0x1A << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_3_35 (0x1B << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_3_3  (0x1C << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_3_25 (0x1D << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_3_2  (0x1E << ST7735_PWCTR1_VRHN_OFS)
#define ST7735_PWCTR1_VRHN_3_15 (0x1F << ST7735_PWCTR1_VRHN_OFS)

// 3rd parameter
// Mode: ...? Not sure...
#define ST7735_PWCTR1_MODE_OFS  6
#define ST7735_PWCTR1_MODE_MASK (0x03 << ST7735_PWCTR1_MODE_OFS)

#define ST7735_PWCTR1_MODE_2X     (0x00 << ST7735_PWCTR1_MODE_OFS)
#define ST7735_PWCTR1_MODE_3X     (0x01 << ST7735_PWCTR1_MODE_OFS)
#define ST7735_PWCTR1_MODE_AUTO   (0x02 << ST7735_PWCTR1_MODE_OFS)
#define ST7735_PWCTR1_MODE_3X_2   (0x03 << ST7735_PWCTR1_MODE_OFS)


/////////////////////////////////////
// PWCTR2: Power control 2 (pg. 132)
/////////////////////////////////////
// 1st parameter
// VGH25: Set the VGH supply level...
#define ST7735_PWCTR2_VGH25_OFS  6
#define ST7735_PWCTR2_VGH25_MASK (0x03 << ST7735_PWCTR2_VGH25_OFS)

#define ST7735_PWCTR2_VGH25_2_1  (0x00 << ST7735_PWCTR2_VGH25_OFS)
#define ST7735_PWCTR2_VGH25_2_2  (0x01 << ST7735_PWCTR2_VGH25_OFS)
#define ST7735_PWCTR2_VGH25_2_3  (0x02 << ST7735_PWCTR2_VGH25_OFS)
#define ST7735_PWCTR2_VGH25_2_4  (0x03 << ST7735_PWCTR2_VGH25_OFS)

// VGLSEL: Set the VGL supply level...
// Values include -7.5V, -10V, -12.5V, and -13V
#define ST7735_PWCTR2_VGLSEL_OFS  2
#define ST7735_PWCTR2_VGLSEL_MASK (0x03 << ST7735_PWCTR2_VGLSEL_OFS)

#define ST7735_PWCTR2_VGLSEL_7_5  (0x00 << ST7735_PWCTR2_VGLSEL_OFS)
#define ST7735_PWCTR2_VGLSEL_10   (0x01 << ST7735_PWCTR2_VGLSEL_OFS)
#define ST7735_PWCTR2_VGLSEL_12_5 (0x02 << ST7735_PWCTR2_VGLSEL_OFS)
#define ST7735_PWCTR2_VGLSEL_13   (0x03 << ST7735_PWCTR2_VGLSEL_OFS)

// VGHBT: Selects equation used for supply levels
#define ST7735_PWCTR2_VGHBT_OFS  2
#define ST7735_PWCTR2_VGHBT_MASK (0x03 << ST7735_PWCTR2_VGHBT_OFS)

#define ST7735_PWCTR2_VGHBT_EQ_0 (0x00 << ST7735_PWCTR2_VGHBT_OFS) // 2 * AVDD + VGH25
#define ST7735_PWCTR2_VGHBT_EQ_1 (0x01 << ST7735_PWCTR2_VGHBT_OFS) // 3 * AVDD
#define ST7735_PWCTR2_VGHBT_EQ_2 (0x02 << ST7735_PWCTR2_VGHBT_OFS) // 3 * AVDD + VGH25

/////////////////////////////////////
// PWCTR3: Power control 3 (pg. 134)
/////////////////////////////////////
// 1st parameter
// DCA[9:8]: Set the booster circuit step-up cycle in normal mode/full color
#define ST7735_PWCTR3_DCA_98_OFS  6
#define ST7735_PWCTR3_DCA_98_MASK (0x03 << ST7735_PWCTR3_DCA_98_OFS)

#define ST7735_PWCTR3_DCA_98_DIV_1   (0x00 << ST7735_PWCTR3_DCA_98_OFS)
#define ST7735_PWCTR3_DCA_98_DIV_1_5 (0x01 << ST7735_PWCTR3_DCA_98_OFS)
#define ST7735_PWCTR3_DCA_98_DIV_2   (0x02 << ST7735_PWCTR3_DCA_98_OFS)
#define ST7735_PWCTR3_DCA_98_DIV_4   (0x03 << ST7735_PWCTR3_DCA_98_OFS)

// SAPA: Adjust the amount of fixed current from the fixed current source in the operational amplifier for the source driver.
#define ST7735_PWCTR3_SAPA_OFS  3
#define ST7735_PWCTR3_SAPA_MASK (0x07 << ST7735_PWCTR3_SAPA_OFS)

#define ST7735_PWCTR3_SAPA_STOP        (0x00 << ST7735_PWCTR3_SAPA_OFS)
#define ST7735_PWCTR3_SAPA_SMALL       (0x01 << ST7735_PWCTR3_SAPA_OFS)
#define ST7735_PWCTR3_SAPA_MEDIUM_LOW  (0x02 << ST7735_PWCTR3_SAPA_OFS)
#define ST7735_PWCTR3_SAPA_MEDIUM      (0x03 << ST7735_PWCTR3_SAPA_OFS)
#define ST7735_PWCTR3_SAPA_MEDIUM_HIGH (0x04 << ST7735_PWCTR3_SAPA_OFS)
#define ST7735_PWCTR3_SAPA_LARGE       (0x05 << ST7735_PWCTR3_SAPA_OFS)

// APA: Adjust the amount of fixed current from the fixed current source in the operational amplifier for the source driver.
#define ST7735_PWCTR3_APA_OFS  0
#define ST7735_PWCTR3_APA_MASK (0x07 << ST7735_PWCTR3_APA_OFS)

#define ST7735_PWCTR3_APA_STOP        (0x00 << ST7735_PWCTR3_APA_OFS)
#define ST7735_PWCTR3_APA_SMALL       (0x01 << ST7735_PWCTR3_APA_OFS)
#define ST7735_PWCTR3_APA_MEDIUM_LOW  (0x02 << ST7735_PWCTR3_APA_OFS)
#define ST7735_PWCTR3_APA_MEDIUM      (0x03 << ST7735_PWCTR3_APA_OFS)
#define ST7735_PWCTR3_APA_MEDIUM_HIGH (0x04 << ST7735_PWCTR3_APA_OFS)
#define ST7735_PWCTR3_APA_LARGE       (0x05 << ST7735_PWCTR3_APA_OFS)

// 2nd parameter
// DCA[7:6]: Set the booster circuit step-up cycle in normal mode/full color
#define ST7735_PWCTR3_DCA_76_OFS  6
#define ST7735_PWCTR3_DCA_76_MASK (0x03 << ST7735_PWCTR3_DCA_76_OFS)

#define ST7735_PWCTR3_DCA_76_DIV_1   (0x00 << ST7735_PWCTR3_DCA_76_OFS)
#define ST7735_PWCTR3_DCA_76_DIV_1_5 (0x01 << ST7735_PWCTR3_DCA_76_OFS)
#define ST7735_PWCTR3_DCA_76_DIV_2   (0x02 << ST7735_PWCTR3_DCA_76_OFS)
#define ST7735_PWCTR3_DCA_76_DIV_4   (0x03 << ST7735_PWCTR3_DCA_76_OFS)

// DCA[5:4]: Set the booster circuit step-up cycle in normal mode/full color
#define ST7735_PWCTR3_DCA_54_OFS  4
#define ST7735_PWCTR3_DCA_54_MASK (0x03 << ST7735_PWCTR3_DCA_54_OFS)

#define ST7735_PWCTR3_DCA_54_DIV_1   (0x00 << ST7735_PWCTR3_DCA_54_OFS)
#define ST7735_PWCTR3_DCA_54_DIV_1_5 (0x01 << ST7735_PWCTR3_DCA_54_OFS)
#define ST7735_PWCTR3_DCA_54_DIV_2   (0x02 << ST7735_PWCTR3_DCA_54_OFS)
#define ST7735_PWCTR3_DCA_54_DIV_4   (0x03 << ST7735_PWCTR3_DCA_54_OFS)

// DCA[3:2]: Set the booster circuit step-up cycle in normal mode/full color
#define ST7735_PWCTR3_DCA_32_OFS  2
#define ST7735_PWCTR3_DCA_32_MASK (0x03 << ST7735_PWCTR3_DCA_32_OFS)

#define ST7735_PWCTR3_DCA_32_DIV_1   (0x00 << ST7735_PWCTR3_DCA_32_OFS)
#define ST7735_PWCTR3_DCA_32_DIV_1_5 (0x01 << ST7735_PWCTR3_DCA_32_OFS)
#define ST7735_PWCTR3_DCA_32_DIV_2   (0x02 << ST7735_PWCTR3_DCA_32_OFS)
#define ST7735_PWCTR3_DCA_32_DIV_4   (0x03 << ST7735_PWCTR3_DCA_32_OFS)

// DCA[1:0]: Set the booster circuit step-up cycle in normal mode/full color
#define ST7735_PWCTR3_DCA_10_OFS  0
#define ST7735_PWCTR3_DCA_10_MASK (0x03 << ST7735_PWCTR3_DCA_10_OFS)

#define ST7735_PWCTR3_DCA_10_DIV_1   (0x00 << ST7735_PWCTR3_DCA_10_OFS)
#define ST7735_PWCTR3_DCA_10_DIV_1_5 (0x01 << ST7735_PWCTR3_DCA_10_OFS)
#define ST7735_PWCTR3_DCA_10_DIV_2   (0x02 << ST7735_PWCTR3_DCA_10_OFS)
#define ST7735_PWCTR3_DCA_10_DIV_4   (0x03 << ST7735_PWCTR3_DCA_10_OFS)

///////////////////////////////////////////
// PWCTR4: Power control 4 (pg. 136)
///////////////////////////////////////////
// 1st parameter
// DCB[9:8]: Set the booster circuit step-up cycle in idle mode/8 color
#define ST7735_PWCTR4_DCB_98_OFS  6
#define ST7735_PWCTR4_DCB_98_MASK (0x03 << ST7735_PWCTR4_DCB_98_OFS)

#define ST7735_PWCTR4_DCB_98_DIV_1   (0x00 << ST7735_PWCTR4_DCB_98_OFS)
#define ST7735_PWCTR4_DCB_98_DIV_1_5 (0x01 << ST7735_PWCTR4_DCB_98_OFS)
#define ST7735_PWCTR4_DCB_98_DIV_2   (0x02 << ST7735_PWCTR4_DCB_98_OFS)
#define ST7735_PWCTR4_DCB_98_DIV_4   (0x03 << ST7735_PWCTR4_DCB_98_OFS)

// SAPB: Adjust the amount of fixed current from the fixed current source in the operational amplifier for the source driver.
#define ST7735_PWCTR4_SAPB_OFS  3
#define ST7735_PWCTR4_SAPB_MASK (0x07 << ST7735_PWCTR4_SAPB_OFS)

#define ST7735_PWCTR4_SAPB_STOP        (0x00 << ST7735_PWCTR4_SAPB_OFS)
#define ST7735_PWCTR4_SAPB_SMALL       (0x01 << ST7735_PWCTR4_SAPB_OFS)
#define ST7735_PWCTR4_SAPB_MEDIUM_LOW  (0x02 << ST7735_PWCTR4_SAPB_OFS)
#define ST7735_PWCTR4_SAPB_MEDIUM      (0x03 << ST7735_PWCTR4_SAPB_OFS)
#define ST7735_PWCTR4_SAPB_MEDIUM_HIGH (0x04 << ST7735_PWCTR4_SAPB_OFS)
#define ST7735_PWCTR4_SAPB_LARGE       (0x05 << ST7735_PWCTR4_SAPB_OFS)

// APB: Adjust the amount of fixed current from the fixed current source in the operational amplifier for the source driver.
#define ST7735_PWCTR4_APB_OFS  0
#define ST7735_PWCTR4_APB_MASK (0x07 << ST7735_PWCTR4_APB_OFS)

#define ST7735_PWCTR4_APB_STOP        (0x00 << ST7735_PWCTR4_APB_OFS)
#define ST7735_PWCTR4_APB_SMALL       (0x01 << ST7735_PWCTR4_APB_OFS)
#define ST7735_PWCTR4_APB_MEDIUM_LOW  (0x02 << ST7735_PWCTR4_APB_OFS)
#define ST7735_PWCTR4_APB_MEDIUM      (0x03 << ST7735_PWCTR4_APB_OFS)
#define ST7735_PWCTR4_APB_MEDIUM_HIGH (0x04 << ST7735_PWCTR4_APB_OFS)
#define ST7735_PWCTR4_APB_LARGE       (0x05 << ST7735_PWCTR4_APB_OFS)

// 2nd parameter
// DCB[7:6]: Set the booster circuit step-up cycle in idle mode/8 color
#define ST7735_PWCTR4_DCB_76_OFS  6
#define ST7735_PWCTR4_DCB_76_MASK (0x03 << ST7735_PWCTR4_DCB_76_OFS)

#define ST7735_PWCTR4_DCB_76_DIV_1   (0x00 << ST7735_PWCTR4_DCB_76_OFS)
#define ST7735_PWCTR4_DCB_76_DIV_1_5 (0x01 << ST7735_PWCTR4_DCB_76_OFS)
#define ST7735_PWCTR4_DCB_76_DIV_2   (0x02 << ST7735_PWCTR4_DCB_76_OFS)
#define ST7735_PWCTR4_DCB_76_DIV_4   (0x03 << ST7735_PWCTR4_DCB_76_OFS)

// DCB[5:4]: Set the booster circuit step-up cycle in idle mode/8 color
#define ST7735_PWCTR4_DCB_54_OFS  4
#define ST7735_PWCTR4_DCB_54_MASK (0x03 << ST7735_PWCTR4_DCB_54_OFS)

#define ST7735_PWCTR4_DCB_54_DIV_1   (0x00 << ST7735_PWCTR4_DCB_54_OFS)
#define ST7735_PWCTR4_DCB_54_DIV_1_5 (0x01 << ST7735_PWCTR4_DCB_54_OFS)
#define ST7735_PWCTR4_DCB_54_DIV_2   (0x02 << ST7735_PWCTR4_DCB_54_OFS)
#define ST7735_PWCTR4_DCB_54_DIV_4   (0x03 << ST7735_PWCTR4_DCB_54_OFS)

// DCB[3:2]: Set the booster circuit step-up cycle in idle mode/8 color
#define ST7735_PWCTR4_DCB_32_OFS  2
#define ST7735_PWCTR4_DCB_32_MASK (0x03 << ST7735_PWCTR4_DCB_32_OFS)

#define ST7735_PWCTR4_DCB_32_DIV_1   (0x00 << ST7735_PWCTR4_DCB_32_OFS)
#define ST7735_PWCTR4_DCB_32_DIV_1_5 (0x01 << ST7735_PWCTR4_DCB_32_OFS)
#define ST7735_PWCTR4_DCB_32_DIV_2   (0x02 << ST7735_PWCTR4_DCB_32_OFS)
#define ST7735_PWCTR4_DCB_32_DIV_4   (0x03 << ST7735_PWCTR4_DCB_32_OFS)

// DCB[1:0]: Set the booster circuit step-up cycle in idle mode/8 color
#define ST7735_PWCTR4_DCB_10_OFS  0
#define ST7735_PWCTR4_DCB_10_MASK (0x03 << ST7735_PWCTR4_DCB_10_OFS)

#define ST7735_PWCTR4_DCB_10_DIV_1   (0x00 << ST7735_PWCTR4_DCB_10_OFS)
#define ST7735_PWCTR4_DCB_10_DIV_1_5 (0x01 << ST7735_PWCTR4_DCB_10_OFS)
#define ST7735_PWCTR4_DCB_10_DIV_2   (0x02 << ST7735_PWCTR4_DCB_10_OFS)
#define ST7735_PWCTR4_DCB_10_DIV_4   (0x03 << ST7735_PWCTR4_DCB_10_OFS)


///////////////////////////////////////////
// PWCTR5: Power control 5 (pg. 138)
///////////////////////////////////////////
// 1st parameter
// DCC[9:8]: Set the booster circuit step-up cycle in partial mode/full color
#define ST7735_PWCTR5_DCC_98_OFS  6
#define ST7735_PWCTR5_DCC_98_MASK (0x03 << ST7735_PWCTR5_DCC_98_OFS)

#define ST7735_PWCTR5_DCC_98_DIV_1   (0x00 << ST7735_PWCTR5_DCC_98_OFS)
#define ST7735_PWCTR5_DCC_98_DIV_1_5 (0x01 << ST7735_PWCTR5_DCC_98_OFS)
#define ST7735_PWCTR5_DCC_98_DIV_2   (0x02 << ST7735_PWCTR5_DCC_98_OFS)
#define ST7735_PWCTR5_DCC_98_DIV_4   (0x03 << ST7735_PWCTR5_DCC_98_OFS)

// SAPC: Adjust the amount of fixed current from the fixed current source in the operational amplifier for the source driver.
#define ST7735_PWCTR5_SAPC_OFS  3
#define ST7735_PWCTR5_SAPC_MASK (0x07 << ST7735_PWCTR5_SAPC_OFS)

#define ST7735_PWCTR5_SAPC_STOP        (0x00 << ST7735_PWCTR5_SAPC_OFS)
#define ST7735_PWCTR5_SAPC_SMALL       (0x01 << ST7735_PWCTR5_SAPC_OFS)
#define ST7735_PWCTR5_SAPC_MEDIUM_LOW  (0x02 << ST7735_PWCTR5_SAPC_OFS)
#define ST7735_PWCTR5_SAPC_MEDIUM      (0x03 << ST7735_PWCTR5_SAPC_OFS)
#define ST7735_PWCTR5_SAPC_MEDIUM_HIGH (0x04 << ST7735_PWCTR5_SAPC_OFS)
#define ST7735_PWCTR5_SAPC_LARGE       (0x05 << ST7735_PWCTR5_SAPC_OFS)

// APC: Adjust the amount of fixed current from the fixed current source in the operational amplifier for the source driver.
#define ST7735_PWCTR5_APC_OFS  0
#define ST7735_PWCTR5_APC_MASK (0x07 << ST7735_PWCTR5_APC_OFS)

#define ST7735_PWCTR5_APC_STOP        (0x00 << ST7735_PWCTR5_APC_OFS)
#define ST7735_PWCTR5_APC_SMALL       (0x01 << ST7735_PWCTR5_APC_OFS)
#define ST7735_PWCTR5_APC_MEDIUM_LOW  (0x02 << ST7735_PWCTR5_APC_OFS)
#define ST7735_PWCTR5_APC_MEDIUM      (0x03 << ST7735_PWCTR5_APC_OFS)
#define ST7735_PWCTR5_APC_MEDIUM_HIGH (0x04 << ST7735_PWCTR5_APC_OFS)
#define ST7735_PWCTR5_APC_LARGE       (0x05 << ST7735_PWCTR5_APC_OFS)

// 2nd parameter
// DCC[7:6]: Set the booster circuit step-up cycle in partial mode/full color
#define ST7735_PWCTR5_DCC_76_OFS  6
#define ST7735_PWCTR5_DCC_76_MASK (0x03 << ST7735_PWCTR5_DCC_76_OFS)

#define ST7735_PWCTR5_DCC_76_DIV_1   (0x00 << ST7735_PWCTR5_DCC_76_OFS)
#define ST7735_PWCTR5_DCC_76_DIV_1_5 (0x01 << ST7735_PWCTR5_DCC_76_OFS)
#define ST7735_PWCTR5_DCC_76_DIV_2   (0x02 << ST7735_PWCTR5_DCC_76_OFS)
#define ST7735_PWCTR5_DCC_76_DIV_4   (0x03 << ST7735_PWCTR5_DCC_76_OFS)

// DCC[5:4]: Set the booster circuit step-up cycle in partial mode/full color
#define ST7735_PWCTR5_DCC_54_OFS  4
#define ST7735_PWCTR5_DCC_54_MASK (0x03 << ST7735_PWCTR5_DCC_54_OFS)

#define ST7735_PWCTR5_DCC_54_DIV_1   (0x00 << ST7735_PWCTR5_DCC_54_OFS)
#define ST7735_PWCTR5_DCC_54_DIV_1_5 (0x01 << ST7735_PWCTR5_DCC_54_OFS)
#define ST7735_PWCTR5_DCC_54_DIV_2   (0x02 << ST7735_PWCTR5_DCC_54_OFS)
#define ST7735_PWCTR5_DCC_54_DIV_4   (0x03 << ST7735_PWCTR5_DCC_54_OFS)

// DCC[3:2]: Set the booster circuit step-up cycle in partial mode/full color
#define ST7735_PWCTR5_DCC_32_OFS  2
#define ST7735_PWCTR5_DCC_32_MASK (0x03 << ST7735_PWCTR5_DCC_32_OFS)

#define ST7735_PWCTR5_DCC_32_DIV_1   (0x00 << ST7735_PWCTR5_DCC_32_OFS)
#define ST7735_PWCTR5_DCC_32_DIV_1_5 (0x01 << ST7735_PWCTR5_DCC_32_OFS)
#define ST7735_PWCTR5_DCC_32_DIV_2   (0x02 << ST7735_PWCTR5_DCC_32_OFS)
#define ST7735_PWCTR5_DCC_32_DIV_4   (0x03 << ST7735_PWCTR5_DCC_32_OFS)

// DCC[1:0]: Set the booster circuit step-up cycle in partial mode/full color
#define ST7735_PWCTR5_DCC_10_OFS  0
#define ST7735_PWCTR5_DCC_10_MASK (0x03 << ST7735_PWCTR5_DCC_10_OFS)

#define ST7735_PWCTR5_DCC_10_DIV_1   (0x00 << ST7735_PWCTR5_DCC_10_OFS)
#define ST7735_PWCTR5_DCC_10_DIV_1_5 (0x01 << ST7735_PWCTR5_DCC_10_OFS)
#define ST7735_PWCTR5_DCC_10_DIV_2   (0x02 << ST7735_PWCTR5_DCC_10_OFS)
#define ST7735_PWCTR5_DCC_10_DIV_4   (0x03 << ST7735_PWCTR5_DCC_10_OFS)

////////////////////////////////////
// VMCTR1: VCOM control 1 (pg. 140)
////////////////////////////////////
// 1st parameter
// VCOM voltage setting (-0.425V to -2V)
#define ST7735_VMCTR1_VCOM_OFS  0
#define ST7735_VMCTR1_VCOM_MASK (0x3F << ST7735_VMCTR1_VCOM_OFS)

#define ST7735_VMCTR1_VCOM_0_425 (0x00 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_0_45  (0x01 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_0_475 (0x02 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_0_5   (0x03 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_0_525 (0x04 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_0_55  (0x05 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_0_575 (0x06 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_0_6   (0x07 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_0_625 (0x08 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_0_65  (0x09 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_0_675 (0x0A << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_0_7   (0x0B << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_0_725 (0x0C << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_0_75  (0x0D << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_0_775 (0x0E << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_0_8   (0x0F << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_0_825 (0x10 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_0_85  (0x11 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_0_875 (0x12 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_0_9   (0x13 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_0_925 (0x14 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_0_95  (0x15 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_0_975 (0x16 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_0   (0x17 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_025 (0x18 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_05  (0x19 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_075 (0x1A << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_1   (0x1B << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_125 (0x1C << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_15  (0x1D << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_175 (0x1E << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_2   (0x1F << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_225 (0x20 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_25  (0x21 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_275 (0x22 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_3   (0x23 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_325 (0x24 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_35  (0x25 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_375 (0x26 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_4   (0x27 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_425 (0x28 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_45  (0x29 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_475 (0x2A << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_5   (0x2B << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_525 (0x2C << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_55  (0x2D << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_575 (0x2E << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_6   (0x2F << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_625 (0x30 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_65  (0x31 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_675 (0x32 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_7   (0x33 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_725 (0x34 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_75  (0x35 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_775 (0x36 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_8   (0x37 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_825 (0x38 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_85  (0x39 << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_875 (0x3A << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_9   (0x3B << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_925 (0x3C << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_95  (0x3D << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_1_975 (0x3E << ST7735_VMCTR1_VCOM_OFS)
#define ST7735_VMCTR1_VCOM_2_0   (0x3F << ST7735_VMCTR1_VCOM_OFS)

//////////////////////////////////////////
// VMOFCTR: VCOM offset control (pg. 142)
//////////////////////////////////////////
// NOTE: Before using this command, the bit VMF_EN of command NVFCTR1 must be set.
// 1st parameter
// Set VCOM voltage level to reduce flicker...?
// Question: Would definitions for these values be beneficial for readability?
#define ST7735_VMOFCTR_VMF_OFS  0
#define ST7735_VMOFCTR_VMF_MASK (0x1F << ST7735_VMOFCTR_VMF_OFS)

///////////////////////////////////////////////////////////////////////
// WRID2: Write ID2 value (LCD module version, saved to NVM) (pg. 143)
///////////////////////////////////////////////////////////////////////
// 1st parameter
#define ST7735_WRID2_ID2_OFS  0
#define ST7735_WRID2_ID2_MASK (0x7F << ST7735_WRID2_ID2_OFS)

//////////////////////////////////////////////////////////////////////
// WRID3: Write ID3 value (Project module ID, saved to NVM) (pg. 144)
//////////////////////////////////////////////////////////////////////
// 1st parameter
#define ST7735_WRID3_ID3_OFS  0
#define ST7735_WRID3_ID3_MASK (0xFF << ST7735_WRID2_ID3_OFS)

/////////////////////////////////////////
// NVFCTR1: NVM control status (pg. 145)
/////////////////////////////////////////
// 1st parameter
// VMF_EN: Enable use of `VMOFCTR` commands
#define ST7735_NVFCTR1_VMF_EN_OFS  6
#define ST7735_NVFCTR1_VMF_EN_MASK (0x01 << ST7735_NVFCTR1_VMF_EN_OFS)

// ID2_EN: Enable use of `WRID2` command
#define ST7735_NVFCTR1_ID2_EN_OFS  5
#define ST7735_NVFCTR1_ID2_EN_MASK (0x01 << ST7735_NVFCTR1_ID2_EN_OFS)

// EXT_R: Extension command status (That's pretty vague...)
#define ST7735_NVFCTR1_EXT_R_OFS  0
#define ST7735_NVFCTR1_EXT_R_MASK (0x01 << ST7735_NVFCTR1_EXT_R_OFS)

////////////////////////////////////////
// NVFCTR2: NVM read command (pg. 146)
// Question: If everythin is specified in the datasheet, why is this a command?

// NVFCTR3: NVM write command (pg. 147)
// Command used to program/erase parts of NVM

// GMCTRP1: Gamma ('+' polarity) correction characteristics setting (pg. 148)
// See datasheet for usage

// GMCTRN1: Gamma ‘-’polarity Correction Characteristics Setting (pg. 150)
// See datasheet for usage
////////////////////////////////////////


/**********************************
 * ST7735 library functions
 **********************************/
// st7735 initialization functions
void st7735_setup(void);
void st7735_setup_pins(void);
void st7735_setup_peripherals(void);
void st7735_setup_peripherals_spi(void);
void st7735_hard_reset(void);

// st7735 communication functions
uint8_t st7735_send_data(uint8_t data);
uint8_t st7735_send_command(uint8_t cmd);

#endif /* JEDGE_ST7735_H_ */
