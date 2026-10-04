#pragma once

#include <SDL3/SDL.h>
#include <memory>
#include "../core/Scene.hpp"
#include "GameScene.hpp"
#include "TitleScene.hpp"

class GameOverScene : public Scene {
public:
  explicit GameOverScene(SceneManager *manager , std::string name);
  
  void HandleEvent(const SDL_Event& event) override;

  void Render(SDL_Renderer *renderer) override;
  
};
