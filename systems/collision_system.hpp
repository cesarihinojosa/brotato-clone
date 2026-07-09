#pragma once
#include "system.hpp"

/// Detects collisions between entities with hitboxes and applies damage.
class CollisionSystem : public System {
public:
  void update(Scene &scene, float dt) override;
};
