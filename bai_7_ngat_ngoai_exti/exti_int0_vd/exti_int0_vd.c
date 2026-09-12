// Lesson 7 - External interrupt INT0 (P0.0): toggle the LED on falling edge, no polling in main().
#include <stdint.h>
#include <mcs51/N76E885.h>
#include <mcs51/Define.h>

#define LED1    P04
#define ON_LED  0
#define OFF_LED 1

void ext0_isr(void) __interrupt(0) {
    LED1 = !LED1;
}

void main(void) {
    // P0.4 (LED1) quasi-bidirectional mode
    P0M1 &= CLR_BIT4;
    P0M2 &= CLR_BIT4;
    LED1 = OFF_LED;

    // P0.0 (INT0/button) quasi-bidirectional mode
    P0M1 &= CLR_BIT0;
    P0M2 &= CLR_BIT0;
    P00 = 1;    // use as input

    IT0 = 1;    // INT0 falling-edge triggered (TCON.0)
    EX0 = 1;    // enable External Interrupt 0
    EA = 1;     // enable global interrupts

    while (1) {
        // everything happens in ext0_isr
    }
}
