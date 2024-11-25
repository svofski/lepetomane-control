// LED refresher for petocontrole
//
// The LEDs are arranged in a 8x8 matrix (row 7 of odd columns is absent).
// Consult the schematics for details.
//
// svofski 2024

#pragma once

#include "params.h"

#include <cstdint>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>

void spi_reset(int dev)
{
    switch (dev) {
        case SPI1:
            rcc_periph_reset_pulse(RST_SPI1);
            break;
        case SPI2:
            rcc_periph_reset_pulse(RST_SPI2);
            break;
        default:
            for(;;);
    }
}


// LED_CLK      PB3     SPI1_SCK (remapped)
// LED_LATCH    PB4     (GPIO)
// LED_DATA     PB5     SPI1_MOSI (remapped)
//template<int N_KNOBS, int N_LED_GROUPS>
struct LedRefresh {
    static constexpr uint32_t gpio_port = GPIOB;
    static constexpr uint32_t gpio_clk = GPIO3,
                       gpio_latch = GPIO4,
                       gpio_data = GPIO5; 

    union {
        uint8_t bitmap[N_LED_GROUPS]; // LED matrix columns
        uint16_t bitmap16[N_KNOBS];   // each knob has 15 leds (2 columns)
    };

    int index;

    LedRefresh() : bitmap{}, index(0) {}

    void init()
    {
        /* Enable Alternate Function clock. */
	rcc_periph_clock_enable(RCC_AFIO);
        /* Enable SPI1 clock */
        rcc_periph_clock_enable(RCC_SPI1);

        /* remap SPI1 to PB3..5 */
        gpio_primary_remap(AFIO_MAPR_SWJ_CFG_JTAG_OFF_SW_ON, AFIO_MAPR_SPI1_REMAP);
        
        gpio_set_mode(gpio_port, GPIO_MODE_OUTPUT_50_MHZ,
            GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, gpio_clk | gpio_data | gpio_latch );

        spi_reset(SPI1);

        spi_init_master(SPI1, 
                SPI_CR1_BAUDRATE_FPCLK_DIV_16, 
                SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE,
                SPI_CR1_CPHA_CLK_TRANSITION_2,
                SPI_CR1_DFF_16BIT,
                SPI_CR1_MSBFIRST);

        spi_set_bidirectional_transmit_only_mode(SPI1);

        // examples have this but i don't know why...
        spi_enable_software_slave_management(SPI1);
        spi_set_nss_high(SPI1);

        spi_enable(SPI1);

        gpio_set_mode(gpio_port, GPIO_MODE_OUTPUT_50_MHZ,
                GPIO_CNF_OUTPUT_PUSHPULL, gpio_latch);
    }

    void latch(int on)
    {
        if (on) {
            gpio_set(gpio_port, gpio_latch);
            for (unsigned i = 0; i < 5; ++i) { __asm__("nop"); }
        }
        else {
            gpio_clear(gpio_port, gpio_latch);
            for (unsigned i = 0; i < 35; ++i) { __asm__("nop"); }
        }
    }

    void strobe()
    {
        latch(0);
        latch(1);
        latch(0);
    }

    // iterate with 1 as column selector (group) in msb and bitmap as rows in lsb
    void refresh()
    {
        spi_send(SPI1, 0);
        latch(1);
        latch(0);

        spi_send(SPI1, (1 << (index + 8)) | bitmap[index]);
        latch(1);
        latch(0);

        ++index;
        if (index == N_LED_GROUPS) {
            index = 0;
        }
    }

    void off()
    {
        spi_send(SPI1, 0);
        strobe();
    }
};

