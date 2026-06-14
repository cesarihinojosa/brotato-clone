#include "component.hpp"
#include "raylib.h"

class SpriteComponent : public Component {
public:
  SpriteComponent(const char *filename, float scale);
  ~SpriteComponent();
  void draw() const override;

private:
  Texture2D texture;
  float scale;
};
