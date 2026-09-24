#pragma once

#include <Arduino.h>

typedef enum {
  UI_NONE = 0,
  UI_NUM_0,
  UI_NUM_1,
  UI_NUM_2,
  UI_NUM_3,
  UI_NUM_4,
  UI_NUM_5,
  UI_NUM_6,
  UI_NUM_7,
  UI_NUM_8,
  UI_NUM_9,
  UI_CONFIRM,
  UI_WAVEFORM_TOGGLE,
  UI_ACTIVE_CHANNEL_TOGGLE,
  UI_OUTPUT_CHANNEL_TOGGLE,
  UI_MODIFY_TOGGLE,
  UI_MAGNITUDE_TOGGLE,
  UI_NEXT_FIELD
} UIEvent;

// Implementations were not present in the supplied report package.
void input_init(void);
void input_update(void);
UIEvent input_get_event(void);
void input_inject_event(UIEvent event);
