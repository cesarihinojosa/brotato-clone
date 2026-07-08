#include "component.hpp"

class DamageComponent : Component {
public:
  DamageComponent(
      int damage,
      int max_damage); // TODO: damage in constructor bypasses setDamage()
  void setDamage(int damage);
  int getDamage();

private:
  int damage_;
  int max_damage_;
};
