#pragma once

#include "GameScene.hpp"
#include "Scene.hpp"
#include <SDL3/SDL.h>
#include <memory>


class TitleScene : public Scene {

public:
  
  TitleScene() = default;

  explicit TitleScene(SceneManager *manager , std::string name) : Scene(manager,name){}

  void HandleEvent(const SDL_Event& event) {
    if(event.type == SDL_EVENT_KEY_DOWN) {
      if(event.key.scancode == SDL_SCANCODE_SPACE ||
	 event.key.scancode == SDL_SCANCODE_RETURN) {
	m_manager->ChangeScene(std::move(std::make_unique<GameScene>(m_manager , "GameScene")));
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
