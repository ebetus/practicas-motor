#include "Engine/Components/SpriteComponent.hpp"
#include "Engine/GameObject.hpp"                 
#include "Engine/Components/TransformComponent.hpp"

SpriteComponent::SpriteComponent(SDL_Texture* t, float w, float h) 
  : m_texture(t), m_width(w), m_height(h) {
  m_colorMod = SDL_FColor{1.0f, 1.0f, 1.0f, 1.0f};
}

SpriteComponent::SpriteComponent(SDL_Texture* t, float w, float h,
                                 SDL_FRect r, SDL_FColor c) 
  : m_texture(t), m_width(w), m_height(h),
    m_srcRect(r), m_useSrcRect(true), m_colorMod(c) {}

void SpriteComponent::Render(SDL_Renderer *renderer) {
  if (!renderer || !m_texture) {
    return;
  }
    
  SDL_FRect dstRect{0.0f, 0.0f, m_width, m_height};
  double rotation = 0.0;
    
  if (owner) {
    auto *transform = owner->GetComponent<TransformComponent>();
    if (transform) {
      dstRect.x = transform->position.x;
      dstRect.y = transform->position.y;
      dstRect.w = (m_useSrcRect ? m_srcRect.w : m_width) * transform->scale.x;
      dstRect.h = (m_useSrcRect ? m_srcRect.h : m_height) * transform->scale.y;
    }
  }
    
  SDL_SetTextureColorModFloat(m_texture, m_colorMod.r, m_colorMod.g, m_colorMod.b);
  SDL_SetTextureAlphaModFloat(m_texture, m_colorMod.a);
    
  const SDL_FRect *src = m_useSrcRect ? &m_srcRect : nullptr;
  SDL_RenderTextureRotated(renderer, m_texture, src, &dstRect, rotation, nullptr, m_flip);

  SDL_SetTextureColorModFloat(m_texture, 1.0f, 1.0f, 1.0f);
  SDL_SetTextureAlphaModFloat(m_texture, 1.0f);
}

std::unique_ptr<Component> SpriteComponent::Clone() const {
  return std::make_unique<SpriteComponent>(*this);
}
