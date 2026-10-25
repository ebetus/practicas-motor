#include "Game/ResourceDemoScene.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Components/SpriteComponent.hpp"
#include "Engine/Components/PlayerControllerComponent.hpp"
#include "Engine/SceneManager.hpp"
#include <SDL3_image/SDL_image.h>
#include <iostream>

ResourceDemoScene::ResourceDemoScene(SceneManager* manager, ResourceManager* r , std::string name) 
  : Scene(manager, name) , m_resourceManager(r) {
}

void ResourceDemoScene::Init() {
  m_entities.clear();
  auto background = std::make_unique<GameObject>("Background");
  background->AddComponent<TransformComponent>(Vector2{0.0f, 0.0f}, Vector2{1.0f, 1.0f});
  background->AddComponent<SpriteComponent>(
					    m_resourceManager->GetTexture("assets/background.jpg"), 960.0f, 540.0f);
  m_entities.push_back(std::move(background));

  auto player = std::make_unique<GameObject>("Player");

  player->AddComponent<TransformComponent>(Vector2{480.0f, 440.0f}, Vector2{1.5f, 1.5f});
  player->AddComponent<SpriteComponent>(
					m_resourceManager->GetTexture("assets/player.png"), 32.0f, 32.0f);
  player->AddComponent<PlayerControllerComponent>();
  m_player = player.get();
  m_entities.push_back(std::move(player));

  m_enemyCount = 0;

  for(int i = 0; i < 5; i++) {
    SpawnEnemyRow();
  }

  std::cout << "[ResourceDemoScene] Escena inicializada con éxito.\n";
  PrintMetrics();
}

void ResourceDemoScene::SpawnEnemyRow() {
  float startX = 100.0f;

  float y = 50.0f + (m_enemyCount / 10) * 40.0f; 

  for(int i = 0; i < 10; i++) {
    auto enemy = std::make_unique<GameObject>("Enemy");
    enemy->AddComponent<TransformComponent>(Vector2{startX + (i * 50.0f), y}, Vector2{1.0f, 1.0f});
    enemy->AddComponent<SpriteComponent>(
					 m_resourceManager->GetTexture("assets/enemy.png"), 32.0f, 32.0f);
    m_entities.push_back(std::move(enemy));
    m_enemyCount++;
  }
}

void ResourceDemoScene::PrintMetrics() {
  std::cout << "[Flyweight Metric] Entidades en escena: " << m_entities.size() << "\n";
  std::cout << "[Flyweight Metric] Texturas en VRAM: " << m_resourceManager->GetTextureCount() << " (esperado: 3)\n";
}

void ResourceDemoScene::TriggerDeliberateLeak() {
  std::cout << "[Deliberate Leak] Cargando 50 SDL_Surface sin liberar...\n";

  for(int i = 0; i < 50; i++) {
    SDL_Surface* surface = IMG_Load("assets/enemy.png");
  }
}

void ResourceDemoScene::Update(float dt) {
  for (auto& entity : m_entities) {
    if (entity != nullptr && entity->IsActive()) {
      entity->Update(dt);
    }
  }
}

void ResourceDemoScene::Render(SDL_Renderer* renderer) {

  if (!m_resourceManager->GetRenderer()) {
    m_resourceManager->SetRenderer(renderer);
  }

  SDL_SetRenderDrawColor(renderer, 20, 20, 25, 255);
  SDL_RenderClear(renderer);

  for (auto& entity : m_entities) {
    if (entity != nullptr && entity->IsActive()) {
      entity->Render(renderer);
    }
  }
}

void ResourceDemoScene::HandleEvent(const SDL_Event& event) {
  if (event.type == SDL_EVENT_KEY_DOWN) {
    float speed = 15.0f;

    switch(event.key.scancode){
      // Instanciar nueva fila compartiendo VRAM
    case SDL_SCANCODE_SPACE:
      SpawnEnemyRow();
      PrintMetrics();
      break;
    
      // Vaciado explícito de caché
    case SDL_SCANCODE_C:
      m_resourceManager->Clear(); 
      std::cout << "[ResourceDemoScene] Caché limpiada explícitamente.\n";
      break;
            
      // Provocar la fuga de memoria para ASan
    case SDL_SCANCODE_L:
      TriggerDeliberateLeak();
      break;

      // Salir de la escena o cerrar programa
    case SDL_SCANCODE_ESCAPE:
      m_manager->PopScene();
      break;

    default:
      break;
    }
  }
}
