// Knob
//
// svofski 2024
//

#pragma once

#include "params.h"
#include <cstdint>
#include <cmath>

#include <i2cmux.h>

//1/(1+EXP(((A2/21)-6)*-1))*255
static const uint8_t pwm_linearize[128] = 
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


struct Knob
{
    static constexpr int ANIM_SPEED = 56;

    static constexpr int deadzone = 4096 - 4096 * 5 / 6;
    static constexpr int half_deadzone = deadzone / 2;
    static constexpr int min_value = 0;
    static constexpr int max_value = 4095 - deadzone;

    AMS_5600& as5600;

    int raw_value; // 0..4095
    int deadzoned_value;
    uint8_t id;
    bool changed;
    uint8_t cc_value;

    int prev_value;
    int led_value;

    uint8_t knob_change_hold;
    uint8_t silence_hold;
    bool animate_to_knob;

    Knob(AMS_5600& _as5600, int _id)
        : as5600(_as5600), id(_id), changed(1), cc_value(0), prev_value(0), led_value(0)
    {
        knob_change_hold = 0;
        silence_hold = 0;
        animate_to_knob = true;
    }

    void init_sensor()
    {
        I2CMux::select(id);

        rcc_periph_clock_enable(RCC_I2C1);
        uint16_t conf = 0b11 << 2;  // HYST 11
        conf |= 0b00 << 0;          // SF slow filter 16x
        as5600.setConf(conf);
        rcc_periph_clock_disable(RCC_I2C1);
    }

    void check_sensor()
    {
        I2CMux::select(id);

        rcc_periph_clock_enable(RCC_I2C1);
        xprintf("current conf=%04x strength=%d agc=%d a=%d\n", 
                as5600.getConf(), as5600.getMagnetStrength(), as5600.getAgc(),
                as5600.getScaledAngle());
        rcc_periph_clock_disable(RCC_I2C1);
    }

    int poll()
    {
        I2CMux::select(id);

        rcc_periph_clock_enable(RCC_I2C1);
        raw_value = as5600.getScaledAngle();
        rcc_periph_clock_disable(RCC_I2C1);

        deadzoned_value = raw_value - half_deadzone;
        if (deadzoned_value < 0) deadzoned_value = 0;
        if (deadzoned_value > max_value) deadzoned_value = max_value;
        deadzoned_value = deadzoned_value * 1200 / 1000;
      
        deadzoned_value = (prev_value + deadzoned_value) / 2; // hopefully reduce the flicker a little bit
        prev_value = deadzoned_value;

        int new_cc_value = deadzoned_value * 128 / 4096;
        if (new_cc_value != cc_value) {
            changed = 1;
            knob_change_hold = KNOB_CHANGE_HOLD;
            cc_value = new_cc_value;
            //led_value = deadzoned_value;
        }

        if (animate_to_knob) {
            if (led_value < deadzoned_value)
                led_value += ANIM_SPEED;// = deadzoned_value;
            else if (led_value > deadzoned_value)
                led_value -= ANIM_SPEED;
        }
        else if (changed) {
            led_value = deadzoned_value;
        }
        if (animate_to_knob && std::abs(led_value - deadzoned_value) < 2 * ANIM_SPEED) {
            animate_to_knob = false;
        }

        if (knob_change_hold) --knob_change_hold;

        return raw_value;
    }

    void release_hold()
    {
        knob_change_hold = 0;
    }

    int16_t get_bitmap(int pwm_phase)
    {
#if 1
        constexpr int mult = 1 << PWM_BITS;
        int nbits = 1 + led_value * 15 * mult / 4096;
        uint8_t frac = nbits & (mult - 1);

        frac = pwm_linearize[frac]>>1;

        int num = nbits >> PWM_BITS;
        if (frac >= pwm_phase) ++num;
        int bm = (1 << num) - 1;
        return bm;
#else
        int nbits = 1 + led_value * 15 / 4096;
        return 1 << nbits;
#endif
    }

    void set_peak(int value)
    {
        static constexpr int thresh = 3;

        if (knob_change_hold) return;

        if (value <= thresh) {
            if (silence_hold < SILENCE_HOLD) {
                ++silence_hold;
                if (silence_hold == SILENCE_HOLD) {
                    animate_to_knob = true;
                }
            }
        }
        else if (value > thresh) {
            silence_hold = 0;
        }

        if (silence_hold == SILENCE_HOLD) {
            return;
        }

        if (value < 0) value = 0;
        if (value > 127) value = 127;
        led_value = value * 4096 / 128;
    }

    void start_animate_to_knob()
    {
        silence_hold = SILENCE_HOLD;
        led_value = 0;
        animate_to_knob = true;
    }
};

