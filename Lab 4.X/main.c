/*
 * File:   main.c
 * Author: ponti
 *
 * Created on March 2, 2022, 9:13 AM
 */
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 2000000 //Crystal Oscillator Frequency

//#include "osc_config.h"
//#include <pic16F866.h>

#include <xc.h>

void main(void) {

    // P1C = RB1 is output pin
    
    // Set PORTB as output
    TRISB = 0x0;
    // Set PORTB as High
    PORTB = 0x0;
    
    // Clear Analog Select Register
    ANSEL = 0x0;
    // Clear Analog Select High Register
    ANSELH = 0x0;
    
    // Enhanced CCP1 Control Register
    // Select output mode
    CCP1CONbits.CCP1M3 = 1; //  Select Single Output Mode
    CCP1CONbits.CCP1M2 = 1; //  Select Single Output Mode
    CCP1CONbits.P1M = 0b00; // Single output; P1A modulated; P1B, P1C, P1D assigned as port pins    
    
    // Set duty cycle
    CCPR1L = 20; // 50% Duty Cycle
    
    // PWM Frequency, 
    PR2 = 0x65; // 19.61 kHz
    
    // Timer2 Control Register
    T2CONbits.TOUTPS = 0b0000; // Postscalar is 1:16
    T2CONbits.TMR2ON = 1; // timer2 on bit
    T2CONbits.T2CKPS = 0b0; // Prescalar is 16
    
    // Set global interrupt, and peripheral interrupt flags
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    
    // PSTRCON set steering
    PSTRCONbits.STRC = 1; // Set P1C as PWM waveform with polarity control from CCPxM<1:0>
    


    while(1); 
    
    return;
}
