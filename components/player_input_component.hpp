#pragma once
#include "component.hpp"

class PlayerInputComponent : public Component {
public:
  void update(float dt) override;
};
