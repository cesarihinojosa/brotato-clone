#include "animation.hpp"
#include "raylib.h"

Animation::Animation(int first, int last, int curr, float speed, int frames)
    : first(first), last(last), curr(curr), speed(speed), frames(frames),
      duration_left(speed) {}

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
  int x = (curr % frames) * 32;
  int y = (curr / frames) * 32;
  return (Rectangle){(float)x, (float)y, 32, 32};
}
