#pragma once

#include "GameScene.hpp"
#include "Scene.hpp"
#include <SDL3/SDL.h>


class PauseScene : public Scene {
public:
  explicit PauseScene(SceneManager *manager , std::string name) : Scene(manager,name){}

  void HandleEvent(const SDL_Event& event) {
    if(event.type == SDL_EVENT_KEY_DOWN) {
      if(event.key.scancode == SDL_SCANCODE_P ||
	 event.key.scancode == SDL_SCANCODE_ESCAPE) {
	m_manager->PopScene();
      }
    }
  }
  
  void Render(SDL_Renderer *renderer) override {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 175);
    SDL_FRect screen_overlay{0.0f, 0.0f, 960.0f, 540.0f};
    SDL_RenderFillRect(renderer, &screen_overlay);
    SDL_FRect rect {
      540.0f,
      540.0f,
      750.0f,
      750.0f
    };
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
  }

  
  
};
