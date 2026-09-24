#ifndef SIGNAL_GEN_H
#define SIGNAL_GEN_H

#include <Arduino.h>
#include "../app/app.h"

// Implementations were not present in the supplied report package.
void signal_init(void);
void signal_set_frequency(int channel, float frequency);
void signal_set_amplitude(int channel, float amplitude);
void signal_set_offset(int channel, float offset);
void signal_set_waveform(int channel, WaveformType waveform);
void signal_set_output_mode(ChannelMode mode);

#endif
