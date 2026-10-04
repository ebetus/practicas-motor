#pragma once

#include <SDL3/SDL.h>
#include <memory>
#include "GameScene.hpp"
#include "../core/Scene.hpp"



class TitleScene : public Scene {

public:
  
  TitleScene() = default;

  explicit TitleScene(SceneManager *manager , std::string name);

  void HandleEvent(const SDL_Event& event) override;
  
  void Render(SDL_Renderer *renderer) override;

};
