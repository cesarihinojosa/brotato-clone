#include "component.hpp"

/// Creates a circular hitbox.
///
/// Requires: TransformComponent on owner.
class HitboxComponent : public Component {
public:
  bool debug = false; ///< Render the hitbox on screen if debug = true.
  /// @param radius  Hitbox radius
  HitboxComponent(float radius);
  void draw() const override;

private:
  const float radius;
};
