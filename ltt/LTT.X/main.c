/*
 * File:   main.c
 * Author: Manav
 *
 * Created on January 29, 2025, 12:06 PM
 */

#include "stdbool.h"

#include "CONFIG.h"
#include "adc.h"
#include "spi.h"

#define _XTAL_FREQ 12000000 // 12 MHz

void LEDs_Init() {
    // Set LEDs as output
    TRISAbits.TRISA2 = 0; // green
    TRISAbits.TRISA3 = 0; // blue
    TRISAbits.TRISA4 = 0; // red
}

void toggle_LEDs(bool red, bool blue, bool green) {
    LATA2 = 1;
    LATA3 = 1;
    LATA4 = 1;
    
    red = ~red;
    blue = ~blue;
    green = ~green;
    
    LATA2 = red;
    LATA3 = blue;
    LATA4 = green;
            
    __delay_ms(500);
}

void main(void) {
    LEDs_Init();
    ADC_Init();
    
    while (1) {
        read_ADC();
        
        toggle_LEDs(0, 0, 0);
        toggle_LEDs(1, 0, 0);
        toggle_LEDs(0, 1, 0);
        toggle_LEDs(0, 0, 1);
        toggle_LEDs(1, 1, 1);
        toggle_LEDs(0, 0, 0);
        toggle_LEDs(1, 1, 1);
        toggle_LEDs(0, 0, 0);
        toggle_LEDs(1, 1, 1);
        toggle_LEDs(0, 0, 0);
        
    }
    
    return;
}
