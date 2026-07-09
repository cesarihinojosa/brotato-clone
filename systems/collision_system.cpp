#include "collision_system.hpp"
#include "components.hpp"
#include "scene.hpp"

void CollisionSystem::update(Scene &scene, float dt) {
  auto objects = scene.view<HitboxComponent, TransformComponent>();
  for (size_t i = 0; i < objects.size(); i++) {
    auto &[object_a, hitbox_a, position_a] = objects[i];
    for (size_t j = 0; j < objects.size(); j++) {
      auto &[object_b, hitbox_b, position_b] = objects[j];
      float distance_x = abs(position_a.x - position_b.x);
      float distance_y = abs(position_a.y - position_b.y);
      float radii = hitbox_a.getRadius() + hitbox_b.getRadius();
      if (distance_x < radii && distance_y < radii && i != j) {
        object_a.getComponent<HealthComponent>()->current_health -=
            object_b.getComponent<DamageComponent>()->getDamage() * 0.01;
      }
    }
  }
}
