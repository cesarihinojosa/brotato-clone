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

  template <typename T, typename... Args> T &addComponent(Args &&...args) {
    auto c = std::make_unique<T>(std::forward<Args>(args)...);
    T &ref = *c;
    ref.owner = this;
    components[std::type_index(typeid(T))] = std::move(c);
    ref.start();
    return ref;
  }

private:
  std::unordered_map<std::type_index, std::unique_ptr<Component>> components;
};
