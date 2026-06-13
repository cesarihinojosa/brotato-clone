#pragma once
#include "animation.hpp"
#include "raylib.h"

class Player {
public:
  float x;
  float y;
  int velocity;
  int health;
  float width;
  float height;

  Player(float x, float y, int velocity, float width, float height);
  void draw();
  void update();
  void unload();

private:
  Texture2D texture;
  Animation animation;
};
