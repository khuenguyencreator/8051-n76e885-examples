// Lesson 10 - SPI master (SPCR/SPSR/SPDR) driving a 25Q80 SPI NOR flash: read JEDEC ID, erase,
// write, read back, and report over UART1 (reusing lesson 6's UART setup).
#include <stdint.h>
#include <mcs51/N76E885.h>
#include <mcs51/Define.h>

#define CS SS    // chip select (P0.4), manual GPIO since DISMODF disables the SPI's own SS logic

#define CMD_WRITE_ENABLE  0x06
#define CMD_SECTOR_ERASE  0x20
#define CMD_PAGE_PROGRAM  0x02
#define CMD_READ_DATA     0x03
#define CMD_READ_STATUS1  0x05
#define CMD_JEDEC_ID      0x9F

uint8_t const test_data[] = "Hello N76E885!";
#define TEST_ADDR 0x000000UL

void delay1ms(uint16_t duration) {
    for (; duration > 0; duration--) {
        uint16_t i = 1700;
        while (--i);
    }
}

uint8_t spi_transfer(uint8_t data) {
    SPDR = data;
    while (!(SPSR & SET_BIT7));    // wait for SPIF (transfer complete)
    SPSR &= CLR_BIT7;              // clear SPIF
    return SPDR;
}

void flash_write_enable(void) {
    CS = 0;
    spi_transfer(CMD_WRITE_ENABLE);
    CS = 1;
}

// Poll the status register until the Write-In-Progress bit clears.
void flash_wait_ready(void) {
    uint8_t status;

    do {
        CS = 0;
        spi_transfer(CMD_READ_STATUS1);
        status = spi_transfer(0xFF);
        CS = 1;
    } while (status & 0x01);
}

void flash_read_id(uint8_t *mfg, uint8_t *memtype, uint8_t *capacity) {
    CS = 0;
    spi_transfer(CMD_JEDEC_ID);
    *mfg = spi_transfer(0xFF);
    *memtype = spi_transfer(0xFF);
    *capacity = spi_transfer(0xFF);
    CS = 1;
}

void flash_erase_sector(uint32_t addr) {
    flash_write_enable();
    CS = 0;
    spi_transfer(CMD_SECTOR_ERASE);
    spi_transfer((uint8_t)(addr >> 16));
    spi_transfer((uint8_t)(addr >> 8));
    spi_transfer((uint8_t)addr);
    CS = 1;
    flash_wait_ready();
}

void flash_write_bytes(uint32_t addr, uint8_t const *data, uint8_t len) {
    uint8_t i;

    flash_write_enable();
    CS = 0;
    spi_transfer(CMD_PAGE_PROGRAM);
    spi_transfer((uint8_t)(addr >> 16));
    spi_transfer((uint8_t)(addr >> 8));
    spi_transfer((uint8_t)addr);
    for (i = 0; i < len; i++) {
        spi_transfer(data[i]);
    }
    CS = 1;
    flash_wait_ready();
}

void flash_read_bytes(uint32_t addr, uint8_t *buf, uint8_t len) {
    uint8_t i;

    CS = 0;
    spi_transfer(CMD_READ_DATA);
    spi_transfer((uint8_t)(addr >> 16));
    spi_transfer((uint8_t)(addr >> 8));
    spi_transfer((uint8_t)addr);
    for (i = 0; i < len; i++) {
        buf[i] = spi_transfer(0xFF);
    }
    CS = 1;
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

void uart_send_hex_byte(uint8_t value) {
    uint8_t digit = value >> 4;
    uart_send_byte(digit > 9 ? 'A' + (digit - 10) : '0' + digit);
    digit = value & 0x0F;
    uart_send_byte(digit > 9 ? 'A' + (digit - 10) : '0' + digit);
}

void main(void) {
    uint8_t mfg, memtype, capacity;
    uint8_t readback[sizeof(test_data)];
    uint8_t i, ok;

    // MOSI (P2.1) / SPICK (P0.5) push-pull outputs
    P2M1 &= CLR_BIT1;
    P2M2 |= SET_BIT1;
    P0M1 &= CLR_BIT5;
    P0M2 |= SET_BIT5;

    // MISO (P2.2) input
    P2M1 &= CLR_BIT2;
    P2M2 &= CLR_BIT2;
    P22 = 1;

    // SS/CS (P0.4) push-pull output, idle high (chip not selected)
    P0M1 &= CLR_BIT4;
    P0M2 |= SET_BIT4;
    CS = 1;

    SPSR |= SET_BIT3;    // DISMODF = 1: SS follows SSOE (kept as plain GPIO, driven by us)
    SPCR = SET_BIT6 | SET_BIT4 | SET_BIT1 | SET_BIT0;    // SPIEN=1, MSTR=1, SPR[1:0]=11 (slowest), CPOL=0, CPHA=0

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

    delay1ms(10);    // let the flash chip finish its own power-up

    flash_read_id(&mfg, &memtype, &capacity);
    uart_send_string((uint8_t const *)"JEDEC ID: ");
    uart_send_hex_byte(mfg);
    uart_send_byte(' ');
    uart_send_hex_byte(memtype);
    uart_send_byte(' ');
    uart_send_hex_byte(capacity);
    uart_send_string((uint8_t const *)"\r\n");

    flash_erase_sector(TEST_ADDR);
    flash_write_bytes(TEST_ADDR, test_data, sizeof(test_data));
    flash_read_bytes(TEST_ADDR, readback, sizeof(test_data));

    ok = 1;
    for (i = 0; i < sizeof(test_data); i++) {
        if (readback[i] != test_data[i]) {
            ok = 0;
            break;
        }
    }
    uart_send_string(ok ? (uint8_t const *)"Write/Read OK\r\n" : (uint8_t const *)"MISMATCH\r\n");

    while (1) {
        // nothing else to do
    }
}
