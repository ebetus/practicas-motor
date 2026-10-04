#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include "Component.hpp"
#include "../components/ColliderComponent.hpp"
#include "GameObject.hpp"
#include "../components/TransformComponent.hpp"

class CollisionManager {
public:

  std::vector<std::unique_ptr<GameObject>> *m_entities;
  
  explicit CollisionManager(std::vector<std::unique_ptr<GameObject>> *entities);
  
  void SetEntities(std::vector<std::unique_ptr<GameObject>> *entities);
  
  bool CheckAABB(const SDL_FRect &a , const SDL_FRect &b);

  bool CheckCollision(const ColliderComponent &a , const ColliderComponent &b);

  void CheckCollisions();
};

