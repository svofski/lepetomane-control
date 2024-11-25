#pragma once

#define PWM_BITS 7
#define N_KNOBS 4
#define N_LED_GROUPS (N_KNOBS * 2)

#define KNOB_CHANGE_HOLD  100
#define SILENCE_HOLD  20

#define MIDI_CC_BASE 91

#define MIDI_RINGLIGHT1 ((MIDI_CC_BASE) + 0)
#define MIDI_RINGLIGHT2 ((MIDI_CC_BASE) + 1)
#define MIDI_RINGLIGHT3 ((MIDI_CC_BASE) + 2)
#define MIDI_RINGLIGHT4 ((MIDI_CC_BASE) + 3)
