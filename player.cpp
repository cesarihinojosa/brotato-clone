#include "player.hpp"

Player::Player(float x, float y, int velocity)
    : x(x), y(y), velocity(velocity),
      texture(LoadTexture("assets/sprites/knight.png")),
      animation(0, 3, 0, 0.1, 8, "assets/sprites/knight.png") {}

void Player::draw() {
  animation.update();
  DrawTexturePro(texture, animation.get_frame(), {x, y, 64, 64}, {0, 0}, 0.0f,
                 WHITE);
}

void Player::unload() { UnloadTexture(texture); }

void Player::update() {
  if (IsKeyDown(KEY_W)) {
    y += -velocity;
  }
  if (IsKeyDown(KEY_S)) {
    y += velocity;
  }
  if (IsKeyDown(KEY_D)) {
    x += velocity;
  }
  if (IsKeyDown(KEY_A)) {
    x += -velocity;
  }
}
