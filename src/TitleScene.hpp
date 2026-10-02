#pragma once

#include "GameScene.hpp"
#include "Scene.hpp"
#include <SDL3/SDL.h>


class TitleScene : public Scene {

  void HandleEvent(const SDL_Event& event) {
    if(event.type == SDL_EVENT_KEY_DOWN) {
      if(event.key.scancode == SDL_SCANCODE_SPACE ||
	 event.key.scancode == SDL_SCANCODE_RETURN) {
	m_manager->ChangeScene(std::make_unique<GameScene>(m_manager));
      }
    }
  }

  
  void Render(SDL_Renderer *renderer) override {
    SDL_SetRenderDrawColor(renderer, 20, 25, 45, 255);
    SDL_RenderClear(renderer);
    SDL_FRect rect {
      540.0f,
      540.0f,
      750.0f,
      750.0f
    };
    SDL_RenderFillRect(renderer, &rect);
  }

  
  
};
