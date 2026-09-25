#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include "Component.hpp"
#include "ColliderComponent.hpp"
#include "GameObject.hpp"
#include "TransformComponent.hpp"

class CollisionManager {
public:

  std::vector<std::unique_ptr<GameObject>> *m_entities;
  
  explicit CollisionManager(std::vector<std::unique_ptr<GameObject>> *entities)
    : m_entities{entities}{}
  //Entidades que pueden tener colliders
  

  bool CheckAABB(const SDL_FRect &a , const SDL_FRect &b){
    return (a.x < b.x + b.w &&
	    a.x + a.w > b.x &&
	    a.y < b.y + b.h &&
	    a.y + a.h > b.y);
  }

  bool CheckCollision(const ColliderComponent &a , const ColliderComponent &b) {
    return CheckAABB(a.GetWorldBounds(), b.GetWorldBounds());
  }

  void CheckCollisions() {
    for(auto &entity : *m_entities) {
      ColliderComponent* c = entity->GetComponent<ColliderComponent>();
      if(c != nullptr)
	c->is_colliding = false;
    }
    for(size_t i = 0 ; i < m_entities->size() ; i++) {
      for(size_t j = i+1 ; j < m_entities->size() ; j++){
	ColliderComponent* colA = (*m_entities)[i]->GetComponent<ColliderComponent>();
	ColliderComponent* colB = (*m_entities)[j]->GetComponent<ColliderComponent>();
	if(colB == nullptr || colA == nullptr)
	  continue;
	bool colliding = CheckCollision(*colA, *colB);
	if(colliding){
	  colA->is_colliding = colliding;
	  colB->is_colliding = colliding;
	  (*m_entities)[i]->OnCollision((*m_entities)[j].get());
	  (*m_entities)[j]->OnCollision((*m_entities)[i].get());
	  
	}
      }
    }

    
  }
};

