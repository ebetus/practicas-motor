#pragma once

#include <SDL3/SDL.h>
#include "Engine/Component.hpp"

class SpriteComponent : public Component {
private:
  SDL_Texture* m_texture;
  float m_width, m_height;
  SDL_FRect m_srcRect{0.0f, 0.0f, 0.0f, 0.0f};
  bool m_useSrcRect = false;
  SDL_FColor m_colorMod{1.0f, 1.0f, 1.0f, 1.0f};
  SDL_FlipMode m_flip = SDL_FLIP_NONE; 

public:
  SpriteComponent() = default;

  explicit SpriteComponent(SDL_Texture* t, float w, float h);

  explicit SpriteComponent(SDL_Texture* t, float w, float h,
			   SDL_FRect r, SDL_FColor c);
    
  void Render(SDL_Renderer *renderer) override;

  std::unique_ptr<Component> Clone() const override;
};
