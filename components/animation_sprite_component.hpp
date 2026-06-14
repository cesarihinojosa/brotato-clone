#include "component.hpp"
#include "raylib.h"

class AnimationSpriteComponent : public Component {
public:
  AnimationSpriteComponent(const char *filename, float scale, float max_bob,
                           float speed);
  ~AnimationSpriteComponent();
  void draw() const override;
  void update(float dt) override;

private:
  Texture2D texture;
  const float scale;
  const float max_bob;
  const float speed;
  float current_height;
  float current_bob;
  bool up;
};
