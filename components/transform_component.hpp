#include "component.hpp"

class TransformComponent : public Component {
public:
  // TODO: Use a Vector2
  float x;
  float y;
  TransformComponent(float x, float y);
};
