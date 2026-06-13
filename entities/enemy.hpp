#include "animation.hpp"
#include "raylib.h"

class Enemy {
public:
  float x;
  float y;
  int velocity;

  Enemy(float x, float y, int velocity);
  void draw();
  void update();
  void unload();

private:
  Texture2D texture;
  Animation animation;
};
