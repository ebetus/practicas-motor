#pragma once

#include "Engine/Scene.hpp"
#include "Engine/ResourceManager.hpp"
#include <SDL3/SDL.h>
#include <string>

class ResourceDemoScene : public Scene {
public:
  ResourceDemoScene(SceneManager* manager, ResourceManager* r , std::string name);
  ~ResourceDemoScene() override = default;

  void Init() override;
  void Update(float dt) override;
  void Render(SDL_Renderer* renderer) override;
  void HandleEvent(const SDL_Event& event) override;
  void Exit() override;

private:
  void SpawnEnemyRow();
  void TriggerDeliberateLeak();
  void PrintMetrics();
  GameObject* m_player{nullptr}; 
  int m_enemyCount{0};
};
