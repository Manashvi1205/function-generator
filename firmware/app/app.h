#ifndef APP_H
#define APP_H

#include <Arduino.h>

typedef enum {
  WAVE_SINE = 0,
  WAVE_SQUARE,
  WAVE_TRIANGLE,
  WAVEFORM_COUNT
} WaveformType;

typedef enum {
  CHANNEL_NONE = 0,
  CHANNEL_1,
  CHANNEL_2,
  CHANNEL_BOTH,
  CHANNEL_MODE_COUNT
} ChannelMode;

typedef enum {
  APP_VIEW_MODE = 0,
  APP_EDIT_MODE
} AppMode;

typedef enum {
  EDIT_NONE = 0,
  EDIT_FREQ,
  EDIT_AMP,
  EDIT_DC,
  EDIT_TARGET_COUNT
} EditTarget;

typedef enum {
  MAG_HZ = 0,
  MAG_KHZ,
  MAG_MHZ,
  MAG_COUNT
} Magnitude;

typedef struct {
  float frequency;
  float amplitude;
  float dc_offset;
  WaveformType waveform;
} ChannelState;

typedef struct {
  ChannelState ch[2];
  ChannelMode output_mode;
  int active_channel;
  AppMode mode;
  EditTarget edit_target;
  int digits[4];
  int digit_index;
  Magnitude magnitude;
  bool edit_negative;
  bool output_enabled;
} AppState;

// Implementations were not present in the supplied report package.
void app_init(void);
void app_run(void);
const AppState *app_get_state(void);

#endif
