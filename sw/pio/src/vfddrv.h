// FUTABA 8MD-06INKM VFD display driver
//
// based on MicroPython code by Reboot93
// https://github.com/Reboot93/MicroPython-8MD-06INKM-display-driver
//
// svofski 2024
//
#pragma once

#include <cstdint>

#include "swspi.h"

template <typename SPI>
class VFD_8MD06INKM
{
private:
    static constexpr uint8_t DCRAM_DATA_WRITE = 0x20;
    static constexpr uint8_t DGRAM_DATA_CLEAR = 0x10;
    static constexpr uint8_t CGRAM_DATA_WRITE = 0x40;
    static constexpr uint8_t SET_DISPLAY_TIMING = 0xE0;
    static constexpr uint8_t SET_DIMMING_DATA = 0xE4;
    static constexpr uint8_t SET_DISPLAY_LIGHT_ON = 0xE8;
    static constexpr uint8_t SET_DISPLAY_LIGHT_OFF = 0xEA;
    static constexpr uint8_t SET_STAND_BY_MODE = 0xEC;


private:
    SPI & spi;
    int port, cs, reset;
    uint8_t dimming;

    void stupid_delay(unsigned d) {
        for (unsigned i = 0; i < d * 12500; ++i) {
            __asm__("nop");
        }
    }

public:
    static constexpr int ndigits = 8;

    VFD_8MD06INKM(SPI & _spi, int gpio_port, int gpio_cs, int gpio_reset)
        : spi(_spi), port(gpio_port), cs(gpio_cs), reset(gpio_reset),
          dimming(255)
    {
    }

    void init()
    {
        gpio_set_mode(port, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL,
                cs | reset);
        gpio_set(port, cs);
        gpio_set(port, reset);

        spi.init();

        stupid_delay(1);
        gpio_clear(port, reset);
        stupid_delay(10);
        gpio_set(port, reset);
        stupid_delay(3);
        init_display();
        stupid_delay(10);
    }

    void set_dimming(uint8_t value)
    {
        dimming = value;
        write_cmd(SET_DIMMING_DATA, value);
    }

    void on(bool _on)
    {
        write_cmd(SET_STAND_BY_MODE | (_on ? 0 : 1), 0);
    }

    void init_display()
    {
        write_cmd(SET_DISPLAY_TIMING, ndigits - 1);
        write_cmd(SET_DIMMING_DATA, dimming);
        write_cmd(SET_DISPLAY_LIGHT_ON, 0x00);
    }

    void clear(int addr = -1)
    {
        if (addr >= 0 && addr < ndigits) {
            write_cmd(DCRAM_DATA_WRITE | addr, DGRAM_DATA_CLEAR);
        }
        else if (addr < 0) {
            for (unsigned i = 0; i < ndigits; ++i) {
                write_cmd(DCRAM_DATA_WRITE | i, DGRAM_DATA_CLEAR);
            }
        }
    }

    void display_cstr(int addr, const char * strz)
    {
        for (char c; ((c = *strz) != 0) && (addr < ndigits); ++strz, ++addr) {
            write_cmd(DCRAM_DATA_WRITE | addr, (uint8_t)c);
        }
    }

    // display custom bitmap
    void display_custom(int addr, const uint8_t * bytes, size_t len)
    {
        write_data(addr, bytes, len);
        write_cmd(DCRAM_DATA_WRITE | addr, addr);
    }


private:
    void set_cs(uint8_t value)
    {
        if (value)
            gpio_set(port, cs);
        else
            gpio_clear(port, cs);
    }

    void write_cmd(uint8_t cmd, uint8_t param)
    {
        set_cs(1);
        set_cs(0);
        spi.write(cmd);
        spi.write(param);
        set_cs(1);
    }

    void write_data(uint8_t addr, const uint8_t * buf, size_t len)
    {
        set_cs(1);
        set_cs(0);
        spi.write(CGRAM_DATA_WRITE | addr);
        for (size_t i = 0; i < len; ++i) {
            spi.write(*buf++);
        }
        set_cs(1);
    }
};
