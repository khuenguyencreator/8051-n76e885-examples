// Lesson 4 - Timer 2 compare mode, prescaler 1/1, delay1ms() polls the TF2 flag.
#include <stdint.h>
#include <mcs51/N76E885.h>
#include <mcs51/Define.h>

#define LED1    P04
#define ON_LED  0
#define OFF_LED 1

void delay1ms(uint16_t duration) {
    CM_RL2 = 1;          // compare mode
    T2MOD &= CLR_BIT6 & CLR_BIT5 & CLR_BIT4;    // prescaler = 1/1 (T2DIV[2:0] = 000)
    T2MOD |= SET_BIT2;   // auto-clear on compare match
    RCMP2H = HIBYTE(22118);
    RCMP2L = LOBYTE(22118);
    TR2 = 1;
    for (; duration > 0; duration--) {
        while (!TF2);    // wait for compare match
        TF2 = 0;
    }
    TR2 = 0;
}

void main(void) {
    // P0.4 (LED1) quasi-bidirectional mode
    P0M1 &= CLR_BIT4;
    P0M2 &= CLR_BIT4;

    LED1 = OFF_LED;

    while (1) {
        LED1 = !LED1;
        delay1ms(500);
    }
}
