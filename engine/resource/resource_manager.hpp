#include "../core/interface/renderer.hpp"

#include <string>
#include <unordered_map>

class ResourceManager {
public:
  static ResourceManager &getInstance() {
    static ResourceManager instance;
    return instance;
  }

  Texture2D getTexture(const std::string &path) {
    auto it = textures.find(path);
    if (it != textures.end()) {
      return it->second;
    } else {
      Texture2D texture = Renderer::instance().loadTexture2D(path.c_str());
      textures[path] = texture;
      return texture;
    }
  }

  Image getImage(const std::string &path) {
    auto it = images.find(path);
    if (it != images.end()) {
      return it->second;
    } else {
      Image image = Renderer::instance().loadNewImage(path.c_str());
      images[path] = image;
      return image;
    }
  }

private:
  ResourceManager() {}
  ~ResourceManager() { unloadAllTextures(); }

  ResourceManager(const ResourceManager &) = delete;

  std::unordered_map<std::string, Texture2D> textures;
  std::unordered_map<std::string, Image> images;

  void unloadAllTextures() {
    for (auto &pair : textures) {
      Renderer::instance().unloadTexture2D(pair.second);
    }
    textures.clear();
  }
};
