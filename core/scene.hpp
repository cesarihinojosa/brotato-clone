#pragma once
#include "game_object.hpp"
#include <memory>
#include <vector>

class Scene {
public:
  GameObject &spawn();
  void update(float dt);
  void draw() const;

private:
  std::vector<std::unique_ptr<GameObject>> objects;
};
