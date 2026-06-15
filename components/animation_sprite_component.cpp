#include "animation_sprite_component.hpp"
#include "game_object.hpp"
#include "raylib.h"
#include "transform_component.hpp"
#include <algorithm>
#include <cassert>

AnimationSpriteComponent::AnimationSpriteComponent(const char *filename,
                                                   float scale, float max_bob,
                                                   float speed)
    : texture(LoadTexture(filename)), scale(std::clamp(scale, 0.02f, 100.0f)),
      max_bob(std::clamp(max_bob, 0.0f, 1.0f)),
      speed(std::clamp(speed, 0.0f, 100.0f)),
      current_bob(std::clamp(max_bob, 0.0f, 1.0f)), up(true) {}

AnimationSpriteComponent::~AnimationSpriteComponent() {
  UnloadTexture(texture);
}

// TODO: User should pass in x and y to provide more control.
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
  if (up) {
    current_bob += 0.001 * speed;
    if (current_bob >= 1.0)
      up = false;
  } else {
    current_bob -= 0.001 * speed;
    if (current_bob < max_bob)
      up = true;
  }
  current_height = texture.height * current_bob;
}
