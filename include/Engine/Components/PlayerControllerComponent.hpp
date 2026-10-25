#pragma once

#include <SDL3/SDL.h>

#include "Engine/Component.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/Components/TransformComponent.hpp"



class PlayerControllerComponent : public Component {
public:

  PlayerControllerComponent() = default;
  void Update(float dt) override;
  std::unique_ptr<Component> Clone() const override;
};
