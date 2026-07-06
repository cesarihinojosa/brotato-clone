#include "component.hpp"
#include "raylib.h"

/// Renders a static texture at the owner's position.
///
/// Requires: TransformComponent on owner.
class SpriteComponent : public Component {
public:
  /// @param texture   Texture to load
  /// @param scale     Draw scale factor. Clamped to [0.02, 100].
  SpriteComponent(const Texture2D texture, float scale);
  ~SpriteComponent();
  void draw() const override;

private:
  const Texture2D texture;
  const float scale;
};
