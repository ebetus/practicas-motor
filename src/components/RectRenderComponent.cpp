#include "../../include/components/RectRenderComponent.hpp"

RectRenderComponent::RectRenderComponent(Vector2 sz, SDL_Color col) : size(sz), color(col){}

void RectRenderComponent::Render(SDL_Renderer *renderer){
  if (!owner) return;
    
  TransformComponent *transform = owner->GetComponent<TransformComponent>();
  if (!transform)
    return; // No podemos renderizar si la entidad no tiene posicion en el mundo


  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b,color.a);

  SDL_FRect rect{
    transform->position.x,
    transform->position.y,
    size.x * transform->scale.x,
    size.y * transform->scale.y
    
  };
  SDL_RenderFillRect(renderer, &rect);


}

