#include "component.hpp"
#include "raylib.h"

class RectangleComponent : public Component {
public:
  float height;
  float width;
  Color color;
  RectangleComponent(float height, float width, Color color);
  void update(float dt) override;
  void draw() const override;
};
