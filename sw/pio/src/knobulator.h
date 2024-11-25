// Knob poller and light updater
//
// svofski 2024j
//

#include "params.h"

#include <cstdint>
#include "i2cmux.h"
#include "knob.h"

struct Knobulator
{
    static constexpr int KNOB_POLL = 512;
    static constexpr int PEAK_CTR = 5120;

    Knob knobs[N_KNOBS];
    uint8_t peaks[N_KNOBS] {};
    LedRefresh leds;

    int knob_poll_ctr = 0;
    int rr_knob = 0;
    int rr_pwm = 0;
    int pwm_phase = 0;
    int peak_ctr = 0;


    typedef void (*on_cc_changed_t)(int, int);

    on_cc_changed_t on_changed;

    Knobulator(AMS_5600& as5600) 
        : knobs({Knob(as5600, 0), Knob(as5600, 1), Knob(as5600, 2), Knob(as5600, 3)})
    {}

    void setup()
    {
        I2CMux::init();
        leds.init();
        leds.off();

        for (int i = 0; i < N_KNOBS; ++i) {
            knobs[i].init_sensor();
            knobs[i].poll();
            knobs[i].start_animate_to_knob();
        }
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

            //leds.off();
            knobs[rr_knob].poll();

            if (knobs[rr_knob].changed) {
                knobs[rr_knob].changed = 0;
                midi_send_cc(MIDI_CC_BASE + rr_knob, knobs[rr_knob].cc_value);
                if (on_changed != nullptr) {
                    on_changed(MIDI_CC_BASE + rr_knob, knobs[rr_knob].cc_value);
                }
            }

            if (++rr_knob == N_KNOBS) rr_knob = 0;
        }
        else if (++peak_ctr == PEAK_CTR) {
            peak_ctr = 0;
            for (int i = 0; i < N_KNOBS; ++i) {
                knobs[i].set_peak(peaks[i]);
            }
            //knobs[3].check_sensor();
        }
    }

    void set_peak(int chan, int value)
    {
        if (chan < 0 || chan >= N_KNOBS) return;
        peaks[chan] = value;
        knobs[chan].set_peak(value);
    }
};

