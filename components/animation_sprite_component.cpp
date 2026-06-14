#include "animation_sprite_component.hpp"
#include "game_object.hpp"
#include "raylib.h"
#include "transform_component.hpp"
#include <cassert>

AnimationSpriteComponent::AnimationSpriteComponent(const char *filename,
                                                   float scale, float max_bob,
                                                   float speed)
    : texture(LoadTexture(filename)), scale(scale), max_bob(max_bob),
      speed(speed), current_bob(max_bob), direction(1) {}

AnimationSpriteComponent::~AnimationSpriteComponent() {
  UnloadTexture(texture);
}

void AnimationSpriteComponent::draw() const {
  assert(owner->getComponent<TransformComponent>() != nullptr);
  auto transform = owner->getComponent<TransformComponent>();

  Rectangle source = {.x = 0.0,
                      .y = 0.0,
                      .width = (float)texture.width,
                      .height = (float)texture.height};
  Rectangle destination = {.x = transform->x,
                           .y = transform->y +
                                ((texture.height - current_height) * scale),
                           .width = texture.width * scale,
                           .height = current_height * scale};
  DrawTexturePro(texture, source, destination, Vector2{.x = 0.0, .y = 0.0}, 0.0,
                 WHITE);
}

void AnimationSpriteComponent::update(float dt) {
  if (direction == 1) {
    current_bob += 0.001 * speed;
    if (current_bob > 1) {
      direction = -1;
    }
  } else {
    current_bob -= 0.001 * speed;
    if (current_bob < max_bob) {
      direction = 1;
    }
  }
  current_height = texture.height * current_bob;
}
