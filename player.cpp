#include "player.hpp"
#include "raylib.h"

Player::Player(float x, float y, int velocity, float width, float height)
    : x(x), y(y), velocity(velocity), health(9), width(width), height(height),
      texture(LoadTexture("assets/sprites/knight.png")),
      animation(0, 3, 0, 0.1, 8, "assets/sprites/knight.png") {}

void Player::draw() {
  // Health bar
  // TODO: Put health par into function
  DrawRectangleRounded(
      {.x = x + ((width - 20) / 2), .y = y - 5, .width = 20, .height = 4}, 0.5,
      1, BLACK);
  float health_in_bar = health * 2;
  Color health_in_bar_color;
  if (health > 7)
    health_in_bar_color = GREEN;
  else if (health > 4)
    health_in_bar_color = YELLOW;
  else
    health_in_bar_color = RED;
  DrawRectangleRounded({.x = x + ((width - 20) / 2),
                        .y = y - 5,
                        .width = health_in_bar,
                        .height = 4},
                       0.5, 1, health_in_bar_color);

  // TODO: origin point is way off here
  animation.update();
  DrawTexturePro(texture, animation.get_frame(), {x, y, width, height}, {0, 0},
                 0.0f, WHITE);

  // Hitbox for debugging
  DrawRectangleLines(x, y, width, height, RED);
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
