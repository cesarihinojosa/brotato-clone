#pragma once

#include "component.hpp"
#include <algorithm>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <utility>

/// A container for components that defines an entity in the game world.
///
/// GameObjects are created via Scene::spawn() and never constructed directly.
/// Add behavior with addComponent<T>() and retrieve it with getComponent<T>().
class GameObject {
public:
  /// When false, the Scene skips updating and drawing this object.
  bool alive = true;

  /// Creates a component of type T, attaches it to this GameObject, and returns a reference.
  ///
  /// Calls start() on the component immediately after attaching it.
  /// Only one component of each type is allowed per GameObject.
  template <typename T, typename... Args> T &addComponent(Args &&...args) {
    auto c = std::make_unique<T>(std::forward<Args>(args)...);
    T &ref = *c;
    ref.owner = this;
    components[std::type_index(typeid(T))] = std::move(c);
    ref.start();
    return ref;
  }

  /// Returns a pointer to the component of type T, or nullptr if not present.
  template <typename T> T *getComponent() {
    auto it = components.find(std::type_index(typeid(T)));
    return it == components.end() ? nullptr
                                  : static_cast<T *>(it->second.get());
  }

  /// Calls update(dt) on all attached components. Order is unspecified.
  void update(float dt) {
    for (auto &[type, component] : components)
      component->update(dt);
  }

  /// Calls draw() on all attached components. Order is unspecified.
  void draw() const {
    for (auto &[type, component] : components)
      component->draw();
  }

private:
  std::unordered_map<std::type_index, std::unique_ptr<Component>> components;
};
