// Lesson 3 - Timer 0 Mode 2 (8-bit auto-reload) with T0OE: hardware auto-toggles P2.0 on overflow.
#include <stdint.h>
#include <mcs51/N76E885.h>
#include <mcs51/Define.h>

void main(void) {
    // P2.0 (T0) quasi-bidirectional mode
    P2M1 &= CLR_BIT0;
    P2M2 &= CLR_BIT0;

    P20 = 1;    // release the pin to the timer's logic level

    // enable Timer 0 output toggle on P2.0 (T0OE bit in P1M1, see N76E885 datasheet)
    P1M1 |= SET_BIT2;

    // configure Timer 0
    TMOD &= CLR_BIT3 & CLR_BIT2 & CLR_BIT1 & CLR_BIT0;    // clear TMOD low nibble
    TMOD |= SET_BIT1;    // Timer 0: GATE = 0, C/T = 0, mode 2
    CKCON |= SET_BIT3;   // clock = Fsys, prescaler = 1/1
    TH0 = 145;           // reload value
    TR0 = 1;             // run

    while (1) {
        // nothing to do, the pin toggles in hardware
    }
}
