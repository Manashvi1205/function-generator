#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include "../app/app.h"

// Implementations were not present in the supplied report package.
void display_init(void);
void display_update(const AppState *state);

enum WaveType { W_SINE = 0, W_SQUARE = 1, W_TRI = 2 };
enum Channel { CH1 = 0, CH2 };

struct ScreenState {
  double freq = 1000.00;
  WaveType wave = W_SINE;
  double amp = 5.00;
  double offset = 0.00;
  bool outOn = true;
  int cursorPos = 0;
  bool editing = false;
};

#endif
