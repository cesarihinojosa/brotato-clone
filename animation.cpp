#include "animation.hpp"
#include "raylib.h"
#include <arpa/inet.h>
#include <cstdint>
#include <fstream>
#include <string>

// TODO: Restructure animation system to fit component architecture
Animation::Animation(int first, int last, int curr, float speed, int frames,
                     std::string image)
    : first(first), last(last), curr(curr), speed(speed), frames(frames),
      image(image), frame_size_x(get_image_width() / frames),
      frame_size_y(get_image_height() / frames), duration_left(speed) {}

void Animation::update() {
  float dt = GetFrameTime();
  duration_left -= dt;

  if (duration_left <= 0.0) {
    duration_left = speed;
    curr++;
    if (curr > last) {
      curr = first;
    }
  }
}

Rectangle Animation::get_frame() {
  int x = (curr % (last + 1)) * frame_size_x;
  int y = (curr / (last + 1)) * frame_size_x;
  return (Rectangle){(float)x, (float)y, (float)frame_size_x,
                     (float)frame_size_x};
}

uint32_t Animation::get_image_width() {
  std::ifstream file(image, std::ios::binary);

  // Skip 8-byte PNG signature + 4-byte chunk length + 4-byte "IHDR" tag
  file.seekg(16);

  uint32_t width_be, height_be;
  file.read(reinterpret_cast<char *>(&width_be), 4);
  file.read(reinterpret_cast<char *>(&height_be), 4);

  // PNG stores values as big-endian; convert to host byte order
  uint32_t width = ntohl(width_be);

  return width;
}

uint32_t Animation::get_image_height() {
  std::ifstream file(image, std::ios::binary);

  // Skip 8-byte PNG signature + 4-byte chunk length + 4-byte "IHDR" tag
  file.seekg(16);

  uint32_t width_be, height_be;
  file.read(reinterpret_cast<char *>(&width_be), 4);
  file.read(reinterpret_cast<char *>(&height_be), 4);

  // PNG stores values as big-endian; convert to host byte order
  uint32_t height = ntohl(height_be);

  return height;
}
