#pragma once
#include "raylib.h"

class Animation {
public:
  int first; // First frame index
  int last;  // Last frame index
  int curr;  // Current frame index
  float speed;
  int frames; // Number of frames
  Animation(int first, int last, int curr, float speed, int frames);
  void update();
  Rectangle get_frame();

private:
  float duration_left;
};
