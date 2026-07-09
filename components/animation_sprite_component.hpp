#pragma once
#include "component.hpp"
#include "raylib.h"

/// Renders a texture with a vertical bobbing animation.
///
/// Requires: TransformComponent on owner.
class AnimationSpriteComponent : public Component {
public:
  /// @param texture   Texture to load
  /// @param scale     Draw scale factor. Clamped to [0.02, 100].
  /// @param max_bob   Minimum visible height fraction at the bottom of the bob
  /// cycle.
  ///                  Clamped to [0, 1]. A value of 1.0 disables bobbing.
  /// @param speed     Bob animation speed multiplier. Clamped to [0, 100].
  AnimationSpriteComponent(const Texture2D texture, float scale, float max_bob,
                           float speed);
  void draw() const override;
  void update(float dt) override;

private:
  const Texture2D texture;
  const float scale;
  const float max_bob;
  const float speed;
  float current_height;
  float current_bob;
  bool up;
};
