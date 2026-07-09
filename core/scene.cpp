#include "scene.hpp"
#include "game_object.hpp"
#include "system.hpp"
#include <memory>

GameObject &Scene::spawn() {
  objects.push_back(std::make_unique<GameObject>());
  return *objects.back();
}

void Scene::update(float dt) {
  for (auto &o : objects)
    o->update(dt);
  for (auto &s : systems)
    s->update(*this, dt);
}

void Scene::draw() const {
  for (auto &o : objects)
    o->draw();
}
