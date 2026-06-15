#include "component.hpp"
#include "raylib.h"

/// Adds a health component and renders a health bar at TransformComponet->x and
/// TransformComponent->y.
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
