#pragma once
#include "component.hpp"

/// Circular hitbox for collision detection.
///
/// Requires: TransformComponent on owner.
class HitboxComponent : public Component {
public:
  bool debug = false; ///< Render the hitbox outline on screen when true.
  /// @param radius  Hitbox radius in pixels.
  HitboxComponent(float radius);
  void draw() const override;

  /// Returns the hitbox radius.
  int getRadius();

private:
  const float radius_;
};
