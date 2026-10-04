#pragma once

#include <SDL3/SDL.h>
#include <memory>
#include "../core/Scene.hpp"
#include "PauseScene.hpp"
#include "GameOverScene.hpp"
#include "../core/Vector2.hpp"
#include "../core/GameObject.hpp"
#include "../components/TransformComponent.hpp"
#include "../components/RectRenderComponent.hpp"
#include "../components/PlayerControllerComponent.hpp"
#include "../components/PatrolComponent.hpp"
#include "../core/CollisionManager.hpp"
#include "../components/BallComponent.hpp"
#include "../core/SceneManager.hpp"

class GameScene : public Scene {
private:
  std::unique_ptr<CollisionManager> m_collisionManager;
  float m_physicsAccumulator{0.0f};
  bool m_debugDraw{false};

public:

  GameScene() = default;
  
  explicit GameScene(SceneManager *manager , std::string name);

  void Init() override;

  void Update(float dt) override;

  void HandleEvent(const SDL_Event& event) override;

  void Render(SDL_Renderer *renderer) override;
};
