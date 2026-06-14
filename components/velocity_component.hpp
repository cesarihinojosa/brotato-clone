#include "component.hpp"

/// Stores a scalar movement speed for use by input or AI components.
class VelocityComponent : public Component {
public:
  float velocity; ///< Movement speed in pixels per frame.
  VelocityComponent(float velocity);
};
