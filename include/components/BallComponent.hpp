#pragma once

#include <cmath>
#include "../core/Component.hpp"
#include "../core/Vector2.hpp"
#include "components/TransformComponent.hpp"

class BallComponent : public Component{
public:
  Vector2 velocity{220.0f , 180.f};

  void Update(float dt);

  void OnCollision(GameObject *other);
};
