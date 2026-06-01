#pragma once
#include "animation.hpp"
#include "raylib.h"

class Player {
public:
  float x;
  float y;
  int velocity;
  int health;

  Player(float x, float y, int velocity);
  void draw();
  void update();
  void unload();

private:
  Texture2D texture;
  Animation animation;
};
