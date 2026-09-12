// Lesson 4 - Timer 3, prescaler 1/128, delay100ms() polls the TF3 overflow flag (T3CON bit 4).
#include <stdint.h>
#include <mcs51/N76E885.h>
#include <mcs51/Define.h>

#define LED1    P04
#define ON_LED  0
#define OFF_LED 1

void delay100ms(uint16_t duration) {
    T3CON |= SET_BIT2 | SET_BIT1 | SET_BIT0;    // prescaler = 1/128
    RH3 = HIBYTE(65536 - 17280);
    RL3 = LOBYTE(65536 - 17280);
    T3CON |= SET_BIT3;    // run
    for (; duration > 0; duration--) {
        while (!(T3CON & SET_BIT4));    // wait for TF3
        T3CON &= CLR_BIT4;    // clear TF3
    }
    T3CON &= CLR_BIT3;    // stop
}

void main(void) {
    // P0.4 (LED1) quasi-bidirectional mode
    P0M1 &= CLR_BIT4;
    P0M2 &= CLR_BIT4;

    LED1 = OFF_LED;

    while (1) {
        LED1 = !LED1;
        delay100ms(5);
    }
}
