#pragma once

#include <SDL3/SDL.h>

#include "../core/Component.hpp"
#include "../core/GameObject.hpp"
#include "TransformComponent.hpp"
#include "../core/Vector2.hpp"

class RectRenderComponent : public Component {
public:
  Vector2 size{60.0f, 60.0f};
  SDL_Color color{60, 180, 100, 255};
  RectRenderComponent() = default;
  RectRenderComponent(Vector2 sz, SDL_Color col);

  void Render(SDL_Renderer *renderer) override;

};
