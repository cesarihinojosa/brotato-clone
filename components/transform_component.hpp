#include "component.hpp"

class TransformComponent : public Component {
public:
  float x;
  float y;
  TransformComponent(float x, float y);
};
