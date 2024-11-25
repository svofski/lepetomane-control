// i2c device multiplexor for petocontrole
// selects one of AS5600 to talk to
//
// 2024 svofski

#pragma once

#include <cstdint>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/i2c.h>

struct I2CMux
{
    static constexpr uint32_t port = GPIOB;
    static constexpr uint32_t MUXDI = GPIO13,
                     MUXCLK = GPIO14,
                     MUXLATCH = GPIO15;

    static void delay_strobe()
    {
        for (int i = 0; i < 10; ++i) __asm__("nop");
    }

    static void strobe(uint16_t pin)
    {
        gpio_set(port, pin); delay_strobe();
        gpio_clear(port, pin); delay_strobe();
    }

    static void init()
    {
        gpio_set_mode(port, GPIO_MODE_OUTPUT_50_MHZ,
                GPIO_CNF_OUTPUT_PUSHPULL, MUXDI | MUXCLK | MUXLATCH );

        gpio_clear(port, MUXDI | MUXCLK | MUXLATCH);
    }

    // on one board there are 4 devices 0..3
    static void select(int dev)
    {  
        uint8_t value = dev;
        for (int i = 0; i < 8; ++i) {
            if (1 & (value >> 7)) {
                gpio_set(port, MUXDI);
            }
            else {
                gpio_clear(port, MUXDI);
            }
            strobe(MUXCLK);
            value <<= 1;
        }
        strobe(MUXLATCH);
    }
};

