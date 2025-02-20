/*
 * File:   adc.h
 * Author: Manav
 *
 * Created on February 20, 2025, 1:06 PM
 */

#ifndef ADC_H
#define ADC_H

#include "CONFIG.h"

void ADC_Init(void);

uint16_t read_ADC(void);

#endif