#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include "Scene.hpp"


enum class SceneAction {
  None,
  Change,
  Push,
  Pop,
  Clear
};

class SceneManager {

private:
  std::vector<std::unique_ptr<Scene>> m_scenes;
  
  SceneAction m_pendingAction{SceneAction::None};
  
  std::unique_ptr<Scene> m_pendingScene{nullptr};

  void popSceneFromScenes() {
    if(m_scenes.size() != 0){
      auto &scene = m_scenes.back();
      m_scenes.pop_back();
      scene->Exit();
    }
  }

  void transferPendingScene() {
    if(m_pendingScene != nullptr){
      m_scenes.push_back(std::move(m_pendingScene));
      m_pendingScene->Init();
    }
  }

public:
  void ChangeScene(std::unique_ptr<Scene> new_scene) {
    m_pendingAction = SceneAction::Change;
    m_pendingScene = std::move(new_scene);
  }

  void PushScene(std::unique_ptr<Scene> new_scene) {
     m_pendingAction = SceneAction::Push;
     m_pendingScene = std::move(new_scene);
  }

  void PopScene() {
     m_pendingAction = SceneAction::Pop;
  }

  void Clear() {
    //Sacar escenas y ejecutar exit
    while(m_scenes.size() != 0) {
      popSceneFromScenes();
    }
  }

  void ProcessPendingChanges() {
    switch(m_pendingAction) {
    case SceneAction::None:
      return;
    case SceneAction::Change:
      popSceneFromScenes();
      transferPendingScene();
      break;
    case SceneAction::Push:
      transferPendingScene();
      break;
    case SceneAction::Pop:
      popSceneFromScenes();
      break;
    case SceneAction::Clear:
      Clear();
      break;
    }
    m_pendingAction = SceneAction::None;
    m_pendingScene.reset();
  }

  void HandleEvent(const SDL_Event &event) {
    if(m_scenes.size() != 0) {
      m_scenes.back()->HandleEvent(event);
    }
  }

  void Update(float dt) {
    if(m_scenes.size() != 0) {
      m_scenes.back()->Update(dt);
    }
  }

  void Render(SDL_Renderer *renderer) {
    for(auto &scene : m_scenes){
      scene->Render(renderer);
    }
  }

  bool HasScenes() {
    return m_scenes.size() != 0;
  }

};
