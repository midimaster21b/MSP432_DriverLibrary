/*
 * jedge_adc.h
 *
 *  Created on: Jun 28, 2018
 *      Author: Joshua Edgcombe
 */

#ifndef JEDGE_ADC_H_
#define JEDGE_ADC_H_

#include "msp.h"

#define ADC_PORT P4
#define ADC_PIN  4
#define ADC_MASK 1 << ADC_PIN

void ADC_init(void);
void ADC_start_conversion(void);
void ADC_stop_conversions(void);
uint16_t ADC_get_result(void);

#endif /* JEDGE_ADC_H_ */
