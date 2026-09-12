// Lesson 2 - GPIO: same as gpio_vd1.c but using push-pull mode instead of quasi-bidirectional.
#include <stdint.h>
#include <mcs51/N76E885.h>
#include <mcs51/Define.h>

#define LED1    P04
#define ON_LED  0
#define OFF_LED 1

void delay1ms(uint16_t duration) {
    for (; duration > 0; duration--) {
        uint16_t i = 1700;
        while (--i);
    }
}

void main(void) {
    // P0.4 (LED1) push-pull mode (P0M1.4 = 0, P0M2.4 = 1)
    P0M1 &= CLR_BIT4;
    P0M2 |= SET_BIT4;

    LED1 = OFF_LED;

    while (1) {
        LED1 = ON_LED;
        delay1ms(500);
        LED1 = OFF_LED;
        delay1ms(500);
    }
}
