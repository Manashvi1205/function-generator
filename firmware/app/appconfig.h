#ifndef APP_CONFIG_H
#define APP_CONFIG_H

// Values are preserved from report Listing 3, even where they differ from system-level
// requirements elsewhere in the report.
#define DEFAULT_FREQUENCY_HZ 1000.0f
#define DEFAULT_AMPLITUDE 1.0f
#define DEFAULT_DC_OFFSET 0.0f
#define DEFAULT_WAVEFORM WAVE_SINE
#define DEFAULT_OUTPUT_STATE false

#define MIN_FREQUENCY_HZ 1.0f
#define MAX_FREQUENCY_HZ 100000.0f
#define MIN_AMPLITUDE 0.0f
#define MAX_AMPLITUDE 3.3f
#define MIN_DC_OFFSET -1.65f
#define MAX_DC_OFFSET 1.65f

#define APP_LOOP_DELAY_MS 5
#define ENABLE_DEBUG_LOG 1

#endif
