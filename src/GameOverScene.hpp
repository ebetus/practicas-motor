#pragma once


#include "Scene.hpp"
#include <SDL3/SDL.h>
#include "GameScene.hpp"
#include "TitleScene.hpp"

class GameOverScene : public Scene {

  void HandleEvent(const SDL_Event& event) {
    if(event.type == SDL_EVENT_KEY_DOWN) {
      if(event.key.scancode == SDL_SCANCODE_R) {
	//SE CREA UN NUEVO GAMESCENE POR LO QUE SE REINICIA GAMESCENE
	m_manager->ChangeScene(std::make_unique<GameScene>(m_manager));
      }else if(event.key.scancode == SDL_SCANCODE_M) {
	m_manager->ChangeScene(std::make_unique<TitleScene>(m_manager));
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
    SDL_FRect rect2 {
      220.0f,
      220.0f,
      500.0f,
      500.0f
    };
    SDL_RenderFillRect(renderer, &rect2);
  }

  
  
};
