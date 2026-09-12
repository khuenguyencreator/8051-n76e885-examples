// Lesson 3 - Timer 0 Mode 1 (16-bit), clocked from the 32.768 kHz sub-crystal, accurate delay1sec().
#include <stdint.h>
#include <mcs51/N76E885.h>
#include <mcs51/Define.h>

#define LED1    P04
#define ON_LED  0
#define OFF_LED 1

void delay1sec(uint16_t duration) {
    TMOD &= CLR_BIT3 & CLR_BIT2 & CLR_BIT1 & CLR_BIT0;    // clear TMOD low nibble
    TMOD |= SET_BIT0;    // Timer 0: GATE = 0, C/T = 0, mode 1
    AUXR1 |= SET_BIT4;   // clock source = 32.768 kHz crystal
    for (; duration > 0; duration--) {
        TH0 = HIBYTE(32768);
        TL0 = LOBYTE(32768);
        TR0 = 1;         // run
        while (!TF0);    // wait for overflow
        TR0 = 0;         // stop
        TF0 = 0;         // clear overflow flag
    }
}

void main(void) {
    // P0.4 (LED1) quasi-bidirectional mode
    P0M1 &= CLR_BIT4;
    P0M2 &= CLR_BIT4;

    LED1 = OFF_LED;

    // enable the 32.768 kHz crystal (TA-protected register)
    uint8_t tmp = CKEN;
    tmp &= CLR_BIT7;
    tmp |= SET_BIT6;
    TA = 0xaa;
    TA = 0x55;
    CKEN = tmp;

    while (1) {
        LED1 = !LED1;
        delay1sec(2);
    }
}
