// Lesson 6 - UART1 (SCON_1/SBUF_1), 19200 baud, TX only: send "Hello, world!" once.
#include <stdint.h>
#include <mcs51/N76E885.h>
#include <mcs51/Define.h>

void main(void) {
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

    uint8_t const str[] = "Hello, world!";

    for (uint8_t i = 0; str[i] != 0; ++i) {
        while (!TI_1);
        TI_1 = 0;
        SBUF_1 = str[i];
    }

    while (1) {
        // nothing to do
    }
}
