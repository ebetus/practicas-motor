#include "Engine/ResourceManager.hpp"
#include <iostream>


ResourceManager::ResourceManager(SDL_Renderer *renderer) : m_renderer(renderer) {}

ResourceManager::~ResourceManager() {
  Clear();
}

SDL_Texture* ResourceManager::GetTexture(const std::string &filepath) {
  auto it = m_textures.find(filepath);
  if (it != m_textures.end()) {
    return it->second.get(); 
  }
  if (m_renderer == nullptr) {
    std::cerr << "[ResourceManager] Error: Renderer nulo al cargar " << filepath << "\n";
    return nullptr;
  }
  SDL_Surface* surface = IMG_Load(filepath.c_str());
  if (surface == nullptr) {
    std::cerr << "[ResourceManager] Error IMG_Load: " << SDL_GetError() << "\n";
    return nullptr;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);

  SDL_DestroySurface(surface); 

  if (texture == nullptr) {
    std::cerr << "[ResourceManager] Error SDL_CreateTextureFromSurface: " << SDL_GetError() << "\n";
    return nullptr;
  }

  m_textures[filepath] = TexturePtr(texture);
    
  std::cout << "[ResourceManager] Textura cargada en VRAM exitosamente: '" << filepath << "'\n";
  return texture;
}

bool ResourceManager::HasTexture(const std::string &filepath) const {
  return m_textures.find(filepath) != m_textures.end();
}

bool ResourceManager::UnloadTexture(const std::string &filepath) {

  return m_textures.erase(filepath) > 0;
}

void ResourceManager::Clear() {

  m_textures.clear();
}

