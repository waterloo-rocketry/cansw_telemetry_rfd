/*
 * File:   adc.c
 * Author: Manav
 *
 * Created on February 20, 2025, 1:06 PM
 */

// Read current draw value on board

#include "adc.h"

void ADC_Init() {
    ADCON0bits.FM = 1; // right justify
    ADCON0bits.CS = 1; // FRC Clock (dedicated RC oscillator))
    ADPCH = 0x00; // A0 is Analog channel
    TRISAbits.TRISA0 = 1; // Set RA0 to input
    ANSELAbits.ANSELA0 = 1; // Set RA0 to analog
    ADCON0bits.ON = 1; // Turn ADC On
}

uint16_t read_ADC() {
    ADCON0bits.GO = 1; // Start conversation
    while (ADCON0bits.GO); // Wait for conversation to be done
    uint16_t result = ((uint16_t)ADRESH << 8) | ADRESL; // combine two registers into one integer
    
    return result;
}