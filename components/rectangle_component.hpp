#include "component.hpp"
#include "raylib.h"

class RectangleComponent : public Component {
public:
  const float height;
  const float width;
  const Color color;
  RectangleComponent(float height, float width, Color color);
  void update(float dt) override;
  void draw() const override;
};
