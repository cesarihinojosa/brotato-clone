#include "component.hpp"
#include "raylib.h"

/// Renders a static texture at the owner's position.
///
/// Requires: TransformComponent on owner.
class SpriteComponent : public Component {
public:
  /// @param filename  Path to the texture file to load.
  /// @param scale     Draw scale factor. Clamped to [0.02, 100].
  SpriteComponent(const char *filename, float scale);
  ~SpriteComponent();
  void draw() const override;

private:
  Texture2D texture;
  const float scale;
};
