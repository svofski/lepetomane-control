// Petocontrole
//
// MIDI knobs and blinkenlights
// blessed with a VFD display
//
// svofski 2024

#include "params.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/i2c.h>
#include <libopencm3/cm3/nvic.h>

//#include "usrat.h"
#include "xprintf.h"
#include "borat.h"
#include "usbcmp.h"
#include "midi.h"
#include "AS5600.h"
#include "i2cmux.h"
#include "ledrefresh.h"
#include "knob.h"
#include "knobulator.h"

#if WITH_VFD
#include "swspi.h"
#include "vfddrv.h"
#include "display.h"
#endif

#include <cmath>

extern bool usb_configured_flag;

AMS_5600 as5600;
Knobulator knobulator(as5600);

void my_midi_peak_meter_cb(midi_chan_t midichan, uint8_t chan, uint8_t value)
{
    (void)midichan;
    knobulator.set_peak(chan, value);
}

#if WITH_VFD
SW_SPI vfd_spi(/*port*/ GPIOA, /*clk*/GPIO0, /*miso*/-1, /*MOSI*/GPIO1);
VFD_8MD06INKM<SW_SPI> vfddrv(vfd_spi, GPIOA, /*cs*/GPIO4, /*reset*/GPIO2);
Display<VFD_8MD06INKM<SW_SPI>> vfd(vfddrv);
#endif

void knobulator_changed(int cc, int val)
{
    if (cc >= 0 && cc < 100 && val >= 0 && val < 1000) {
        xsprintf(vfd.text(), "CC%02d:%03d", cc, val);
    }
    else if (cc >= 100 && val >= 0 && val < 1000) {
        xsprintf(vfd.text(), "C%03d:%03d", cc, val);
    }
    vfd.invalidate();
    xprintf("%d %d '%s'\n", cc, val, vfd.text()); // dead without this line
}

int main(void)
{
    // reacts to CC91..CC94 to update peaks
    midi_peak_meter_cb = my_midi_peak_meter_cb;

    clock_setup();
    gpio_setup();
    usbcmp_setup();
    wire_begin();
    rcc_periph_clock_disable(RCC_I2C1);
    knobulator.setup();
    knobulator.on_changed = knobulator_changed;

#if WITH_VFD
    vfd.init();
#endif

    int skip_ctr = 0;
    while (1) {
        // no idea, seems to make it a bit more stable
        if (++skip_ctr == 32) {
            usbcmp_poll();
            skip_ctr = 0;

            vfd.animate();
        }
        knobulator.loop();
    }

    return 0;
}
