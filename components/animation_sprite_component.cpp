#include "animation_sprite_component.hpp"
#include "game_object.hpp"
#include "raylib.h"
#include "transform_component.hpp"
#include <algorithm>
#include <cassert>

AnimationSpriteComponent::AnimationSpriteComponent(const Texture2D texture,
                                                   float scale, float max_bob,
                                                   float speed)
    : texture(texture), scale(std::clamp(scale, 0.02f, 100.0f)),
      max_bob(std::clamp(max_bob, 0.0f, 1.0f)),
      speed(std::clamp(speed, 0.0f, 100.0f)),
      current_bob(std::clamp(max_bob, 0.0f, 1.0f)), up(true) {}

// TODO: Find a better way to give user control over where to render
void AnimationSpriteComponent::draw() const {
  assert(owner->getComponent<TransformComponent>() != nullptr);
  auto transform = owner->getComponent<TransformComponent>();

  float destination_x = transform->x - ((texture.width * scale) / 2);
  float destination_y = transform->y - ((texture.height * scale) / 2) +
                        ((texture.height - current_height) * scale);

  Rectangle source = {.x = 0.0,
                      .y = 0.0,
                      .width = (float)texture.width,
                      .height = (float)texture.height};
  Rectangle destination = {.x = destination_x,
                           .y = destination_y,
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
