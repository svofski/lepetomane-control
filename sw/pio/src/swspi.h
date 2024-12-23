// libopencm3 based bit-banged SPI
//
// very basic, transmit-only. add features to taste.
//
// svofski 2024

#pragma once

#include <cstdint>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

// lsb first, polarity = 0, phase = 0 -- rx not implemented
class SW_SPI
{
private:
    int port, clk, miso, mosi;

public:
    SW_SPI(int gpio_port, int gpio_clk, int gpio_miso, int gpio_mosi)
        : port(gpio_port), clk(gpio_clk), miso(gpio_miso), mosi(gpio_mosi)
    {
    }

    void init()
    {
        gpio_set_mode(port, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL,
                clk | mosi);
        if (miso >= 0) {
            gpio_set_mode(port, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN, miso);
        }
    }


    uint8_t write(uint8_t byte)
    {
        for (unsigned i = 0; i < 8; ++i) {
            if (byte & 1)
                gpio_set(port, mosi);
            else
                gpio_clear(port, mosi);

            gpio_set(port, clk);
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
            gpio_clear(port, clk);

            byte >>= 1;
        }
        return 0;
    }
};
