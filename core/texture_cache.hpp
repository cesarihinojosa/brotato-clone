#include "raylib.h"
#include <string>
#include <unordered_map>

class TextureCache {
public:
  Texture2D get(const std::string &filename);
  void unloadAll();

private:
  std::unordered_map<std::string, Texture2D> cache;
};
