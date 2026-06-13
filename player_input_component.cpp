#include "player_input_component.hpp"
#include "game_object.hpp"
#include "raylib.h"
#include "transform_component.hpp"
#include "velocity_component.hpp"
#include <cassert>

void PlayerInputComponent::update(float dt) {
  assert(owner->getComponent<TransformComponent>() != nullptr &&
         owner->getComponent<VelocityComponent>() != nullptr);

  auto transform = owner->getComponent<TransformComponent>();
  auto velocity = owner->getComponent<VelocityComponent>();

  if (IsKeyDown(KEY_W)) {
    transform->y -= velocity->velocity;
  }
  if (IsKeyDown(KEY_D)) {
    transform->x += velocity->velocity;
  }
  if (IsKeyDown(KEY_S)) {
    transform->y += velocity->velocity;
  }
  if (IsKeyDown(KEY_A)) {
    transform->x -= velocity->velocity;
  }
}
