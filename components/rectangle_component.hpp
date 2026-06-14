#include "component.hpp"
#include "raylib.h"

/// Renders a filled rectangle at the owner's position.
///
/// Requires: TransformComponent on owner.
class RectangleComponent : public Component {
public:
  const float height; ///< Rectangle height in pixels.
  const float width;  ///< Rectangle width in pixels.
  const Color color;  ///< Fill color.
  RectangleComponent(float height, float width, Color color);
  void update(float dt) override;
  void draw() const override;
};
