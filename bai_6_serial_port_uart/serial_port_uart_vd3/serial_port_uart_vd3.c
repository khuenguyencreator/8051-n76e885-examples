// Lesson 6 - Combine input capture (NEC IR decode, lesson 5) with UART: send the decoded hex code out.
#include <stdint.h>
#include <mcs51/N76E885.h>
#include <mcs51/Define.h>

#define STATE_INIT          0
#define STATE_BEG_START_BIT 1
#define STATE_MID_START_BIT 2
#define STATE_BEG_LOGIC_BIT 3
#define STATE_MID_LOGIC_BIT 4
#define STATE_BEG_STOP_BIT  5

typedef struct {
    uint8_t logic_bit : 7;
    uint8_t success : 1;
    uint8_t state;
    union {
        struct {
            uint8_t inverse_of_command;
            uint8_t command;
            uint8_t inverse_of_address;
            uint8_t address;
        };
        uint32_t full;
    } code;
} nec_t;

nec_t decode;    // decoded NEC frame

void necReset(void) {
    TR2 = 0;    // stop the timer
    CAPCON1 &= CLR_BIT5 & CLR_BIT4;    // capture channel 2 on falling edge
    decode.success = 0;
    decode.state = STATE_INIT;
}

void necHandler(void) {
    uint16_t capture = MAKEWORD(C2H, C2L);

    switch (decode.state) {
        case STATE_INIT:
            TR2 = 1;    // run the timer
            CAPCON1 |= SET_BIT5;    // capture channel 2 on either edge
            CAPCON1 &= CLR_BIT4;
            decode.state = STATE_BEG_START_BIT;
        break;

        case STATE_BEG_START_BIT:
            if ((capture >= 47000) && (capture <= 60825)) {
                decode.state = STATE_MID_START_BIT;
            } else {
                decode.state = STATE_INIT;
            }
        break;

        case STATE_MID_START_BIT:
            if ((capture >= 22118) && (capture <= 27648)) {
                decode.logic_bit = 0;
                decode.success = 0;
                decode.state = STATE_BEG_LOGIC_BIT;
            } else {
                decode.state = STATE_INIT;
            }
        break;

        case STATE_BEG_LOGIC_BIT:
            if ((capture >= 2212) && (capture <= 4424)) {
                decode.state = STATE_MID_LOGIC_BIT;
            } else {
                decode.state = STATE_INIT;
            }
        break;

        case STATE_MID_LOGIC_BIT:
            if ((capture >= 2212) && (capture <= 4424)) {
                ++decode.logic_bit;
                decode.code.full <<= 1;
            } else if ((capture >= 8294) && (capture <= 9953)) {
                ++decode.logic_bit;
                decode.code.full <<= 1;
                decode.code.inverse_of_command |= SET_BIT0;
            } else {
                decode.state = STATE_INIT;
                break;
            }
            if (decode.logic_bit == 32) {
                decode.state = STATE_BEG_STOP_BIT;
            } else {
                decode.state = STATE_BEG_LOGIC_BIT;
            }
        break;

        case STATE_BEG_STOP_BIT:
            if ((capture >= 2212) && (capture <= 4424)) {
                decode.success = 1;
            }
            decode.state = STATE_INIT;
        break;
    }

    if (decode.state == STATE_INIT) {
        TR2 = 0;    // stop the timer
        CAPCON1 &= CLR_BIT5 & CLR_BIT4;    // capture channel 2 on falling edge
    }
}

void number2TextHex(uint8_t *text_hex, uint8_t number) {
    uint8_t digit;

    digit = number >> 4;
    if (digit > 9) {
        text_hex[0] = 'A' + (digit - 10);
    } else {
        text_hex[0] = '0' + digit;
    }

    digit = number & 0x0f;
    if (digit > 9) {
        text_hex[1] = 'A' + (digit - 10);
    } else {
        text_hex[1] = '0' + digit;
    }
}

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

    // input capture channel 2 (P2.2) input
    P2M1 &= CLR_BIT2;
    P2M2 &= CLR_BIT2;
    P22 = 1;
    CAPCON0 |= SET_BIT6;    // enable channel 2
    CAPCON2 |= SET_BIT6;    // enable channel 2 noise filter
    CAPCON1 &= CLR_BIT5 & CLR_BIT4;    // capture on falling edge

    // Timer 2 setup
    T2MOD &= CLR_BIT6 & CLR_BIT5;
    T2MOD |= SET_BIT4;    // prescaler = 1/4
    CM_RL2 = 0;
    T2MOD &= CLR_BIT7;    // no auto-reload mode
    T2MOD |= SET_BIT3;    // auto-clear the timer on capture

    necReset();

    while (1) {
        if (CAPCON0 & SET_BIT2) {
            CAPCON0 &= CLR_BIT2;    // clear the channel 2 capture flag
            necHandler();
        }

        if (TF2) {
            TF2 = 0;    // clear the Timer 2 overflow flag
            necReset();
        }

        if (decode.success) {
            decode.success = 0;

            uint8_t str[10];

            number2TextHex(str + 0, decode.code.address);
            number2TextHex(str + 2, decode.code.inverse_of_address);
            number2TextHex(str + 4, decode.code.command);
            number2TextHex(str + 6, decode.code.inverse_of_command);
            str[8] = '\n';
            str[9] = 0;

            for (uint8_t i = 0; str[i] != 0; ++i) {
                while (!TI_1);
                TI_1 = 0;
                SBUF_1 = str[i];
            }
        }
    }
}
