#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/i2c.h>
#include <libopencm3/cm3/nvic.h>

//#include "usrat.h"
//#include "xprintf.h"
#include "borat.h"
#include "usbcmp.h"
#include "midi.h"

#include "AS5600.h"

#include "u8g2.h"

#define PWM_BITS 7
#define N_KNOBS 4
#define N_LED_GROUPS (N_KNOBS * 2)

AMS_5600 as5600;

extern bool usb_configured_flag;

//1/(1+EXP(((A2/21)-6)*-1))*255
const uint8_t pwm_linearize[128] = 
{
                                                    
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
    0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 
    0x02, 0x03, 0x03, 0x03, 0x04, 0x04, 0x04, 0x05, 
    0x05, 0x06, 0x07, 0x07, 0x08, 0x09, 0x0A, 0x0B, 
    0x0C, 0x0D, 0x0E, 0x0F, 0x11, 0x12, 0x14, 0x16, 
    0x18, 0x1A, 0x1C, 0x1F, 0x21, 0x24, 0x27, 0x2B, 
    0x2E, 0x32, 0x36, 0x3A, 0x3E, 0x43, 0x47, 0x4C, 
    0x51, 0x57, 0x5C, 0x62, 0x67, 0x6D, 0x73, 0x79, 
    0x7F, 0x85, 0x8B, 0x91, 0x97, 0x9C, 0xA2, 0xA7, 
    0xAD, 0xB2, 0xB7, 0xBB, 0xC0, 0xC4, 0xC8, 0xCC, 
    0xD0, 0xD3, 0xD7, 0xDA, 0xDD, 0xDF, 0xE2, 0xE4, 
    0xE6, 0xE8, 0xEA, 0xEC, 0xED, 0xEF, 0xF0, 0xF1, 
    0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF7, 0xF8, 
    0xF9, 0xF9, 0xFA, 0xFA, 0xFA, 0xFB, 0xFB, 0xFB, 
    0xFC, 0xFC, 0xFC, 0xFC, 0xFD, 0xFD, 0xFD, 0xFD, 
    0xFD, 0xFD, 0xFD, 0xFD, 0xFE, 0xFE, 0xFE, 0xFF, 
};

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
struct LedRefresh {
    static constexpr uint32_t gpio_port = GPIOB;
    static constexpr uint32_t gpio_clk = GPIO3,
                       gpio_latch = GPIO4,
                       gpio_data = GPIO5; 

    union {
        uint8_t bitmap[N_LED_GROUPS];
        uint16_t bitmap16[N_KNOBS];
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
        //spi_enable_software_slave_management(SPI1);
        //spi_set_nss_high(SPI1);

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
            for (unsigned i = 0; i < 30; ++i) { __asm__("nop"); }
        }
    }

    void strobe()
    {
        latch(0);
        latch(1);
        latch(0);
    }

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

struct Knob
{
    static constexpr int deadzone = 4096 - 4096 * 5 / 6;
    static constexpr int half_deadzone = deadzone / 2;
    int min_value = 0;
    int max_value = 4095 - deadzone;
    int raw_value; // 0..4095
    int deadzoned_value;
    int id;
    int changed;
    int cc_value;

    Knob(int _id) : id(_id), changed(1), cc_value(0) {}

    int poll() {
        I2CMux::select(id);

        rcc_periph_clock_enable(RCC_I2C1);
        raw_value = as5600.getScaledAngle();
        rcc_periph_clock_disable(RCC_I2C1);

        deadzoned_value = raw_value - half_deadzone;
        if (deadzoned_value < 0) deadzoned_value = 0;
        if (deadzoned_value > max_value) deadzoned_value = max_value;
        deadzoned_value = deadzoned_value * 1200 / 1000;

        int new_cc_value = deadzoned_value * 128 / 4096;
        if (new_cc_value != cc_value) {
            changed = 1;
            cc_value = new_cc_value;
        }

        return raw_value;
    }

    int16_t get_bitmap(int pwm_phase)
    {
#if 1
        constexpr int mult = 1 << PWM_BITS;
        int nbits = 1 + deadzoned_value * 15 * mult / 4096;
        uint8_t frac = nbits & (mult - 1);

        frac = pwm_linearize[frac]>>1;

        int num = nbits >> PWM_BITS;
        if (frac >= pwm_phase) ++num;
        int bm = (1 << num) - 1;
        return bm;
#else
        int nbits = 1 + deadzoned_value * 15 / 4096;
        return 1 << nbits;
#endif
    }
};

struct Knobulator
{
    static constexpr int KNOB_POLL = 512;

    LedRefresh leds;
    Knob knobs[N_KNOBS] {Knob(0), Knob(1), Knob(2), Knob(3)};

    int knob_poll_ctr = 0;
    int rr_knob = 0;
    int rr_pwm = 0;
    int pwm_phase = 0;

    void setup()
    {
        leds.init();
    }

    void loop()
    {
        leds.refresh();

        if (++rr_pwm == N_KNOBS*2) {
            rr_pwm = 0;
            if (++pwm_phase == (1 << PWM_BITS)) {
                pwm_phase = 0;
            }
            for (int i = 0; i < N_KNOBS; ++i) {
                leds.bitmap16[i] = knobs[i].get_bitmap(pwm_phase);
            }
        }

        if (++knob_poll_ctr == KNOB_POLL) {
            knob_poll_ctr = 0;

            leds.off();
            knobs[rr_knob].poll();

            if (knobs[rr_knob].changed) {
                knobs[rr_knob].changed = 0;
                midi_send_cc(91 + rr_knob, knobs[rr_knob].cc_value);
            }

            if (++rr_knob == N_KNOBS) rr_knob = 0;
        }
    }
};

Knobulator knobulator;

u8g2_t u8g2;
//typedef uint8_t (*u8x8_msg_cb)(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
//typedef uint16_t (*u8x8_char_cb)(u8x8_t *u8x8, uint8_t b);
//
//uint8_t u8x8_msg_cb_sw
static uint8_t u8x8_gpio_and_delay_cm3(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
    switch(msg) {
        case U8X8_MSG_GPIO_AND_DELAY_INIT:
            //i2c_setup();  /* Init I2C communication */
            break;

        default:
            u8x8_SetGPIOResult(u8x8, 1);
            break;
    }

    return 1;
}

void oled_init()
{
//void u8g2_Setup_sh1106_128x64_noname_f(u8g2_t *u8g2, const u8g2_cb_t *rotation, u8x8_msg_cb byte_cb, u8x8_msg_cb gpio_and_delay_cb);
    // rotation = U8G2_R2
    u8g2_Setup_sh1106_128x64_noname_f(&u8g2, U8G2_R2, 
            u8x8_byte_4wire_sw_spi,
            u8x8_gpio_and_delay_cm3);
    //u8x8_SetPin_4Wire_SW_SPI(getU8x8(), clock, data, cs, dc, reset);
    u8g2_InitDisplay(&u8g2);
    u8g2_SetFont(&u8g2, u8x8_font_7x14B_1x2_f);
    u8g2_ClearDisplay(&u8g2);
    u8g2_DrawStr(&u8g2, 1,1, "PETOCONTROLE");
}

int main(void)
{
    clock_setup();

    gpio_setup();

    usbcmp_setup();

    knobulator.setup();

    wire_begin();
    rcc_periph_clock_disable(RCC_I2C1);

    I2CMux::init();

    oled_init();

    while (1) {
        usbcmp_poll();
        knobulator.loop();
    }

    return 0;
}