#include "sprite_component.hpp"
#include "game_object.hpp"
#include "raylib.h"
#include "transform_component.hpp"
#include <cassert>

SpriteComponent::SpriteComponent(const char *filename, float scale)
    : texture(LoadTexture(filename)), scale(scale) {}

SpriteComponent::~SpriteComponent() { UnloadTexture(texture); }

void SpriteComponent::draw() {
  assert(owner->getComponent<TransformComponent>() != nullptr);
  auto transform = owner->getComponent<TransformComponent>();
  DrawTexturePro(texture,
                 {.x = 0.0,
                  .y = 0.0,
                  .width = (float)texture.width,
                  .height = (float)texture.height},
                 {.x = transform->x,
                  .y = transform->y,
                  .width = texture.width * scale,
                  .height = texture.height * scale},
                 Vector2{.x = 0, .y = 0}, 0.0, WHITE);
}
