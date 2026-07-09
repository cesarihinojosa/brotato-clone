#include "system.hpp"

class CollisionSystem : public System {
public:
  void update(Scene &scene, float dt) override;
};
