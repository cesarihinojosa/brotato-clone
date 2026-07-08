#include "hitbox_component.hpp"
#include "game_object.hpp"
#include "raylib.h"
#include "transform_component.hpp"
#include <cassert>

HitboxComponent::HitboxComponent(float radius) : radius_(radius) {}

int HitboxComponent::getRadius() { return radius_; }

void HitboxComponent::draw() const {
  if (debug) {
    auto transform = owner->getComponent<TransformComponent>();
    assert(transform != nullptr);
    DrawCircleLines(transform->x, transform->y, radius_, RED);
  }
}
