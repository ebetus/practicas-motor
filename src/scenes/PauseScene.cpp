#include "../../include/scenes/PauseScene.hpp"

PauseScene::PauseScene(SceneManager *manager , std::string name) : Scene(manager,name){}

void PauseScene::HandleEvent(const SDL_Event& event) {
  if(event.type == SDL_EVENT_KEY_DOWN) {
    if(event.key.scancode == SDL_SCANCODE_P ||
       event.key.scancode == SDL_SCANCODE_ESCAPE) {
      m_manager->PopScene();
    }
  }
}
  
void PauseScene::Render(SDL_Renderer *renderer){
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 175);
  SDL_FRect screen_overlay{0.0f, 0.0f, 960.0f, 540.0f};
  SDL_RenderFillRect(renderer, &screen_overlay);
  SDL_FRect rect {
    240.0f,
    270.0f,
    480.0f,
    230.0f
  };
  SDL_SetRenderDrawColor(renderer,235, 245, 39,100);
  SDL_RenderFillRect(renderer, &rect);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}

