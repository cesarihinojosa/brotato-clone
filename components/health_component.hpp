#pragma once
#include "component.hpp"
#include "raylib.h"

/// Tracks current/max health and renders a color-coded health bar.
///
/// Requires: TransformComponent on owner.
class HealthComponent : public Component {
public:
  float current_health;
  float max_health;
  HealthComponent(float current_health, float max_health);
  void draw() const override;
  void update(float dt) override;

private:
  Color health_in_bar;
};
