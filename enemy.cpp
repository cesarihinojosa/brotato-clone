#include "enemy.hpp"

Enemy::Enemy(float x, float y, int velocity)
    : x(x), y(y), velocity(velocity),
      texture(LoadTexture("assets/sprites/slime_green.png")),
      animation(0, 3, 0, 0.12, 4, "assets/sprites/slime_green.png") {}

void Enemy::draw() {
  animation.update();
  DrawTexturePro(texture, animation.get_frame(), {x, y, 64, 64}, {0, 0}, 0.0f,
                 WHITE);
}

void Enemy::unload() { UnloadTexture(texture); }

void Enemy::update() {}
