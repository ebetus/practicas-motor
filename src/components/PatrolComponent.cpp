#include "../../include/components/PatrolComponent.hpp"

PatrolComponent::PatrolComponent(float spd, float dist) : speed(spd), distance(dist) {}

void PatrolComponent::Init(){
  if (auto *t = owner->GetComponent<TransformComponent>()) {
    origin_x = t->position.x;
  }
}

void PatrolComponent::Update(float dt){
  if (auto *t = owner->GetComponent<TransformComponent>()) {
    timer += dt * (speed / 50.0f);
    t->position.x = origin_x + std::sin(timer) * distance;
  }
}
