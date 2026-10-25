#pragma once

#include <SDL3/SDL.h>
#include <memory>
#include "Engine/Scene.hpp"


class ResourceDemoScene : public Scene {


public:

  ResourceDemoScene() = default;

  explicit ResourceDemoScene(SceneManager *manager , std::string name);

  void HandleEvent(const SDL_Event& event) override;

  void Render(SDL_Renderer *renderer) override;
};
