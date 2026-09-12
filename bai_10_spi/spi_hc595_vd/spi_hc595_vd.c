// Lesson 10 - SPI master (SPCR/SPSR/SPDR) driving a 74HC595 shift register: 8 LEDs running light.
#include <stdint.h>
#include <mcs51/N76E885.h>
#include <mcs51/Define.h>

#define RCLK P10    // 74HC595 latch clock (RCLK/ST_CP), driven manually, not part of the SPI pins

void delay1ms(uint16_t duration) {
    for (; duration > 0; duration--) {
        uint16_t i = 1700;
        while (--i);
    }
}

// Transfer one byte both ways; the received byte is discarded here (no MISO device wired).
uint8_t spi_transfer(uint8_t data) {
    SPDR = data;
    while (!(SPSR & SET_BIT7));    // wait for SPIF (transfer complete)
    SPSR &= CLR_BIT7;              // clear SPIF
    return SPDR;
}

void hc595_write(uint8_t data) {
    spi_transfer(data);    // shift 8 bits into the 74HC595 (SER/SRCLK)
    RCLK = 1;               // latch the shifted byte onto Q0-Q7
    RCLK = 0;
}

void main(void) {
    uint8_t pattern;

    // MOSI (P2.1) / SPICK (P0.5) push-pull outputs
    P2M1 &= CLR_BIT1;
    P2M2 |= SET_BIT1;
    P0M1 &= CLR_BIT5;
    P0M2 |= SET_BIT5;

    // MISO (P2.2) input, unused by the 74HC595 (it has no data-out pin)
    P2M1 &= CLR_BIT2;
    P2M2 &= CLR_BIT2;
    P22 = 1;

    // RCLK (P1.0) push-pull output
    P1M1 &= CLR_BIT0;
    P1M2 |= SET_BIT0;
    RCLK = 0;

    SPSR |= SET_BIT3;    // DISMODF = 1: SS (P0.4) becomes a plain GPIO, unused in this example
    SPCR = SET_BIT6 | SET_BIT4 | SET_BIT1 | SET_BIT0;    // SPIEN=1, MSTR=1, SPR[1:0]=11 (slowest), CPOL=0, CPHA=0

    pattern = 0x01;

    while (1) {
        hc595_write(pattern);
        delay1ms(150);
        pattern <<= 1;
        if (pattern == 0) {
            pattern = 0x01;
        }
    }
}
