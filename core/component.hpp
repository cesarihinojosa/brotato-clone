#pragma once

class GameObject;

/// Base class for all components in the engine.
///
/// Subclass this and override start(), update(), and/or draw() to define
/// entity behavior. The engine calls these automatically through the owning
/// GameObject.
class Component {
public:
  /// The GameObject this component is attached to.
  /// Always set before start() is called; never null during update() or draw().
  GameObject *owner = nullptr;

  virtual ~Component() = default;

  /// Called once immediately when addComponent<T>() is invoked on the owner.
  virtual void start() {}

  /// Called once per frame. @p dt is elapsed time in seconds since the last frame.
  virtual void update(float dt) {}

  /// Called once per frame inside BeginDrawing()/EndDrawing().
  virtual void draw() const {}
};
