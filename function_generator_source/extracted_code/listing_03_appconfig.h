# ifndef APP_CONFIG_H
# define APP_CONFIG_H
// --------------------
// Default Parameters
// --------------------
# define DEFAULT_FREQUENCY_HZ 1000.0 f
# define DEFAULT_AMPLITUDE 1.0 f // Normalized or Volts ( your
choice )
# define DEFAULT_DC_OFFSET 0.0 f
# define DEFAULT_WAVEFORM WAVE_SINE
# define DEFAULT_OUTPUT_STATE false
// --------------------
// Allowed Limits
// --------------------
# define MIN_FREQUENCY_HZ 1.0 f
# define MAX_FREQUENCY_HZ 100000.0 f // Adjust based on DAC
method
# define MIN_AMPLITUDE 0.0 f
# define MAX_AMPLITUDE 3.3 f // ESP32 reference or op -
amp range
# define MIN_DC_OFFSET -1.65 f
# define MAX_DC_OFFSET 1.65 f
// --------------------
// System Timing
// --------------------
# define APP_LOOP_DELAY_MS 5 // Loop pacing ( optional )
// --------------------
// Debug
// --------------------
# define ENABLE_DEBUG_LOG 1
# endif // APP_CONFIG_H
.9.3 Display Module
