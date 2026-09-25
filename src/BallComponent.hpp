#pragma once

#include <cmath>
#include "Component.hpp"
#include "Vector2.hpp"
#include "TransformComponent.hpp"

class BallComponent : public Component{
public:
  Vector2 velocity{220.0f , 180.f};


  void Update(float dt){
    TransformComponent *transform = owner->GetComponent<TransformComponent>();
    if(transform == nullptr)
      return;
    transform->Translate(velocity*dt);
    if(transform->position.x  <= 0){
      velocity.x = std::abs(velocity.x);
    }
    if((transform->position + (transform->scale * 0.5)).x >= 960) {
      velocity.x = -std::abs(velocity.x);
    }
    if(transform->position.y <= 0){
      velocity.y = std::abs(velocity.y);
    }
    if((transform->position + (transform->scale * 0.5)).y >= 540) {
      velocity.y = -std::abs(velocity.y);
    }

  }

  void OnCollision(GameObject *other) {
    TransformComponent* tother = other->GetComponent<TransformComponent>();
    TransformComponent* tmine = owner->GetComponent<TransformComponent>();
    if(tother == nullptr || tmine == nullptr)
      return;
    
    Vector2 cp = tother->position + (tother->scale * 0.5f);
    Vector2 op = tmine->position + (tmine->scale * 0.5f);
    Vector2 d = cp-op;
    if(std::abs(d.x) > std::abs(d.y)) {
      velocity.x = d.x > 0 ? -std::abs(velocity.x) : std::abs(velocity.x);
     
    }else {
      velocity.y = d.y > 0 ? -std::abs(velocity.y) : std::abs(velocity.y);
    
    }
    SDL_Log("Colisión");
  }
};
