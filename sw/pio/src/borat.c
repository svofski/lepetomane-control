#include <inttypes.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/cortex.h>

#include "borat.h"

volatile uint32_t systick_uptime_millis;

void sys_tick_handler(void)
{
    systick_uptime_millis++;
}


// Set up a timer to create 1mS ticks.
void clock_setup(void)
{
    rcc_clock_setup_in_hse_8mhz_out_72mhz();

    // // clock rate / 1000 to get 1mS interrupt rate
    systick_set_reload(F_CPU);
    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
    systick_counter_enable();
    systick_interrupt_enable();
}

uint32_t millis()
{
    return systick_uptime_millis;
}

void gpio_setup(void) {
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_GPIOC);
    rcc_periph_clock_enable(RCC_GPIOC); // ?
}

// declared in libmaple/util.h
void _fail(const char* file, int line, const char* exp) {
    (void)file;
    (void)line;
    (void)exp;
    *((int *)0) = 0;
}
