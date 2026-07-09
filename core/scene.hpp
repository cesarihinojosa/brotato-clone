#pragma once
#include "game_object.hpp"
#include "system.hpp"
#include <memory>
#include <tuple>
#include <utility>
#include <vector>

/// Manages all GameObjects and drives the main update/draw loop.
class Scene {
public:
  /// Creates a new empty GameObject, adds it to the scene, and returns a
  /// reference. The reference remains valid for the lifetime of the Scene.
  GameObject &spawn();

  /// Updates all components, then runs all systems in registration order.
  void update(float dt);

  /// Calls draw() on all living GameObjects.
  void draw() const;

  /// Creates a system of type T and adds it to the scene.
  /// Systems run in the order they are added, after component updates.
  template <typename T, typename... Args> void addSystem(Args &&...args) {
    systems.push_back(std::make_unique<T>(std::forward<Args>(args)...));
  }

  /// Returns all living GameObjects that have every component in Ts,
  /// along with references to those components.
  template <typename... Ts>
  std::vector<std::tuple<GameObject &, Ts &...>> view() {
    std::vector<std::tuple<GameObject &, Ts &...>> result;
    for (auto &o : objects) {
      if (!o->alive)
        continue;
      auto ptrs = std::make_tuple(o->getComponent<Ts>()...);
      if ((std::get<Ts *>(ptrs) && ...)) {
        result.emplace_back(*o, *std::get<Ts *>(ptrs)...);
      }
    }
    return result;
  }

private:
  std::vector<std::unique_ptr<GameObject>> objects;
  std::vector<std::unique_ptr<System>> systems;
};
