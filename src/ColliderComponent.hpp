#pragma once
#include <SDL3/SDL.h>
#include "Vector2.hpp"
#include "Component.hpp"
#include "GameObject.hpp"
#include "TransformComponent.hpp"

class ColliderComponent : public Component {
public:

  //Desplazamiento relativo a la posicion del TransformComponent
  Vector2 offset{0.0f,0.0f};

  //El tamaño del collider
  Vector2 size{60.0f,60.0f};

  //Marca si es un sensor sin fisica
  bool is_trigger{false};

  //Marca si esta tocando con otro collider
  bool is_colliding{false};

  explicit ColliderComponent(Vector2 size): size(size){}


  SDL_FRect GetWorldBounds() const {
    if(owner == nullptr)
      return {offset.x,offset.y,size.x,size.y};
    TransformComponent* transform = owner->GetComponent<TransformComponent>();
    if(transform == nullptr)
      return {offset.x,offset.y,size.x,size.y};
    float x = transform->position.x + (offset.x * transform->scale.x);
    float y = transform->position.y + (offset.y * transform->scale.y);
    float w = size.x * transform->scale.x;
    float h = size.y * transform->scale.y;
    return {x,y,w,h};
  }

  void RenderDebug(SDL_Renderer *renderer) {
    auto bounds = GetWorldBounds();
    if(is_colliding)
      SDL_SetRenderDrawColor(renderer, 255, 50, 50 ,255);
    else
      SDL_SetRenderDrawColor(renderer, 20, 255, 50 ,255);
    SDL_RenderRect(renderer, &bounds);
  }

  
  
};
