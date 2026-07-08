#include "damage_component.hpp"
#include <algorithm>

DamageComponent::DamageComponent(int damage, int max_damage)
    : damage_(damage), max_damage_(max_damage) {}

int DamageComponent::getDamage() { return damage_; }

void DamageComponent::setDamage(int damage) {
  damage_ = std::clamp(damage, 0, max_damage_);
}
