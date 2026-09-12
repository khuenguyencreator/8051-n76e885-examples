// Lesson 8 - I2C master (I2CON/I2DAT/I2STAT/I2CLK) talking to a DS3231 RTC.
// SDA is fixed to P2.3 and SCL to P0.6 on the N76E885 I2C module (cannot be remapped).
#include <stdint.h>
#include <mcs51/N76E885.h>
#include <mcs51/Define.h>

#define LED1    P04
#define ON_LED  0
#define OFF_LED 1

#define DS3231_ADDR 0x68

void delay1ms(uint16_t duration) {
    for (; duration > 0; duration--) {
        uint16_t i = 1700;
        while (--i);
    }
}

// Generate a START (or repeated START) condition and wait for it (I2STAT = 0x08 / 0x10).
void i2c_start(void) {
    STA = 1;
    while (!SI);
    STA = 0;
}

// Generate a STOP condition; hardware clears STO by itself once it is on the bus.
void i2c_stop(void) {
    STO = 1;
    SI = 0;
    while (STO);
}

// Send one byte (slave address+R/W, or a data byte) and wait for the ACK/NACK cycle to finish.
// Expected status after this: 0x18/0x28 (ACK) or 0x20/0x30 (NACK) for a write, 0x40/0x48 for SLA+R.
void i2c_write(uint8_t data) {
    I2DAT = data;
    SI = 0;
    while (!SI);
}

// Read one byte. ack = 1 sends ACK (more bytes follow), ack = 0 sends NACK (last byte).
uint8_t i2c_read(uint8_t ack) {
    AA = ack;
    SI = 0;
    while (!SI);
    return I2DAT;
}

uint8_t bcd2dec(uint8_t bcd) {
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

uint8_t dec2bcd(uint8_t dec) {
    return ((dec / 10) << 4) | (dec % 10);
}

// Write hour:minute:second once (registers 0x00-0x02), 24-hour format.
void ds3231_set_time(uint8_t hour, uint8_t minute, uint8_t second) {
    i2c_start();
    i2c_write((uint8_t)(DS3231_ADDR << 1));    // SLA+W
    i2c_write(0x00);                           // start at register 0x00 (seconds)
    i2c_write(dec2bcd(second));
    i2c_write(dec2bcd(minute));
    i2c_write(dec2bcd(hour));             // bit 6 = 0 -> 24-hour mode
    i2c_stop();
}

// Read the seconds register (0x00) with a repeated START between the write and read phases.
uint8_t ds3231_read_seconds(void) {
    uint8_t second;

    i2c_start();
    i2c_write((uint8_t)(DS3231_ADDR << 1));          // SLA+W
    i2c_write(0x00);                                 // point to register 0x00 (seconds)
    i2c_start();                                     // repeated START, switch to read
    i2c_write((uint8_t)((DS3231_ADDR << 1) | 1));    // SLA+R
    second = i2c_read(0);                 // read 1 byte, NACK (no more bytes wanted)
    i2c_stop();

    return bcd2dec(second & 0x7F);        // bit 7 of the seconds register is unused
}

void main(void) {
    // P0.4 (LED1) quasi-bidirectional mode
    P0M1 &= CLR_BIT4;
    P0M2 &= CLR_BIT4;
    LED1 = OFF_LED;

    // SDA (P2.3) / SCL (P0.6) must be open-drain with latches set high before enabling I2C
    P2M1 |= SET_BIT3;
    P2M2 |= SET_BIT3;
    P23 = 1;
    P0M1 |= SET_BIT6;
    P0M2 |= SET_BIT6;
    P06 = 1;

    I2CLK = 0x36;    // bit rate = Fsys / (4*(I2CLK+1)), ~100kHz at Fsys ~22.1184MHz (default HIRC)
    I2CEN = 1;       // enable the I2C module

    ds3231_set_time(10, 30, 0);    // set the RTC once at startup: 10:30:00

    while (1) {
        uint8_t second = ds3231_read_seconds();
        LED1 = (second % 2 == 0) ? ON_LED : OFF_LED;    // toggle LED each second, driven by the RTC
        delay1ms(200);
    }
}
