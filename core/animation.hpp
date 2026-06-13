#pragma once
#include "raylib.h"
#include <cstdint>
#include <string>

class Animation {
public:
  int first; // First frame index
  int last;  // Last frame index
  int curr;  // Current frame index
  float speed;
  int frames; // Number of frames
  std::string image;
  uint32_t frame_size_x;
  uint32_t frame_size_y;
  Animation(int first, int last, int curr, float speed, int frames,
            std::string image);
  void update();
  Rectangle get_frame();

private:
  float duration_left;
  uint32_t get_image_width();
  uint32_t get_image_height();
};
