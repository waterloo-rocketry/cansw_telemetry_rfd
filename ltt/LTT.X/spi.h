/*
 * File:   spi.h
 * Author: Manav
 *
 * Created on February 20, 2025, 1:13 PM
 */

#ifndef SPI_H
#define SPI_H

#include "CONFIG.h"

void SPI_Init(void);

uint8_t Read_SPI(void);

void Write_SPI(uint8_t);

#endif
