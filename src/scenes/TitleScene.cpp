#include "scenes/TitleScene.hpp"

TitleScene::TitleScene(SceneManager *manager , std::string name) : Scene(manager,name){}

void TitleScene::HandleEvent(const SDL_Event& event) {
  if(event.type == SDL_EVENT_KEY_DOWN) {
    if(event.key.scancode == SDL_SCANCODE_SPACE ||
       event.key.scancode == SDL_SCANCODE_RETURN) {
      m_manager->ChangeScene(std::move(std::make_unique<GameScene>(m_manager , "GameScene")));
    }
  }
}

  
void TitleScene::Render(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 20, 25, 45, 255);
  SDL_RenderClear(renderer);
  SDL_FRect rect {
    240.0f,
    135.0f,
    480.0f,
    270.0f
  };
  SDL_SetRenderDrawColor(renderer,39, 245, 70,255);
  SDL_RenderFillRect(renderer, &rect);
}

