#include "health_component.hpp"
#include "game_object.hpp"
#include "raylib.h"
#include "transform_component.hpp"
#include <algorithm>
#include <cassert>

HealthComponent::HealthComponent(float current_health, float max_health)
    : current_health(current_health), max_health(max_health) {}

// TODO: Find a better way to position health bar
void HealthComponent::draw() const {
  auto transform = owner->getComponent<TransformComponent>();
  assert(transform != nullptr);
  DrawRectangleRounded(
      {.x = transform->x, .y = transform->y, .width = 50, .height = 7}, 0.5, 1,
      BLACK);
  DrawRectangleRounded({.x = transform->x,
                        .y = transform->y,
                        .width = (50 * current_health) / max_health,
                        .height = 8},
                       0.5, 1, health_in_bar);
}

void HealthComponent::update(float dt) {
  current_health = std::clamp(current_health, 0.0f, max_health);
  if (current_health > max_health * 0.6)
    health_in_bar = GREEN;
  else if (current_health > max_health * 0.3)
    health_in_bar = YELLOW;
  else
    health_in_bar = RED;
}
