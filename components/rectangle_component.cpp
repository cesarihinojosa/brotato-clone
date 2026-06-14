#include "rectangle_component.hpp"
#include "game_object.hpp"
#include "raylib.h"
#include "transform_component.hpp"
#include <cassert>

RectangleComponent::RectangleComponent(float height, float width, Color color)
    : height(height), width(width), color(color) {}

void RectangleComponent::draw() const {
  assert(owner->getComponent<TransformComponent>() != nullptr);

  // TODO: I dont think this should happen every time, maybe keep as attribute?
  // But then it would still need to know about updates...
  float x = owner->getComponent<TransformComponent>()->x;
  float y = owner->getComponent<TransformComponent>()->y;
  DrawRectangle(x, y, (int)width, (int)height, color);
}

void RectangleComponent::update(float dt) {}
