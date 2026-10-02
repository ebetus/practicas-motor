#pragma once

#include <SDL3/SDL.h>
#include "Scene.hpp"
#include "PauseScene.hpp"
#include "GameOverScene.hpp"
#include "Vector2.hpp"
#include "GameObject.hpp"
#include "TransformComponent.hpp"
#include "RectRenderComponent.hpp"
#include "PlayerControllerComponent.hpp"
#include "PatrolComponent.hpp"
#include "CollisionManager.hpp"
#include "BallComponent.hpp"
#include "SceneManager.hpp"

#include <memory>

class GameScene : public Scene {
private:
  std::unique_ptr<CollisionManager> m_collisionManager;
  float m_physicsAccumulator{0.0f};
  bool m_debugDraw{false};

public:

  GameScene() = default;
  
  explicit GameScene(SceneManager *manager , std::string name) : Scene(manager,name){
    m_collisionManager = std::make_unique<CollisionManager>(&m_entities);
  }

  void Init() override {
    m_entities.clear();
    m_collisionManager->SetEntities(&m_entities);
    auto player = std::make_unique<GameObject>("Player");
    player->AddComponent<TransformComponent>(Vector2{440.0f, 240.0f},
					     Vector2{1.0f, 1.0f});
    player->AddComponent<RectRenderComponent>(Vector2{60.0f, 60.0f},
					      SDL_Color{60, 180, 100, 255});
    player->AddComponent<ColliderComponent>(Vector2{60.0f,60.0f});
    player->AddComponent<PlayerControllerComponent>(300.0f, true);
    m_entities.push_back(std::move(player));

    auto obstacle = std::make_unique<GameObject>("Obstacle");
    obstacle->AddComponent<TransformComponent>(Vector2{150.0f, 120.0f},
					       Vector2{1.5f, 1.5f});
    obstacle->AddComponent<RectRenderComponent>(Vector2{40.0f, 40.0f},
						SDL_Color{220, 70, 70, 255});
    obstacle->AddComponent<PatrolComponent>(120.0f, 100.0f);
    obstacle->AddComponent<ColliderComponent>(Vector2{40.0f,40.0f});
    m_entities.push_back(std::move(obstacle));

    auto ball = std::make_unique<GameObject>("Ball");
    ball->AddComponent<TransformComponent>(Vector2{468.0f , 80.0f});
    ball->AddComponent<RectRenderComponent>(Vector2{24.0f, 24.0f},
					    SDL_Color{240, 210, 60, 255});
    ball->AddComponent<ColliderComponent>(Vector2{24.0f,24.0f});
    ball->AddComponent<BallComponent>();
    m_entities.push_back(std::move(ball));
  }

  void Update(float dt) override {
    constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;
    m_physicsAccumulator += dt;
    while (m_physicsAccumulator >= FIXED_TIMESTEP) {
      for (auto &entity : m_entities)
	entity->Update(FIXED_TIMESTEP);
      m_collisionManager->CheckCollisions();
      m_physicsAccumulator -= FIXED_TIMESTEP;
    }
  }

  //Aqui va todo lo del juego.
  void HandleEvent(const SDL_Event& event) override {
    if(event.type == SDL_EVENT_KEY_DOWN) {
      if(event.key.scancode == SDL_SCANCODE_F1) {
	m_debugDraw = !m_debugDraw;
      }
      if(event.key.scancode == SDL_SCANCODE_P ||
	 event.key.scancode == SDL_SCANCODE_ESCAPE) {
	m_manager->PushScene(std::move(std::make_unique<PauseScene>(m_manager , "PauseScene")));
      }
      if(event.key.scancode == SDL_SCANCODE_G) {
	m_manager->ChangeScene(std::move(std::make_unique<GameOverScene>(m_manager , "PauseScene")));
      }
    }
  }

  void Render(SDL_Renderer *renderer) override {
     SDL_SetRenderDrawColor(renderer, 25, 25, 30, 255);
     SDL_RenderClear(renderer);
     for (auto &entity : m_entities)
       entity->Render(renderer);
     if (m_debugDraw) {
       for (auto &entity : m_entities) {
	 if (auto *col = entity->GetComponent<ColliderComponent>()) {
	   col->RenderDebug(renderer);
	 }
       }
     }
  }
};
