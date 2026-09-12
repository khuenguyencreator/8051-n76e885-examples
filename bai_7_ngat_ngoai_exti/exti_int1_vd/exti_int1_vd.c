// Lesson 7 - External interrupt INT1 (P0.1): count pulses in the ISR, blink the LED that many
// times every 3 seconds in main(). Shows how to keep an ISR short and hand data off to main().
#include <stdint.h>
#include <mcs51/N76E885.h>
#include <mcs51/Define.h>

#define LED1    P04
#define ON_LED  0
#define OFF_LED 1

volatile uint8_t pulse_count = 0;

void delay1ms(uint16_t duration) {
    for (; duration > 0; duration--) {
        uint16_t i = 1700;
        while (--i);
    }
}

void ext1_isr(void) __interrupt(2) {
    pulse_count++;
}

void main(void) {
    // P0.4 (LED1) quasi-bidirectional mode
    P0M1 &= CLR_BIT4;
    P0M2 &= CLR_BIT4;
    LED1 = OFF_LED;

    // P0.1 (INT1/pulse input) quasi-bidirectional mode
    P0M1 &= CLR_BIT1;
    P0M2 &= CLR_BIT1;
    P01 = 1;    // use as input

    IT1 = 1;    // INT1 falling-edge triggered (TCON.2)
    EX1 = 1;    // enable External Interrupt 1
    EA = 1;     // enable global interrupts

    while (1) {
        delay1ms(3000);

        // briefly disable interrupts to read and reset the shared counter safely
        EA = 0;
        uint8_t count = pulse_count;
        pulse_count = 0;
        EA = 1;

        for (uint8_t i = 0; i < count; i++) {
            LED1 = ON_LED;
            delay1ms(150);
            LED1 = OFF_LED;
            delay1ms(150);
        }
    }
}
