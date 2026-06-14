#pragma once
#include "component.hpp"

/// Translates WASD keyboard input into movement via the owner's TransformComponent.
///
/// Requires: TransformComponent, VelocityComponent on owner.
class PlayerInputComponent : public Component {
public:
  void update(float dt) override;
};
