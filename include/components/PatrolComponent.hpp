#pragma once
#include <cmath>
#include "../core/Component.hpp"
#include "../core/GameObject.hpp"
#include "TransformComponent.hpp"

class PatrolComponent : public Component
{
public:
  float speed{100.0f};
  float distance{150.0f};
  float origin_x{0.0f};
  float timer{0.0f};

  PatrolComponent(float spd, float dist);

  void Init() override;

  void Update(float dt) override;
};
