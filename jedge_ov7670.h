p/*
 * jedge_ov7670.h
 *
 *  Created on: July 6, 2018
 *      Author: Joshua Edgcombe
 */

#ifndef JEDGE_OV7670_H_
#define JEDGE_OV7670_H_

#define OV7670_REG_GAIN     0x00 // Gain control gain setting
#define OV7670_REG_BLUE     0x01 // Blue channel gain setting
#define OV7670_REG_RED      0x02 // Red channel gain setting
#define OV7670_REG_VREF     0x03 // Vertical frame control
#define OV7670_REG_COM1     0x04 // Common control 1
#define OV7670_REG_BAVE     0x05 // U/B average level
#define OV7670_REG_GbAVE    0x06 // Y/Gb average level
#define OV7670_REG_AECHH    0x07 // Exposure value
#define OV7670_REG_RAVE     0x08 // V/R average level
#define OV7670_REG_COM2     0x09 // Common control 2
#define OV7670_REG_PID      0x0A // Product ID number (MSB) (Read only)
#define OV7670_REG_VER      0x0B // Product ID number (LSB) (Read only)
#define OV7670_REG_COM3     0x0C // Common control 3
#define OV7670_REG_COM4     0x0D // Common control 4
#define OV7670_REG_COM5     0x0E // Common control 5
#define OV7670_REG_COM6     0x0F // Common control 6
#define OV7670_REG_AECH     0x10 // Exposure value
#define OV7670_REG_CLKRC    0x11 // Internal clock
#define OV7670_REG_COM7     0x12 // Common control 7
#define OV7670_REG_COM8     0x13 // Common control 8
#define OV7670_REG_COM9     0x14 // Common control 9
#define OV7670_REG_COM10    0x15 // Common control 10
#define OV7670_REG_RSVD     0x16 // Reserved...
#define OV7670_REG_HSTART   0x17 // Output format - Horizontal frame start
#define OV7670_REG_HSTOP    0x18 // Output format - Horizontal frame end
#define OV7670_REG_VSTART   0x19 // Output format - Vertical frame start
#define OV7670_REG_VSTOP    0x1A // Output format - Vertical frame stop
#define OV7670_REG_PSHFT    0x1B // Data format - pixel delay select
#define OV7670_REG_MIDH     0x1C // Manufacturer ID byte - high (Read only)
#define OV7670_REG_MIDL     0x1D // Manufacturer ID byte - low (Read only)
#define OV7670_REG_MVFP     0x1E // Mirror/VFlip enable
#define OV7670_REG_LAEC     0x1F // Reserved...
#define OV7670_REG_ADCCTR0  0x20 // ADC control 0
#define OV7670_REG_ADCCTR1  0x21 // ADC control 1
#define OV7670_REG_ADCCTR2  0x22 // ADC control 2
#define OV7670_REG_ADCCTR3  0x23 // ADC control 3
#define OV7670_REG_AEW      0x24 // AGC/AEC - Stable operating region (upper limit)
#define OV7670_REG_AEB      0x25 // AGC/AEC - Stable operating region (lower limit)
#define OV7670_REG_VPT      0x26 // AGC/AEC - Fast mode operating region
#define OV7670_REG_BBIAS    0x27 // B channel signal output bias
#define OV7670_REG_GbBIAS   0x28 // Gb channel signal output bias
#define OV7670_REG_RSVD_2   0x29 // Reserved...
#define OV7670_REG_EXHCH    0x2A // Dummy pixel insert MSB
#define OV7670_REG_EXHCL    0x2B // Dummy pixel insert LSB
#define OV7670_REG_RBIAS    0x2C // R channel signal output bias
#define OV7670_REG_ADVFL    0x2D // LSB of insert dummy lines in vertical direction
#define OV7670_REG_ADVFH    0x2E // MSB of insert dummy lines in vertical direction
#define OV7670_REG_YAVE     0x2F // Y/G channel average value
#define OV7670_REG_HSYST    0x30 // HSYNC rising edge delay (low 8 bits)
#define OV7670_REG_HSYEN    0x31 // HSYNC falling edge delay (low 8 bits)
#define OV7670_REG_HREF     0x32 // HREF control
#define OV7670_REG_CHLF     0x33 // Array current control (Reserved)
#define OV7670_REG_ARBLM    0x34 // Array reference control (Reserved)
#define OV7670_REG_RSVD_3   0x35 // Reserved...
#define OV7670_REG_RSVD_4   0x36 // Reserved...
#define OV7670_REG_ADC      0x37 // ADC control
#define OV7670_REG_ACOM     0x38 // ADC and analog common mode control
#define OV7670_REG_OFON     0x39 // ADC offset control
#define OV7670_REG_TSLB     0x3A // Line buffer test option
#define OV7670_REG_COM11    0x3B // Common control 11
#define OV7670_REG_COM12    0x3C // Common control 12
#define OV7670_REG_COM13    0x3D // Common control 13
#define OV7670_REG_COM14    0x3E // Common control 14
#define OV7670_REG_EDGE     0x3F // Edge enhancement adjustment
#define OV7670_REG_COM15    0x40 // Common control 15
#define OV7670_REG_COM16    0x41 // Common control 16
#define OV7670_REG_COM17    0x42 // Common control 17
#define OV7670_REG_AWBC1    0x43 // Reserved...
#define OV7670_REG_AWBC2    0x44 // Reserved...
#define OV7670_REG_AWBC3    0x45 // Reserved...
#define OV7670_REG_AWBC4    0x46 // Reserved...
#define OV7670_REG_AWBC5    0x47 // Reserved...
#define OV7670_REG_AWBC6    0x48 // Reserved...
#define OV7670_REG_RSVD_5   0x49 // Reserved...
#define OV7670_REG_RSVD_6   0x4A // Reserved...
#define OV7670_REG_REG4B    0x4B // Register 4B
#define OV7670_REG_DNSTH    0x4C // De-noise threshold
#define OV7670_REG_RSVD_7   0x4D // Reserved...
#define OV7670_REG_RSVD_8   0x4E // Reserved...
#define OV7670_REG_MTX1     0x4F // Matrix coefficient 1
#define OV7670_REG_MTX2     0x50 // Matrix coefficient 2
#define OV7670_REG_MTX3     0x51 // Matrix coefficient 3
#define OV7670_REG_MTX4     0x52 // Matrix coefficient 4
#define OV7670_REG_MTX5     0x53 // Matrix coefficient 5
#define OV7670_REG_MTX6     0x54 // Matrix coefficient 6
#define OV7670_REG_BRIGHT   0x55 // Brightness control
#define OV7670_REG_CONTRAS  0x56 // Contrast control
#define OV7670_REG_CONTRAS_CENTER  0x57 // Contrast center
#define OV7670_REG_MTXS     0x58 // Matrix coefficient signs
#define OV7670_REG_RSVD_9   0x59 // Reserved...
#define OV7670_REG_RSVD_10  0x5A // Reserved...
#define OV7670_REG_RSVD_11  0x5B // Reserved...
#define OV7670_REG_RSVD_12  0x5C // Reserved...
#define OV7670_REG_RSVD_13  0x5D // Reserved...
#define OV7670_REG_RSVD_14  0x5E // Reserved...
#define OV7670_REG_RSVD_15  0x5F // Reserved...
#define OV7670_REG_RSVD_16  0x60 // Reserved...
#define OV7670_REG_RSVD_17  0x61 // Reserved...
#define OV7670_REG_LCC1     0x62 // Lens correction option 1
#define OV7670_REG_LCC2     0x63 // Lens correction option 2
#define OV7670_REG_LCC3     0x64 // Lens correction option 3
#define OV7670_REG_LCC4     0x65 // Lens correction option 4
#define OV7670_REG_LCC5     0x66 // Lens correction option 5
#define OV7670_REG_MANU     0x67 // Manual U value
#define OV7670_REG_MANV     0x68 // Manual V value
#define OV7670_REG_GFIX     0x69 // Fix gain control
#define OV7670_REG_GGAIN    0x6A // G channel AWB gain
#define OV7670_REG_DBLV     0x6B // PLL control
#define OV7670_REG_AWBCTR3  0x6C // AWB control 3
#define OV7670_REG_AWBCTR2  0x6D // AWB control 2
#define OV7670_REG_AWBCTR1  0x6E // AWB control 1
#define OV7670_REG_AWBCTR0  0x6F // AWB control 0
#define OV7670_REG_SCALING_XSC 0x70 // Test_pattern
#define OV7670_REG_SCALING_YSC 0x71 // Test_pattern
#define OV7670_REG_SCALING_DCWCTR 0x72 // DCW control
#define OV7670_REG_SCALING_PCLK_DIV 0x73 // DSP clock divider control
#define OV7670_REG_REG74    0x74 // Register 74
#define OV7670_REG_REG75    0x75 // Edge enhancement lower limit
#define OV7670_REG_REG76    0x76 // Edge enhancement higher limit and pixel correction
#define OV7670_REG_REG77    0x77 // Offset de-noiserange control
#define OV7670_REG_RSVD_18  0x78 // Reserved...
#define OV7670_REG_RSVD_19  0x79 // Reserved...
#define OV7670_REG_GAM1     0x7A // Gamma curve 1st segment input end point 0x010 output value
#define OV7670_REG_GAM2     0x7B // Gamma curve 2nd segment input end point 0x020 output value
#define OV7670_REG_GAM3     0x7C // Gamma curve 3rd segment input end point 0x040 output value
#define OV7670_REG_GAM4     0x7D // Gamma curve 4th segment input end point 0x080 output value
#define OV7670_REG_GAM5     0x7E // Gamma curve 5th segment input end point 0x0A0 output value
#define OV7670_REG_GAM6     0x7F // Gamma curve 6th segment input end point 0x0C0 output value
#define OV7670_REG_GAM7     0x80 // Gamma curve 7th segment input end point 0x0E0 output value
#define OV7670_REG_GAM8     0x89 // Gamma curve 8th segment input end point 0x100 output value (WRONG ADDRESS?)
#define OV7670_REG_GAM9     0x89 // Gamma curve 9th segment input end point 0x120 output value (WRONG ADDRESS?)
#define OV7670_REG_GAM10    0x89 // Gamma curve 10th segment input end point 0x140 output value (WRONG ADDRESS?)
#define OV7670_REG_GAM11    0x89 // Gamma curve 11th segment input end point 0x180 output value (WRONG ADDRESS?)
#define OV7670_REG_GAM12    0x86 // Gamma curve 12th segment input end point 0x1C0 output value
#define OV7670_REG_GAM13    0x87 // Gamma curve 13th segment input end point 0x240 output value
#define OV7670_REG_GAM14    0x88 // Gamma curve 14th segment input end point 0x2C0 output value
#define OV7670_REG_GAM15    0x89 // Gamma curve 15th segment input end point 0x340 output value
#define OV7670_REG_RSVD_20  0x8A // Reserved...
#define OV7670_REG_RSVD_21  0x8B // Reserved...
#define OV7670_REG_RSVD_22  0x8C // Reserved...
#define OV7670_REG_RSVD_23  0x8D // Reserved...
#define OV7670_REG_RSVD_24  0x8E // Reserved...
#define OV7670_REG_RSVD_25  0x8F // Reserved...
#define OV7670_REG_RSVD_26  0x90 // Reserved...
#define OV7670_REG_RSVD_27  0x91 // Reserved...
#define OV7670_REG_DM_LNL   0x92 // Dummy line low 8-bits
#define OV7670_REG_DM_LNH   0x93 // Dummy line high 8-bits
#define OV7670_REG_LCC6     0x94 // Lens correction option 6
#define OV7670_REG_LCC7     0x95 // Lens correction option 7
#define OV7670_REG_RSVD_28  0x96 // Reserved...
#define OV7670_REG_RSVD_29  0x97 // Reserved...
#define OV7670_REG_RSVD_30  0x98 // Reserved...
#define OV7670_REG_RSVD_31  0x99 // Reserved...
#define OV7670_REG_RSVD_32  0x9A // Reserved...
#define OV7670_REG_RSVD_33  0x9B // Reserved...
#define OV7670_REG_RSVD_34  0x9C // Reserved...
#define OV7670_REG_BD50ST   0x9D // 50 Hz banding filter value
#define OV7670_REG_BD60ST   0x9E // 60 Hz banding filter value
#define OV7670_REG_HIST_0   0x9F // Histogram-based AEC/AGC control
#define OV7670_REG_HIST_1   0xA0 // Histogram-based AEC/AGC control
#define OV7670_REG_HIST_2   0xA1 // Histogram-based AEC/AGC control
#define OV7670_REG_HIST_3   0xA2 // Histogram-based AEC/AGC control
#define OV7670_REG_HIST_4   0xA3 // Histogram-based AEC/AGC control
#define OV7670_REG_HIST_5   0xA4 // Histogram-based AEC/AGC control
#define OV7670_REG_HIST_6   0xA5 // Histogram-based AEC/AGC control
#define OV7670_REG_HIST_7   0xA6 // Histogram-based AEC/AGC control
#define OV7670_REG_HIST_8   0xA7 // Histogram-based AEC/AGC control
#define OV7670_REG_HIST_9   0xA8 // Histogram-based AEC/AGC control
#define OV7670_REG_HIST_10  0xA9 // Histogram-based AEC/AGC control
#define OV7670_REG_HIST_11  0xAA // Histogram-based AEC/AGC control
#define OV7670_REG_HIST_12  0xAB // Histogram-based AEC/AGC control
#define OV7670_REG_STR_OPT  0xAC // Strobe options
#define OV7670_REG_STR_R    0xAD // R gain for LED output frame
#define OV7670_REG_STR_G    0xAE // G gain for LED output frame
#define OV7670_REG_STR_B    0xAF // B gain for LED output frame
#define OV7670_REG_RSVD_35  0xB0 // Reserved...
#define OV7670_REG_RSVD_36  0xB1 // Reserved...
#define OV7670_REG_RSVD_37  0xB2 // Reserved...
#define OV7670_REG_THL_ST   0xB3 // Digital BLC target
#define OV7670_REG_RSVD_38  0xB4 // Reserved...
#define OV7670_REG_THL_DLT  0xB5 // Digital BLC stable range
#define OV7670_REG_RSVD_39  0xB6 // Reserved...
#define OV7670_REG_RSVD_40  0xB7 // Reserved...
#define OV7670_REG_RSVD_41  0xB8 // Reserved...
#define OV7670_REG_RSVD_42  0xB9 // Reserved...
#define OV7670_REG_RSVD_43  0xBA // Reserved...
#define OV7670_REG_RSVD_44  0xBB // Reserved...
#define OV7670_REG_RSVD_45  0xBC // Reserved...
#define OV7670_REG_RSVD_46  0xBD // Reserved...
#define OV7670_REG_AD_CHB   0xBE // ADC offset value & sign bit
#define OV7670_REG_AD_CHR   0xBF // ADC offset value & sign bit
#define OV7670_REG_AD_CHGb  0xC0 // ADC offset value & sign bit
#define OV7670_REG_AD_CHGr  0xC1 // ADC offset value & sign bit
#define OV7670_REG_RSVD_47  0xC2 // Reserved...
#define OV7670_REG_RSVD_48  0xC3 // Reserved...
#define OV7670_REG_RSVD_49  0xC4 // Reserved...
#define OV7670_REG_RSVD_50  0xC5 // Reserved...
#define OV7670_REG_RSVD_51  0xC6 // Reserved...
#define OV7670_REG_RSVD_52  0xC7 // Reserved...
#define OV7670_REG_RSVD_53  0xC8 // Reserved...
#define OV7670_REG_SATCTR   0xC9 // Saturation control

#endif /* JEDGE_OV7670_H_ */
