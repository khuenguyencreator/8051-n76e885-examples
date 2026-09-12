// Lesson 2 - GPIO: share one pin (P0.4) as both LED (output) and push button (input).
#include <stdint.h>
#include <mcs51/N76E885.h>
#include <mcs51/Define.h>

#define LED1     P04
#define ON_LED   0
#define OFF_LED  1

#define BTN      P04
#define PRESSED  0

void delay1ms(uint16_t duration) {
    for (; duration > 0; duration--) {
        uint16_t i = 1700;
        while (--i);
    }
}

void main(void) {
    // P0.4 (LED1/BTN) quasi-bidirectional mode
    P0M1 &= CLR_BIT4;
    P0M2 &= CLR_BIT4;

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

            BTN = 1;    // switch back to input
        }
    }
}
