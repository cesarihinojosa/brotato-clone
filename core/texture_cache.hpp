#pragma once
#include "raylib.h"
#include <string>
#include <unordered_map>

/// Caches loaded textures so each file is only read from disk once.
class TextureCache {
public:
  /// Returns the texture for @p filename, loading it on first access.
  Texture2D get(const std::string &filename);

  /// Unloads all cached textures. Call before CloseWindow().
  void unloadAll();

private:
  std::unordered_map<std::string, Texture2D> cache;
};
