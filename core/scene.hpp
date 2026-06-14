#pragma once
#include "game_object.hpp"
#include <memory>
#include <vector>

/// Manages all GameObjects and drives the main update/draw loop.
class Scene {
public:
  /// Creates a new empty GameObject, adds it to the scene, and returns a reference.
  /// The reference remains valid for the lifetime of the Scene.
  GameObject &spawn();

  /// Calls update(dt) on all living GameObjects.
  void update(float dt);

  /// Calls draw() on all living GameObjects.
  void draw() const;

private:
  std::vector<std::unique_ptr<GameObject>> objects;
};
