#include <USBComposite.h>
#include <SPI.h>

//#include <SoftWire.h>
//extern SoftWire Wire;
#include <Wire.h>

#include "AS5600.h"

#define WITH_LEDS 1
#define LED_LATCH PB4

#define MUXDI     PB13
#define MUXCLK    PB14
#define MUXLATCH  PB15

#define STROBE_US 1

#define PWM_BITS 7

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

USBCompositeSerial CompositeSerial;


#define STROBE(pin) {digitalWrite(pin, 1); delay_us(STROBE_US); digitalWrite(pin, 0); /*delay_us(STROBE_US);*/}

class myMidi : public USBMIDI {
    virtual void handleNoteOff(unsigned int channel, unsigned int note, unsigned int velocity) {
        //noTone(SPEAKER_PIN);
    }
    virtual void handleNoteOn(unsigned int channel, unsigned int note, unsigned int velocity) {
        //tone(SPEAKER_PIN, (midiNoteFrequency_10ths[note]+5)/10);
        CompositeSerial.print("midi note on chan="); CompositeSerial.println(note);
    }

};

myMidi midi;
AMS_5600 as5600;

void iicmux_init()
{
    pinMode(MUXDI, OUTPUT);
    pinMode(MUXCLK, OUTPUT);
    pinMode(MUXLATCH, OUTPUT);
    digitalWrite(MUXDI, 0);
    digitalWrite(MUXCLK, 0);
    digitalWrite(MUXLATCH, 0);
}

// on one board there are 4 devices 0..3
void iicmux_sel(int dev)
{  
    uint8_t value = dev;
    for (int i = 0; i < 8; ++i) {
        digitalWrite(MUXDI, 1 & (value >> 7));
        STROBE(MUXCLK);
        value <<= 1;
    }
    STROBE(MUXLATCH);
}

int poll_knob(int n)
{
    iicmux_sel(n);

    rcc_clk_enable(RCC_I2C1);
    int result = as5600.getScaledAngle();
    rcc_clk_disable(RCC_I2C1);

    return result;
}

void begin_spi()
{
    afio_remap(AFIO_REMAP_SPI1);
    // setup SPI1 for LED shift registers
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE2);    
    SPI.setClockDivider(SPI_CLOCK_DIV4);      // Slow speed (72 / 16 = 4.5 MHz SPI_1 speed)
    pinMode(LED_LATCH, OUTPUT); // SPI MISO is actually SR latch
}

#if 0
void end_spi()
{
    SPI.end();
    afio_unremap(AFIO_REMAP_SPI1);
    SPI.begin();
    SPI.end();
    rcc_clk_disable(RCC_SPI1);
}
#endif

void setup() {
    // this makes boot/reset buttons necessary for uploading via st-link
    disableDebugPorts();
    //enableDebugPorts();

    USBComposite.setProductId(0x0030);
    midi.registerComponent();
    CompositeSerial.registerComponent();
    USBComposite.begin();

    // i2c 
    Wire.begin();
    rcc_clk_disable(RCC_I2C1);
    iicmux_init();
    iicmux_sel(0);


#if WITH_LEDS
    begin_spi();
#endif
    pinMode(LED_LATCH, OUTPUT); // SPI MISO is actually SR latch
}



long lastmillis = millis();
int delaytime = 0;

#define N_KNOBS 4
#define N_LED_GROUPS (N_KNOBS * 2)
// 15 leds per knob

struct LedRefresh {
    union {
        uint8_t bitmap[N_LED_GROUPS];
        uint16_t bitmap16[N_KNOBS];
    };
    int index;

    LedRefresh() : bitmap{}, index(0) {}

    void refresh()
    {
        digitalWrite(LED_LATCH, 0);
        SPI.transfer16(0);
        digitalWrite(LED_LATCH, 1);
        digitalWrite(LED_LATCH, 0);    

        digitalWrite(LED_LATCH, 0);
        SPI.transfer16((1 << (index + 8)) | bitmap[index]);
        digitalWrite(LED_LATCH, 1);
        digitalWrite(LED_LATCH, 0);    
        //STROBE(LED_LATCH);


        ++index;
        if (index == N_LED_GROUPS) {
            index = 0;
        }    
    }

    void off()
    {
        SPI.transfer(0);
        SPI.transfer(0);
        STROBE(LED_LATCH);  
    }
};

struct Knob {
    static constexpr int deadzone = 4096 - 4096 * 5 / 6;
    static constexpr int half_deadzone = deadzone / 2;
    int min_value = 0;
    int max_value = 4095 - deadzone;
    int raw_value; // 0..4095
    int deadzoned_value;
    int id;

    Knob(int id) : id(id) {}

    int poll() {
        iicmux_sel(id);

        rcc_clk_enable(RCC_I2C1);
        raw_value = as5600.getScaledAngle();
        rcc_clk_disable(RCC_I2C1);


        deadzoned_value = raw_value - half_deadzone;
        if (deadzoned_value < 0) deadzoned_value = 0;
        if (deadzoned_value > max_value) deadzoned_value = max_value;
        deadzoned_value = deadzoned_value * 1200 / 1000;

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

LedRefresh leds;
Knob knobs[N_KNOBS] {Knob(0), Knob(1), Knob(2), Knob(3)};

int slowctr = 0;

#define KNOB_POLL 512
int knob_poll_ctr = 0;
int rr_knob = 0;
int rr_pwm = 0;
int pwm_phase = 0;

void loop() {
    midi.poll();

    leds.refresh();
    //delay_us(10);

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
        if (++rr_knob == N_KNOBS) rr_knob = 0;
    }
}

