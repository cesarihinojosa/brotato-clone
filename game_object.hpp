#pragma once

#include "component.hpp"
#include <algorithm>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <utility>

class GameObject {
public:
  bool alive = true;

  // Factory method to auto generate functions based off Component
  // implementaions
  template <typename T, typename... Args> T &addComponent(Args &&...args) {
    // Call the constructor for Component T
    auto c = std::make_unique<T>(std::forward<Args>(args)...);
    // Ref is an alias of c to avoid dereferencing c
    T &ref = *c;
    // The component's owner is this GameObject
    ref.owner = this;
    // Add component to the HashMap using type_index to hash the type and map it
    // to the Component's pointer
    components[std::type_index(typeid(T))] = std::move(c);
    // Call the component's start() method;
    ref.start();
    return ref;
  }

  template <typename T> T &getComponent() {
    auto it = components.find(std::type_index(typeid(T)));
    return it == components.end() ? nullptr
                                  : static_cast<T *>(it->second.get());
  }

  // Go through each component in components and call it's update()
  void update(float dt) {
    for (auto &[type, component] : components)
      component->update(dt);
  }

  // Go through each component in components and call it's draw()
  void draw() {
    for (auto &[type, component] : components)
      component->draw();
  }

private:
  std::unordered_map<std::type_index, std::unique_ptr<Component>> components;
};
