// Lesson 2 - GPIO: add a push button on P0.0 (input), press it to blink the LED 3 times fast.
#include <stdint.h>
#include <mcs51/N76E885.h>
#include <mcs51/Define.h>

#define LED1     P04
#define ON_LED   0
#define OFF_LED  1

#define BTN      P00
#define PRESSED  0

void delay1ms(uint16_t duration) {
    for (; duration > 0; duration--) {
        uint16_t i = 1700;
        while (--i);
    }
}

void main(void) {
    // P0.4 (LED1) quasi-bidirectional mode
    P0M1 &= CLR_BIT4;
    P0M2 &= CLR_BIT4;

    LED1 = OFF_LED;

    // P0.0 (BTN) quasi-bidirectional mode
    P0M1 &= CLR_BIT0;
    P0M2 &= CLR_BIT0;

    BTN = 1;    // use as input

    while (1) {
        if (BTN == PRESSED) {
            while (BTN == PRESSED);    // wait until released

            delay1ms(1000);

            LED1 = ON_LED;
            delay1ms(200);
            LED1 = OFF_LED;
            delay1ms(200);

            LED1 = ON_LED;
            delay1ms(200);
            LED1 = OFF_LED;
            delay1ms(200);

            LED1 = ON_LED;
            delay1ms(200);
            LED1 = OFF_LED;
            delay1ms(200);
        }
    }
}
