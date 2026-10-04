#include "../../include/scenes/GameOverScene.hpp"


GameOverScene::GameOverScene(SceneManager *manager , std::string name) : Scene(manager,name){}

void GameOverScene::HandleEvent(const SDL_Event& event) {
  if(event.type == SDL_EVENT_KEY_DOWN) {
    if(event.key.scancode == SDL_SCANCODE_R) {
      //SE CREA UN NUEVO GAMESCENE POR LO QUE SE REINICIA GAMESCENE
      m_manager->ChangeScene(std::move(std::make_unique<GameScene>(m_manager , "GameScene")));
    }else if(event.key.scancode == SDL_SCANCODE_M) {
      m_manager->ChangeScene(std::move(std::make_unique<TitleScene>(m_manager , "TitleScene")));
    }
  }
}

  
void GameOverScene::Render(SDL_Renderer *renderer){
  SDL_SetRenderDrawColor(renderer,245, 60, 39,255);
  
  SDL_RenderClear(renderer);
  SDL_FRect rect {
    190.0f,
    355.0f,
    240.0f,
    135.0f
  };
  SDL_SetRenderDrawColor(renderer, 20, 25, 45, 255);
  SDL_RenderFillRect(renderer, &rect);
  SDL_FRect rect2 {
    670.0f,
    355.0f,
    240.0f,
    135.0f
  };
  SDL_SetRenderDrawColor(renderer,39, 245, 228,255);
  SDL_RenderFillRect(renderer, &rect2);
}

