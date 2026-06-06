#pragma once

class GameObject;

class Component {
public:
  GameObject *owner = nullptr;
  virtual ~Component() = default;
  virtual void start() {}
  virtual void update(float dt) {}
  virtual void draw() {}
};
