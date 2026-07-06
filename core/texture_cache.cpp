#include "texture_cache.hpp"
#include "raylib.h"
#include <string>

Texture2D TextureCache::get(const std::string &filename) {
  auto it = cache.find(filename);
  if (it != cache.end()) {
    return it->second;
  }
  Texture2D t = LoadTexture(filename.c_str());
  cache[filename] = t;
  return t;
}

void TextureCache::unloadAll() {
  for (auto &[_, t] : cache) {
    UnloadTexture(t);
  }
  cache.clear();
}
