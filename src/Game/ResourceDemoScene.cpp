#include "Game/ResourceDemoScene.hpp"

ResourceDemoScene::ResourceDemoScene(SceneManager *manager , std::string name) : Scene(manager , name){}

void ResourceDemoScene::HandleEvent(const SDL_Event& event) {
  
}

void ResourceDemoScene::Render(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 15, 15, 15, 255);
  SDL_RenderClear(renderer);
   SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
  SDL_FRect r = {0 , 0 , 30 , 30};
  SDL_RenderFillRect(renderer , &r);
}


