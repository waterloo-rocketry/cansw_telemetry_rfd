/*
 * File:   spi.c
 * Author: Manav
 *
 * Created on February 20, 2025, 1:14 PM
 */

#include "spi.h"

void SPI_Init() {
    // Set Pins as outputs
    TRISCbits.TRISC3 = 0; // SCLK 
    TRISCbits.TRISC4 = 1; // MISO (input)
    TRISCbits.TRISC5 = 0; // MOSI
    TRISAbits.TRISA5 = 0; // CS
    
    LATAbits.LATA5 = 1; // Set CS high
    
    SPI1CON0bits.EN = 0; // Disable SPI to configure settings
    
    SPI1CON0bits.MST = 1; // Operate as Master
    SPI1CON0bits.LSBF = 0; // MSB First
    
    SPI1CON1bits.CKP = 0; // SCLK idles low
    SPI1CON1bits.CKE = 0; // Change data on falling edge
    
    // Full Duplex Mode
    SPI1CON2bits.TXR = 1;
    SPI1CON2bits.RXR = 1;
    
    // Clock Speed
    SPI1BAUD = 0; // (12 MHz / 2*(0+1)) = 6 MHz
    
    
    SPI1CON0bits.EN = 1; // Enable SPI
    
}

uint8_t Read_SPI() {
    uint8_t data;
    // Wait for RX buffer to be full
    while(!SPI1STATUSbits.RXBF);
    data = SPI1RXB;
    return data;
}

void Write_SPI(uint8_t data) {
    // Wait for TX buffer to be empty
    while (SPI1STATUSbits.TXBE);
    SPI1TXB = data;
}
