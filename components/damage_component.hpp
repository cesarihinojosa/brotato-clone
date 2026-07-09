#pragma once
#include "component.hpp"

/// Stores how much damage this entity deals on contact.
class DamageComponent : public Component {
public:
  // TODO: damage in constructor bypasses setDamage()
  DamageComponent(int damage, int max_damage);

  /// Sets damage, clamped to [0, max_damage].
  void setDamage(int damage);

  /// Returns the current damage value.
  int getDamage();

private:
  int damage_;
  int max_damage_;
};
