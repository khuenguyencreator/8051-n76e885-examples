// Lesson 11 - 1-Wire (bit-banged on GPIO, N76E885 has no hardware 1-Wire module) talking to a
// DS18B20 temperature sensor, result printed over UART1 (reusing lesson 6's UART setup).
#include <stdint.h>
#include <mcs51/N76E885.h>
#include <mcs51/Define.h>

#define DQ P12    // 1-Wire data pin

// NOTE: this delay loop is a rough, compiler/clock-dependent approximation, not a
// cycle-accurate microsecond delay. 1-Wire/DS18B20 timing has some tolerance, but if
// communication fails on real hardware (ow_reset() always returns "no presence"), re-tune
// the constant below with a logic analyzer/oscilloscope, or replace this with a hardware
// timer-based delay.
void delay_us(uint16_t us) {
    while (us--) {
        uint8_t i = 5;
        while (--i);
    }
}

void delay1ms(uint16_t duration) {
    for (; duration > 0; duration--) {
        uint16_t i = 1700;
        while (--i);
    }
}

// Reset pulse + presence detect. Returns 1 if a device answered, 0 otherwise.
uint8_t ow_reset(void) {
    uint8_t presence;

    DQ = 0;
    delay_us(480);
    DQ = 1;
    delay_us(60);
    presence = !DQ;    // the device pulls DQ low during the presence pulse
    delay_us(420);

    return presence;
}

void ow_write_bit(uint8_t bit) {
    DQ = 0;
    if (bit) {
        delay_us(6);
        DQ = 1;
        delay_us(64);
    } else {
        delay_us(60);
        DQ = 1;
        delay_us(10);
    }
}

uint8_t ow_read_bit(void) {
    uint8_t bit;

    DQ = 0;
    delay_us(2);
    DQ = 1;
    delay_us(8);
    bit = DQ;
    delay_us(50);

    return bit;
}

void ow_write_byte(uint8_t byte) {
    uint8_t i;

    for (i = 0; i < 8; i++) {
        ow_write_bit(byte & 0x01);
        byte >>= 1;
    }
}

uint8_t ow_read_byte(void) {
    uint8_t i, byte = 0;

    for (i = 0; i < 8; i++) {
        byte >>= 1;
        if (ow_read_bit()) {
            byte |= 0x80;
        }
    }

    return byte;
}

void uart_send_byte(uint8_t byte) {
    while (!TI_1);
    TI_1 = 0;
    SBUF_1 = byte;
}

void uart_send_string(uint8_t const *str) {
    while (*str) {
        uart_send_byte(*str++);
    }
}

// Print an 8-bit value (0-255) as decimal, no leading zeros.
void uart_send_uint8(uint8_t value) {
    if (value >= 100) {
        uart_send_byte('0' + value / 100);
        value %= 100;
        uart_send_byte('0' + value / 10);
    } else if (value >= 10) {
        uart_send_byte('0' + value / 10);
    }
    uart_send_byte('0' + value % 10);
}

// DS18B20 "Convert T" + "Read Scratchpad" (Skip ROM, only works with a single device on the bus).
// Returns the temperature in units of 1/16 degree C (12-bit resolution, DS18B20 default).
int16_t ds18b20_read_temp_raw(void) {
    uint8_t lsb, msb;

    ow_reset();
    ow_write_byte(0xCC);    // Skip ROM
    ow_write_byte(0x44);    // Convert T
    delay1ms(750);          // max conversion time at 12-bit resolution

    ow_reset();
    ow_write_byte(0xCC);    // Skip ROM
    ow_write_byte(0xBE);    // Read Scratchpad
    lsb = ow_read_byte();
    msb = ow_read_byte();

    return (int16_t)((msb << 8) | lsb);
}

void main(void) {
    // P1.2 (DQ) open-drain, required by the 1-Wire bus (external pull-up resistor to VDD)
    P1M1 |= SET_BIT2;
    P1M2 |= SET_BIT2;
    DQ = 1;

    // UART1, 19200 baud (see lesson 6 for details)
    P2M1 &= CLR_BIT4;
    P2M2 &= CLR_BIT4;
    P24 = 1;
    P2M1 &= CLR_BIT5;
    P2M2 &= CLR_BIT5;
    P25 = 1;
    SM0_1 = 0;
    SM1_1 = 1;
    REN_1 = 1;
    TI_1 = 1;
    T3CON &= CLR_BIT7;
    RH3 = HIBYTE(65464);
    RL3 = LOBYTE(65464);
    T3CON |= SET_BIT3;

    while (1) {
        int16_t raw = ds18b20_read_temp_raw();
        uint8_t negative = 0;
        uint16_t whole, frac_tenths;

        if (raw < 0) {
            negative = 1;
            raw = -raw;
        }
        whole = (uint16_t)raw >> 4;
        frac_tenths = (((uint16_t)raw & 0x0F) * 625 + 500) / 1000;    // max 9, rounding never carries into whole

        if (negative) {
            uart_send_byte('-');
        }
        uart_send_uint8((uint8_t)whole);
        uart_send_byte('.');
        uart_send_byte('0' + frac_tenths);
        uart_send_string((uint8_t const *)" C\r\n");

        delay1ms(1000);
    }
}
