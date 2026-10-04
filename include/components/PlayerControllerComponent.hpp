#pragma once

#include <SDL3/SDL.h>

#include "core/Component.hpp"
#include "core/GameObject.hpp"
#include "components/TransformComponent.hpp"
#include "components/RectRenderComponent.hpp"
#include "core/Vector2.hpp"


class PlayerControllerComponent : public Component {
public:
  float speed{300.0f};
  bool follow_mouse{true};

  PlayerControllerComponent() = default;
  explicit PlayerControllerComponent(float spd, bool mouse_follow = true);
  void Update(float dt) override;
};
