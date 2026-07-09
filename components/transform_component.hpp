#pragma once
#include "component.hpp"

/// Stores the world-space position of a GameObject.
/// Required by most rendering and physics components.
class TransformComponent : public Component {
public:
  float x; ///< World-space X position in pixels.
  float y; ///< World-space Y position in pixels.
  TransformComponent(float x, float y);
};
