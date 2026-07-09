#pragma once

class Scene;

/// Base class for cross-entity logic that operates on the Scene each frame.
///
/// Subclass this and override update() to define system behavior.
/// Systems are added to a Scene via Scene::addSystem<T>() and run
/// after all component updates.
class System {
public:
  virtual ~System() = default;

  /// Called once per frame after all component updates.
  /// @p dt is elapsed time in seconds since the last frame.
  virtual void update(Scene &scene, float dt) = 0;
};
