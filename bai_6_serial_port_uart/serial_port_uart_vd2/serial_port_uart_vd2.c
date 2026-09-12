// Lesson 6 - UART1, 19200 baud, TX/RX: type 'y'/'n' over UART to turn the LED on/off.
#include <stdint.h>
#include <mcs51/N76E885.h>
#include <mcs51/Define.h>

#define LED1    P04
#define ON_LED  0
#define OFF_LED 1

void main(void) {
    // P0.4 (LED1) quasi-bidirectional mode
    P0M1 &= CLR_BIT4;
    P0M2 &= CLR_BIT4;
    LED1 = OFF_LED;

    // P2.4 (RXD_1) bi-directional mode
    P2M1 &= CLR_BIT4;
    P2M2 &= CLR_BIT4;
    P24 = 1;

    // P2.5 (TXD_1) bi-directional mode
    P2M1 &= CLR_BIT5;
    P2M2 &= CLR_BIT5;
    P25 = 1;

    // UART1: mode 1 - 8-bit UART
    SM0_1 = 0;
    SM1_1 = 1;
    REN_1 = 1;    // enable reception
    TI_1 = 1;     // ready for the first transmission

    // Baud rate = 19200 (SMOD = PCON.7 = 0, normal speed, no doubling)
    T3CON &= CLR_BIT7;
    // reload value = 65536 - 1/16 * Fsys / prescale / Baud
    RH3 = HIBYTE(65464);
    RL3 = LOBYTE(65464);
    T3CON |= SET_BIT3;    // run Timer 3

    while (1) {
        if (RI_1) {
            uint8_t key = SBUF_1;
            RI_1 = 0;
            switch (key) {
                case 'y':
                    LED1 = ON_LED;
                    break;
                case 'n':
                    LED1 = OFF_LED;
                    break;
                default:;
            }
        }
    }
}
