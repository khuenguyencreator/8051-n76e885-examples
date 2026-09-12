// Lesson 9 - N76E885's own PWM module (not the standard 8051 one): 12-bit period/duty registers,
// edge-aligned type, independent mode. LED breathing effect on PWM0 (P1.0).
#include <stdint.h>
#include <mcs51/N76E885.h>
#include <mcs51/Define.h>

// {PWMPH,PWMPL}: with PWMDIV = 1/32 and Fsys ~22.1184MHz (default HIRC),
// PWM frequency = (Fsys/32) / (PWM_PERIOD+1) ~= 1kHz.
#define PWM_PERIOD 690

void delay1ms(uint16_t duration) {
    for (; duration > 0; duration--) {
        uint16_t i = 1700;
        while (--i);
    }
}

// Set the duty of the PWM0/1 pair. In independent mode (default) only PWM0/P1.0 actually
// toggles; PWM1/P1.1 stays high. The period/duty registers are double buffered, so the new
// value only takes effect once LOAD is set and the current PWM period finishes.
void set_pwm0_duty(uint16_t duty) {
    PWM01H = HIBYTE(duty);    // valid bits [11:8] only
    PWM01L = LOBYTE(duty);
    LOAD = 1;
    while (LOAD);    // wait for the hardware to finish loading the new duty
}

void main(void) {
    // P1.0 (PWM0) push-pull output
    P1M1 &= CLR_BIT0;
    P1M2 |= SET_BIT0;
    PIO |= SET_BIT0;    // route PWM0 onto the P1.0 pin (PIO is not bit-addressable)

    PWMCON1 &= CLR_BIT2 & CLR_BIT1 & CLR_BIT0;
    PWMCON1 |= SET_BIT2 | SET_BIT0;    // PWMDIV[2:0] = 101b = 1/32 prescaler

    CLRPWM = 1;    // reset the 12-bit counter for an accurate first period
    while (CLRPWM);

    PWMPH = HIBYTE(PWM_PERIOD);
    PWMPL = LOBYTE(PWM_PERIOD);
    set_pwm0_duty(0);

    PWMRUN = 1;    // start the PWM generator

    while (1) {
        uint16_t duty;

        for (duty = 0; duty <= PWM_PERIOD; duty += 10) {
            set_pwm0_duty(duty);
            delay1ms(10);
        }
        for (duty = PWM_PERIOD; duty > 0; duty -= 10) {
            set_pwm0_duty(duty);
            delay1ms(10);
        }
        set_pwm0_duty(0);
        delay1ms(200);
    }
}
