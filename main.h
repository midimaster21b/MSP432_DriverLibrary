/*
 * main.h
 *
 *  Created on: July 5, 2018
 *      Author: Joshua Edgcombe
 */

#ifndef JEDGE_MAIN_H_
#define JEDGE_MAIN_H_

// Number of samples to be taken in each buffer
#define NUM_SAMPLES 4000

// Define buffer full flags
#define BUFFER_HANDLED 0
#define BUFFER_A_FULL 1
#define BUFFER_B_FULL 2

// Average calculation function
float calculate_average(uint16_t *buffer);

#endif /* JEDGE_MAIN_H_ */
